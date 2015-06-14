//=======================================================================================
//
//	  �V�[�� �N���X�錾
//
//=======================================================================================
#pragma once

#include "Graphics.h"
#include "define.h"
#include "Mesh.h"		// CMesh�N���X
#include "Camera.h"		// CCamera�N���X
#include "TexMgr.h"
#include "ObjMgr.h"
#include "Input.h"
#include "CaptureWindow.h"
#include "SoundMgr.h"
#include "FactoryBase.h"

// �V�[���Ǘ��N���X
class CSceneBase
{
protected:
	static CSceneBase*		m_pStacTop;		// �O�V�[���i�[�X�^�b�N
	CSceneBase*		m_pStacPrev;	// �O 
	CSceneBase*		m_pStacNext;	// ��
	
	static CSceneBase*		m_pThis;		// ���̃N���X���w��
	static CSceneBase*		m_pCurScene;	// ���݃V�[���i�[�|�C���^
	static CGraphics*		m_pGraph;			// �O���t�B�b�N�f�o�C�X
	
	// �C���X�^���X
	CObjMgr*		m_pObjMgr;		// �I�u�W�F���Ǘ�����
	CCamera			m_camera;		// �J����
	CTexMgr*		m_pTexMgr;		// �e�N�X�`���}�l�[�W��
	CMesh**			m_ppMesh;		// ���b�V���ۊǏ��i���I�j
	CCaptureWindow* m_pCapWin;		// �X�N�V���p
	CObjBase*		m_pCameraBase;	// �J�����̊�ƂȂ�I�u�W�F���i�[
	CSoundMgr*		m_pSoundMgr;
	CFactoryBase*	m_pFactory;
	// ���̑�
	//CObject3D*	m_pHitObj[OBJTYPE_ALL][PUTOBJ_MAX];
	TCHAR		m_szDebug[4096];	// �f�o�b�O�p������
	bool		m_bSC;		// �V�[���؂�ւ��p(SceneChange)

	// ����
	bool		m_bInput[INPTYPE][INP_BTN_MAX];

private:
	static DWORD			m_dwNewStateID;			// �V�[��ID
	static DWORD			m_dwOldStateID;			// ���V�[��ID 
	
	//-------- �Q�[���p�I�u�W�F�N�g
public:
	CSceneBase(int n){};
	CSceneBase();
	virtual ~CSceneBase();

	static CSceneBase* CreateScene(CGraphics* pGraph);
	
	// ��{�@�\
	void Render();
	// CSceneBase* Create();
	void Initialze();
	virtual void Update();
	virtual void Draw();
	virtual void Release();
	virtual void CheckRunHit(){};		// �����蔻��܂Ƃ�
	void AddDebugStr(LPCTSTR psz) {lstrcat(m_szDebug, psz);};

	// �g���@�\
	void StacScene();		// �V�[�����X�^�b�N����
	void PopScene();		// �V�[�����|�b�v
	void SetInputData(bool bInp[INPTYPE][INP_BTN_MAX]);	// ���͏�ԃZ�b�g
	// void MoveScenePrev();	// �O�V�[���Ɉړ��iCtrl + Z �I�ȁj
	// void MoveSceneNext();	// ���V�[���Ɉړ��iCtrl + Y �I�ȁj

	// �Q�b�^�[
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

// �f�o�b�O�p


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