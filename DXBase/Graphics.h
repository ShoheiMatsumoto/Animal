//=======================================================================================
//
//	  DirectX Graphics9 クラス定義
//
//=======================================================================================
#pragma once

#include "main.h"

#define FOVY			60.0f								// 視野角
#define NEAR_CLIP		0.1f								// ニアクリップを行う距離
#define FAR_CLIP		10000.0f							// ファークリップを行う距離

//#define GETDEVICE (CGraphics::GetDevice())
enum
{
	PROJ_PERS = 1,
	PROJ_ORT,

	PROJ_MAX
};

class CGraphics
{
private:
	LPDIRECT3D9					m_pD3D;			// Direct3D9 オブジェクト
	static LPDIRECT3DDEVICE9	m_pDevice;		// Direct3DDevice9 オブジェクト
	D3DPRESENT_PARAMETERS		m_D3DPP;		// PRESENT PARAMETERS
	LPD3DXFONT					m_pFont;		// D3DXFont オブジェクト

	D3DXMATRIX					m_MatView;		// ビュー マトリックス
	D3DXMATRIX					m_MatProj;		// 射影マトリックス

	HWND						m_hWnd;			// ウィンドウ ハンドル
	int							m_nWidth;		// 表示領域幅
	int							m_nHeight;		// 表示領域高さ
	float						m_fFovy;		// 画角

public:
	static LPDIRECT3DDEVICE9 GetDevice() {return m_pDevice;}

	static CGraphics* Create(HWND hWnd, int nWidth, int nHeight, bool bWindow);
	void Release();
	bool Begin();
	void End();
	void SwapBuffer();
	void DrawText(int nX, int nY, LPCTSTR psz);

	void SetProjection(int n);

	// ゲッター

	// セッター
	void SetFovy(float fFovy);		// 画角の変更
	void SetOrt(float fRate);		// 平行投影拡大率変更（0.0~1.0）
	
private:
	bool Initialize(HWND hWnd, int nWidth, int nHeight, bool bWindow);
	void Finalize();
};

//=======================================================================================
//	End of File
//=======================================================================================