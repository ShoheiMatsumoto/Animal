// Title.cpp	

// �C���N���[�h
#include <stdio.h>
#include "Title.h"
#include "define.h"
#include "GameMgr.h"
#include "Input.h"
#include "MyCollision.h"
#include "TitleFactory.h"
#include "Collision.h"



// �R���X�g���N�^
CTitle::CTitle()
{
	m_nSwitch = 0;
}

// �f�X�g���N�^
CTitle::~CTitle()
{
	
}

//--------------------------------------------------------
// �^�C�g������
//--------------------------------------------------------
CSceneBase* CTitle::Create()
{
	CTitle* pTitle = new CTitle();		// �^�C�g���C���X�^���X����

	if(!pTitle->Initialize())
		SAFE_DELETE(pTitle);

	//delete pTitle;

	return pTitle;
}

//--------------------------------------------------------
// �^�C�g��������
//--------------------------------------------------------
bool CTitle::Initialize()
{
	// �^�C�g���Ɏg�����̗p��
	//m_pGraph = pGraph;

	// �e�N�X�`���}�l�[�W������
	m_pTexMgr = m_pTexMgr->Create(T_TEX_MAX);
	
	// �e�N�X�`���G���g���[
	m_pTexMgr->Entry(T_TEX_0, _T("../Data/Image/ButtonCircle.png"), 1);
	m_pTexMgr->Entry(T_TEX_MOON, _T("../Data/Image/moon.png"), 1);

	// ���f���f�[�^�i�[�z�񐶐�
	m_ppMesh = new CMesh*[T_MESH_MAX];

	
	
	// ���b�V���f�[�^�ǂݍ���
	//LPCTSTR pszXFile[T_MESH_MAX] = {
	//	_T("../model/skydome/liblary.x"),
	//};
	/*for (int i = 0; i < T_MESH_MAX; i++) {
		if (!m_Mesh[i].Initialize(pszXFile[i], MESH_N)) {
			::MessageBox(NULL, _T("X�t�@�C�����ǂ߂܂���."), _T("error"), MB_OK);
			return false;
		}
		m_Mesh[i].InitParticle();
	}*/

	// �I�u�W�F�}�l�[�W������
	m_pObjMgr = m_pObjMgr->Create();

	// �t�@�N�g������
	m_pFactory = CTitleFactory::Create();

	// �I�u�W�F�N�g����
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

	// �~���l�߂�
	for(int j = -nj; j < nj + jamari; j++)
	{
		pv = D3DXVECTOR3(sx * j + rx, -288.0f + CHIPSIZE_X, j * 10.0f);
		//m_pFactory->Request3D(OBJ3D_TESTBILL, pv);

	}
	

	for(int i = 0; i < 1; i++)
	{
		//m_pFactory->Request3D(OBJ3D_MOON, D3DXVECTOR3(32.0f * i, -288.0f + CHIPSIZE_X, 0.0f));
	}
	

	// �J�����ݒ�
	// �J������u���ʒu�����߂�
	D3DXVECTOR3 vNScreentoCam = D3DXVECTOR3(0.0f, 1.0f, 0.0f); // �X�N���[������J�����ʒu�ւ̃x�N�g��
	D3DXVECTOR3 vNFrametoCam;

	// �X�N���[��������J�������W�ւ̃x�N�g�������߂�
	float rot = 90.0f - FOVY / 2.0f;		// �X�N���[��������J�����ւ̊p�x
	float x = (float)(-cos(rot * 3.14 / 180.0f));	// X�x�N�g��
	float y = (float)(sin(rot * 3.14 / 180.0f));		// �{����Z������Y�Ƃ��Ĉ���
	vNFrametoCam = D3DXVECTOR3(x, y, 0.0f);	// ������J�����ւ̃x�N�g��

	// �X�N���[�����S����J�����A������J�����ւ�2�����̌�_�����߂�
	CMyCollision MyCol;		// ����C���X�^���X
	Segment Seg1, Seg2;		// �����v�f����
	D3DXVECTOR3 vCross;		// ��_�擾�p

	Seg1.vSPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���S����J�����i���W�j
	vNScreentoCam *= 3000.0f;						// �x�N�g�����\���ɐL�΂�
	Seg1.vVec = vNScreentoCam;						// �x�N�g��

	Seg2.vSPos = D3DXVECTOR3( (float)SCREEN_HEIGHT / 2.0f, 0.0f, 0.0f);		// �����W
	vNFrametoCam *= 3000.0f;						
	Seg2.vVec = vNFrametoCam;

	// ��_�����߂�
	bool bCroos = MyCol.CollisionLineToLine2D(Seg1, Seg2, &vCross);
	
	// ��_���J�������W�Ƃ���
	g_z = vCross.y;

	m_pCameraBase = m_pCameraBase->Create();
	D3DXMATRIX mat = m_pCameraBase->GetMatrix();
	D3DXVECTOR3 vAdPos = D3DXVECTOR3(0.0f, 0.0f, g_z);	
	D3DXVECTOR3 vLook =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_camera.SetAdjustPos(vAdPos);
	m_camera.SetLookPos(vLook);
	m_camera.SetEffect(C_EFFECT_NORMAL);

	// �T�E���h������
	// �T�E���h�t�@�N�g������
	m_pSoundMgr = m_pSoundMgr->Create(T_SOUND_MAX);

	// �G���g���[(ID�̓V�[���̃w�b�_�ł͂Ȃ��A�t�@�N�g���̃w�b�_�ɋL�����������L�q)
	m_pSoundMgr->Entry(SOUND_TEST, _T("../Data/Sound/BGM/bgm_fall.wav"));

	//m_pSoundMgr->RequestSound(SOUND_TEST, SOUND_ONE);
	//m_pSoundMgr->RequestSound(SOUND_TEST, SOUND_LOOP);

	return true;


}

//--------------------------------------------------------
// �^�C�g���X�V
//--------------------------------------------------------
void CTitle::Update()
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
	// �V�[���؂�ւ�����
	if(m_bSC)
	{
		if(m_pFadeOut->AskFin())		// �t�F�[�h���I�������
		{
			CGameMgr::GetThis()->SetScene(SCENE_STAGE);		// �V�[���؂�ւ�
		}
	}
	else
	{
		if(GETINPUT->GetKey(KEY_TRG, DIK_SPACE))
		{
			m_pFadeOut = m_pFadeOut->Create(T_TEX_CARTEN);		// �t�F�[�h�A�E�g����
			m_bSC = true;
			//CGameMgr::m_pGameMgr->SetScene(SCENE_STAGE);
		}
	}

	// �S�I�u�W�F�N�g�X�V
	m_pObjMgr->AllUpdate();		// 3D2D�܂Ƃ߂čX�V

	// �����蔻��܂Ƃߑ���
	CheckRunHit();
	
	// �r���{�[�h�I�u�W�F�ւ̃r���[�}�g���b�N�X�Z�b�g
	//CBillboard::SetMatView(m_camera.GetMatView());		
	
	// �J�����X�V
	m_camera.Update(&m_pCameraBase->GetMatrix());
}

//--------------------------------------------------------
// �^�C�g���̕`��
//--------------------------------------------------------
void CTitle::Draw()
{
	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���
	TCHAR	str[256];
	
	//----- �����ɕ`�揈��
	
	// �J�����ݒ�
	m_camera.Draw();

	// �S�I�u�W�F�N�g�`��
	m_pObjMgr->AllDraw();		// �QD�RD�܂Ƃ߂ĕ`��

	

	// �e��f�o�b�O�p���l�\��
	_stprintf(str, _T("�^�C�g��\n"));
	lstrcat(m_szDebug, str);
	
	// �f�o�b�O������`��
	m_pGraph->DrawText((int)g_fX, (int)g_fY, m_szDebug);
	
}

void CTitle::Release()
{
	// �e�N�X�`�����
	m_pTexMgr->Release();
	
	// ���f�����
	for(int i = 0; i < T_MESH_MAX; i++)
	{
		m_ppMesh[i]->Finalize();
	}
	SAFE_DELETE_ARRAY(m_ppMesh);		// ���ꕨ���
	
	// �}�l�[�W�����
	m_pObjMgr->Release();
	//SAFE_DELETE(m_pObjMgr);

	// �J�����x�[�X���
	SAFE_DELETE(m_pCameraBase);

	//m_pFadeIn->Create();
	//m_pFadeOut->Release();

}

void CTitle::SetChangeScene()
{

}

// �����蔻��܂Ƃ�
void CTitle::CheckRunHit()
{
	// �����蔻�葖��
	Collision Col;
	
	Col.CollSquareRunBill(m_pObjMgr->GetListTop3D(OBJ3DGROUP_PLAYER), m_pObjMgr->GetListTop3D(OBJ3DGROUP_MAP));
}






//=============================================
// EOF
//=============================================