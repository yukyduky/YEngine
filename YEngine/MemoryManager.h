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

	char* memHandle;
	size_t totalMem;
	size_t memInUse;
	size_t blockSize;
	std::vector<MemoryBlock> blocks;

	const size_t& blockify(const size_t& size);
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
	size_t nrOfBlocks = blockedSize / blockSize;
	size_t blockNr = -1;

	if (size <= this->totalMem - this->memInUse && this->findFreeMemoryBlock(nrOfBlocks, blockNr)) 
	{
		void* ptr = this->memHandle + blockNr * blockSize;
		memcpy(ptr, data, size);
		dataPtr = static_cast<T1*>(ptr);

		MemoryBlock* selectedBlock = &this->blocks[blockNr];
		this->memInUse += blockedSize;

		if (selectedBlock->nrOfBlocks != nrOfBlocks) 
		{
			this->blocks[blockNr + nrOfBlocks].memHandle = this->memHandle + (blockNr + nrOfBlocks) * blockSize;
			this->blocks[blockNr + nrOfBlocks].nrOfBlocks = selectedBlock->nrOfBlocks - nrOfBlocks;
		}
		selectedBlock->memHandle = this->memHandle + blockNr * blockSize;
		selectedBlock->nrOfBlocks = nrOfBlocks;
		selectedBlock->status = MEMORY::USED;
	}
	else {
		assert(dataPtr != nullptr && "MemoryManager ran out of memory - Allocate more memory");
	}
}

#endif // MEMORYMANAGER_H
