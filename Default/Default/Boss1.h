#pragma once
#include "Monster.h"
#include "Timer.h"

class CBoss1 : public CMonster
{
public:
	CBoss1();
	virtual ~CBoss1();

	void Initialize() override;
	void Render(HDC hDC) override;
	void Release() override;

protected:
	void BehaviorEnter() override;
	void BehaviorExecute() override;
	void BehaviorExit() override;

	void Die() override;

private:
	void RandomPattern();

private:
	enum State {
		Create,
		Pattern1,		// 3방향 총알 발사
		Pattern2,		// 돌진
		Pattern3,		// 한꺼번에 회전발사
		Pattern4,		// 시간차 회전발사
		Return,			// 돌진 복귀
		Idle
	};

	State currentState;

	CTimer* bossShotTimer;

	int patternAngle;

	int m_iShotCount;

};

