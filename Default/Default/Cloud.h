#pragma once
#include "Ui.h"
class CCloud :
	public CUi
{
public:
	CCloud();
	virtual ~CCloud();

public :
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);

	//���� �����Ϸ� �浹ó�� �߰�
};

