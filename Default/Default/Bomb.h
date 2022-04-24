#pragma once
#include "Ui.h"
class CBomb :
	public CUi
{
public:
	CBomb();
	virtual ~CBomb();

public :
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);
};

