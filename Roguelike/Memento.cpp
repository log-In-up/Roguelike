#include "Memento.h"

namespace Roguelike
{
	Memento::Memento(int state) : mementoState(state)
	{
		currentLevel = new int(0);
	}

	Memento::~Memento()
	{
		delete currentLevel;
	}
}