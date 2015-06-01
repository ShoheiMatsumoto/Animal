// 2Dグラフィックス
#pragma once

// インクルード
#include "main.h"
#include "Graphics.h"
#include "Image.h"

// 頂点フォーマット（ 頂点座標[2D] / 反射光 / テクスチャ座標 ）
#define FVF_VERTEX_2D	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

// 上記頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR4 vtx;		// 頂点座標
	D3DCOLOR	diffuse;	// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
}VERTEX_2D;

class CBoard2D
{
protected:
	D3DXVECTOR2 m_vSize;
	D3DXVECTOR2 m_vHalfSize;

public:
	VERTEX_2D m_verWk[4];				// 頂点情報
	VERTEX_2D m_verWkCpy[4];			// コピー
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

	// ビルボード用変数
	LPDIRECT3DVERTEXBUFFER9		m_pVertexBuffer;	// 頂点バッファオブジェクト
	LPDIRECT3DINDEXBUFFER9		m_pIndexBuffer;	// インデックスバッファオブジェクト


public:
	CBoard2D(void);
	virtual ~CBoard2D(void);

	void					Initialize(DWORD);	//初期化処理
	//void					Update(void);
	//void					Draw(void);
	void					SetPosC(D3DXVECTOR3 vPos);
	void					SetPosL(D3DXVECTOR3 vPos);
	D3DXVECTOR2*			GetImageSize(){return m_pImage->GetSize();}
	float					GetRadius() {return m_fRadius;}
	void					SetRadius(float fRadius)	{m_fRadius = fRadius;}
	CImage*					GetImage(){return m_pImage;};
	VERTEX_2D*				GetVerWk(){return m_verWk;};

	// セッター
	void SetNum(int);		// テクスチャ座標セット
	void SetAlpha(float fAlpha);		// 透明度変更
	void SetColor(int nR, int nG, int nB);
	void ReSize(D3DXVECTOR2 vSize);		// 板ポリのリサイズ
	void SetLength(float fLength);					// 左を基準に長さを変える
	void SetSize(D3DXVECTOR2 vSize);

	// ゲッター
	D3DXVECTOR2 GetSize(){return m_vSize;};
};

