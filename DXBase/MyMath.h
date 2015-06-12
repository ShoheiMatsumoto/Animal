#pragma once
#include "main.h"
#include "Graphics.h"

// �\����
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

	// �x�W�G�Ȑ�
	void Bezier2D(float* x, float* y, float t, KEY Key[4]);					// �x�W�G�Ȑ��\����
	void Bezier3D(float* x, float* y, float* z, float t, KEY Key[4]);					// �x�W�G�Ȑ��\����

	// �G���~�[�g
	void Hermite2D(float* x, float* y, float t, KEY Key[2], KEY VKey[2]);	// �G���~�[�g
	void Hermite3D(float* x, float* y, float* z, float t, KEY Key[2], KEY VKey[2]);	// �G���~�[�g

	// ���`�ۊ�
	float		LinerInterPos1V(float fSPos, float fGPos, float fRate);
	D3DXVECTOR3 LinerInterPol2V(D3DXVECTOR3 vSpos, D3DXVECTOR3 vGPos, float fRate);
	D3DXVECTOR3 LinerInterPol3V(D3DXVECTOR3 vSpos, D3DXVECTOR3 vGPos, float fRate);
};

