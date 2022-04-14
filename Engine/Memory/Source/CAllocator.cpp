#include "CAllocator.h"

//	* malloc
//	* free
#include <stdlib.h>

CAllocator::CAllocator() { }
CAllocator::~CAllocator() { }

///////////////////////////////////////////////////////////////////////////////

void* CAllocator::_alloc(const unsigned int& size)
{
	return malloc(size);
}

bool CAllocator::_free(void * ptr)
{
	free(ptr);
	return true;
}