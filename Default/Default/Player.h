#pragma once
#include "Obj.h"

class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual	void CollisionEnter(CObj* _sour);

public:
	void SetObjList(list<CObj*>* pObjList);
	void SetMonsterList(list<CObj*>* pMonsterList);
	void SetGetBarrierItem(); // 베리어 아이템 먹게되면 발동 함수
	void SetGetPowerItem(); // 파워아이템을 먹게 되면 발동 함수
	class CObj* GetBarrierClass(); // 베리어클래스 포인터를 반환하는 함수
	int* GetPowerUpItemCount(); //파워업 아이템 먹은 횟수 반환
	int* GetLife(); //플레이어 목숨 
	int* GetBombNum(); // 폭탄 개수 반환
	void PlayerHit(); // 플레이어 피격시 발동 함수

	INFO* GetPlayerInfo(void) { return &m_tInfo; }

private:
	void		Key_Input(void);
	void		NormalFire(); //일반 총알 발사
	void		LevelOneFire(); // 1단계 총알 발사
	void		ShotGunFire(); // 샷건 총알 발사
	void		BombGunFire();
	void		CollisionWindow(); //플레이어가 화면 으로 못나가게 충돌처리
	void		InitBarrier(); // 베리어 생성 함수
	void		InitAssistantPlane(); //보조 비행기 생성 함수
	void		PowerUp(); // 파워업 카운트 상승
	void		AddBomb(); // 폭탄 추가
	bool		DeployBomb(); // 폭탄 발동
	void		RunEffect(); //피격 이펙트
	void		EffectRender(); //피격이펙트 실행


private:
	int m_iLife; // 목숨
	int m_iBomb; // 폭탄 개수
	int m_iPowerUpItemCount; // 파워업 아이템 먹은 횟수
	bool m_bIsBarrier; // 방어막 아이템 사용/불가능 판단
	class CBarrier* m_pBarrier; // 배리어 클래스
	class CAssistantPlayer* m_pAssistant[AST_END]; // 보조미니비행기 클래스
	list<CObj*>* m_bulletList; // 총알 리스트
	list<CObj*>* m_MonsterList; // 몬스터 리스트
	bool m_bIsCollision; //충돌 됐는지 안됐는지 확인
	bool m_bIsRunEffect; //피격 받았는지 안받았는지 확인
	int m_iEffectCount; // 이펙트 색상

};

