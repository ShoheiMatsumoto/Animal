#pragma once

#include "Billboard.h"

class CTestBill :
	public CBillboard
{
private:

public:
	CTestBill(void);
	CTestBill(int n, int nTexNum);
	virtual ~CTestBill(void);

	CTestBill*	Create(int nID, int nTexNum, D3DXVECTOR3 vPos);
	bool		Initialize(int nTexNum);

	virtual void		Update();
	//virtual	void		Draw();

	void Hit(CObject3D* pObj){};

};

