#pragma once
#include "define.h"

#include "ObjBase.h"

struct OBB
{
	D3DXVECTOR3 vCenter;		// ���S���W
	D3DXVECTOR3 vHalf;			// �����̃T�C�Y
};

class Collision
{
public:
	Collision(void);
	~Collision(void);

	void CollSquareRunBill(CObjBase* pTop1, CObjBase* pTop2);
	//void CollSquareBBill(CObjBase* pTop1, CObjBase* pTop2);		// ���
	//void CollSquareCBill(CObjBase* pTop1, CObjBase* pTop2);		// ���S�

	void CollCircleLTBill(CObjBase* pTop1, CObjBase* pTop2);	// ����
	//void CollCircleB(CObjBase* pTop1, CObjBase* pTop2);		// ���
	//void CollCircleC(CObjBase* pTop1, CObjBase* pTop2);		// ���S�
	
	bool CollSquare3D(CObjBase* pObj1, CObjBase* pObj2);
	
	// void CollCircle(CObjBase* pTop1, CObjBase* pTop2);

	bool IntersectOBB(D3DXMATRIX& world1, OBB& obb1, D3DXMATRIX& world2, OBB& obb2);

	void SetAdjSquare2D(float* fAd , int nType, D3DXVECTOR3 s, D3DXVECTOR3 r);
	void SetAdjSquare3D(float* fAd , int nType, D3DXVECTOR3 s, D3DXVECTOR3 r);

};

