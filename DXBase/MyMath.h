#pragma once

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

	static void Bezier2D(float* x, float* y, float t, KEY Key[4]);					// ベジエ曲線表現式
	static void Bezier3D(float* x, float* y, float* z, float t, KEY Key[4]);					// ベジエ曲線表現式

	static void Hermite2D(float* x, float* y, float t, KEY Key[2], KEY VKey[2]);	// エルミート
	static void Hermite3D(float* x, float* y, float* z, float t, KEY Key[2], KEY VKey[2]);	// エルミート

};

