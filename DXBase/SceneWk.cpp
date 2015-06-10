// Title.cpp	

// インクルード
#include <stdio.h>
#include "SceneWk.h"
#include "define.h"
#include "GameMgr.h"
#include "Input.h"
#include "MyCollision.h"
#include "WkFactory.h"
#include "Collision.h"
#include "AnimalColl.h"


// コンストラクタ
CSceneWk::CSceneWk()
{
	
}

// デストラクタ
CSceneWk::~CSceneWk()
{
	
}

//--------------------------------------------------------
// タイトル生成
//--------------------------------------------------------
CSceneWk* CSceneWk::Create()
{
	CSceneWk* pTitle = new CSceneWk();		// タイトルインスタンス生成

	if(!pTitle->Initialize())
		SAFE_DELETE(pTitle);

	//delete pTitle;

	return pTitle;
}

//--------------------------------------------------------
// タイトル初期化
//--------------------------------------------------------
bool CSceneWk::Initialize()
{
	// タイトルに使うもの用意
	//m_pGraph = pGraph;

	// テクスチャマネージャ生成
	m_pTexMgr = m_pTexMgr->Create(T_TEX_MAX);
	
	// テクスチャエントリー
	m_pTexMgr->Entry(WK_TEX_0, _T("../Data/Image/ButtonCircle.png"), 1);
	m_pTexMgr->Entry(WK_TEX_MOON, _T("../Data/Image/moon.png"), 1);
	m_pTexMgr->Entry(WK_TEX_SQUARE, _T("../Data/Image/UI/ButtonSquare.png"), 1);
	m_pTexMgr->Entry(WK_TEX_PLAYER, _T("../Data/Image/player_def.png"), 1);
	m_pTexMgr->Entry(WK_TEX_SLOPE, _T("../Data/Image/slope.png"), 1);

	m_pTexMgr->Entry(WK_TEX_NEZU, _T("../Data/Image/Animaru/nezu.png"), 1);
	m_pTexMgr->Entry(WK_TEX_USHI, _T("../Data/Image/Animaru/ushi.png"), 1);
	m_pTexMgr->Entry(WK_TEX_TORA, _T("../Data/Image/Animaru/tora.png"), 1);
	m_pTexMgr->Entry(WK_TEX_MIMI, _T("../Data/Image/Animaru/mimi.png"), 1);
	m_pTexMgr->Entry(WK_TEX_TATSU, _T("../Data/Image/Animaru/tatsu.png"), 1);
	m_pTexMgr->Entry(WK_TEX_HEBI, _T("../Data/Image/Animaru/hebi.png"), 1);
	m_pTexMgr->Entry(WK_TEX_UMA, _T("../Data/Image/Animaru/uma.png"), 1);
	m_pTexMgr->Entry(WK_TEX_MERRY, _T("../Data/Image/Animaru/merry.png"), 1);
	m_pTexMgr->Entry(WK_TEX_SARU, _T("../Data/Image/Animaru/saru.png"), 1);
	m_pTexMgr->Entry(WK_TEX_TORI, _T("../Data/Image/Animaru/tori.png"), 1);
	m_pTexMgr->Entry(WK_TEX_INU, _T("../Data/Image/Animaru/inu.png"), 1);
	m_pTexMgr->Entry(WK_TEX_URI, _T("../Data/Image/Animaru/uri.png"), 1);

	// オブジェマネージャ生成
	m_pObjMgr = m_pObjMgr->Create();

	// ファクトリ生成
	m_pFactory = CWkFactory::Create();

	// オブジェクト生成
	// 2D
	for(int i = 0; i < 1; i++)
	{
		//m_pFactory->Request2D(OBJ2D_TEST2D, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	}
	/*m_pFactory->Request2D(OBJ2D_TEST0, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	m_pFactory->Request2D(OBJ2D_TEST1, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	m_pFactory->Request2D(OBJ2D_TEST2, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	m_pFactory->Request2D(OBJ2D_TEST2D, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	*/
	// 3D
	D3DXVECTOR3 pv;
	int ChipX, ChipY;
	ChipX = (int)(SCREEN_WIDTH / CHIPSIZE_X);
	ChipY = (int)(SCREEN_HEIGHT / CHIPSIZE_Y);

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
	for(int j = -6; j < 0; j++)
	{
		pv = D3DXVECTOR3(sx * j - 96.0f, -288.0f + 32.0f, 10.0f);
		m_pFactory->Request3D(WK_OBJ3D_MPSQUARE, WK_TEX_SQUARE, pv);

	}
	m_pFactory->Request3D(WK_OBJ3D_MPSQUARE, WK_TEX_SQUARE, D3DXVECTOR3(-288.0f, -224.0f + 32.0f, 10.0f));
	m_pFactory->Request3D(WK_OBJ3D_MPRDOWN, WK_TEX_SLOPE, D3DXVECTOR3(0.0f, -288.0f + 32.0f, 10.0f));
	m_pFactory->Request3D(WK_OBJ3D_MPSQUARE, WK_TEX_SQUARE, D3DXVECTOR3(160.0f, -352.0f + 32.0f, 10.0f));
	m_pFactory->Request3D(WK_OBJ3D_MPRUP, WK_TEX_SLOPE, D3DXVECTOR3(320.0f, -288.0f + 32.0f, 10.0f));

	// プレイヤー
	m_pFactory->Request3D(WK_OBJ3D_PLAYER, WK_TEX_PLAYER, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	

	// カメラ設定
	// カメラを置く位置を求める(平行投影するから意味が無くなったかも)
	D3DXVECTOR3 vNScreentoCam = D3DXVECTOR3(0.0f, 1.0f, 0.0f); // スクリーンからカメラ位置へのベクトル
	D3DXVECTOR3 vNFrametoCam;

	// スクリーン淵からカメラ座標へのベクトルを求める
	float rot = 90.0f - FOVY / 2.0f;		// スクリーン淵からカメラへの角度
	float x = (float)(-cos(rot * 3.14 / 180.0f));	// Xベクトル
	float y = (float)(sin(rot * 3.14 / 180.0f));		// 本来はZ軸だがYとして扱う
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
	m_pCameraBase = m_pObjMgr->GetListTop3D(OBJ3DGROUP_PLAYER);

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
	// m_pSoundMgr->RequestSound(SOUND_TEST, SOUND_LOOP);

	return true;


}

//--------------------------------------------------------
// タイトル更新
//--------------------------------------------------------
void CSceneWk::Update()
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
		g_fOrt += 0.01f;
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
	//// シーン切り替え制御
	//if(m_bSC)
	//{
	//	if(m_pFadeOut->AskFin())		// フェードが終わったか
	//	{
	//		CGameMgr::GetThis()->SetScene(SCENE_STAGE);		// シーン切り替え
	//	}
	//}
	//else
	//{
	//	if(GETINPUT->GetKey(KEY_TRG, DIK_SPACE))
	//	{
	//		m_pFadeOut = m_pFadeOut->Create(T_TEX_CARTEN);		// フェードアウト生成
	//		m_bSC = true;
	//		//CGameMgr::m_pGameMgr->SetScene(SCENE_STAGE);
	//	}
	//}

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
void CSceneWk::Draw()
{
	m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
	TCHAR	str[256];
	
	// 各種デバッグ用数値表示
	_stprintf(str, _T("松本ワークスペース\n"));
	lstrcat(m_szDebug, str);
	
	// デバッグ文字列描画
	m_pGraph->DrawText((int)10, (int)20, m_szDebug);

	//----- ここに描画処理
	
	// カメラ設定
	m_camera.Draw();

	// 全オブジェクト描画
	m_pObjMgr->AllDraw();		// ２D３Dまとめて描画

	

	
	
}

void CSceneWk::Release()
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

void CSceneWk::SetChangeScene()
{

}

// あたり判定まとめ
void CSceneWk::CheckRunHit()
{
	// あたり判定走査
	Collision Col;
	CAnimalColl ACol;
	
	//Col.CollSquareRunBill(m_pObjMgr->GetListTop3D(OBJ3DGROUP_PLAYER), m_pObjMgr->GetListTop3D(OBJ3DGROUP_MAP));
	ACol.CheckRunToMap(m_pObjMgr->GetListTop3D(OBJ3DGROUP_PLAYER), m_pObjMgr->GetListTop3D(OBJ3DGROUP_MAP));
}






//=============================================
// EOF
//=============================================