#include "Locator.h"

IGameTime* Locator::ms_GT = nullptr;
IConfigHandler* Locator::ms_CH = nullptr;
IEventHandler* Locator::ms_EH = nullptr;
MemoryManager* Locator::ms_PermMem = nullptr;
MemoryManager* Locator::ms_StateMem = nullptr;
MemoryManager* Locator::ms_FrameMem = nullptr;
ID3D* Locator::ms_D3D = nullptr;

void Locator::provide(IGameTime* gameTime)
{
	ms_GT = gameTime;
}

void Locator::provide(IConfigHandler* configHandler)
{
	ms_CH = configHandler;
}

void Locator::provide(IEventHandler* eventHandler)
{
	ms_EH = eventHandler;
}

void Locator::provide(MemoryManager* mm, MEMORYTYPE type)
{
	switch (type)
	{
	case MEMORYTYPE::PERM:
		ms_PermMem = mm;
		break;
	case MEMORYTYPE::STATE:
		ms_StateMem = mm;
		break;
	case MEMORYTYPE::FRAME:
		ms_FrameMem = mm;
		break;
	}
}

void Locator::provide(ID3D* d3d)
{
	ms_D3D = d3d;
}

IGameTime* Locator::getGameTime()
{
	return ms_GT;
}

IConfigHandler* Locator::getConfigHandler()
{
	return ms_CH;
}

IEventHandler* Locator::getEventHandler()
{
	return ms_EH;
}

MemoryManager* Locator::getMemoryManager(MEMORYTYPE type)
{
	MemoryManager* mem = nullptr;
	switch (type)
	{
	case MEMORYTYPE::PERM:
		mem = ms_PermMem;
		break;
	case MEMORYTYPE::STATE:
		mem = ms_StateMem;
		break;
	case MEMORYTYPE::FRAME:
		mem = ms_FrameMem;
		break;
	}
	return mem;
}

ID3D* Locator::getD3D()
{
	return ms_D3D;
}
