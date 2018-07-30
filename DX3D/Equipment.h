#pragma once

#include "UIButton.h"
#include "UIImage.h"
#include "IUIObject.h"

class Item;
class Inventory;

class Equipment : public IDisplayObject
{
private:
	UIImage *		m_pEquipmentIcon;
	Inventory*		m_pIeven;
	LPD3DXSPRITE	m_pSprite;

private:
	SYNTHESIZE(bool, m_isGun, IsGun);
	SYNTHESIZE(bool, m_isBackpack, IsBackpack);
	SYNTHESIZE(bool, m_isHead, IsHead);
	SYNTHESIZE(bool, m_isArmor, IsArmor);

public:
	Equipment();
	~Equipment();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	vector<Item*> m_vecEquipmentItemIcon;

private:
	bool m_isEquipmentUI;

public:
	void AddItemToEquipment(ITEM_LIST IL);
	void RemoveItemFromEquipment();
	void EquipmentItemIconUpdate();
	void EquipmentItemIconRender();
	void SetTrueItemIcon(ITEM_LIST IL);
	void SetFalseItemIcon(ITEM_LIST IL);

public:
	vector<Item*> GetVecEquipmentItemIcon() { return m_vecEquipmentItemIcon; }
	void AddressLink(Inventory* pinven) { m_pIeven = pinven; }
};

