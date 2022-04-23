#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
public :
	void Set_pos(float _fX, float _fY)	{ m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	void Set_Dir(DIRECTION _eDir)		{ m_eDir = _eDir; }
	void Set_Dead(void)					{ m_bDead = true; }

	const INFO& Get_Info(void) const { return m_tInfo; }
	const RECT& Get_Rect(void) const { return m_tRect; }

public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

protected:
	void		Update_Rect(void);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;
	float		m_fSpeed;
	bool		m_bDead;
};

