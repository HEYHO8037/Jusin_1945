#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
public :
	void Set_pos(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; Update_Rect(); }
	void Set_Dir(DIRECTION _eDir)		{ m_eDir = _eDir; }
	void Set_Dead(void)					{ m_bDead = true; }
	void SetHP(int _hp)					{ m_iHP = _hp; }
	void SetMaxHP(int _maxHp)			{ m_iMaxHP = _maxHp; }

	int GetHP() { return m_iHP; }
	int GetMaxHP() { return m_iMaxHP; }

	bool GetDead() { return m_bDead; }

	const INFO& Get_Info(void) const { return m_tInfo; }
	const RECT& Get_Rect(void) const { return m_tRect; }

	void SetTarget(CObj* _targetObj) { m_targetObj = _targetObj; }
	CObj* GetTarget() { return m_targetObj; }
	void ClearTarget() { m_targetObj = nullptr; }

public:
	virtual		void	Initialize(void)			PURE;
	virtual		int		Update(void)				PURE;
	virtual		void	Late_Update(void)			PURE;
	virtual		void	Render(HDC hDC)				PURE;
	virtual		void	Release(void)				PURE;
	virtual		void	CollisionEnter(CObj* _sour) PURE;

protected:
	void		Update_Rect(void);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;
	float		m_fSpeed;
	bool		m_bDead;
	int			m_iMaxHP;
	int			m_iHP;

	CObj* m_targetObj;
};

