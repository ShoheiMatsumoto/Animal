#pragma once

#include "Graphics.h"
#include "SceneBase.h"
#include "Title.h"
#include "Stage.h"

// ゲームに使用するシーン列挙
enum
{
	SCENE_START = 0,
	SCENE_WK,
	SCENE_WK_I,
	SCENE_WK_N,
	SCENE_TITLE,
	SCENE_RETITLE,
	SCENE_STAGE,
	SCENE_RESULT,
	SCENE_GAMEOVER,

	SCENE_MAX
};

class CGameMgr
{
public:
	CGameMgr(void);
	~CGameMgr(void);

	bool Initialize(CGraphics* pGraph);
	static CGameMgr* Create(CGraphics* pGraph);
	void Update();
	void Render();
	// void Draw();
	void Release();
	void Finalize();
	static CGameMgr* GetThis(){return m_pGameMgr;};

private:	
	static CGameMgr*		m_pGameMgr;			// これを指すポインタ

	CGraphics*		m_pGraph;			// グラフィックデバイス

	CSceneBase*			m_pStScene;			// シーンインスタンス?

	static DWORD			m_dwNewScene;		// 新シーン
	DWORD			m_dwOldScene;		// 旧シーン

	int				m_FPS;				// フレーム数カウント用

	TCHAR		m_szDebug[4096];	// デバッグ用文字列
	
	// インスタンス
	//CTitle m_Title;
	//CStage m_Stage;

	// CFadeIn* m_pFadeIn;
public:
	void SetFPS(int nFPS) {m_FPS = nFPS;}
	void SetScene(DWORD dwScene);

private:
	// void SetScene(DWORD dwScene);
	void SceneMgr();
	void Draw();
	

};

