#pragma once
#include <vector>

#include "Memento.h"
#include "GameState.h"

namespace Arkanoid
{
	class Caretaker
	{
	private:
		std::vector<GameState>& originatorStack;
		std::vector<Memento*>* historySaved;

		int state = 0;
	public:
		Caretaker(std::vector<GameState>& originatorStack);
		~Caretaker();
		void Save();
		void Undo();
	private:
		void SetStackMementoData(Memento& memento);
		void GetStackMementoData(Memento& memento);
	};
}