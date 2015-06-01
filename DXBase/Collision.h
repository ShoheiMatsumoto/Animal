#pragma once
#include "define.h"

#include "ObjBase.h"

struct OBB
{
	D3DXVECTOR3 vCenter;		// 中心座標
	D3DXVECTOR3 vHalf;			// 半分のサイズ
};

class Collision
{
public:
	Collision(void);
	~Collision(void);

	void CollSquareRunBill(CObjBase* pTop1, CObjBase* pTop2);
	//void CollSquareBBill(CObjBase* pTop1, CObjBase* pTop2);		// 下基準
	//void CollSquareCBill(CObjBase* pTop1, CObjBase* pTop2);		// 中心基準

	void CollCircleLTBill(CObjBase* pTop1, CObjBase* pTop2);	// 左上基準
	//void CollCircleB(CObjBase* pTop1, CObjBase* pTop2);		// 下基準
	//void CollCircleC(CObjBase* pTop1, CObjBase* pTop2);		// 中心基準
	
	bool CollSquare3D(CObjBase* pObj1, CObjBase* pObj2);
	// void CollCircle(CObjBase* pTop1, CObjBase* pTop2);

	bool IntersectOBB(D3DXMATRIX& world1, OBB& obb1, D3DXMATRIX& world2, OBB& obb2);

	void SetAdjSquare2D(float* fAd , int nType, D3DXVECTOR3 s, D3DXVECTOR3 r);
	void SetAdjSquare3D(float* fAd , int nType, D3DXVECTOR3 s, D3DXVECTOR3 r);

};

