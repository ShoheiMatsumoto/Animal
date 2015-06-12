#include "Player.h"
#include "Input.h"
#include "MapPartsBase.h"
#include "AnimalColl.h"
#include "SceneBase.h"
#include "WkFactory.h"



float g_fJumpMax; 
float g_fJumpBrk; 
float g_fAddfSpd; 
float g_ffSpdMax; 
float g_fFirSpd;  
//float g_fSpdMax = 5.0f;


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

	p->m_vPos = vPos;
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

	m_nObjStatus = ST_STAND;
	m_vSpd.y = -1.0f;
	
	// プレイヤー固有ステータス
	CSt.m_nMoveVecType = MOVEVEC_TYPE_RIGHT;		// 右向き
	CSt.m_fFallSpd = ADDFSPD;
	CSt.m_fJumpPow = 0.0f;
	CSt.m_fMovePow = 0.0f;
	CSt.m_bJump = false;

	// アニまるセット
	SetAnimaru();


	/*g_fJumpMax = JUMPPOW;
	g_fJumpBrk = JUMPBRK;
	g_fAddfSpd = ADDFSPD;
	g_ffSpdMax = FSPDMAX;
	g_fFirSpd = FFIRSTSPD;*/
}

// 更新
void		CPlayer::Update()
{
	if(GETINPUT->GetKey(KEY_TRG, DIK_1))
		m_vPos = D3DXVECTOR3(0.0f, 280.0f, 0.0f);
		
	/*if(GETINPUT->GetKey(KEY_TRG, DIK_O))
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
		g_fAddfSpd -= 0.1f;*/

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


	//TCHAR		m_szDebug[4096];
	//
	//TCHAR	str[256];
	//
	//// 各種デバッグ用数値表示
	//m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
	//_stprintf(str, _T("OL ジャンプマックス:%f"), g_fJumpMax);
	//lstrcat(m_szDebug, str);
	//CSceneBase::GetThis()->GetGraph()->DrawText(10, 40, m_szDebug);

	//m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
	//_stprintf(str, _T("IK ジャンプブレーキ:%f"), g_fJumpBrk);
	//lstrcat(m_szDebug, str);
	//CSceneBase::GetThis()->GetGraph()->DrawText(10, 60, m_szDebug);
	//
	//m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
	//_stprintf(str, _T("UJ 落下マックス:%f"), g_ffSpdMax);
	//lstrcat(m_szDebug, str);
	//CSceneBase::GetThis()->GetGraph()->DrawText(10, 80, m_szDebug);

	//m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
	//_stprintf(str, _T("TG 落下加算:%f"), g_fAddfSpd);
	//lstrcat(m_szDebug, str);
	//CSceneBase::GetThis()->GetGraph()->DrawText(10, 100, m_szDebug);

	//m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
	//_stprintf(str, _T("YH 落下初速:%f"), g_fFirSpd);
	//lstrcat(m_szDebug, str);
	//CSceneBase::GetThis()->GetGraph()->DrawText(10, 120, m_szDebug);

	//m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
	//_stprintf(str, _T("YH 落下速度:%f"), m_fFallSpd);
	//lstrcat(m_szDebug, str);
	//CSceneBase::GetThis()->GetGraph()->DrawText(10, 140, m_szDebug);
	
}


// 解放
void		CPlayer::Release()
{

	delete this;
}


// 立ち
void		CPlayer::BacktoStand()
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
void		CPlayer::Move()
{
	// 右
	if(GETINPUT->GetKey(KEY_PRS, DIK_RIGHT))
	{
		//if(GETINPUT->GetKey(KEY_TRG, DIK_RIGHT))
			//ReverseLR(TEX_LRREV);

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
	if(GETINPUT->GetKey(KEY_PRS, DIK_LEFT))
	{
		//if(GETINPUT->GetKey(KEY_TRG, DIK_LEFT))
			

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

// ジャンプし始め
void		CPlayer::PushJump()
{
	if(GETINPUT->GetKey(KEY_TRG, DIK_SPACE))
	{
		if(!CSt.m_bJump)
		{
			m_nObjStatus = ST_JUMPUP;		// ステータスセット
			CSt.m_fJumpPow = JUMPPOW;	// 初期パワーセット
		}
	}

}


// ジャンプ
void		CPlayer::Jump()
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
void		CPlayer::Fall()
{
	m_vSpd.y = CSt.m_fFallSpd;

	CSt.m_fFallSpd -= 0.3f;
	if(CSt.m_fFallSpd <= -FSPDMAX)
		CSt.m_fFallSpd = -FSPDMAX;

	
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
	case ST_STAND:
		BacktoStand();
		Move();			// 移動
		Fall();			// 自然落下
		PushJump();		// ジャンプはじめ
		PushAct();		// アクションはじめ
		break;

	case ST_RUN:
		Move();
		Fall();			// 自然落下
		PushJump();
		PushAct();
		break;

	case ST_ACTION:
		Action();
		Fall();			// 自然落下
		break;

	case ST_JUMPUP:
		Move();
		Jump();
		//Fall();			// 自然落下
		PushAct();
		break;

	case ST_FALL:
		Fall();			// 自然落下
		break;
	default:

		break;
	}

	
}

// プレイヤーが置かれている環境をチェックし、ステータスを変更
void			CPlayer::CheckEnvir()
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
	if(CSt.m_fJumpPow > 0.0f)
		return true;

	return false;
}

// 落ちてるか
bool		CPlayer::CheckFall()
{
	// 下方向の初速以上のスピードが出てる
	if(CSt.m_fFallSpd < -(FFIRSTSPD + 1.0f))
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

// ↓アニマル関連
void CPlayer::SetAnimaru()
{
	// アニまる準備
	for(int i = 0; i < 12; i++)
		m_pAnimaruBox[i] = NULL;	// 初期化
	for(int i = 0; i < 3; i++)
		m_pAnimaruSlot[i] = NULL;

	// 使用可能かの状態を外部から読み込み

	// 生成
	D3DXVECTOR3 vPos = D3DXVECTOR3(m_vPos.x - 10.0f, 0.0f, 0.0f);
	CFactoryBase* pFac;
	pFac = CSceneBase::GetCurScene()->GetFactory();
	m_pAnimaruBox[ANIMARU_NO_NEZU] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_NEZU, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_USHI] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_USHI, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_TORA] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_TORA, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_MIMI] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_MIMI, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_TATSU] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_TATSU, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_HEBI] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_HEBI, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_UMA] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_UMA, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_MOKO] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_MERRY, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_SARU] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_SARU, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_TORI] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_TORI, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_INU] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_INU, 0, vPos);
	m_pAnimaruBox[ANIMARU_NO_URI] = (CAnimaruBase *)pFac->Request3D(WK_OBJ3D_URI, 0, vPos);

	for(int i = 0; i < ANIMARU_NO_MAX; i++)
		m_pAnimaruBox[i]->SetbUse(false);		// とりあえず非更新状態

	// 外部から現在スロットにセットされているアニまるをもらいスロットにセット
	// 今はとりあえず　ね、うし、とら
	m_pAnimaruSlot[0] = m_pAnimaruBox[ANIMARU_NO_NEZU];
	m_pAnimaruSlot[1] = m_pAnimaruBox[ANIMARU_NO_USHI];
	m_pAnimaruSlot[2] = m_pAnimaruBox[ANIMARU_NO_TORA];

	m_pAnimaruSlot[0]->SetbUse(true);
	m_pAnimaruSlot[1]->SetbUse(true);
	m_pAnimaruSlot[2]->SetbUse(true);
}

// 距離判定
void CPlayer::CheckAniDist()
{
	// 一匹目との距離を測る

}

// 座標保存
void CPlayer::PreservPos()
{
	m_vPrePos = m_vPos;
}

// eof
