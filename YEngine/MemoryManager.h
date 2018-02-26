#pragma once
#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <vector>
#include <cassert>

class MemoryManager
{
private:
	enum class MEMORY { FREE, USED };

	struct MemoryBlock
	{
		char* memHandle;
		size_t nrOfBlocks;
		MEMORY status;

		MemoryBlock() : memHandle(), nrOfBlocks(0), status(MEMORY::FREE) {}
	};

	char* m_MemHandle;
	size_t m_TotalMem;
	size_t m_MemInUse;
	size_t m_BlockSize;
	std::vector<MemoryBlock> m_Blocks;

	const size_t blockify(const size_t& size);
	bool findFreeMemoryBlock(const size_t& nrOfBlocks, size_t& blockNr);
public:
	MemoryManager(const size_t blockSize, const size_t nrOfBlocks);
	virtual ~MemoryManager() {}
	//***********************************************************
	// Method:    requestMemory
	// FullName:  MemoryManager::requestMemory
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: T1 * & dataPtr
	// Parameter: T2 * data
	// Parameter: const size_t size
	// Description: Copies the data into the dynamic memory and returns a ptr to that memory
	//***********************************************************
	template<typename T1, typename T2>
	void requestMemory(T1*&  dataPtr, T2* data, const size_t size);
	//***********************************************************
	// Method:    releaseMemory
	// FullName:  MemoryManager::releaseMemory
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: void * data
	// Description: Finds the corresponding memory to the pointer and sets it to be overwritten
	//***********************************************************
	void releaseMemory(void* data);
	//***********************************************************
	// Method:    resizeMemory
	// FullName:  MemoryManager::resizeMemory
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: const size_t blockSize
	// Parameter: const size_t nrOfBlocks
	// Description: Deletes the memory and creates a new block of the specified size
	//***********************************************************
	void resizeMemory(const size_t blockSize, const size_t nrOfBlocks);
	//***********************************************************
	// Method:    resetMemory
	// FullName:  MemoryManager::resetMemory
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: Sets all memory to be overwritten
	//***********************************************************
	void resetMemory();
	//***********************************************************
	// Method:    cleanup
	// FullName:  MemoryManager::cleanup
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: Deletes the memory completely
	//***********************************************************
	void cleanup();
};

template<typename T1, typename T2>
inline void MemoryManager::requestMemory(T1*& dataPtr, T2* data, const size_t size)
{
	dataPtr = nullptr;
	size_t blockedSize = this->blockify(size);
	size_t nrOfBlocks = blockedSize / m_BlockSize;
	size_t blockNr = -1;

	if (size <= m_TotalMem - m_MemInUse && this->findFreeMemoryBlock(nrOfBlocks, blockNr)) 
	{
		void* ptr = m_MemHandle + blockNr * m_BlockSize;
		memcpy(ptr, data, size);
		dataPtr = static_cast<T1*>(ptr);

		MemoryBlock* selectedBlock = &m_Blocks[blockNr];
		m_MemInUse += blockedSize;

		if (selectedBlock->nrOfBlocks != nrOfBlocks) 
		{
			m_Blocks[blockNr + nrOfBlocks].memHandle = m_MemHandle + (blockNr + nrOfBlocks) * m_BlockSize;
			m_Blocks[blockNr + nrOfBlocks].nrOfBlocks = selectedBlock->nrOfBlocks - nrOfBlocks;
		}
		selectedBlock->memHandle = m_MemHandle + blockNr * m_BlockSize;
		selectedBlock->nrOfBlocks = nrOfBlocks;
		selectedBlock->status = MEMORY::USED;
	}
	else 
	{
		assert(dataPtr != nullptr && "MemoryManager ran out of memory - Allocate more memory");
	}
}

#endif // MEMORYMANAGER_H
