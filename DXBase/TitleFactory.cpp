#include "TitleFactory.h"
#include "SceneBase.h"
#include "ObjBase.h"
#include "Title.h"

CTitleFactory::CTitleFactory(void)
{
}


CTitleFactory::~CTitleFactory(void)
{
}

// ������
void CTitleFactory::Initialize()
{

}

// �����i���g�j
CTitleFactory* CTitleFactory::Create()
{
	CTitleFactory* pFac = new CTitleFactory();

	pFac->Initialize();

	return pFac;
}

// ���
void CTitleFactory::Release()
{

}

//�����˗�
void CTitleFactory::Request2D(int nID, int nTexID, D3DXVECTOR3 vPos)
{
	CObjBase* pObj;

	switch(nID)
	{
	case OBJ2D_TEST2D:
		pObj = m_Test2D.Create(nID, T_TEX_0, vPos);
		//pObj = m_Test2D.Create(nID, T_TEX_0);
		break;

	case OBJ2D_TEST0:
		vPos.x += 100.0f;
		pObj = m_Test2D.Create(nID, T_TEX_0, vPos);
		//pObj = m_Test2D.Create(nID, T_TEX_0);
		break;

	case OBJ2D_TEST1:
		vPos.x += -100.0f;
		pObj = m_Test2D.Create(nID, T_TEX_0, vPos);
		//pObj = m_Test2D.Create(nID, T_TEX_0);
		break;

	case OBJ2D_TEST3:
		vPos.y += 100.0f;
		pObj = m_Test2D.Create(nID, T_TEX_0, vPos);
		//pObj = m_Test2D.Create(nID, T_TEX_0);
		break;

	case OBJ2D_TEST2:
		vPos.y += -100.0f;
		pObj = m_Test2D.Create(nID, T_TEX_0, vPos);
		//pObj = m_Test2D.Create(nID, T_TEX_0);
		break;
	default:
		// �o�^�O
		// �G���[����
		break;
	}

	// �I�u�W�F�}�l�[�W���֓o�^
	CSceneBase::GetCurScene()->GetObjMgr()->EntryObj2D(pObj);
}

void CTitleFactory::Request3D(int nID, int nTexID, D3DXVECTOR3 vPos)
{
	CObjBase* pObj;

	switch(nID)
	{
	case OBJ3D_MOON:
		pObj = m_Moon.Create(nID, T_TEX_MOON, vPos);
		break;

	case OBJ3D_TESTBILL:
		pObj = m_TestBill.Create(nID, T_TEX_0, vPos);
		break;
	default:
		// �o�^�O

		break;
	}

	// �I�u�W�F�}�l�[�W���֓o�^
	CSceneBase::GetCurScene()->GetObjMgr()->EntryObj3D(pObj);
}





//eof