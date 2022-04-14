#pragma once
#include "Memory\Source\Interface\IAllocator.h"

//	* Use Basic C's allocator
class PoolAllocator : public IAllocator
{
private:
	struct Node {	// 4 Bytes
		Node() :next(nullptr) {}
		Node* next;				// 4 Bytes
	};
	static const int NodeSize = sizeof(Node);

	struct StackLinkedList
	{
	private:
		Node* _head;

	public:
		StackLinkedList() :_head(nullptr) {}

		inline void push(Node * newNode)
		{
			newNode->next = _head;
			_head = newNode;
		}
		inline Node* pop()
		{
			Node * top = _head;
			_head = _head->next;
			return top;
		}

		inline Node* head()
		{
			return _head;
		}

		inline void head_nullptr()
		{
			_head = nullptr;
		}
	};


public:
	PoolAllocator();
	~PoolAllocator();

	//	* PoolAllocator Allocate
	//	! size < Size must be less than or equal to chunkSize. >
	void* _alloc(const unsigned int& size) override;

	template<typename T> T* _alloc()
	{
		return reinterpret_cast<T*>(_alloc(sizeof(T)));
	}

	//	* PoolAllocator Free
	bool _free(void * ptr) override;


	//	* PoolAllocator Buffer Set
	//	! chunkCount < Pool Chunk Count >
	//	! chunkSize < Pool Chunk Size >
	//	! initData < Buffer Init Data Value >
	//	Recommend [ chunkSize must be greater than or equal to 8 Bytes. ]
	//	* buffer size = cunckCount * cunckSize
	void buffer_set(const unsigned int& chunkCount, const unsigned int& chunkSize = 8, const int& initData = 0);

	//	* PoolAllocator Buffer Clear
	void buffer_clear();


	inline unsigned int get_buffer_size() { return buffer_size; }
	inline unsigned int get_used_size() { return used_size; }
	inline unsigned int get_used_count() { return used_count; }
	inline unsigned int get_chunk_size() { return chunk_size; }
	inline unsigned int get_chunk_count() { return chunk_count; }


private:
	StackLinkedList stackList;

	void * buffer;

	unsigned int buffer_size;
	unsigned int used_size;
	unsigned int used_count;
	unsigned int chunk_count;
	unsigned int chunk_size;

private:
	PoolAllocator(const PoolAllocator& other) {}

};