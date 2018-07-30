#pragma once
#include "IDisplayObject.h"
//씬에다가 그냥 하면 지저분해 지니까, 3차원에 그리는 용도의 클래스를 따로만듬.
class Picking :
	public IDisplayObject
{
private:
	RECT rc;
	LPD3DXMESH m_pSphere;
	vector<BoundingSphere*> m_vecBoundary;

public:
	Picking();
	~Picking();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

