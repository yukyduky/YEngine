/*#pragma once
#ifndef MEMORYMANAGERTEMPLATE_H
#define MEMORYMANAGERTEMPLATE_H

#include <vector>

class MemoryManager
{
private:
	enum class MEMORY { FREE, USED };

	struct MemoryBlock
	{
		char* memHandle;
		size_t nrOfBlocks;
		MEMORY status;

		MemoryBlock() : memHandle(nullptr), nrOfBlocks(0), status(MEMORY::FREE) {}
	};

	const size_t MEM_BLOCK_SIZE = 16;

	char* memHandle;
	size_t totalMem;
	size_t memInUse;
	std::vector<MemoryBlock> blocks;

	const size_t& blockify(const size_t& size);
	bool findFreeMemoryBlock(const size_t& nrOfBlocks, size_t& blockNr);
public:
	MemoryManager(const size_t nrOfBlocks);
	virtual ~MemoryManager() {}
	void* requestMemory(void* data, const size_t size);
	void releaseMemory(void* data) override;
	void resizeMemory(const size_t nrOfBlocks);
	void resetMemory();
	void cleanup();
};

#endif
*/