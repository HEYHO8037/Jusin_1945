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

	static void Create(std::list<CObj*>* ItemList,CObj* _ObjPtr)
	{
		CItem* Item = new CItem;

		ItemList->push_back(Item);

		srand((unsigned int)time(NULL));
		Item->iCreate_Per = (rand() % 10) + 1;
			if (Item->iCreate_Per == 1)
			{
				Item->Initialize();

			}
	}


public:
	void Item_Render(HDC hDC);
	ITEMID GetItemID() const;
private:
	float m_fAngle;
	int m_iCount; 
	int iCreate_Per = 0;
	ITEMID m_Item_Id;
	RECT rc;
	TCHAR		m_szItem_Name[64];
	HFONT m_Font;
	POINT m_ItemPoint;
	HBRUSH m_brush = CreateSolidBrush(RGB(0, 0, 200)); 
	HPEN m_pen = CreatePen(PS_SOLID, 5, RGB(153, 153, 153));
};

