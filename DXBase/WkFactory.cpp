#include "WkFactory.h"
#include "SceneBase.h"
#include "ObjBase.h"
#include "SceneWk.h"

CWkFactory::CWkFactory(void)
{
}


CWkFactory::~CWkFactory(void)
{
}


// ������
void CWkFactory::Initialize()
{

}

// �����i���g�j
CWkFactory* CWkFactory::Create()
{
	CWkFactory* pFac = new CWkFactory();

	pFac->Initialize();

	return pFac;
}

// ���
void CWkFactory::Release()
{

}

//�����˗�
void CWkFactory::Request2D(int nID, D3DXVECTOR3 vPos)
{
	CObjBase* pObj;

	switch(nID)
	{
	case OBJ2D_TEST2D:
		pObj = m_Test2D.Create(nID, WK_TEX_0, vPos);
		//pObj = m_Test2D.Create(nID, WK_TEX_0);
		break;

	default:
		// �o�^�O
		// �G���[����
		break;
	}

	// �I�u�W�F�}�l�[�W���֓o�^
	CSceneBase::GetCurScene()->GetObjMgr()->EntryObj2D(pObj);
}

void CWkFactory::Request3D(int nID, D3DXVECTOR3 vPos)
{
	CObjBase* pObj;

	switch(nID)
	{
	case OBJ3D_MOON:
		pObj = m_Moon.Create(nID, WK_TEX_MOON, vPos);
		break;

	case OBJ3D_TESTBILL:
		pObj = m_TestBill.Create(nID, WK_TEX_0, vPos);
		break;
	default:
		// �o�^�O

		break;
	}

	// �I�u�W�F�}�l�[�W���֓o�^
	CSceneBase::GetCurScene()->GetObjMgr()->EntryObj3D(pObj);
}





//eof