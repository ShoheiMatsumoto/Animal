//=======================================================================================
//
//	  メッシュ クラス定義
//
//=======================================================================================
#pragma once
#include <windows.h>		// Windowsプログラムにはこれを付ける
#include <tchar.h>			// 汎用テキスト マッピング
#include <d3d9.h>			// DirectX Graphics 関連のヘッダ
#include <d3dx9.h>			// DirectX Graphics 関連のヘッダ
#include <dxerr.h>			// DirectX Graphics 関連のヘッダ

#include "MyHierarchy.h"

//enum
//{
//	MESH_PLAYER,
//	MESH_ENEMY,
//	MESH_SKY,
//	MESH_BULLET,
//
//
//
//	MAX_MESH
//};

struct BVERTEX {
	D3DXVECTOR3	pos;
	D3DXVECTOR3	nor;
	D3DXVECTOR2	tex;
};
#define FVF_BVERTEX		(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

struct PARTICLE {
	D3DXVECTOR3 acl;	// 加速度
	D3DXVECTOR3 spd;	// 速度
};

#define INIT_SPD	3.0f	// 初速(要調節)
#define GRAVITY		0.098f	// 重力加速度(要調節)

// アニメーションステータス
struct HLANIM_DESC
{
	UINT m_uiAnimID;                 // アニメーションID
	ID3DXAnimationSet *pAnimSet;   // アニメーションセット
	FLOAT fLoopTime;               // 1ループの時間
	FLOAT fTrackSpeed;             // トラックスピード調節値
	FLOAT fShiftTime;              // シフトするのにかかる時間
	FLOAT fCurWeightTime;          // 現在のウェイト時間
};

enum
{
	MESH_N,
	MESH_S,
};

class CMesh
{
private:
	int		m_nMeshType;

	// アニメ関連
	LPD3DXFRAME					m_pFrameRoot;	// ルート フレーム オブジェクト
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;	// アニメーション コントローラ オブジェクト
	UINT						m_uNumAnimSet;	// アニメーション セット数
	LPD3DXANIMATIONSET*			m_ppAnimSet;	// アニメーション セット
	CMyHierarchy				m_Hierarchy;	// 階層メモリ確保/解放クラス
	DWORD						m_dwPrev;		// 直前の時刻
	HLANIM_DESC*				m_pAnim;			// アニメパラメータ
	UINT m_uiPreID;			// 前回ＩＤ
	UINT m_uiCurID;			 // 現在アニメID

	//---------------------------------------------------------------------------------------

	LPD3DXMESH			m_pD3DMesh;			// D3DXMesh オブジェクト
	DWORD				m_dwNumMaterial;	// マテリアル数
	D3DMATERIAL9*		m_pMaterial;		// マテリアル
	LPDIRECT3DTEXTURE9*	m_ppTexture;		// テクスチャ

	D3DXATTRIBUTERANGE*	m_pAttr;			// 属性テーブル
	DWORD				m_dwAttr;			// 属性数
	DWORD				m_dwVtx;			// 頂点数
	BVERTEX*			m_pVtx;				// 頂点配列
	DWORD				m_dwIdx;			// インデックス数
	WORD*				m_pIdx;				// インデックス配列

	D3DXVECTOR3			m_vHalf;			// 境界ボックス ハーフサイズ
	D3DXVECTOR3			m_vCenter;			// 境界ボックス(境界球)中心座標
	float				m_fRadius;			// 境界球半径
	LPD3DXMESH			m_pSphere;			// 境界球表示用メッシュ
	LPD3DXMESH			m_pBox;				// 境界ボックス表示用メッシュ

	PARTICLE*			m_pPiece;			// 断片の制御用
	BVERTEX*			m_pPieceVtx;
	DWORD				m_dwFace;			// 面数

	int					m_nBombCnt;

public:
	// アニメ関連
	void SwitchAnimSet(UINT uAnimSet);		// アニメーション切替
	void SetTime(double dTime);				// アニメーション開始時間設定
	void SetAnimationController(ID3DXAnimationController* pAnimCont);// アニメーションコントローラを設定
	void GetAnimationController( ID3DXAnimationController **ppAnimCont );// アニメーションコントローラを取得
	void SetLoopTime(int nNo, float fSec);	// アニメーションのスピード設定
	void SetShiftTime( UINT animID, FLOAT interval );// 動作開始にかかる時間を設定
	void ChangeAnimation( UINT animID );// アニメーションを切り替え
	void AdvanceTime( FLOAT time );// アニメーションを更新


	CMesh();								// コンストラクタ
	virtual ~CMesh();						// デストラクタ
	bool Initialize(LPCTSTR pszFName, int nType);		// メッシュ初期化
	bool InitializeNorm(LPCTSTR pszFName);
	bool InitializeSkin(LPCTSTR pszFName);	// スキンメッシュ初期化
	void Finalize();						// メッシュ解放
	void Draw(D3DXMATRIX& world);			// メッシュ描画
	void Draw(D3DXMATRIX& world, float fAlpha);
	void DrawSkin(D3DXMATRIX& world);		// スキンアニメ用描画
	DWORD GetNumVertex() {return m_dwVtx;}	// 頂点数取得
	BVERTEX* GetVertex() {return m_pVtx;}	// 頂点配列取得
	DWORD GetNumIndex() {return m_dwIdx;}	// インデックス数取得
	WORD* GetIndex() {return m_pIdx;}		// インデックス配列取得
	DWORD GetFaceNum(){return m_dwFace;};
	D3DXVECTOR3& GetHalfSize() {return m_vHalf;}	// ボックスハーフサイズ取得
	D3DXVECTOR3& GetCenter() {return m_vCenter;}	// 境界ボックス/球中心座標取得
	float GetRadius() {return m_fRadius;}	// 境界球半径取得
	void InitParticle();					// 断片の初期化
	bool UpdateParticle();					// 断片の移動
	void DrawSphere(D3DXMATRIX& world, D3DCOLORVALUE color);
	void DrawBox(D3DXMATRIX& world, D3DCOLORVALUE color);

	void DrawNoAlpha(D3DXMATRIX& world);
	void DrawAlpha(D3DXMATRIX& world);

	// 追加ゲッター
	LPD3DXMESH GetBaseMesh(){return m_pD3DMesh;};

	// あたり判定
	bool CMesh::Intersect(LPD3DXVECTOR3 pPos,		//始点
						 LPD3DXVECTOR3 pDir,		//向き
						 LPD3DXVECTOR3 pCross,	    //交点
						 LPD3DXVECTOR3 pNormal);    //交点の法線
private:
	// アニメ関連
	void RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase);
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	void DrawFrame(LPD3DXFRAME pFrame);
	HRESULT AllocBoneMatrix(LPD3DXMESHCONTAINER pMeshContainerBase);
	HRESULT AllocAllBoneMatrix(LPD3DXFRAME pFrameBase);

};

//=======================================================================================
//	End of File
//=======================================================================================