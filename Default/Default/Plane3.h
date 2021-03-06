#pragma once
#include "Monster.h"
#include "Timer.h"

class CPlane3 : public CMonster
{
public:
	CPlane3();
	virtual ~CPlane3();

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
		Create, // ????
		Pattern1
	};

	const float shotInterval;

	State currentState;
	CTimer* shotTimer;

	INFO m_tDir;
};

