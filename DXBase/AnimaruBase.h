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
	CContSt CSt;	// 基本ステータス
	int		m_nSlotID;		// 自分が何番目に入ってるか
	int		m_nAnimaruSt;	// アニマル固有の状態
	int		m_nCoolTime;	// クールタイム
	
	// 追跡関連
	bool	m_bChase;
	bool	m_bCBrk;
	int		m_nChaseVec;
#define		CHASE_NONE  0
#define		CHASE_RIGHT 1
#define		CHASE_LEFT  2

	D3DXVECTOR3* m_pvChaseTargetPos;		// 追跡ターゲット（Pキャラ）の座標
	

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
	void SetMJump();		// 移動ジャンプのセット
	void MoveJump();		// 移動時の小ジャンプ


	void Control();

	// 状態チェッカー
	void CheckEnvir();
	bool CheckRun();
	bool CheckJump();
	bool CheckFall();

	void CheckDist();		// 追跡対象との距離チェック
	
	// セッター
	void SetSlotID(int nSlotID);
	void SetbChase(bool bChase, int nChaseVec);
	void SetChasePos(D3DXVECTOR3* pvPos){m_pvChaseTargetPos = pvPos;};

	// 判定後
	void HitUDToMapParts(CObjBase* pObj, int nType, D3DXVECTOR3 vPos);


};

