#include "Block.h"
#include "BlockFactory.h"

namespace Arkanoid
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