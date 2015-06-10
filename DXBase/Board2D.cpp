// �C���N���[�h
#include "Board2D.h"
#include "SceneBase.h"


CBoard2D::CBoard2D(void)
{

}


CBoard2D::~CBoard2D(void)
{
	//SAFE_RELEASE(m_Image->pTexture);			// �e�N�X�`���I�u�W�F�N�g�����
	
}

//==============================
//��������
//==============================
void CBoard2D::Initialize(DWORD dwImageType)
{
	// �e�N�X�`�����Ȃ�������G���[����
	/*if(dwImageType == 0)
		return E_FAIL;*/

	//2D�|���S���p�e�N�X�`���̃��[�h
	
	m_nImageType = dwImageType;
	m_pImage = CSceneBase::GetCurScene()->GetTexMgr()->GetTex(dwImageType);	// �V�[������C���[�W�f�[�^�����
	
	//���_�̐ݒ�
	D3DXVECTOR2* pv = m_pImage->GetSize();
	m_vSize = *pv;							// �T�C�Y�擾
	m_vHalfSize = m_vSize / 2.0f;			// ���a�擾

	m_verWk[0].vtx = D3DXVECTOR4(-pv->x / 2.0f,	-pv->y / 2.0f,	0.0f, 0.0f);
	m_verWk[1].vtx = D3DXVECTOR4( pv->x / 2.0f,	-pv->y / 2.0f,	0.0f, 0.0f);
	m_verWk[2].vtx = D3DXVECTOR4(-pv->x / 2.0f,	 pv->y / 2.0f,	0.0f, 0.0f);
	m_verWk[3].vtx = D3DXVECTOR4( pv->x / 2.0f,	 pv->y / 2.0f,	0.0f, 0.0f);

	//���_�J���[�E���`�����l���̐ݒ�
	m_verWk[0].diffuse = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	m_verWk[1].diffuse = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	m_verWk[2].diffuse = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	m_verWk[3].diffuse = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	//�e�N�X�`�����W�̐ݒ�
	int nMaxNum = m_pImage->GetPattern();
	m_verWk[0].tex = D3DXVECTOR2(0.0f				, 0.0f);
	m_verWk[1].tex = D3DXVECTOR2(1.0f / nMaxNum	, 0.0f);
	m_verWk[2].tex = D3DXVECTOR2(0.0f				, 1.0f);
	m_verWk[3].tex = D3DXVECTOR2(1.0f / nMaxNum	, 1.0f);

	m_nMaxPlain		= nMaxNum;
	/*m_bScrollFlag	= false;
	m_fScrollSpdX	= 0.0f;
	m_fScrollSpdY	= 0.0f;
	m_fScrollPosX	= 0.0f;
	m_fScrollPosY	= 0.0f;*/

	// ���a�v�Z�H(�Ƃ肠�����Z�����𔼌a��)
	D3DXVECTOR2* pV = m_pImage->GetHalfSize();
	m_fRadius		= pV->x < pV->y ? pV->x : pV->y;

	for(int i = 0; i < 4; i++)
		m_nColor[i] = 255;

	m_nR = 255;
	m_nG = 255;
	m_nB = 255;
	m_nAlpha = 255;
	m_nCurDivNum = 0;
	m_ntexLR = 0;
	m_ntexTB = 0;
	//return S_OK;
}

//==============================
//�X�V����
//==============================
//void CBoard2D::Update(void)
//{

	//D3DXMATRIX mWorld, mT, mR, mS;

	////�s��v�Z
	//D3DXMatrixTranslation(&mT, (float)m_Data.x, (float)m_Data.y, 0.0f);
	//D3DXMatrixScaling(&mS, (float)m_Data.sx, (float)m_Data.sy, 0.0f);
	//D3DXMatrixRotationZ(&mR , D3DXToRadian(m_Data.angle));

	//mWorld = mS * mR * mT;

	//if(m_Data.alpha > 255 || m_Data.alpha < 0)
	//	int a = 0;

	//m_verPos[0].diffuse = D3DCOLOR_RGBA(m_nColor[0], m_nColor[1], m_nColor[2], m_Data.alpha);
	//m_verPos[1].diffuse = D3DCOLOR_RGBA(m_nColor[0], m_nColor[1], m_nColor[2], m_Data.alpha);
	//m_verPos[2].diffuse = D3DCOLOR_RGBA(m_nColor[0], m_nColor[1], m_nColor[2], m_Data.alpha);
	//m_verPos[3].diffuse = D3DCOLOR_RGBA(m_nColor[0], m_nColor[1], m_nColor[2], m_Data.alpha);

	////�A�t�B���ϊ�
	//for(int nCntVer = 0 ; nCntVer < 4 ; nCntVer ++)
	//{
	//	m_verCopy[nCntVer] = m_verPos[nCntVer];
	//	D3DXVec2TransformCoord((D3DXVECTOR2 *)&m_verCopy[nCntVer].vtx , (D3DXVECTOR2 *)&m_verPos[nCntVer].vtx , &mWorld);
	//}

	//if(m_bScrollFlag)
	//{
	//	m_fScrollPosX += m_fScrollSpdX;
	//	m_fScrollPosY += m_fScrollSpdY;

	//	m_verPos[0].tex = D3DXVECTOR2(m_fScrollPosX        , m_fScrollPosY);
	//	m_verPos[1].tex = D3DXVECTOR2(m_fScrollPosX + 1.0f , m_fScrollPosY);
	//	m_verPos[2].tex = D3DXVECTOR2(m_fScrollPosX        , m_fScrollPosY + 1.0f);
	//	m_verPos[3].tex = D3DXVECTOR2(m_fScrollPosX + 1.0f , m_fScrollPosY + 1.0f);
	//}
//}


//==============================
//�`�揈��
//==============================
//void CBoard2D::Draw(void)
//{
//	// �e�N�X�`�����\���Ă��Ȃ�������G���[����
//	if(m_Data.type == 0)
//		return;
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	GetGraph->GetDevice()->SetFVF(FVF_VERTEX_2D);
//
//	// �����_�����O�X�e�[�g�̐ݒ�
//	CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,	(m_Data.flag & FLAG_ALPHA) ? TRUE:FALSE);						// �A���t�@�u�����h����
//	CGraphics::GetDevice()->SetRenderState(D3DRS_DESTBLEND,			(m_Data.flag & FLAG_ONE) ? D3DBLEND_ONE:D3DBLEND_INVSRCALPHA);	// ���Z��������
////	CGraphics::GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);	// �g��p(�o�C���j�A�E�t�B���^�����O)
////	CGraphics::GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);	// �k���p(�o�C���j�A�E�t�B���^�����O)
//
//	//�e�N�X�`���̐ݒ�
//	if(m_nImageType != NULL)	//������O���Ȃ���1�O�̃e�N�X�`���̂܂�
//		GetGraph->GetDevice()->SetTexture(0 , CScene::GetThis()->GetImage(m_nImageType)->GetTexture());
//
//	//�|���S���̕`��
//	GetGraph->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP , 2 , m_verCopy , sizeof(VERTEX_2D));
//
//}


//==============================
//�ʒu��ς���C
//==============================
void CBoard2D::SetPosC(D3DXVECTOR3 vPos)
{
	D3DXVECTOR2 vS = m_vHalfSize;

	m_verWk[0].vtx = D3DXVECTOR4(vPos.x - vS.x,	vPos.y - vS.y, vPos.z, 1.0f); 
	m_verWk[1].vtx = D3DXVECTOR4(vPos.x + vS.x, vPos.y - vS.y, vPos.z, 1.0f);
	m_verWk[2].vtx = D3DXVECTOR4(vPos.x - vS.x,	vPos.y + vS.y, vPos.z, 1.0f);
	m_verWk[3].vtx = D3DXVECTOR4(vPos.x + vS.x, vPos.y + vS.y, vPos.z, 1.0f);
}

//==============================
//�ʒu��ς���L
//==============================
void CBoard2D::SetPosL(D3DXVECTOR3 vPos)
{
	D3DXVECTOR2 vS = m_vSize;

	m_verWk[0].vtx = D3DXVECTOR4(vPos.x       ,	vPos.y, vPos.z, 1.0f); 
	m_verWk[1].vtx = D3DXVECTOR4(vPos.x + vS.x, vPos.y, vPos.z, 1.0f);
	m_verWk[2].vtx = D3DXVECTOR4(vPos.x       ,	vPos.y + vS.y, vPos.z, 1.0f);
	m_verWk[3].vtx = D3DXVECTOR4(vPos.x + vS.x, vPos.y + vS.y, vPos.z, 1.0f);
}

//==============================
//�\������G��ς���
//==============================
void CBoard2D::SetNum(int nNum)
{
	//�ϐ��錾
	float a = 1.0f / m_nMaxPlain;	//���ȗ��p�ϐ�
	float sub;

	if(nNum >= m_nMaxPlain)
		return;
	
	sub = (nNum - m_nCurDivNum) * a;	// �ړ�����

	m_nCurDivNum = nNum;		// ���ݕ����ʒu�X�V

	m_verWk[0].tex = D3DXVECTOR2(m_verWk[0].tex.x + sub     , 0.0f);
	m_verWk[1].tex = D3DXVECTOR2(m_verWk[1].tex.x + sub , 0.0f);
	m_verWk[2].tex = D3DXVECTOR2(m_verWk[2].tex.x + sub     , 1.0f);
	m_verWk[3].tex = D3DXVECTOR2(m_verWk[3].tex.x + sub , 1.0f);
}


//==============================
//���ߓx��ς���
//==============================
void CBoard2D::SetAlpha(float fAlpha)
{
	int nAlpha = (int)(255 * fAlpha);
	m_nAlpha = nAlpha;

	m_verWk[0].diffuse = D3DCOLOR_RGBA(m_nR , m_nG , m_nB , nAlpha);
	m_verWk[1].diffuse = D3DCOLOR_RGBA(m_nR , m_nG , m_nB , nAlpha);
	m_verWk[2].diffuse = D3DCOLOR_RGBA(m_nR , m_nG , m_nB , nAlpha);
	m_verWk[3].diffuse = D3DCOLOR_RGBA(m_nR , m_nG , m_nB , nAlpha);
}

//==============================
// �|���̃��T�C�Y
//==============================
void CBoard2D::ReSize(D3DXVECTOR2 vSize)
{
	D3DXVECTOR2 vPos;
	D3DXVECTOR2 v = m_vHalfSize;		// ���n�[�t�T�C�Y�擾

	// ���S���W
	vPos.x = m_verWk[0].vtx.x + v.x;
	vPos.y = m_verWk[0].vtx.y + v.y;

	m_verWk[0].vtx = D3DXVECTOR4(vPos.x + (-vSize.x / 2.0f), vPos.y + (-vSize.y / 2.0f),	0.0f, 0.0f);
	m_verWk[1].vtx = D3DXVECTOR4(vPos.x + (vSize.x / 2.0f),  vPos.y + (-vSize.y / 2.0f),	0.0f, 0.0f);
	m_verWk[2].vtx = D3DXVECTOR4(vPos.x + (-vSize.x / 2.0f), vPos.y + (vSize.y / 2.0f),	0.0f, 0.0f);
	m_verWk[3].vtx = D3DXVECTOR4(vPos.x + (vSize.x / 2.0f),  vPos.y + (vSize.y / 2.0f),	0.0f, 0.0f);

	// �T�C�Y�X�V
	m_vSize = vSize;
	m_vHalfSize = vSize / 2.0f;
	m_fRadius = m_vHalfSize.x;
}

//==============================
// �|����������Ƀ��T�C�Y
//==============================
void CBoard2D::SetLength(float fLength)
{
	float fPos = 	m_verWk[0].vtx.x;

	m_verWk[1].vtx.x = fPos + fLength;
	m_verWk[3].vtx.x = fPos + fLength;
}

// �T�C�Y�̕ύX
void CBoard2D::SetSize(D3DXVECTOR2 vSize)
{
	m_vSize = vSize;
	m_vHalfSize = vSize / 2.0f;
}

// �J���[�̕ύX
void CBoard2D::SetColor(int nR, int nG, int nB)
{
	m_nR = nR;
	m_nG = nG;
	m_nB = nB;

	//���_�J���[�E���`�����l���̐ݒ�
	m_verWk[0].diffuse = D3DCOLOR_RGBA(nR , nG , nB , m_nAlpha);
	m_verWk[1].diffuse = D3DCOLOR_RGBA(nR , nG , nB , m_nAlpha);
	m_verWk[2].diffuse = D3DCOLOR_RGBA(nR , nG , nB , m_nAlpha);
	m_verWk[3].diffuse = D3DCOLOR_RGBA(nR , nG , nB , m_nAlpha);

}

// ���E���]
void CBoard2D::ReverseLR(int nType)
{
	//�ϐ��錾
	float a = 1.0f / m_nMaxPlain;	//���ȗ��p�ϐ�

	if(nType >= TEX_LRALL || nType < 0)
		return;

	m_ntexLR = nType;

	if(nType == TEX_LRNORMAL)
	{
		m_verWk[0].tex = D3DXVECTOR2(a * m_nCurDivNum     , 0.0f);
		m_verWk[1].tex = D3DXVECTOR2(a * m_nCurDivNum + a , 0.0f);
		m_verWk[2].tex = D3DXVECTOR2(a * m_nCurDivNum     , 1.0f);
		m_verWk[3].tex = D3DXVECTOR2(a * m_nCurDivNum + a , 1.0f);
	}
	else
	{
		m_verWk[1].tex = D3DXVECTOR2(a * m_nCurDivNum     , 0.0f);
		m_verWk[0].tex = D3DXVECTOR2(a * m_nCurDivNum + a , 0.0f);
		m_verWk[3].tex = D3DXVECTOR2(a * m_nCurDivNum     , 1.0f);
		m_verWk[2].tex = D3DXVECTOR2(a * m_nCurDivNum + a , 1.0f);
	}

	
}

// �㉺���]
void CBoard2D::ReverseTB(int nType)
{

}
