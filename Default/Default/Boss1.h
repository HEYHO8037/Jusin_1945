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
		Pattern1,		// 3���� �Ѿ� �߻�
		Pattern2,		// ����
		Pattern3,		// �Ѳ����� ȸ���߻�
		Pattern4,		// �ð��� ȸ���߻�
		Return,			// ���� ����
		Idle
	};

	State currentState;

	CTimer* bossShotTimer;

	int patternAngle;

	int m_iShotCount;

};

