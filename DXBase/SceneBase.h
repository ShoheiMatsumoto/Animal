//=======================================================================================
//
//	  シーン クラス宣言
//
//=======================================================================================
#pragma once

#include "Graphics.h"
#include "define.h"
#include "Mesh.h"		// CMeshクラス
#include "Camera.h"		// CCameraクラス
#include "TexMgr.h"
#include "ObjMgr.h"
#include "Input.h"
#include "CaptureWindow.h"
#include "SoundMgr.h"
#include "FactoryBase.h"

// シーン管理クラス
class CSceneBase
{
protected:
	static CSceneBase*		m_pStacTop;		// 前シーン格納スタック
	CSceneBase*		m_pStacPrev;	// 前 
	CSceneBase*		m_pStacNext;	// 次
	
	static CSceneBase*		m_pThis;		// このクラスを指す
	static CSceneBase*		m_pCurScene;	// 現在シーン格納ポインタ
	static CGraphics*		m_pGraph;			// グラフィックデバイス
	
	// インスタンス
	CObjMgr*		m_pObjMgr;		// オブジェを管理する
	CCamera			m_camera;		// カメラ
	CTexMgr*		m_pTexMgr;		// テクスチャマネージャ
	CMesh**			m_ppMesh;		// メッシュ保管所（動的）
	CCaptureWindow* m_pCapWin;		// スクショ用
	CObjBase*		m_pCameraBase;	// カメラの基準となるオブジェを格納
	CSoundMgr*		m_pSoundMgr;
	CFactoryBase*	m_pFactory;
	// その他
	//CObject3D*	m_pHitObj[OBJTYPE_ALL][PUTOBJ_MAX];
	TCHAR		m_szDebug[4096];	// デバッグ用文字列
	bool		m_bSC;		// シーン切り替え用(SceneChange)

	// 入力
	bool		m_bInput[INPTYPE][INP_BTN_MAX];

private:
	static DWORD			m_dwNewStateID;			// シーンID
	static DWORD			m_dwOldStateID;			// 旧シーンID 
	
	//-------- ゲーム用オブジェクト
public:
	CSceneBase(int n){};
	CSceneBase();
	virtual ~CSceneBase();

	static CSceneBase* CreateScene(CGraphics* pGraph);
	
	// 基本機能
	void Render();
	// CSceneBase* Create();
	void Initialze();
	virtual void Update();
	virtual void Draw();
	virtual void Release();
	virtual void CheckRunHit(){};		// あたり判定まとめ
	void AddDebugStr(LPCTSTR psz) {lstrcat(m_szDebug, psz);};

	// 拡張機能
	void StacScene();		// シーンをスタックする
	void PopScene();		// シーンをポップ
	void SetInputData(bool bInp[INPTYPE][INP_BTN_MAX]);	// 入力状態セット
	// void MoveScenePrev();	// 前シーンに移動（Ctrl + Z 的な）
	// void MoveSceneNext();	// 次シーンに移動（Ctrl + Y 的な）

	// ゲッター
	static CSceneBase* GetCurScene(){return m_pCurScene;};
	static CSceneBase* GetThis(){return m_pThis;};

	CObjMgr*	GetObjMgr(){return m_pObjMgr;};
	CFactoryBase*	GetFactory(){return m_pFactory;};
	CTexMgr*		GetTexMgr(){return m_pTexMgr;};
	CGraphics*		GetGraph(){return m_pGraph;};

private:
	virtual bool	InitializeScene(CGraphics* pGraph);

	//bool Initialize(CGraphics* pGraph);
	void Finalize();
	

};

// デバッグ用


static float g_fX = 0.0f;
static float g_fY = 0.0f;
static float g_z = 200.0f;
static float g_fovy = 30.0f;
static float g_fOrt = 1.0f;
#define CHIPSIZE_X (64.0f)
#define CHIPSIZE_Y (64.0f)

//=======================================================================================
//	End of File
//=======================================================================================