#pragma once

#include "define.h"
#include "Mesh.h"

struct Segment
{
	D3DXVECTOR3 vSPos;		// 始点
	D3DXVECTOR3 vVec;		// 方向ベクトル
};

class CMyCollision
{
public:
	CMyCollision(void);
	virtual ~CMyCollision(void);

	float D3DXVec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2);

	bool CollisionLineToLine2D(Segment Seg1, Segment Seg2, D3DXVECTOR3* vCrossPos);
	bool CollisionLineToLine3D(Segment Seg1, Segment Seg2, D3DXVECTOR3* vCrossPos);

};

