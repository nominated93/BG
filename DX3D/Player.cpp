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

	//Player �ִϸ��̼� ����
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

	//�κ��丮
	m_pInven = new Inventory(); m_pInven->AddressLink(m_pIM); m_pInven->Init();

	//�ǰ�
	m_pHitUI = new HitUI; m_pHitUI->Init();
	
	//�浹
	m_pOBB = new OBB;
	m_pOBB->Init(D3DXVECTOR3(m_pSkinnedMesh->GetMin().x, m_pSkinnedMesh->GetMin().y, m_pSkinnedMesh->GetMin().z)
		, D3DXVECTOR3(m_pSkinnedMesh->GetMax().x, m_pSkinnedMesh->GetMax().y, m_pSkinnedMesh->GetMax().z));

	m_bulletCntStr[0] = '\0';
	m_bulletTotalStr[0] = '\0';
	strcat_s(m_bulletCntStr, to_string(m_bulletCurrCnt).data());
	strcat_s(m_bulletTotalStr, "�� ");
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

	//ü�¹�
	m_fMaxHP = m_fCurrHP = 100.f;
	m_pPB = new ProgressBarManager; m_pPB->Init();
	m_pPB->SetPosition(WINSIZEX / 2 - m_pPB->GetPUIImg()->GetInfo().Width / 2, WINSIZEY - WINSIZEY / 15);
	m_pPB->SetGauge(m_fCurrHP, m_fMaxHP);

	//�������浹 �� ����
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
		//���Ǿ��浹 ��ǥ����
		m_tCollisionSphere_Item.center = m_pos;


		//�κ��� �ƴҶ�
		if (m_isGun && !(m_pInven->m_isInvenUI))
		{
			//�ѽ��
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

			//������
			if (g_pKeyboardManager->isOnceKeyDown('R'))
			{
				m_isReload = true;
				ReloadAction();
			}
			else
			{
				m_isReload = false;
			}


			//��
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

		//�κ��丮
		m_pInven->Update();

		//�ǰ�
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




	//ü�¹� �����
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

	//��ġ
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

		//�κ��丮
		m_pInven->Render();

		//�ǰ�
		m_pHitUI->Render();
	}

	if (m_pSkinnedMesh)
	{
		m_pSkinnedMesh->Render(NULL, &m_matWorld);
		m_pOBB->Render_Debug(255);
	}


	//ü�¹�
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

	// �ִϸ��̼� ����
	if (m_keyState.bSit)	// �ɾ��ֳ� �ƴϳ�
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
	m_isJumping = false; //�Ǵ��� Ȯ��


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
	{	// �ִϸ��̼� ����
		if (m_keyState.bSit)	// �ɾ��ֳ� �ƴϳ�
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
		// �ִϸ��̼� ����
		if (m_keyState.bSit)	// �ɾ��ֳ� �ƴϳ�
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
		m_pSkinnedMesh->SetAnimationIndexBlend(83);//������� ���ֱ�
		break;
	case Melee_stand_pickup:
		m_pSkinnedMesh->SetAnimationIndexBlend(82);//������� �� �ݱ�
		break;
	case Melee_stand_jump:
		m_pSkinnedMesh->SetAnimationIndexBlend(81);//������� ����
		break;
	case Melee_stand_punch1:
		m_pSkinnedMesh->SetAnimationIndexBlend(80);//������� �ָ���1
		break;
	case Melee_stand_punch2:
		m_pSkinnedMesh->SetAnimationIndexBlend(79);//������� �ָ���2
		break;
	case Melee_stand_punch3:
		m_pSkinnedMesh->SetAnimationIndexBlend(78);//������� �ָ���3
		break;
	case Melee_stand_fastrun:
		m_pSkinnedMesh->SetAnimationIndexBlend(77);//������� ���� ��������(??)
		break;
	case Melee_stand_run_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(76);//������� �پ ������
		break;
	case Melee_stand_run_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(75);//������� �پ ���ʾ�����
		break;
	case Melee_stand_run_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(74);//������� �پ ��������
		break;
	case Melee_stand_run_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(73);//������� �پ ���ʵڷ�
		break;
	case Melee_stand_run_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(72);//������� �پ �ڷ�
		break;
	case Melee_stand_run_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(71);//������� �پ �����ڷ�
		break;
	case Melee_stand_run_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(70);//������� �پ ��������
		break;
	case Melee_stand_run_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(69);//������� �پ ����������
		break;
	case Melee_stand_walk_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(68);//������� ������
		break;
	case Melee_stand_walk_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(67);//������� ���ʾ�����
		break;
	case Melee_stand_walk_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(66);//������� ��������
		break;
	case Melee_stand_walk_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(65);//������� ���ʵڷ�
		break;
	case Melee_stand_walk_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(64);//������� �ڷ�
		break;
	case Melee_stand_walk_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(63);//������� �����ڷ�
		break;
	case Melee_stand_walk_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(62);//������� ��������
		break;
	case Melee_stand_walk_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(61);//������� ����������
		break;

		//60~39 ���� ���� �ɾƼ� �ൿ
	case Melee_crouch_idle:
		m_pSkinnedMesh->SetAnimationIndexBlend(60);//������� �ɾ� �ֱ�
		break;
	case Melee_crouch_pickup:
		m_pSkinnedMesh->SetAnimationIndexBlend(59);//������� �ɾ� �� �ݱ�
		break;
	case Melee_crouch_punch1:
		m_pSkinnedMesh->SetAnimationIndexBlend(58);//������� �ɾ� �ָ���1
		break;
	case Melee_crouch_punch2:
		m_pSkinnedMesh->SetAnimationIndexBlend(57);//������� �ɾ� �ָ���2
		break;
	case Melee_crouch_punch3:
		m_pSkinnedMesh->SetAnimationIndexBlend(56);//������� �ɾ� �ָ���3
		break;
	case Melee_crouch_fastrun:
		m_pSkinnedMesh->SetAnimationIndexBlend(55);//������� �ɾ� ���� ��������(??)
		break;
	case Melee_crouch_run_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(54);//������� �ɾ� �پ ������
		break;
	case Melee_crouch_run_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(53);//������� �ɾ� �پ ���ʾ�����
		break;
	case Melee_crouch_run_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(52);//������� �ɾ� �پ ��������
		break;
	case Melee_crouch_run_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(51);//������� �ɾ� �پ ���ʵڷ�
		break;
	case Melee_crouch_run_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(50);//������� �ɾ� �پ �ڷ�
		break;
	case Melee_crouch_run_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(49);//������� �ɾ� �پ �����ڷ�
		break;
	case Melee_crouch_run_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(48);//������� �ɾ� �پ ��������
		break;
	case Melee_crouch_run_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(47);//������� �ɾ� �پ ����������
		break;
	case Melee_crouch_walk_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(46);//������� �ɾ� ������
		break;
	case Melee_crouch_walk_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(45);//������� �ɾ� ���ʾ�����
		break;
	case Melee_crouch_walk_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(44);//������� �ɾ� ��������
		break;
	case Melee_crouch_walk_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(43);//������� �ɾ� ���ʵڷ�
		break;
	case Melee_crouch_walk_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(42);//������� �ɾ� �ڷ�
		break;
	case Melee_crouch_walk_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(41);//������� �ɾ� �����ڷ�
		break;
	case Melee_crouch_walk_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(40);//������� �ɾ� ��������
		break;
	case Melee_crouch_walk_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(39);//������� �ɾ� ����������
		break;

		//38 ~ 19�� ������ �ൿ.
	case Rifle_stand_idle:
		m_pSkinnedMesh->SetAnimationIndexBlend(38);//������ ���ֱ�
		break;
	case Rifle_stand_pickup:
		m_pSkinnedMesh->SetAnimationIndexBlend(37);//������ �� �ݱ�
		break;
	case Rifle_stand_jump:
		m_pSkinnedMesh->SetAnimationIndexBlend(36);//������ ����
		break;
	case Rifle_stand_fastrun:
		m_pSkinnedMesh->SetAnimationIndexBlend(35);//������ ���� ��������(??)
		break;
	case Rifle_stand_run_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(34);//������ �پ ������
		break;
	case Rifle_stand_run_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(33);//������ �پ ���ʾ�����
		break;
	case Rifle_stand_run_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(32);//������ �پ ��������
		break;
	case Rifle_stand_run_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(31);//������ �پ ���ʵڷ�
		break;
	case Rifle_stand_run_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(30);//������ �پ �ڷ�
		break;
	case Rifle_stand_run_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(29);//������ �پ �����ڷ�
		break;
	case Rifle_stand_run_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(28);//������ �پ ��������
		break;
	case Rifle_stand_run_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(27);//������ �پ ����������
		break;
	case Rifle_stand_walk_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(26);//������ ������
		break;
	case Rifle_stand_walk_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(25);//������ ���ʾ�����
		break;
	case Rifle_stand_walk_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(24);//������ ��������
		break;
	case Rifle_stand_walk_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(23);//������ ���ʵڷ�
		break;
	case Rifle_stand_walk_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(22);//������ �ڷ�
		break;
	case Rifle_stand_walk_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(21);//������ �����ڷ�
		break;
	case Rifle_stand_walk_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(20);//������ ��������
		break;
	case Rifle_stand_walk_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(19);//������ ����������
		break;

		//18 ~ 0 ���� ��� �ɾƼ� �ൿ
	case Rifle_crouch_idle:
		m_pSkinnedMesh->SetAnimationIndexBlend(18);//������ �ɾ� �ֱ�
		break;
	case Rifle_crouch_pickup:
		m_pSkinnedMesh->SetAnimationIndexBlend(17);//������ �ɾ� �� �ݱ�
		break;
	case Rifle_crouch_fastrun:
		m_pSkinnedMesh->SetAnimationIndexBlend(16);//������ �ɾ� ���� ��������(??)
		break;
	case Rifle_crouch_run_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(15);//������ �ɾ� �پ ������
		break;
	case Rifle_crouch_run_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(14);//������ �ɾ� �پ ���ʾ�����
		break;
	case Rifle_crouch_run_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(13);//������ �ɾ� �پ ��������
		break;
	case Rifle_crouch_run_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(12);//������ �ɾ� �پ ���ʵڷ�
		break;
	case Rifle_crouch_run_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(11);//������ �ɾ� �پ �ڷ�
		break;
	case Rifle_crouch_run_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(10);//������ �ɾ� �پ �����ڷ�
		break;
	case Rifle_crouch_run_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(9);//������ �ɾ� �پ ��������
		break;
	case Rifle_crouch_run_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(8);//������ �ɾ� �پ ����������
		break;
	case Rifle_crouch_walk_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(7);//������ �ɾ� ������
		break;
	case Rifle_crouch_walk_left_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(6);//������ �ɾ� ���ʾ�����
		break;
	case Rifle_crouch_walk_left:
		m_pSkinnedMesh->SetAnimationIndexBlend(5);//������ �ɾ� ��������
		break;
	case Rifle_crouch_walk_left_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(4);//������ �ɾ� ���ʵڷ�
		break;
	case Rifle_crouch_walk_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(3);//������ �ɾ� �ڷ�
		break;
	case Rifle_crouch_walk_right_back:
		m_pSkinnedMesh->SetAnimationIndexBlend(2);//������ �ɾ� �����ڷ�
		break;
	case Rifle_crouch_walk_right:
		m_pSkinnedMesh->SetAnimationIndexBlend(1);//������ �ɾ� ��������
		break;
	case Rifle_crouch_walk_right_front:
		m_pSkinnedMesh->SetAnimationIndexBlend(0);//������ �ɾ� ����������
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
		//�ǰ�
		m_pHitUI->AddHitUI(g_pRandomFunc->GetInt(2));

		m_fCurrHP -= 10.f;
	}
}