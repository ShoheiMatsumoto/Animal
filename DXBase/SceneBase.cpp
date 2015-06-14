//=======================================================================================
//
//	  シーン クラス
//
//=======================================================================================
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <windows.h>
#include <stdio.h>
#include "GameWnd.h"
#include "SceneBase.h"
#include "Input.h"


// スタティック初期化
CSceneBase* CSceneBase::m_pThis = NULL;
CSceneBase* CSceneBase::m_pCurScene = NULL;
CSceneBase* CSceneBase::m_pStacTop = NULL;
CGraphics* CSceneBase::m_pGraph = NULL;

//---------------------------------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------------------------------
CSceneBase::CSceneBase()
{
	// m_bSphere	 = true;
	//m_nSwCamera	 = 0;
	// m_nSceneID = SCENE_TITLE;
	
	//m_dwNewStateID = SCENE_TITLE;
	//m_dwOldStateID = SCENE_START;
	
	// 生成したものを現在シーンとする
	m_bSC = false;
	m_pCurScene = this;

}

// シーンをスタックする
void CSceneBase::StacScene()
{
	// 現在シーンがあったら
	if(m_pCurScene)
	{
		// スタックのトップになにかあれば
		if(m_pStacTop)		
		{
			m_pCurScene->m_pStacPrev = m_pStacTop;		// 現在シーンの前がトップ
			m_pStacTop = m_pCurScene;					// 現在シーンを次のトップに
		}
		else
		{
			m_pStacTop = m_pCurScene;		// 現在シーンをトップに登録
		}
	}	
	else
	{
		// エラー処理

	}
}

// シーンをポップする
void CSceneBase::PopScene()
{
	// トップに何かあったら
	if(m_pStacTop)
	{
		// 現在シーンの解放
		m_pCurScene->Release();

		// 現在シーンにトップを入れる
		m_pCurScene = m_pStacTop;

		// スタックされているシーンがあればずらす
		if(m_pStacTop->m_pStacPrev)
		{
			m_pStacTop = m_pStacTop->m_pStacPrev;		// トップより底にあるシーンをずらす
		}
	}	
	else
	{
		// エラー処理

	}
}
//---------------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------------
CSceneBase::~CSceneBase()
{
	

}

//---------------------------------------------------------------------------------------
// シーン生成
//---------------------------------------------------------------------------------------
CSceneBase* CSceneBase::CreateScene(CGraphics* pGraph)
{
	CSceneBase* pScene = new CSceneBase(0);
	if (pScene) {
		if (!pScene->InitializeScene(pGraph)) {
			SAFE_DELETE(pScene);
		}
	}

	m_pThis = pScene;
	//m_pScene = m_pThis;
	return pScene;
}

//---------------------------------------------------------------------------------------
// デバイス、リソース初期化
//---------------------------------------------------------------------------------------
bool CSceneBase::InitializeScene(CGraphics* pGraph)
{
	// 上位（GameWnd）からグラフィックデバイス共有
	m_pGraph = pGraph;		
	//m_pImage[TEX_CARTEN_BK]	= CImage::Create(_T("../Data/Image/Carten/CartenBk.png"), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 1);
	m_pCapWin = m_pCapWin->Create();

	return true;
}

//---------------------------------------------------------------------------------------
// デバイス、リソース解放
//---------------------------------------------------------------------------------------
void CSceneBase::Finalize()
{
	//-------- ゲーム用オブジェクトの後始末
	/*for (int i = 0; i < MAX_MESH; i++) {
		m_mesh[i].Finalize();
	}
	*/
}

//---------------------------------------------------------------------------------------
// シーン解放
//---------------------------------------------------------------------------------------
void CSceneBase::Release()
{
	// テクスチャの解放
	//SAFE_DELETE_ARRAY(m_ppImage);

	// マネージャの解放


	// 現在シーンの解放
	if(m_pCurScene)
	{
		SAFE_DELETE(m_pCurScene);
	}
}

//---------------------------------------------------------------------------------------
// ゲーム描画処理（GameMgr::Render()からコールされる）
//---------------------------------------------------------------------------------------
void CSceneBase::Render()
{
	//if (m_pGraph->Begin()) {	// 描画開始

		Draw();					// 描画処理

		// 画面キャプチャ（内部でやるやらないの判定）
		
		//if(m_pCapWin->ScreenShot())
		//	m_ppImage[TEX_SCREENSHOT]	= CImage::Create(_T("../Data/Image/scr_shot/scrshot.bmp"), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 1);

		//m_pGraph->End();		// 描画終了
	//}
	//m_pGraph->SwapBuffer();		// バックバッファ入替
}

//---------------------------------------------------------------------------------------
// シーン更新処理（GameMgr::Update()からコールされる）
//---------------------------------------------------------------------------------------
void CSceneBase::Update()
{
	//----- ここにゲーム本体処理
	
	// 各シーン更新
	m_pCurScene->Update();		// 
}

//---------------------------------------------------------------------------------------
// 描画処理（CGraphics::Render() からコールされる）
//---------------------------------------------------------------------------------------
void CSceneBase::Draw()
{
	//m_szDebug[0] = _T('\0');	// デバッグ文字列初期化

	
	// 全オブジェクト描画
	m_pCurScene->Draw();
}

//-----------------------------------
// 入力状態セット
//------------------------------------
void CSceneBase::SetInputData(bool bInp[INPTYPE][INP_BTN_MAX])
{
	// プレス*******************************************
	if(GETINPUT->GetKey(KEY_PRS, DIK_LEFT))		// 左
		bInp[KEY_PRS][INP_BTN_LEFT] = true;

	if(GETINPUT->GetKey(KEY_PRS, DIK_RIGHT))	// 右
		bInp[KEY_PRS][INP_BTN_RIGHT] = true;

	if(GETINPUT->GetKey(KEY_PRS, DIK_UP))		// 上
		bInp[KEY_PRS][INP_BTN_UP] = true;

	if(GETINPUT->GetKey(KEY_PRS, DIK_DOWN))		// 下
		bInp[KEY_PRS][INP_BTN_DOWN] = true;

	if(GETINPUT->GetKey(KEY_PRS, DIK_SPACE))	// space
		bInp[KEY_PRS][INP_BTN_SPACE] = true;

	if(GETINPUT->GetKey(KEY_PRS, DIK_LSHIFT))		// lshift
		bInp[KEY_PRS][INP_BTN_LSHIFT] = true;

	if(GETINPUT->GetKey(KEY_PRS, DIK_Q))		// Q
		bInp[KEY_PRS][INP_BTN_Q] = true;

	if(GETINPUT->GetKey(KEY_PRS, DIK_W))		// W
		bInp[KEY_PRS][INP_BTN_W] = true;

	if(GETINPUT->GetKey(KEY_PRS, DIK_E))		// E
		bInp[KEY_PRS][INP_BTN_E] = true;

	if(GETINPUT->GetKey(KEY_PRS, DIK_A))		// A
		bInp[KEY_PRS][INP_BTN_A] = true;
	
	if(GETINPUT->GetKey(KEY_PRS, DIK_S))		// S		
		bInp[KEY_PRS][INP_BTN_S] = true;

	if(GETINPUT->GetKey(KEY_PRS, DIK_D))		// D
		bInp[KEY_PRS][INP_BTN_D] = true;

	// トリガー***************************************:
	if(GETINPUT->GetKey(KEY_TRG, DIK_LEFT))		// 左
		bInp[KEY_TRG][INP_BTN_LEFT] = true;

	if(GETINPUT->GetKey(KEY_TRG, DIK_RIGHT))	// 右
		bInp[KEY_TRG][INP_BTN_RIGHT] = true;

	if(GETINPUT->GetKey(KEY_TRG, DIK_UP))		// 上
		bInp[KEY_TRG][INP_BTN_UP] = true;

	if(GETINPUT->GetKey(KEY_TRG, DIK_DOWN))		// 下
		bInp[KEY_TRG][INP_BTN_DOWN] = true;

	if(GETINPUT->GetKey(KEY_TRG, DIK_SPACE))	// space
		bInp[KEY_TRG][INP_BTN_SPACE] = true;

	if(GETINPUT->GetKey(KEY_TRG, DIK_LSHIFT))		// lshift
		bInp[KEY_TRG][INP_BTN_LSHIFT] = true;

	if(GETINPUT->GetKey(KEY_TRG, DIK_Q))		// Q
		bInp[KEY_TRG][INP_BTN_Q] = true;

	if(GETINPUT->GetKey(KEY_TRG, DIK_W))		// W
		bInp[KEY_TRG][INP_BTN_W] = true;

	if(GETINPUT->GetKey(KEY_TRG, DIK_E))		// E
		bInp[KEY_TRG][INP_BTN_E] = true;

	if(GETINPUT->GetKey(KEY_TRG, DIK_A))		// A
		bInp[KEY_TRG][INP_BTN_A] = true;
	
	if(GETINPUT->GetKey(KEY_TRG, DIK_S))		// S		
		bInp[KEY_TRG][INP_BTN_S] = true;

	if(GETINPUT->GetKey(KEY_TRG, DIK_D))		// D
		bInp[KEY_TRG][INP_BTN_D] = true;

	// リリース****************************************
	if(GETINPUT->GetKey(KEY_RLS, DIK_LEFT))		// 左
		bInp[KEY_RLS][INP_BTN_LEFT] = true;

	if(GETINPUT->GetKey(KEY_RLS, DIK_RIGHT))	// 右
		bInp[KEY_RLS][INP_BTN_RIGHT] = true;

	if(GETINPUT->GetKey(KEY_RLS, DIK_UP))		// 上
		bInp[KEY_RLS][INP_BTN_UP] = true;

	if(GETINPUT->GetKey(KEY_RLS, DIK_DOWN))		// 下
		bInp[KEY_RLS][INP_BTN_DOWN] = true;

	if(GETINPUT->GetKey(KEY_RLS, DIK_SPACE))	// space
		bInp[KEY_RLS][INP_BTN_SPACE] = true;

	if(GETINPUT->GetKey(KEY_RLS, DIK_LSHIFT))		// lshift
		bInp[KEY_RLS][INP_BTN_LSHIFT] = true;

	if(GETINPUT->GetKey(KEY_RLS, DIK_Q))		// Q
		bInp[KEY_RLS][INP_BTN_Q] = true;

	if(GETINPUT->GetKey(KEY_RLS, DIK_W))		// W
		bInp[KEY_RLS][INP_BTN_W] = true;

	if(GETINPUT->GetKey(KEY_RLS, DIK_E))		// E
		bInp[KEY_RLS][INP_BTN_E] = true;

	if(GETINPUT->GetKey(KEY_RLS, DIK_A))		// A
		bInp[KEY_RLS][INP_BTN_A] = true;
	
	if(GETINPUT->GetKey(KEY_RLS, DIK_S))		// S		
		bInp[KEY_RLS][INP_BTN_S] = true;

	if(GETINPUT->GetKey(KEY_RLS, DIK_D))		// D
		bInp[KEY_RLS][INP_BTN_D] = true;
}

//=======================================================================================
//	End of File
//=======================================================================================