#include <assert.h>
#include <sstream>

#include "Application.h"
#include "Block.h"
#include "Game.h"
#include "GameStatePlaying.h"
#include "randomizer.h"
#include "SimpleBlockFactory.h"
#include "Text.h"
#include "ThreeHitBlock.h"
#include "ThreeHitBlockFactory.h"
#include "UnbreackableBlockFactory.h"

namespace Arkanoid
{
	GameStatePlayingData::GameStatePlayingData()
	{
		appleTexture = new sf::Texture();
		rockTexture = new sf::Texture();
		font = new sf::Font();
		eatAppleSoundBuffer = new sf::SoundBuffer();
		gameOverSoundBuffer = new sf::SoundBuffer();
		bonusSoundBuffer = new sf::SoundBuffer();

		gameObjects = new std::vector<std::shared_ptr<GameObject>>();
		blocks = new std::vector<std::shared_ptr<Block>>();
		bonusObjects = new std::vector<std::shared_ptr<BonusObject>>();

		scoreText = new sf::Text();
		inputHintText = new sf::Text();
		background = new sf::RectangleShape();

		gameOverSound = new sf::Sound();
		bonusSound = new sf::Sound();

		factories = new std::unordered_map<BlockType, std::unique_ptr<BlockFactory>>();
		levelLoder = new LevelLoader();

		bonuses = new std::map<BonusType, Bonus>();
	}

	GameStatePlayingData::~GameStatePlayingData()
	{
		gameObjects->clear();
		blocks->clear();
		bonusObjects->clear();
		factories->clear();

		delete appleTexture;
		delete rockTexture;
		delete font;
		delete eatAppleSoundBuffer;
		delete gameOverSoundBuffer;
		delete bonusSoundBuffer;
		delete gameObjects;
		delete blocks;
		delete bonusObjects;
		delete scoreText;
		delete inputHintText;
		delete background;
		delete gameOverSound;
		delete bonusSound;
		delete factories;
		delete levelLoder;
		delete bonuses;
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		window.draw(*background);

		static auto drawFunc = [&window](auto block)
			{
				block->Draw(window);
			};

		std::for_each(gameObjects->begin(), gameObjects->end(), drawFunc);
		std::for_each(blocks->begin(), blocks->end(), drawFunc);

		scoreText->setOrigin(GetTextOrigin(*scoreText, { 0.f, 0.f }));
		scoreText->setPosition(10.f, 10.f);
		window.draw(*scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText->setPosition(viewSize.x - 10.f, 10.f);
		window.draw(*inputHintText);
	}

	void GameStatePlayingData::GetStateData(Memento& memento)
	{
		blocks->clear();
		currentLevel = *memento.currentLevel;
		CreateBlocks();
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PauseGame();
			}
		}
	}

	void GameStatePlayingData::Init()
	{
		assert(font->loadFromFile(SETTINGS.FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer->loadFromFile(SETTINGS.SOUNDS_PATH + "Death.wav"));

		factories->emplace(BlockType::Simple, std::make_unique<SimpleBlockFactory>());
		factories->emplace(BlockType::ThreeHit, std::make_unique<ThreeHitBlockFactory>());
		factories->emplace(BlockType::Unbreackable, std::make_unique<UnbreackableBlockFactory>());

		background->setSize(sf::Vector2f((float)SETTINGS.SCREEN_WIDTH, (float)SETTINGS.SCREEN_HEIGHT));
		background->setPosition(0.f, 0.f);
		background->setFillColor(sf::Color(0, 0, 0));

		scoreText->setFont(*font);
		scoreText->setCharacterSize(24);
		scoreText->setFillColor(sf::Color::Yellow);

		SetTextData(*inputHintText, "Use arrow keys to move, ESC to pause", *font, 24, sf::Color::White);
		inputHintText->setOrigin(GetTextOrigin(*inputHintText, { 1.f, 0.f }));

		auto platform = std::make_shared<Platform>(sf::Vector2f({ SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - SETTINGS.PLATFORM_HEIGHT / 2.f }));
		gameObjects->emplace_back(platform);

		auto ball = std::make_shared<Ball>(sf::Vector2f({ SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - SETTINGS.PLATFORM_HEIGHT - SETTINGS.BALL_SIZE / 2.f }));
		ball->AddObserver(weak_from_this());
		gameObjects->emplace_back(ball);

		gameOverSound->setBuffer(*gameOverSoundBuffer);
		bonusSound->setBuffer(*bonusSoundBuffer);
		bonuses->emplace(BonusType::BiggerPlatform, Bonus(
			[wplatform = std::weak_ptr<Platform>(platform), &sound = bonusSound]()
			{
				auto platform = wplatform.lock();
				if (platform)
				{
					sound->play();
					platform->ChangeWidth(2);
				}
			},
			[wplatform = std::weak_ptr<Platform>(platform)]()
			{
				auto platform = wplatform.lock();
				if (platform)
				{
					platform->ChangeWidth(0.5);
				}
			},
			SETTINGS.BONUS_DURATION)
		);

		bonuses->emplace(BonusType::SlowBall, Bonus(
			[wball = std::weak_ptr<Ball>(ball), &sound = bonusSound]()
			{
				auto ball = wball.lock();
				if (ball)
				{
					sound->play();
					ball->ChangeSpeed(0.5);
				}
			},
			[wball = std::weak_ptr<Ball>(ball)]()
			{
				auto ball = wball.lock();
				if (ball)
				{
					ball->ChangeSpeed(1);
				}
			},
			SETTINGS.BONUS_DURATION)
		);

		bonuses->emplace(BonusType::FastPlatform, Bonus(
			[wplatform = std::weak_ptr<Platform>(platform), &sound = bonusSound]()
			{
				auto platform = wplatform.lock();
				if (platform)
				{
					sound->play();
					platform->ChangeSpeed(SETTINGS.PLATFORM_SPEED_INCREASED);
				}
			},
			[wplatform = std::weak_ptr<Platform>(platform)]()
			{
				auto platform = wplatform.lock();
				if (platform)
				{
					platform->ChangeSpeed(SETTINGS.PLATFORM_SPEED);
				}
			},
			SETTINGS.BONUS_DURATION)
		);
	}

	void GameStatePlayingData::LoadNextLevel()
	{
		if (currentLevel >= levelLoder->GetLevelCount() - 1)
		{
			Game& game = Application::Instance().GetGame();

			game.WinGame();
		}
		else
		{
			std::shared_ptr <Platform> platform = std::dynamic_pointer_cast<Platform>(gameObjects->at(0));
			std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects->at(1));
			platform->Restart();
			ball->Restart();

			blocks->clear();
			++currentLevel;
			CreateBlocks();
		}
	}

	void GameStatePlayingData::Notify(std::shared_ptr<IObservable> observable)
	{
		if (auto block = std::dynamic_pointer_cast<Block>(observable); block)
		{
			--breackableBlocksCount;
			Game& game = Application::Instance().GetGame();
			if (breackableBlocksCount == 0)
			{
				game.LoadNextLevel();
			}
			else
			{
				int percent = random<int>(0, 100);

				if (SETTINGS.BONUS_PROPABILITY_PERCENT >= percent)
				{
					BonusType bonusType = (BonusType)(random<int>(0, (int)BonusType::Count - 1));

					auto bonusObject = std::make_shared<BonusObject>(bonusType, block->GetPosition());
					bonusObject->AddObserver(weak_from_this());

					gameObjects->emplace_back(bonusObject);
					bonusObjects->push_back(bonusObject);
				}

				int playerRecord = game.GetRecordByPlayerId(SETTINGS.PLAYER_NAME);
				game.UpdateRecord(SETTINGS.PLAYER_NAME, playerRecord + block->GetReward());
			}
		}
		else if (auto ball = std::dynamic_pointer_cast<Ball>(observable); ball)
		{
			if (ball->GetPosition().y > gameObjects->front()->GetRect().top)
			{
				gameOverSound->play();
				Application::Instance().GetGame().LooseGame();
			}
		}
		else if (auto bonusObject = std::dynamic_pointer_cast<BonusObject>(observable); bonusObject)
		{
			bonuses->at(bonusObject->GetBonus()).Activate();

			auto bonusObj = std::find(bonusObjects->begin(), bonusObjects->end(), bonusObject);
			bonusObjects->erase(bonusObj);

			auto object = std::find(gameObjects->begin(), gameObjects->end(), bonusObject);
			gameObjects->erase(object);
		}
	}

	void GameStatePlayingData::SetStateData(Memento& memento)
	{
		*memento.currentLevel = currentLevel;
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		static auto updateFunctor = [timeDelta](auto obj) { obj->Update(timeDelta); };

		std::for_each(gameObjects->begin(), gameObjects->end(), updateFunctor);
		std::for_each(blocks->begin(), blocks->end(), updateFunctor);
		std::for_each(bonuses->begin(), bonuses->end(), [timeDelta](auto& bonusPair)
			{
				bonusPair.second.Update(timeDelta);
			});

		std::shared_ptr<Platform> platform = std::dynamic_pointer_cast<Platform>(gameObjects->at(0));
		std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects->at(1));

		bool isCollision = platform->CheckCollision(ball);
		for (std::shared_ptr<BonusObject> bonusObject : *bonusObjects)
		{
			if (bonusObject)
			{
				bonusObject->CheckCollision(platform);
			}
		}

		bool needInverseDirX = false;
		bool needInverseDirY = false;
		bool hasBrokeOneBlock = false;

		auto remove_if_lambda = [ball, &hasBrokeOneBlock, &needInverseDirX, &needInverseDirY, this](auto block)
			{
				if ((!hasBrokeOneBlock) && block->CheckCollision(ball))
				{
					hasBrokeOneBlock = true;
					const auto ballPos = ball->GetPosition();
					const auto blockRect = block->GetRect();

					GetBallInverse(ballPos, blockRect, needInverseDirX, needInverseDirY);
				}
				return block->IsBroken();
			};

		blocks->erase(std::remove_if(blocks->begin(), blocks->end(), remove_if_lambda), blocks->end());

		if (needInverseDirX)
		{
			ball->InvertDirectionX();
		}
		if (needInverseDirY)
		{
			ball->InvertDirectionY();
		}
	}

	void GameStatePlayingData::CreateBlocks()
	{
		for (const auto& pair : *factories)
		{
			pair.second->ClearCounter();
		}
		auto self = weak_from_this();

		Level level = levelLoder->GetLevel(currentLevel);

		for (auto pairPosBlockTYpe : level.m_blocks)
		{
			auto blockType = pairPosBlockTYpe.second;
			sf::Vector2i pos = pairPosBlockTYpe.first;

			sf::Vector2f position
			{
				(float)(SETTINGS.BLOCK_SHIFT + SETTINGS.BLOCK_WIDTH / 2.f + pos.x * (SETTINGS.BLOCK_WIDTH + SETTINGS.BLOCK_SHIFT))
				, (float)pos.y * SETTINGS.BLOCK_HEIGHT
			};

			blocks->emplace_back(factories->at(blockType)->CreateBlock(position));
			blocks->back()->AddObserver(self);
		}

		for (const auto& pair : *factories)
		{
			breackableBlocksCount += pair.second->GetcreatedBreackableBlocksCount();
		}
	}

	void GameStatePlayingData::GetBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, bool& needInverseDirX, bool& needInverseDirY)
	{
		if (ballPos.y > blockRect.top + blockRect.height)
		{
			needInverseDirY = true;
		}
		if (ballPos.x < blockRect.left)
		{
			needInverseDirX = true;
		}
		if (ballPos.x > blockRect.left + blockRect.width)
		{
			needInverseDirX = true;
		}
	}
}