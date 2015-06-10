// 3D�`��I�u�W�F�N�g �N���X��`
#pragma once
#include "ObjBase.h"

#define FVF_DVERTEX		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// �I�u�W�F�N�g���


// �I�u�W�F�N�g�����^�C�v
enum
{
	OT_3D,
	OT_2D,
	OT_BILLBOARD,

	OT_MAX
};

// ���e�@��
enum
{
	VIEWPROJ_PERS = 0,
	VIEWPROJ_ORT,
};

// �I�u�W�F�N�g�X�e�[�^�X
enum
{
	OBJST_NONE = 0,		// �ʏ�
	OBJST_DELETE,		// ��������
	OBJST_NOUPDATE,		// �X�V���Ȃ�
	OBJST_NODRAW,		// �`�悵�Ȃ�
	OBJST_UNBUSH,		//�@�X�V�`��Ƃ��ɂ��Ȃ� 

	OBJST_ALL
};

#define MAX_OBJTYPE (20)
#define PUTOBJ_MAX 1000 

class CObject3D : public CObjBase
{
protected:
	// ���X�g�֘A	
	//CObject3D* m_pNext;		// ��
	//CObject3D* m_pPrev;		// �O

	D3DXVECTOR3			m_vLocalVec[3];	// ���[�J�����W�� 

	// 3D���b�V���p
	//CMesh				m_Mesh;
	CMesh*				m_pMesh;	// ���b�V���ւ̃|�C���^
	
	// �X�e�[�^�X
	bool				m_bUse;
	bool				m_bSphere;
	bool				m_bBox;
	
	// �`��֘A
	int					m_nViewProjType;	// ���e�@

public:
	//CObject3D(int nObjType);
	CObject3D();
	CObject3D(int nID);
	virtual ~CObject3D(void);

	// ���X�g�Ǘ�
	//void InitListTop();
	
	// ���ʋ@�\
	//CObject3D* Create();
	void Initilaize();		// ������
	virtual void Update(void);		// �X�V
	// virtual void SetViewProj();
	virtual void DrawSetUp();
	virtual void DrawEnd();
	virtual void Draw();		// �s���������`��
	virtual void DrawAlpha(void);	// ���������`��
	virtual void Release(){};			// ��� 

	// ���ʓ���

	// �g��
	bool CollBox(CObjBase* pObj){};
	bool CollSphere(CObjBase* pObj){};

	// �Z�b�^�[
	void SetPosToMatrix();		// �}�g���b�N�X�ւ̍��W�Z�b�g
	void SetAccel(D3DXVECTOR3& accel) {m_vAccel = accel;};
	void SetMesh(CMesh* pMesh) {m_pMesh = pMesh;};	// ���b�V���̃Z�b�g
	//void SetMesh(CMesh Mesh) {m_Mesh = Mesh;};	// ���b�V���̃Z�b�g
	void SetObjStatus(int nStatus){m_nObjStatus = nStatus;};
	void SetSpeed(D3DXVECTOR3& speed) {m_vSpd = speed;};
	void SetBeAlphaBlend(bool bAlpha){m_bAlphaBlend = bAlpha;}
	
	// �Q�b�^�[
	CMesh* GetMesh(void) {return m_pMesh;};				// ���b�V�����Q�b�g
	bool GetUse(){return m_bUse;};
	int		GetViewType(){return m_nViewProjType;};

};

