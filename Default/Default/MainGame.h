#pragma once

#include "Include.h"

#include "Player.h"
#include "Ui.h"
#include "Item.h"
#include "Timer.h"

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

	void	RemovedToTargetClear(CObj*);

public:
	static int TotalKillCount;
	static int KillCount;
	static int BossCount;
	static bool bBoss;
	static long Score;
	static int Level;
	static int PlayTime;
								
private:
	enum monsterType {
		Plane,
		Suicide,
		MonsterEnd
	};
	HDC		m_hDC;
	
	list<CObj*> m_ObjList[OBJ_END];
	list<CUi*> m_UiList[UI_END];

	TCHAR m_szFPS[64];

	// map
	CTimer* m_timer;

	CObj* m_player;

	bool m_debug;
	
};

