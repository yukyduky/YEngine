#include "Locator.h"

IGameTime* Locator::m_sGT = nullptr;
IConfigHandler* Locator::m_sCH = nullptr;
IEventHandler* Locator::m_sEH = nullptr;
MemoryManager* Locator::m_sPermMem = nullptr;
MemoryManager* Locator::m_sStateMem = nullptr;
MemoryManager* Locator::m_sFrameMem = nullptr;

void Locator::provide(IGameTime* gameTime)
{
	m_sGT = gameTime;
}

void Locator::provide(IConfigHandler* configHandler)
{
	m_sCH = configHandler;
}

void Locator::provide(IEventHandler* eventHandler)
{
	m_sEH = eventHandler;
}

void Locator::provide(MemoryManager* mm, MEMORYTYPE type)
{
	switch (type)
	{
	case MEMORYTYPE::PERM:
		m_sPermMem = mm;
		break;
	case MEMORYTYPE::STATE:
		m_sStateMem = mm;
		break;
	case MEMORYTYPE::FRAME:
		m_sFrameMem = mm;
		break;
	}
}

IGameTime* Locator::getGameTime()
{
	return m_sGT;
}

IConfigHandler* Locator::getConfigHandler()
{
	return m_sCH;
}

IEventHandler* Locator::getEventHandler()
{
	return m_sEH;
}

MemoryManager* Locator::getMemoryManager(MEMORYTYPE type)
{
	MemoryManager* mem = nullptr;
	switch (type)
	{
	case MEMORYTYPE::PERM:
		mem = m_sPermMem;
		break;
	case MEMORYTYPE::STATE:
		mem = m_sStateMem;
		break;
	case MEMORYTYPE::FRAME:
		mem = m_sFrameMem;
		break;
	}
	return mem;
}
