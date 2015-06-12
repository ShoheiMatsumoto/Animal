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
	OBJ3DGROUP_ANIMARU,
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

class CContSt
{
private:
	// 定数定義
	// 移動系
	#define ADDMSPD (0.1f)
	#define MOVESPDMAX (4.0f)
	#define BREAKERATE (1.5f)
	#define BRKSPD (0.1f)

	// ジャンプ関連

	#define ADDJSPD ()
	#define FFIRSTSPD (0.5f)
	#define ADDFSPD (0.4f / 60.0f)
	#define FSPDMAX (10.0f)
	#define JUMPPOW (10.0f)
	#define JUMPBRK (0.3f)


	#define ST_STAND	0		// 立ち
	#define ST_WALK		1		// 歩き
	#define ST_RUN		2		// 走り
	#define ST_ACTION	3		// アクション
	#define ST_JUMPUP	4		// ジャンプ
	#define ST_FALL		5		// 落下

	#define MOVEVEC_TYPE_RIGHT 0
	#define MOVEVEC_TYPE_LEFT  1

public:
	int		m_nMoveVecType;	// 向いてる方向
	float	m_fFallSpd;	// 落下移動調整用
	float	m_fJumpPow;	// ジャンプ力
	float	m_fMovePow; // 移動力
	bool	m_bJump;	// ジャンプフラグ
};

// オブジェベースクラス
class CObjBase
{
protected:
	CObjBase* m_pNext;		// 次
	CObjBase* m_pPrev;		// 前
	// 管理用
	int					m_nObjGroupID;			// グループ		
	int					m_nObjTypeID;			// グループ内での種類ごとのID
	int					m_nIdentifID;			// 識別番号
	static int			m_nIdentifCnt;

	// ステータス
	// 動作
	D3DXMATRIX			m_world;	// ワールド変換行列
	D3DXVECTOR3			m_vPos;		// 座標
	D3DXVECTOR3			m_vOldPos;	// 旧座標
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
	virtual void HitUpdate(CObjBase* pObj, D3DXVECTOR3 vPos){};		// 当たり判定後更新

	// 拡張
	//bool CollSquare(CObjBase* pObj);
	//bool CollCircle(CObjBase* pObj);
	

	// ゲッター
	CObjBase* GetNext(){return m_pNext;};		// 次のポインタを取得
	CObjBase* GetPrev(){return m_pPrev;};		// 前のポインタを取得

	D3DXVECTOR3 GetPos(){return m_vPos;};
	D3DXVECTOR3 GetOldPos(){return m_vOldPos;};
	D3DXVECTOR3 GetSpeed(void) {return m_vSpd;};		// 速度ゲット
	D3DXVECTOR3 GetAccel(void) {return m_vAccel;};		// 加速度ゲット
	D3DXVECTOR3 GetSize(){return m_vSize;};
	D3DXVECTOR3 GetRadius(){return m_vRadius;};
	D3DXMATRIX  GetMatrix(void) {return m_world;};		// ワールドマトリックスゲット
	int			GetDrawType(){return m_nDrawType;};
	int			GetGroupID(){return m_nObjGroupID;};	// グループIDの取得
	int			GetTypeID(){return m_nObjTypeID;};		// タイプIDの取得
	int			GetIdentifID(){return m_nIdentifID;};
	int			GetCollType(){return m_nCollBasePoint;};
	bool		GetbUse(){return m_bUse;};

	// セッター
	void SetNext(CObjBase* pObj){m_pNext = pObj;};
	void SetPrev(CObjBase* pObj){m_pPrev = pObj;};
	void SetPostoOldPos(){m_vOldPos = m_vPos;};		// 座標保存
	void SetbAlpha(bool bAlpha){m_bAlphaBlend = bAlpha;};		// アルファブレンドの可否のセット
	void SetDelete(){m_bDelete = true;};		// 消去準備
	void SetbCull(bool bTrueIsBe){m_bCull = bTrueIsBe;};
	void SetSize(D3DXVECTOR3 vSize)
	{
		m_vSize = vSize;
		SetRadius(vSize /2.0f);
	};
	void SetRadius(D3DXVECTOR3 vRadius){m_vRadius = vRadius;};
	void SetSpeed(D3DXVECTOR3 vSpd){m_vSpd = vSpd;};
	void SetbUse(bool bUse){m_bUse = bUse;};

	// チェッカー
	bool CheckbeDelete(){return m_bDelete;};		// デリートするか
	
};

D3DXMATRIX CreateScreenMat();

