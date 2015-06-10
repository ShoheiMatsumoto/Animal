#pragma once
#include "main.h"
#include "Object2D.h"
#include "Object3D.h"
#include "Camera.h"

class CBillboard : public CObject3D
{
protected:
	//static D3DXMATRIX m_MatView;

	//--- ビルボード用頂点フォーマット
	int m_nR, m_nG, m_nB;
	int m_nAlpha;
	int m_nAnimNum;

	// 各自設定項目
	bool				m_bTrueIsZBuffer;	// Zバッファ更新フラグ
	bool				m_bBillBoard;	// カメラに向かせるか
	CBoard2D			m_Board;	// ２Dボード情報

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

	// 拡張
	void InverseScreen(D3DXVECTOR3 vPos);		// スクリーン座標でのアクセス用変換

	


	// セッター
	//static void SetMatView(D3DXMATRIX matView){m_MatView = matView;};
	void SetBillColor(D3DXVECTOR3 vColor);
	void SetTexBillUV(int nPattern);
	void SetBillAlpha(float fAlphaRate);
	void SetbBillboard(bool bTrueIsBe){m_bBillBoard = bTrueIsBe;};

	// 基準点に合わせローカル座法系を変える
	void SetLocalWkC();		
	void SetLocalWkTL();
	void SetLocalWkB();

	void ReverseLR(int nType);		// 左右反転
	void ReverseTB(int nType);		// 上下反転
};

