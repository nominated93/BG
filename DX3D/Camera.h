#pragma once

#define g_pCamera Camera::GetInstance()

class Camera
{
	SINGLETON(Camera)
public:
	D3DXVECTOR3		m_eye;
	D3DXVECTOR3		m_lookAt;
	D3DXVECTOR3		m_up;
	D3DXMATRIXA16	m_matProj;
	float			m_basePosY;
	float			m_distance;
	bool			m_isAngleMove;
	POINT			m_ptPrevMouse;
	D3DXVECTOR3*	m_pTarget;
	D3DXVECTOR3		m_matRot;
	float			m_rotX;
	float			m_rotY;
	D3DXMATRIXA16	m_matView;
	D3DXVECTOR3		m_forward;

	bool			m_isLobby;
	float			m_fDir;

public:
	void Init();
	void Update();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetTarget(D3DXVECTOR3* pTarget) { m_pTarget = pTarget; }
	bool GetIsAngleMove() { return m_isAngleMove; }
	void SetIsAngleMove(bool isAngleMove) {	m_isAngleMove = isAngleMove; }

	void SetLookAt(D3DXVECTOR3 lookAt) { m_lookAt = lookAt; }
	void SetDistance(float distance) { m_distance = distance; }
	void SetBasePosY(float posY) { m_basePosY = posY; }
};

