#pragma once
#include "SceneBase.h"
#include "Collision.h"
#include "FadeOut.h"
#include "FadeIn.h"

// 使用するメッシュ
enum 
{
	T_MESH_A = 0,

	T_MESH_MAX
};

// 使用するテクスチャ
enum
{
	T_TEX_0 = 0,
	T_TEX_MOON,
	T_TEX_CARTEN,

	T_TEX_MAX,
};


// タイトル内で使用する２Dオブジェクトの種類(目安)
enum
{
	T_2D_OBJ_TEST = 0,

	// 最大数を元に最初のObjMgrの入れ物の数を設定
	T_2D_OBJ_MAX// 後から入れ物のサイズを変えられる
};

// タイトル内で使用する３Dオブジェクトの種類
enum
{
	T_3D_OBJ_TEST = 0,
	T_3D_OBJ_TEST_BILL,

	T_3D_OBJ_MAX
};

// 使用サウンド
enum
{
	T_SOUND_TEST = 0,

	T_SOUND_MAX			// 使用するのは最大数のみ
};

class CTitle : public CSceneBase
{
public:
	CTitle(void);
	~CTitle(void);

	void Update();			// 更新
	void Draw();			// 描画
	void Release();
			//void InitTitle();		// 初期化
	static CSceneBase* Create();	
	void CheckRunHit();
	//CImage* GetImage(int nTexNum){return m_pImage[nTexNum];};
	
	void SetChangeScene();
private:
	bool		 Initialize();
	
private:

	//CMesh		 m_Mesh[T_MESH_MAX];
	//CMesh		 m_MMesh[MORPMODEL_MAX];
	//CImage*		 m_pImage[TEX_ALL];

	// インスタンス	
	CFadeOut* m_pFadeOut;
	CFadeIn* m_pFadeIn;

	int    m_nSwitch;

};

