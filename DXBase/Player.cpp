#include "Player.h"
#include "Input.h"


// 定数定義
// 移動系
#define PLAYER_ADDMSPD (0.05f)
#define PLAYER_MOVESPDMAX (4.0f)
#define PLAYER_BREAKERATE (1.5f)
#define PLAYER_BREAKISPD (0.1f)

// ジャンプ関連
#define PLAYER_JMPPOW (10.0f)
#define PLAYER_ADDJSPD ()
#define PLAYER_ADDFSPD ()


#define PLAYER_JUMPPOW (10.0f)

enum
{
	PLAYER_MOVEVEC_TYPE_RIGHT,
	PLAYER_MOVEVEC_TYPE_LEFT,

	
};

// プレイヤー状態列挙
enum
{
	PLST_STAND = 0,		// 立ち
	PLST_WALK,			// 歩き
	PLST_RUN,			// 走り
	PLST_ACTION,		// アクション
	PLST_JUMPUP,			// ジャンプ
	PLST_FALL,			// 落下

	PLST_ALL
};

CPlayer::CPlayer(void)
{
}

CPlayer::CPlayer(int n, int nTexID) : CBillboard(n, nTexID)
{

}

CPlayer::~CPlayer(void)
{
}

// 生成
CPlayer*	CPlayer::Create(int nID, int nTexNum, D3DXVECTOR3 vPos)
{
	CPlayer* p = new CPlayer(nID, nTexNum);

	p->Initialize();

	return p;
}

// 初期化
void		CPlayer::Initialize()
{
	m_nObjGroupID = OBJ3DGROUP_PLAYER;		// グループ設定
	//m_nDType = OT_2D;
	
	// 2Dステータスセット
	m_Board.ReSize(D3DXVECTOR2(32.0f, 64.0f));		
	m_nCollBasePoint = COLLBASEPOINT_BOTTOM;		// あたり判定基準点
	SetSize(D3DXVECTOR3(m_Board.GetSize().x, m_Board.GetSize().y, 0.0f));
	SetPosToMatrix();

	// ビルボード初期化
	InitializeBillboard();		// ビルボード初期処理
	SetLocalWkB();				// 基準座標を下に

	// ビルボード処理オフ
	m_bBillBoard = false;

	// カリングオフ
	SetbCull(true);

	m_bAlphaBlend = false;

	m_nObjStatus = PLST_STAND;

	// プレイヤー固有ステータス
	m_nMoveVecType = PLAYER_MOVEVEC_TYPE_RIGHT;		// 右向き
}

// 更新
void		CPlayer::Update()
{
	Control();

	m_vPos += m_vSpd;		// 座標への代入

	UpdateBillBoard();		// ビルボード更新
}

// 判定後処理
void		CPlayer::HitUpdate(CObjBase* pObj)
{

}

// 解放
void		CPlayer::Release()
{

	delete this;
}


// 立ち
void		CPlayer::BacktoStand()
{
	if(m_vSpd.x > 0.0f)
	{
		m_vSpd.x -= PLAYER_ADDMSPD;
		if(m_vSpd.x <= 0.0f)
			m_vSpd.x = 0.0f;
	}

	if(m_vSpd.x < 0.0f)
	{
		m_vSpd.x += PLAYER_ADDMSPD;
		if(m_vSpd.x >= 0.0f)
			m_vSpd.x = 0.0f;
	}

}

// 移動
void		CPlayer::Move()
{
	// 右
	if(GETINPUT->GetKey(KEY_PRS, DIK_RIGHT))
	{
		if(m_vSpd.x < -PLAYER_MOVESPDMAX / PLAYER_BREAKERATE)
			m_vSpd.x = -PLAYER_MOVESPDMAX / PLAYER_BREAKERATE;
		
		if(m_vSpd.x <= PLAYER_MOVESPDMAX)
		{
			m_vSpd.x += PLAYER_ADDMSPD;		// 加速
		}
		else
		{
			m_vSpd.x = PLAYER_MOVESPDMAX;	// 最大速度
		}
	}

	// 左
	if(GETINPUT->GetKey(KEY_PRS, DIK_LEFT))
	{
		if(m_vSpd.x > PLAYER_MOVESPDMAX / PLAYER_BREAKERATE)
			m_vSpd.x = PLAYER_MOVESPDMAX / PLAYER_BREAKERATE;

		if(m_vSpd.x >= -PLAYER_MOVESPDMAX)
		{
			m_vSpd.x -= PLAYER_ADDMSPD;		// 加速
		}
		else
		{
			m_vSpd.x = -PLAYER_MOVESPDMAX;	// 最大速度
		}
	}

	
}

// ジャンプし始め
void		CPlayer::PushJump()
{
	m_nObjStatus = PLST_JUMPUP;		// ステータスセット


}


// ジャンプ
void		CPlayer::Jump()
{

}
	
// 落下
void		CPlayer::Fall()
{
	// m_vSpd.y -= 
}

// アクション開始
void		CPlayer::PushAct()
{

}

// アクションコマンド
void		CPlayer::Action()
{

}

// 制御
void		CPlayer::Control()
{
	// 環境チェックステータス更新
	CheckEnvir();

	switch(m_nObjStatus)
	{
	case PLST_STAND:
		BacktoStand();
		Move();			// 移動
		PushJump();		// ジャンプはじめ
		PushAct();		// アクションはじめ
		break;

	case PLST_RUN:
		Move();
		PushJump();
		PushAct();
		break;

	case PLST_ACTION:
		Action();
		break;

	case PLST_JUMPUP:
		Move();
		Jump();
		PushAct();
		break;

	case PLST_FALL:

		break;
	default:

		break;
	}

	
}

// プレイヤーが置かれている環境をチェックし、ステータスを変更
void			CPlayer::CheckEnvir()
{
	m_nObjStatus = PLST_STAND;		// 

	if(CheckRun())
		m_nObjStatus = PLST_RUN;

	if(CheckJump())
		m_nObjStatus = PLST_JUMPUP;

	if(CheckFall())
		m_nObjStatus = PLST_FALL;

	


}

// 走ってるか
bool		CPlayer::CheckRun()
{
	// 上下方向のスピードが出てる
	if(m_vSpd.y > 0.0f || m_vSpd.y < 0.0f)
		return false;		// ジャンプ中または落下中である

	// 左右の入力がある
	if((GETINPUT->GetKey(KEY_PRS, DIK_RIGHT)) || (GETINPUT->GetKey(KEY_PRS, DIK_LEFT)))
		return true;

	return false;		// 止まってる
}

// 跳んでるか
bool		CPlayer::CheckJump()
{
	// 上方向のスピードが出てる
	if(m_vSpd.y > 0.0f)
		return true;

	return false;
}

// 落ちてるか
bool		CPlayer::CheckFall()
{
	// 下方向のスピードが出てる
	if(m_vSpd.y < 0.0f)
		return true;

	return false;
}

// 入力データ
//void		CPlayer::SetInputData()
//{
//	// プレス----------------------------------------------------------
//	// ↑
//	if(GETINPUT->GetKey(KEY_PRS, DIK_UP))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_UP] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_UP] = false;
//	
//	// ↓
//	if(GETINPUT->GetKey(KEY_PRS, DIK_DOWN))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_DOWN] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_DOWN] = false;
//
//	// ←
//	if(GETINPUT->GetKey(KEY_PRS, DIK_LEFT))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_LEFT] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_LEFT] = false;
//
//	// →
//	if(GETINPUT->GetKey(KEY_PRS, DIK_RIGHT))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_RIGHT] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_RIGHT] = false;
//
//	// SPACE
//	if(GETINPUT->GetKey(KEY_PRS, DIK_SPACE))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_SPACE] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_SPACE] = false;
//
//	// SHIFT
//	if(GETINPUT->GetKey(KEY_PRS, DIK_LSHIFT))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_SHIFT] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_SHIFT] = false;
//
//	// Q
//	if(GETINPUT->GetKey(KEY_PRS, DIK_Q))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_Q] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_Q] = false;
//
//	// W
//	if(GETINPUT->GetKey(KEY_PRS, DIK_W))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_W] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_W] = false;
//
//	// E
//	if(GETINPUT->GetKey(KEY_PRS, DIK_E))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_E] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_E] = false;
//
//	// R
//	if(GETINPUT->GetKey(KEY_PRS, DIK_R))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_R] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_R] = false;
//
//	// Z
//	if(GETINPUT->GetKey(KEY_PRS, DIK_Z))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_Z] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_Z] = false;
//
//	// X
//	if(GETINPUT->GetKey(KEY_PRS, DIK_X))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_X] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_X] = false;
//	// トリガー---------------------------------------------------------------
//	// ↑
//	if(GETINPUT->GetKey(KEY_TRG, DIK_))
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_LEFT] = true;
//	else
//		m_bInput[PINP_TYPE_PRS][PINP_BTN_LEFT] = false;
//
//
//	// リリース----------------------------------------------------------
//}

// eof
