#include "ObjBase.h"
#include "SceneBase.h"

int CObjBase::m_nIdentifCnt = 0;

CObjBase::CObjBase(void)
{
	D3DXMatrixIdentity(&m_world);		// ワールド変換行列初期化

	m_vPos.x = m_world._41;
	m_vPos.y = m_world._42;
	m_vPos.z = m_world._43;
	
	// 速度、加速度初期化
	m_vSpd = D3DXVECTOR3(0, 0, 0);
	m_vAccel = D3DXVECTOR3(0, 0, 0);
	m_vAngle = D3DXVECTOR3(0, 0, 0);

	m_fAlpha = 1.0f;

	m_bUse = true;
	m_bDraw = true;
	m_nObjStatus = OBJST_NONE;
	m_bHit = false;
	m_bUseShader = false;
	m_bAlphaBlend = true;		// アルファブレンドON

	m_nShadeTechNum = 0;
	m_nCollBasePoint = COLLBASEPOINT_CENTER;		// 中心

	m_bDelete = false;

	m_pNext = NULL;
	m_pPrev = NULL;

	// 入力
	for(int i = 0; i < INPTYPE; i++)
	{
		for(int j = 0; j < INP_BTN_MAX; j++)
			m_bInput[i][j] = false;
	}
	m_bEvent = false;

	m_bUpdate = false;
	m_bDraw = false;
}

CObjBase::CObjBase(int nID)
{

	m_nObjTypeID = nID;
	m_nIdentifID = m_nIdentifCnt;
	m_nIdentifCnt ++;	// 個別識別用IDカウンタ


	D3DXMatrixIdentity(&m_world);		// ワールド変換行列初期化

	m_vPos.x = m_world._41;
	m_vPos.y = m_world._42;
	m_vPos.z = m_world._43;
	
	// 速度、加速度初期化
	m_vSpd = D3DXVECTOR3(0, 0, 0);
	m_vAccel = D3DXVECTOR3(0, 0, 0);
	m_vAngle = D3DXVECTOR3(0, 0, 0);

	m_fAlpha = 1.0f;

	m_bUse = true;
	m_bDraw = true;
	m_nObjStatus = OBJST_NONE;
	m_bHit = false;
	m_bUseShader = false;
	m_bAlphaBlend = true;		// アルファブレンドON

	m_nShadeTechNum = 0;

	m_bDelete = false;

	m_pNext = NULL;
	m_pPrev = NULL;

	// 入力
	for(int i = 0; i < INPTYPE; i++)
	{
		for(int j = 0; j < INP_BTN_MAX; j++)
			m_bInput[i][j] = false;
	}
	m_bEvent = false;
}

CObjBase::~CObjBase(void)
{
	// リストから除外
	if(m_pPrev)
		m_pPrev->SetNext(m_pNext);		// 自分の前の次に自分の次をセット
	if(m_pNext)
		m_pNext->SetPrev(m_pPrev);		// 自分の次の前に自分の前をセット

	m_nIdentifCnt --;	// 個別識別用IDカウンタ
}

CObjBase* CObjBase::Create()
{
	CObjBase* pObj = new CObjBase();

	//pObj->m_world = D3DXMATRIX();

	return pObj;
}

void CObjBase::Initialize()
{

}

void CObjBase::Update()
{

}

void CObjBase::Draw()
{

}

void CObjBase::DrawSetUp()
{

}

void CObjBase::DrawEnd()
{

}

void CObjBase::Release()
{

}

D3DXMATRIX CreateScreenMat()
{
	D3DXMATRIX mat;
	
		mat._11 = SCREEN_WIDTH / 2.0f;
		mat._12 = 0;
		mat._13 = 0;
		mat._14 = 0;

		mat._21 = 0;
		mat._22 = -SCREEN_HEIGHT / 2.0f;
		mat._23 = 0;
		mat._24 = 0;

		mat._31 = 0;
		mat._32 = 0;
		mat._33 = 1;
		mat._34 = 0;

		mat._41 = SCREEN_WIDTH / 2.0f;
		mat._42 = SCREEN_HEIGHT / 2.0f;
		mat._43 = 0;
		mat._44 = 1;
	
		return mat;
}

// 入力
void		CObjBase::SetInputData(bool bInp[INPTYPE][INP_BTN_MAX])
{
	for(int i = 0; i < INPTYPE; i++)
	{
		for(int j = 0; j < INP_BTN_MAX; j++)
			m_bInput[i][j] = bInp[i][j];
	}
}

//// 四角判定
//bool CObjBase::CollSquare(CObjBase* pObj)
//{
//	D3DXVECTOR3 p1, p2;		// 座標
//	D3DXVECTOR3 s1, s2;		// サイズ
//	// X
//	if(m_vSize.x)
//	{
//
//	}
//
//}
//
//
//bool CObjBase::CollCircle(CObjBase* pObj)
//{
//
//}



//eof