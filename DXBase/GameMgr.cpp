
// インクルード
#include <stdio.h>
#include "GameMgr.h"
#include "define.h"
#include "Title.h"
#include "Stage.h"
#include "Input.h"

// グローバル
DWORD	CGameMgr::m_dwNewScene = SCENE_TITLE;		// 新シーン
CGameMgr*		CGameMgr::m_pGameMgr = NULL;			// これを指すポインタ

CGameMgr::CGameMgr(void)
{
	m_FPS		 = 0;				// FPS表示変数初期化
	m_dwOldScene = SCENE_START;		// 立ち上げからスタート

}


CGameMgr::~CGameMgr(void)
{

}


//---------------------------------------------------------------------------------------
// マネージャーインスタンス生成
//---------------------------------------------------------------------------------------
CGameMgr* CGameMgr::Create(CGraphics* pGraph)
{
	CGameMgr* pMgr = new CGameMgr();
	if (pMgr) {
		if (!pMgr->Initialize(pGraph)) {
			SAFE_DELETE(pMgr);
		}
	}
	return pMgr;
}

//---------------------------------------------------------------------------------------
// デバイス、リソース初期化
//---------------------------------------------------------------------------------------
bool CGameMgr::Initialize(CGraphics* pGraph)
{
	// グラフィックデバイス共有
	m_pGraph = pGraph;

	// シーンインスタンス生成
	CSceneBase::CreateScene(m_pGraph);
	m_pStScene = CSceneBase::GetThis();
	if (!m_pStScene) return false;



	return true;
}

//---------------------------------------------------------------------------------------
// デバイス、リソース解放
//---------------------------------------------------------------------------------------
void CGameMgr::Finalize()
{
	//-------- ゲーム用オブジェクトの後始末
	/*for (int i = 0; i < MAX_MESH; i++) {
		m_mesh[i].Finalize();
	}
	*/
}

//---------------------------------------------------------------------------------------
// 解放
//---------------------------------------------------------------------------------------
void CGameMgr::Release()
{
	Finalize();
	delete this;
}

//---------------------------------------------------------------------------------------
// ゲーム描画処理（メインループからコールされる）
//---------------------------------------------------------------------------------------
void CGameMgr::Render()
{
	if (m_pGraph->Begin()) {	// 描画開始
	
		// シーンレンダリング
		m_pStScene->Render();
		Draw();					// 描画処理

		m_pGraph->End();		// 描画終了
	}
	m_pGraph->SwapBuffer();		// バックバッファ入替
}

//-------------------------------------------------
// ゲーム更新
//-------------------------------------------------
void CGameMgr::Update()
{
	if(GETINPUT->GetKey(KEY_TRG, DIK_0))
	{
		SetScene(SCENE_RETITLE);
	}

	// ステート変更管理
	SceneMgr();

	// シーンの更新
	m_pStScene->Update();
}

//----------------------------------------------------
// シーン切り替え管理
//----------------------------------------------------
void CGameMgr::SceneMgr()
{
	int nID = 0;

	// 切り替えチェック
	if(m_dwNewScene == m_dwOldScene)
		return;

	// 管理変数更新
	m_dwOldScene = m_dwNewScene;
	
	// 各シーンの生成
	switch(m_dwNewScene)
	{
	case SCENE_RETITLE:
		m_pStScene->Release();
	
		CTitle::Create();		// タイトル生成
		break;
	case SCENE_TITLE:
		CTitle::Create();		// タイトル生成
		break;

	case SCENE_STAGE:
		m_pStScene->Release();
		CStage::Create();		// ステージ生成
		break;

	default:

		break;
	}

	//m_pStScene = CScene::GetThis();
	// 管理変数更新
	m_dwOldScene = m_dwNewScene;

	
}

//-------------------------------------------------------
// 描画
//--------------------------------------------------------
void CGameMgr::Draw()
{
	m_szDebug[0] = _T('\0');	// デバッグ文字列初期化

	// FPS を画面に描画するための文字列を作成
	TCHAR	str[256];
	_stprintf(str, _T("FPS = %d\n"), m_FPS);
	lstrcat(m_szDebug, str);

	//----- ここに描画処理

	// デバッグ文字列描画
	m_pGraph->DrawText(10, 2, m_szDebug);
}

// シーンのセット
void CGameMgr::SetScene(DWORD dwScene)
{
	m_dwNewScene = dwScene;
	
}


