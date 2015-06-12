// プレイヤークラス宣言
#pragma once

#include "billboard.h"
#include "AnimaruBase.h"

//enum
//{
//	PINP_TYPE_PRS,
//	PINP_TYPE_TRG,
//	PINP_TYPE_RLS,
//
//	PINP_TYPE_MAX
//};
//
//enum
//{
//	PINP_BTN_UP,
//	PINP_BTN_DOWN,
//	PINP_BTN_RIGHT,
//	PINP_BTN_LEFT,
//	PINP_BTN_SPACE,
//	PINP_BTN_SHIFT,
//	PINP_BTN_Q,
//	PINP_BTN_W,
//	PINP_BTN_E,
//	PINP_BTN_R,
//	PINP_BTN_Z,
//	PINP_BTN_X,
//
//	PINP_BTN_MAX
//};

class CPlayer :
	public CBillboard
{
protected:
	// bool m_bInput[PINP_TYPE_MAX][PINP_BTN_MAX];
	CContSt CSt;

	// アニマル関連
	CAnimaruBase* m_pAnimaruBox[12];		// 保存場所
	CAnimaruBase* m_pAnimaruSlot[3];		// スロット
	D3DXVECTOR3		m_vPrePos;			// 追従用座標

public:
	CPlayer(void);
	CPlayer(int n, int nTexNum);
	virtual ~CPlayer(void);

	CPlayer*	Create(int nID, int nTexNum, D3DXVECTOR3 vPos);
	void		Initialize();
	void		Update();
	void		Draw();
	void		HitUpdate(CObjBase* pObj, D3DXVECTOR3 vPos);
	void		Release();

	// 拡張
	void		SetInputData();

	void		BacktoStand();	// 立ち状態に戻ろうとする
	void		Move();			// 移動
	void		PushJump();		// ジャンプはじめ
	void		Jump();			// ジャンプ更新
	void		Fall();			// 落下
	void		PushAct();		// アクションはじめ
	void		Action();		// アクション更新

	void		Control();

	void		CheckEnvir();	// プレイヤーが置かれている環境をチェックし、ステータスを変更
	bool		CheckRun();		// 走ってるか
	bool		CheckJump();	// 跳んでるか
	bool		CheckFall();	// 落ちてるか
	
	// 判定後処理小分け
	void HitUDToMapParts(CObjBase* pObj, int nType, D3DXVECTOR3 vPos);

	// アニまる関連
	void SetAnimaru();			// アニマル初期セット
	void CheckAniDist();		// 距離判定
	void PreservPos();			// 座標保存
};

