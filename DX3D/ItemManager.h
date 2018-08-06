#pragma once
#include "IDisplayObject.h"

class Item;
class ItemManager : public IDisplayObject
{
private:
	list<Item*> m_listItem;
	list<Item*>::iterator m_iterItem;

public:
	ItemManager();
	~ItemManager();

	void Init();
	void Update();
	void Render();

	void ItemSetup(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ITEM_LIST IL,ITEM_INTO II);
public:
	list<Item*>* GetPListItem() { return &m_listItem; }
};

