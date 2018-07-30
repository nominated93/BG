#pragma once
#include "BaseObject.h"

class AStarNode;
class Heap;

class AStar :
	public BaseObject
{
private:
	vector<AStarNode*>	m_vecNode;
	list<AStarNode*>	m_pOpenNodeList;
	Heap*				m_pOpenNodeHeap;
	LPD3DXMESH			m_pSphere;
	vector<D3DXVECTOR3>	m_vecObstacle;

public:
	AStar();
	virtual ~AStar();

	void Init();
	void Render();
	void InitNodes(IMap* pMap);
	const vector<AStarNode*>& GetNodes() { return m_vecNode; }
	void SetObstacle(const vector<D3DXVECTOR3> &vecObstacle) {m_vecObstacle = vecObstacle;}

	void FindPath(D3DXVECTOR3 startPos, D3DXVECTOR3 destPos, OUT vector<int>& vecIndex);

private:
	void RestNodes();
	int FindClosestNode(const D3DXVECTOR3 &pos);
	float GetManHattanDistance(int from, int to);
	int GetMinFNodeIndex();
	void Extend(int targetIdx, int destIdx);

public:
	void MakeDirectPath(const D3DXVECTOR3 &startPos, const D3DXVECTOR3 &destPos, OUT vector<int>& vecIndex);
private:
	void CalcEraseCount(const D3DXVECTOR3 &pos, const vector<int>& vecIndex, bool bByStartPos, OUT int &numEraseNode);

};

