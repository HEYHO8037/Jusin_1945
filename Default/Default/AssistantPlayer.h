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
	void SetPlayerInfo(INFO* pPlayerInfo);
	void SetSpeed(float fSpeed);

private:
	ASSISTANT_DIR m_iLeftRight;
	INFO* m_pPlayerInfo;
};

