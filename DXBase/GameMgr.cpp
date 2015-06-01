
// �C���N���[�h
#include <stdio.h>
#include "GameMgr.h"
#include "define.h"
#include "Title.h"
#include "Stage.h"
#include "SceneWk.h"
#include "Input.h"

// �O���[�o��
DWORD	CGameMgr::m_dwNewScene = SCENE_WK;		// �V�V�[��
CGameMgr*		CGameMgr::m_pGameMgr = NULL;			// ������w���|�C���^

CGameMgr::CGameMgr(void)
{
	m_FPS		 = 0;				// FPS�\���ϐ�������
	m_dwOldScene = SCENE_START;		// �����グ����X�^�[�g

}


CGameMgr::~CGameMgr(void)
{

}


//---------------------------------------------------------------------------------------
// �}�l�[�W���[�C���X�^���X����
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
// �f�o�C�X�A���\�[�X������
//---------------------------------------------------------------------------------------
bool CGameMgr::Initialize(CGraphics* pGraph)
{
	// �O���t�B�b�N�f�o�C�X���L
	m_pGraph = pGraph;

	// �V�[���C���X�^���X����
	CSceneBase::CreateScene(m_pGraph);
	m_pStScene = CSceneBase::GetThis();
	if (!m_pStScene) return false;



	return true;
}

//---------------------------------------------------------------------------------------
// �f�o�C�X�A���\�[�X���
//---------------------------------------------------------------------------------------
void CGameMgr::Finalize()
{
	//-------- �Q�[���p�I�u�W�F�N�g�̌�n��
	/*for (int i = 0; i < MAX_MESH; i++) {
		m_mesh[i].Finalize();
	}
	*/
}

//---------------------------------------------------------------------------------------
// ���
//---------------------------------------------------------------------------------------
void CGameMgr::Release()
{
	Finalize();
	delete this;
}

//---------------------------------------------------------------------------------------
// �Q�[���`�揈���i���C�����[�v����R�[�������j
//---------------------------------------------------------------------------------------
void CGameMgr::Render()
{
	if (m_pGraph->Begin()) {	// �`��J�n
	
		// �V�[�������_�����O
		m_pStScene->Render();
		Draw();					// �`�揈��

		m_pGraph->End();		// �`��I��
	}
	m_pGraph->SwapBuffer();		// �o�b�N�o�b�t�@����
}

//-------------------------------------------------
// �Q�[���X�V
//-------------------------------------------------
void CGameMgr::Update()
{
	if(GETINPUT->GetKey(KEY_TRG, DIK_0))
	{
		SetScene(SCENE_RETITLE);
	}

	// �X�e�[�g�ύX�Ǘ�
	SceneMgr();

	// �V�[���̍X�V
	m_pStScene->Update();
}

//----------------------------------------------------
// �V�[���؂�ւ��Ǘ�
//----------------------------------------------------
void CGameMgr::SceneMgr()
{
	int nID = 0;

	// �؂�ւ��`�F�b�N
	if(m_dwNewScene == m_dwOldScene)
		return;

	// �Ǘ��ϐ��X�V
	m_dwOldScene = m_dwNewScene;
	
	// �e�V�[���̐���
	switch(m_dwNewScene)
	{
	case SCENE_RETITLE:
		m_pStScene->Release();
	
		CTitle::Create();		// �^�C�g������
		break;
	case SCENE_TITLE:
		m_pStScene->Release();
		CTitle::Create();		// �^�C�g������
		break;

	case SCENE_STAGE:
		m_pStScene->Release();
		CStage::Create();		// �X�e�[�W����
		break;

	case SCENE_WK:
		m_pStScene->Release();
		CSceneWk::Create();		// ���[�N�X�y�[�X����
		break;
	default:

		break;
	}

	//m_pStScene = CScene::GetThis();
	// �Ǘ��ϐ��X�V
	m_dwOldScene = m_dwNewScene;

	
}

//-------------------------------------------------------
// �`��
//--------------------------------------------------------
void CGameMgr::Draw()
{
	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���

	// FPS ����ʂɕ`�悷�邽�߂̕�������쐬
	TCHAR	str[256];
	_stprintf(str, _T("FPS = %d\n"), m_FPS);
	lstrcat(m_szDebug, str);

	//----- �����ɕ`�揈��

	// �f�o�b�O������`��
	m_pGraph->DrawText(10, 2, m_szDebug);
}

// �V�[���̃Z�b�g
void CGameMgr::SetScene(DWORD dwScene)
{
	m_dwNewScene = dwScene;
	
}


