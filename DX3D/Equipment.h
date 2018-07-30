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

public:
	vector<Item*> GetVecEquipmentItemIcon() { return m_vecEquipmentItemIcon; }
	void AddressLink(Inventory* pinven) { m_pIeven = pinven; }
};

