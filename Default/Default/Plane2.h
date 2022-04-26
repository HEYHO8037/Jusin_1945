#pragma once
#include "Monster.h"
#include "Timer.h"

class CPlane2 : public CMonster
{
public:
	CPlane2();
	~CPlane2();

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
		Create, // ����
		Pattern1
	};
	// Pattern1 �밢������ �̵��ϸ� �Ѿ� �߻�

	const float shotInterval;

	State currentState;
	CTimer* shotTimer;

	INFO m_tDir;
};

