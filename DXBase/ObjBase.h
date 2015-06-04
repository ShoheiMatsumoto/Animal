// �I�u�W�F�̃x�[�X�N���X�錾
#pragma once
#include "Graphics.h"
#include "Mesh.h"		// CMesh�N���X��`
#include "Board2D.h"	// 2D�{�[�h
// #include "Collision.h"

struct DVERTEX{			//--- �r���{�[�h�p���_�t�H�[�}�b�g
	float				x, y, z;			// ���_
	float				nx, ny, nz;			// �@���x�N�g��
	D3DCOLOR			color;				// �f�B�t���[�Y�J���[
	float				tu, tv;				// �e�N�X�`�����W
};

enum
{
	OBJ2DGROUP_EFFECT,
	OBJ2DGROUP_TEXT,
	OBJ2DGROUP_UI,

	OBJ2DGROUP_MAX
};

enum
{
	OBJ3DGROUP_PLAYER,
	OBJ3DGROUP_ENEMY,
	OBJ3DGROUP_MAP,
	OBJ3DGROUP_EFFECT,
	OBJ3DGROUP_COLLI,
	OBJ3DGROUP_ITEM,
	OBJ3DGROUP_UI,

	OBJ3DGROUP_MAX
};

// �`��^�C�v��
enum
{
	DRAWTYPE_2D_NORMAL = 0,
	DRAWTYPE_3D_NORMAL,
	DRAWTYPE_BILLBOARD,

	DRAWTYPE_MAX
};

// �����蔻���_�^�C�v
enum
{
	COLLBASEPOINT_CENTER,		// ���S
	COLLBASEPOINT_TOPLEFT,		// ����
	COLLBASEPOINT_BOTTOM,		// ��

	COLLBASEPOINT_MAX,
};

// �I�u�W�F�x�[�X�N���X
class CObjBase
{
protected:
	CObjBase* m_pNext;		// ��
	CObjBase* m_pPrev;		// �O
	// �Ǘ��p
	int					m_nObjGroupID;			// �O���[�v		
	int					m_nObjTypeID;			// �I�u�W�F��ނ��Ƃ�ID

	// �X�e�[�^�X
	// ����
	D3DXMATRIX			m_world;	// ���[���h�ϊ��s��
	D3DXVECTOR3			m_vPos;		// ���W
	D3DXVECTOR3			m_vAccel;	// �����x
	D3DXVECTOR3			m_vSpd;		// ���x
	D3DXVECTOR3			m_vAngle;	// �p�x
	D3DXVECTOR3			m_vSize;	// �T�C�Y
	D3DXVECTOR3			m_vRadius;	// ���a
	bool				m_bUse;		// �g�p�t���O
	bool				m_bHit;		// �q�b�g�t���O
	int					m_nObjStatus;		// �X�e�[�^�X
	
	// �`��
	int					m_nDrawType;
	bool				m_bDraw;			// �`��t���O	
	bool				m_bUseShader;		// �V�F�[�_���g����
	int					m_nShadeTechNum;	// �V�F�[�_�e�N�j�b�N�ԍ�
	bool				m_bAlphaBlend;	// �A���t�@�u�����h���邩
	float				m_fAlpha;	// �A���t�@�l
	bool				m_bCull;	// �J�����O

	// ���̑�
	int					m_nCollBasePoint;		// �����_�^�C�v
	//int					m_nDType;		// �����^�C�v
	bool				m_bDelete;

public:
	CObjBase(void);
	CObjBase(int nID);
	virtual ~CObjBase(void);

	// ��{�@�\
	CObjBase* Create();
	void Initialize();
	virtual void Update();
	virtual void Release();
	virtual void Draw();
	virtual void DrawSetUp();
	virtual void DrawEnd();
	virtual void HitUpdate(CObjBase* pObj, D3DXVECTOR3 vPos){};		// �����蔻���X�V

	// �g��
	//bool CollSquare(CObjBase* pObj);
	//bool CollCircle(CObjBase* pObj);
	

	// �Q�b�^�[
	CObjBase* GetNext(){return m_pNext;};		// ���̃|�C���^���擾
	CObjBase* GetPrev(){return m_pPrev;};		// �O�̃|�C���^���擾

	D3DXVECTOR3 GetPos(){return m_vPos;};
	D3DXVECTOR3 GetSpeed(void) {return m_vSpd;};		// ���x�Q�b�g
	D3DXVECTOR3 GetAccel(void) {return m_vAccel;};		// �����x�Q�b�g
	D3DXVECTOR3 GetSize(){return m_vSize;};
	D3DXVECTOR3 GetRadius(){return m_vRadius;};
	D3DXMATRIX  GetMatrix(void) {return m_world;};		// ���[���h�}�g���b�N�X�Q�b�g
	int			GetDrawType(){return m_nDrawType;};
	int			GetGroupID(){return m_nObjGroupID;};
	int			GetCollType(){return m_nCollBasePoint;};

	// �Z�b�^�[
	void SetNext(CObjBase* pObj){m_pNext = pObj;};
	void SetPrev(CObjBase* pObj){m_pPrev = pObj;};
	void SetbAlpha(bool bAlpha){m_bAlphaBlend = bAlpha;};		// �A���t�@�u�����h�̉ۂ̃Z�b�g
	void SetDelete(){m_bDelete = true;};		// ��������
	void SetbCull(bool bTrueIsBe){m_bCull = bTrueIsBe;};
	void SetSize(D3DXVECTOR3 vSize)
	{
		m_vSize = vSize;
		SetRadius(vSize /2.0f);
	};
	void SetRadius(D3DXVECTOR3 vRadius){m_vRadius = vRadius;};
	// �`�F�b�J�[
	bool CheckbeDelete(){return m_bDelete;};		// �f���[�g���邩
	
};

D3DXMATRIX CreateScreenMat();

