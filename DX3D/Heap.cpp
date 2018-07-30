#include "stdafx.h"
#include "Heap.h"
#include "AStarNode.h"


Heap::Heap()
{
}


Heap::~Heap()
{
}

void Heap::Insert(AStarNode * pNode)
{
	//마지막에 새 노드 추가 후, 부모와 비교해가며 작으면 스왑

	//if(m_vecNode == )
	m_vecNode.push_back(pNode);
	UpHeap(m_vecNode.size() - 1);
}

AStarNode * Heap::ExtractMin()
{
	//루트를 추출
	//제일 마지막 노드를 루트 자리로 올린 후 자식보다 큰 값이면 스왑

	//m_vecNode.begin = m_vecNode.pop_back();
	if (m_vecNode.empty()) 
		return NULL;
	
	AStarNode* minFNode = m_vecNode.front();

	Swap(0, m_vecNode.size() - 1);
	m_vecNode.pop_back();
	DownHeap(0);

	return minFNode;
}

void Heap::Clear()
{
	m_vecNode.clear();
}

void Heap::UpHeap(int targetIdx)
{
	if (targetIdx == 0) return; //루트라면 더이상 진행 X

	int parentIdx = (targetIdx - 1) / 2;

	if (m_vecNode[parentIdx]->m_f > m_vecNode[targetIdx]->m_f)
	{
		Swap(targetIdx, parentIdx);
		UpHeap(parentIdx);
	}
}

void Heap::DownHeap(int targetIdx)
{
	int LChildIdx = targetIdx * 2 + 1;

	if (LChildIdx >= m_vecNode.size()) return;

	int minChildIdx = LChildIdx;
	int RChildeIdx = LChildIdx + 1;

	//두 개의 자식 중 더 작은 값 선택
	if (RChildeIdx < m_vecNode.size())
	{
		if (m_vecNode[RChildeIdx]->m_f < m_vecNode[LChildIdx]->m_f)
			minChildIdx = RChildeIdx;
	}

	//target의 값이 더 크면 해당 child와 swap
	if (m_vecNode[targetIdx]->m_f > m_vecNode[minChildIdx]->m_f)
	{
		Swap(targetIdx, minChildIdx);
		DownHeap(minChildIdx);
	}
}

void Heap::Swap(int idx1, int idx2)
{
	AStarNode* pTemp = m_vecNode[idx2];
	m_vecNode[idx2] = m_vecNode[idx1];
	m_vecNode[idx1] = pTemp;
}