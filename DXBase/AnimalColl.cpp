#include "AnimalColl.h"
#include "MyCollision.h"

CAnimalColl::CAnimalColl(void)
{
}


CAnimalColl::~CAnimalColl(void)
{
}

// �����ƃ}�b�v�̔��葖��
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
		pObj1 = pObj1->GetNext();		// ����
		pObj2 = pMapTop2;		// ���꒼��
	}
}

// �����ƃ}�b�v�̔���
bool CAnimalColl::CollToMapSwitch(CObjBase* pObj1, CMapPartsBase* pObj2, D3DXVECTOR3* vPos)
{
	int nType = pObj2->GetPartsType();		// �p�[�c�^�C�v�擾

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

// �}�b�v�p�[�c�{�b�N�X�p
bool CAnimalColl::CollToMapBox(CObjBase* pObj1, CMapPartsBase* pObj2, D3DXVECTOR3* vPos)
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
			// ��������
			return true;
		}
	}
	
	return false;
}


// �}�b�v�p�[�c��p����
bool CAnimalColl::CollToMapSlope(CObjBase* pObj1, CMapPartsBase* pObj2, int nType, D3DXVECTOR3* vPos)
{
	D3DXVECTOR3 p2, p2l, p2r;		// ���W
	D3DXVECTOR3 r2;		// ���a
	Segment Seg1, Seg2;		// ��������p
	// D3DXVECTOR3 vCross;		// �������W�擾�p
	CMyCollision Mycoll;	// �}�C�R���V�����i���̂��������j

	// ������
	Seg1.vSPos = pObj1->GetPos();
	Seg1.vVec = D3DXVECTOR3(0.0f, 1000.0f, 0.0f);	// ������̃x�N�g��

	// �}�b�v��
	p2 = pObj2->GetPos();
	r2 = pObj2->GetRadius();


	if(nType == MAPPARTS_RUP)
	{
		p2l = D3DXVECTOR3(p2.x - r2.x, p2.y - r2.y, p2.z);		// ����
		p2r = D3DXVECTOR3(p2.x + r2.x, p2.y + r2.y, p2.z);		// �E��
		Seg2.vSPos = p2l;	// �������n�_�ɐݒ�
		Seg2.vVec = p2r - p2l;		// �E��̓_�Ɍ������x�N�g��
	}

	if(nType == MAPPARTS_RDOWN)
	{
		p2l = D3DXVECTOR3(p2.x - r2.x, p2.y + r2.y, p2.z);		// ����
		p2r = D3DXVECTOR3(p2.x + r2.x, p2.y - r2.y, p2.z);		// �E��
		Seg2.vSPos = p2l;	// ������n�_�ɐݒ�
		Seg2.vVec = p2r - p2l;		// �E���̓_�Ɍ������x�N�g��
	}

	return Mycoll.CollisionLineToLine2D(Seg1, Seg2, vPos);
	
}




//eof