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
	void CollisionEnter(CObj* _sour);

public :
	void BehaviorEnter() override; //������ ����
	void BehaviorExecute() override; //update ����
	void BehaviorExit() override; //�Ҹ��� ����

public :
	void SetPlayerInfo(INFO* _pPlayerInfo) { m_pPlayerInfo = _pPlayerInfo; }
	void SetDirection(float _x, float _y) { m_tDir.fX = _x, m_tDir.fY = _y; };

private:
	enum State
	{
		Create,
		Pattern, // �÷��̾� ���� (�÷��̾� ��ǥ ���ͼ�)
		Leave, // ����
		Destroy
	};

	State currentState;

	INFO* m_pPlayerInfo;

	INFO m_tDir;
	POINT m_tPosin;

	float m_fDiagonal;
	float m_fAngle;
};

