#pragma once
#include "scenebase.h"

#include "FadeOut.h"
#include "FadeIn.h"


// �g�p����e�N�X�`��
enum
{
	WK_TEX_NONE = 0,		// �e�N�X�`���Ȃ�
	WK_TEX_PLAYER,
	WK_TEX_MOON,
	WK_TEX_CARTEN,
	WK_TEX_SQUARE,
	WK_TEX_SLOPE,
	WK_TEX_NEZU,
	WK_TEX_USHI,
	WK_TEX_TORA,
	WK_TEX_MIMI,
	WK_TEX_TATSU,
	WK_TEX_HEBI,
	WK_TEX_UMA,
	WK_TEX_MERRY,
	WK_TEX_SARU,
	WK_TEX_TORI,
	WK_TEX_INU,
	WK_TEX_URI,

	WK_TEX_MAX,
};


// ���̃V�[���Ŏg�p����QD�I�u�W�F�N�g�̎��(�ڈ�)
enum
{
	WK_2D_OBJ_TEST = 0,

	// �ő吔�����ɍŏ���ObjMgr�̓��ꕨ�̐���ݒ�
	WK_2D_OBJ_MAX// �ォ����ꕨ�̃T�C�Y��ς�����
};

// ���̃V�[�����Ŏg�p����RD�I�u�W�F�N�g�̎��
enum
{
	WK_3D_OBJ_MOON = 0,
	WK_3D_OBJ_TEST_BILL,

	WK_3D_OBJ_MAX
};

// �g�p�T�E���h
enum
{
	WK_SOUND_TEST = 0,

	WK_SOUND_MAX			// �g�p����͍̂ő吔�̂�
};

class CSceneWk :
	public CSceneBase
{
public:
	CSceneWk(void);
	virtual ~CSceneWk(void);

	void Update();			// �X�V
	void Draw();			// �`��
	void Release();
			//void InitTitle();		// ������
	static CSceneWk* Create();	
	void CheckRunHit();
	//CImage* GetImage(int nTexNum){return m_pImage[nTexNum];};
	
	void SetChangeScene();
private:
	bool		 Initialize();
	CObjBase*	m_pControlObj;

private:
	// �C���X�^���X	
	CFadeOut* m_pFadeOut;
	CFadeIn* m_pFadeIn;

};

