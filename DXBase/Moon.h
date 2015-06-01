#pragma once
#include "billboard.h"
class CMoon :
	public CBillboard
{
public:
	CMoon(void);
	CMoon(int n, int nTexNum);
	virtual ~CMoon(void);

	CMoon*	Create(int nID, int nTexNum, D3DXVECTOR3 vPos);
	void		Initialize();

	virtual void		Update();
	//virtual	void		Draw();

	void Hit(CObject3D* pObj){};
};

