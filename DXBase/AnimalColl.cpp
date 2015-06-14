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
		return CollToMapBox(pObj1, pObj2, vPos);
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
	//int nLine;
	float ad1[4];
	float ad2[4];

	p1 = pObj1->GetPos();
	s1 = pObj1->GetSize();
	r1 = pObj1->GetRadius();
	bp1 = pObj1->GetCollType();
	s1.x --;
	r1.x -= 0.5f;
	SetAdjSquare3D(ad1, bp1, s1, r1);

	p2 = pObj2->GetPos();
	s2 = pObj2->GetSize();
	r2 = pObj2->GetRadius();
	bp2 = pObj2->GetCollType();
	SetAdjSquare3D(ad2, bp2, s2, r2);

	// X
	if(p1.x + ad1[1] >= p2.x + ad2[3] && p1.x + ad1[1] <= p2.x + ad2[1] ||
		p1.x + ad1[3] >= p2.x + ad2[3] && p1.x + ad1[3] <= p2.x + ad2[1])
	{
		// Y
		if(p1.y + ad1[0] >= p2.y + ad2[0] && p1.y + ad1[2] <= p2.y + ad2[0] ||
		p1.y + ad1[0] >= p2.y + ad2[2] && p1.y + ad1[2] <= p2.y + ad2[2])
		{
			// 交点を求める
			//*vPos = GetMapBoxCrossPos(pObj1, pObj2, &nLine);


			return true;
		}
	}
	
	return false;
}


#define COLL_RATE (0.7f)
// 箱判定後交点取得用
D3DXVECTOR3 CAnimalColl::GetMapBoxCrossPos(CObjBase* pObj1, CMapPartsBase* pObj2, int* pnLine)
{
	// 変数用意
	D3DXVECTOR3 p1, p2;		// 座標
	D3DXVECTOR3 op1;		// 旧座標
	D3DXVECTOR3 spd1;		// 速度
	D3DXVECTOR3 r1, r2;		// 半径
	D3DXVECTOR3 s1;			// 
	float ad1[4];
	int bp1;
	Segment Seg1, Seg2;
	CMyCollision Mycoll;
	D3DXVECTOR3 vCross;
	bool bCross = false;
	float adx, ady;

	// obj1の変数移し替え
	p1 = pObj1->GetPos();
	op1 = pObj1->GetOldPos();
	spd1 = pObj1->GetSpeed();
	s1 = pObj1->GetSize();
	s1.x --;
	r1 = pObj1->GetRadius();
	r1.x -= 0.5f;
	bp1 = pObj1->GetCollType();
	SetAdjSquare3D(ad1, bp1, s1, r1);
	Seg1.vSPos = op1 + spd1;		// 始点は移動後の原点とする
	//Seg1.vVec = spd1;		// とりあえず速度を方向ベクトルとする

	// obj2の変数移し替え
	p2 = pObj2->GetPos();
	r2 = pObj2->GetRadius();

	



	// xとy要素を分けて交線判定
	// 上下の線と
	
	{	// 箱の上の線と（恐らく一番接触が多い）
		// 始点の補正
		// 接触する線の方向へ補正
		Seg1.vSPos.y += ad1[2];		
		ady = ad1[2];		// 後で交点から原点へ調整する

		Seg1.vSPos.x += ad1[1];		// 右

		// y方向のベクトルのみにする
		Seg1.vVec.x = 0.0f;
		Seg1.vVec.y = -spd1.y + 1.0f;		// 上方向に

		Seg2.vSPos = D3DXVECTOR3(p2.x - r2.x, p2.y + r2.y, p2.x);		// 左上
		Seg2.vVec = D3DXVECTOR3(p2.x + r2.x - Seg2.vSPos.x, p2.y + r2.y - Seg2.vSPos.y, 0.0f);		// 右上
		
		bCross = Mycoll.CollisionLineToLine2D(Seg1, Seg2, &vCross);


		*pnLine = CROSSLINE_T;
		// 反対の点からも
		if(!bCross)
		{
			
			Seg1.vSPos.x += -ad1[1] + ad1[3];
			adx = ad1[3];
			bCross = Mycoll.CollisionLineToLine2D(Seg1, Seg2, &vCross);
		}
	}
	
	if(bCross)
	{
		vCross.x = p1.x;		// 調整座標X
		vCross.y -= ady;		// 調整座標Y
		vCross.z = p1.z;
		return vCross;
	}

	// リセット
	Seg1.vSPos = op1 + spd1;		// 始点は移動後の原点とする
	{	// 下の線
		// 始点の補正
		Seg1.vSPos.x += ad1[1];

		// 接触する線の方向へ補正
		Seg1.vSPos.y += ad1[0];
		ady = ad1[0];		// 後で交点から原点へ調整する

		// y方向のベクトルのみにする
		Seg1.vVec.x = 0.0f;
		Seg1.vVec.y = -spd1.y - 1.0f;		// 下方向に

		Seg2.vSPos = D3DXVECTOR3(p2.x - r2.x, p2.y - r2.y, p2.x);		// 左下
		Seg2.vVec = D3DXVECTOR3(p2.x + r2.x - Seg2.vSPos.x, p2.y - r2.y - Seg2.vSPos.y, 0.0f);		// 右下

		bCross = Mycoll.CollisionLineToLine2D(Seg1, Seg2, &vCross);

		*pnLine = CROSSLINE_B;

		// 反対の点からも
		if(!bCross)
		{
			adx = ad1[3];
			Seg1.vSPos.x += -ad1[1] * COLL_RATE + ad1[3] * COLL_RATE;
			bCross = Mycoll.CollisionLineToLine2D(Seg1, Seg2, &vCross);
		}
	}
	
	if(bCross)
	{
		vCross.x = p1.x;		// 調整座標X
		vCross.y -= ady;		// 調整座標Y
		vCross.z = p1.z;
		return vCross;
	}

	// 洩れたら
	// X

	// リセット
	Seg1.vSPos = op1 + spd1;		// 始点は移動後の原点とする
	//Seg1.vVec = spd1;		// とりあえず速度を方向ベクトルとする

	
	{	// 箱の右の線と
		// 始点の補正
		Seg1.vSPos.y += ad1[0];

		// 接触する線の方向へ補正
		Seg1.vSPos.x += ad1[3];
		adx = ad1[3];		// 後で交点から原点へ調整する

		// x方向のベクトルのみにする
		Seg1.vVec.y = 0.0f;
		Seg1.vVec.x = -spd1.x + 1.0f;		// 右方向に

		Seg2.vSPos = D3DXVECTOR3(p2.x + r2.x, p2.y + r2.y, 0.0f);		// 右上
		Seg2.vVec = D3DXVECTOR3(p2.x + r2.x - Seg2.vSPos.x, p2.y - r2.y - Seg2.vSPos.y, 0.0f);		// 右下
		
		bCross = Mycoll.CollisionLineToLine2D(Seg1, Seg2, &vCross);

		*pnLine = CROSSLINE_R;

		// 反対の点からも
		if(!bCross)
		{
			ady = ad1[2];
			Seg1.vSPos.y += -ad1[0] + ad1[2];
			bCross = Mycoll.CollisionLineToLine2D(Seg1, Seg2, &vCross);
		}
	}
	
	if(bCross)
	{
		vCross.y = p1.y;
		vCross.x -= adx;
		vCross.z = p1.z;
		return vCross;
	}

	// リセット
	Seg1.vSPos = op1 + spd1;		// 始点は移動後の原点とする
	{	// 左の線
		/// 始点の補正
		Seg1.vSPos.y += ad1[0];

		// 接触する線の方向へ補正
		Seg1.vSPos.x += ad1[1];
		adx = ad1[1];		// 後で交点から原点へ調整する

		// x方向のベクトルのみにする
		Seg1.vVec.y = 0.0f;
		Seg1.vVec.x = -spd1.x - 1.0f;		// 左方向に

		Seg2.vSPos = D3DXVECTOR3(p2.x - r2.x, p2.y + r2.y, 0.0f);		// 左上
		Seg2.vVec = D3DXVECTOR3(p2.x - r2.x - Seg2.vSPos.x, p2.y - r2.y - Seg2.vSPos.y, 0.0f);		// 左下
	
		bCross = Mycoll.CollisionLineToLine2D(Seg1, Seg2, &vCross);

		*pnLine = CROSSLINE_L;

		// 反対の点からも
		if(!bCross)
		{
			ady = ad1[2];
			Seg1.vSPos.y += -ad1[0] + ad1[2];
			bCross = Mycoll.CollisionLineToLine2D(Seg1, Seg2, &vCross);
		}
	}
	
	// 調整
	vCross.y = p1.y;
	vCross.x -= adx;
	vCross.z = p1.z;
 
	return vCross;

}

// マップパーツ坂用判定
bool CAnimalColl::CollToMapSlope(CObjBase* pObj1, CMapPartsBase* pObj2, int nType, D3DXVECTOR3* vPos)
{
	D3DXVECTOR3 p2, p2l, p2r;		// 座標
	D3DXVECTOR3 r1, r2;		// 半径
	Segment Seg1, Seg2;		// 交差判定用
	D3DXVECTOR3 vCrossl, vCrossr;		// 交差座標取得用
	CMyCollision Mycoll;	// マイコリション（そのうち統合）
	bool bHit = false;

	// 何かの
	Seg1.vSPos = pObj1->GetPos();
	Seg1.vVec = D3DXVECTOR3(0.0f, 1000.0f, 0.0f);	// 上方向のベクトル
	r1 = pObj1->GetRadius();

	// マップの
	p2 = pObj2->GetPos();
	r2 = pObj2->GetRadius();

	// 交差点初期化
	vCrossl = D3DXVECTOR3(0.0f, -9999.0f, Seg1.vSPos.z);
	vCrossr = D3DXVECTOR3(0.0f, -9999.0f, 0.0f);

	if(nType == MAPPARTS_RUP)
	{
		p2l = D3DXVECTOR3(p2.x - r2.x, p2.y - r2.y, p2.z);		// 左下
		p2r = D3DXVECTOR3(p2.x + r2.x, p2.y + r2.y, p2.z);		// 右上
		Seg2.vSPos = p2l;	// 左下を始点に設定
		Seg2.vVec = p2r - p2l;		// 右上の点に向かうベクトル

		Seg1.vSPos.x += r1.x;
		bHit = Mycoll.CollisionLineToLine2D(Seg1, Seg2, vPos);
		vPos->x -= r1.x;		// 中心に戻す
	}

	if(nType == MAPPARTS_RDOWN)
	{
		p2l = D3DXVECTOR3(p2.x - r2.x, p2.y + r2.y, p2.z);		// 左上
		p2r = D3DXVECTOR3(p2.x + r2.x, p2.y - r2.y, p2.z);		// 右下
		Seg2.vSPos = p2l;	// 左上を始点に設定
		Seg2.vVec = p2r - p2l;		// 右下の点に向かうベクトル

		Seg1.vSPos.x -= r1.x;
		bHit = Mycoll.CollisionLineToLine2D(Seg1, Seg2, vPos);
		vPos->x += r1.x;		// 中心に戻す
	}
	
	return bHit;
	
}




//eof