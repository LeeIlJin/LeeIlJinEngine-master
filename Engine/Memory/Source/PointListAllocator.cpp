#include "PointListAllocator.h"

//     * malloc
//     * free
#include <stdlib.h>

//     * max
#include <algorithm>

//     * assert
#include <assert.h>

//	* memset
#include <string.h>

//	* CalculatePadding
#include "MemoryFunction.h"


const unsigned int PointListAllocator::_HeaderSize = sizeof(PointListAllocator::AllocationHeader);
const unsigned int PointListAllocator::_PointSize = sizeof(PointListAllocator::PointNode);


unsigned int PointListAllocator::PointList::get_space(void*& pointer, const unsigned int & use_size)
{
	unsigned int size = use_size + _HeaderSize;
	if (size < _PointSize)
		size += MemoryFunction::CalculatePadding(size, _PointSize);

	for (PointNode* point = head; point != nullptr; point = point->Next)
	{
		if (point->FrontSize < size)
			continue;

		//	There is free space after allocation.
		if (point->FrontSize - size >= _PointSize)	// Add New Node
		{
			PointNode* newNode = (PointNode*)((unsigned int)point + size);
			newNode->set_sibling_null();

			newNode->FrontSize = point->FrontSize - size;
			newNode->BackSize = point->BackSize + size;

			point->bind_prev_new_next(newNode);

			if(point->Previous == nullptr)
			{
				head = newNode;
			}
		}
		else
		{
			if (point->Next != nullptr)
			{
				//	* point is head
				if (point->Previous == nullptr)
				{
					head = point->Next;
					head->Previous = nullptr;
					head->BackSize += point->BackSize + point->FrontSize;
				}
				else
				{
					point->Next->Previous = point->Previous;
					point->Previous->Next = point->Next;
					point->Next->BackSize += point->BackSize + point->FrontSize;
				}
			}
			else
			{
				//	The Last Point
				PointNode* newNode = (PointNode*)((unsigned int)point + point->FrontSize);
				newNode->set_sibling_null();

				newNode->FrontSize = 0;
				newNode->BackSize = point->BackSize + point->FrontSize;

				//	* There was only one point.
				if (point->Previous == nullptr)
					head = newNode;
				else
				{
					newNode->Previous = point->Previous;
					point->Previous->Next = newNode;
				}
			}

			size = point->FrontSize;
		}

		((AllocationHeader*)point)->Size = size;
		pointer = (void*)((unsigned int)point + _HeaderSize);

		return size;

	}	// for : point

	return 0;
}

unsigned int PointListAllocator::PointList::set_space(unsigned int address)
{
	address = address - _HeaderSize;

	unsigned int size = ((AllocationHeader*)address)->Size;

	for (PointNode* point = head; point != nullptr; point = point->Next)
	{
		const unsigned int pointAddress = (unsigned int)point;
		const unsigned int backAddress = pointAddress - point->BackSize;

		if (address < backAddress || address > pointAddress)
			continue;

		memset((void*)address, 0, size);
		//

		//	* The address is at the leftmost position in the Back Space.
		if (address == backAddress)
		{
			//	* point is head
			if (point->Previous == nullptr)
			{
				PointNode* newNode = (PointNode*)address;
				newNode->set_init();

				newNode->Next = point;
				point->Previous = newNode;
				head = newNode;
			}

			if (size >= point->BackSize)
			{
				point->bind_prev_next();

				point->Previous->FrontSize += point->BackSize + point->FrontSize;
			}
			else
			{
				point->BackSize -= size;
				point->Previous->FrontSize += size;
			}
		}
		//	* The address is at the rightmost position in the Back Space.
		else if (address + size == pointAddress)
		{
			PointNode* newNode = (PointNode*)(address);
			if (point->Previous == nullptr)
				head = newNode;

			newNode->BackSize = point->BackSize - size;
			newNode->FrontSize = point->FrontSize + size;

			point->bind_prev_new_next(newNode);

		}
		//	* The address is in the middle.
		else
		{
			PointNode* newNode = (PointNode*)(address);

			newNode->BackSize = address - backAddress;
			newNode->FrontSize = size;
			point->BackSize = pointAddress - (address + size);

			newNode->set_sibling_null();

			newNode->Next = point;

			if (point->Previous != nullptr)
			{
				newNode->Previous = point->Previous;
				point->Previous->Next = newNode;
			}
			else
			{
				head = newNode;
			}

			point->Previous = newNode;
		}

		return size;
	}	// for : point

	return 0;
}




///////////////////////////////////////////////////////////////////////////////

PointListAllocator::PointListAllocator() :buffer(nullptr), buffer_size(0), used_size(0) { }
PointListAllocator::~PointListAllocator() { if (buffer != nullptr) this->buffer_clear(); }

///////////////////////////////////////////////////////////////////////////////

void * PointListAllocator::_alloc(const unsigned int & size)
{
	unsigned int size_;
	void* ptr = nullptr;
	size_ = pointList.get_space(ptr, size);

	assert(size_ != 0 && " * Buffer Overflow * ");

	used_size += size_;

	return ptr;
}

bool PointListAllocator::_free(void * ptr)
{
	unsigned int address = (unsigned int)ptr;
	unsigned int buffer_start = (unsigned int)buffer;

	if (address < buffer_start || address > buffer_start + buffer_size)
		return false;

	unsigned int size = pointList.set_space(address);
	used_size -= size;

	return (size != 0);
}

void PointListAllocator::buffer_set(const unsigned int & bufferSize, const int & initData)
{
	if (buffer != nullptr)
		free(buffer);

	buffer = malloc(bufferSize + _PointSize);
	memset(buffer, initData, bufferSize + _PointSize);

	buffer_size = bufferSize;
	used_size = 0;

	pointList.head = (PointNode*)buffer;
	pointList.head->set_init();
	pointList.head->FrontSize = bufferSize;
}

void PointListAllocator::buffer_clear()
{
	if (buffer != nullptr)
		free(buffer);
	buffer = nullptr;

	buffer_size = 0;
	used_size = 0;

	pointList.head = nullptr;
}
