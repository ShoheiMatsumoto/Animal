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

// �}�b�v�p�[�c�{�b�N�X�p
bool CAnimalColl::CollToMapBox(CObjBase* pObj1, CMapPartsBase* pObj2, D3DXVECTOR3* vPos)
{
	D3DXVECTOR3 p1, p2;		// ���W
	D3DXVECTOR3 s1, s2;		// �T�C�Y
	D3DXVECTOR3 r1, r2;		// ���a
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
			// ��_�����߂�
			//*vPos = GetMapBoxCrossPos(pObj1, pObj2, &nLine);


			return true;
		}
	}
	
	return false;
}


#define COLL_RATE (0.7f)
// ��������_�擾�p
D3DXVECTOR3 CAnimalColl::GetMapBoxCrossPos(CObjBase* pObj1, CMapPartsBase* pObj2, int* pnLine)
{
	// �ϐ��p��
	D3DXVECTOR3 p1, p2;		// ���W
	D3DXVECTOR3 op1;		// �����W
	D3DXVECTOR3 spd1;		// ���x
	D3DXVECTOR3 r1, r2;		// ���a
	D3DXVECTOR3 s1;			// 
	float ad1[4];
	int bp1;
	Segment Seg1, Seg2;
	CMyCollision Mycoll;
	D3DXVECTOR3 vCross;
	bool bCross = false;
	float adx, ady;

	// obj1�̕ϐ��ڂ��ւ�
	p1 = pObj1->GetPos();
	op1 = pObj1->GetOldPos();
	spd1 = pObj1->GetSpeed();
	s1 = pObj1->GetSize();
	s1.x --;
	r1 = pObj1->GetRadius();
	r1.x -= 0.5f;
	bp1 = pObj1->GetCollType();
	SetAdjSquare3D(ad1, bp1, s1, r1);
	Seg1.vSPos = op1 + spd1;		// �n�_�͈ړ���̌��_�Ƃ���
	//Seg1.vVec = spd1;		// �Ƃ肠�������x������x�N�g���Ƃ���

	// obj2�̕ϐ��ڂ��ւ�
	p2 = pObj2->GetPos();
	r2 = pObj2->GetRadius();

	



	// x��y�v�f�𕪂��Č������
	// �㉺�̐���
	
	{	// ���̏�̐��Ɓi���炭��ԐڐG�������j
		// �n�_�̕␳
		// �ڐG������̕����֕␳
		Seg1.vSPos.y += ad1[2];		
		ady = ad1[2];		// ��Ō�_���猴�_�֒�������

		Seg1.vSPos.x += ad1[1];		// �E

		// y�����̃x�N�g���݂̂ɂ���
		Seg1.vVec.x = 0.0f;
		Seg1.vVec.y = -spd1.y + 1.0f;		// �������

		Seg2.vSPos = D3DXVECTOR3(p2.x - r2.x, p2.y + r2.y, p2.x);		// ����
		Seg2.vVec = D3DXVECTOR3(p2.x + r2.x - Seg2.vSPos.x, p2.y + r2.y - Seg2.vSPos.y, 0.0f);		// �E��
		
		bCross = Mycoll.CollisionLineToLine2D(Seg1, Seg2, &vCross);


		*pnLine = CROSSLINE_T;
		// ���΂̓_�����
		if(!bCross)
		{
			
			Seg1.vSPos.x += -ad1[1] + ad1[3];
			adx = ad1[3];
			bCross = Mycoll.CollisionLineToLine2D(Seg1, Seg2, &vCross);
		}
	}
	
	if(bCross)
	{
		vCross.x = p1.x;		// �������WX
		vCross.y -= ady;		// �������WY
		vCross.z = p1.z;
		return vCross;
	}

	// ���Z�b�g
	Seg1.vSPos = op1 + spd1;		// �n�_�͈ړ���̌��_�Ƃ���
	{	// ���̐�
		// �n�_�̕␳
		Seg1.vSPos.x += ad1[1];

		// �ڐG������̕����֕␳
		Seg1.vSPos.y += ad1[0];
		ady = ad1[0];		// ��Ō�_���猴�_�֒�������

		// y�����̃x�N�g���݂̂ɂ���
		Seg1.vVec.x = 0.0f;
		Seg1.vVec.y = -spd1.y - 1.0f;		// ��������

		Seg2.vSPos = D3DXVECTOR3(p2.x - r2.x, p2.y - r2.y, p2.x);		// ����
		Seg2.vVec = D3DXVECTOR3(p2.x + r2.x - Seg2.vSPos.x, p2.y - r2.y - Seg2.vSPos.y, 0.0f);		// �E��

		bCross = Mycoll.CollisionLineToLine2D(Seg1, Seg2, &vCross);

		*pnLine = CROSSLINE_B;

		// ���΂̓_�����
		if(!bCross)
		{
			adx = ad1[3];
			Seg1.vSPos.x += -ad1[1] * COLL_RATE + ad1[3] * COLL_RATE;
			bCross = Mycoll.CollisionLineToLine2D(Seg1, Seg2, &vCross);
		}
	}
	
	if(bCross)
	{
		vCross.x = p1.x;		// �������WX
		vCross.y -= ady;		// �������WY
		vCross.z = p1.z;
		return vCross;
	}

	// �k�ꂽ��
	// X

	// ���Z�b�g
	Seg1.vSPos = op1 + spd1;		// �n�_�͈ړ���̌��_�Ƃ���
	//Seg1.vVec = spd1;		// �Ƃ肠�������x������x�N�g���Ƃ���

	
	{	// ���̉E�̐���
		// �n�_�̕␳
		Seg1.vSPos.y += ad1[0];

		// �ڐG������̕����֕␳
		Seg1.vSPos.x += ad1[3];
		adx = ad1[3];		// ��Ō�_���猴�_�֒�������

		// x�����̃x�N�g���݂̂ɂ���
		Seg1.vVec.y = 0.0f;
		Seg1.vVec.x = -spd1.x + 1.0f;		// �E������

		Seg2.vSPos = D3DXVECTOR3(p2.x + r2.x, p2.y + r2.y, 0.0f);		// �E��
		Seg2.vVec = D3DXVECTOR3(p2.x + r2.x - Seg2.vSPos.x, p2.y - r2.y - Seg2.vSPos.y, 0.0f);		// �E��
		
		bCross = Mycoll.CollisionLineToLine2D(Seg1, Seg2, &vCross);

		*pnLine = CROSSLINE_R;

		// ���΂̓_�����
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

	// ���Z�b�g
	Seg1.vSPos = op1 + spd1;		// �n�_�͈ړ���̌��_�Ƃ���
	{	// ���̐�
		/// �n�_�̕␳
		Seg1.vSPos.y += ad1[0];

		// �ڐG������̕����֕␳
		Seg1.vSPos.x += ad1[1];
		adx = ad1[1];		// ��Ō�_���猴�_�֒�������

		// x�����̃x�N�g���݂̂ɂ���
		Seg1.vVec.y = 0.0f;
		Seg1.vVec.x = -spd1.x - 1.0f;		// ��������

		Seg2.vSPos = D3DXVECTOR3(p2.x - r2.x, p2.y + r2.y, 0.0f);		// ����
		Seg2.vVec = D3DXVECTOR3(p2.x - r2.x - Seg2.vSPos.x, p2.y - r2.y - Seg2.vSPos.y, 0.0f);		// ����
	
		bCross = Mycoll.CollisionLineToLine2D(Seg1, Seg2, &vCross);

		*pnLine = CROSSLINE_L;

		// ���΂̓_�����
		if(!bCross)
		{
			ady = ad1[2];
			Seg1.vSPos.y += -ad1[0] + ad1[2];
			bCross = Mycoll.CollisionLineToLine2D(Seg1, Seg2, &vCross);
		}
	}
	
	// ����
	vCross.y = p1.y;
	vCross.x -= adx;
	vCross.z = p1.z;
 
	return vCross;

}

// �}�b�v�p�[�c��p����
bool CAnimalColl::CollToMapSlope(CObjBase* pObj1, CMapPartsBase* pObj2, int nType, D3DXVECTOR3* vPos)
{
	D3DXVECTOR3 p2, p2l, p2r;		// ���W
	D3DXVECTOR3 r1, r2;		// ���a
	Segment Seg1, Seg2;		// ��������p
	D3DXVECTOR3 vCrossl, vCrossr;		// �������W�擾�p
	CMyCollision Mycoll;	// �}�C�R���V�����i���̂��������j
	bool bHit = false;

	// ������
	Seg1.vSPos = pObj1->GetPos();
	Seg1.vVec = D3DXVECTOR3(0.0f, 1000.0f, 0.0f);	// ������̃x�N�g��
	r1 = pObj1->GetRadius();

	// �}�b�v��
	p2 = pObj2->GetPos();
	r2 = pObj2->GetRadius();

	// �����_������
	vCrossl = D3DXVECTOR3(0.0f, -9999.0f, Seg1.vSPos.z);
	vCrossr = D3DXVECTOR3(0.0f, -9999.0f, 0.0f);

	if(nType == MAPPARTS_RUP)
	{
		p2l = D3DXVECTOR3(p2.x - r2.x, p2.y - r2.y, p2.z);		// ����
		p2r = D3DXVECTOR3(p2.x + r2.x, p2.y + r2.y, p2.z);		// �E��
		Seg2.vSPos = p2l;	// �������n�_�ɐݒ�
		Seg2.vVec = p2r - p2l;		// �E��̓_�Ɍ������x�N�g��

		Seg1.vSPos.x += r1.x;
		bHit = Mycoll.CollisionLineToLine2D(Seg1, Seg2, vPos);
		vPos->x -= r1.x;		// ���S�ɖ߂�
	}

	if(nType == MAPPARTS_RDOWN)
	{
		p2l = D3DXVECTOR3(p2.x - r2.x, p2.y + r2.y, p2.z);		// ����
		p2r = D3DXVECTOR3(p2.x + r2.x, p2.y - r2.y, p2.z);		// �E��
		Seg2.vSPos = p2l;	// ������n�_�ɐݒ�
		Seg2.vVec = p2r - p2l;		// �E���̓_�Ɍ������x�N�g��

		Seg1.vSPos.x -= r1.x;
		bHit = Mycoll.CollisionLineToLine2D(Seg1, Seg2, vPos);
		vPos->x += r1.x;		// ���S�ɖ߂�
	}
	
	return bHit;
	
}




//eof