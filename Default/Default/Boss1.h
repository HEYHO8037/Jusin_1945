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
		Idle,
		Leave,
		Destroy
	};

	State currentState;

	CTimer* bossShotTimer;
};

