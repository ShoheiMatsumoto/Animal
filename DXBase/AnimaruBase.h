#pragma once

// �C���N���[�h
#include "billboard.h"

// �A�j�}��No
enum
{
	ANIMARU_NO_NEZU = 0,
	ANIMARU_NO_USHI,
	ANIMARU_NO_TORA,
	ANIMARU_NO_MIMI,
	ANIMARU_NO_TATSU,
	ANIMARU_NO_HEBI,
	ANIMARU_NO_UMA,
	ANIMARU_NO_MOKO,
	ANIMARU_NO_SARU,
	ANIMARU_NO_TORI,
	ANIMARU_NO_INU,
	ANIMARU_NO_URI,

	ANIMARU_NO_MAX
};

// �A�j�܂�̊�{�@�\�N���X
class CAnimaruBase :
	public CBillboard
{
protected:
	CContSt CSt;	

public:
	CAnimaruBase(void);
	CAnimaruBase(int nGroupID, int nTypeID, int nTexID, D3DXVECTOR3 vPos);
	virtual ~CAnimaruBase(void);

	virtual CAnimaruBase* Create(int nGroupID, int nTypeID, int nTexID, D3DXVECTOR3 vPos);
	void Initialize();
	void Update();
	//void Draw();
	void Release();
	void HitUpdate(CObjBase* pObj, D3DXVECTOR3 vPos);

	void BacktoStand();		// ������Ԃɖ߂낤�Ƃ���
	void Move();			// �ړ�
	void SetJump();			// �W�����v�̃Z�b�g
	void Jump();			// �W�����v
	void Fall();			// ����
	void SetAct();			// �A�N�V�����Z�b�g
	void Action();			// �A�N�V����

	void Control();

	void CheckEnvir();
	bool CheckRun();
	bool CheckJump();
	bool CheckFall();

	void HitUDToMapParts(CObjBase* pObj, int nType, D3DXVECTOR3 vPos);
};

