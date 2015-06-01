#pragma once
#include "object2d.h"
#include "Carten.h"

#define FADE_POS_X (SCREEN_WIDTH /2.0f)
#define FADE_POS_Y (SCREEN_HEIGHT /2.0f)

#define FADE_ADDTIME (120)
#define FADE_ADDALPHA (1.0f / FADE_ADDTIME)


class CFade :
	public CObject2D
{
protected:
	int m_nFadeCnt;
	float m_fAlpha;
	bool m_bFinIsTrue;
	CCarten* m_pCarten;

public:
	CFade(void);
	CFade(int n);
	virtual ~CFade(void);

	bool AskFin(){return m_bFinIsTrue;};
};

