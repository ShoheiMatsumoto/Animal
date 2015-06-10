// 2D�O���t�B�b�N�X
#pragma once

// �C���N���[�h
#include "main.h"
#include "Graphics.h"
#include "Image.h"


enum
{
	TEX_LRNORMAL,
	TEX_LRREV,
	TEX_LRALL
};

enum
{
	TEX_TBNORMAL,
	TEX_TB_REV,
	TEX_TB_ALL
};

// ���_�t�H�[�}�b�g�i ���_���W[2D] / ���ˌ� / �e�N�X�`�����W �j
#define FVF_VERTEX_2D	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

// ��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR4 vtx;		// ���_���W
	D3DCOLOR	diffuse;	// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
}VERTEX_2D;

class CBoard2D
{
protected:
	D3DXVECTOR2 m_vSize;
	D3DXVECTOR2 m_vHalfSize;

public:
	VERTEX_2D m_verWk[4];				// ���_���
	VERTEX_2D m_verWkCpy[4];			// �R�s�[
	int						m_nImageType;
	int						m_nMaxPlain;
	bool					m_bScrollFlag;
	//float					m_fScrollSpdX;
	//float					m_fScrollSpdY;
	//float					m_fScrollPosX;
	//float					m_fScrollPosY;
	int						m_nColor[4];
	CImage*					m_pImage;
	float					m_fRadius;
	int m_nR;
	int m_nG;
	int m_nB;
	int m_nAlpha;
	int m_nCurDivNum;		
	int m_ntexLR;
	int m_ntexTB;

	// �r���{�[�h�p�ϐ�
	LPDIRECT3DVERTEXBUFFER9		m_pVertexBuffer;	// ���_�o�b�t�@�I�u�W�F�N�g
	LPDIRECT3DINDEXBUFFER9		m_pIndexBuffer;	// �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g


public:
	CBoard2D(void);
	virtual ~CBoard2D(void);

	void					Initialize(DWORD);	//����������
	//void					Update(void);
	//void					Draw(void);
	void					SetPosC(D3DXVECTOR3 vPos);
	void					SetPosL(D3DXVECTOR3 vPos);
	D3DXVECTOR2*			GetImageSize(){return m_pImage->GetSize();}
	float					GetRadius() {return m_fRadius;}
	void					SetRadius(float fRadius)	{m_fRadius = fRadius;}
	CImage*					GetImage(){return m_pImage;};
	VERTEX_2D*				GetVerWk(){return m_verWk;};

	// �Z�b�^�[
	void SetNum(int);		// �e�N�X�`�����W�Z�b�g
	void ReverseLR(int nType);		// ���E���]
	void ReverseTB(int nType);		// �㉺���]
	void SetAlpha(float fAlpha);		// �����x�ύX
	void SetColor(int nR, int nG, int nB);
	void ReSize(D3DXVECTOR2 vSize);		// �|���̃��T�C�Y
	void SetLength(float fLength);					// ������ɒ�����ς���
	void SetSize(D3DXVECTOR2 vSize);

	// �Q�b�^�[
	D3DXVECTOR2 GetSize(){return m_vSize;};
};

