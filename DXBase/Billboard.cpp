//=======================================================================================
//
//	  �r���{�[�h�֘A���W���[��
//
//=======================================================================================
//-------- �C���N���[�h�w�b�_
#include "Billboard.h"

D3DXMATRIX matS;


CBillboard::CBillboard(void)
{
	m_nDrawType = DRAWTYPE_BILLBOARD;
	m_bTrueIsZBuffer = true;

	// ���e�@
	m_nViewProjType = VIEWPROJ_ORT;

	m_Board.m_pIndexBuffer = NULL;
	m_Board.m_pVertexBuffer = NULL;
}

CBillboard::CBillboard(int nID, int nTexNum) : CObject3D(nID)
{
	m_Board.Initialize(nTexNum);		// �e�N�X�`���o�^
	m_nDrawType = DRAWTYPE_2D_NORMAL;
	m_bTrueIsZBuffer = true;
	m_bAlphaBlend = true;

	m_vSize.x = m_Board.GetSize().x;	// �e�N�X�`���T�C�Y����T�C�Y�ݒ�
	m_vSize.y = m_Board.GetSize().y;
	m_vRadius.x = m_vSize.x / 2.0f;
	m_vRadius.y = m_vSize.y / 2.0f;

	// ���e�@
	m_nViewProjType = VIEWPROJ_ORT;
}

CBillboard::~CBillboard(void)
{
	ReleaseBillboard();
}


#define FVF_DVERTEX		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define RATE_WIDTH (1.0f / ((float)SCREEN_WIDTH / 2.0f))
#define RATE_HEIGHT (1.0f / ((float)SCREEN_HEIGHT / 2.0f))

////---------------------------------------------------------------------------------------
//// �r���{�[�h������
////---------------------------------------------------------------------------------------
void CBillboard::InitializeBillboard()
{
	float radius = m_Board.m_fRadius;
	D3DXVECTOR2 v  = m_Board.GetSize();
	v.x /= 2.0f;
	v.y /= 2.0f;
	int nMaxNum = m_Board.GetImage()->GetPattern();

	// ���[�J�����W�ݒ�
	m_verWk[0].x = -v.x;
	m_verWk[0].y = v.y;
	m_verWk[0].z = 0.0f;

	m_verWk[0].nx = 0.0f;
	m_verWk[0].ny = 0.0f;
	m_verWk[0].nz = -1.0f;

	m_verWk[0].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
	m_verWk[0].tu = 0.0f;
	m_verWk[0].tv = 0.0f;

	m_verWk[1].x = v.x;
	m_verWk[1].y = v.y;
	m_verWk[1].z = 0.0f;

	m_verWk[1].nx = 0.0f;
	m_verWk[1].ny = 0.0f;
	m_verWk[1].nz = -1.0f;

	m_verWk[1].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
	m_verWk[1].tu = 1.0f / nMaxNum;
	m_verWk[1].tv = 0.0f;

	m_verWk[2].x = -v.x;
	m_verWk[2].y = -v.y;
	m_verWk[2].z = 0.0f;

	m_verWk[2].nx = 0.0f;
	m_verWk[2].ny = 0.0f;
	m_verWk[2].nz = -1.0f;

	m_verWk[2].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
	m_verWk[2].tu = 0.0f;// / (float)nMaxNum;
	m_verWk[2].tv = 1.0f;
	
	m_verWk[3].x = v.x;
	m_verWk[3].y = -v.y;
	m_verWk[3].z = 0.0f;

	m_verWk[3].nx = 0.0f;
	m_verWk[3].ny = 0.0f;
	m_verWk[3].nz = -1.0f;

	m_verWk[3].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
	m_verWk[3].tu = 1.0f;
	m_verWk[3].tv = 1.0f;

	m_world._41 = m_vPos.x;
	m_world._42 = m_vPos.y;
	m_world._43 = m_vPos.z;

	// ���X�e�[�^�X�����l
	m_nR = 255;
	m_nG = 255;
	m_nB = 255;

	m_nAlpha = 255;
	m_nAnimNum = 0;
	m_nCurDivNum = 0;
	m_ntexLR = 0;
	m_ntexTB = 0;
}


//---------------------------------------------------------------------------------------
// �r���{�[�h���
//---------------------------------------------------------------------------------------
void CBillboard::ReleaseBillboard()
{
	SAFE_RELEASE(m_Board.m_pIndexBuffer);		// �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�����
	SAFE_RELEASE(m_Board.m_pVertexBuffer);		// ���_�o�b�t�@�I�u�W�F�N�g�����
}

//---------------------------------------------------------------------------------------
// �r���{�[�h�X�V
//---------------------------------------------------------------------------------------
void CBillboard::UpdateBillBoard()
{	
	D3DXMatrixTranslation(&m_world, m_vPos.x, m_vPos.y, m_vPos.z);

	if(m_bBillBoard)
	{
		D3DXMATRIX matView = CCamera::GetThis()->GetMatView();		// �r���[�}�g���b�N�X�擾

		m_world._11 = matView._11;
		m_world._12 = matView._21;
		m_world._13 = matView._31;

		m_world._21 = matView._12;
		m_world._22 = matView._22;
		m_world._23 = matView._32;

		m_world._31 = matView._13;
		m_world._32 = matView._23;
		m_world._33 = matView._33;
	}
	
}

//---------------------------------------------------------------------------------------
// �r���{�[�h�`��J�n
//---------------------------------------------------------------------------------------
void CBillboard::DrawSetUp()
{
	// ���ߐF(�����F)���\�ɂ���
	CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Z�o�b�t�@���X�V

	if(m_bAlphaBlend)
	{
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);		// ���u�����h��
		CGraphics::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		CGraphics::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		//CGraphics::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
		//CGraphics::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
	}

	if (m_bTrueIsZBuffer) {
		// ���ߐF(�����F)�̕������o�b�t�@�ɏ������܂Ȃ�
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0);
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	} else {
		CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	// Z�o�b�t�@���X�V���Ȃ�
		
	}
	// �`��ݒ�
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);			// ���C�e�B���O���Ȃ�

	if(m_bCull)
	{
		// �J�����O�I�t
		CGraphics::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}
	

	//:::::::::::::::::::::::::::::::::::::::::::::::
}


//---------------------------------------------------------------------------------------
// �r���{�[�h�`��I��
//---------------------------------------------------------------------------------------
void CBillboard::DrawEnd()
{
	if(m_bCull)
	{
		// �J�����O
		CGraphics::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
	
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);				// ���C�e�B���O����

	CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			// Z�o�b�t�@���X�V����

	CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);	// ���u�����h �s��

}

//---------------------------------------------------------------------------------------
// �r���{�[�h�`��
//---------------------------------------------------------------------------------------
void CBillboard::Draw()
{
	//// ���[���h�}�g���b�N�X���Z�b�g
	if (m_world) 
		CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &m_world);


	// �`��
	CGraphics::GetDevice()->SetFVF(FVF_DVERTEX);

	CGraphics::GetDevice()->SetTexture(0, m_Board.m_pImage->GetTexture());						// �e�N�X�`����o�^
	CGraphics::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_verWk, sizeof(DVERTEX));// �|���S���`��

}

// �F�Z�b�g
void CBillboard::SetBillColor(D3DXVECTOR3 vColor)
{
	//DVERTEX*	VBuffer;								// ���_�o�b�t�@�ւ̃|�C���^
	m_nR = (int)vColor.x;
	m_nG = (int)vColor.y;
	m_nB = (int)vColor.z;

	m_verWk[0].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
	m_verWk[1].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
	m_verWk[2].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
	m_verWk[3].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
}

// �e�N�X�`�����W�Z�b�g
void CBillboard::SetTexBillUV(int nPattern)
{
	//DVERTEX*	VBuffer;								// ���_�o�b�t�@�ւ̃|�C���^
	
	int nMaxNum = m_Board.GetImage()->GetPattern();
	float fUSize = 1.0f / nMaxNum;
	
	float sub;
	sub = (nPattern - m_nCurDivNum) * fUSize;
	m_nCurDivNum = nPattern;

	m_verWk[0].tu += sub;
	m_verWk[0].tv = 0.0f;

	m_verWk[1].tu += sub;
	m_verWk[1].tv = 0.0f;

	m_verWk[2].tu += sub;
	m_verWk[2].tv = 1.0f;
	
	m_verWk[3].tu += sub;
	m_verWk[3].tv = 1.0f;
}

// �A���t�@�l�̃Z�b�g
void CBillboard::SetBillAlpha(float fAlphaRate)
{
	
	//DVERTEX*	VBuffer;								// ���_�o�b�t�@�ւ̃|�C���^
	m_nAlpha = (int)(255 * fAlphaRate);
	//
	
	m_verWk[0].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
	m_verWk[1].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
	m_verWk[2].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
	m_verWk[3].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
}



// �X�N���[�����W�ł̃A�N�Z�X�p�ϊ�
void CBillboard::InverseScreen(D3DXVECTOR3 vPos)
{
	D3DXMATRIX matMove;
	D3DXMATRIX matView = CCamera::GetThis()->GetMatView();;
	
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(FOVY), (float)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_CLIP, FAR_CLIP);

	D3DXMATRIX matScreen = CreateScreenMat();

	D3DXMatrixIdentity(&matMove);
	D3DXMATRIX matViewToScreen = matView * matProj * matScreen;

	D3DXMATRIX matInv;
	D3DXMatrixInverse(&matInv, NULL, &matViewToScreen);

	D3DXVECTOR3 vOut;
	D3DXVec3TransformCoord(&vOut, &vPos, &matInv);

	m_world._41 = vOut.x;
	m_world._42 = vOut.y;
	m_world._43 = vOut.z;

	//m_vPos = vOut;
}

// ���S
void CBillboard::SetLocalWkC()
{
	float radius = m_Board.m_fRadius;
	D3DXVECTOR2 v  = m_Board.GetSize();
	v.x /= 2.0f;
	v.y /= 2.0f;
	
	// ���[�J�����W�ݒ�
	m_verWk[0].x = -v.x;		// ����
	m_verWk[0].y = v.y;
	m_verWk[0].z = 0.0f;

	m_verWk[1].x = v.x;			// �E��
	m_verWk[1].y = v.y;
	m_verWk[1].z = 0.0f;

	m_verWk[2].x = -v.x;		// ����
	m_verWk[2].y = -v.y;
	m_verWk[2].z = 0.0f;

	m_verWk[3].x = v.x;			// �E��
	m_verWk[3].y = -v.y;
	m_verWk[3].z = 0.0f;

	m_nCollBasePoint = COLLBASEPOINT_CENTER;
}

// ����
void CBillboard::SetLocalWkTL()
{
	D3DXVECTOR2 v = m_Board.GetSize();

	// ���[�J�����W�ݒ�
	m_verWk[0].x = 0.0f;		// ����
	m_verWk[0].y = 0.0f;
	m_verWk[0].z = 0.0f;

	m_verWk[1].x = v.x;			// �E��
	m_verWk[1].y = 0.0f;
	m_verWk[1].z = 0.0f;

	m_verWk[2].x = 0.0f;		// ����
	m_verWk[2].y = -v.y;
	m_verWk[2].z = 0.0f;

	m_verWk[3].x = v.x;			// �E��
	m_verWk[3].y = -v.y;
	m_verWk[3].z = 0.0f;

	m_nCollBasePoint = COLLBASEPOINT_TOPLEFT;
}

// ��
void CBillboard::SetLocalWkB()
{
	D3DXVECTOR2 v = m_Board.GetSize();
	D3DXVECTOR2 r = v / 2.0f;

	// ���[�J�����W�ݒ�
	m_verWk[0].x = -r.x;		// ����
	m_verWk[0].y = v.y;
	m_verWk[0].z = 0.0f;

	m_verWk[1].x = r.x;			// �E��
	m_verWk[1].y = v.y;
	m_verWk[1].z = 0.0f;

	m_verWk[2].x = -r.x;		// ����
	m_verWk[2].y = 0.0f;
	m_verWk[2].z = 0.0f;

	m_verWk[3].x = r.x;			// �E��
	m_verWk[3].y = 0.0f;
	m_verWk[3].z = 0.0f;

	m_nCollBasePoint = COLLBASEPOINT_BOTTOM;
}

// ���E���]
void CBillboard::ReverseLR(int nType)
{
	//�ϐ��錾
	float a = 1.0f / m_Board.m_nMaxPlain;	//���ȗ��p�ϐ�

	if(nType >= TEX_LRALL || nType < 0)
		return;

	m_ntexLR = nType;

	if(nType == TEX_LRNORMAL)
	{
		m_verWk[0].tu = a * m_nCurDivNum;//D3DXVECTOR2(     , 0.0f);
		m_verWk[0].tv = 0.0f;
		m_verWk[1].tu = a * m_nCurDivNum + a;//D3DXVECTOR2( , 0.0f);
		m_verWk[1].tv = 0.0f;
		m_verWk[2].tu = a * m_nCurDivNum;//D3DXVECTOR2(     , 1.0f);
		m_verWk[2].tv = 1.0f;
		m_verWk[3].tu = a * m_nCurDivNum + a;//D3DXVECTOR2( , 1.0f);
		m_verWk[3].tv = 1.0f;
	}
	else
	{
		m_verWk[1].tu = a * m_nCurDivNum;//D3DXVECTOR2(     , 0.0f);
		m_verWk[1].tv = 0.0f;
		m_verWk[0].tu = a * m_nCurDivNum + a;//D3DXVECTOR2( , 0.0f);
		m_verWk[0].tv = 0.0f;
		m_verWk[3].tu = a * m_nCurDivNum;//D3DXVECTOR2(     , 1.0f);
		m_verWk[3].tv = 1.0f;
		m_verWk[2].tu = a * m_nCurDivNum + a;//D3DXVECTOR2( , 1.0f);
		m_verWk[2].tv = 1.0f;
	}

	
}

//=======================================================================================
//	End of File
//=======================================================================================

