#pragma once
#include "main.h"
#include "Object2D.h"
#include "Object3D.h"
#include "Camera.h"

class CBillboard : public CObject3D
{
protected:
	//static D3DXMATRIX m_MatView;

	//--- �r���{�[�h�p���_�t�H�[�}�b�g
	int m_nR, m_nG, m_nB;
	int m_nAlpha;
	int m_nAnimNum;

	// �e���ݒ荀��
	bool				m_bTrueIsZBuffer;	// Z�o�b�t�@�X�V�t���O
	bool				m_bBillBoard;	// �J�����Ɍ������邩
	CBoard2D			m_Board;	// �QD�{�[�h���

	DVERTEX m_verWk[4];
	int m_nCurDivNum;		
	int m_ntexLR;
	int m_ntexTB;

private:
	D3DXVECTOR3	m_vLinePos;	
	
public:
	CBillboard(void);
	CBillboard(int n, int nTexNum);
	virtual ~CBillboard(void);

	void InitializeBillboard();
	void DrawSetUp();
	virtual void  Draw();
	void DrawEnd();
	void BeginBillboard();
	void EndBillboard();

	void ReleaseBillboard();

	void UpdateBillBoard();

	// �g��
	void InverseScreen(D3DXVECTOR3 vPos);		// �X�N���[�����W�ł̃A�N�Z�X�p�ϊ�

	


	// �Z�b�^�[
	//static void SetMatView(D3DXMATRIX matView){m_MatView = matView;};
	void SetBillColor(D3DXVECTOR3 vColor);
	void SetTexBillUV(int nPattern);
	void SetBillAlpha(float fAlphaRate);
	void SetbBillboard(bool bTrueIsBe){m_bBillBoard = bTrueIsBe;};

	// ��_�ɍ��킹���[�J�����@�n��ς���
	void SetLocalWkC();		
	void SetLocalWkTL();
	void SetLocalWkB();

	void ReverseLR(int nType);		// ���E���]
	void ReverseTB(int nType);		// �㉺���]
};

