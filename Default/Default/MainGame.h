#pragma once

#include "Include.h"

#include "Player.h"
#include "Ui.h"
#include "Item.h"

class CMainGame
{
public:				
	CMainGame();
	~CMainGame();

public:
	void	Initialize(void);		
	void	Update(void);			
	void	Late_Update(void);
	void	Render(void);			
	void	Release(void);			

								
private:
	HDC		m_hDC;
	
	list<CObj*> m_ObjList[OBJ_END];
	list<CUi*> m_UiList[UI_END];

	TCHAR m_szFPS[64];
	
	CObj* TestItem;
};

