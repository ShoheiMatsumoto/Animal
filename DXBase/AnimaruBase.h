#pragma once

// インクルード
#include "billboard.h"

// アニまるの基本機能クラス
class CAnimaruBase :
	public CBillboard
{
public:
	CAnimaruBase(void);
	CAnimaruBase(int nGroupID, int nTypeID, int nTexID);
	virtual ~CAnimaruBase(void);
};

