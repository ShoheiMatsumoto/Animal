#include "AnimaruBase.h"
#include "AnimalColl.h"

// �A�j�܂��ԗ�


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
	m_vSpd.y = -1.0f;
	
	// �v���C���[�ŗL�X�e�[�^�X
	CSt.m_nMoveVecType = MOVEVEC_TYPE_RIGHT;		// �E����
	CSt.m_fFallSpd = ADDFSPD;
	CSt.m_fJumpPow = 0.0f;
	CSt.m_fMovePow = 0.0f;
	CSt.m_bJump = false;

}

// �X�V
void		CAnimaruBase::Update()
{
	Control();

	
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
		CSt.m_fMovePow -= BRKSPD;
		if(CSt.m_fMovePow <= 0.0f)
			CSt.m_fMovePow = 0.0f;
	}

	if(CSt.m_fMovePow < 0.0f)
	{
		CSt.m_fMovePow += BRKSPD;
		if(CSt.m_fMovePow >= 0.0f)
			CSt.m_fMovePow = 0.0f;
	}
	m_vSpd.x = CSt.m_fMovePow;
}

// �ړ�
void		CAnimaruBase::Move()
{
	

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
		SetAct();		// �A�N�V�����͂���
		break;

	case ST_RUN:
		Move();
		Fall();			// ���R����
		SetJump();
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

	


}

// �����Ă邩
bool		CAnimaruBase::CheckRun()
{
	
	return false;		// �~�܂��Ă�
}

// ����ł邩
bool		CAnimaruBase::CheckJump()
{
	// ������̃X�s�[�h���o�Ă�
	if(CSt.m_fJumpPow > 0.0f)
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
		}
		if(nLine == CROSSLINE_L || nLine == CROSSLINE_R)
		{	
			CSt.m_fMovePow = 0.0f;
		}
		m_vPos = vPos;
		break;

	case MAPPARTS_RUP:
		CSt.m_fFallSpd = -FFIRSTSPD;
		m_vPos = vPos;
		CSt.m_bJump = false;
		break;

	case MAPPARTS_RDOWN:
		CSt.m_fFallSpd = -FFIRSTSPD;
		m_vPos = vPos;
		CSt.m_bJump = false;
		break;
	}
}
// eof
