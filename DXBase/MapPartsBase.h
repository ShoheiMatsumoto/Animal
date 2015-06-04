// �}�b�v���\������I�u�W�F�N�g�̃x�[�X�錾��
#pragma once

// �C���N���[�h
#include "billboard.h"

// �p�[�c�̃O���[�v
enum
{
	MAPPARTS_SQUARE = 0,
	MAPPARTS_RUP,		// �E�オ��
	MAPPARTS_RDOWN,		// �E������

	MAPPARTS_MAX
};

class CMapPartsBase :
	public CBillboard
{
protected:
	int		m_nPartsType;		// �p�[�c�̃^�C�v

public:
	CMapPartsBase(void);
	CMapPartsBase(int nID, int nTexNum, D3DXVECTOR3 vPos);
	virtual ~CMapPartsBase(void);

	// ��{
	CMapPartsBase*	Create(int nID, int nTexNum, D3DXVECTOR3 vPos, D3DXVECTOR3 vSize, int nPartsType);
	void		Initialize(int nPartsType, D3DXVECTOR3 vSize);
	void		Update();
	void		HitUpdate();
	void		Release();

	// �g��
	int		GetPartsType(){return m_nPartsType;};
};

