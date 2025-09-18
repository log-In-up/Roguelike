#include "AIActor.h"

#include "AIAttackComponent.h"
#include "AIBlackboard.h"
#include "AIChaseTargetComponent.h"
#include "AIInputComponent.h"
#include "AIPerceptionComponent.h"
#include "AITargetSelector.h"
#include "Actor.h"
#include "PerceptionComponentDebugDraw.h"
#include "Settings.h"
#include "Vector.h"

namespace Roguelike
{
AIActor::AIActor(const Parameters &parameters, const GameEngine::Vector2Df &position)
    : Actor(parameters.baseActorParameters, position)
{
    auto input = gameObject->AddComponent<AIInputComponent>();
    auto enemyChase = gameObject->AddComponent<AIChaseTargetComponent>(parameters.chaseTargetParameters);

    gameObject->AddComponent<AIBlackboard>();

    auto perception = gameObject->AddComponent<AIPerceptionComponent>(parameters.perceptionParameters);
    input->AddObserver(perception);

    auto animationFind =
        parameters.baseActorParameters.animations.find(parameters.baseActorParameters.defaultAnimationName);
    if (animationFind != parameters.baseActorParameters.animations.end())
    {
        perception->SetVisionDirection(animationFind->second.isRightDirected ? GameEngine::Vector2Df(1.0F, 0.0F)
                                                                             : GameEngine::Vector2Df(-1.0F, 0.0F));
    }
    gameObject->AddComponent<PerceptionComponentDebugDraw>(static_cast<int>(Settings::RenderLayers::Debug));
    auto targetSelector = gameObject->AddComponent<AITargetSelector>();
    perception->AddObserver(targetSelector);

    gameObject->AddComponent<AIAttackComponent>(parameters.baseActorParameters.attackComponentParameters);
}
} // namespace Roguelike