#include "stdafx.h"
#include "Player.h"
#include "UIImage.h"
#include "UIText.h"
#include "SkinnedMesh.h"
#include "BulletManager.h"
#include "OBB.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Ray.h"
#include "HitUI.h"


Player::Player() :
	m_pSkinnedMesh(NULL),
	m_pBM(NULL),
	m_pCrossImg(NULL),
	m_pBulletCurrText(NULL),
	m_pBulletTotalText(NULL),
	m_pPB(NULL),
	m_pOBB(NULL),
	m_pHitUI(NULL),
	m_isZoom(false),
	m_bulletTotalCnt(100),
	m_isReload(false),
	m_eState(Melee_stand_idle),
	aniControlerTmp(NULL),
	m_pAniSet(NULL),
	m_pInven(NULL),
	m_pGun(NULL),
	m_pHead(NULL),
	m_pBackpack(NULL),
	m_pArmor(NULL),
	m_isAlive(true),
	m_isGun(false),
	m_isHead(false),
	m_isBackpack(false),
	m_isArmor(false),
	m_isBlend(false),
	m_fPassedBlendTime(0.0f),
	m_fEndPatternCount(0.0f)
{
}

Player::~Player()
{
	SAFE_RELEASE(m_pSkinnedMesh);
	SAFE_RELEASE(m_pGun);
	SAFE_RELEASE(m_pHead);
	SAFE_RELEASE(m_pBackpack);
	SAFE_RELEASE(m_pArmor);

	SAFE_DELETE(m_pOBB);
	SAFE_RELEASE(m_pBM);
	SAFE_RELEASE(m_pCrossImg);
	SAFE_RELEASE(m_pBulletCurrText);
	SAFE_RELEASE(m_pBulletTotalText);
	SAFE_RELEASE(m_pPB);
	SAFE_RELEASE(aniControlerTmp);
	SAFE_RELEASE(m_pAniSet);
	SAFE_RELEASE(m_pInven);
	SAFE_RELEASE(m_pHitUI);
}

void Player::Init(BulletManager* bm)
{
	m_pBM = bm;
}

void Player::Init()
{
	m_pos = D3DXVECTOR3(-207, -87, -47);
	m_bulletCurrCnt = m_bulletTotalCnt;

	g_pObjMgr->AddToTagList(TAG_PLAYER, this);
	g_pCamera->SetTarget(&m_pos);
	g_pKeyboardManager->SetMovingTarget(&m_keyState);

	//Player 애니메이션 셋팅
	m_pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh("PlayerAction");
	//aniControlerTmp = m_pSkinnedMesh->GetAnimationController();
	m_pSkinnedMesh->SetAnimationIndex(6);

	m_pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Character");
	walkAniIndex = 0;
	curAniIndex = baseAniIndex = Melee_stand_idle;
	m_pSkinnedMesh->SetAnimationIndex(curAniIndex);

	m_pGun = g_pMeshManager->GetStaticMesh("AK-47");
	m_pBackpack = g_pMeshManager->GetStaticMesh("Backpack");
	m_pHead = g_pMeshManager->GetStaticMesh("Head");
	m_pArmor = g_pMeshManager->GetStaticMesh("Armor");

	//crosshair
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXCreateSprite(g_pDevice, &m_pSprite);

	m_pCrossImg = new UIImage(m_pSprite);
	m_pCrossImg->SetTexture("resources/images/cross5.png");	
	m_pCrossImg->SetPosition(&D3DXVECTOR3(rc.right/2-10, rc.bottom/2, 0));
	m_pCrossImg->Update();

	m_pZoomin = new UIImage(m_pSprite);
	m_pZoomin->SetTexture("resources/images/zoom.png");
	m_pZoomin->SetPosition(&D3DXVECTOR3(rc.right / 2 - m_pZoomin->GetInfo().Width / 2 , rc.bottom / 2 - m_pZoomin->GetInfo().Height / 2, 0));
	m_pZoomin->Update();

	//인벤토리
	m_pInven = new Inventory(); m_pInven->AddressLink(m_pIM); m_pInven->Init();

	//피격
	m_pHitUI = new HitUI; m_pHitUI->Init();
	
	//충돌
	m_pOBB = new OBB;
	m_pOBB->Init(D3DXVECTOR3(m_pSkinnedMesh->GetMin().x, m_pSkinnedMesh->GetMin().y, m_pSkinnedMesh->GetMin().z)
		, D3DXVECTOR3(m_pSkinnedMesh->GetMax().x, m_pSkinnedMesh->GetMax().y, m_pSkinnedMesh->GetMax().z));

	m_bulletCntStr[0] = '\0';
	m_bulletTotalStr[0] = '\0';
	strcat_s(m_bulletCntStr, to_string(m_bulletCurrCnt).data());
	strcat_s(m_bulletTotalStr, "ㅣ ");
	strcat_s(m_bulletTotalStr, to_string(m_bulletTotalCnt).data());
	
	m_pBulletCurrText = new UIText(GetFont(FontType_NORMAL), NULL);
	m_pBulletCurrText->m_text = m_bulletCntStr;
	m_pBulletCurrText->m_drawTextFormat = DT_RIGHT | DT_NOCLIP;
	m_pBulletCurrText->m_size = D3DXVECTOR2(40, 100);
	m_pBulletCurrText->SetPosition(&D3DXVECTOR3(rc.right / 2 - 40, WINSIZEY - WINSIZEY / 5, 0));
	m_pBulletCurrText->Update();
	
	m_pBulletTotalText = new UIText(GetFont(FontType_BULLETTOTAL), NULL);
	m_pBulletTotalText->m_text = m_bulletTotalStr;
	m_pBulletTotalText->m_drawTextFormat = DT_LEFT | DT_NOCLIP;
	m_pBulletTotalText->m_size = D3DXVECTOR2(50, 100);
	m_pBulletTotalText->SetPosition(&D3DXVECTOR3(rc.right / 2, WINSIZEY - WINSIZEY / 5 + 10, 0));
	m_pBulletTotalText->Update();
	
	m_pAk47Img = new UIImage(m_pSprite);
	m_pAk47Img->SetTexture("resources/UI/ak-47_back.png");
	m_pAk47Img->SetPosition(&D3DXVECTOR3(rc.right / 2 - m_pAk47Img->GetInfo().Width / 2, WINSIZEY - WINSIZEY / 6.6, 0));
	m_pAk47Img->Update();

	//체력바
	m_fMaxHP = m_fCurrHP = 100.f;
	m_pPB = new ProgressBarManager; m_pPB->Init();
	m_pPB->SetPosition(WINSIZEX / 2 - m_pPB->GetPUIImg()->GetInfo().Width / 2, WINSIZEY - WINSIZEY / 15);
	m_pPB->SetGauge(m_fCurrHP, m_fMaxHP);

	//아이템충돌 구 생성
	m_tCollisionSphere_Item.center = m_pos;
	//m_tCollisionSphere_Item.center = D3DXVECTOR3(0,0,0);
	m_tCollisionSphere_Item.radius = 100;
	D3DXCreateSphere(g_pDevice, m_tCollisionSphere_Item.radius, 10, 10, &m_pMesh, NULL);
}


void Player::Update()
{
	IUnitObject::UpdateKeyboardState();
	m_rot.y = g_pCamera->m_rotY;
	IUnitObject::UpdatePosition();


	D3DXMatrixScaling(&matS, 0.04f, 0.04f, 0.04f);
	D3DXMatrixRotationY(&matRY, m_rot.y);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = matS  * matRY * matT;

	//m_isReload = false;

	m_isGun = m_pInven->GetPEquipment()->GetIsGun();
	m_isBackpack = m_pInven->GetPEquipment()->GetIsBackpack();
	m_isHead = m_pInven->GetPEquipment()->GetIsHead();
	m_isArmor = m_pInven->GetPEquipment()->GetIsArmor();


	if (m_isAlive)
	{
		//스피어충돌 좌표갱신
		m_tCollisionSphere_Item.center = m_pos;


		//인벤이 아닐때
		if (m_isGun && !(m_pInven->m_isInvenUI))
		{
			//총쏘기
			if (g_pKeyboardManager->isOnceKeyDown(VK_LBUTTON))
			{
				if (m_bulletCurrCnt > 0)
				{
					m_bulletCurrCnt--;
					UpdateBulletText();
				}
				RECT rc;
				GetClientRect(g_hWnd, &rc);

				float vpWidth = rc.right - rc.left;
				float vpHeight = rc.bottom - rc.top;

				Ray r = Ray::RayAtWorldSpace(vpWidth / 2, vpHeight / 2);

				g_pCamera->m_fDir = 200;

				//m_pBM->Fire(10, 0.1f, 100.0f, &(m_pos + D3DXVECTOR3(0.5f, 4.0f, 0.0f) + 2.2f * (g_pCamera->m_forward)), &(g_pCamera->m_forward));
				m_pBM->Fire(10, 0.1f, 100.0f, &(r.m_pos), &r.m_dir);

				if (g_pCamera->m_fDir <= 1000)
				{
					g_pCamera->m_fDir += 100;
				}
			}
			else
			{
				g_pCamera->m_fDir = 1000;
			}

			//재장전
			if (g_pKeyboardManager->isOnceKeyDown('R'))
			{
				m_isReload = true;
				ReloadAction();
			}
			else
			{
				m_isReload = false;
			}


			//줌
			if (m_isZoom == false)
			{
				if (g_pKeyboardManager->isOnceKeyDown(VK_RBUTTON))
				{
					m_isZoom = true;
					m_pZoomin->Update();
					g_pCamera->SetDistance(-30.0f);
				}
			}
			else
			{
				if (g_pKeyboardManager->isOnceKeyDown(VK_RBUTTON) || g_pKeyboardManager->isOnceKeyDown(VK_LBUTTON))
				{
					m_isZoom = false;
					m_pZoomin->Update();
					g_pCamera->SetDistance(5.0f);
				}
			}
		}


		//AnimationConversion();
		SetPlayerState();
		//PlayerMotion();
		m_pSkinnedMesh->Update();

		m_pOBB->Update(&m_matWorld);

		//인벤토리
		m_pInven->Update();

		//피격
		m_pHitUI->Update();
	}

	else
	{
		m_pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh("PlayerAction");
		aniControlerTmp = m_pSkinnedMesh->GetAnimationController();

		LPD3DXKEYFRAMEDANIMATIONSET aniset = NULL;
		D3DXTRACK_DESC td;

		aniControlerTmp->GetTrackAnimationSet(0, (LPD3DXANIMATIONSET*)&aniset);
		aniControlerTmp->GetTrackDesc(0, &td);

		if (td.Position > aniset->GetPeriod())
		{
			LPD3DXANIMATIONSET	pAnimSet = NULL;
			aniControlerTmp->GetAnimationSet(1, &pAnimSet);
			aniControlerTmp->SetTrackAnimationSet(0, pAnimSet);


			SAFE_RELEASE(pAnimSet);


			m_fEndPatternCount += g_pTimeManager->GetEllapsedTime();
			if (m_fEndPatternCount >= 60 * g_pTimeManager->GetEllapsedTime())
			{
				m_fEndPatternCount = 0.0f;
				m_pOBB->Init(D3DXVECTOR3(m_pSkinnedMesh->GetMin().x, m_pSkinnedMesh->GetMin().y, m_pSkinnedMesh->GetMin().z)
					, D3DXVECTOR3(m_pSkinnedMesh->GetMax().x, m_pSkinnedMesh->GetMax().y, m_pSkinnedMesh->GetMax().z));
			}
			aniControlerTmp = NULL;

			SAFE_RELEASE(aniset);
		}

		m_pSkinnedMesh->Update();

		m_pSkinnedMesh = NULL;
	}




	//체력바 디버그
	if (g_pKeyboardManager->isStayKeyDown('1'))
	{
		if (m_fCurrHP > 0)
		{
			m_fCurrHP -= 0.5f;
		}
	}
	if (g_pKeyboardManager->isStayKeyDown('2'))
	{
		if (m_fCurrHP <= 100)
		{
			m_fCurrHP += 0.5f;
		}
	}


	if (m_fCurrHP > 0)
	{
		m_isAlive = true;
	}
	else if (m_fCurrHP == 0)
	{
		m_isAlive = false;
	}

	m_pPB->SetGauge(m_fCurrHP, m_fMaxHP);
	m_pPB->Update();

	//위치
	Debug->AddText("pos : ");
	Debug->AddText(m_pos);
	Debug->EndLine();
}

void Player::Render()
{
	D3DXMATRIXA16 matT_tmp;

	if (m_isAlive)
	{
		if (m_isGun)
		{
			D3DXMatrixIdentity(&matR);
			D3DXMatrixRotationY(&matR, D3DX_PI);

			D3DXMatrixTranslation(&matT_tmp, 1, 10, 1);

			g_pSkinnedMeshManager->GetBoneMatrix("Character", "hand_r", matBone);
			matWorld = matBone * matR * matT_tmp * m_matWorld;
			g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
			m_pGun->Render();
		}
		if (m_isBackpack)
		{
			D3DXMatrixIdentity(&matR);
			D3DXMatrixRotationY(&matR, D3DX_PI /2);
			D3DXMatrixTranslation(&matT_tmp, m_pos.x + 10, m_pos.y+10, m_pos.z);
			g_pSkinnedMeshManager->GetBoneMatrix("Character", "breat_l", matBone);	
			matWorld = matBone * matR  * m_matWorld;

			g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
			m_pBackpack->Render();
		}
		if (m_isHead)
		{
			g_pSkinnedMeshManager->GetBoneMatrix("Character", "hair_f_01", matBone);
			matWorld = matBone * matR * m_matWorld;
			g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
			m_pHead->Render();
		}
		//if (m_isArmor)
		//{
		//	g_pSkinnedMeshManager->GetBoneMatrix("Character", "backpack_01", matBone);
		//	matWorld = matBone * matR * m_matWorld;
		//	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
		//	m_pBackpack->Render();
		//}

		if (m_isZoom)
		{
			m_pZoomin->Render();
		}
		else
		{
			m_pCrossImg->Render();
		}

		//인벤토리
		m_pInven->Render();

		//피격
		m_pHitUI->Render();
	}

	if (m_pSkinnedMesh)
	{
		m_pSkinnedMesh->Render(NULL, &m_matWorld);
		m_pOBB->Render_Debug(255);
	}


	//체력바
	m_pBulletCurrText->Render();
	m_pBulletTotalText->Render();
	m_pAk47Img->Render();
	m_pPB->Render();

	Debug->AddText("HP : ");
	Debug->AddText(m_fCurrHP);
	Debug->EndLine();
} 

void Player::SetAnimationIndexBlend(int nIndex)
{
	if (curAniIndex != nIndex)
	{
		m_pSkinnedMesh->SetAnimationIndexBlend(nIndex);
		curAniIndex = nIndex;
	}
}

void Player::AnimationConversion()
{
	m_pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Character");

	//m_moveSpeed = 0.15;

	// 애니메이션 셋팅
	if (m_keyState.bSit)	// 앉아있냐 아니냐
	{
		//m_currMoveSpeedRate = 0.5f; 

		if (m_isGun)
		{
			baseAniIndex = Rifle_crouch_idle;
		}
		else
		{
			baseAniIndex = Melee_crouch_idle;
		}

		//g_pCamera->SetLookAt(m_rot + D3DXVECTOR3(0, -10, 0));
	}
	else
	{
		if (m_isGun)
		{
			baseAniIndex = Rifle_stand_idle;
		}
		else
		{
			baseAniIndex = Melee_stand_idle;
		}

		//g_pCamera->SetLookAt(m_rot);
	}

	nextAniIndex = baseAniIndex;

	if (m_keyState.bWalk && !m_keyState.bSit && !m_isJumping)
	{
		m_currMoveSpeedRate = 0.6f;
		walkAniIndex = 9;
	}
	else
		walkAniIndex = 0;

	//if (m_keyState.deltaPos.x < 0)
	//	nextAniIndex = baseAniIndex - walkAniIndex - Left;
	//else if (m_keyState.deltaPos.x > 0)
	//	nextAniIndex = baseAniIndex - walkAniIndex - Right;

	if (m_keyState.deltaPos.z > 0)
		//nextAniIndex = baseAniIndex - walkAniIndex - Front;
		nextAniIndex = Melee_stand_run_front;
	else if (m_keyState.deltaPos.z < 0)
		//nextAniIndex = baseAniIndex - walkAniIndex - Back;
		nextAniIndex = Melee_stand_idle;

	m_eState = nextAniIndex;
	SetAnimationIndexBlend(nextAniIndex);
}

void Player::ReloadAction()
{
	//Jump(NULL);
	m_isJumping = false; //되는지 확인


	aniTime = g_pTimeManager->GetEllapsedTime();
	if (m_isJumping == false)
	{
		if (m_isReload == true)
		{
			m_pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh("PlayerAction");
			m_eState = Reload;

			m_bulletCurrCnt = m_bulletTotalCnt;
			UpdateBulletText();

			LPD3DXKEYFRAMEDANIMATIONSET aniset = NULL;
			D3DXTRACK_DESC td;

			aniControlerTmp = m_pSkinnedMesh->GetAnimationController();

			aniControlerTmp->GetTrackAnimationSet(0, (LPD3DXANIMATIONSET*)&aniset);

			aniControlerTmp->GetTrackDesc(0, &td);

			//aniControlerTmp->SetTrackAnimationSet(0, m_pAniSet);
			SetAnimationIndexBlend(19);


			if (td.Position > aniset->GetPeriod())
			{

				m_pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Character");

				aniControlerTmp->SetTrackPosition(0, 0);
			}
		}
	}

	m_isReload = false;
}

void Player::UpdateBulletText()
{
	m_bulletCntStr[0] = '\0';
	strcat_s(m_bulletCntStr, to_string(m_bulletCurrCnt).data());
	m_pBulletCurrText->m_text = m_bulletCntStr;
	m_pBulletCurrText->Update();
}

void Player::SetPlayerState()
{
	m_pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Character");

	if (m_isGun)
	{	// 애니메이션 셋팅
		if (m_keyState.bSit)	// 앉아있냐 아니냐
		{
			baseAniIndex = Rifle_crouch_idle;
		}
		else
		{
			baseAniIndex = Rifle_stand_idle;
		}

		nextAniIndex = baseAniIndex;

		if (m_keyState.bWalk && !m_keyState.bSit && !m_isJumping)
		{
			m_currMoveSpeedRate = 0.6f;
			//walkAniIndex = 9;
		}
		else
		{
			//walkAniIndex = 0;
		}

		if (m_keyState.deltaPos.x < 0)
			nextAniIndex = Rifle_stand_run_left;
		else if (m_keyState.deltaPos.x > 0)
			nextAniIndex = Rifle_stand_run_right;

		if (m_keyState.deltaPos.z > 0)
		{
			nextAniIndex = Rifle_stand_run_front;
		}
		else if (m_keyState.deltaPos.z < 0)
		{
			nextAniIndex = Rifle_stand_run_back;
		}

	}
	else
	{	
		// 애니메이션 셋팅
		if (m_keyState.bSit)	// 앉아있냐 아니냐
		{
			baseAniIndex = Melee_crouch_idle;
		}
		else
		{
			baseAniIndex = Melee_stand_idle;
		}

		nextAniIndex = baseAniIndex;

		if (m_keyState.bWalk && !m_keyState.bSit && !m_isJumping)
		{
			m_currMoveSpeedRate = 0.6f;
			//walkAniIndex = 9;
		}
		else
		{
			//walkAniIndex = 0;
		}

		if (m_keyState.deltaPos.x < 0)
			nextAniIndex = Melee_stand_run_left;
		else if (m_keyState.deltaPos.x > 0)
			nextAniIndex = Melee_stand_run_right;

		if (m_keyState.deltaPos.z > 0)
		{
			nextAniIndex = Melee_stand_run_front;
		}
		else if (m_keyState.deltaPos.z < 0)
		{
			nextAniIndex = Melee_stand_run_back;
		}

	}

	SetAnimationIndexBlend(nextAniIndex);
}

void Player::PlayerMotion()
{
	//if (m_pSkinnedMesh == g_pSkinnedMeshManager->GetSkinnedMesh("Character"))
	//{
	switch (m_eState)
	{
	case Melee_stand_idle:
		m_pSkinnedMesh->SetAnimationIndexBlend(83);//무기없이 서있기
		break;
	case Melee_stand_pickup:
		m_pSkinnedMesh->SetAnimationIndexBlend(82);//무기없이 템 줍기
		break;
	case Melee_stand_jump:
		m_pSkinnedMesh->SetAnimationIndexBlend(81);//무기없이 점프
		break;
	case Melee_stand_punch1:
		m_pSkinnedMesh->SetAnimationIndexBlend(80);//무기없이 주먹질1
		break;
	case Melee_stand_punch2:
		m_pSkinnedMesh->SetAnimationIndexBlend(79);//무기없이 주먹질2
		break;
	case Melee_stand_punch3:
		m_pSkinnedMesh->SetAnimationIndexBlend(78);//무기없이 주먹질3
		break;
	case Melee_stand_fastrun:
		m_pSkinnedMesh->SetAnimationIndexBlend(77);//무기없이 서서 빠른걸음(??)
		break;
	case Melee_stand_run_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(76);//무기없이 뛰어서 앞으로
		break;
	case Melee_stand_run_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(75);//무기없이 뛰어서 왼쪽앞으로
		break;
	case Melee_stand_run_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(74);//무기없이 뛰어서 왼쪽으로
		break;
	case Melee_stand_run_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(73);//무기없이 뛰어서 왼쪽뒤로
		break;
	case Melee_stand_run_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(72);//무기없이 뛰어서 뒤로
		break;
	case Melee_stand_run_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(71);//무기없이 뛰어서 우측뒤로
		break;
	case Melee_stand_run_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(70);//무기없이 뛰어서 우측으로
		break;
	case Melee_stand_run_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(69);//무기없이 뛰어서 우측앞으로
		break;
	case Melee_stand_walk_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(68);//무기없이 앞으로
		break;
	case Melee_stand_walk_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(67);//무기없이 왼쪽앞으로
		break;
	case Melee_stand_walk_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(66);//무기없이 왼쪽으로
		break;
	case Melee_stand_walk_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(65);//무기없이 왼쪽뒤로
		break;
	case Melee_stand_walk_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(64);//무기없이 뒤로
		break;
	case Melee_stand_walk_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(63);//무기없이 우측뒤로
		break;
	case Melee_stand_walk_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(62);//무기없이 우측으로
		break;
	case Melee_stand_walk_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(61);//무기없이 우측앞으로
		break;

		//60~39 무기 없이 앉아서 행동
	case Melee_crouch_idle:
		m_pSkinnedMesh->SetAnimationIndexBlend(60);//무기없이 앉아 있기
		break;
	case Melee_crouch_pickup:
		m_pSkinnedMesh->SetAnimationIndexBlend(59);//무기없이 앉아 템 줍기
		break;
	case Melee_crouch_punch1:
		m_pSkinnedMesh->SetAnimationIndexBlend(58);//무기없이 앉아 주먹질1
		break;
	case Melee_crouch_punch2:
		m_pSkinnedMesh->SetAnimationIndexBlend(57);//무기없이 앉아 주먹질2
		break;
	case Melee_crouch_punch3:
		m_pSkinnedMesh->SetAnimationIndexBlend(56);//무기없이 앉아 주먹질3
		break;
	case Melee_crouch_fastrun:
		m_pSkinnedMesh->SetAnimationIndexBlend(55);//무기없이 앉아 서서 빠른걸음(??)
		break;
	case Melee_crouch_run_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(54);//무기없이 앉아 뛰어서 앞으로
		break;
	case Melee_crouch_run_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(53);//무기없이 앉아 뛰어서 왼쪽앞으로
		break;
	case Melee_crouch_run_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(52);//무기없이 앉아 뛰어서 왼쪽으로
		break;
	case Melee_crouch_run_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(51);//무기없이 앉아 뛰어서 왼쪽뒤로
		break;
	case Melee_crouch_run_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(50);//무기없이 앉아 뛰어서 뒤로
		break;
	case Melee_crouch_run_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(49);//무기없이 앉아 뛰어서 우측뒤로
		break;
	case Melee_crouch_run_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(48);//무기없이 앉아 뛰어서 우측으로
		break;
	case Melee_crouch_run_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(47);//무기없이 앉아 뛰어서 우측앞으로
		break;
	case Melee_crouch_walk_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(46);//무기없이 앉아 앞으로
		break;
	case Melee_crouch_walk_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(45);//무기없이 앉아 왼쪽앞으로
		break;
	case Melee_crouch_walk_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(44);//무기없이 앉아 왼쪽으로
		break;
	case Melee_crouch_walk_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(43);//무기없이 앉아 왼쪽뒤로
		break;
	case Melee_crouch_walk_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(42);//무기없이 앉아 뒤로
		break;
	case Melee_crouch_walk_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(41);//무기없이 앉아 우측뒤로
		break;
	case Melee_crouch_walk_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(40);//무기없이 앉아 우측으로
		break;
	case Melee_crouch_walk_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(39);//무기없이 앉아 우측앞으로
		break;

		//38 ~ 19번 무기들고 행동.
	case Rifle_stand_idle:
		m_pSkinnedMesh->SetAnimationIndexBlend(38);//무기들고 서있기
		break;
	case Rifle_stand_pickup:
		m_pSkinnedMesh->SetAnimationIndexBlend(37);//무기들고 템 줍기
		break;
	case Rifle_stand_jump:
		m_pSkinnedMesh->SetAnimationIndexBlend(36);//무기들고 점프
		break;
	case Rifle_stand_fastrun:
		m_pSkinnedMesh->SetAnimationIndexBlend(35);//무기들고 서서 빠른걸음(??)
		break;
	case Rifle_stand_run_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(34);//무기들고 뛰어서 앞으로
		break;
	case Rifle_stand_run_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(33);//무기들고 뛰어서 왼쪽앞으로
		break;
	case Rifle_stand_run_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(32);//무기들고 뛰어서 왼쪽으로
		break;
	case Rifle_stand_run_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(31);//무기들고 뛰어서 왼쪽뒤로
		break;
	case Rifle_stand_run_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(30);//무기들고 뛰어서 뒤로
		break;
	case Rifle_stand_run_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(29);//무기들고 뛰어서 우측뒤로
		break;
	case Rifle_stand_run_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(28);//무기들고 뛰어서 우측으로
		break;
	case Rifle_stand_run_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(27);//무기들고 뛰어서 우측앞으로
		break;
	case Rifle_stand_walk_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(26);//무기들고 앞으로
		break;
	case Rifle_stand_walk_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(25);//무기들고 왼쪽앞으로
		break;
	case Rifle_stand_walk_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(24);//무기들고 왼쪽으로
		break;
	case Rifle_stand_walk_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(23);//무기들고 왼쪽뒤로
		break;
	case Rifle_stand_walk_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(22);//무기들고 뒤로
		break;
	case Rifle_stand_walk_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(21);//무기들고 우측뒤로
		break;
	case Rifle_stand_walk_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(20);//무기들고 우측으로
		break;
	case Rifle_stand_walk_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(19);//무기들고 우측앞으로
		break;

		//18 ~ 0 무기 들고 앉아서 행동
	case Rifle_crouch_idle:
		m_pSkinnedMesh->SetAnimationIndexBlend(18);//무기들고 앉아 있기
		break;
	case Rifle_crouch_pickup:
		m_pSkinnedMesh->SetAnimationIndexBlend(17);//무기들고 앉아 템 줍기
		break;
	case Rifle_crouch_fastrun:
		m_pSkinnedMesh->SetAnimationIndexBlend(16);//무기들고 앉아 서서 빠른걸음(??)
		break;
	case Rifle_crouch_run_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(15);//무기들고 앉아 뛰어서 앞으로
		break;
	case Rifle_crouch_run_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(14);//무기들고 앉아 뛰어서 왼쪽앞으로
		break;
	case Rifle_crouch_run_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(13);//무기들고 앉아 뛰어서 왼쪽으로
		break;
	case Rifle_crouch_run_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(12);//무기들고 앉아 뛰어서 왼쪽뒤로
		break;
	case Rifle_crouch_run_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(11);//무기들고 앉아 뛰어서 뒤로
		break;
	case Rifle_crouch_run_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(10);//무기들고 앉아 뛰어서 우측뒤로
		break;
	case Rifle_crouch_run_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(9);//무기들고 앉아 뛰어서 우측으로
		break;
	case Rifle_crouch_run_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(8);//무기들고 앉아 뛰어서 우측앞으로
		break;
	case Rifle_crouch_walk_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(7);//무기들고 앉아 앞으로
		break;
	case Rifle_crouch_walk_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(6);//무기들고 앉아 왼쪽앞으로
		break;
	case Rifle_crouch_walk_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(5);//무기들고 앉아 왼쪽으로
		break;
	case Rifle_crouch_walk_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(4);//무기들고 앉아 왼쪽뒤로
		break;
	case Rifle_crouch_walk_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(3);//무기들고 앉아 뒤로
		break;
	case Rifle_crouch_walk_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(2);//무기들고 앉아 우측뒤로
		break;
	case Rifle_crouch_walk_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(1);//무기들고 앉아 우측으로
		break;
	case Rifle_crouch_walk_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(0);//무기들고 앉아 우측앞으로
		break;

	default:
		break;
	}
	//}
	//else if (m_pSkinnedMesh == g_pSkinnedMeshManager->GetSkinnedMesh("PlayerAction"))
	//{
	//	switch (m_eState)
	//	{

	//	case Medkit:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(24);
	//		break;
	//	case Bandage:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(23);
	//		break;
	//	case Drink:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(22);
	//		break;
	//	case PainKiller:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(21);
	//		break;
	//	case Aiming:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(20);
	//		break;
	//	case Rebound:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(19);
	//		break;
	//	case Reload:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(18);
	//		break;
	//	case Stand_idle:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(17);
	//		break;
	//	case Crouch_idle:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(16);
	//		break;
	//	case Gun_acceptance:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(15);
	//		break;
	//	case Null:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(14);
	//		break;
	//	case Swap_Weapon:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(13);
	//		break;
	//	case Stand_Punch1:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(12);
	//		break;
	//	case Stand_Punch2:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(11);
	//		break;
	//	case Stand_Punch3:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(10);
	//		break;
	//	case Crouch_punch1:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(9);
	//		break;
	//	case Crouch_punch2:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(8);
	//		break;
	//	case Crouch_punch3:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(7);
	//		break;
	//	case Aiming2:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(6);
	//		break;
	//	case Stand_Rifle_idle:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(5);
	//		break;
	//	case Crouch_rifle_idle:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(4);
	//		break;
	//	case Kar98_reload:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(3);
	//		break;
	//	case Kar98_boltAction:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(2);
	//		break;
	//	case Falldown:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(1);
	//		break;
	//	case Faint_idle:
	//		m_pSkinnedMesh->SetAnimationIndexBlend(0);
	//		break;
	//	default:
	//		break;
	//	}
	//}
}

void Player::BulletHit()
{
	if (m_fCurrHP <= 0)
	{
		m_fCurrHP = 0;

		m_eState = Falldown;
		m_pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh("PlayerAction");
		LPD3DXANIMATIONSET	pAnimSet = NULL;
		aniControlerTmp->GetAnimationSet(1, &pAnimSet);
		aniControlerTmp->SetTrackAnimationSet(0, pAnimSet);

		SAFE_RELEASE(pAnimSet);
	}
	else
	{
		//피격
		m_pHitUI->AddHitUI(g_pRandomFunc->GetInt(2));

		m_fCurrHP -= 10.f;
	}
}