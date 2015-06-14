#pragma once
#include "scenebase.h"

#include "FadeOut.h"
#include "FadeIn.h"


// 使用するテクスチャ
enum
{
	WK_TEX_NONE = 0,		// テクスチャなし
	WK_TEX_PLAYER,
	WK_TEX_MOON,
	WK_TEX_CARTEN,
	WK_TEX_SQUARE,
	WK_TEX_SLOPE,
	WK_TEX_NEZU,
	WK_TEX_USHI,
	WK_TEX_TORA,
	WK_TEX_MIMI,
	WK_TEX_TATSU,
	WK_TEX_HEBI,
	WK_TEX_UMA,
	WK_TEX_MERRY,
	WK_TEX_SARU,
	WK_TEX_TORI,
	WK_TEX_INU,
	WK_TEX_URI,

	WK_TEX_MAX,
};


// このシーンで使用する２Dオブジェクトの種類(目安)
enum
{
	WK_2D_OBJ_TEST = 0,

	// 最大数を元に最初のObjMgrの入れ物の数を設定
	WK_2D_OBJ_MAX// 後から入れ物のサイズを変えられる
};

// このシーン内で使用する３Dオブジェクトの種類
enum
{
	WK_3D_OBJ_MOON = 0,
	WK_3D_OBJ_TEST_BILL,

	WK_3D_OBJ_MAX
};

// 使用サウンド
enum
{
	WK_SOUND_TEST = 0,

	WK_SOUND_MAX			// 使用するのは最大数のみ
};

class CSceneWk :
	public CSceneBase
{
public:
	CSceneWk(void);
	virtual ~CSceneWk(void);

	void Update();			// 更新
	void Draw();			// 描画
	void Release();
			//void InitTitle();		// 初期化
	static CSceneWk* Create();	
	void CheckRunHit();
	//CImage* GetImage(int nTexNum){return m_pImage[nTexNum];};
	
	void SetChangeScene();
private:
	bool		 Initialize();
	CObjBase*	m_pControlObj;

private:
	// インスタンス	
	CFadeOut* m_pFadeOut;
	CFadeIn* m_pFadeIn;

};

