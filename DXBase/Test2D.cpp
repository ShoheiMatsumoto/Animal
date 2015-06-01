#include "Test2D.h"
#include "Input.h"


CTest2D::CTest2D(void)
{
}

CTest2D::CTest2D(int nID, int nTexNum) : CObject2D(nID, nTexNum)
{
		
}

CTest2D::~CTest2D(void)
{

}

// 生成
CTest2D*	CTest2D::Create(int nID, int nTexNum, D3DXVECTOR3 vPos)
{
	CTest2D*	pTest = new CTest2D(nID, nTexNum);

	if(!pTest->Initialize(nTexNum))
	{
		SAFE_DELETE(pTest);
	}
	
	pTest->m_vPos = vPos;

	return pTest;
}

bool		CTest2D::Initialize(int nTexNum)
{
	m_nObjGroupID = OBJ2DGROUP_UI;

	// 2Dステータスセット
	m_Board.Initialize(nTexNum);
	m_Board.ReSize(D3DXVECTOR2(64, 64));
	VERTEX_2D* ver = m_Board.GetVerWk();		// リサイズ
	D3DXVECTOR2 vHalf = m_Board.GetSize() / 2.0f;
	m_vPos.x = ver->vtx.x + vHalf.x;
	m_vPos.y = ver->vtx.y + vHalf.y;
	m_vPos.z = ver->vtx.z;

	

	return true;
}

float g_fAlpha = 0.0f;

void		CTest2D::Update()
{
	if(GETINPUT->GetKey(KEY_PRS, DIK_RIGHT))
	{
		m_vPos.x ++;
		g_fAlpha += 0.001f;
		if(g_fAlpha >= 1.0f)
			g_fAlpha = 1.0f;
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_LEFT))
	{
		m_vPos.x --;
		g_fAlpha -= 0.001f;
		if(g_fAlpha <= 0.0f)
			g_fAlpha = 0.0f;
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_UP))
	{
		m_vPos.y --;
		g_fAlpha += 0.001f;
		if(g_fAlpha >= 1.0f)
			g_fAlpha = 1.0f;
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_DOWN))
	{
		m_vPos.y ++;
		g_fAlpha -= 0.001f;
		if(g_fAlpha <= 0.0f)
			g_fAlpha = 0.0f;
	}

	if(GETINPUT->GetKey(KEY_TRG, DIK_E))
	{
		m_Board.ReSize(D3DXVECTOR2(128, 128));
	}

	if(GETINPUT->GetKey(KEY_TRG, DIK_R))
	{
		m_Board.ReSize(D3DXVECTOR2(64, 64));
	}
	//m_Board.SetAlpha(g_fAlpha);
	/*if(GETINPUT->GetKey(KEY_PRS, DIK_UP))
	{
		m_vPos.y ++;
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_DOWN))
	{
		m_vPos.y --;
	}*/
	// 座標セット
	m_Board.SetPosC(m_vPos);
}

// 解放
void CTest2D::Release()
{

}