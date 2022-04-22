#pragma once

#include "Include.h"

#include "Player.h"
#include "Ui.h"

class CMainGame
{
public:				// 생성자, 소멸자
	CMainGame();
	~CMainGame();

	// public, protected, private 함수
public:
	void	Initialize(void);		// 초기화 함수
	void	Update(void);			// 매 프레임마다 갱신되는 데이터를 만드는 함수
	void	Late_Update(void);
	void	Render(void);			// 매 프레임마다 출력하는 함수
	void	Release(void);			// 동적할당한 포인터를 해제하는 함수

									// public, protected, private 변수
private:
	HDC		m_hDC;
	
	list<CObj*> m_ObjList[OBJ_END];
	list<CUi*> m_UiList[4];

	TCHAR m_szFPS[64];
	
};

