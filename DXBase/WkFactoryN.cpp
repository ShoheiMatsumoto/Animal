#include "WkFactoryN.h"
#include "SceneBase.h"
#include "ObjBase.h"
#include "SceneWkN.h"

CWkFactoryN::CWkFactoryN(void)
{
}


CWkFactoryN::~CWkFactoryN(void)
{
}


// ������
void CWkFactoryN::Initialize()
{

}

// �����i���g�j
CWkFactoryN* CWkFactoryN::Create()
{
	CWkFactoryN* pFac = new CWkFactoryN();

	pFac->Initialize();

	return pFac;
}

// ���
void CWkFactoryN::Release()
{

}

//�����˗�
void CWkFactoryN::Request2D(int nID, D3DXVECTOR3 vPos)
{
	CObjBase* pObj;

	switch(nID)
	{
	case OBJ2D_TEST2D:
		pObj = m_Test2D.Create(nID, WK_N_TEX_0, vPos);
		//pObj = m_Test2D.Create(nID, WK_N_TEX_0);
		break;

	default:
		// �o�^�O
		// �G���[����
		break;
	}

	// �I�u�W�F�}�l�[�W���֓o�^
	CSceneBase::GetCurScene()->GetObjMgr()->EntryObj2D(pObj);
}

void CWkFactoryN::Request3D(int nID, D3DXVECTOR3 vPos)
{
	CObjBase* pObj;

	switch(nID)
	{
	case OBJ3D_MOON:
		pObj = m_Moon.Create(nID, WK_N_TEX_MOON, vPos);
		break;

	case OBJ3D_TESTBILL:
		pObj = m_TestBill.Create(nID, WK_N_TEX_0, vPos);
		break;
	default:
		// �o�^�O

		break;
	}

	// �I�u�W�F�}�l�[�W���֓o�^
	CSceneBase::GetCurScene()->GetObjMgr()->EntryObj3D(pObj);
}





//eof