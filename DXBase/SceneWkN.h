#pragma once
#include "scenebase.h"
#include "SceneBase.h"
#include "Collision.h"
#include "FadeOut.h"
#include "FadeIn.h"


// �g�p����e�N�X�`��
enum
{
	WK_N_TEX_0 = 0,
	WK_N_TEX_MOON,
	WK_N_TEX_CARTEN,

	WK_N_TEX_MAX,
};


// ���̃V�[���Ŏg�p����QD�I�u�W�F�N�g�̎��(�ڈ�)
enum
{
	WK_N_2D_OBJ_TEST = 0,

	// �ő吔�����ɍŏ���ObjMgr�̓��ꕨ�̐���ݒ�
	WK_N_2D_OBJ_MAX// �ォ����ꕨ�̃T�C�Y��ς�����
};

// ���̃V�[�����Ŏg�p����RD�I�u�W�F�N�g�̎��
enum
{
	WK_N_3D_OBJ_MOON = 0,
	WK_N_3D_OBJ_TEST_BILL,

	WK_N_3D_OBJ_MAX
};

// �g�p�T�E���h
enum
{
	WK_N_SOUND_TEST = 0,

	WK_N_SOUND_MAX			// �g�p����͍̂ő吔�̂�
};

class CSceneWkN :
	public CSceneBase
{
public:
	CSceneWkN(void);
	virtual ~CSceneWkN(void);

	void Update();			// �X�V
	void Draw();			// �`��
	void Release();
			//void InitTitle();		// ������
	static CSceneWkN* Create();	
	void CheckRunHit();
	//CImage* GetImage(int nTexNum){return m_pImage[nTexNum];};
	
	void SetChangeScene();
private:
	bool		 Initialize();

private:
	// �C���X�^���X	
	CFadeOut* m_pFadeOut;
	CFadeIn* m_pFadeIn;

};

