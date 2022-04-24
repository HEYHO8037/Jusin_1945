#pragma once
#include "Monster.h"
#include "Timer.h"

class CPlane : public CMonster
{
public:
	CPlane();
	~CPlane();

public:
	void Initialize() override;
	void Render(HDC hDC) override;
	void Release() override;

protected:
	virtual void BehaviorEnter();
	virtual void BehaviorExecute();
	virtual void BehaviorExit();

private:
	enum State {
		Create, // 생성
		Pattern1,
		Idle,
		Leave,
		Destroy
	};

	// Pattern1 아래방향으로 총알 발사
	// Pattern2 현재 플레이어 쪽으로 돌진
	// Pattern3 원위치
	// Pattern4 
	// Leave 퇴장(아래로 쭉 이동함)
	// Destroy 삭제

	State currentState;

	const int residenceSecond = 3;
	CTimer* residenceTimer;
};

