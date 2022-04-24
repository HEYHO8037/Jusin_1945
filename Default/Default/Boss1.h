#pragma once
#include "Monster.h"
#include "Timer.h"

class CBoss1 : public CMonster
{
public:
	CBoss1();
	~CBoss1();

	void Initialize() override;
	void Render(HDC hDC) override;
	void Release() override;

protected:
	void BehaviorEnter();
	void BehaviorExecute();
	void BehaviorExit();

private:
	enum State {
		Create,
		Pattern1,
		Pattern2,
		Pattern2Back,
		Pattern3,		// 한꺼번에 회전발사
		Pattern4,		// 시간차 회전발사
		Idle,
		Leave,
		Destroy
	};

	State currentState;

	CTimer* bossShotTimer;

	int patternAngle;
};

