#include "AnimalColl.h"
#include "MyCollision.h"

CAnimalColl::CAnimalColl(void)
{
}


CAnimalColl::~CAnimalColl(void)
{
}

// 何かとマップの判定走査
void CAnimalColl::CheckRunToMap(CObjBase* pTop1, CObjBase* pMapTop2)
{
	CObjBase* pObj1, *pObj2;
	pObj1 = pTop1;
	pObj2 = pMapTop2;
	D3DXVECTOR3 vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	while(pObj1)
	{
		while(pObj2)
		{
			if(CollToMapSwitch(pObj1, (CMapPartsBase*)pObj2, &vPos))
			{
				pObj1->HitUpdate(pObj2, vPos);
				pObj2->HitUpdate(pObj1, vPos);
			}

			pObj2 = pObj2->GetNext();
		}
		pObj1 = pObj1->GetNext();		// 次の
		pObj2 = pMapTop2;		// 入れ直し
	}
}

// 何かとマップの判定
bool CAnimalColl::CollToMapSwitch(CObjBase* pObj1, CMapPartsBase* pObj2, D3DXVECTOR3* vPos)
{
	int nType = pObj2->GetPartsType();		// パーツタイプ取得

	switch(nType)
	{
	case MAPPARTS_SQUARE:
		return CollSquare3D(pObj1, pObj2);
		break;

	case MAPPARTS_RUP:
		return CollToMapSlope(pObj1, pObj2, nType, vPos);
		break;

	case MAPPARTS_RDOWN:
		return CollToMapSlope(pObj1, pObj2, nType, vPos);
		break;

	default:
		return false;
		break;
	}

	return false;
}

// マップパーツボックス用
bool CAnimalColl::CollToMapBox(CObjBase* pObj1, CMapPartsBase* pObj2, D3DXVECTOR3* vPos)
{
	D3DXVECTOR3 p1, p2;		// 座標
	D3DXVECTOR3 s1, s2;		// サイズ
	D3DXVECTOR3 r1, r2;		// 半径
	int bp1, bp2;
	float ad1[4];
	float ad2[4];

	p1 = pObj1->GetPos();
	s1 = pObj1->GetSize();
	r1 = pObj1->GetRadius();
	bp1 = pObj1->GetCollType();
	SetAdjSquare3D(ad1, bp1, s1, r1);

	p2 = pObj2->GetPos();
	s2 = pObj2->GetSize();
	r2 = pObj2->GetRadius();
	bp2 = pObj2->GetCollType();
	SetAdjSquare3D(ad2, bp2, s2, r2);

	// X
	if(p1.x + ad1[3] <= p2.x + ad2[3] && p1.x + ad1[1] >= p2.x + ad2[3] ||
		p1.x + ad1[3] <= p2.x + ad2[1] && p1.x + ad1[1] >= p2.x + ad2[1])
	{
		// Y
		if(p1.y + ad1[0] >= p2.y + ad2[0] && p1.y + ad1[2] <= p2.y + ad2[0] ||
		p1.y + ad1[0] >= p2.y + ad2[2] && p1.y + ad1[2] <= p2.y + ad2[2])
		{
			// 交差判定
			return true;
		}
	}
	
	return false;
}


// マップパーツ坂用判定
bool CAnimalColl::CollToMapSlope(CObjBase* pObj1, CMapPartsBase* pObj2, int nType, D3DXVECTOR3* vPos)
{
	D3DXVECTOR3 p2, p2l, p2r;		// 座標
	D3DXVECTOR3 r2;		// 半径
	Segment Seg1, Seg2;		// 交差判定用
	// D3DXVECTOR3 vCross;		// 交差座標取得用
	CMyCollision Mycoll;	// マイコリション（そのうち統合）

	// 何かの
	Seg1.vSPos = pObj1->GetPos();
	Seg1.vVec = D3DXVECTOR3(0.0f, 1000.0f, 0.0f);	// 上方向のベクトル

	// マップの
	p2 = pObj2->GetPos();
	r2 = pObj2->GetRadius();


	if(nType == MAPPARTS_RUP)
	{
		p2l = D3DXVECTOR3(p2.x - r2.x, p2.y - r2.y, p2.z);		// 左下
		p2r = D3DXVECTOR3(p2.x + r2.x, p2.y + r2.y, p2.z);		// 右上
		Seg2.vSPos = p2l;	// 左下を始点に設定
		Seg2.vVec = p2r - p2l;		// 右上の点に向かうベクトル
	}

	if(nType == MAPPARTS_RDOWN)
	{
		p2l = D3DXVECTOR3(p2.x - r2.x, p2.y + r2.y, p2.z);		// 左上
		p2r = D3DXVECTOR3(p2.x + r2.x, p2.y - r2.y, p2.z);		// 右下
		Seg2.vSPos = p2l;	// 左上を始点に設定
		Seg2.vVec = p2r - p2l;		// 右下の点に向かうベクトル
	}

	return Mycoll.CollisionLineToLine2D(Seg1, Seg2, vPos);
	
}




//eof