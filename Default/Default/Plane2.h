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
		Create, // 생성
		Pattern1
	};
	// Pattern1 대각선으로 이동하며 총알 발사

	const float shotInterval;

	State currentState;
	CTimer* shotTimer;

	INFO m_tDir;
};

