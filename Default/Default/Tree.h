#pragma once
#include "Ui.h"
class CTree :
	public CUi
{
public:
	CTree();
	virtual ~CTree();

public :
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);
};

