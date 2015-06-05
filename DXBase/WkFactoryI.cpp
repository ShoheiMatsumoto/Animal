#include "WkFactoryI.h"
#include "SceneBase.h"
#include "ObjBase.h"
#include "SceneWkI.h"

CWkFactoryI::CWkFactoryI(void)
{
}


CWkFactoryI::~CWkFactoryI(void)
{
}


// ������
void CWkFactoryI::Initialize()
{

}

// �����i���g�j
CWkFactoryI* CWkFactoryI::Create()
{
	CWkFactoryI* pFac = new CWkFactoryI();

	pFac->Initialize();

	return pFac;
}

// ���
void CWkFactoryI::Release()
{

}

//�����˗�
void CWkFactoryI::Request2D(int nID, D3DXVECTOR3 vPos)
{
	CObjBase* pObj;

	switch(nID)
	{
	case OBJ2D_TEST2D:
		pObj = m_Test2D.Create(nID, WK_I_TEX_0, vPos);
		//pObj = m_Test2D.Create(nID, WK_I_TEX_0);
		break;

	default:
		// �o�^�O
		// �G���[����
		break;
	}

	// �I�u�W�F�}�l�[�W���֓o�^
	CSceneBase::GetCurScene()->GetObjMgr()->EntryObj2D(pObj);
}

void CWkFactoryI::Request3D(int nID, D3DXVECTOR3 vPos)
{
	CObjBase* pObj;

	switch(nID)
	{
	case WKI_OBJ3D_MOON:
		pObj = m_Moon.Create(nID, WK_I_TEX_MOON, vPos);
		break;

	case WKI_OBJ3D_TESTBILL :
		pObj = m_TestBill.Create(nID, WK_I_TEX_0, vPos);
		break;
	default:
		// �o�^�O

		break;
	}

	// �I�u�W�F�}�l�[�W���֓o�^
	CSceneBase::GetCurScene()->GetObjMgr()->EntryObj3D(pObj);
}





//eof