#include "FadeOut.h"
#include "SceneBase.h"



CFadeOut::CFadeOut(void)
{
	m_nFadeCnt = 0;
	m_fAlpha = 0.0f;
	m_bFinIsTrue = false;
}

CFadeOut::~CFadeOut(void)
{
}

CFadeOut* CFadeOut::Create(int nImage)
{
	CFadeOut*	pFade = new CFadeOut();

	pFade->Initialize(nImage);

	return pFade;
}

void CFadeOut::Initialize(int nImage)
{
	// 2Dステータスセット
	m_Board.Initialize(nImage);
	m_Board.ReSize(D3DXVECTOR2( SCREEN_WIDTH, SCREEN_HEIGHT));
	D3DXVECTOR2 vHalf = m_Board.GetSize() / 2.0f;
	m_vPos.x =  FADE_POS_X;
	m_vPos.y =  FADE_POS_Y;
	m_vPos.z = 0.0f;
	m_Board.SetAlpha(0.0f);

	
	//m_pCarten = m_pCarten->Create(TEX_CARTEN_BK, 0);
}

void CFadeOut::Update()
{
	m_fAlpha += FADE_ADDALPHA;

	if(m_fAlpha >= 1.0f)
	{
		m_fAlpha = 1.0f;
		m_bFinIsTrue = true;
		

	}

	m_Board. SetAlpha(m_fAlpha);

	m_Board.SetPosC(m_vPos);
}

void CFadeOut::Release()
{
	m_nObjStatus = OBJST_DELETE;
}


