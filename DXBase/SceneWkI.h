#pragma once
#include "scenebase.h"
#include "SceneBase.h"
#include "Collision.h"
#include "FadeOut.h"
#include "FadeIn.h"


// �g�p����e�N�X�`��
enum
{
	WK_I_TEX_0 = 0,
	WK_I_TEX_MOON,
	WK_I_TEX_CARTEN,

	WK_I_TEX_MAX,
};


// ���̃V�[���Ŏg�p����QD�I�u�W�F�N�g�̎��(�ڈ�)
enum
{
	WK_I_2D_OBJ_TEST = 0,

	// �ő吔�����ɍŏ���ObjMgr�̓��ꕨ�̐���ݒ�
	WK_I_2D_OBJ_MAX// �ォ����ꕨ�̃T�C�Y��ς�����
};

// ���̃V�[�����Ŏg�p����RD�I�u�W�F�N�g�̎��
enum
{
	WK_I_3D_OBJ_MOON = 0,
	WK_I_3D_OBJ_TEST_BILL,

	WK_I_3D_OBJ_MAX
};

// �g�p�T�E���h
enum
{
	WK_I_SOUND_TEST = 0,

	WK_I_SOUND_MAX			// �g�p����͍̂ő吔�̂�
};

class CSceneWkI :
	public CSceneBase
{
public:
	CSceneWkI(void);
	virtual ~CSceneWkI(void);

	void Update();			// �X�V
	void Draw();			// �`��
	void Release();
			//void InitTitle();		// ������
	static CSceneWkI* Create();	
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

