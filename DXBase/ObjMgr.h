// �I�u�W�F�}�l�[�W���N���X�錾
#pragma once

// �C���N���[�h
#include "ObjBase.h"
#include "Object2D.h"
#include "Object3D.h"
#include "Collision.h"

#define DRAWOBJ_MAX (512)

//�I�u�W�F�Ǘ��N���X
// �V�[�����ɐ�������B
// �V�[�����ƂɈႤ���ꕨ�ŃI�u�W�F���Ǘ����Ă����B
class CObjMgr
{
protected:
	

public:
	CObjMgr(void);
	virtual ~CObjMgr(void);

	// ��{�@�\
	CObjMgr* Create();		// �I�u�W�F�}�l�[�W������
	void Initialize();		// ����������
	void InitList();		// ���X�g�̏�����

	void SetDrawList(CObject2D* pObj);			// 2D�p�̕`�惊�X�g�̃Z�b�g
	void ResetDrawList();		// �I�u�W�F���������ۂ̃��X�g�̃��Z�b�g
	void DrawSort();			// �`��Z�b�g

	void Update2D();		// 2DObj�̍X�V
	void Update3D();		// 3DObj�̍X�V
	void AllUpdate();		// �SOBJ�̍X�V
	
	void Draw2D();			// 2DObj�̕`��
	void Draw3D();			// 3DObj�̕`��
	void AllDraw();			// �SOBJ�̕`��
	
	void Release();			// ���

	// �g��
	void EntryObj2D(CObjBase* pObj);		// �I�u�W�F�o�^
	void EntryObj3D(CObjBase* pObj);		// �I�u�W�F�o�^
	// void ReleaseObj2D();

	void DeleteObj();		// �I�u�W�F����
	void DeleteObj2D();
	void DeleteObj3D();
	
	void ReleaseList();		// ���X�g�̉��
	void ReleaseList2D();
	void ReleaseList3D();
	// void Hit(CObjBase* pObj){};		// �����蔻��㏈��

	// �Q�b�^�[
	CObject2D*	GetListTop2D(int nGroupID);		// ���ۃg�b�v�ɂ����OBJ�͂Ƃ΂�
	CObject3D*	GetListTop3D(int nGroupID);
	CObjBase*	GetIdentifObj2D(int nGID, int nTID, int nIID);		// �ʂ̃I�u�W�F�N�g���擾
	CObjBase*	GetIdentifObj3D(int nGID, int nTID, int nIID);		// �ʂ̃I�u�W�F�N�g���擾

	// �Z�b�^�[
	void SetbReset(){m_bResetDrawList = true;};
private:
	CObjBase*	m_pObj;
	CObject2D* m_p2DObj;
	CObject3D* m_p3DObj;

	CObject2D* m_pObjListTop2D[OBJ2DGROUP_MAX];		// ���I���X�g
	CObject3D* m_pObjListTop3D[OBJ3DGROUP_MAX];		// ���I���X�g

	CObject2D* m_pObj2DDraw[DRAWOBJ_MAX];	// �QD�`��p
	
	bool	m_bResetDrawList;		// 2D�p�`�惊�X�g���Z�b�g�t���O

	int		m_nCurDrawType;			// �`��^�C�v
};

