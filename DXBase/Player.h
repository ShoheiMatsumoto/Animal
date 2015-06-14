// �v���C���[�N���X�錾
#pragma once

#include "billboard.h"
#include "AnimaruBase.h"

//enum
//{
//	PINP_TYPE_PRS,
//	PINP_TYPE_TRG,
//	PINP_TYPE_RLS,
//
//	PINP_TYPE_MAX
//};
//


class CPlayer :
	public CBillboard
{
protected:
	
	CContSt CSt;

	// �A�j�}���֘A
	CAnimaruBase* m_pAnimaruBox[12];		// �ۑ��ꏊ
	CAnimaruBase* m_pAnimaruSlot[3];		// �X���b�g
	D3DXVECTOR3		m_vPrePos;			// �Ǐ]�p���W

public:
	CPlayer(void);
	CPlayer(int n, int nTexNum);
	virtual ~CPlayer(void);

	CPlayer*	Create(int nID, int nTexNum, D3DXVECTOR3 vPos);
	void		Initialize();
	void		Update();
	void		Draw();
	void		HitUpdate(CObjBase* pObj, D3DXVECTOR3 vPos);
	void		Release();

	// �g��

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
	
	// ����㏈��������
	void HitUDToMapParts(CObjBase* pObj, int nType, D3DXVECTOR3 vPos);

	// �A�j�܂�֘A
	void SetAnimaru();			// �A�j�}�������Z�b�g
	void AnimaruCont();		// �A�j�}���֘A�̍X�V�܂Ƃ�
	void CheckAniDist();		// ��������
	void PreservPos();			// ���W�ۑ�
	void ChangeAnimaru();
};

