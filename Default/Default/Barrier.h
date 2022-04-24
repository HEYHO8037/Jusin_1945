#pragma once
#include "Obj.h"
class CBarrier :
	public CObj
{
public:
	CBarrier();
	virtual ~CBarrier();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual	void CollisionEnter(CObj* _sour);

public:
	void SetPlayerInfo(INFO* pPlayerInfo);
	int GetRotateRate() const; // ȸ�������� ��ȯ

private:
	void UpdatePos();

private:
	INFO* m_pPlayerInfo;
	float m_fAngle;
	int m_iRotate;

};

