#include "Cursor.h"
#include "Input.h"
#include "SceneBase.h"
#include "Camera.h"

CCursor::CCursor(void)
{
}

CCursor::~CCursor(void)
{
}

CCursor*	CCursor::Create(int nTexNum)
{
	CCursor*	pCursor = new CCursor();

	if(!pCursor->Initialize(nTexNum))
	{
		SAFE_DELETE(pCursor);
	}

	return pCursor;
}

bool		CCursor::Initialize(int nTexNum)
{
	// 2Dステータスセット
	m_Board.Initialize(nTexNum);
	VERTEX_2D* ver = m_Board.m_verWk;
	m_vPos.x = ver->vtx.x = 0;
	m_vPos.y = ver->vtx.y = 0;
	m_vPos.z = ver->vtx.z = 0;

	// HWND hWnd = CGameWindow::GetHwnd();

	// ビルボード初期化
	InitializeBillboard();
	
	

	return true;
}
#define BILLSPD (0.4)
void		CCursor::Update()
{
	/*if(GETINPUT->GetKey(KEY_PRS, DIK_RIGHT))
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
		m_vPos.z += BILLSPD;
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_K))
	{
		m_vPos.z -= BILLSPD;
	}*/

	// 座標セット
	m_Board.SetPosC((D3DXVECTOR3)m_vPos);

	// ビルボード用***************************
	D3DXMATRIX matPos;

	D3DXMatrixTranslation(&matPos, m_vPos.x, m_vPos.y, m_vPos.z);
	//D3DXMatrixMultiply(m_world, );
	m_world = matPos;

	// ビルボード更新
	UpdateBillBoard();
	//****************************************************

}



