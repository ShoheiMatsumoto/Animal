#pragma once

// �C���N���[�h
#include "billboard.h"

// �A�j�܂�̊�{�@�\�N���X
class CAnimaruBase :
	public CBillboard
{
public:
	CAnimaruBase(void);
	CAnimaruBase(int nGroupID, int nTypeID, int nTexID);
	virtual ~CAnimaruBase(void);
};

