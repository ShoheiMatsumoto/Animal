#include "MapPartsBase.h"


CMapPartsBase::CMapPartsBase(void)
{
}

CMapPartsBase::CMapPartsBase(int nID, int nTexNum, D3DXVECTOR3 vPos) : CBillboard(nID, nTexNum)
{
	m_nObjGroupID = OBJ3DGROUP_MAP;		// �O���[�v�^�C�v�ݒ�
	m_vPos = vPos;		// ��Ńx�[�X�Ɉڂ�����

	m_bBillBoard = false;	// �r���{�[�h�����I�t
	m_bAlphaBlend = false;	// �A���t�@�u�����h�I�t
}

CMapPartsBase::~CMapPartsBase(void)
{
}

// ����
CMapPartsBase*	CMapPartsBase::Create(int nID, int nTexNum, D3DXVECTOR3 vPos, D3DXVECTOR3 vSize, int nPartsType)
{
	CMapPartsBase* p = new CMapPartsBase(nID, nTexNum, vPos);

	p->Initialize(nPartsType, vSize);

	return p;
}

// ������
void		CMapPartsBase::Initialize(int nPartsType, D3DXVECTOR3 vSize)
{
	m_nPartsType = nPartsType;		// �p�[�c�^�C�v�Z�b�g
	m_Board.ReSize(D3DXVECTOR2(vSize.x, vSize.y));		
	m_nCollBasePoint = COLLBASEPOINT_BOTTOM;		// �����蔻���_
	SetSize(D3DXVECTOR3(vSize.x, vSize.y, 0.0f));
	SetPosToMatrix();		// �}�g���b�N�X�ւ̍��W�Z�b�g

	// �r���{�[�h������
	InitializeBillboard();
}

// �X�V
void		CMapPartsBase::Update()
{
	// �r���{�[�h�X�V
	UpdateBillBoard();
}

// �����X�V
void		CMapPartsBase::HitUpdate()
{

}

// ���
void		CMapPartsBase::Release()
{
	delete this;
}



// eof
