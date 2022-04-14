#pragma once

#include <vector>

struct IPriorityNode
{
	friend class PriorityQueue;

protected:
	virtual float& Priority() = 0;
	virtual unsigned int& InsertionIndex() = 0;
	virtual unsigned int& QueueIndex() = 0;
};

class PriorityQueue
{
public:
	PriorityQueue() noexcept;
	~PriorityQueue() noexcept;


	void Enqueue(IPriorityNode* node, float priority);
	template <typename RETURN_TYPE> RETURN_TYPE* Dequeue()
	{
		IPriorityNode* node = nodes[0];
		Remove(node);
		return static_cast<RETURN_TYPE*>(node);
	}
	template <typename RETURN_TYPE> RETURN_TYPE* First() const
	{
		return static_cast<RETURN_TYPE*>(nodes[0]);
	}

	unsigned int NodeCount() const;
	void Clear();
	bool Contains(IPriorityNode* node) const;

private:
	void NodeUpdate(unsigned int update_start);
	bool HigherPriority(IPriorityNode* higher, IPriorityNode* lower);
	void CascadeUp(IPriorityNode* node);

	void Remove(IPriorityNode* node);
	void Swap(IPriorityNode* node1, IPriorityNode* node2);

private:
	std::vector<IPriorityNode*> nodes;
	unsigned int nodeEverEnqueuedCount;

	int finalIndex;
};