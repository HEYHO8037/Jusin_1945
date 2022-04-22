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
	void		CollisionWindow(); //플레이어가 화면 밖으로 못나가게 충돌처리
	void		SetBarrier();

private:
	class CBarrier* m_pBarrier;
	list<CObj*>* m_pObjList;



	//bullet 클래스 생성시 Set_BulletList 함수 만들기
};

