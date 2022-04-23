#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	CItem();
	virtual ~CItem();
public:
	virtual		void	Initialize(void);
	virtual		int	Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);
public:
	void Item_Render(HDC hDC);
private:
	float m_fAngle;
	ITEMID m_Item_Id;
	RECT rc;
	TCHAR		m_szItem_Name[64];
};

