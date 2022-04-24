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
		Create, // ����
		Pattern1,
		Idle,
		Leave,
		Destroy
	};

	// Pattern1 �Ʒ��������� �Ѿ� �߻�
	// Pattern2 ���� �÷��̾� ������ ����
	// Pattern3 ����ġ
	// Pattern4 
	// Leave ����(�Ʒ��� �� �̵���)
	// Destroy ����

	State currentState;

	const int residenceSecond = 3;
	CTimer* residenceTimer;
};

