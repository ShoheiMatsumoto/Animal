#include "FactoryBase.h"
#include "ObjBase.h"
#include "Title.h"

CFactoryBase::CFactoryBase(void)
{
}


CFactoryBase::~CFactoryBase(void)
{
}

// ‰Šú‰»
void CFactoryBase::Initialize()
{

}

// ¶¬i©gj
CFactoryBase* CFactoryBase::Create()
{
	CFactoryBase* pFac = new CFactoryBase();

	pFac->Initialize();

	return pFac;
}

// ‰ğ•ú
void CFactoryBase::Release()
{

}

// ¶¬ˆË—Š
CObjBase* CFactoryBase::Request2D(int nID, int nTexID, D3DXVECTOR3 vPos)
{
	return NULL;
}

// ¶¬ˆË—Š
CObjBase* CFactoryBase::Request3D(int nID, int nTexID, D3DXVECTOR3 vPos)
{
	return NULL;
}