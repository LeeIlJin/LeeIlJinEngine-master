#pragma once

class IAllocator
{
public:
	virtual ~IAllocator() {}

	virtual void* _alloc(const unsigned int& size) = 0;
	virtual bool _free(void* ptr) = 0;
};