#include "PoolAllocator.h"

//	* malloc
//	* free
#include <stdlib.h>

//	* assert
#include <assert.h>

//	* memset
#include <string.h>


PoolAllocator::PoolAllocator() :buffer(nullptr), buffer_size(0), used_count(0), used_size(0), chunk_count(0), chunk_size(16) { }
PoolAllocator::~PoolAllocator() { if (buffer != nullptr) this->buffer_clear(); }

///////////////////////////////////////////////////////////////////////////////

void * PoolAllocator::_alloc(const unsigned int & size)
{
	assert(size <= chunk_size && "Size must be less than or equal to chunkSize.");

	Node * allocAddress = stackList.pop();

	if (allocAddress == nullptr)
		return nullptr;

	used_size += chunk_size;
	used_count++;

	memset(allocAddress, 0, size);
	return (void *)allocAddress;
}

bool PoolAllocator::_free(void * ptr)
{
	if ((unsigned int)ptr < (unsigned int)buffer || (unsigned int)ptr >(unsigned int)buffer + buffer_size)
		return false;

	used_size -= chunk_size;
	used_count--;

	stackList.push((Node *)ptr);

	return true;
}

void PoolAllocator::buffer_set(const unsigned int & chunkCount, const unsigned int & chunkSize, const int & initData)
{
	assert(chunkSize >= 4 && "ChunkSize must be greater than or equal to 4 Bytes.");
	assert(chunkCount > 0 && "ChunkCount must be greater than zero.");

	//     * Check that alignment size is a pwr of 2.
	assert((chunkSize & (chunkSize - 1)) == 0 && "chunkSize must be pwr of 2");

	if (buffer != nullptr)
	{
		free(buffer);
		buffer = nullptr;
	}

	stackList.head_nullptr();

	//	buffer
	buffer_size = chunkCount * chunkSize;
	used_count = 0;
	used_size = 0;

	//	chunk
	chunk_count = chunkCount;
	chunk_size = chunkSize;


	//	data set
	buffer = malloc(buffer_size);
	memset(buffer, initData, buffer_size);

	for (unsigned int i = 0; i < chunkCount; ++i)
	{
		Node* nodeAddress = (Node*)((unsigned int)buffer + i * chunkSize);
		stackList.push(nodeAddress);
	}
}


void PoolAllocator::buffer_clear()
{
	if (buffer != nullptr)
	{
		free(buffer);
		buffer = nullptr;
	}

	buffer_size = 0;
	used_size = 0;
	chunk_size = 16;

	stackList.head_nullptr();
}


///////////////////////////////////////////////////////////////////////////////

