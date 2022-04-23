#pragma once
#include "Obj.h"

class CMonster : public CObj
{

public:
	CMonster();
	~CMonster();
	
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void SetBulletList(std::list<CObj*>* _pList) { m_bulletList = _pList; };
	void SetTarget(CObj* _obj) { targetObj = _obj; };

	virtual void BehaviorStart(); // AI시작

protected:
	bool TargetMove(); // 설정한 위치로 이동(true시 이동 완료)
	void Fire(float); // 총알 발사

	void BehaviorUpdate();
	virtual void BehaviorEnter();
	virtual void BehaviorExecute();
	virtual void BehaviorExit();

private:
	enum State {
		Create, // 생성
		Pattern1,
		Pattern2,
		Pattern3,
		Leave,
		Destroy
	};

	// Pattern1 3방향으로 총알 발사
	// Pattern2 현재 플레이어 쪽으로 돌진
	// Pattern3 원위치
	// Pattern4 
	// Leave 퇴장(아래로 쭉 이동함)
	// Destroy 삭제
	State currentState;


protected:
	enum Behavior {
		Enter,
		Execute,
		Exit
	};

	POINT originPosition; // 원위치
	POINT targetPosition; // 이동할 위치
	
	CObj* targetObj; // 대상

	
	Behavior behaviorState;

	std::list<CObj*>* m_bulletList;
	
	bool m_bAIStart;
};

