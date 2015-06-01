#pragma once
#include "scenebase.h"
#include "SceneBase.h"
#include "Collision.h"
#include "FadeOut.h"
#include "FadeIn.h"


// 使用するテクスチャ
enum
{
	WK_I_TEX_0 = 0,
	WK_I_TEX_MOON,
	WK_I_TEX_CARTEN,

	WK_I_TEX_MAX,
};


// このシーンで使用する２Dオブジェクトの種類(目安)
enum
{
	WK_I_2D_OBJ_TEST = 0,

	// 最大数を元に最初のObjMgrの入れ物の数を設定
	WK_I_2D_OBJ_MAX// 後から入れ物のサイズを変えられる
};

// このシーン内で使用する３Dオブジェクトの種類
enum
{
	WK_I_3D_OBJ_MOON = 0,
	WK_I_3D_OBJ_TEST_BILL,

	WK_I_3D_OBJ_MAX
};

// 使用サウンド
enum
{
	WK_I_SOUND_TEST = 0,

	WK_I_SOUND_MAX			// 使用するのは最大数のみ
};

class CSceneWkI :
	public CSceneBase
{
public:
	CSceneWkI(void);
	virtual ~CSceneWkI(void);

	void Update();			// 更新
	void Draw();			// 描画
	void Release();
			//void InitTitle();		// 初期化
	static CSceneWkI* Create();	
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

