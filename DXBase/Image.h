// テクスチャ管理クラス宣言
#pragma once

#include "main.h"
#include "Graphics.h"

enum
{
	TEX_A = 0,
	TEX_B,

	TEX_MAX
};

// ２Dテクスチャ管理クラス
class CImage
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DXVECTOR2			m_vSize;
	D3DXVECTOR2			m_vHalfSize;
	int					m_nPattern;
	D3DSURFACE_DESC		m_Desc;					// テクスチャのサイズ等の情報を保持する
	D3DXIMAGE_INFO		m_Info;					// 元画像のサイズ等の情報を保持する

public:
	CImage(void);
	virtual ~CImage(void);

	static	CImage*		Create(LPCTSTR pszFName, int nPattern);
	bool	Initialize(LPCTSTR pszFName);
	bool	InitializeN(LPCTSTR pszFName);

	void				Release(void);				// 解放処理
	D3DXVECTOR2*		GetSize()		{return &m_vSize;}
	D3DXVECTOR2*		GetHalfSize()	{return &m_vHalfSize;}
	LPDIRECT3DTEXTURE9	GetTexture()	{return m_pTexture;}
	int					GetPattern()	{return m_nPattern;}
	
};

