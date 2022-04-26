#pragma once
#include "Obj.h"
class CEffect : public CObj
{
public:
	CEffect();
	~CEffect();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual	void CollisionEnter(CObj* _sour);

	void SetEndSize(const float _x, const float _y) { m_effectEndSize.fX = _x * 1.5f; m_effectEndSize.fY = _y * 1.5f; };

private:
	INFO m_effectEndSize;
};

