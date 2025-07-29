#include "Block.h"
#include "BlockFactory.h"

namespace Roguelike
{
	int BlockFactory::GetcreatedBreackableBlocksCount()
	{
		return createdBreackableBlocksCount;
	}

	void BlockFactory::ClearCounter()
	{
		createdBreackableBlocksCount = 0;
	}
}