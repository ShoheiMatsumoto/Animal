#pragma once
#include "main.h"
#include "Graphics.h"

// 構造体
typedef struct
{
	float x;
	float y;
	float z;
}KEY;

class CMyMath
{
private:

public:
	CMyMath(void);
	virtual ~CMyMath(void);

	// ベジエ曲線
	void Bezier2D(float* x, float* y, float t, KEY Key[4]);					// ベジエ曲線表現式
	void Bezier3D(float* x, float* y, float* z, float t, KEY Key[4]);					// ベジエ曲線表現式

	// エルミート
	void Hermite2D(float* x, float* y, float t, KEY Key[2], KEY VKey[2]);	// エルミート
	void Hermite3D(float* x, float* y, float* z, float t, KEY Key[2], KEY VKey[2]);	// エルミート

	// 線形保管
	float		LinerInterPos1V(float fSPos, float fGPos, float fRate);
	D3DXVECTOR3 LinerInterPol2V(D3DXVECTOR3 vSpos, D3DXVECTOR3 vGPos, float fRate);
	D3DXVECTOR3 LinerInterPol3V(D3DXVECTOR3 vSpos, D3DXVECTOR3 vGPos, float fRate);
};

