#include "MemoryManager.h"
#include <string.h>
#include <cassert>


const size_t& MemoryManager::blockify(const size_t& size)
{
	size_t blockedSize = size + this->blockSize - (size % this->blockSize);
	if (blockedSize - this->blockSize == size) {
		blockedSize -= this->blockSize;
	}
	return blockedSize;
}

bool MemoryManager::findFreeMemoryBlock(const size_t& nrOfBlocks, size_t& blockNr)
{
	bool blockFound = false;

	size_t i = 0;
	while (!blockFound && i < this->blocks.size()) {
		if (nrOfBlocks <= this->blocks[i].nrOfBlocks && this->blocks[i].status == MEMORY::FREE) {
			blockFound = true;
			blockNr = i;
		}
		else if (this->blocks[i].status == MEMORY::FREE) {
			i += this->blocks[i].nrOfBlocks;

			if (i < this->blocks.size()) {
				i += this->blocks[i].nrOfBlocks;
			}
		}
		else {
			i += this->blocks[i].nrOfBlocks;
		}
	}

	return blockFound;
}

MemoryManager::MemoryManager(const size_t blockSize, const size_t nrOfBlocks) : memHandle(), totalMem(0), memInUse(0), blockSize(0)
{
	this->resizeMemory(blockSize, nrOfBlocks);
}

void MemoryManager::releaseMemory(void* data)
{
	bool blockFound = false;
	size_t i = 0;
	MemoryBlock* prevBlock = &this->blocks[i];
	MemoryBlock* currBlock = &this->blocks[i];
	while (!blockFound && i < this->blocks.size()) {
		if (data == currBlock->memHandle) {
			blockFound = true;

			if (prevBlock->status == MEMORY::FREE && prevBlock->memHandle != currBlock->memHandle) {
				prevBlock->nrOfBlocks += currBlock->nrOfBlocks;
				currBlock->nrOfBlocks = 0;
			}
			else if (this->blocks[i + currBlock->nrOfBlocks].status == MEMORY::FREE) {
				size_t nextNrOfBlocks = i + currBlock->nrOfBlocks;
				currBlock->nrOfBlocks += this->blocks[nextNrOfBlocks].nrOfBlocks;
				this->blocks[nextNrOfBlocks].nrOfBlocks = 0;
			}

			currBlock->status = MEMORY::FREE;
		}
		else {
			prevBlock = &this->blocks[i];
			i += this->blocks[i].nrOfBlocks;
			if (i < this->blocks.size()) {
				currBlock = &this->blocks[i];
			}
		}
	}
}

void MemoryManager::resizeMemory(const size_t blockSize, const size_t nrOfBlocks)
{
	this->cleanup();
	if (nrOfBlocks != 0) {
		this->blockSize = blockSize;
		size_t blockedSize = nrOfBlocks * blockSize;
		this->memHandle = new char[blockedSize];
		this->totalMem = blockedSize;
		this->memInUse = 0;
		this->blocks.resize(blockedSize / blockSize);
		this->blocks.front().memHandle = this->memHandle;
		this->blocks.front().nrOfBlocks = blockedSize / blockSize;
	}
}

void MemoryManager::resetMemory()
{
	this->memInUse = 0;

	MemoryBlock* currBlock = &this->blocks[0];
	for (size_t i = 0; i < this->blocks.size(); i++) {
		i += currBlock->nrOfBlocks;
		currBlock->nrOfBlocks = 0;
		currBlock->status = MEMORY::FREE;
	}
}

void MemoryManager::cleanup()
{
	if (this->totalMem != 0) {
		delete[] this->memHandle;
	}
}
