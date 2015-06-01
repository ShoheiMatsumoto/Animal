#include "PoliLine3D.h"


CPoliLine3D::CPoliLine3D(void)
{
}


CPoliLine3D::~CPoliLine3D(void)
{
}


CPoliLine3D* CPoliLine3D::Create(D3DXVECTOR3 vInitPos, D3DXVECTOR3 vDestPos, float fWidth)
{
	CPoliLine3D* pPoli = new CPoliLine3D();

	return pPoli;
	
}

void CPoliLine3D::Initialize()
{

}