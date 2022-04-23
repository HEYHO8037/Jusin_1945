#pragma once
#include "Obj.h"
class CBullet : public CObj
{
public:
	CBullet();
	~CBullet();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void SetDirection(float _x, float _y) { m_tDir.fX = _x, m_tDir.fY = _y; };

private:
	INFO m_tDir;
};

