#pragma once

#include "objbase.h"
#include "MyMath.h"


#define LINEPOINT_MAX (10)		// 中間点の数
// #define FVF_DVERTEX		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)


struct POLIVERTEX
{
	int		m_nTimer;
	float	m_fRate;
	KEY		m_HKey[2];		// エルミート始点終点		
	KEY		m_HVecKey[2];	// エルミート始点終点ベクトル
};

// #define D3DFVF_POLIVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class CPoliLine :
	public CObjBase
{
protected:
	

public:
	CBoard2D	m_Board;		// ボード情報（テクスチャ情報のみ使う）
	float		m_fLineWidth;	// ライン幅
	float		m_fRate;		// 移動比率
	D3DXVECTOR3 m_vInitPos;		// 始点
	D3DXVECTOR3 m_vDestPos;		// 終点
	D3DXVECTOR3	m_vLinePos[LINEPOINT_MAX];		// 中間点
	
	D3DXVECTOR3 m_vDirVec[LINEPOINT_MAX];		// 進行方向ベクトル
	D3DXVECTOR3 m_vCameraVec[LINEPOINT_MAX];	// カメラへのベクトル
	D3DXVECTOR3 m_vDiffVec[LINEPOINT_MAX];		// 広げる方向

	POLIVERTEX	m_Point[LINEPOINT_MAX * 2];	// ポリラインスクエア
	DVERTEX		m_verWk[LINEPOINT_MAX * 2];

	// 関数
	CPoliLine(void);
	virtual ~CPoliLine(void);

	CPoliLine* Create(int nTexNum, D3DXVECTOR3 vInitPos, D3DXVECTOR3 vDestPos, float fWidth);
	void Initialize(int nImage);

	void Update();
	void Draw();
	void DrawSetUp();
	void DrawEnd();

	void CalcLine();		// ライン計算
	void CalcDirVec();		// 進行方向計算
	void CalcCameraVec();	// カメラへのベクトル計算
	void CalcDiffVec();		// 拡散方向計算
	void CalcSquare();		// 四角計算

	// セッター
	void SetPosLine();

};

