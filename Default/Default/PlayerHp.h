#pragma once
#include "Obj.h"
class CPlayerHp :
	public CObj
{
public:
	CPlayerHp();
	virtual ~CPlayerHp();

public :
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);

};

