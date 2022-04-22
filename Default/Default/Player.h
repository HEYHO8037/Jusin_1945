#pragma once
#include "Obj.h"

class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void SetObjList(list<CObj*>* pObjList);

private:
	void		Key_Input(void);
	void		CollisionWindow(); //�÷��̾ ȭ�� ������ �������� �浹ó��
	void		SetBarrier();

private:
	class CBarrier* m_pBarrier;
	list<CObj*>* m_pObjList;



	//bullet Ŭ���� ������ Set_BulletList �Լ� �����
};

