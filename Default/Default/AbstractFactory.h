#pragma once

#include "Obj.h"
#include "Ui.h"

template<typename T>
class CAbstractFactory
{
public:

	CAbstractFactory(){}

	~CAbstractFactory(){}

public :
	static CObj* Create(void)
	{
		CObj* pObj = new T;
		
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float _fX, float _fY, DIRECTION _eDir = DIR_END)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->Set_pos(_fX, _fY);

		if (DIR_END >= _eDir)
		{
			pObj->Set_Dir(_eDir);
		}

		return pObj;
	}

	static CUi* UICreate(void)
	{
		CUi* pUi = new T;
		pUi->Initialize();

		return pUi;
	}

	static CUi* UICreate(float _fX, float _fY)
	{
		CUi* pUi = new T;
		pUi->Initialize();
		pUi->Set_Pos(_fX, _fY);

		return pUi;
	}
};

