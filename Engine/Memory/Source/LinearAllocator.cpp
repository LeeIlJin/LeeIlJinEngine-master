#include "LinearAllocator.h"

//     * malloc
//     * free
#include <stdlib.h>

//     * assert
#include <assert.h>

//	* memset
#include <string.h>

LinearAllocator::LinearAllocator() noexcept
	:buffer(nullptr), offset(0), size(0)
{
}

LinearAllocator::~LinearAllocator() noexcept
{
	if (buffer != nullptr)
		buffer_reset();
}

void * LinearAllocator::_alloc(unsigned int size) noexcept
{
	if (buffer == nullptr)
		return nullptr;

	if (((int)this->size - (int)offset) < (int)size)
		return nullptr;

	void * result = (void *)((unsigned int)buffer + offset);
	this->offset += size;

	return result;
}

void LinearAllocator::buffer_set(unsigned int size)
{
	buffer_reset();

	buffer = malloc(size);
	memset(buffer, 0, size);
}

void LinearAllocator::buffer_reset()
{
	if (buffer != nullptr)
		free(buffer);

	size = 0;
	offset = 0;
	buffer = nullptr;
}
