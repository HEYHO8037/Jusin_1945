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
	void SetGetBarrierItem(); // 베리어 아이템 먹게되면 발동 함수
	void SetGetPowerItem(); // 파워아이템을 먹게 되면 발동 함수
	class CBarrier* GetBarrierClass(); // 베리어클래스 포인터를 반환하는 함수

	 INFO* GetPlayerPointer(void) { return &m_tInfo; }

private:
	void		Key_Input(void);
	void		CollisionWindow(); //플레이어가 화면 밖으로 못나가게 충돌처리
	void		InitBarrier(); // 베리어 생성 함수
	void		InitAssistantPlane(); //보조 비행기 생성 함수

private:
	int m_iHP; // 체력
	int m_iPowerUpItemCount; // 파워업 아이템 먹은 횟수
	bool m_bIsBarrier; // 방어막 아이템 사용/불가능 판단
	class CBarrier* m_pBarrier; // 배리어 클래스
	class CAssistantPlayer* m_pAssistant[AST_END]; // 보조미니비행기 클래스
	list<CObj*>* m_pObjList;




	//bullet 클래스 생성시 Set_BulletList 함수 만들기
};

