#pragma once
#include "Ui.h"

class CMonsterHp :
	public CUi
{
public:
	CMonsterHp();
	~CMonsterHp();

public :
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);

private :
	float m_barRight;
};

