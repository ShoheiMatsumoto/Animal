#include "Carten.h"


CCarten::CCarten(void)
{
	m_nR = 255;
	m_nG = 255;
	m_nB = 255;
	m_fAlpha = 1.0f;
	/*m_dwObjTypeID = OBJTYPE_CARTEN2D;*/
}

CCarten::~CCarten(void)
{
}

// 生成
CCarten* CCarten::Create(int nTexNum)
{
	CCarten*	pCarten = new CCarten();

	if(!pCarten->Initialize(nTexNum))
	{
		SAFE_DELETE(pCarten);
	}

	return pCarten;
}

// 初期化
bool CCarten::Initialize(int nTexNum)
{
	// 2Dステータスセット
	m_Board.Initialize(nTexNum);
	
	VERTEX_2D* ver = m_Board.GetVerWk();		
	D3DXVECTOR2 vHalf = m_Board.GetSize() / 2.0f;
	m_vPos.x += vHalf.x;
	m_vPos.y += vHalf.y;
	m_vPos.z = ver->vtx.z;

	return true;
}

void CCarten::SetColor(int nR, int nG, int nB)
{
	m_nR = nR;
	m_nG = nG;
	m_nB = nB;

	m_Board.SetColor(nR, nG, nB);
}

void CCarten::SetAlpha(float fAlpha)
{
	m_fAlpha = fAlpha;

	m_Board.SetAlpha(fAlpha);
}


// eof