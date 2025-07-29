#pragma once

namespace Arkanoid
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