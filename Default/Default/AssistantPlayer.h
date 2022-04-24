#pragma once
#include "Obj.h"
class CAssistantPlayer :
	public CObj
{
public:
	CAssistantPlayer();
	CAssistantPlayer(ASSISTANT_DIR iLeftRight);
	virtual ~CAssistantPlayer();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void SetPlayer(class CPlayer* pPlayer);
	void SetSpeed(float fSpeed);
	void SetObjList(list<CObj*>* pObjList);

public:
	void NormalFire();
	void ShotGunFire();

private:
	ASSISTANT_DIR m_eDir;
	CPlayer* m_pPlayer;
	list<CObj*>* m_bulletList;
};

