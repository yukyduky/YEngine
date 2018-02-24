#include "Locator.h"

IGameTime* Locator::sGT = nullptr;
IConfigHandler* Locator::sCH = nullptr;
IEventHandler* Locator::sEH = nullptr;
MemoryManager* Locator::sPermMem = nullptr;
MemoryManager* Locator::sStateMem = nullptr;
MemoryManager* Locator::sFrameMem = nullptr;
ID3D* Locator::sD3D = nullptr;

void Locator::provide(IGameTime* gameTime)
{
	sGT = gameTime;
}

void Locator::provide(IConfigHandler* configHandler)
{
	sCH = configHandler;
}

void Locator::provide(IEventHandler* eventHandler)
{
	sEH = eventHandler;
}

void Locator::provide(MemoryManager* mm, MEMORYTYPE type)
{
	switch (type)
	{
	case MEMORYTYPE::PERM:
		sPermMem = mm;
		break;
	case MEMORYTYPE::STATE:
		sStateMem = mm;
		break;
	case MEMORYTYPE::FRAME:
		sFrameMem = mm;
		break;
	}
}

void Locator::provide(ID3D* d3d)
{
	sD3D = d3d;
}

IGameTime* Locator::getGameTime()
{
	return sGT;
}

IConfigHandler* Locator::getConfigHandler()
{
	return sCH;
}

IEventHandler* Locator::getEventHandler()
{
	return sEH;
}

MemoryManager* Locator::getMemoryManager(MEMORYTYPE type)
{
	MemoryManager* mem = nullptr;
	switch (type)
	{
	case MEMORYTYPE::PERM:
		mem = sPermMem;
		break;
	case MEMORYTYPE::STATE:
		mem = sStateMem;
		break;
	case MEMORYTYPE::FRAME:
		mem = sFrameMem;
		break;
	}
	return mem;
}

ID3D* Locator::getD3D()
{
	return sD3D;
}
