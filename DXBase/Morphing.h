// モーフィングオブジェクトベースクラス
#pragma once
#include "object3d.h"

#define MORPMODEL_MAX	(10)	// 登録できるモデル数 

struct MORPH_VERTEX {
	float x, y, z;				// 頂点座標（座標変換あり）
	D3DXVECTOR3	vNromVec;			// 法線ベクトル
	float		tu, tv;				// テクスチャ座標
};
#define FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

//----- 構造体定義
struct MORPH_OBJECT {			//--- オブジェクト用構造体
	int			status;				// ステータス
	float		x, y, z;			// 座標
	float		rotx, roty, rotz;	// 角度
	D3DXMATRIX	matrix;				// 変換マトリックス
	int			morph_count;		// モーフィング計算用時間カウント値
	int			morph_dir;			// モーフィングの方向
	int			morph_time[2];		// モーフィングに要する時間
	int			StopCnt;			// 状態留めカウンタ
};

class CMorphing :
	public CObject3D
{
protected:
	// モーフィング用メッシュ入れ
	CMesh m_pMorpMesh[MORPMODEL_MAX];

	// モーフィングに必要なステータス
	int m_nMorpMeshNum;		// 登録してるメッシュ数
	int m_nPrevID;			// 変形元のメッシュID
	int m_nNextID;			// 変形先のメッシュID

	// モーフィング用保存データ
	LPDIRECT3DTEXTURE9			m_pD3DTexture;			// Direct3DTexture8 オブジェクト
	MORPH_OBJECT	m_Obj;							// オブジェデータ
	MORPH_VERTEX*	m_pVertex[MORPMODEL_MAX];		// 頂点データ
	WORD*			m_dwIndex[MORPMODEL_MAX];		// インデックス
	int				m_nVertexNum[MORPMODEL_MAX];		// 頂点数
	int				m_nFaceNum[MORPMODEL_MAX];		// 面数
	MORPH_VERTEX*	m_pMorph_Vertex;				// モーフィング用頂点データ
	WORD*			m_pwMorph_Index;					// モーフィング用インデックス

private:


public:
	CMorphing(void);
	CMorphing(int n);
	virtual ~CMorphing(void);

	virtual void InitializeMorph(int nMeshNum);

	void UpdateMorph();
	virtual void Update();
	virtual void Draw();
	virtual void Release(){};
};

