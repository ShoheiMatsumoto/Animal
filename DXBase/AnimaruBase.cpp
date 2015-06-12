#include "AnimaruBase.h"
#include "AnimalColl.h"

// アニまる状態列挙


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
	m_vSpd.y = -1.0f;
	
	// プレイヤー固有ステータス
	CSt.m_nMoveVecType = MOVEVEC_TYPE_RIGHT;		// 右向き
	CSt.m_fFallSpd = ADDFSPD;
	CSt.m_fJumpPow = 0.0f;
	CSt.m_fMovePow = 0.0f;
	CSt.m_bJump = false;

}

// 更新
void		CAnimaruBase::Update()
{
	Control();

	
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
		CSt.m_fMovePow -= BRKSPD;
		if(CSt.m_fMovePow <= 0.0f)
			CSt.m_fMovePow = 0.0f;
	}

	if(CSt.m_fMovePow < 0.0f)
	{
		CSt.m_fMovePow += BRKSPD;
		if(CSt.m_fMovePow >= 0.0f)
			CSt.m_fMovePow = 0.0f;
	}
	m_vSpd.x = CSt.m_fMovePow;
}

// 移動
void		CAnimaruBase::Move()
{
	

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
		SetAct();		// アクションはじめ
		break;

	case ST_RUN:
		Move();
		Fall();			// 自然落下
		SetJump();
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

	


}

// 走ってるか
bool		CAnimaruBase::CheckRun()
{
	
	return false;		// 止まってる
}

// 跳んでるか
bool		CAnimaruBase::CheckJump()
{
	// 上方向のスピードが出てる
	if(CSt.m_fJumpPow > 0.0f)
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
		}
		if(nLine == CROSSLINE_L || nLine == CROSSLINE_R)
		{	
			CSt.m_fMovePow = 0.0f;
		}
		m_vPos = vPos;
		break;

	case MAPPARTS_RUP:
		CSt.m_fFallSpd = -FFIRSTSPD;
		m_vPos = vPos;
		CSt.m_bJump = false;
		break;

	case MAPPARTS_RDOWN:
		CSt.m_fFallSpd = -FFIRSTSPD;
		m_vPos = vPos;
		CSt.m_bJump = false;
		break;
	}
}
// eof
