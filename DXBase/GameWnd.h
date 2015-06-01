//=======================================================================================
//
//	  ゲーム用ウィンドウ クラス定義
//
//=======================================================================================
#pragma once

#include "Window.h"
#include "Graphics.h"
#include "SceneBase.h"
#include "GameMgr.h"
#include "Input.h"
#include "Sound.h"

#define FRAME_RATE		(1000/60)	// フレームレート

class CGameWindow : public CWindow
{
private:
	CGraphics*	m_pGraph;			// 描画デバイス クラス
	// CScene*		m_pScene;			// シーン
	CGameMgr*	m_pGameMgr;			// ゲームマネージャインスタンス？
	CInput*		m_pInput;			// 入力インスタンス
	CSound*		m_pSound;			// サウンドインスタンス

	bool		m_bWindow;			// ウィンドウ / フルスクリーン

	DWORD		m_dwExecLastTime;	// FPS計測用
	DWORD		m_dwFPSLastTime;
	DWORD		m_dwFrameCount;

	HIMC		m_himc;

public:
	bool InitInstance();
	int ExitInstance();
	bool OnIdle(long lCount);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	bool OnEraseBkgnd(HDC hdc);
	bool OnSetCursor(HWND hwnd, UINT nHitTest, UINT uMouseMsg);
};

//=======================================================================================
//	End of File
//=======================================================================================