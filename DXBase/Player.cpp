#include "Player.h"
#include "Input.h"
#include "MapPartsBase.h"
#include "AnimalColl.h"
#include "SceneBase.h"


// �萔��`
// �ړ��n
#define PLAYER_ADDMSPD (0.1f)
#define PLAYER_MOVESPDMAX (4.0f)
#define PLAYER_BREAKERATE (1.5f)
#define PLAYER_BRKSPD (0.1f)

// �W�����v�֘A

#define PLAYER_ADDJSPD ()
#define PLAYER_FFIRSTSPD (0.5f)
#define PLAYER_ADDFSPD (0.4f / 60.0f)
#define PLAYER_FSPDMAX (10.0f)
#define PLAYER_JUMPPOW (10.0f)
#define PLAYER_JUMPBRK (0.3f)
float g_fJumpMax = PLAYER_JUMPPOW;
float g_fJumpBrk = PLAYER_JUMPBRK;
float g_fAddfSpd = PLAYER_ADDFSPD;
float g_ffSpdMax = PLAYER_FSPDMAX;
float g_fFirSpd = PLAYER_FFIRSTSPD;
//float g_fSpdMax = 5.0f;



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
	m_vSpd.y = -1.0f;
	
	// �v���C���[�ŗL�X�e�[�^�X
	m_nMoveVecType = PLAYER_MOVEVEC_TYPE_RIGHT;		// �E����
	m_fFallSpd = PLAYER_ADDFSPD;
	m_fJumpPow = 0.0f;
	m_fMovePow = 0.0f;
	m_bJump = false;
}

// �X�V
void		CPlayer::Update()
{
	if(GETINPUT->GetKey(KEY_TRG, DIK_1))
		m_vPos = D3DXVECTOR3(0.0f, 280.0f, 0.0f);
		
	if(GETINPUT->GetKey(KEY_TRG, DIK_O))
		g_fJumpMax += 0.1f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_L))
		g_fJumpMax -= 0.1f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_I))
		g_fJumpBrk += 0.01f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_K))
		g_fJumpBrk -= 0.01f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_U))
		g_ffSpdMax += 0.1f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_J))
		g_ffSpdMax -= 0.1f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_Y))
		g_fFirSpd += 0.1f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_H))
		g_fFirSpd -= 0.1f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_T))
		g_fAddfSpd += 0.1f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_G))
		g_fAddfSpd -= 0.1f;

	Control();

	
	m_vPos += m_vSpd;		// ���W�ւ̑��

	

	UpdateBillBoard();		// �r���{�[�h�X�V
}

void		CPlayer::Draw()
{
	

	//// ���[���h�}�g���b�N�X���Z�b�g
	if (m_world) 
		CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &m_world);


	// �`��
	CGraphics::GetDevice()->SetFVF(FVF_DVERTEX);

	CGraphics::GetDevice()->SetTexture(0, m_Board.m_pImage->GetTexture());						// �e�N�X�`����o�^
	CGraphics::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_verWk, sizeof(DVERTEX));// �|���S���`��


	TCHAR		m_szDebug[4096];
	
	TCHAR	str[256];
	
	// �e��f�o�b�O�p���l�\��
	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���
	_stprintf(str, _T("OL �W�����v�}�b�N�X:%f"), g_fJumpMax);
	lstrcat(m_szDebug, str);
	CSceneBase::GetThis()->GetGraph()->DrawText(10, 40, m_szDebug);

	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���
	_stprintf(str, _T("IK �W�����v�u���[�L:%f"), g_fJumpBrk);
	lstrcat(m_szDebug, str);
	CSceneBase::GetThis()->GetGraph()->DrawText(10, 60, m_szDebug);
	
	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���
	_stprintf(str, _T("UJ �����}�b�N�X:%f"), g_ffSpdMax);
	lstrcat(m_szDebug, str);
	CSceneBase::GetThis()->GetGraph()->DrawText(10, 80, m_szDebug);

	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���
	_stprintf(str, _T("TG �������Z:%f"), g_fAddfSpd);
	lstrcat(m_szDebug, str);
	CSceneBase::GetThis()->GetGraph()->DrawText(10, 100, m_szDebug);

	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���
	_stprintf(str, _T("YH ��������:%f"), g_fFirSpd);
	lstrcat(m_szDebug, str);
	CSceneBase::GetThis()->GetGraph()->DrawText(10, 120, m_szDebug);

	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���
	_stprintf(str, _T("YH �������x:%f"), m_fFallSpd);
	lstrcat(m_szDebug, str);
	CSceneBase::GetThis()->GetGraph()->DrawText(10, 140, m_szDebug);
	
}


// ���
void		CPlayer::Release()
{

	delete this;
}


// ����
void		CPlayer::BacktoStand()
{
	if(m_fMovePow > 0.0f)
	{
		m_fMovePow -= PLAYER_BRKSPD;
		if(m_fMovePow <= 0.0f)
			m_fMovePow = 0.0f;
	}

	if(m_fMovePow < 0.0f)
	{
		m_fMovePow += PLAYER_BRKSPD;
		if(m_fMovePow >= 0.0f)
			m_fMovePow = 0.0f;
	}
	m_vSpd.x = m_fMovePow;
}

// �ړ�
void		CPlayer::Move()
{
	// �E
	if(GETINPUT->GetKey(KEY_PRS, DIK_RIGHT))
	{
		//if(GETINPUT->GetKey(KEY_TRG, DIK_RIGHT))
			//ReverseLR(TEX_LRREV);

		if(m_fMovePow < -PLAYER_MOVESPDMAX / PLAYER_BREAKERATE)
			m_fMovePow = -PLAYER_MOVESPDMAX / PLAYER_BREAKERATE;
		

		if(m_fMovePow <= PLAYER_MOVESPDMAX)
		{
			m_fMovePow += PLAYER_ADDMSPD;		// ����
			
		}
		else
		{
			m_fMovePow = PLAYER_MOVESPDMAX;	// �ő呬�x
			
		}
	}

	// ��
	if(GETINPUT->GetKey(KEY_PRS, DIK_LEFT))
	{
		//if(GETINPUT->GetKey(KEY_TRG, DIK_LEFT))
			

		if(m_fMovePow > PLAYER_MOVESPDMAX / PLAYER_BREAKERATE)
			m_fMovePow = PLAYER_MOVESPDMAX / PLAYER_BREAKERATE;

		if(m_fMovePow >= -PLAYER_MOVESPDMAX)
		{
			m_fMovePow -= PLAYER_ADDMSPD;		// ����
		}
		else
		{
			m_fMovePow = -PLAYER_MOVESPDMAX;	// �ő呬�x
		}
	}

	if(m_fMovePow > 0.0f)
	{
		ReverseLR(TEX_LRREV);
	}
	else if(m_fMovePow < 0.0f)
	{
		ReverseLR(TEX_LRNORMAL);
	}

	m_vSpd.x = m_fMovePow;

	
}

// �W�����v���n��
void		CPlayer::PushJump()
{
	if(GETINPUT->GetKey(KEY_TRG, DIK_SPACE))
	{
		if(!m_bJump)
		{
			m_nObjStatus = PLST_JUMPUP;		// �X�e�[�^�X�Z�b�g
			//m_fJumpPow = PLAYER_JUMPPOW;	// �����p���[�Z�b�g
			m_fJumpPow = g_fJumpMax;
			
			
		}
	}

}


// �W�����v
void		CPlayer::Jump()
{
	m_vSpd.y = m_fJumpPow;		// �X�s�[�h�ɕϊ�

	//m_fJumpPow -= PLAYER_JUMPBRK;
	//if(m_fJumpPow >= 2.0f)
	//{
		m_fJumpPow -= g_fJumpBrk;
	//}
	

	if(m_fJumpPow <= 0.0f)
	{
		m_fFallSpd = 0.0f;
		m_bJump = true;
	}
}
	
// ����
void		CPlayer::Fall()
{
	m_vSpd.y = m_fFallSpd;

	m_fFallSpd -= 0.3f;
	if(m_fFallSpd <= -PLAYER_FSPDMAX)
		m_fFallSpd = -PLAYER_FSPDMAX;

	
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
		Fall();			// ���R����
		PushJump();		// �W�����v�͂���
		PushAct();		// �A�N�V�����͂���
		break;

	case PLST_RUN:
		Move();
		Fall();			// ���R����
		PushJump();
		PushAct();
		break;

	case PLST_ACTION:
		Action();
		Fall();			// ���R����
		break;

	case PLST_JUMPUP:
		Move();
		Jump();
		//Fall();			// ���R����
		PushAct();
		break;

	case PLST_FALL:
		Fall();			// ���R����
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
	//if(m_vSpd.y > 0.0f || m_vSpd.y < 0.0f)
	//	return false;		// �W�����v���܂��͗������ł���

	// �������͂��Ă�
	if((GETINPUT->GetKey(KEY_PRS, DIK_RIGHT)) && (GETINPUT->GetKey(KEY_PRS, DIK_LEFT)))
		return false;

	// ���E�̓��͂�����
	if((GETINPUT->GetKey(KEY_PRS, DIK_RIGHT)) || (GETINPUT->GetKey(KEY_PRS, DIK_LEFT)))
		return true;

	return false;		// �~�܂��Ă�
}

// ����ł邩
bool		CPlayer::CheckJump()
{
	// ������̃X�s�[�h���o�Ă�
	if(m_fJumpPow > 0.0f)
		return true;

	return false;
}

// �����Ă邩
bool		CPlayer::CheckFall()
{
	// �������̏����ȏ�̃X�s�[�h���o�Ă�
	if(m_fFallSpd < -(PLAYER_FFIRSTSPD + 1.0f))
		return true;

	return false;
}

// ����㏈��
void		CPlayer::HitUpdate(CObjBase* pObj, D3DXVECTOR3 vPos)
{
	// m_vPos = vPos;
	UpdateBillBoard();		// �r���{�[�h�X�V
	int nObjGroup = pObj->GetGroupID();

	switch(nObjGroup)
	{
	case OBJ3DGROUP_MAP:
		HitUDToMapParts(pObj, pObj->GetTypeID(), vPos);
		break;

	default:

		break;
	}
}

// �}�b�v�̃p�[�c����̌㏈��
void CPlayer::HitUDToMapParts(CObjBase* pObj, int nType, D3DXVECTOR3 vPos)
{
	CAnimalColl Coll;
	D3DXVECTOR3 vWkPos;
	int nLine;

	// ��ނ��Ƃ�
	switch(nType)
	{
	case MAPPARTS_SQUARE:
		vWkPos = Coll.GetMapBoxCrossPos(this, (CMapPartsBase*)pObj, &nLine);
		if(nLine == CROSSLINE_T)
		{	
			m_fFallSpd = -PLAYER_FFIRSTSPD;
			m_bJump = false;
		}
		if(nLine == CROSSLINE_L || nLine == CROSSLINE_R)
		{	
			m_fMovePow = 0.0f;
		}
		m_vPos = vPos;
		break;

	case MAPPARTS_RUP:
		m_fFallSpd = -PLAYER_FFIRSTSPD;
		m_vPos = vPos;
		m_bJump = false;
		break;

	case MAPPARTS_RDOWN:
		m_fFallSpd = -PLAYER_FFIRSTSPD;
		m_vPos = vPos;
		m_bJump = false;
		break;
	}
}
// eof
