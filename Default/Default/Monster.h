#pragma once
#include "Obj.h"

class CMonster : public CObj
{

public:
	CMonster();
	~CMonster();
	
	int Update() override;
	void Late_Update() override;

	void SetBulletList(std::list<CObj*>* _pList) { m_bulletList = _pList; };
	void SetAppearPosition(const int _x, const int _y) { appearPosition = { _x, _y }; };

	void CollisionEnter(CObj* _sour);
	void BehaviorStart(CObj*, std::list<CObj*>*, std::list<CObj*>*);

	int GetScore() { return m_iScore; }

	void Hit(); // 공격당함

protected:
	bool TargetMove(); 
	void Fire(float); 
	void DisplayInfo(HDC, int);
	void RunEffect();
	void EffectRender();

	void BehaviorUpdate();
	virtual void BehaviorEnter() PURE;
	virtual void BehaviorExecute() PURE;
	virtual void BehaviorExit() PURE;

	void Die();

protected:
	enum Behavior {
		Enter,
		Execute,
		Exit
	};


	POINT originPosition;
	POINT targetPosition;
	POINT appearPosition; // 생성후 이동할 위치

	Behavior behaviorState;

	std::list<CObj*>* m_bulletList;
	std::list<CObj*>* m_itemList;
	
	bool m_bAIStart;
	bool m_bDisplayInfo;

	int m_effectCount;
	
	int m_iScore;

private:
	bool m_bRunEffect;

};

