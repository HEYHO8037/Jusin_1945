#include "stdafx.h"
#include "Barrier.h"
#include "AssistantPlayer.h"
#include "Bullet.h"
#include "Player.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "PlayerHp.h"
#include "Item.h"

CPlayer::CPlayer()
	: m_pBarrier(nullptr),
	  m_iPowerUpItemCount(0),
	  m_bIsBarrier(false),
	  m_bIsCollision(false),
	  m_iBomb(0)
{
	for (int i = 0; i < AST_END; ++i)
	{
		m_pAssistant[i] = nullptr;
	}
}

CPlayer::~CPlayer()
{
	Release();
	m_bulletList = nullptr;
	m_MonsterList = nullptr;
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 700.f;
	m_iHP = 100;
	m_iMaxHP = 100;
	m_iLife = 3;

	m_tInfo.fCX = (float)PlayerSize;
	m_tInfo.fCY = (float)PlayerSize;

	m_fSpeed = 10.f;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Key_Input();

	if (m_pBarrier)
	{
		m_pBarrier->Update();
	}

	if (m_pAssistant[AST_LEFT])
	{
		for (int i = 0; i < AST_END; ++i)
		{
			m_pAssistant[i]->Update();
		}
	}

	Update_Rect();
	CollisionWindow();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	if (m_pBarrier)
	{
		m_pBarrier->Late_Update();

		if (m_pBarrier->GetRotateRate() >= 10)
		{
			delete m_pBarrier;
			m_pBarrier = nullptr;
		}
	}
}

void CPlayer::Render(HDC hDC)
{
	HBRUSH brush;
	HGDIOBJ OldBrush;

	brush = CreateSolidBrush(RGB(0, 200, 200));
	OldBrush = SelectObject(hDC, brush);

	SelectObject(hDC, brush);

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	SelectObject(hDC, OldBrush);
	DeleteObject(brush);

	if (m_pBarrier)
	{
		m_pBarrier->Render(hDC);
	}

	if (m_pAssistant[AST_LEFT])
	{
		for (int i = 0; i < AST_END; ++i)
		{
			m_pAssistant[i]->Render(hDC);
		}
	}
}

void CPlayer::Release(void)
{
	if (m_pAssistant[AST_LEFT])
	{
		for (int i = 0; i < AST_END; ++i)
		{
			delete m_pAssistant[i];
			m_pAssistant[i] = nullptr;
		}
	}

	if (m_pBarrier)
	{
		delete m_pBarrier;
		m_pBarrier = nullptr;
	}
}

void CPlayer::CollisionEnter(CObj * _sour)
{


	if (dynamic_cast<CBullet*>(_sour)->GetType() == PLAYER_BULLET)
	{
		return;
	}

	if (dynamic_cast<CBullet*>(_sour)->GetType() == MONSTER_BULLET)
	{
		PlayerHit();
	}
	else if (dynamic_cast<CItem*>(_sour)->GetItemID() == ITEM_POWER)
	{
		_sour->Set_Dead();
		PowerUp();
	}
	else if (dynamic_cast<CItem*>(_sour)->GetItemID() == ITEM_SHIELD)
	{
		_sour->Set_Dead();
		InitBarrier();

	}
	else if (dynamic_cast<CItem*>(_sour)->GetItemID() == ITEM_BOMB)
	{
 		_sour->Set_Dead();
 		AddBomb();
	}
	else if (dynamic_cast<CMonster*>(_sour)->GetDead() == false)
	{
		PlayerHit();
		if (_sour->GetMaxHP() == 1)
		{
			_sour->Set_Dead();
		}
		else
		{
			m_tInfo.fY += 200;
		}
	}

}

void CPlayer::SetObjList(list<CObj*>* pObjList)
{
	m_bulletList = pObjList;
}

void CPlayer::SetMonsterList(list<CObj*>* pMonsterList)
{
	m_MonsterList = pMonsterList;
}

void CPlayer::SetGetBarrierItem()
{
	m_bIsBarrier = true;
}

void CPlayer::SetGetPowerItem()
{
	m_iPowerUpItemCount++;
}

CObj * CPlayer::GetBarrierClass()
{
	if (m_pBarrier)
	{
		return dynamic_cast<CObj*>(m_pBarrier); 
	}
	else
	{
		return nullptr;
	}
}

int* CPlayer::GetPowerUpItemCount()
{
	return &m_iPowerUpItemCount;
}

int * CPlayer::GetLife()
{
	return &m_iLife;
}

int * CPlayer::GetBombNum()
{
	return &m_iBomb;
}

void CPlayer::PlayerHit()
{
	m_iHP -= 20;

	if (m_iHP <= 0)
	{
		m_iLife -= 1;
		m_iHP = m_iMaxHP;
	}

	if (m_iLife == 0)
	{
		Set_Dead();
	}
}


void CPlayer::Key_Input(void)
{
	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if(GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else

		m_tInfo.fX -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX += m_fSpeed;

	}
	else if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	else if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;



	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_iPowerUpItemCount == 1)
		{
			LevelOneFire();
		}
		else if (m_iPowerUpItemCount == 3)
		{
			ShotGunFire();

			if (m_pAssistant[AST_LEFT])
			{
				for (int i = 0; i < AST_END; ++i)
				{
					m_pAssistant[i]->ShotGunFire();
				}
			}
		}
		else
		{
			NormalFire();

			if (m_pAssistant[AST_LEFT])
			{
				for (int i = 0; i < AST_END; ++i)
				{
					m_pAssistant[i]->NormalFire();
				}
			}
		}
	}
}

void CPlayer::NormalFire()
{
	int iDegree = -90;
	CObj* newBullet = CAbstractFactory<CBullet>::Create();
	CBullet* BulletObj = dynamic_cast<CBullet*>(newBullet);
	BulletObj->SetDirection(cosf(iDegree * PI / 180.f), sinf(iDegree * PI / 180.f));
	BulletObj->SetType(PLAYER_BULLET);
	BulletObj->Set_pos(m_tInfo.fX, m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_bulletList->push_back(newBullet);
}

void CPlayer::LevelOneFire()
{
	int iDegree = -90;
	iDegree -= 15;
	CObj* newBullet = CAbstractFactory<CBullet>::Create();
	CBullet* BulletObj = dynamic_cast<CBullet*>(newBullet);
	BulletObj->SetDirection(cosf(iDegree * PI / 180.f), sinf(iDegree * PI / 180.f));
	BulletObj->SetType(PLAYER_BULLET);
	BulletObj->Set_pos(m_tInfo.fX, m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_bulletList->push_back(newBullet);

	iDegree = -90;
	iDegree += 15;
	newBullet = CAbstractFactory<CBullet>::Create();
	BulletObj = dynamic_cast<CBullet*>(newBullet);
	BulletObj->SetDirection(cosf(iDegree * PI / 180.f), sinf(iDegree * PI / 180.f));
	BulletObj->SetType(PLAYER_BULLET);
	BulletObj->Set_pos(m_tInfo.fX, m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_bulletList->push_back(newBullet);
}

void CPlayer::ShotGunFire()
{
	int iDegree = -90;
	CObj* newBullet = CAbstractFactory<CBullet>::Create();
	CBullet* BulletObj = dynamic_cast<CBullet*>(newBullet);
	BulletObj->SetDirection(cosf(iDegree * PI / 180.f), sinf(iDegree * PI / 180.f));
	BulletObj->SetType(PLAYER_BULLET);
	BulletObj->Set_pos(m_tInfo.fX, m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_bulletList->push_back(newBullet);

	iDegree -= 15;
	newBullet = CAbstractFactory<CBullet>::Create();
	BulletObj = dynamic_cast<CBullet*>(newBullet);
	BulletObj->SetDirection(cosf(iDegree * PI / 180.f), sinf(iDegree * PI / 180.f));
	BulletObj->SetType(PLAYER_BULLET);
	BulletObj->Set_pos(m_tInfo.fX, m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_bulletList->push_back(newBullet);

	iDegree = -90;

	iDegree += 15;
	newBullet = CAbstractFactory<CBullet>::Create();
	BulletObj = dynamic_cast<CBullet*>(newBullet);
	BulletObj->SetDirection(cosf(iDegree * PI / 180.f), sinf(iDegree * PI / 180.f));
	BulletObj->SetType(PLAYER_BULLET);
	BulletObj->Set_pos(m_tInfo.fX, m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_bulletList->push_back(newBullet);
}

void CPlayer::CollisionWindow()
{
	if (m_tRect.left < 0)
	{
		m_tInfo.fX = m_tInfo.fCX / 2.f;
		Update_Rect();
	}
	else if (m_tRect.right > WINCX)
	{
		m_tInfo.fX = WINCX - m_tInfo.fCX / 2.f;
		Update_Rect();
	}

	if (m_tRect.top < 0)
	{
		m_tInfo.fY = m_tInfo.fCY / 2.f;
		Update_Rect();
	}
	else if (m_tRect.bottom > WINCY)
	{
		m_tInfo.fY = WINCY - m_tInfo.fCY / 2.f;
		Update_Rect();
	}
}

void CPlayer::InitBarrier()
{
	if (m_pBarrier)
	{
		delete m_pBarrier;
		m_pBarrier = nullptr;
		m_pBarrier = new CBarrier();
		m_pBarrier->Initialize();
		m_pBarrier->SetPlayerInfo(&m_tInfo);
	}
	else if (!m_pBarrier)
	{
		m_pBarrier = new CBarrier();
		m_pBarrier->Initialize();
		m_pBarrier->SetPlayerInfo(&m_tInfo);
	}
}

void CPlayer::InitAssistantPlane()
{
	m_pAssistant[0] = new CAssistantPlayer(AST_LEFT);
	m_pAssistant[0]->Initialize();
	m_pAssistant[0]->SetPlayer(this);
	m_pAssistant[0]->SetObjList(m_bulletList);
	m_pAssistant[0]->SetSpeed(m_fSpeed);

	m_pAssistant[1] = new CAssistantPlayer(AST_RIGHT);
	m_pAssistant[1]->Initialize();
	m_pAssistant[1]->SetPlayer(this);
	m_pAssistant[1]->SetObjList(m_bulletList);
	m_pAssistant[1]->SetSpeed(m_fSpeed);
}

void CPlayer::PowerUp()
{
	m_iPowerUpItemCount++;

	if (m_iPowerUpItemCount == 2)
	{
		InitAssistantPlane();
	}
}

void CPlayer::AddBomb()
{
	if (m_iBomb == 3)
	{
		return;
	}

	m_iBomb++;
}

bool CPlayer::DeployBomb()
{
	if (m_iBomb)
	{
		m_iBomb--;
		return true;
	}
	else
	{
		return false;
	}

}
