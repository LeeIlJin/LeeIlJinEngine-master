#pragma once
#include "Memory\Source\Interface\IAllocator.h"

//	* Use Basic C's allocator
class CAllocator : public IAllocator
{
public:
	CAllocator();
	~CAllocator();

	//	* CAllocator Allocate (Just malloc ptr)
	void* _alloc(const unsigned int& size) override;
	
	template<typename T> T* _alloc()
	{
		return reinterpret_cast<T*>(_alloc(sizeof(T)));
	}

	//	* CAllocator Free (Just free ptr)
	bool _free(void * ptr) override;

private:
	CAllocator(const CAllocator& other) {}

};