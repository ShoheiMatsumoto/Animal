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
	CContSt CSt;	// ��{�X�e�[�^�X
	int		m_nSlotID;		// ���������Ԗڂɓ����Ă邩
	int		m_nAnimaruSt;	// �A�j�}���ŗL�̏��
	int		m_nCoolTime;	// �N�[���^�C��
	
	// �ǐՊ֘A
	bool	m_bChase;
	bool	m_bCBrk;
	int		m_nChaseVec;
#define		CHASE_NONE  0
#define		CHASE_RIGHT 1
#define		CHASE_LEFT  2

	D3DXVECTOR3* m_pvChaseTargetPos;		// �ǐՃ^�[�Q�b�g�iP�L�����j�̍��W
	

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
	void SetMJump();		// �ړ��W�����v�̃Z�b�g
	void MoveJump();		// �ړ����̏��W�����v


	void Control();

	// ��ԃ`�F�b�J�[
	void CheckEnvir();
	bool CheckRun();
	bool CheckJump();
	bool CheckFall();

	void CheckDist();		// �ǐՑΏۂƂ̋����`�F�b�N
	
	// �Z�b�^�[
	void SetSlotID(int nSlotID);
	void SetbChase(bool bChase, int nChaseVec);
	void SetChasePos(D3DXVECTOR3* pvPos){m_pvChaseTargetPos = pvPos;};

	// �����
	void HitUDToMapParts(CObjBase* pObj, int nType, D3DXVECTOR3 vPos);


};

