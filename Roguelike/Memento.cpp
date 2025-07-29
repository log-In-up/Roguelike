#include "Memento.h"

namespace Arkanoid
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