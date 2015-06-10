// オブジェマネージャクラス宣言
#pragma once

// インクルード
#include "ObjBase.h"
#include "Object2D.h"
#include "Object3D.h"
#include "Collision.h"

#define DRAWOBJ_MAX (512)

//オブジェ管理クラス
// シーン毎に生成する。
// シーンごとに違う入れ物でオブジェを管理していく。
class CObjMgr
{
protected:
	

public:
	CObjMgr(void);
	virtual ~CObjMgr(void);

	// 基本機能
	CObjMgr* Create();		// オブジェマネージャ生成
	void Initialize();		// 初期化処理
	void InitList();		// リストの初期化

	void SetDrawList(CObject2D* pObj);			// 2D用の描画リストのセット
	void ResetDrawList();		// オブジェを消した際のリストのリセット
	void DrawSort();			// 描画セット

	void Update2D();		// 2DObjの更新
	void Update3D();		// 3DObjの更新
	void AllUpdate();		// 全OBJの更新
	
	void Draw2D();			// 2DObjの描画
	void Draw3D();			// 3DObjの描画
	void AllDraw();			// 全OBJの描画
	
	void Release();			// 解放

	// 拡張
	void EntryObj2D(CObjBase* pObj);		// オブジェ登録
	void EntryObj3D(CObjBase* pObj);		// オブジェ登録
	// void ReleaseObj2D();

	void DeleteObj();		// オブジェ消去
	void DeleteObj2D();
	void DeleteObj3D();
	
	void ReleaseList();		// リストの解放
	void ReleaseList2D();
	void ReleaseList3D();
	// void Hit(CObjBase* pObj){};		// あたり判定後処理

	// ゲッター
	CObject2D*	GetListTop2D(int nGroupID);		// 実際トップにある空OBJはとばす
	CObject3D*	GetListTop3D(int nGroupID);
	CObjBase*	GetIdentifObj2D(int nGID, int nTID, int nIID);		// 個別のオブジェクトを取得
	CObjBase*	GetIdentifObj3D(int nGID, int nTID, int nIID);		// 個別のオブジェクトを取得

	// セッター
	void SetbReset(){m_bResetDrawList = true;};
private:
	CObjBase*	m_pObj;
	CObject2D* m_p2DObj;
	CObject3D* m_p3DObj;

	CObject2D* m_pObjListTop2D[OBJ2DGROUP_MAX];		// 動的リスト
	CObject3D* m_pObjListTop3D[OBJ3DGROUP_MAX];		// 動的リスト

	CObject2D* m_pObj2DDraw[DRAWOBJ_MAX];	// ２D描画用
	
	bool	m_bResetDrawList;		// 2D用描画リストリセットフラグ

	int		m_nCurDrawType;			// 描画タイプ
};

