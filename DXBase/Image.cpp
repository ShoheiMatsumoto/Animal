// �C���N���[�h

#include "Image.h"

CImage::CImage(void)
{
}


CImage::~CImage(void)
{
}

//==============================
//�C�j�V�����C�U�i���ʂ́j
//==============================
bool	CImage::InitializeN(LPCTSTR pszFName)
{
	//2D�|���S���p�e�N�X�`���̃��[�h
	if(pszFName == NULL)
	{
		m_pTexture = NULL;
	}
	else if(FAILED(D3DXCreateTextureFromFile(CGraphics::GetDevice() , pszFName , &m_pTexture)))
	{
		MessageBox(NULL , _T("�t�@�C���̓ǂݍ��݂Ɏ��s���܂���") , pszFName , MB_OK);
		return false;
	}
	
	// ���摜�̃T�C�Y���̏���ێ�����
	D3DXGetImageInfoFromFile(pszFName, &m_Info);
	m_vSize.x = m_Info.Width;
	m_vSize.y = m_Info.Height;
	m_vHalfSize.x = m_vSize.x / 2.0f;
	m_vHalfSize.y = m_vSize.y / 2.0f;

	// 2�̗ݏ�ɕϊ����ꂽ��̉摜�T�C�Y���̏����擾
	m_pTexture->GetLevelDesc(0, &m_Desc);

	return true;
}

//==============================
//�C�j�V�����C�U�i���F���߁j
//==============================
bool CImage::Initialize(LPCTSTR pszFName)
{
	

	// �e�N�X�`���t�@�C����ǂݍ���
	D3DXIMAGE_INFO info;

	if(pszFName == NULL)
	{
		m_pTexture = NULL;
	}
	else if(D3DXCreateTextureFromFileExA(CGraphics::GetDevice(),
		pszFName,
		D3DX_DEFAULT, 
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0, 
		D3DFMT_UNKNOWN, 
		D3DPOOL_MANAGED, 
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_ARGB(255, 0, 255, 0),  // �ΐF�𓧉ߐF�Ƃ���
		&info, 
		NULL, 
		&m_pTexture))
	{
		MessageBox(NULL , _T("�t�@�C���̓ǂݍ��݂Ɏ��s���܂���") , pszFName , MB_OK);
		return false;
	}
	
	// ���摜�̃T�C�Y���̏���ێ�����
	D3DXGetImageInfoFromFile(pszFName, &m_Info);
	m_vSize.x = m_Info.Width;
	m_vSize.y = m_Info.Height;
	m_vHalfSize.x = m_vSize.x / 2.0f;
	m_vHalfSize.y = m_vSize.y / 2.0f;

	// 2�̗ݏ�ɕϊ����ꂽ��̉摜�T�C�Y���̏����擾
	m_pTexture->GetLevelDesc(0, &m_Desc);

	return true;
}

//==============================
//�ǂݍ��ݏ���
//==============================
CImage* CImage::Create(LPCTSTR pszFName, int nPattern)
{
	CImage* pImage = new CImage();
	if(pImage)
	{
		if(!pImage->InitializeN(pszFName))
		{
			SAFE_DELETE(pImage);
		}
	}

	pImage->m_nPattern = nPattern;

	return pImage;
}


//==============================
//�I������
//==============================
void CImage::Release(void)
{
	//2D�|���S���p�e�N�X�`���̉��
	SAFE_RELEASE(m_pTexture);
	delete this;
}