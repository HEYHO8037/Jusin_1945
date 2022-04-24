#pragma once
#include "Ui.h"
#include "Obj.h"
class CLife :
	public CUi
{
public:
	CLife();
	virtual ~CLife();

	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);

};

