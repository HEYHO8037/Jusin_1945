#pragma once
#include "Include.h"
#include "Obj.h"

class CUi
{
public:
	CUi();
	virtual ~CUi();

public :
	virtual void Initialize(void)	PURE;
	virtual int Update(void)		PURE;
	virtual void Late_Update(void)	PURE;
	virtual void Render(HDC hDC)	PURE;
	virtual void Release(void)		PURE;

public :
	void Set_Pos(float _fX, float _fY)	{ m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	void SetObjInfo(CObj* _pObj)		{ m_pObj = _pObj; }
protected:
	void Update_Rect(void);

protected:
	INFO m_tInfo;
	RECT m_tRect;

	float m_fSpeed;
	bool m_bDead;

	CObj* m_pObj;

	//업데이트마다 GETHP해서 줄어들게하기
};

