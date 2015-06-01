// Title.cpp	

// インクルード
#include <stdio.h>
#include "SceneWkI.h"
#include "define.h"
#include "GameMgr.h"
#include "Input.h"
#include "MyCollision.h"
#include "WkFactoryI.h"
#include "Collision.h"



// コンストラクタ
CSceneWkI::CSceneWkI()
{
	
}

// デストラクタ
CSceneWkI::~CSceneWkI()
{
	
}

//--------------------------------------------------------
// タイトル生成
//--------------------------------------------------------
CSceneWkI* CSceneWkI::Create()
{
	CSceneWkI* pTitle = new CSceneWkI();		// タイトルインスタンス生成

	if(!pTitle->Initialize())
		SAFE_DELETE(pTitle);

	//delete pTitle;

	return pTitle;
}

//--------------------------------------------------------
// タイトル初期化
//--------------------------------------------------------
bool CSceneWkI::Initialize()
{
	// タイトルに使うもの用意
	//m_pGraph = pGraph;

	// テクスチャマネージャ生成
	m_pTexMgr = m_pTexMgr->Create(T_TEX_MAX);
	
	// テクスチャエントリー
	m_pTexMgr->Entry(T_TEX_0, _T("../Data/Image/ButtonCircle.png"), 1);
	m_pTexMgr->Entry(T_TEX_MOON, _T("../Data/Image/moon.png"), 1);

	// オブジェマネージャ生成
	m_pObjMgr = m_pObjMgr->Create();

	// ファクトリ生成
	m_pFactory = CWkFactoryI::Create();

	// オブジェクト生成
	// 2D
	for(int i = 0; i < 1; i++)
	{
		//m_pFactory->Request2D(OBJ2D_TEST2D, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	}
	/*m_pFactory->Request2D(OBJ2D_TEST0, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	m_pFactory->Request2D(OBJ2D_TEST1, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	m_pFactory->Request2D(OBJ2D_TEST2, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	m_pFactory->Request2D(OBJ2D_TEST3, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
*/
	// 3D
	D3DXVECTOR3 pv;
	int ChipX, ChipY;
	ChipX = SCREEN_WIDTH / CHIPSIZE_X;
	ChipY = SCREEN_HEIGHT / CHIPSIZE_Y;

	int ni = ChipY / 2;
	int iamari = ChipY % 2;
	
	int nj = ChipX / 2;
	int jamari = ChipX % 2;
	
	float sx = CHIPSIZE_X;
	float sy = CHIPSIZE_Y;

	float rx = sx / 2.0f;
	float ry = sy / 2.0f;

	
	if(iamari == 1)
		ry = 0.0f;

	// 敷き詰める
	for(int j = -nj; j < nj + jamari; j++)
	{
		pv = D3DXVECTOR3(sx * j + rx, -288.0f + CHIPSIZE_X, j * 10.0f);
		m_pFactory->Request3D(OBJ3D_TESTBILL, pv);

	}
	

	for(int i = 0; i < 1; i++)
	{
		m_pFactory->Request3D(OBJ3D_MOON, D3DXVECTOR3(32.0f * i, -288.0f + CHIPSIZE_X, 0.0f));
	}
	

	// カメラ設定
	// カメラを置く位置を求める(平行投影するから意味が無くなったかも)
	D3DXVECTOR3 vNScreentoCam = D3DXVECTOR3(0.0f, 1.0f, 0.0f); // スクリーンからカメラ位置へのベクトル
	D3DXVECTOR3 vNFrametoCam;

	// スクリーン淵からカメラ座標へのベクトルを求める
	float rot = 90.0f - FOVY / 2.0f;		// スクリーン淵からカメラへの角度
	float x = -cos(rot * 3.14 / 180.0f);	// Xベクトル
	float y = sin(rot * 3.14 / 180.0f);		// 本来はZ軸だがYとして扱う
	vNFrametoCam = D3DXVECTOR3(x, y, 0.0f);	// 淵からカメラへのベクトル

	// スクリーン中心からカメラ、淵からカメラへの2直線の交点を求める
	CMyCollision MyCol;		// 判定インスタンス
	Segment Seg1, Seg2;		// 線分要素入れ
	D3DXVECTOR3 vCross;		// 交点取得用

	Seg1.vSPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 中心からカメラ（座標）
	vNScreentoCam *= 3000.0f;						// ベクトルを十分に伸ばす
	Seg1.vVec = vNScreentoCam;						// ベクトル

	Seg2.vSPos = D3DXVECTOR3( (float)SCREEN_HEIGHT / 2.0f, 0.0f, 0.0f);		// 淵座標
	vNFrametoCam *= 3000.0f;						
	Seg2.vVec = vNFrametoCam;

	// 交点を求める
	bool bCroos = MyCol.CollisionLineToLine2D(Seg1, Seg2, &vCross);
	
	// 交点をカメラ座標とする
	g_z = vCross.y;

	m_pCameraBase = m_pCameraBase->Create();
	D3DXMATRIX mat = m_pCameraBase->GetMatrix();
	D3DXVECTOR3 vAdPos = D3DXVECTOR3(0.0f, 0.0f, g_z);	
	D3DXVECTOR3 vLook =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_camera.SetAdjustPos(vAdPos);
	m_camera.SetLookPos(vLook);
	m_camera.SetEffect(C_EFFECT_NORMAL);

	// サウンド初期化
	// サウンドファクトリ生成
	m_pSoundMgr = m_pSoundMgr->Create(T_SOUND_MAX);

	// エントリー(IDはシーンのヘッダではなく、ファクトリのヘッダに記入した方を記述)
	m_pSoundMgr->Entry(SOUND_TEST, _T("../Data/Sound/BGM/bgm_fall.wav"));

	//m_pSoundMgr->RequestSound(SOUND_TEST, SOUND_ONE);
	//m_pSoundMgr->RequestSound(SOUND_TEST, SOUND_LOOP);

	return true;


}

//--------------------------------------------------------
// タイトル更新
//--------------------------------------------------------
void CSceneWkI::Update()
{
#ifdef _DEBUG
	if(GETINPUT->GetKey(KEY_PRS, DIK_1))
	{
		m_pGraph->SetProjection(PROJ_ORT);
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_2))
	{
		m_pGraph->SetProjection(PROJ_PERS);
	}

	if(GETINPUT->GetKey(KEY_PRS, DIK_A))
	{
		g_fX -= 1.0f;
		m_camera.SetAdjustPos(D3DXVECTOR3(g_fX,g_fY, g_z));
		m_camera.SetLookPos(D3DXVECTOR3(g_fX,g_fY, 0.0f));
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_D))
	{
		g_fX += 1.0f;
		m_camera.SetAdjustPos(D3DXVECTOR3(g_fX,g_fY, g_z));
		m_camera.SetLookPos(D3DXVECTOR3(g_fX,g_fY, 0.0f));
	}

	if(GETINPUT->GetKey(KEY_PRS, DIK_W))
	{
		g_fY += 1.0f;
		m_camera.SetAdjustPos(D3DXVECTOR3(g_fX,g_fY, g_z));
		m_camera.SetLookPos(D3DXVECTOR3(g_fX,g_fY, 0.0f));
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_S))
	{
		g_fY -= 1.0f;
		m_camera.SetAdjustPos(D3DXVECTOR3(g_fX,g_fY, g_z));
		m_camera.SetLookPos(D3DXVECTOR3(g_fX,g_fY, 0.0f));
	}

	if(GETINPUT->GetKey(KEY_PRS, DIK_Q))
	{
		g_fOrt += 0.01;
		if(g_fOrt > 1.0f)
			g_fOrt = 1.0f;
		m_pGraph->SetOrt(g_fOrt);
		/*g_z += 1.0f;
		m_camera.SetAdjustPos(D3DXVECTOR3(g_fX,g_fY, g_z));*/
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_E))
	{
		g_fOrt -= 0.01f;
		if(g_fOrt < 0.0f)
			g_fOrt = 0.0f;
		m_pGraph->SetOrt(g_fOrt);
		/*g_z -= 1.0f;
		m_camera.SetAdjustPos(D3DXVECTOR3(g_fX,g_fY, g_z));
		m_camera.SetLookPos(D3DXVECTOR3(g_fX,g_fY, 0.0f));*/
	}
#endif
	// シーン切り替え制御
	if(m_bSC)
	{
		if(m_pFadeOut->AskFin())		// フェードが終わったか
		{
			CGameMgr::GetThis()->SetScene(SCENE_STAGE);		// シーン切り替え
		}
	}
	else
	{
		if(GETINPUT->GetKey(KEY_TRG, DIK_SPACE))
		{
			m_pFadeOut = m_pFadeOut->Create(T_TEX_CARTEN);		// フェードアウト生成
			m_bSC = true;
			//CGameMgr::m_pGameMgr->SetScene(SCENE_STAGE);
		}
	}

	// 全オブジェクト更新
	m_pObjMgr->AllUpdate();		// 3D2Dまとめて更新

	// あたり判定まとめ走査
	CheckRunHit();
	
	// カメラ更新
	m_camera.Update(&m_pCameraBase->GetMatrix());
}

//--------------------------------------------------------
// タイトルの描画
//--------------------------------------------------------
void CSceneWkI::Draw()
{
	m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
	TCHAR	str[256];
	
	//----- ここに描画処理
	
	// カメラ設定
	m_camera.Draw();

	// 全オブジェクト描画
	m_pObjMgr->AllDraw();		// ２D３Dまとめて描画

	

	// 各種デバッグ用数値表示
	_stprintf(str, _T("稲垣ワークスペース\n"));
	lstrcat(m_szDebug, str);
	
	// デバッグ文字列描画
	m_pGraph->DrawText((int)g_fX, (int)g_fY, m_szDebug);
	
}

void CSceneWkI::Release()
{
	// テクスチャ解放
	m_pTexMgr->Release();
	
	// モデル解放
	for(int i = 0; i < T_MESH_MAX; i++)
	{
		m_ppMesh[i]->Finalize();
	}
	SAFE_DELETE_ARRAY(m_ppMesh);		// 入れ物解放
	
	// マネージャ解放
	m_pObjMgr->Release();
	//SAFE_DELETE(m_pObjMgr);

	// カメラベース解放
	SAFE_DELETE(m_pCameraBase);

	//m_pFadeIn->Create();
	//m_pFadeOut->Release();

}

void CSceneWkI::SetChangeScene()
{

}

// あたり判定まとめ
void CSceneWkI::CheckRunHit()
{
	// あたり判定走査
	Collision Col;
	
	Col.CollSquareRunBill(m_pObjMgr->GetListTop3D(OBJ3DGROUP_PLAYER), m_pObjMgr->GetListTop3D(OBJ3DGROUP_MAP));
}






//=============================================
// EOF
//=============================================