// オブジェのベースクラス宣言
#pragma once
#include "Graphics.h"
#include "Mesh.h"		// CMeshクラス定義
#include "Board2D.h"	// 2Dボード
// #include "Collision.h"

struct DVERTEX{			//--- ビルボード用頂点フォーマット
	float				x, y, z;			// 頂点
	float				nx, ny, nz;			// 法線ベクトル
	D3DCOLOR			color;				// ディフューズカラー
	float				tu, tv;				// テクスチャ座標
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

// 描画タイプ列挙
enum
{
	DRAWTYPE_2D_NORMAL = 0,
	DRAWTYPE_3D_NORMAL,
	DRAWTYPE_BILLBOARD,

	DRAWTYPE_MAX
};

// あたり判定基準点タイプ
enum
{
	COLLBASEPOINT_CENTER,		// 中心
	COLLBASEPOINT_TOPLEFT,		// 左上
	COLLBASEPOINT_BOTTOM,		// 下

	COLLBASEPOINT_MAX,
};

// オブジェベースクラス
class CObjBase
{
protected:
	CObjBase* m_pNext;		// 次
	CObjBase* m_pPrev;		// 前
	// 管理用
	int					m_nObjGroupID;			// グループ		
	int					m_nObjTypeID;			// オブジェ種類ごとのID

	// ステータス
	// 動作
	D3DXMATRIX			m_world;	// ワールド変換行列
	D3DXVECTOR3			m_vPos;		// 座標
	D3DXVECTOR3			m_vAccel;	// 加速度
	D3DXVECTOR3			m_vSpd;		// 速度
	D3DXVECTOR3			m_vAngle;	// 角度
	D3DXVECTOR3			m_vSize;	// サイズ
	D3DXVECTOR3			m_vRadius;	// 半径
	bool				m_bUse;		// 使用フラグ
	bool				m_bHit;		// ヒットフラグ
	int					m_nObjStatus;		// ステータス
	
	// 描画
	int					m_nDrawType;
	bool				m_bDraw;			// 描画フラグ	
	bool				m_bUseShader;		// シェーダを使うか
	int					m_nShadeTechNum;	// シェーダテクニック番号
	bool				m_bAlphaBlend;	// アルファブレンドするか
	float				m_fAlpha;	// アルファ値
	bool				m_bCull;	// カリング

	// その他
	int					m_nCollBasePoint;		// 判定基準点タイプ
	//int					m_nDType;		// 次元タイプ
	bool				m_bDelete;

public:
	CObjBase(void);
	CObjBase(int nID);
	virtual ~CObjBase(void);

	// 基本機能
	CObjBase* Create();
	void Initialize();
	virtual void Update();
	virtual void Release();
	virtual void Draw();
	virtual void DrawSetUp();
	virtual void DrawEnd();
	virtual void HitUpdate(CObjBase* pObj){};		// 当たり判定後更新

	// 拡張
	//bool CollSquare(CObjBase* pObj);
	//bool CollCircle(CObjBase* pObj);
	

	// ゲッター
	CObjBase* GetNext(){return m_pNext;};		// 次のポインタを取得
	CObjBase* GetPrev(){return m_pPrev;};		// 前のポインタを取得

	D3DXVECTOR3 GetPos(){return m_vPos;};
	D3DXVECTOR3 GetSpeed(void) {return m_vSpd;};		// 速度ゲット
	D3DXVECTOR3 GetAccel(void) {return m_vAccel;};		// 加速度ゲット
	D3DXVECTOR3 GetSize(){return m_vSize;};
	D3DXVECTOR3 GetRadius(){return m_vRadius;};
	D3DXMATRIX  GetMatrix(void) {return m_world;};		// ワールドマトリックスゲット
	int			GetDrawType(){return m_nDrawType;};
	int			GetGroupID(){return m_nObjGroupID;};
	int			GetCollType(){return m_nCollBasePoint;};

	// セッター
	void SetNext(CObjBase* pObj){m_pNext = pObj;};
	void SetPrev(CObjBase* pObj){m_pPrev = pObj;};
	void SetbAlpha(bool bAlpha){m_bAlphaBlend = bAlpha;};		// アルファブレンドの可否のセット
	void SetDelete(){m_bDelete = true;};		// 消去準備
	void SetbCull(bool bTrueIsBe){m_bCull = bTrueIsBe;};
	void SetSize(D3DXVECTOR3 vSize)
	{
		m_vSize = vSize;
		SetRadius(vSize /2.0f);
	};
	void SetRadius(D3DXVECTOR3 vRadius){m_vRadius = vRadius;};
	// チェッカー
	bool CheckbeDelete(){return m_bDelete;};		// デリートするか
	
};

D3DXMATRIX CreateScreenMat();

