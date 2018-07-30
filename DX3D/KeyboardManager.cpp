#include "stdafx.h"
#include "KeyboardManager.h"


KeyboardManager::KeyboardManager()
{
}


KeyboardManager::~KeyboardManager()
{
}

void KeyboardManager::Update()
{
	UpdateMoving();
}

void KeyboardManager::UpdateMoving()
{
	if (m_pKeyState == NULL)
		return;

	//눌렸냐 안 눌렸냐만 체크해주는 기능을 만들자.
	if (GetKeyState('A') & 0x08000)
	{
		//m_pTargetRot->y = -1;
		m_pKeyState->deltaPos.x = -1;
		//m_pTargetPos->x = -1;
	}
	else if (GetKeyState('D') & 0x08000)
	{
		//m_pTargetRot->y = 1;
		m_pKeyState->deltaPos.x = 1;
		//m_pTargetPos->x = 1;
	}
	else
	{
		m_pKeyState->deltaPos.x = 0;
	}

	if (GetKeyState('W') & 0x8000)
	{
		m_pKeyState->deltaPos.z = 1;
	}
	else if (GetKeyState('S') & 0x8000)
	{
		m_pKeyState->deltaPos.z = -1;
	}
	else
	{
		m_pKeyState->deltaPos.z = 0;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
		m_pKeyState->bJump = true;
	else
		m_pKeyState->bJump = false;

	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
		m_pKeyState->bSit = true;
	else
		m_pKeyState->bSit = false;

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		m_pKeyState->bWalk = true;
	else
		m_pKeyState->bWalk = false;


	if (GetAsyncKeyState(VK_LEFT) & 0x0001)
	{
		m_pTargetRot->y = (D3DX_PI/2) * 10;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
	{
		m_pTargetRot->y = -(D3DX_PI / 2) * 10;
	}

}
//키값을 적용 시키고 싶은 객체가 이동과 회전을 갖고 있을 테니까 그 객체에게 키보드 값을 주기 위해 넘겨주자.
void KeyboardManager::SetMovingTarget(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pRot, bool * pIsJumping)
{
	m_pTargetPos = pPos;
	m_pTargetRot = pRot;
	m_pTargetIsJumping = pIsJumping;
}

HRESULT KeyboardManager::init(void)
{
	//처음엔 아무것도 눌려져있지 않다
	for (int i = 0; i < KEYMAX; i++)
	{
		this->getKeyUp().set(i, false);
		this->getKeyUp().set(i, false);
	}


	return S_OK;
}

void KeyboardManager::release(void)
{

}

bool KeyboardManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);

	return false;

}

bool KeyboardManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) this->setKeyUp(key, true);
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}

	return false;
}

bool KeyboardManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool KeyboardManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}