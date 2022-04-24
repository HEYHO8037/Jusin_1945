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
	//�÷��̾��� �ǽð� info�޾ƿ��� ���ؼ�
	void SetPlayerInfo(INFO* _pPlayerInfo)
	{
		m_pPlayerInfo = _pPlayerInfo;
	}


	//�÷��̾��� �ּҸ� �޾ƿ��� ����
private :
	INFO* m_pPlayerInfo;

	float m_barRight;

};

