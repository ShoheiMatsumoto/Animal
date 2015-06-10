// 「アニまる」このゲーム特有の判定クラス
#pragma once

// インクルード
#include "collision.h"
#include "MapPartsBase.h"

enum
{
	CROSSLINE_T,
	CROSSLINE_B,
	CROSSLINE_R,
	CROSSLINE_L,
};

// アニまる衝突判定クラス
class CAnimalColl :
	public Collision
{
public:
	CAnimalColl(void);
	virtual ~CAnimalColl(void);

	void CheckRunToMap(CObjBase* pTop1, CObjBase* pMapTop2);		// 何かとマップの判定走査

	bool CollToMapSwitch(CObjBase* pObj1, CMapPartsBase* pObj2, D3DXVECTOR3* vPos);			// 何かとマップの判定
	bool CollToMapBox(CObjBase* pObj1, CMapPartsBase* pObj2, D3DXVECTOR3* vPos);		// 箱用判定
	D3DXVECTOR3 GetMapBoxCrossPos(CObjBase* pObj1, CMapPartsBase* pObj2, int* pnLine);
	bool CollToMapSlope(CObjBase* pObj1, CMapPartsBase* pObj2, int nType, D3DXVECTOR3* vPos);		// 坂用判定
};

