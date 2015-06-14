#include "AnimaruBase.h"
#include "AnimalColl.h"
#include "Input.h"

// アニまる状態列挙

// 定数定義
#define DIST_ONE (100.0f)
#define DIST_TWO (50.0f)
#define BRK_DIST (100.0f)

#define ANIMARU_BRKONE (0.2f)
#define ANIMARU_BRKTWO (0.4f)

#define MOVEJUMPPOW (5.0f)

enum
{
	ANST_MOVEJUMP = ST_ALL,

	ANST_ALL
};

CAnimaruBase::CAnimaruBase(void)
{
}

CAnimaruBase::CAnimaruBase(int nGroupID, int nTypeID, int nTexID, D3DXVECTOR3 vPos) : CBillboard(nTypeID, nTexID)
{
	m_nObjGroupID = nGroupID;
	m_vPos = vPos;
}

CAnimaruBase::~CAnimaruBase(void)
{
	
}


// 生成
CAnimaruBase*	CAnimaruBase::Create(int nGroupID, int nTypeID, int nTexID, D3DXVECTOR3 vPos)
{
	CAnimaruBase* p = new CAnimaruBase(nGroupID, nTypeID, nTexID, vPos);

	p->Initialize();

	return p;
}

// 初期化
void		CAnimaruBase::Initialize()
{
	m_nObjGroupID = OBJ3DGROUP_ANIMARU;		// グループ設定
	//m_nDType = OT_2D;
	
	// 2Dステータスセット
	m_Board.ReSize(D3DXVECTOR2(64.0f, 64.0f));		
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

	m_nObjStatus = ST_STAND;
	//m_vSpd.y = -1.0f;
	
	// 固有ステータス
	CSt.m_nMoveVecType = MOVEVEC_TYPE_RIGHT;		// 右向き
	CSt.m_fFallSpd = ADDFSPD;
	CSt.m_fJumpPow = 0.0f;
	CSt.m_fMovePow = 0.0f;
	CSt.m_bJump = false;

	m_bChase = false;
	m_bCBrk = false;

}

// 更新
void		CAnimaruBase::Update()
{
	
	if(!m_bEvent)
	{
		Control();

		// 入力初期化
		InitInputData();
	}
	else	// ムービー用制御
	{

	}

	m_vPos += m_vSpd;		// 座標への代入
	UpdateBillBoard();		// ビルボード更新

	
}

// 解放
void		CAnimaruBase::Release()
{

	delete this;
}


// 立ち
void		CAnimaruBase::BacktoStand()
{
	if(CSt.m_fMovePow > 0.0f)
	{
		CSt.m_fMovePow -= CSt.m_fBrakePow;
		if(CSt.m_fMovePow <= 0.0f)
			CSt.m_fMovePow = 0.0f;
	}

	if(CSt.m_fMovePow < 0.0f)
	{
		CSt.m_fMovePow += CSt.m_fBrakePow;
		if(CSt.m_fMovePow >= 0.0f)
			CSt.m_fMovePow = 0.0f;
	}
	m_vSpd.x = CSt.m_fMovePow;
}

// 移動
void		CAnimaruBase::Move()
{
	// 追跡フラグが降りてたら
	if(!m_bChase)
		return;

	// 右
	//if(m_nChaseVec == CHASE_RIGHT)
	if(m_bInput[KEY_PRS][INP_BTN_RIGHT])
	{
		if(CSt.m_fMovePow < -MOVESPDMAX / BREAKERATE)
			CSt.m_fMovePow = -MOVESPDMAX / BREAKERATE;
		
		if(CSt.m_fMovePow <= MOVESPDMAX)
		{
			CSt.m_fMovePow += ADDMSPD;		// 加速
			
		}
		else
		{
			CSt.m_fMovePow = MOVESPDMAX;	// 最大速度
			
		}
	}

	// 左
	//if(m_nChaseVec == CHASE_LEFT)
	if(m_bInput[KEY_PRS][INP_BTN_LEFT])
	{
		if(CSt.m_fMovePow > MOVESPDMAX / BREAKERATE)
			CSt.m_fMovePow = MOVESPDMAX / BREAKERATE;

		if(CSt.m_fMovePow >= -MOVESPDMAX)
		{
			CSt.m_fMovePow -= ADDMSPD;		// 加速
		}
		else
		{
			CSt.m_fMovePow = -MOVESPDMAX;	// 最大速度
		}
	}

	if(CSt.m_fMovePow > 0.0f)
	{
		ReverseLR(TEX_LRREV);
	}
	else if(CSt.m_fMovePow < 0.0f)
	{
		ReverseLR(TEX_LRNORMAL);
	}

	m_vSpd.x = CSt.m_fMovePow;


}

// 移動ジャンプのセット
void CAnimaruBase::SetMJump()
{
	//if(m_bChase && !CSt.m_bJump)
	if(m_bChase && !CSt.m_bJump)
	{
		m_nObjStatus = ANST_MOVEJUMP;
		CSt.m_fJumpPow = MOVEJUMPPOW;
		
	}
}

// 移動時の小ジャンプ
void CAnimaruBase::MoveJump()
{
	m_vSpd.y = CSt.m_fJumpPow;		// スピードに変換

	CSt.m_fJumpPow -= JUMPBRK;

	if(CSt.m_fJumpPow <= 0.0f)
	{
		CSt.m_fFallSpd = 0.0f;
		CSt.m_bJump = true;
	}
}

// ジャンプし始め
void		CAnimaruBase::SetJump()
{
	
	
}


// ジャンプ
void		CAnimaruBase::Jump()
{
	m_vSpd.y = CSt.m_fJumpPow;		// スピードに変換

	CSt.m_fJumpPow -= JUMPBRK;
	
	if(CSt.m_fJumpPow <= 0.0f)
	{
		CSt.m_fFallSpd = 0.0f;
		CSt.m_bJump = true;
	}
}
	
// 落下
void		CAnimaruBase::Fall()
{
	m_vSpd.y = CSt.m_fFallSpd;

	CSt.m_fFallSpd -= 0.3f;
	if(CSt.m_fFallSpd <= -FSPDMAX)
		CSt.m_fFallSpd = -FSPDMAX;

	
}

// アクション開始
void		CAnimaruBase::SetAct()
{

}

// アクションコマンド
void		CAnimaruBase::Action()
{

}

// 制御
void		CAnimaruBase::Control()
{
	// 環境チェックステータス更新
	CheckEnvir();

	switch(m_nObjStatus)
	{
	case ST_STAND:
		BacktoStand();
		Move();			// 移動
		Fall();			// 自然落下
		SetJump();		// ジャンプはじめ
		SetMJump();
		SetAct();		// アクションはじめ
		break;

	case ST_RUN:
		Move();
		Fall();			// 自然落下
		SetJump();
		SetMJump();
		SetAct();
		break;

	case ST_ACTION:
		Action();
		Fall();			// 自然落下
		break;

	case ST_JUMPUP:
		Move();
		Jump();
		//Fall();			// 自然落下
		SetAct();
		break;

	case ST_FALL:
		Fall();			// 自然落下
		break;
	default:

		break;
	}

	
}

// プレイヤーが置かれている環境をチェックし、ステータスを変更
void			CAnimaruBase::CheckEnvir()
{
	m_nObjStatus = ST_STAND;		// 

	if(CheckRun())
		m_nObjStatus = ST_RUN;

	if(CheckJump())
		m_nObjStatus = ST_JUMPUP;

	if(CheckFall())
		m_nObjStatus = ST_FALL;

	CheckDist();
}

// 走ってるか
bool		CAnimaruBase::CheckRun()
{
	// 追跡フラグがたってる
	if(m_bChase)		
		return true;

	return false;		// 止まってる




}

// 跳んでるか
bool		CAnimaruBase::CheckJump()
{
	// 上方向のスピードが出てる
	if(CSt.m_fJumpPow > 0.0f && m_bChase)
		return true;

	return false;
}

// 落ちてるか
bool		CAnimaruBase::CheckFall()
{
	// 下方向の初速以上のスピードが出てる
	if(CSt.m_fFallSpd < -(FFIRSTSPD + 1.0f))
		return true;

	return false;
}

// 判定後処理
void		CAnimaruBase::HitUpdate(CObjBase* pObj, D3DXVECTOR3 vPos)
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
void CAnimaruBase::HitUDToMapParts(CObjBase* pObj, int nType, D3DXVECTOR3 vPos)
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
			CSt.m_fFallSpd = -FFIRSTSPD;
			CSt.m_bJump = false;
			//m_bInput[KEY_TRG][INP_BTN_SPACE] = true;
		}
		if(nLine == CROSSLINE_L || nLine == CROSSLINE_R)
		{	
			CSt.m_fMovePow = 0.0f;
		}
		m_vPos = vWkPos;
		break;

	case MAPPARTS_RUP:
		CSt.m_fFallSpd = -FFIRSTSPD;
		m_vPos = vPos;
		CSt.m_bJump = false;
		//m_bInput[KEY_TRG][INP_BTN_SPACE] = true;
		break;

	case MAPPARTS_RDOWN:
		CSt.m_fFallSpd = -FFIRSTSPD;
		m_vPos = vPos;
		CSt.m_bJump = false;
		//m_bInput[KEY_TRG][INP_BTN_SPACE] = true;
		break;
	}
}

void CAnimaruBase::SetbChase(bool bChase, int nChaseVec)
{
	m_bChase = bChase;		// フラグON

	m_nChaseVec = nChaseVec;	// 追跡方向の決定

	if(nChaseVec == CHASE_RIGHT)
	{
		m_bInput[KEY_PRS][INP_BTN_RIGHT] = true;
	}
	
	if(nChaseVec == CHASE_LEFT)
	{
		m_bInput[KEY_PRS][INP_BTN_LEFT] = true;
	}

}

void CAnimaruBase::SetSlotID(int nSlotID)
{
	m_nSlotID = nSlotID;

	if(nSlotID == 0)
		CSt.m_fBrakePow = ANIMARU_BRKONE;
	else if(nSlotID >= 1)
		CSt.m_fBrakePow = ANIMARU_BRKTWO;
}


// 追跡対象との距離チェック
void CAnimaruBase::CheckDist()
{
	float Subx = m_pvChaseTargetPos->x - m_vPos.x; 
	float fDist;
	int nVec;

	//fDist = DIST_ONE;

	// IDによる距離の違い
	if(m_nSlotID == 0)
		fDist = DIST_ONE;
	else if(m_nSlotID >= 1)
		fDist = DIST_TWO;

	if(abs(Subx) > fDist)
	{
		if(Subx > 0.0f)
			nVec = CHASE_RIGHT;		// 正なら右方向へ追跡
		else
			nVec = CHASE_LEFT;		// 正なら左方向へ追跡

		// 追跡フラグと方向のセット
		SetbChase(true, nVec);

		if(m_nSlotID >= 1)
		{
			if(abs(Subx) >= BRK_DIST)
			{
				m_bCBrk = true;
			}
		}
	}
	
	
	if(m_nSlotID == 0)
	{
		if(abs(Subx) <= fDist)
			SetbChase(false, CHASE_NONE);
	}

	
	if(m_nSlotID >= 1)
	{
		if(m_bCBrk)
		{
			if(abs(Subx) <= BRK_DIST)
			{
				SetbChase(false, CHASE_NONE);
				if(abs(Subx) <= fDist)
					m_bCBrk = false;
			}
		}
	}
	


		
	
	
}


// eof
