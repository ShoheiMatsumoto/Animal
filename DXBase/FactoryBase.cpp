#include "FactoryBase.h"
#include "ObjBase.h"
#include "Title.h"

CFactoryBase::CFactoryBase(void)
{
}


CFactoryBase::~CFactoryBase(void)
{
}

// ������
void CFactoryBase::Initialize()
{

}

// �����i���g�j
CFactoryBase* CFactoryBase::Create()
{
	CFactoryBase* pFac = new CFactoryBase();

	pFac->Initialize();

	return pFac;
}

// ���
void CFactoryBase::Release()
{

}

// �����˗�
void CFactoryBase::Request2D(int nID, int nTexID, D3DXVECTOR3 vPos)
{
	
}

// �����˗�
void CFactoryBase::Request3D(int nID, int nTexID, D3DXVECTOR3 vPos)
{
	
}