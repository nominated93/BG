#pragma once
#include "IDisplayObject.h"

class Monster;
class MonsterManager : public IDisplayObject
{
private:
	vector<Monster*> m_vecMonster;
	vector<Monster*>::iterator m_iterMonster;

public:
	MonsterManager();
	~MonsterManager();

	void Init();
	void Update();
	void Render();

	void MonsterSetup(char * fileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

public:
	vector<Monster*>* GetPVecItem() { return &m_vecMonster; }
};
