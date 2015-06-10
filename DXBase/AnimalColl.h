// �u�A�j�܂�v���̃Q�[�����L�̔���N���X
#pragma once

// �C���N���[�h
#include "collision.h"
#include "MapPartsBase.h"

enum
{
	CROSSLINE_T,
	CROSSLINE_B,
	CROSSLINE_R,
	CROSSLINE_L,
};

// �A�j�܂�Փ˔���N���X
class CAnimalColl :
	public Collision
{
public:
	CAnimalColl(void);
	virtual ~CAnimalColl(void);

	void CheckRunToMap(CObjBase* pTop1, CObjBase* pMapTop2);		// �����ƃ}�b�v�̔��葖��

	bool CollToMapSwitch(CObjBase* pObj1, CMapPartsBase* pObj2, D3DXVECTOR3* vPos);			// �����ƃ}�b�v�̔���
	bool CollToMapBox(CObjBase* pObj1, CMapPartsBase* pObj2, D3DXVECTOR3* vPos);		// ���p����
	D3DXVECTOR3 GetMapBoxCrossPos(CObjBase* pObj1, CMapPartsBase* pObj2, int* pnLine);
	bool CollToMapSlope(CObjBase* pObj1, CMapPartsBase* pObj2, int nType, D3DXVECTOR3* vPos);		// ��p����
};

