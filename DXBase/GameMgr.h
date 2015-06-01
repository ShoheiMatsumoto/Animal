#pragma once

#include "Graphics.h"
#include "SceneBase.h"
#include "Title.h"
#include "Stage.h"

// �Q�[���Ɏg�p����V�[����
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
	static CGameMgr*		m_pGameMgr;			// ������w���|�C���^

	CGraphics*		m_pGraph;			// �O���t�B�b�N�f�o�C�X

	CSceneBase*			m_pStScene;			// �V�[���C���X�^���X?

	static DWORD			m_dwNewScene;		// �V�V�[��
	DWORD			m_dwOldScene;		// ���V�[��

	int				m_FPS;				// �t���[�����J�E���g�p

	TCHAR		m_szDebug[4096];	// �f�o�b�O�p������
	
	// �C���X�^���X
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

