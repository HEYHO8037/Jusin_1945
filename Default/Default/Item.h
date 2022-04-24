#pragma once
#include "Obj.h"
#include <fontsub.h>
class CItem :
	public CObj
{
public:
	CItem();
	virtual ~CItem();
public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);
	virtual		void	CollisionEnter(CObj* _sour);

public:
	void Item_Render(HDC hDC);
	ITEMID GetItemID() const;
private:
	float m_fAngle;
	int m_iCount;
	ITEMID m_Item_Id;
	RECT rc;
	TCHAR		m_szItem_Name[64];
	HFONT m_Font;
	POINT m_ItemPoint;
	HBRUSH m_brush = CreateSolidBrush(RGB(0, 0, 200)); 
	HPEN m_pen = CreatePen(PS_SOLID, 5, RGB(153, 153, 153));
};

