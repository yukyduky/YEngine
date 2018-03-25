#include "MemoryManager.h"
#include <string.h>
#include <cassert>


const size_t MemoryManager::blockify(const size_t& size)
{
	size_t blockedSize = size + m_BlockSize - (size % m_BlockSize);
	if (blockedSize - m_BlockSize == size)
	{
		blockedSize -= m_BlockSize;
	}
	return blockedSize;
}

bool MemoryManager::findFreeMemoryBlock(const size_t& nrOfBlocks, size_t& blockNr)
{
	bool blockFound = false;

	size_t i = 0;
	while (!blockFound && i < m_Blocks.size())
	{
		if (nrOfBlocks <= m_Blocks[i].nrOfBlocks && m_Blocks[i].status == MEMORY::FREE)
		{
			blockFound = true;
			blockNr = i;
		}
		else if (m_Blocks[i].status == MEMORY::FREE)
		{
			i += m_Blocks[i].nrOfBlocks;

			if (i < m_Blocks.size())
			{
				i += m_Blocks[i].nrOfBlocks;
			}
		}
		else {
			i += m_Blocks[i].nrOfBlocks;
		}
	}

	return blockFound;
}

MemoryManager::MemoryManager(const size_t blockSize, const size_t nrOfBlocks) : m_MemHandleFront(), m_TotalMem(0), m_MemInUse(0), m_BlockSize(0)
{
	this->resizeMemory(blockSize, nrOfBlocks);
}

void MemoryManager::releaseMemory(void* data)
{
	bool blockFound = false;
	size_t i = 0;
	MemoryBlock* prevBlock = &m_Blocks[i];
	MemoryBlock* currBlock = &m_Blocks[i];
	while (!blockFound && i < m_Blocks.size())
	{
		if (data == currBlock->memHandle)
		{
			blockFound = true;

			if (prevBlock->status == MEMORY::FREE && prevBlock->memHandle != currBlock->memHandle)
			{
				prevBlock->nrOfBlocks += currBlock->nrOfBlocks;
				currBlock->nrOfBlocks = 0;
			}
			else if (m_Blocks[i + currBlock->nrOfBlocks].status == MEMORY::FREE)
			{
				size_t nextNrOfBlocks = i + currBlock->nrOfBlocks;
				currBlock->nrOfBlocks += m_Blocks[nextNrOfBlocks].nrOfBlocks;
				m_Blocks[nextNrOfBlocks].nrOfBlocks = 0;
			}

			currBlock->status = MEMORY::FREE;
		}
		else {
			prevBlock = &m_Blocks[i];
			i += m_Blocks[i].nrOfBlocks;
			if (i < m_Blocks.size())
			{
				currBlock = &m_Blocks[i];
			}
		}
	}
}

void MemoryManager::resizeMemory(const size_t blockSize, const size_t nrOfBlocks)
{
	this->cleanup();
	if (nrOfBlocks != 0)
	{
		m_BlockSize = blockSize;
		size_t blockedSize = nrOfBlocks * blockSize;
		m_MemHandleFront = new char[blockedSize];
		m_TotalMem = blockedSize;
		m_MemInUse = 0;
		m_Blocks.resize(blockedSize / blockSize);
		m_Blocks.front().memHandle = m_MemHandleFront;
		m_Blocks.front().nrOfBlocks = blockedSize / blockSize;
	}
}

void MemoryManager::resetMemory()
{
	m_MemInUse = 0;

	MemoryBlock* currBlock = &m_Blocks[0];
	for (size_t i = 0; i < m_Blocks.size(); i++)
	{
		i += currBlock->nrOfBlocks;
		currBlock->nrOfBlocks = 0;
		currBlock->status = MEMORY::FREE;
	}
}

void MemoryManager::defrag()
{
	size_t nrOfBlocks = m_Blocks.size();
	size_t blockSize = m_BlockSize;

	for (size_t i = 0; i < nrOfBlocks; i += m_Blocks[i].nrOfBlocks)
	{
		if (m_Blocks[i].status == MEMORY::FREE)
		{
			bool filled = false;
			size_t k = nrOfBlocks;

			while (!filled && k < nrOfBlocks)
			{
				if (m_Blocks[k].status == MEMORY::USED && m_Blocks[k].nrOfBlocks <= m_Blocks[i].nrOfBlocks)
				{
					filled = true;
					this->requestMemory(m_Blocks[i].memHandle, m_Blocks[k].memHandle, m_Blocks[k].nrOfBlocks * blockSize);
					this->releaseMemory(m_Blocks[k].memHandle);
				}

				k--;
			}

			if (!filled)
			{
				filled = true;
				k = i + m_Blocks[i].nrOfBlocks;
				if (k < nrOfBlocks)
				{
					this->requestMemory(m_Blocks[i].memHandle, m_Blocks[k].memHandle, m_Blocks[k].nrOfBlocks * blockSize);
					this->releaseMemory(m_Blocks[k].memHandle);
				}
			}
		}
	}
}

void MemoryManager::cleanup()
{
	if (m_TotalMem != 0)
	{
		delete[] m_MemHandleFront;
	}
}
