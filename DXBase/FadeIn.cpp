#include "FadeIn.h"
#include "SceneBase.h"

CFadeIn::CFadeIn(void)
{
}

CFadeIn::~CFadeIn(void)
{
}

CFadeIn* CFadeIn::Create(int nImage)
{
	CFadeIn*	pFade = new CFadeIn();

	pFade->Initialize(nImage);

	return pFade;
}

void CFadeIn::Initialize(int nImage)
{
	// 2Dステータスセット
	m_Board.Initialize(nImage);
	m_Board.ReSize(D3DXVECTOR2( SCREEN_WIDTH, SCREEN_HEIGHT));
	D3DXVECTOR2 vHalf = m_Board.GetSize() / 2.0f;
	m_vPos.x =  FADE_POS_X;
	m_vPos.y =  FADE_POS_Y;
	m_vPos.z = 0.0f;
	m_Board.SetAlpha(1.0f);
	m_nFadeCnt = 0;
	m_fAlpha = 1.0f;
	m_bFinIsTrue = false;
	
	//m_pCarten = m_pCarten->Create(TEX_CARTEN_BK, 0);
}

void CFadeIn::Update()
{
	m_fAlpha -= FADE_ADDALPHA;

	if(m_fAlpha <= 0.0f)
	{
		m_fAlpha = 0.0f;
		m_bFinIsTrue = true;
		m_nObjStatus = OBJST_DELETE;

	}

	m_Board. SetAlpha(m_fAlpha);

	m_Board.SetPosC(m_vPos);
}

void CFadeIn::Release()
{

}

