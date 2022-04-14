#include "StackAllocator.h"

//     * malloc
//     * free
#include <stdlib.h>

//     * max
#include <algorithm>

//     * assert
#include <assert.h>

//	* memset
#include <string.h>

//	* CalculatePaddingWithHeader
#include "MemoryFunction.h"


StackAllocator::StackAllocator() :buffer(nullptr), last_header(nullptr), offset(0), buffer_size(0), used_size(0) { }
StackAllocator::~StackAllocator() { }

///////////////////////////////////////////////////////////////////////////////

void* StackAllocator::_alloc(const unsigned int & size, const unsigned int & alignment)
{
	assert(alignment >= 1 && "alignment can't be 0");
	assert(alignment <= 128 && "alignment can't greater than 128 bytes");

	//     * Check that alignment size is a pwr of 2.
	assert((alignment & (alignment - 1)) == 0 && "alignment must be pwr of 2");

	assert(size <= 65535 && "size can't greater than 65,535 bytes");

	//
	//     ! currentAddress <Last Allocated Address + Last Allocated Size>
	const unsigned int currentAddress = (unsigned)buffer + offset;

	//     Get Padding Size With Header Size
	unsigned int padding = MemoryFunction::CalculatePaddingWithHeader(currentAddress, alignment, _HeaderSize);

	if (offset + padding + size > buffer_size)
	{
		return nullptr;
	}//    over than buffer size

	 //     Add Padding(Header Space + Empty Space) To Offset
	offset += padding;

	//     * Get Next Address
	const unsigned int nextAddress = currentAddress;

	//     * Get Header Address
	const unsigned int headerAddress = nextAddress + size + (padding - _HeaderSize);

	//     * Memory : (Last Allocated Address) + {Last Allocated Space Size} ...
	//     + {Empty Space Size} ...
	//     -> (Header Address) + {Header Space Size} ...
	//     -> (Current Allocating Address) + {Current Allocating Space Size}
	AllocationHeader * headerPtr = (AllocationHeader*)headerAddress;

	last_header = headerPtr;

	//     * Header Have Empty Space Size
	headerPtr->padding = (unsigned short)padding;
	//     * Header Have Pointer Space Size
	headerPtr->size = (unsigned short)size;


	//     Add Current Allocating Space Size To Offset
	offset += size;
	used_size = offset;

	memset((void*)nextAddress, 0, size);

	return (void*)nextAddress;
}

bool StackAllocator::_free()
{
	if (last_header == nullptr)
		return false;

	offset -= (last_header->padding + last_header->size);

	if (offset != 0)
		last_header = (AllocationHeader *)((unsigned int)buffer + offset - _HeaderSize);
	else
		last_header = nullptr;

	used_size = offset;
	return true;
}

void StackAllocator::buffer_set(const unsigned int & bufferSize, const int& initData)
{
	if (buffer != nullptr)
		free(buffer);

	buffer = malloc(bufferSize);
	memset(buffer, initData, bufferSize);

	buffer_size = bufferSize;
	used_size = 0;
	offset = 0;
	last_header = nullptr;
}

void StackAllocator::buffer_clear()
{
	if (buffer != nullptr)
		free(buffer);
	buffer = nullptr;

	buffer_size = 0;
	used_size = 0;
	offset = 0;
	last_header = nullptr;
}
