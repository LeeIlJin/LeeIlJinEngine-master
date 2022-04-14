#pragma once
//	Made By Lee Il Jin

#include "Memory\Source\Interface\IAllocator.h"

//	* Point List Allocator
class PointListAllocator : public IAllocator
{
private:
	//     * Size And Header Position (2 Bytes)
	struct AllocationHeader {
		unsigned short Size;
	};
	static const unsigned int _HeaderSize;

	struct PointNode	// 16 Bytes
	{
		PointNode() :Next(nullptr), Previous(nullptr), FrontSize(0), BackSize(0) {}

		void set_size_zero() { this->FrontSize = 0; this->BackSize = 0; }
		void set_sibling_null() { this->Next = nullptr; this->Previous = nullptr; }
		void set_init() { *this = PointNode(); }

		inline void bind_prev_next()
		{
			if(Next != nullptr)
				Next->Previous = Previous;
			if(Previous != nullptr)
				Previous->Next = Next;
		}

		inline void bind_prev_new_next(PointNode *& newNode)
		{
			newNode->set_sibling_null();
			if (Next != nullptr)
			{
				Next->Previous = newNode;
				newNode->Next = Next;
			}
			if (Previous != nullptr)
			{
				Previous->Next = newNode;
				newNode->Previous = Previous;
			}
		}

		PointNode* Next;		// 4Bytes
		PointNode* Previous;	// 4Bytes

		//	* Empty Space Size	: Point ->(Space)
		// 4Bytes
		unsigned int FrontSize;

		//	* Filled Space Size	: (Space)<- Point
		// 4Bytes
		unsigned int BackSize;

	};
	static const unsigned int _PointSize;

	struct PointList
	{
		PointList() :head(nullptr) {}

		unsigned int get_space(void*& pointer, const unsigned int& use_size);

		unsigned int set_space(unsigned int address);

		PointNode* head;
	};

public:
	PointListAllocator();
	~PointListAllocator();

	//     * Point List Allocator Allocate
	void* _alloc(const unsigned int & size) override;

	template <typename T> T* _alloc()
	{
		return reinterpret_cast<T*>(this->_alloc(sizeof(T)));
	}

	//     * Point List Allocator Free
	bool _free(void* ptr) override;

	//     * Point List Allocator Buffer Set
	void buffer_set(const unsigned int & bufferSize, const int& initData = 0);

	//     * Point List Allocator Buffer Clear
	void buffer_clear();

	inline unsigned int get_buffer_size() { return buffer_size; }
	inline unsigned int get_used_size() { return used_size; }


private:
	PointList pointList;

	void * buffer;

	unsigned int buffer_size;
	unsigned int used_size;

};
