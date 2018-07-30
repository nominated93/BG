#pragma once
#include "IDisplayObject.h"
#include "Particle.h"
#include "EnemyParticle.h"

class Player;
class SkinnedMesh;
class BulletManager;
class Mesh;
class OBB;
class IMap;

enum E_Pattern
{
	Pattern_IDLE,
	Pattern_MOVE_LEFT,
	Pattern_MOVE_RIGHT,
	Pattern_ATTACK,
	Pattern_RELOAD,
	Pattern_Dying,
	Pattern_End,
	Pattern_Move
};

class Enemy : public IDisplayObject
{
private:
	SkinnedMesh *				m_pSkinnedMesh;
	Player*						m_pPlayer;
	Mesh*						m_pGun;
	D3DXMATRIXA16 				m_matWorld;
	BulletManager*				m_pBulletsManager;
	E_Pattern					m_ePattern;
	LPD3DXANIMATIONCONTROLLER	m_pAniController;
	LPD3DXANIMATIONCONTROLLER	m_pAniController2;
	int							m_nMaxHp;
	int							m_nCurrentHp;
	int							m_nPatternNum;
	IMap*						m_pMap;

	Particle*					particle;

	D3DXVECTOR3					m_vMoveStartPos;
	D3DXVECTOR3					m_vDirForMoving;

	SYNTHESIZE(OBB*, m_pOBB, Obb);

	SYNTHESIZE(int, m_nAniIndex, AniIndex);
	LPD3DXANIMATIONSET			m_pAniSet;
	bool						m_isBlend;
	float						m_fBlendTime;
	float						m_fPassedBlendTime;
	D3DXTRACK_DESC				m_stTrackDesc;
	SYNTHESIZE(bool, m_IsAlive, IsAlive);
	SYNTHESIZE(bool, m_isMove, IsMove);
	float						m_fAttackPatternCount;
	float						m_fReloadPatternCount;
	float						m_fEndPatternCount;

	int							m_nAmmoRemain;



private:
	void SetWorldMat();
	void SetDirByGetPlayerPos();
	void BulletFire();
	void AttackPattern();
	void ReloadPattern();
	void MoveLeftPattern();
	void MoveRightPattern();
	void Move();

public:
	void Init(Player* player, std::string keyName, BulletManager* bulletsManager, IMap* map);
	void Update();
	void Render();
	void reMake(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int patternNum);
	void SetAniByIndex();
	void SkinnedMeshUpdate();

	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);
	void BulletHit(int damage);
	float GetLength();

	Enemy();
	~Enemy();

	// Inherited via IDisplayObject
	virtual void Init() override;
};