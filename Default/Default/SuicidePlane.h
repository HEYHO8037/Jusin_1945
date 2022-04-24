#pragma once
#include "Monster.h"
class CSuicidePlane :
	public CMonster
{
public:
	CSuicidePlane();
	virtual ~CSuicidePlane();
	
public : //obj 속성
	void Initialize() override;
	void Render(HDC hDC) override;
	void Release() override;
	void CollisionEnter(CObj* _sour);

public :
	void BehaviorEnter() override; //생성자 역할
	void BehaviorExecute() override; //update 역할
	void BehaviorExit() override; //소멸자 역할

public :
	void SetPlayerInfo(INFO* _pPlayerInfo) { m_pPlayerInfo = _pPlayerInfo; }
	void SetDirection(float _x, float _y) { m_tDir.fX = _x, m_tDir.fY = _y; };

private:
	enum State
	{
		Create,
		Pattern, // 플레이어 돌격 (플레이어 좌표 얻어와서)
		Leave, // 퇴장
		Destroy
	};

	State currentState;

	INFO* m_pPlayerInfo;

	INFO m_tDir;
	POINT m_tPosin;

	float m_fDiagonal;
	float m_fAngle;
};

