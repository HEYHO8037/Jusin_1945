#pragma once

#include "Obj.h"

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
};

