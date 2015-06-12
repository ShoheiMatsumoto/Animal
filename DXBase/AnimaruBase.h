#pragma once

// インクルード
#include "billboard.h"

// アニマルNo
enum
{
	ANIMARU_NO_NEZU = 0,
	ANIMARU_NO_USHI,
	ANIMARU_NO_TORA,
	ANIMARU_NO_MIMI,
	ANIMARU_NO_TATSU,
	ANIMARU_NO_HEBI,
	ANIMARU_NO_UMA,
	ANIMARU_NO_MOKO,
	ANIMARU_NO_SARU,
	ANIMARU_NO_TORI,
	ANIMARU_NO_INU,
	ANIMARU_NO_URI,

	ANIMARU_NO_MAX
};

// アニまるの基本機能クラス
class CAnimaruBase :
	public CBillboard
{
protected:
	CContSt CSt;	

public:
	CAnimaruBase(void);
	CAnimaruBase(int nGroupID, int nTypeID, int nTexID, D3DXVECTOR3 vPos);
	virtual ~CAnimaruBase(void);

	virtual CAnimaruBase* Create(int nGroupID, int nTypeID, int nTexID, D3DXVECTOR3 vPos);
	void Initialize();
	void Update();
	//void Draw();
	void Release();
	void HitUpdate(CObjBase* pObj, D3DXVECTOR3 vPos);

	void BacktoStand();		// 立ち状態に戻ろうとする
	void Move();			// 移動
	void SetJump();			// ジャンプのセット
	void Jump();			// ジャンプ
	void Fall();			// 落下
	void SetAct();			// アクションセット
	void Action();			// アクション

	void Control();

	void CheckEnvir();
	bool CheckRun();
	bool CheckJump();
	bool CheckFall();

	void HitUDToMapParts(CObjBase* pObj, int nType, D3DXVECTOR3 vPos);
};

