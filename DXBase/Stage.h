#pragma once
#include "SceneBase.h"
#include "Image.h"
#include "TestBill.h"
#include "FadeOut.h"
#include "FadeIn.h"

// 使用メッシュ
enum
{
	S_MESH_PLAYER = 0,
	S_MESH_ENEMY,
	S_MESH_MAP,
	S_MESH_SKY,		// スカイドーム

	S_NMESH,

	S_MESH_DOLL,
	S_MESH_BUNNY,
	// S_MESH_BATTLE,

	S_MESH_MAX
};

// 使用テクスチャ
enum
{
	S_TEX_TEST = 0,
	S_TEX_CARTEN,

	S_TEX_MAX
};

// ステージクラス
class CStage : public CSceneBase
{
private:
	static CStage*		m_pThis;

	// 使用オブジェクト先頭アドレス入れ
	CFadeOut* m_pFadeOut;
	CFadeIn* m_pFadeIn;
	
public:
	CStage(void);					// コンストラクタ
	virtual ~CStage(void);			// デストラクタ

	void InitReturn();
	virtual void Update();			// 更新
	virtual void Draw();		// 描画処理

	static void Create();		// 生成
	virtual void Release();		// 解放処理

	void UnbushStage();			// マップ探索のオブジェを伏せる
	void PopStage();			// 上の反対

	// ゲッター
	static CStage*	GetThis(){return m_pThis;};
	
	// セッター
	
private:
	void Initialize();		// 初期化処理
	

};

