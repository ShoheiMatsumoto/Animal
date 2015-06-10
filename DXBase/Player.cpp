#include "Player.h"
#include "Input.h"
#include "MapPartsBase.h"
#include "AnimalColl.h"
#include "SceneBase.h"


// 定数定義
// 移動系
#define PLAYER_ADDMSPD (0.1f)
#define PLAYER_MOVESPDMAX (4.0f)
#define PLAYER_BREAKERATE (1.5f)
#define PLAYER_BRKSPD (0.1f)

// ジャンプ関連

#define PLAYER_ADDJSPD ()
#define PLAYER_FFIRSTSPD (0.5f)
#define PLAYER_ADDFSPD (0.4f / 60.0f)
#define PLAYER_FSPDMAX (10.0f)
#define PLAYER_JUMPPOW (10.0f)
#define PLAYER_JUMPBRK (0.3f)
float g_fJumpMax = PLAYER_JUMPPOW;
float g_fJumpBrk = PLAYER_JUMPBRK;
float g_fAddfSpd = PLAYER_ADDFSPD;
float g_ffSpdMax = PLAYER_FSPDMAX;
float g_fFirSpd = PLAYER_FFIRSTSPD;
//float g_fSpdMax = 5.0f;



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
	m_vSpd.y = -1.0f;
	
	// プレイヤー固有ステータス
	m_nMoveVecType = PLAYER_MOVEVEC_TYPE_RIGHT;		// 右向き
	m_fFallSpd = PLAYER_ADDFSPD;
	m_fJumpPow = 0.0f;
	m_fMovePow = 0.0f;
	m_bJump = false;
}

// 更新
void		CPlayer::Update()
{
	if(GETINPUT->GetKey(KEY_TRG, DIK_1))
		m_vPos = D3DXVECTOR3(0.0f, 280.0f, 0.0f);
		
	if(GETINPUT->GetKey(KEY_TRG, DIK_O))
		g_fJumpMax += 0.1f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_L))
		g_fJumpMax -= 0.1f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_I))
		g_fJumpBrk += 0.01f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_K))
		g_fJumpBrk -= 0.01f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_U))
		g_ffSpdMax += 0.1f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_J))
		g_ffSpdMax -= 0.1f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_Y))
		g_fFirSpd += 0.1f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_H))
		g_fFirSpd -= 0.1f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_T))
		g_fAddfSpd += 0.1f;

	if(GETINPUT->GetKey(KEY_TRG, DIK_G))
		g_fAddfSpd -= 0.1f;

	Control();

	
	m_vPos += m_vSpd;		// 座標への代入

	

	UpdateBillBoard();		// ビルボード更新
}

void		CPlayer::Draw()
{
	

	//// ワールドマトリックスをセット
	if (m_world) 
		CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &m_world);


	// 描画
	CGraphics::GetDevice()->SetFVF(FVF_DVERTEX);

	CGraphics::GetDevice()->SetTexture(0, m_Board.m_pImage->GetTexture());						// テクスチャを登録
	CGraphics::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_verWk, sizeof(DVERTEX));// ポリゴン描画


	TCHAR		m_szDebug[4096];
	
	TCHAR	str[256];
	
	// 各種デバッグ用数値表示
	m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
	_stprintf(str, _T("OL ジャンプマックス:%f"), g_fJumpMax);
	lstrcat(m_szDebug, str);
	CSceneBase::GetThis()->GetGraph()->DrawText(10, 40, m_szDebug);

	m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
	_stprintf(str, _T("IK ジャンプブレーキ:%f"), g_fJumpBrk);
	lstrcat(m_szDebug, str);
	CSceneBase::GetThis()->GetGraph()->DrawText(10, 60, m_szDebug);
	
	m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
	_stprintf(str, _T("UJ 落下マックス:%f"), g_ffSpdMax);
	lstrcat(m_szDebug, str);
	CSceneBase::GetThis()->GetGraph()->DrawText(10, 80, m_szDebug);

	m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
	_stprintf(str, _T("TG 落下加算:%f"), g_fAddfSpd);
	lstrcat(m_szDebug, str);
	CSceneBase::GetThis()->GetGraph()->DrawText(10, 100, m_szDebug);

	m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
	_stprintf(str, _T("YH 落下初速:%f"), g_fFirSpd);
	lstrcat(m_szDebug, str);
	CSceneBase::GetThis()->GetGraph()->DrawText(10, 120, m_szDebug);

	m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
	_stprintf(str, _T("YH 落下速度:%f"), m_fFallSpd);
	lstrcat(m_szDebug, str);
	CSceneBase::GetThis()->GetGraph()->DrawText(10, 140, m_szDebug);
	
}


// 解放
void		CPlayer::Release()
{

	delete this;
}


// 立ち
void		CPlayer::BacktoStand()
{
	if(m_fMovePow > 0.0f)
	{
		m_fMovePow -= PLAYER_BRKSPD;
		if(m_fMovePow <= 0.0f)
			m_fMovePow = 0.0f;
	}

	if(m_fMovePow < 0.0f)
	{
		m_fMovePow += PLAYER_BRKSPD;
		if(m_fMovePow >= 0.0f)
			m_fMovePow = 0.0f;
	}
	m_vSpd.x = m_fMovePow;
}

// 移動
void		CPlayer::Move()
{
	// 右
	if(GETINPUT->GetKey(KEY_PRS, DIK_RIGHT))
	{
		//if(GETINPUT->GetKey(KEY_TRG, DIK_RIGHT))
			//ReverseLR(TEX_LRREV);

		if(m_fMovePow < -PLAYER_MOVESPDMAX / PLAYER_BREAKERATE)
			m_fMovePow = -PLAYER_MOVESPDMAX / PLAYER_BREAKERATE;
		

		if(m_fMovePow <= PLAYER_MOVESPDMAX)
		{
			m_fMovePow += PLAYER_ADDMSPD;		// 加速
			
		}
		else
		{
			m_fMovePow = PLAYER_MOVESPDMAX;	// 最大速度
			
		}
	}

	// 左
	if(GETINPUT->GetKey(KEY_PRS, DIK_LEFT))
	{
		//if(GETINPUT->GetKey(KEY_TRG, DIK_LEFT))
			

		if(m_fMovePow > PLAYER_MOVESPDMAX / PLAYER_BREAKERATE)
			m_fMovePow = PLAYER_MOVESPDMAX / PLAYER_BREAKERATE;

		if(m_fMovePow >= -PLAYER_MOVESPDMAX)
		{
			m_fMovePow -= PLAYER_ADDMSPD;		// 加速
		}
		else
		{
			m_fMovePow = -PLAYER_MOVESPDMAX;	// 最大速度
		}
	}

	if(m_fMovePow > 0.0f)
	{
		ReverseLR(TEX_LRREV);
	}
	else if(m_fMovePow < 0.0f)
	{
		ReverseLR(TEX_LRNORMAL);
	}

	m_vSpd.x = m_fMovePow;

	
}

// ジャンプし始め
void		CPlayer::PushJump()
{
	if(GETINPUT->GetKey(KEY_TRG, DIK_SPACE))
	{
		if(!m_bJump)
		{
			m_nObjStatus = PLST_JUMPUP;		// ステータスセット
			//m_fJumpPow = PLAYER_JUMPPOW;	// 初期パワーセット
			m_fJumpPow = g_fJumpMax;
			
			
		}
	}

}


// ジャンプ
void		CPlayer::Jump()
{
	m_vSpd.y = m_fJumpPow;		// スピードに変換

	//m_fJumpPow -= PLAYER_JUMPBRK;
	//if(m_fJumpPow >= 2.0f)
	//{
		m_fJumpPow -= g_fJumpBrk;
	//}
	

	if(m_fJumpPow <= 0.0f)
	{
		m_fFallSpd = 0.0f;
		m_bJump = true;
	}
}
	
// 落下
void		CPlayer::Fall()
{
	m_vSpd.y = m_fFallSpd;

	m_fFallSpd -= 0.3f;
	if(m_fFallSpd <= -PLAYER_FSPDMAX)
		m_fFallSpd = -PLAYER_FSPDMAX;

	
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
		Fall();			// 自然落下
		PushJump();		// ジャンプはじめ
		PushAct();		// アクションはじめ
		break;

	case PLST_RUN:
		Move();
		Fall();			// 自然落下
		PushJump();
		PushAct();
		break;

	case PLST_ACTION:
		Action();
		Fall();			// 自然落下
		break;

	case PLST_JUMPUP:
		Move();
		Jump();
		//Fall();			// 自然落下
		PushAct();
		break;

	case PLST_FALL:
		Fall();			// 自然落下
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
	//if(m_vSpd.y > 0.0f || m_vSpd.y < 0.0f)
	//	return false;		// ジャンプ中または落下中である

	// 両方入力してる
	if((GETINPUT->GetKey(KEY_PRS, DIK_RIGHT)) && (GETINPUT->GetKey(KEY_PRS, DIK_LEFT)))
		return false;

	// 左右の入力がある
	if((GETINPUT->GetKey(KEY_PRS, DIK_RIGHT)) || (GETINPUT->GetKey(KEY_PRS, DIK_LEFT)))
		return true;

	return false;		// 止まってる
}

// 跳んでるか
bool		CPlayer::CheckJump()
{
	// 上方向のスピードが出てる
	if(m_fJumpPow > 0.0f)
		return true;

	return false;
}

// 落ちてるか
bool		CPlayer::CheckFall()
{
	// 下方向の初速以上のスピードが出てる
	if(m_fFallSpd < -(PLAYER_FFIRSTSPD + 1.0f))
		return true;

	return false;
}

// 判定後処理
void		CPlayer::HitUpdate(CObjBase* pObj, D3DXVECTOR3 vPos)
{
	// m_vPos = vPos;
	UpdateBillBoard();		// ビルボード更新
	int nObjGroup = pObj->GetGroupID();

	switch(nObjGroup)
	{
	case OBJ3DGROUP_MAP:
		HitUDToMapParts(pObj, pObj->GetTypeID(), vPos);
		break;

	default:

		break;
	}
}

// マップのパーツ相手の後処理
void CPlayer::HitUDToMapParts(CObjBase* pObj, int nType, D3DXVECTOR3 vPos)
{
	CAnimalColl Coll;
	D3DXVECTOR3 vWkPos;
	int nLine;

	// 種類ごとに
	switch(nType)
	{
	case MAPPARTS_SQUARE:
		vWkPos = Coll.GetMapBoxCrossPos(this, (CMapPartsBase*)pObj, &nLine);
		if(nLine == CROSSLINE_T)
		{	
			m_fFallSpd = -PLAYER_FFIRSTSPD;
			m_bJump = false;
		}
		if(nLine == CROSSLINE_L || nLine == CROSSLINE_R)
		{	
			m_fMovePow = 0.0f;
		}
		m_vPos = vPos;
		break;

	case MAPPARTS_RUP:
		m_fFallSpd = -PLAYER_FFIRSTSPD;
		m_vPos = vPos;
		m_bJump = false;
		break;

	case MAPPARTS_RDOWN:
		m_fFallSpd = -PLAYER_FFIRSTSPD;
		m_vPos = vPos;
		m_bJump = false;
		break;
	}
}
// eof
