#include "AnimaruBase.h"
#include "AnimalColl.h"
#include "Input.h"

// �A�j�܂��ԗ�

// �萔��`
#define DIST_ONE (100.0f)
#define DIST_TWO (50.0f)
#define BRK_DIST (100.0f)

#define ANIMARU_BRKONE (0.2f)
#define ANIMARU_BRKTWO (0.4f)

#define MOVEJUMPPOW (5.0f)

enum
{
	ANST_MOVEJUMP = ST_ALL,

	ANST_ALL
};

CAnimaruBase::CAnimaruBase(void)
{
}

CAnimaruBase::CAnimaruBase(int nGroupID, int nTypeID, int nTexID, D3DXVECTOR3 vPos) : CBillboard(nTypeID, nTexID)
{
	m_nObjGroupID = nGroupID;
	m_vPos = vPos;
}

CAnimaruBase::~CAnimaruBase(void)
{
	
}


// ����
CAnimaruBase*	CAnimaruBase::Create(int nGroupID, int nTypeID, int nTexID, D3DXVECTOR3 vPos)
{
	CAnimaruBase* p = new CAnimaruBase(nGroupID, nTypeID, nTexID, vPos);

	p->Initialize();

	return p;
}

// ������
void		CAnimaruBase::Initialize()
{
	m_nObjGroupID = OBJ3DGROUP_ANIMARU;		// �O���[�v�ݒ�
	//m_nDType = OT_2D;
	
	// 2D�X�e�[�^�X�Z�b�g
	m_Board.ReSize(D3DXVECTOR2(64.0f, 64.0f));		
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

	m_nObjStatus = ST_STAND;
	//m_vSpd.y = -1.0f;
	
	// �ŗL�X�e�[�^�X
	CSt.m_nMoveVecType = MOVEVEC_TYPE_RIGHT;		// �E����
	CSt.m_fFallSpd = ADDFSPD;
	CSt.m_fJumpPow = 0.0f;
	CSt.m_fMovePow = 0.0f;
	CSt.m_bJump = false;

	m_bChase = false;
	m_bCBrk = false;

}

// �X�V
void		CAnimaruBase::Update()
{
	
	if(!m_bEvent)
	{
		Control();

		// ���͏�����
		InitInputData();
	}
	else	// ���[�r�[�p����
	{

	}

	m_vPos += m_vSpd;		// ���W�ւ̑��
	UpdateBillBoard();		// �r���{�[�h�X�V

	
}

// ���
void		CAnimaruBase::Release()
{

	delete this;
}


// ����
void		CAnimaruBase::BacktoStand()
{
	if(CSt.m_fMovePow > 0.0f)
	{
		CSt.m_fMovePow -= CSt.m_fBrakePow;
		if(CSt.m_fMovePow <= 0.0f)
			CSt.m_fMovePow = 0.0f;
	}

	if(CSt.m_fMovePow < 0.0f)
	{
		CSt.m_fMovePow += CSt.m_fBrakePow;
		if(CSt.m_fMovePow >= 0.0f)
			CSt.m_fMovePow = 0.0f;
	}
	m_vSpd.x = CSt.m_fMovePow;
}

// �ړ�
void		CAnimaruBase::Move()
{
	// �ǐՃt���O���~��Ă���
	if(!m_bChase)
		return;

	// �E
	//if(m_nChaseVec == CHASE_RIGHT)
	if(m_bInput[KEY_PRS][INP_BTN_RIGHT])
	{
		if(CSt.m_fMovePow < -MOVESPDMAX / BREAKERATE)
			CSt.m_fMovePow = -MOVESPDMAX / BREAKERATE;
		
		if(CSt.m_fMovePow <= MOVESPDMAX)
		{
			CSt.m_fMovePow += ADDMSPD;		// ����
			
		}
		else
		{
			CSt.m_fMovePow = MOVESPDMAX;	// �ő呬�x
			
		}
	}

	// ��
	//if(m_nChaseVec == CHASE_LEFT)
	if(m_bInput[KEY_PRS][INP_BTN_LEFT])
	{
		if(CSt.m_fMovePow > MOVESPDMAX / BREAKERATE)
			CSt.m_fMovePow = MOVESPDMAX / BREAKERATE;

		if(CSt.m_fMovePow >= -MOVESPDMAX)
		{
			CSt.m_fMovePow -= ADDMSPD;		// ����
		}
		else
		{
			CSt.m_fMovePow = -MOVESPDMAX;	// �ő呬�x
		}
	}

	if(CSt.m_fMovePow > 0.0f)
	{
		ReverseLR(TEX_LRREV);
	}
	else if(CSt.m_fMovePow < 0.0f)
	{
		ReverseLR(TEX_LRNORMAL);
	}

	m_vSpd.x = CSt.m_fMovePow;


}

// �ړ��W�����v�̃Z�b�g
void CAnimaruBase::SetMJump()
{
	//if(m_bChase && !CSt.m_bJump)
	if(m_bChase && !CSt.m_bJump)
	{
		m_nObjStatus = ANST_MOVEJUMP;
		CSt.m_fJumpPow = MOVEJUMPPOW;
		
	}
}

// �ړ����̏��W�����v
void CAnimaruBase::MoveJump()
{
	m_vSpd.y = CSt.m_fJumpPow;		// �X�s�[�h�ɕϊ�

	CSt.m_fJumpPow -= JUMPBRK;

	if(CSt.m_fJumpPow <= 0.0f)
	{
		CSt.m_fFallSpd = 0.0f;
		CSt.m_bJump = true;
	}
}

// �W�����v���n��
void		CAnimaruBase::SetJump()
{
	
	
}


// �W�����v
void		CAnimaruBase::Jump()
{
	m_vSpd.y = CSt.m_fJumpPow;		// �X�s�[�h�ɕϊ�

	CSt.m_fJumpPow -= JUMPBRK;
	
	if(CSt.m_fJumpPow <= 0.0f)
	{
		CSt.m_fFallSpd = 0.0f;
		CSt.m_bJump = true;
	}
}
	
// ����
void		CAnimaruBase::Fall()
{
	m_vSpd.y = CSt.m_fFallSpd;

	CSt.m_fFallSpd -= 0.3f;
	if(CSt.m_fFallSpd <= -FSPDMAX)
		CSt.m_fFallSpd = -FSPDMAX;

	
}

// �A�N�V�����J�n
void		CAnimaruBase::SetAct()
{

}

// �A�N�V�����R�}���h
void		CAnimaruBase::Action()
{

}

// ����
void		CAnimaruBase::Control()
{
	// ���`�F�b�N�X�e�[�^�X�X�V
	CheckEnvir();

	switch(m_nObjStatus)
	{
	case ST_STAND:
		BacktoStand();
		Move();			// �ړ�
		Fall();			// ���R����
		SetJump();		// �W�����v�͂���
		SetMJump();
		SetAct();		// �A�N�V�����͂���
		break;

	case ST_RUN:
		Move();
		Fall();			// ���R����
		SetJump();
		SetMJump();
		SetAct();
		break;

	case ST_ACTION:
		Action();
		Fall();			// ���R����
		break;

	case ST_JUMPUP:
		Move();
		Jump();
		//Fall();			// ���R����
		SetAct();
		break;

	case ST_FALL:
		Fall();			// ���R����
		break;
	default:

		break;
	}

	
}

// �v���C���[���u����Ă�������`�F�b�N���A�X�e�[�^�X��ύX
void			CAnimaruBase::CheckEnvir()
{
	m_nObjStatus = ST_STAND;		// 

	if(CheckRun())
		m_nObjStatus = ST_RUN;

	if(CheckJump())
		m_nObjStatus = ST_JUMPUP;

	if(CheckFall())
		m_nObjStatus = ST_FALL;

	CheckDist();
}

// �����Ă邩
bool		CAnimaruBase::CheckRun()
{
	// �ǐՃt���O�������Ă�
	if(m_bChase)		
		return true;

	return false;		// �~�܂��Ă�




}

// ����ł邩
bool		CAnimaruBase::CheckJump()
{
	// ������̃X�s�[�h���o�Ă�
	if(CSt.m_fJumpPow > 0.0f && m_bChase)
		return true;

	return false;
}

// �����Ă邩
bool		CAnimaruBase::CheckFall()
{
	// �������̏����ȏ�̃X�s�[�h���o�Ă�
	if(CSt.m_fFallSpd < -(FFIRSTSPD + 1.0f))
		return true;

	return false;
}

// ����㏈��
void		CAnimaruBase::HitUpdate(CObjBase* pObj, D3DXVECTOR3 vPos)
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
void CAnimaruBase::HitUDToMapParts(CObjBase* pObj, int nType, D3DXVECTOR3 vPos)
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
			CSt.m_fFallSpd = -FFIRSTSPD;
			CSt.m_bJump = false;
			//m_bInput[KEY_TRG][INP_BTN_SPACE] = true;
		}
		if(nLine == CROSSLINE_L || nLine == CROSSLINE_R)
		{	
			CSt.m_fMovePow = 0.0f;
		}
		m_vPos = vWkPos;
		break;

	case MAPPARTS_RUP:
		CSt.m_fFallSpd = -FFIRSTSPD;
		m_vPos = vPos;
		CSt.m_bJump = false;
		//m_bInput[KEY_TRG][INP_BTN_SPACE] = true;
		break;

	case MAPPARTS_RDOWN:
		CSt.m_fFallSpd = -FFIRSTSPD;
		m_vPos = vPos;
		CSt.m_bJump = false;
		//m_bInput[KEY_TRG][INP_BTN_SPACE] = true;
		break;
	}
}

void CAnimaruBase::SetbChase(bool bChase, int nChaseVec)
{
	m_bChase = bChase;		// �t���OON

	m_nChaseVec = nChaseVec;	// �ǐՕ����̌���

	if(nChaseVec == CHASE_RIGHT)
	{
		m_bInput[KEY_PRS][INP_BTN_RIGHT] = true;
	}
	
	if(nChaseVec == CHASE_LEFT)
	{
		m_bInput[KEY_PRS][INP_BTN_LEFT] = true;
	}

}

void CAnimaruBase::SetSlotID(int nSlotID)
{
	m_nSlotID = nSlotID;

	if(nSlotID == 0)
		CSt.m_fBrakePow = ANIMARU_BRKONE;
	else if(nSlotID >= 1)
		CSt.m_fBrakePow = ANIMARU_BRKTWO;
}


// �ǐՑΏۂƂ̋����`�F�b�N
void CAnimaruBase::CheckDist()
{
	float Subx = m_pvChaseTargetPos->x - m_vPos.x; 
	float fDist;
	int nVec;

	//fDist = DIST_ONE;

	// ID�ɂ�鋗���̈Ⴂ
	if(m_nSlotID == 0)
		fDist = DIST_ONE;
	else if(m_nSlotID >= 1)
		fDist = DIST_TWO;

	if(abs(Subx) > fDist)
	{
		if(Subx > 0.0f)
			nVec = CHASE_RIGHT;		// ���Ȃ�E�����֒ǐ�
		else
			nVec = CHASE_LEFT;		// ���Ȃ獶�����֒ǐ�

		// �ǐՃt���O�ƕ����̃Z�b�g
		SetbChase(true, nVec);

		if(m_nSlotID >= 1)
		{
			if(abs(Subx) >= BRK_DIST)
			{
				m_bCBrk = true;
			}
		}
	}
	
	
	if(m_nSlotID == 0)
	{
		if(abs(Subx) <= fDist)
			SetbChase(false, CHASE_NONE);
	}

	
	if(m_nSlotID >= 1)
	{
		if(m_bCBrk)
		{
			if(abs(Subx) <= BRK_DIST)
			{
				SetbChase(false, CHASE_NONE);
				if(abs(Subx) <= fDist)
					m_bCBrk = false;
			}
		}
	}
	


		
	
	
}


// eof
