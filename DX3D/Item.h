#pragma once

enum eMouseState
{
	NORMAL,
	MOUSEOVER,
	SELECTED,
	SELECTEDMOVE,
	COUNT
};

class SkinnedMesh;
class UIImage;
class IUIObject;
class Item : public IDisplayObject
{
private:
	SkinnedMesh * m_pSkinnedMesh;
	UIImage*		m_pIconImage;
	UIImage*		m_pIconBackGroundImage;
	LPD3DXSPRITE	m_pSprite;
	LPD3DXMESH		m_pMesh;

public:
	float			m_fFixRenderX, m_fFixRenderZ;
	int				m_iVecIndex;

private:
	SYNTHESIZE(ITEM_LIST, m_tItemName, ItemName);
	SYNTHESIZE(ITEM_INTO, m_tItemInto, ItemInto);
	BoundingSphere	m_tCollisionSphere;

private:
	eMouseState		m_eMouseState;

public:
	IUIObject * m_pRootIcon;
	vector<Item*>::iterator m_iterItem;

private:
	SYNTHESIZE(bool, m_isCollision, IsCollision);
	bool			m_isPick;

public:
	Item();
	~Item();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Setup(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ITEM_LIST IL, ITEM_INTO II);
	virtual void Update() override;
	virtual void Render() override;

public:
	void MouseDrag(bool isClick);
	void IconUpdate();
	void IconRender();
public:

	BoundingSphere GetCollisionSphere() { return m_tCollisionSphere; }
	UIImage* GetPIconImage() { return m_pIconImage; }
	UIImage* GetPBGIconImage() { return m_pIconBackGroundImage; }


};

