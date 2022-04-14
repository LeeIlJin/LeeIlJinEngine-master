#pragma once

class LinearAllocator
{
public:
	LinearAllocator() noexcept;
	~LinearAllocator() noexcept;

	inline unsigned int used_size()
	{
		return offset;
	}

	void * _alloc(unsigned int size) noexcept;

	void buffer_set(unsigned int size);
	void buffer_reset();

private:
	void * buffer;
	unsigned int size;
	unsigned int offset;


};