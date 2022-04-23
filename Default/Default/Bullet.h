#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	CBullet(INFO tInfo, bool bIsScrew);
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	float m_fAngle;
	bool m_bIsScrew;

};

