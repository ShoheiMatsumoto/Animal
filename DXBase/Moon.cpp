#include "Moon.h"
#include "Input.h"
#include "Graphics.h"
#include "SceneBase.h"
#include "Camera.h"
#include "SceneBase.h"


CMoon::CMoon(void)
{
}

CMoon::CMoon(int nID, int nTexNum) : CBillboard(nID, nTexNum)
{

}


CMoon::~CMoon(void)
{

}


CMoon*	CMoon::Create(int nID, int nTexNum, D3DXVECTOR3 vPos)
{
	CMoon*	pTest = new CMoon(nID, nTexNum);

	pTest->m_vPos = vPos;

	pTest->Initialize();

	return pTest;
}

void		CMoon::Initialize()
{
	m_nObjGroupID = OBJ3DGROUP_PLAYER;		// グループ設定
	//m_nDType = OT_2D;
	
	// 2Dステータスセット
	
	m_Board.ReSize(D3DXVECTOR2(64.0f, 64.0f));		
	m_nCollBasePoint = COLLBASEPOINT_BOTTOM;		// あたり判定基準点
	SetSize(D3DXVECTOR3(64.0f, 64.0f, 0.0f));
	SetPosToMatrix();

	// ビルボード初期化
	InitializeBillboard();		// ビルボード初期処理
	SetLocalWkB();				// 基準座標を下に

	// ビルボード処理オフ
	m_bBillBoard = false;

	// カリングオフ
	SetbCull(true);

	m_bAlphaBlend = false;
}
#define BILLSPD (1.0f)
void		CMoon::Update()
{
	if(GETINPUT->GetKey(KEY_PRS, DIK_RIGHT))
	{
		m_vPos.x += BILLSPD;
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_LEFT))
	{
		m_vPos.x -= BILLSPD;
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_UP))
	{
		m_vPos.y += BILLSPD;
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_DOWN))
	{
		m_vPos.y -= BILLSPD;
	}

	if(GETINPUT->GetKey(KEY_PRS, DIK_I))
	{
		m_vPos.z += 1.0f;
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_K))
	{
		m_vPos.z -= 1.0f;
	}
	// 座標セット
	// ビルボード用***************************

	// ビルボード更新
	UpdateBillBoard();
	//****************************************************

}



