#include "Caretaker.h"

namespace Arkanoid
{
	Caretaker::Caretaker(std::vector<GameState>& originator) : originatorStack(originator)
	{
		state = 0;

		historySaved = new std::vector<Memento*>();
	}

	Caretaker::~Caretaker()
	{
		for (auto memento : *historySaved)
		{
			if (memento)
			{
				delete memento;
			}
		}

		historySaved->clear();
		delete historySaved;
	}

	void Caretaker::Save()
	{
		Memento* memento = new Memento(++state);
		SetStackMementoData(*memento);

		historySaved->push_back(memento);
	}

	void Caretaker::Undo()
	{
		if (historySaved->empty())
		{
			return;
		}

		Memento* memento = historySaved->back();
		GetStackMementoData(*memento);

		historySaved->pop_back();
		historySaved->push_back(memento);
	}

	void Caretaker::SetStackMementoData(Memento& memento)
	{
		for (auto it = originatorStack.begin(); it != originatorStack.end(); ++it)
		{
			it->SetGameStateData(memento);
		}
	}

	void Caretaker::GetStackMementoData(Memento& memento)
	{
		for (auto it = originatorStack.begin(); it != originatorStack.end(); ++it)
		{
			it->GetGameStateData(memento);
		}
	}
}