#pragma once
#include "Memory\Source\Interface\IAllocator.h"

class StackAllocator : public IAllocator
{
private:
	//     * Padding And Header Position (4 Bytes)
	struct AllocationHeader {
		unsigned short padding;
		unsigned short size;
	};
public:
	static const unsigned int _HeaderSize = sizeof(AllocationHeader);

public:
	StackAllocator();
	~StackAllocator();

	//     * Stack Allocator Allocate
	void* _alloc(const unsigned int & size, const unsigned int & alignment);

	template <typename T> T* _alloc(const unsigned int& alignment)
	{
		return reinterpret_cast<T*>(_alloc(sizeof(T), alignment));
	}

	//     * Stack Allocator Free
	//     * Free the last pointer.
	bool _free();


	void* _alloc(const unsigned int & size) override
	{
		return this->_alloc(size, 4);
	}
	bool _free(void* ptr) override
	{
		return _free();
	}

	//     * StackAllocator Buffer Set
	void buffer_set(const unsigned int & bufferSize, const int& initData = 0);

	static const unsigned int CalcBufferSize(const unsigned int& bufferSize, const unsigned int& headerCount)
	{
		return bufferSize + (_HeaderSize * headerCount);
	}

	//     * StackAllocator Buffer Clear
	void buffer_clear();

	inline unsigned int get_buffer_size() { return buffer_size; }
	inline unsigned int get_used_size() { return used_size; }

	inline unsigned short get_last_allocated_size() { return (last_header != nullptr) ? last_header->size : 0; }

private:
	void* buffer;        // Buffer = Buffer's Start Address
	unsigned int buffer_size;
	unsigned int used_size;
	unsigned int offset;  // Address Offset

	AllocationHeader* last_header;

private:
	StackAllocator(const StackAllocator& other) {}
	
};