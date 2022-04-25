#include "stdafx.h"
#include "CollisionMgr.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}


void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				Dest->CollisionEnter(Sour);
				Sour->CollisionEnter(Dest);
			}
		}
	}
}

void CCollisionMgr::Collision_ObjListRect(CObj* _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	if (!_Dest)
	{
		return;
	}


	for (auto& Sour : _Sour)
	{
		if (IntersectRect(&rc, &(_Dest->Get_Rect()), &(Sour->Get_Rect())))
		{
			_Dest->CollisionEnter(Sour);
			Sour->CollisionEnter(_Dest);
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour)
{
	
	// abs : 절대값을 구해주는 함수
	float	fWidth  = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	// sqrt : 루트를 씌워주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;

	return fRadius > fDiagonal;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->CollisionEnter(Sour);
				Sour->CollisionEnter(Dest);
			}
		}
	}
}
