#include "MyMath.h"


CMyMath::CMyMath(void)
{
}


CMyMath::~CMyMath(void)
{
}

// ベジエ曲線表現式
void CMyMath::Bezier2D(float* x, float* y, float t, KEY Key[4] )
{
	*x = ((1.0f - t) * (1.0f - t) * (1.0f - t)) * Key[0].x 
		 + 3.0f * ((1.0f - t) * (1.0f - t)) * t * Key[1].x
		 + 3.0f * (1.0f - t) * (t * t) * Key[2].x
		 + (t * t * t) * Key[3].x;

	*y = ((1.0f - t) * (1.0f - t) * (1.0f - t)) * Key[0].y
		 + 3.0f * ((1.0f - t) * (1.0f - t)) * t * Key[1].y
		 + 3.0f * (1.0f - t) * (t * t) * Key[2].y
		 + (t * t * t) * Key[3].y;
}

// ３D用ベジエ
void CMyMath::Bezier3D(float* x, float* y, float* z, float t, KEY Key[4] )
{
	*x = ((1.0f - t) * (1.0f - t) * (1.0f - t)) * Key[0].x 
		 + 3.0f * ((1.0f - t) * (1.0f - t)) * t * Key[1].x
		 + 3.0f * (1.0f - t) * (t * t) * Key[2].x
		 + (t * t * t) * Key[3].x;

	*y = ((1.0f - t) * (1.0f - t) * (1.0f - t)) * Key[0].y
		 + 3.0f * ((1.0f - t) * (1.0f - t)) * t * Key[1].y
		 + 3.0f * (1.0f - t) * (t * t) * Key[2].y
		 + (t * t * t) * Key[3].y;

	*z = ((1.0f - t) * (1.0f - t) * (1.0f - t)) * Key[0].z
		 + 3.0f * ((1.0f - t) * (1.0f - t)) * t * Key[1].z
		 + 3.0f * (1.0f - t) * (t * t) * Key[2].z
		 + (t * t * t) * Key[3].z;
}

// エルミート
void CMyMath::Hermite2D(float* x, float* y, float t, KEY Key[2], KEY VKey[2])
{
	*x = ((t - 1.0f) * (t - 1.0f)) * (2.0f * t + 1.0f) * Key[0].x
		+ (t * t) * (3.0f - (2.0f * t)) * Key[1].x
		+ ((1.0f - t) * (1.0f - t)) * t * VKey[0].x
		+ (t - 1.0f) * (t * t) * VKey[1].x;

	*y = ((t - 1.0f) * (t - 1.0f)) * (2.0f * t + 1.0f) * Key[0].y
		+ (t * t) * (3.0f - (2.0f * t)) * Key[1].y
		+ ((1.0f - t) * (1.0f - t)) * t * VKey[0].y
		+ (t - 1.0f) * (t * t) * VKey[1].y;
};

// 3D用エルミート
void CMyMath::Hermite3D(float* x, float* y, float* z, float t, KEY Key[2], KEY VKey[2])
{
	*x = ((t - 1.0f) * (t - 1.0f)) * (2.0f * t + 1.0f) * Key[0].x
		+ (t * t) * (3.0f - (2.0f * t)) * Key[1].x
		+ ((1.0f - t) * (1.0f - t)) * t * VKey[0].x
		+ (t - 1.0f) * (t * t) * VKey[1].x;

	*y = ((t - 1.0f) * (t - 1.0f)) * (2.0f * t + 1.0f) * Key[0].y
		+ (t * t) * (3.0f - (2.0f * t)) * Key[1].y
		+ ((1.0f - t) * (1.0f - t)) * t * VKey[0].y
		+ (t - 1.0f) * (t * t) * VKey[1].y;

	*z = ((t - 1.0f) * (t - 1.0f)) * (2.0f * t + 1.0f) * Key[0].z
		+ (t * t) * (3.0f - (2.0f * t)) * Key[1].z
		+ ((1.0f - t) * (1.0f - t)) * t * VKey[0].z
		+ (t - 1.0f) * (t * t) * VKey[1].z;
};

// 一方向線形補間
float		LinerInterPos1V(float fSPos, float fGPos, float fRate)
{
	float fSub = fGPos - fSPos;

	return fSub * fRate;
}

// 二方向線形補間
D3DXVECTOR3 LinerInterPol2V(D3DXVECTOR3 vSpos, D3DXVECTOR3 vGPos, float fRate)
{
	D3DXVECTOR3 vSub = vGPos - vSpos;
	vSub.z = 0.0f;

	return vSub * fRate;
}

// 三方向線形補間
D3DXVECTOR3 LinerInterPol3V(D3DXVECTOR3 vSpos, D3DXVECTOR3 vGPos, float fRate)
{
	D3DXVECTOR3 vSub = vGPos - vSpos;

	return vSub * fRate;
}

// eof