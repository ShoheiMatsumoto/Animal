// インクルード

#include "Image.h"

CImage::CImage(void)
{
}


CImage::~CImage(void)
{
}

//==============================
//イニシャライザ（普通の）
//==============================
bool	CImage::InitializeN(LPCTSTR pszFName)
{
	//2Dポリゴン用テクスチャのロード
	if(pszFName == NULL)
	{
		m_pTexture = NULL;
	}
	else if(FAILED(D3DXCreateTextureFromFile(CGraphics::GetDevice() , pszFName , &m_pTexture)))
	{
		MessageBox(NULL , _T("ファイルの読み込みに失敗しました") , pszFName , MB_OK);
		return false;
	}
	
	return true;
}

//==============================
//イニシャライザ（黒色透過）
//==============================
bool CImage::Initialize(LPCTSTR pszFName)
{
	

	// テクスチャファイルを読み込む
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
		D3DCOLOR_ARGB(255, 0, 255, 0),  // 緑色を透過色とする
		&info, 
		NULL, 
		&m_pTexture))
	{
		MessageBox(NULL , _T("ファイルの読み込みに失敗しました") , pszFName , MB_OK);
		return false;
	}
	
	// 元画像のサイズ等の情報を保持する
	D3DXGetImageInfoFromFile(pszFName, &m_Info);
	m_vSize.x = m_Info.Width;
	m_vSize.y = m_Info.Height;
	m_vHalfSize.x = m_vSize.x / 2.0f;
	m_vHalfSize.y = m_vSize.y / 2.0f;

	// 2の累乗に変換された後の画像サイズ等の情報を取得
	m_pTexture->GetLevelDesc(0, &m_Desc);

	return true;
}

//==============================
//読み込み処理
//==============================
CImage* CImage::Create(LPCTSTR pszFName, int nPattern)
{
	CImage* pImage = new CImage();
	if(pImage)
	{
		if(!pImage->Initialize(pszFName))
		{
			SAFE_DELETE(pImage);
		}
	}

	pImage->m_nPattern = nPattern;

	return pImage;
}


//==============================
//終了処理
//==============================
void CImage::Release(void)
{
	//2Dポリゴン用テクスチャの解放
	SAFE_RELEASE(m_pTexture);
	delete this;
}