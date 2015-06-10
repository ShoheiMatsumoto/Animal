// 3D描画オブジェクト クラス定義
#pragma once
#include "ObjBase.h"

#define FVF_DVERTEX		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// オブジェクト種類


// オブジェクト次元タイプ
enum
{
	OT_3D,
	OT_2D,
	OT_BILLBOARD,

	OT_MAX
};

// 投影法列挙
enum
{
	VIEWPROJ_PERS = 0,
	VIEWPROJ_ORT,
};

// オブジェクトステータス
enum
{
	OBJST_NONE = 0,		// 通常
	OBJST_DELETE,		// 消去準備
	OBJST_NOUPDATE,		// 更新しない
	OBJST_NODRAW,		// 描画しない
	OBJST_UNBUSH,		//　更新描画ともにしない 

	OBJST_ALL
};

#define MAX_OBJTYPE (20)
#define PUTOBJ_MAX 1000 

class CObject3D : public CObjBase
{
protected:
	// リスト関連	
	//CObject3D* m_pNext;		// 次
	//CObject3D* m_pPrev;		// 前

	D3DXVECTOR3			m_vLocalVec[3];	// ローカル座標軸 

	// 3Dメッシュ用
	//CMesh				m_Mesh;
	CMesh*				m_pMesh;	// メッシュへのポインタ
	
	// ステータス
	bool				m_bUse;
	bool				m_bSphere;
	bool				m_bBox;
	
	// 描画関連
	int					m_nViewProjType;	// 投影法

public:
	//CObject3D(int nObjType);
	CObject3D();
	CObject3D(int nID);
	virtual ~CObject3D(void);

	// リスト管理
	//void InitListTop();
	
	// 共通機能
	//CObject3D* Create();
	void Initilaize();		// 初期化
	virtual void Update(void);		// 更新
	// virtual void SetViewProj();
	virtual void DrawSetUp();
	virtual void DrawEnd();
	virtual void Draw();		// 不透明部分描画
	virtual void DrawAlpha(void);	// 透明部分描画
	virtual void Release(){};			// 解放 

	// 共通動作

	// 拡張
	bool CollBox(CObjBase* pObj){};
	bool CollSphere(CObjBase* pObj){};

	// セッター
	void SetPosToMatrix();		// マトリックスへの座標セット
	void SetAccel(D3DXVECTOR3& accel) {m_vAccel = accel;};
	void SetMesh(CMesh* pMesh) {m_pMesh = pMesh;};	// メッシュのセット
	//void SetMesh(CMesh Mesh) {m_Mesh = Mesh;};	// メッシュのセット
	void SetObjStatus(int nStatus){m_nObjStatus = nStatus;};
	void SetSpeed(D3DXVECTOR3& speed) {m_vSpd = speed;};
	void SetBeAlphaBlend(bool bAlpha){m_bAlphaBlend = bAlpha;}
	
	// ゲッター
	CMesh* GetMesh(void) {return m_pMesh;};				// メッシュ情報ゲット
	bool GetUse(){return m_bUse;};
	int		GetViewType(){return m_nViewProjType;};

};

