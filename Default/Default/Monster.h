#pragma once
#include "Obj.h"

class CMonster : public CObj
{

public:
	CMonster();
	virtual ~CMonster();
	
	int Update() override;
	void Late_Update() override;

	void SetBulletList(std::list<CObj*>* _pList) { m_bulletList = _pList; };
	void SetAppearPosition(const float _x, const float _y) { appearPosition = { _x, _y }; };

	void CollisionEnter(CObj* _sour);
	void BehaviorStart(CObj*, std::list<CObj*>*, std::list<CObj*>*, std::list<CObj*>*);

	int GetScore() { return m_iScore; }

	void Hit(); // 공격당함

protected:
	const int baseShotAngle;

	bool TargetMove(); 
	void Fire(const int); 
	void DisplayInfo(HDC, const int);
	void RunEffect();
	void EffectRender();

	void BehaviorUpdate();
	virtual void BehaviorEnter() PURE;
	virtual void BehaviorExecute() PURE;
	virtual void BehaviorExit() PURE;

	void CommonDie();
	virtual void Die();

	void LeaveCheck();

protected:
	enum Behavior {
		Enter,
		Execute,
		Exit
	};


	Vector2D originPosition;
	Vector2D targetPosition;
	Vector2D appearPosition; // 생성후 이동할 위치

	Behavior behaviorState;

	std::list<CObj*>* m_bulletList;
	std::list<CObj*>* m_itemList;
	std::list<CObj*>* m_effectList;
	
	bool m_bAIStart;
	bool m_bDisplayInfo;

	int m_effectCount;
	
	int m_iScore;

private:
	bool m_bRunEffect;

	int effectDecreasePoint;
};

