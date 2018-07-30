#pragma once

#include "UIImage.h"
#include "IUIObject.h"
#include "ItemManager.h"

class Item;
class Inventory;
class ItemBox : public IDisplayObject
{
private:
	Inventory *				m_pInven;
	ItemManager*			m_pIM;

public:
	int						m_iVecIndex;

private:
	SYNTHESIZE(vector<Item*>, m_vecItemBoxIcon, VecItemBoxIcon);
	vector<Item*>::iterator m_iterItemBoxIcon;

public:
	ItemBox();
	~ItemBox();

	//IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

public:
	void AddItemToItemBox(ITEM_LIST IL);
	void RemoveItemFromItemBox_Item();
	void RemoveItemFromItemBox();
	void ItemBoxIconUpdate();
	void ItemBoxIconRender();

	void AddressLink(ItemManager* pIM, Inventory * pInven) {m_pIM = pIM; m_pInven = pInven;	}

};

