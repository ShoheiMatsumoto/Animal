#pragma once
#include "billboard.h"


class CCursor :
	public CBillboard
{
private:

public:
	CCursor(void);
	CCursor(int n);
	virtual ~CCursor(void);

	CCursor* Create(int nTexNum);
	bool		Initialize(int nTexNum);

	void Update();
	void Delete(){m_nObjStatus = OBJST_DELETE;};

	void SetPos(D3DXVECTOR3 vPos){m_vPos = vPos;};
};

