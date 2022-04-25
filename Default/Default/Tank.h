#pragma once
#include "Monster.h"
class CTank :
	public CMonster
{
public:
	CTank();
	virtual ~CTank();
public:
	virtual void BehaviorEnter() PURE;
	virtual void BehaviorExecute() PURE;
	virtual void BehaviorExit() PURE;
};

