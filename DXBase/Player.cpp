#include "Player.h"
#include "Input.h"
#include "MapPartsBase.h"
#include "AnimalColl.h"
#include "SceneBase.h"
#include "WkFactory.h"



float g_fJumpMax; 
float g_fJumpBrk; 
float g_fAddfSpd; 
float g_ffSpdMax; 
float g_fFirSpd;  
//float g_fSpdMax = 5.0f;


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

	p->m_vPos = vPos;
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

	m_nObjStatus = ST_STAND;
	m_vSpd.y = -1.0f;
	
	// �v���C���[�ŗL�X�e�[�^�X
	CSt.m_nMoveVecType = MOVEVEC_TYPE_RIGHT;		// �E����
	CSt.m_fFallSpd = ADDFSPD;
	CSt.m_fJumpPow = 0.0f;
	CSt.m_fMovePow = 0.0f;
	CSt.m_bJump = false;

	// �A�j�܂�Z�b�g
	SetAnimaru();


	/*g_fJumpMax = JUMPPOW;
	g_fJumpBrk = JUMPBRK;
	g_fAddfSpd = ADDFSPD;
	g_ffSpdMax = FSPDMAX;
	g_fFirSpd = FFIRSTSPD;*/
}

// �X�V
void		CPlayer::Update()
{
	if(GETINPUT->GetKey(KEY_TRG, DIK_1))
		m_vPos = D3DXVECTOR3(0.0f, 280.0f, 0.0f);
		
	/*if(GETINPUT->GetKey(KEY_TRG, DIK_O))
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
		g_fAddfSpd -= 0.1f;*/

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


	//TCHAR		m_szDebug[4096];
	//
	//TCHAR	str[256];
	//
	//// �e��f�o�b�O�p���l�\��
	//m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���
	//_stprintf(str, _T("OL �W�����v�}�b�N�X:%f"), g_fJumpMax);
	//lstrcat(m_szDebug, str);
	//CSceneBase::GetThis()->GetGraph()->DrawText(10, 40, m_szDebug);

	//m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���
	//_stprintf(str, _T("IK �W�����v�u���[�L:%f"), g_fJumpBrk);
	//lstrcat(m_szDebug, str);
	//CSceneBase::GetThis()->GetGraph()->DrawText(10, 60, m_szDebug);
	//
	//m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���
	//_stprintf(str, _T("UJ �����}�b�N�X:%f"), g_ffSpdMax);
	//lstrcat(m_szDebug, str);
	//CSceneBase::GetThis()->GetGraph()->DrawText(10, 80, m_szDebug);

	//m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���
	//_stprintf(str, _T("TG �������Z:%f"), g_fAddfSpd);
	//lstrcat(m_szDebug, str);
	//CSceneBase::GetThis()->GetGraph()->DrawText(10, 100, m_szDebug);

	//m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���
	//_stprintf(str, _T("YH ��������:%f"), g_fFirSpd);
	//lstrcat(m_szDebug, str);
	//CSceneBase::GetThis()->GetGraph()->DrawText(10, 120, m_szDebug);

	//m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���
	//_stprintf(str, _T("YH �������x:%f"), m_fFallSpd);
	//lstrcat(m_szDebug, str);
	//CSceneBase::GetThis()->GetGraph()->DrawText(10, 140, m_szDebug);
	
}


// ���
void		CPlayer::Release()
{

	delete this;
}


// ����
void		CPlayer::BacktoStand()
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
void		CPlayer::Move()
{
	// �E
	if(GETINPUT->GetKey(KEY_PRS, DIK_RIGHT))
	{
		//if(GETINPUT->GetKey(KEY_TRG, DIK_RIGHT))
			//ReverseLR(TEX_LRREV);

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
	if(GETINPUT->GetKey(KEY_PRS, DIK_LEFT))
	{
		//if(GETINPUT->GetKey(KEY_TRG, DIK_LEFT))
			

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

// �W�����v���n��
void		CPlayer::PushJump()
{
	if(GETINPUT->GetKey(KEY_TRG, DIK_SPACE))
	{
		if(!CSt.m_bJump)
		{
			m_nObjStatus = ST_JUMPUP;		// �X�e�[�^�X�Z�b�g
			CSt.m_fJumpPow = JUMPPOW;	// �����p���[�Z�b�g
		}
	}

}


// �W�����v
void		CPlayer::Jump()
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
void		CPlayer::Fall()
{
	m_vSpd.y = CSt.m_fFallSpd;

	CSt.m_fFallSpd -= 0.3f;
	if(CSt.m_fFallSpd <= -FSPDMAX)
		CSt.m_fFallSpd = -FSPDMAX;

	
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
	case ST_STAND:
		BacktoStand();
		Move();			// �ړ�
		Fall();			// ���R����
		PushJump();		// �W�����v�͂���
		PushAct();		// �A�N�V�����͂���
		break;

	case ST_RUN:
		Move();
		Fall();			// ���R����
		PushJump();
		PushAct();
		break;

	case ST_ACTION:
		Action();
		Fall();			// ���R����
		break;

	case ST_JUMPUP:
		Move();
		Jump();
		//Fall();			// ���R����
		PushAct();
		break;

	case ST_FALL:
		Fall();			// ���R����
		break;
	default:

		break;
	}

	
}

// �v���C���[���u����Ă�������`�F�b�N���A�X�e�[�^�X��ύX
void			CPlayer::CheckEnvir()
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
	if(CSt.m_fJumpPow > 0.0f)
		return true;

	return false;
}

// �����Ă邩
bool		CPlayer::CheckFall()
{
	// �������̏����ȏ�̃X�s�[�h���o�Ă�
	if(CSt.m_fFallSpd < -(FFIRSTSPD + 1.0f))
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

// ���A�j�}���֘A
void CPlayer::SetAnimaru()
{
	// �A�j�܂鏀��
	for(int i = 0; i < 12; i++)
		m_pAnimaruBox[i] = NULL;	// ������
	for(int i = 0; i < 3; i++)
		m_pAnimaruSlot[i] = NULL;

	// �g�p�\���̏�Ԃ��O������ǂݍ���

	// ����
	D3DXVECTOR3 vPos = D3DXVECTOR3(m_vPos.x - 10.0f, 0.0f, 0.0f);
	CFactoryBase* pFac;
	pFac = CSceneBase::GetCurScene()->GetFactory();
	m_pAnimaruBox[ANIMARU_NO_NEZU] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_NEZU, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_USHI] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_USHI, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_TORA] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_TORA, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_MIMI] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_MIMI, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_TATSU] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_TATSU, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_HEBI] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_HEBI, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_UMA] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_UMA, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_MOKO] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_MERRY, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_SARU] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_SARU, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_TORI] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_TORI, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_INU] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_INU, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_URI] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_URI, 0, vPos);

	for(int i = 0; i < ANIMARU_NO_MAX; i++)
		m_pAnimaruBox[i]->SetbUse(false);		// �Ƃ肠������X�V���

	// �O�����猻�݃X���b�g�ɃZ�b�g����Ă���A�j�܂�����炢�X���b�g�ɃZ�b�g
	// ���͂Ƃ肠�����@�ˁA�����A�Ƃ�
	m_pAnimaruSlot[0] = m_pAnimaruBox[ANIMARU_NO_NEZU];
	m_pAnimaruSlot[1] = m_pAnimaruBox[ANIMARU_NO_USHI];
	m_pAnimaruSlot[2] = m_pAnimaruBox[ANIMARU_NO_TORA];

	m_pAnimaruSlot[0]->SetbUse(true);
	m_pAnimaruSlot[1]->SetbUse(true);
	m_pAnimaruSlot[2]->SetbUse(true);
}

// ��������
void CPlayer::CheckAniDist()
{
	// ��C�ڂƂ̋����𑪂�

}

// ���W�ۑ�
void CPlayer::PreservPos()
{
	m_vPrePos = m_vPos;
}

// eof
