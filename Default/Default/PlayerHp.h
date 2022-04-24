#pragma once
#include "Ui.h"

class CPlayerHp :
	public CUi
{
public:
	CPlayerHp();
	virtual ~CPlayerHp();

public :
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);

public:
	//플레이어의 실시간 info받아오기 위해서
	void SetPlayerInfo(INFO* _pPlayerInfo)
	{
		m_pPlayerInfo = _pPlayerInfo;
	}


	//플레이어의 주소를 받아오는 변수
private :
	INFO* m_pPlayerInfo;

	float m_barRight;

};

