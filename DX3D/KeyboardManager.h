#pragma once

#define g_pKeyboardManager KeyboardManager::GetInstance()
#define KEYMAX 256

class KeyboardManager
{
	SINGLETON(KeyboardManager)
private:
	D3DXVECTOR3 * m_pTargetPos;
	D3DXVECTOR3 * m_pTargetRot;
	bool * m_pTargetIsJumping;
	KEYBOARD_STATE* m_pKeyState;

	std::bitset<KEYMAX> _keyUp;
	std::bitset<KEYMAX> _keyDown;

public:
	void Update();
	void UpdateMoving();
	void SetMovingTarget(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pRot, bool * pIsJumping);
	void SetMovingTarget(KEYBOARD_STATE* pKeyState){m_pKeyState = pKeyState;}

	HRESULT init(void);
	void release(void);

	bool isOnceKeyDown(int key);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	std::bitset<KEYMAX> getKeyUp() { return _keyUp; }
	std::bitset<KEYMAX> getKeyDown() { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
};

