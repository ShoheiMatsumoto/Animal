#include "MyCollision.h"


CMyCollision::CMyCollision(void)
{
}


CMyCollision::~CMyCollision(void)
{
}

// 2D外積
float CMyCollision::D3DXVec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	return v1->x * v2->y - v1->y * v2->x;			
};

// 線分のあたり判定
bool CMyCollision::CollisionLineToLine2D(Segment Seg1, Segment Seg2, D3DXVECTOR3* vCrossPos)
{
	D3DXVECTOR3 v = Seg2.vSPos - Seg1.vSPos;
	
	float fCrs_v1_v2 = D3DXVec2Cross(&Seg1.vVec, &Seg2.vVec);

	if(fCrs_v1_v2 == 0.0f)
	{	// 平行
		return false;
	}

	float fCrs_v_v1 = D3DXVec2Cross(&v, &Seg1.vVec);
	float fCrs_v_v2 = D3DXVec2Cross(&v, &Seg2.vVec);

	float t1 = fCrs_v_v2 / fCrs_v1_v2;
	float t2 = fCrs_v_v1 / fCrs_v1_v2;

	const float eps = 0.00001f;		// 誤差許容値

	float t1p = t1 + eps;
	float t2p = t2 + eps;

	float t1m = t1 - eps;
	float t2m = t2 - eps;

	if(t1p < 0 || t1m > 1 || t2p < 0 || t2m > 1)
	{	// 交差していない
		return false;
	}

	if(vCrossPos)
	{
		*vCrossPos = Seg1.vSPos + Seg1.vVec * t1;
	}

	return true;

}

bool CMyCollision::CollisionLineToLine3D(Segment Seg1, Segment Seg2, D3DXVECTOR3* vCrossPos)
{


	return true;
}





