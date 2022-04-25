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
	virtual	void CollisionEnter(CObj* _sour);

public:
	void SetObjList(list<CObj*>* pObjList);
	void SetMonsterList(list<CObj*>* pMonsterList);
	void SetGetBarrierItem(); // ������ ������ �԰ԵǸ� �ߵ� �Լ�
	void SetGetPowerItem(); // �Ŀ��������� �԰� �Ǹ� �ߵ� �Լ�
	class CObj* GetBarrierClass(); // ������Ŭ���� �����͸� ��ȯ�ϴ� �Լ�
	int* GetPowerUpItemCount(); //�Ŀ��� ������ ���� Ƚ�� ��ȯ
	int* GetLife(); //�÷��̾� ��� 
	int* GetBombNum(); // ��ź ���� ��ȯ
	void PlayerHit(); // �÷��̾� �ǰݽ� �ߵ� �Լ�

	INFO* GetPlayerInfo(void) { return &m_tInfo; }

private:
	void		Key_Input(void);
	void		NormalFire(); //�Ϲ� �Ѿ� �߻�
	void		LevelOneFire(); // 1�ܰ� �Ѿ� �߻�
	void		ShotGunFire(); // ���� �Ѿ� �߻�
	void		BombGunFire();
	void		CollisionWindow(); //�÷��̾ ȭ�� ���� �������� �浹ó��
	void		InitBarrier(); // ������ ���� �Լ�
	void		InitAssistantPlane(); //���� ����� ���� �Լ�
	void		PowerUp(); // �Ŀ��� ī��Ʈ ���
	void		AddBomb(); // ��ź �߰�
	bool		DeployBomb(); // ��ź �ߵ�
	void		RunEffect(); //�ǰ� ����Ʈ
	void		EffectRender(); //�ǰ�����Ʈ ����


private:
	int m_iLife; // ���
	int m_iBomb; // ��ź ����
	int m_iPowerUpItemCount; // �Ŀ��� ������ ���� Ƚ��
	bool m_bIsBarrier; // �� ������ ���/�Ұ��� �Ǵ�
	class CBarrier* m_pBarrier; // �踮�� Ŭ����
	class CAssistantPlayer* m_pAssistant[AST_END]; // �����̴Ϻ���� Ŭ����
	list<CObj*>* m_bulletList; // �Ѿ� ����Ʈ
	list<CObj*>* m_MonsterList; // ���� ����Ʈ
	bool m_bIsCollision; //�浹 �ƴ��� �ȵƴ��� Ȯ��
	bool m_bIsRunEffect; //�ǰ� �޾Ҵ��� �ȹ޾Ҵ��� Ȯ��
	int m_iEffectCount; // ����Ʈ ����

};

