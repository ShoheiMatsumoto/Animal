#pragma once

#include "Object2D.h"


class CTest2D :
	public CObject2D
{
private:
	
public:
	CTest2D(void);
	CTest2D(int nID, int nTexNum);
	virtual ~CTest2D(void);

	CTest2D*	Create(int nID, int nTexNum, D3DXVECTOR3 vPos);
	bool		Initialize(int nTexNum);

	void		Update();
	void		Release(); 
	//virtual	void		Draw();

	void Hit(CObjBase* pObj){};
};
