#include "Collision.h"
#include "ObjBase.h"

Collision::Collision(void)
{
}


Collision::~Collision(void)
{
}

// 3D�I�u�W�F�N�g���l�p����
bool Collision::CollSquare3D(CObjBase* pObj1, CObjBase* pObj2)
{
	D3DXVECTOR3 p1, p2;		// ���W
	D3DXVECTOR3 s1, s2;		// �T�C�Y
	D3DXVECTOR3 r1, r2;		// ���a
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
			return true;
		}
	}
	
	return false;
}



// ����
void Collision::CollSquareRunBill(CObjBase* pTop1, CObjBase* pTop2)
{
	CObjBase* pObj1, *pObj2;
	pObj1 = pTop1;
	pObj2 = pTop2;
	D3DXVECTOR3 vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	while(pObj1)
	{
		while(pObj2)
		{
			if(CollSquare3D(pObj1, pObj2))
			{
				pObj1->HitUpdate(pObj2, vPos);
				pObj2->HitUpdate(pObj1, vPos);
			}

			pObj2 = pObj2->GetNext();
		}
		pObj1 = pObj1->GetNext();		// ����
		pObj2 = pTop2;		// ���꒼��
	}
}

bool Collision::IntersectOBB(D3DXMATRIX& world1, OBB& obb1, D3DXMATRIX& world2, OBB& obb2)
{
	// ���[�J�����W���̒��o
	D3DXVECTOR3 vN[6];
	vN[0] = D3DXVECTOR3(world1._11, world1._12, world1._13);
	vN[1] = D3DXVECTOR3(world1._21, world1._22, world1._23);
	vN[2] = D3DXVECTOR3(world1._31, world1._32, world1._33);

	vN[3] = D3DXVECTOR3(world2._11, world1._12, world1._13);
	vN[4] = D3DXVECTOR3(world2._21, world1._22, world1._23);
	vN[5] = D3DXVECTOR3(world2._31, world1._32, world1._33);

	// ���W���ɒ����𔽉f
	D3DXVECTOR3 vH[6];
	vH[0] = vN[0] * obb1.vHalf.x;
	vH[1] = vN[1] * obb1.vHalf.y;
	vH[2] = vN[2] * obb1.vHalf.z;
	vH[3] = vN[3] * obb2.vHalf.x;
	vH[4] = vN[4] * obb2.vHalf.y;
	vH[5] = vN[5] * obb2.vHalf.z;

	// ���S���W�Ԃ̃x�N�g��
	D3DXVECTOR3 vC1, vC2;
	D3DXVec3TransformCoord(&vC1, &obb1.vCenter, &world1);
	D3DXVec3TransformCoord(&vC2, &obb2.vCenter, &world2);
	D3DXVECTOR3 vD = vC2 - vC1;

	// ���ꂼ��̃��[�J�����W���̊e�������������
	float fD, fH;
	for(int i = 0; i < 6; i ++)
	{
		D3DXVECTOR3* pvSep = &vN[i];		// ���������
		
		// fD��OBB���S�Ԃ̋����̓��e
		fD = fabs(D3DXVec3Dot(&vD, pvSep));

		// OBB1,OBB2(�̔���)�̕������ւ̓��e
		fH = 0.0f;
		for(int j = 0; j < 6; j ++)
		{
			fH += fabs(D3DXVec3Dot(&vH[j], pvSep));
		}

		if(fD > fH)
		{
			return false;
		}
	}

	// ���W���̑g�ݍ��킹�����������
	D3DXVECTOR3 vSep;
	for(int i = 0; i < 3; i ++)
	{
		for(int j = 3; j < 6; j++)
		{
			D3DXVec3Cross(&vSep, &vN[i], &vN[j]);
			D3DXVec3Normalize(&vSep, &vSep);		// ���������
			// fD��OBB���S�Ԃ̋����̓��e
			fD = fabs(D3DXVec3Dot(&vD, &vSep));
			// OBB1,OBB2(�̔���)�̕������ւ̓��e
			fH = 0.0f;
			for(int k = 0; k < 6; k ++)
			{
				fH += fabs(D3DXVec3Dot(&vH[k], &vSep));
			}

			if(fD > fH)
			{
				return false;
			}
		}
	}

	return true;
}

// �r���{�[�h�p
void Collision::SetAdjSquare3D(float* fAd , int nType, D3DXVECTOR3 s, D3DXVECTOR3 r)
{
	switch(nType)
	{
	// ���S�
	case COLLBASEPOINT_CENTER:
		fAd[0] = r.y;		// ��������玞�v���
		fAd[1] = r.x;
		fAd[2] = -r.y;
		fAd[3] = -r.x;
		break;

	// ����
	case COLLBASEPOINT_TOPLEFT:
		fAd[0] = 0.0f;		// ��������玞�v���
		fAd[1] = s.x;
		fAd[2] = -s.y;
		fAd[3] = 0.0f;
		break;

	// ���
	case COLLBASEPOINT_BOTTOM:
		fAd[0] = s.y;		// ��������玞�v���
		fAd[1] = r.x;
		fAd[2] = 0.0f;
		fAd[3] = -r.x;
		break;

	default:

		break;
	}
}

// eof