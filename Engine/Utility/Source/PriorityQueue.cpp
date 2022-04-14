#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() noexcept
	:finalIndex(-1), nodeEverEnqueuedCount(0)
{
	//
}

PriorityQueue::~PriorityQueue() noexcept
{
	nodes.clear();
}

///////////////////////////////////////////////////////////////////////////////

void PriorityQueue::Enqueue(IPriorityNode * node, float priority)
{
	node->Priority() = priority;

	nodes.push_back(node);
	node->QueueIndex() = nodes.size() - 1;
	node->InsertionIndex() = nodeEverEnqueuedCount++;
	finalIndex++;

	CascadeUp(nodes[nodes.size() - 1]);
}

unsigned int PriorityQueue::NodeCount() const
{
	return nodes.size();
}

void PriorityQueue::Clear()
{
	nodes.clear();
	nodeEverEnqueuedCount = 0;
	finalIndex = -1;
}

bool PriorityQueue::Contains(IPriorityNode * node) const
{
	return nodes[node->QueueIndex()] == node;
}



///////////////////////////////////////////////////////////////////////////////

void PriorityQueue::NodeUpdate(unsigned int update_start)
{
	for (unsigned int i = update_start; i < nodes.size(); i++)
	{
		nodes[i]->QueueIndex() = i;
	}
}

bool PriorityQueue::HigherPriority(IPriorityNode * higher, IPriorityNode* lower)
{
	return higher->Priority() < lower->Priority() ||
		((fabsf(higher->Priority() - lower->Priority()) < FLT_EPSILON) &&
			higher->InsertionIndex() < lower->InsertionIndex());
}

void PriorityQueue::CascadeUp(IPriorityNode * node)
{
	int index = (int)node->QueueIndex();
	int parent = index - 1;

	while (parent >= 0 && parent != index)
	{
		index = (int)node->QueueIndex();

		IPriorityNode* parentNode = nodes[parent];
		if (HigherPriority(parentNode, node))
		{
			break;
		}

		Swap(node, parentNode);
		parent = index - 1;
	}
}

void PriorityQueue::Remove(IPriorityNode * node)
{
	if (finalIndex <= 0)
	{
		nodes.clear();
		finalIndex = -1;
		return;
	}

	unsigned int node_index = node->QueueIndex();

	bool wasFinalNode = false;
	if (node_index != finalIndex)
	{
		wasFinalNode = true;
	}

	nodes.erase(nodes.begin() + node_index);
	finalIndex--;

	if (wasFinalNode)
	{
		NodeUpdate(node_index);
	}
}

void PriorityQueue::Swap(IPriorityNode * node1, IPriorityNode * node2)
{
	nodes[node1->QueueIndex()] = node2;
	nodes[node2->QueueIndex()] = node1;
	unsigned int temp = node1->QueueIndex();
	node1->QueueIndex() = node2->QueueIndex();
	node2->QueueIndex() = temp;
}
