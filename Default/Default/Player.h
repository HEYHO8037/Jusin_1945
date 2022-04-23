#pragma once
#include "Obj.h"

class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void SetObjList(list<CObj*>* pObjList);
	void SetGetBarrierItem(); // ������ ������ �԰ԵǸ� �ߵ� �Լ�
	void SetGetPowerItem(); // �Ŀ��������� �԰� �Ǹ� �ߵ� �Լ�
	class CBarrier* GetBarrierClass(); // ������Ŭ���� �����͸� ��ȯ�ϴ� �Լ�

	 INFO* GetPlayerPointer(void) { return &m_tInfo; }

private:
	void		Key_Input(void);
	void		CollisionWindow(); //�÷��̾ ȭ�� ������ �������� �浹ó��
	void		InitBarrier(); // ������ ���� �Լ�
	void		InitAssistantPlane(); //���� ����� ���� �Լ�

private:
	int m_iHP; // ü��
	int m_iPowerUpItemCount; // �Ŀ��� ������ ���� Ƚ��
	bool m_bIsBarrier; // �� ������ ���/�Ұ��� �Ǵ�
	class CBarrier* m_pBarrier; // �踮�� Ŭ����
	class CAssistantPlayer* m_pAssistant[AST_END]; // �����̴Ϻ���� Ŭ����
	list<CObj*>* m_pObjList;




	//bullet Ŭ���� ������ Set_BulletList �Լ� �����
};

