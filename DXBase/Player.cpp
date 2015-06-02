#include "Player.h"
#include "Input.h"


// �萔��`
// �ړ��n
#define PLAYER_ADDMSPD (0.05f)
#define PLAYER_MOVESPDMAX (4.0f)
#define PLAYER_BREAKERATE (1.5f)
#define PLAYER_BREAKISPD (0.1f)

// �W�����v�֘A
#define PLAYER_JMPPOW (10.0f)
#define PLAYER_ADDJSPD ()
#define PLAYER_ADDFSPD ()


#define PLAYER_JUMPPOW (10.0f)

enum
{
	PLAYER_MOVEVEC_TYPE_RIGHT,
	PLAYER_MOVEVEC_TYPE_LEFT,

	
};

// �v���C���[��ԗ�
enum
{
	PLST_STAND = 0,		// ����
	PLST_WALK,			// ����
	PLST_RUN,			// ����
	PLST_ACTION,		// �A�N�V����
	PLST_JUMPUP,			// �W�����v
	PLST_FALL,			// ����

	PLST_ALL
};

CPlayer::CPlayer(void)
{
}

CPlayer::CPlayer(int n, int nTexID) : CBillboard(n, nTexID)
{

}

CPlayer::~CPlayer(void)
{
}

// ����
CPlayer*	CPlayer::Create(int nID, int nTexNum, D3DXVECTOR3 vPos)
{
	CPlayer* p = new CPlayer(nID, nTexNum);

	p->Initialize();

	return p;
}

// ������
void		CPlayer::Initialize()
{
	m_nObjGroupID = OBJ3DGROUP_PLAYER;		// �O���[�v�ݒ�
	//m_nDType = OT_2D;
	
	// 2D�X�e�[�^�X�Z�b�g
	m_Board.ReSize(D3DXVECTOR2(32.0f, 64.0f));		
	m_nCollBasePoint = COLLBASEPOINT_BOTTOM;		// �����蔻���_
	SetSize(D3DXVECTOR3(m_Board.GetSize().x, m_Board.GetSize().y, 0.0f));
	SetPosToMatrix();

	// �r���{�[�h������
	InitializeBillboard();		// �r���{�[�h��������
	SetLocalWkB();				// ����W������

	// �r���{�[�h�����I�t
	m_bBillBoard = false;

	// �J�����O�I�t
	SetbCull(true);

	m_bAlphaBlend = false;

	m_nObjStatus = PLST_STAND;

	// �v���C���[�ŗL�X�e�[�^�X
	m_nMoveVecType = PLAYER_MOVEVEC_TYPE_RIGHT;		// �E����
}

// �X�V
void		CPlayer::Update()
{
	Control();

	m_vPos += m_vSpd;		// ���W�ւ̑��

	UpdateBillBoard();		// �r���{�[�h�X�V
}

// ����㏈��
void		CPlayer::HitUpdate(CObjBase* pObj)
{

}

// ���
void		CPlayer::Release()
{

	delete this;
}


// ����
void		CPlayer::BacktoStand()
{
	if(m_vSpd.x > 0.0f)
	{
		m_vSpd.x -= PLAYER_ADDMSPD;
		if(m_vSpd.x <= 0.0f)
			m_vSpd.x = 0.0f;
	}

	if(m_vSpd.x < 0.0f)
	{
		m_vSpd.x += PLAYER_ADDMSPD;
		if(m_vSpd.x >= 0.0f)
			m_vSpd.x = 0.0f;
	}

}

// �ړ�
void		CPlayer::Move()
{
	// �E
	if(GETINPUT->GetKey(KEY_PRS, DIK_RIGHT))
	{
		if(m_vSpd.x < -PLAYER_MOVESPDMAX / PLAYER_BREAKERATE)
			m_vSpd.x = -PLAYER_MOVESPDMAX / PLAYER_BREAKERATE;
		
		if(m_vSpd.x <= PLAYER_MOVESPDMAX)
		{
			m_vSpd.x += PLAYER_ADDMSPD;		// ����
		}
		else
		{
			m_vSpd.x = PLAYER_MOVESPDMAX;	// �ő呬�x
		}
	}

	// ��
	if(GETINPUT->GetKey(KEY_PRS, DIK_LEFT))
	{
		if(m_vSpd.x > PLAYER_MOVESPDMAX / PLAYER_BREAKERATE)
			m_vSpd.x = PLAYER_MOVESPDMAX / PLAYER_BREAKERATE;

		if(m_vSpd.x >= -PLAYER_MOVESPDMAX)
		{
			m_vSpd.x -= PLAYER_ADDMSPD;		// ����
		}
		else
		{
			m_vSpd.x = -PLAYER_MOVESPDMAX;	// �ő呬�x
		}
	}

	
}

// �W�����v���n��
void		CPlayer::PushJump()
{
	m_nObjStatus = PLST_JUMPUP;		// �X�e�[�^�X�Z�b�g


}


// �W�����v
void		CPlayer::Jump()
{

}
	
// ����
void		CPlayer::Fall()
{
	// m_vSpd.y -= 
}

// �A�N�V�����J�n
void		CPlayer::PushAct()
{

}

// �A�N�V�����R�}���h
void		CPlayer::Action()
{

}

// ����
void		CPlayer::Control()
{
	// ���`�F�b�N�X�e�[�^�X�X�V
	CheckEnvir();

	switch(m_nObjStatus)
	{
	case PLST_STAND:
		BacktoStand();
		Move();			// �ړ�
		PushJump();		// �W�����v�͂���
		PushAct();		// �A�N�V�����͂���
		break;

	case PLST_RUN:
		Move();
		PushJump();
		PushAct();
		break;

	case PLST_ACTION:
		Action();
		break;

	case PLST_JUMPUP:
		Move();
		Jump();
		PushAct();
		break;

	case PLST_FALL:

		break;
	default:

		break;
	}

	
}

// �v���C���[���u����Ă�������`�F�b�N���A�X�e�[�^�X��ύX
void			CPlayer::CheckEnvir()
{
	m_nObjStatus = PLST_STAND;		// 

	if(CheckRun())
		m_nObjStatus = PLST_RUN;

	if(CheckJump())
		m_nObjStatus = PLST_JUMPUP;

	if(CheckFall())
		m_nObjStatus = PLST_FALL;

	


}

// �����Ă邩
bool		CPlayer::CheckRun()
{
	// �㉺�����̃X�s�[�h���o�Ă�
	if(m_vSpd.y > 0.0f || m_vSpd.y < 0.0f)
		return false;		// �W�����v���܂��͗������ł���

	// ���E�̓��͂�����
	if((GETINPUT->GetKey(KEY_PRS, DIK_RIGHT)) || (GETINPUT->GetKey(KEY_PRS, DIK_LEFT)))
		return true;

	return false;		// �~�܂��Ă�
}

// ����ł邩
bool		CPlayer::CheckJump()
{
	// ������̃X�s�[�h���o�Ă�
	if(m_vSpd.y > 0.0f)
		return true;

	return false;
}

// �����Ă邩
bool		CPlayer::CheckFall()
{
	// �������̃X�s�[�h���o�Ă�
	if(m_vSpd.y < 0.0f)
		return true;

	return false;
}

// ���̓f�[�^
//void		CPlayer::SetInputData()
//{
//	// �v���X----------------------------------------------------------
//	// ��
//	if(GETINPUT->GetKey(KEY_PRS, DIK_UP))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_UP] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_UP] = false;
//	
//	// ��
//	if(GETINPUT->GetKey(KEY_PRS, DIK_DOWN))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_DOWN] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_DOWN] = false;
//
//	// ��
//	if(GETINPUT->GetKey(KEY_PRS, DIK_LEFT))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_LEFT] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_LEFT] = false;
//
//	// ��
//	if(GETINPUT->GetKey(KEY_PRS, DIK_RIGHT))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_RIGHT] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_RIGHT] = false;
//
//	// SPACE
//	if(GETINPUT->GetKey(KEY_PRS, DIK_SPACE))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_SPACE] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_SPACE] = false;
//
//	// SHIFT
//	if(GETINPUT->GetKey(KEY_PRS, DIK_LSHIFT))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_SHIFT] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_SHIFT] = false;
//
//	// Q
//	if(GETINPUT->GetKey(KEY_PRS, DIK_Q))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_Q] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_Q] = false;
//
//	// W
//	if(GETINPUT->GetKey(KEY_PRS, DIK_W))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_W] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_W] = false;
//
//	// E
//	if(GETINPUT->GetKey(KEY_PRS, DIK_E))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_E] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_E] = false;
//
//	// R
//	if(GETINPUT->GetKey(KEY_PRS, DIK_R))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_R] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_R] = false;
//
//	// Z
//	if(GETINPUT->GetKey(KEY_PRS, DIK_Z))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_Z] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_Z] = false;
//
//	// X
//	if(GETINPUT->GetKey(KEY_PRS, DIK_X))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_X] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_X] = false;
//	// �g���K�[---------------------------------------------------------------
//	// ��
//	if(GETINPUT->GetKey(KEY_TRG, DIK_))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_LEFT] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_LEFT] = false;
//
//
//	// �����[�X----------------------------------------------------------
//}

// eof
