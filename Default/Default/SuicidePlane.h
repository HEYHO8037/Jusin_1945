#pragma once
#include "Monster.h"
class CSuicidePlane :
	public CMonster
{
public:
	CSuicidePlane();
	virtual ~CSuicidePlane();
	
public : //obj �Ӽ�
	void Initialize() override;
	void Render(HDC hDC) override;
	void Release() override;

public :
	void BehaviorEnter() override; //������ ����
	void BehaviorExecute() override; //update ����
	void BehaviorExit() override; //�Ҹ��� ����

private:
	enum State
	{
		Create,
		Pattern, // �÷��̾� ���� (�÷��̾� ��ǥ ���ͼ�)
		Leave, // ����
		Destroy
	};

	State currentState;
};

