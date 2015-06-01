#pragma once
#include "scenebase.h"
#include "SceneBase.h"
#include "Collision.h"
#include "FadeOut.h"
#include "FadeIn.h"


// 使用するテクスチャ
enum
{
	WK_N_TEX_0 = 0,
	WK_N_TEX_MOON,
	WK_N_TEX_CARTEN,

	WK_N_TEX_MAX,
};


// このシーンで使用する２Dオブジェクトの種類(目安)
enum
{
	WK_N_2D_OBJ_TEST = 0,

	// 最大数を元に最初のObjMgrの入れ物の数を設定
	WK_N_2D_OBJ_MAX// 後から入れ物のサイズを変えられる
};

// このシーン内で使用する３Dオブジェクトの種類
enum
{
	WK_N_3D_OBJ_MOON = 0,
	WK_N_3D_OBJ_TEST_BILL,

	WK_N_3D_OBJ_MAX
};

// 使用サウンド
enum
{
	WK_N_SOUND_TEST = 0,

	WK_N_SOUND_MAX			// 使用するのは最大数のみ
};

class CSceneWkN :
	public CSceneBase
{
public:
	CSceneWkN(void);
	virtual ~CSceneWkN(void);

	void Update();			// 更新
	void Draw();			// 描画
	void Release();
			//void InitTitle();		// 初期化
	static CSceneWkN* Create();	
	void CheckRunHit();
	//CImage* GetImage(int nTexNum){return m_pImage[nTexNum];};
	
	void SetChangeScene();
private:
	bool		 Initialize();

private:
	// インスタンス	
	CFadeOut* m_pFadeOut;
	CFadeIn* m_pFadeIn;

};

