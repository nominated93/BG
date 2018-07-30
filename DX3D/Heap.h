#pragma once

class AStarNode;

class Heap
{
public:
	vector<AStarNode*> m_vecNode;

	Heap();
	~Heap();

	void Insert(AStarNode* pNode);
	AStarNode* ExtractMin();
	void Clear();

private:
	void UpHeap(int targetIdx); //하나하나 올라가면서 부모보다 작으면 올려줌
	void DownHeap(int targetIdx);
	void Swap(int idx1, int idx2);
};

