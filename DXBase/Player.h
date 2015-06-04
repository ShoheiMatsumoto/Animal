// �v���C���[�N���X�錾
#pragma once

#include "billboard.h"


//enum
//{
//	PINP_TYPE_PRS,
//	PINP_TYPE_TRG,
//	PINP_TYPE_RLS,
//
//	PINP_TYPE_MAX
//};
//
//enum
//{
//	PINP_BTN_UP,
//	PINP_BTN_DOWN,
//	PINP_BTN_RIGHT,
//	PINP_BTN_LEFT,
//	PINP_BTN_SPACE,
//	PINP_BTN_SHIFT,
//	PINP_BTN_Q,
//	PINP_BTN_W,
//	PINP_BTN_E,
//	PINP_BTN_R,
//	PINP_BTN_Z,
//	PINP_BTN_X,
//
//	PINP_BTN_MAX
//};

class CPlayer :
	public CBillboard
{
protected:
	// bool m_bInput[PINP_TYPE_MAX][PINP_BTN_MAX];
	int		m_nMoveVecType;

public:
	CPlayer(void);
	CPlayer(int n, int nTexNum);
	virtual ~CPlayer(void);

	CPlayer*	Create(int nID, int nTexNum, D3DXVECTOR3 vPos);
	void		Initialize();
	void		Update();
	void		HitUpdate(CObjBase* pObj, D3DXVECTOR3 vPos);
	void		Release();

	// �g��
	void		SetInputData();

	void		BacktoStand();	// ������Ԃɖ߂낤�Ƃ���
	void		Move();			// �ړ�
	void		PushJump();		// �W�����v�͂���
	void		Jump();			// �W�����v�X�V
	void		Fall();			// ����
	void		PushAct();		// �A�N�V�����͂���
	void		Action();		// �A�N�V�����X�V

	void		Control();

	void		CheckEnvir();	// �v���C���[���u����Ă�������`�F�b�N���A�X�e�[�^�X��ύX
	bool		CheckRun();		// �����Ă邩
	bool		CheckJump();	// ����ł邩
	bool		CheckFall();	// �����Ă邩
	
};

