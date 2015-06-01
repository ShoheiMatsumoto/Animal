#include "PoliLine2D.h"


CPoliLine2D::CPoliLine2D(void)
{
}


CPoliLine2D::~CPoliLine2D(void)
{
}

CPoliLine2D* CPoliLine2D::Create(D3DXVECTOR3 vInitPos, D3DXVECTOR3 vDestPos, float fWidth)
{
	CPoliLine2D* pPoli = new CPoliLine2D();

	return pPoli;
}

void CPoliLine2D::Initialize()
{

}

void CPoliLine2D::Release()
{

}