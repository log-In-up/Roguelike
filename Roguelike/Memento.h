#pragma once

namespace Roguelike
{
	class Memento
	{
	public:
		int* currentLevel;
		int mementoState;
	public:
		Memento(int state);
		~Memento();
	};
}