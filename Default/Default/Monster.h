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

	void BehaviorStart(CObj*, std::list<CObj*>*); // AI����

protected:
	bool TargetMove(); // ������ ��ġ�� �̵�(true�� �̵� �Ϸ�)
	void Fire(float); // �Ѿ� �߻�

	void BehaviorUpdate();
	virtual void BehaviorEnter();
	virtual void BehaviorExecute();
	virtual void BehaviorExit();

	void DisplayInfo(HDC, int);

private:
	enum State {
		Create, // ����
		Pattern1,
		Pattern2,
		Pattern3,
		Leave,
		Destroy
	};

	// Pattern1 3�������� �Ѿ� �߻�
	// Pattern2 ���� �÷��̾� ������ ����
	// Pattern3 ����ġ
	// Pattern4 
	// Leave ����(�Ʒ��� �� �̵���)
	// Destroy ����
	State currentState;


protected:
	enum Behavior {
		Enter,
		Execute,
		Exit
	};

	POINT originPosition; // ����ġ
	POINT targetPosition; // �̵��� ��ġ
	
	CObj* targetObj; // ���

	Behavior behaviorState;

	std::list<CObj*>* m_bulletList;
	
	bool m_bAIStart;
	bool m_bDisplayInfo;
};

