#pragma once
#include "object2d.h"
class CCarten :
	public CObject2D
{
protected:
	int m_nR;
	int m_nG;
	int m_nB;
	float m_fAlpha;

public:
	CCarten(void);
	CCarten(int n);
	virtual ~CCarten(void);

	CCarten* Create(int nTexNum);
	bool Initialize(int nTexNum);
	void Update(){};
	void Draw(){};
	void DrawSetUp(){};
	void DrawEnd(){};
	void Release(){};

	// セッター
	void SetColor(int nR, int nG, int nB);
	void SetAlpha(float fAlpha);
};

