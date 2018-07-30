#pragma once

#include "UIButton.h"
#include "UIImage.h"
#include "IUIObject.h"
#include "ItemManager.h"

class Cursor;
class Equipment;
class Item;
class ItemBox;
class Inventory : public IDisplayObject, public IUIButtonDelegate
{
private:
	UIImage *		m_pInvenUI;
	UIImage *		m_pInvenUI2;
	LPD3DXSPRITE	m_pSprite;
	IUIObject*		m_pRootUI;
	Equipment*		m_pEquipment;
	Cursor*			m_pCursor;
	ItemBox*		m_pItemBox;
	ItemManager*	m_pIM;

private:
	SYNTHESIZE(bool, m_isGun, IsGun);
	SYNTHESIZE(bool, m_isBackpack, IsBackpack);
	SYNTHESIZE(bool, m_isHead, IsHead);
	SYNTHESIZE(bool, m_isArmor, IsArmor);

private:
	vector<Item*> m_vecInvenItemIcon;
	vector<Item*>::iterator m_iterInvenItemIcon;

public:
	bool m_isInvenUI;

public:
	Inventory();
	~Inventory();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void OnClick(UIButton * pSender) override;

public:
	void AddItemToInven(ITEM_LIST IL);
	void RemoveItemFromInven();
	void ItemIconImageUpdate();
	void ItemIconImageRender();

	void AddressLink(ItemManager* pIM) { m_pIM = pIM; }

	void Drag();

public:
	vector<Item*> GetVecInvenItemIcon() { return m_vecInvenItemIcon; }
	ItemBox* GetPItemBox() { return m_pItemBox; }
	Equipment* GetPEquipment() { return m_pEquipment; }

	void SetIsEquipFromPlayer();
};

