// ステージ管理クラス

// インクルード
#include "define.h"
#include "Stage.h"
#include "GameMgr.h"
#include "Input.h"

CStage* CStage::m_pThis = NULL;

int g_n = 0;
// コンストラクタ
CStage::CStage(void)
{
	m_pThis = this;
}

// デストラクタ
CStage::~CStage(void)
{
}

//--------------------------------------------------------
// ステージ生成
//--------------------------------------------------------
void CStage::Create()
{
	CStage* pStage = new CStage();		// タイトルインスタンス生成

	pStage->Initialize();
}

//--------------------------------------------------------
// ステージ初期化
//--------------------------------------------------------
void CStage::Initialize()
{
	// ステージに使うもの用意
	
	// テクスチャ読み込み

	// テクスチャ情報読み込み

	// ２Dオブジェ生成
	//m_pTest2D->Create(TEX_MOON);

	// ビルボード

	// メッシュ読み込み
	
	// カメラ
	m_pCameraBase = m_pCameraBase->Create();
	D3DXMATRIX mat = m_pCameraBase->GetMatrix();
	D3DXVECTOR3 vAdPos = D3DXVECTOR3(0.0f, 5.0f, 20.0f);
	D3DXVECTOR3 vLookPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_camera.SetAdjustPos(vAdPos);
	m_camera.SetLookPos(vLookPos);
	m_camera.SetEffect(C_EFFECT_NORMAL);

	// フェード
	m_pFadeIn->Create(S_TEX_CARTEN);
}

void CStage::InitReturn()
{
	// フェード
	m_pFadeIn->Create(S_TEX_CARTEN);
}

// 更新
void CStage::Update()
{
	if(m_bSC)
	{
		if(m_pFadeOut->AskFin())
		{
			CGameMgr::GetThis()->SetScene(SCENE_RESULT);

			//m_pGlassPoint = m_pGlassPoint->OrgCreate();
			//m_pGlassPoint->GlassCreate();
		}
	}
	else
	{
		if(GETINPUT->GetKey(KEY_TRG, DIK_SPACE))
		{
			m_pFadeOut = m_pFadeOut->Create(S_TEX_CARTEN);
			m_bSC = true;
		}
	}

	// 全オブジェクト更新
	m_pObjMgr->AllUpdate();		// 3D2Dまとめて更新
	
	// ビルボードオブジェへのビューマトリックスセット
	//CTestBill::SetMatView(m_camera.GetMatView());		
	
	// カメラ座標セット
	m_camera.Update(&m_pCameraBase->GetMatrix());

}

void CStage::Draw()
{
	m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
	TCHAR	str[256];

	// カメラ
	m_camera.Draw();

	// 全オブジェクト描画
	m_pObjMgr->AllDraw();		// ２D３Dまとめて描画

	_stprintf(str, _T("ステージ\n"));
	lstrcat(m_szDebug, str);
	
	// デバッグ文字列描画
	m_pGraph->DrawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, m_szDebug);
	
	
}

//----------------------------------
// 解放処理
//-------------------------------------
void CStage::Release()
{
	// テクスチャ解放
	m_pTexMgr->Release();

	// モデル解放
	for(int i = 0; i < S_MESH_MAX; i++)
	{
		m_ppMesh[i]->Finalize();
	}
	SAFE_DELETE_ARRAY(m_ppMesh);		// 入れ物解放
	
	// マネージャ解放
	m_pObjMgr->Release();
	SAFE_DELETE(m_pObjMgr);

	// カメラベース解放
	SAFE_DELETE(m_pCameraBase);

	//m_pFadeIn->Create();
	//m_pFadeOut->Release();
}



// EOF