//=======================================================================================
//
//	  �V�[�� �N���X
//
//=======================================================================================
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <windows.h>
#include <stdio.h>
#include "GameWnd.h"
#include "SceneBase.h"
#include "Input.h"


// �X�^�e�B�b�N������
CSceneBase* CSceneBase::m_pThis = NULL;
CSceneBase* CSceneBase::m_pCurScene = NULL;
CSceneBase* CSceneBase::m_pStacTop = NULL;
CGraphics* CSceneBase::m_pGraph = NULL;

//---------------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------------
CSceneBase::CSceneBase()
{
	// m_bSphere	 = true;
	//m_nSwCamera	 = 0;
	// m_nSceneID = SCENE_TITLE;
	
	//m_dwNewStateID = SCENE_TITLE;
	//m_dwOldStateID = SCENE_START;
	
	// �����������̂����݃V�[���Ƃ���
	m_bSC = false;
	m_pCurScene = this;

}

// �V�[�����X�^�b�N����
void CSceneBase::StacScene()
{
	// ���݃V�[������������
	if(m_pCurScene)
	{
		// �X�^�b�N�̃g�b�v�ɂȂɂ������
		if(m_pStacTop)		
		{
			m_pCurScene->m_pStacPrev = m_pStacTop;		// ���݃V�[���̑O���g�b�v
			m_pStacTop = m_pCurScene;					// ���݃V�[�������̃g�b�v��
		}
		else
		{
			m_pStacTop = m_pCurScene;		// ���݃V�[�����g�b�v�ɓo�^
		}
	}	
	else
	{
		// �G���[����

	}
}

// �V�[�����|�b�v����
void CSceneBase::PopScene()
{
	// �g�b�v�ɉ�����������
	if(m_pStacTop)
	{
		// ���݃V�[���̉��
		m_pCurScene->Release();

		// ���݃V�[���Ƀg�b�v������
		m_pCurScene = m_pStacTop;

		// �X�^�b�N����Ă���V�[��������΂��炷
		if(m_pStacTop->m_pStacPrev)
		{
			m_pStacTop = m_pStacTop->m_pStacPrev;		// �g�b�v����ɂ���V�[�������炷
		}
	}	
	else
	{
		// �G���[����

	}
}
//---------------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------------
CSceneBase::~CSceneBase()
{
	

}

//---------------------------------------------------------------------------------------
// �V�[������
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
// �f�o�C�X�A���\�[�X������
//---------------------------------------------------------------------------------------
bool CSceneBase::InitializeScene(CGraphics* pGraph)
{
	// ��ʁiGameWnd�j����O���t�B�b�N�f�o�C�X���L
	m_pGraph = pGraph;		
	//m_pImage[TEX_CARTEN_BK]	= CImage::Create(_T("../Data/Image/Carten/CartenBk.png"), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 1);
	m_pCapWin = m_pCapWin->Create();

	return true;
}

//---------------------------------------------------------------------------------------
// �f�o�C�X�A���\�[�X���
//---------------------------------------------------------------------------------------
void CSceneBase::Finalize()
{
	//-------- �Q�[���p�I�u�W�F�N�g�̌�n��
	/*for (int i = 0; i < MAX_MESH; i++) {
		m_mesh[i].Finalize();
	}
	*/
}

//---------------------------------------------------------------------------------------
// �V�[�����
//---------------------------------------------------------------------------------------
void CSceneBase::Release()
{
	// �e�N�X�`���̉��
	//SAFE_DELETE_ARRAY(m_ppImage);

	// �}�l�[�W���̉��


	// ���݃V�[���̉��
	if(m_pCurScene)
	{
		SAFE_DELETE(m_pCurScene);
	}
}

//---------------------------------------------------------------------------------------
// �Q�[���`�揈���iGameMgr::Render()����R�[�������j
//---------------------------------------------------------------------------------------
void CSceneBase::Render()
{
	//if (m_pGraph->Begin()) {	// �`��J�n

		Draw();					// �`�揈��

		// ��ʃL���v�`���i�����ł����Ȃ��̔���j
		
		//if(m_pCapWin->ScreenShot())
		//	m_ppImage[TEX_SCREENSHOT]	= CImage::Create(_T("../Data/Image/scr_shot/scrshot.bmp"), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 1);

		//m_pGraph->End();		// �`��I��
	//}
	//m_pGraph->SwapBuffer();		// �o�b�N�o�b�t�@����
}

//---------------------------------------------------------------------------------------
// �V�[���X�V�����iGameMgr::Update()����R�[�������j
//---------------------------------------------------------------------------------------
void CSceneBase::Update()
{
	//----- �����ɃQ�[���{�̏���
	
	// �e�V�[���X�V
	m_pCurScene->Update();		// 
}

//---------------------------------------------------------------------------------------
// �`�揈���iCGraphics::Render() ����R�[�������j
//---------------------------------------------------------------------------------------
void CSceneBase::Draw()
{
	//m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���

	
	// �S�I�u�W�F�N�g�`��
	m_pCurScene->Draw();
}

//-----------------------------------
// ���͏�ԃZ�b�g
//------------------------------------
void CSceneBase::SetInputData(bool bInp[INPTYPE][INP_BTN_MAX])
{
	// �v���X*******************************************
	if(GETINPUT->GetKey(KEY_PRS, DIK_LEFT))		// ��
		bInp[KEY_PRS][INP_BTN_LEFT] = true;

	if(GETINPUT->GetKey(KEY_PRS, DIK_RIGHT))	// �E
		bInp[KEY_PRS][INP_BTN_RIGHT] = true;

	if(GETINPUT->GetKey(KEY_PRS, DIK_UP))		// ��
		bInp[KEY_PRS][INP_BTN_UP] = true;

	if(GETINPUT->GetKey(KEY_PRS, DIK_DOWN))		// ��
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

	// �g���K�[***************************************:
	if(GETINPUT->GetKey(KEY_TRG, DIK_LEFT))		// ��
		bInp[KEY_TRG][INP_BTN_LEFT] = true;

	if(GETINPUT->GetKey(KEY_TRG, DIK_RIGHT))	// �E
		bInp[KEY_TRG][INP_BTN_RIGHT] = true;

	if(GETINPUT->GetKey(KEY_TRG, DIK_UP))		// ��
		bInp[KEY_TRG][INP_BTN_UP] = true;

	if(GETINPUT->GetKey(KEY_TRG, DIK_DOWN))		// ��
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

	// �����[�X****************************************
	if(GETINPUT->GetKey(KEY_RLS, DIK_LEFT))		// ��
		bInp[KEY_RLS][INP_BTN_LEFT] = true;

	if(GETINPUT->GetKey(KEY_RLS, DIK_RIGHT))	// �E
		bInp[KEY_RLS][INP_BTN_RIGHT] = true;

	if(GETINPUT->GetKey(KEY_RLS, DIK_UP))		// ��
		bInp[KEY_RLS][INP_BTN_UP] = true;

	if(GETINPUT->GetKey(KEY_RLS, DIK_DOWN))		// ��
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