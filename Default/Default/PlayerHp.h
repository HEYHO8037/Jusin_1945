#pragma once
#include "Ui.h"

class CPlayerHp :
	public CUi
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

