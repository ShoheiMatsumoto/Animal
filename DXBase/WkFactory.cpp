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
CObjBase* CWkFactory::Request2D(int nID, int nTexID, D3DXVECTOR3 vPos)
{
	CObjBase* pObj;

	switch(nID)
	{
	case WK_OBJ2D_TEST2D:
		pObj = m_Test2D.Create(nID, nTexID, vPos);
		//pObj = m_Test2D.Create(nID, WK_TEX_0);
		break;

	default:
		// �o�^�O
		// �G���[����
		break;
	}

	// �I�u�W�F�}�l�[�W���֓o�^
	CSceneBase::GetCurScene()->GetObjMgr()->EntryObj2D(pObj);

	return pObj;
}

CObjBase* CWkFactory::Request3D(int nID, int nTexID, D3DXVECTOR3 vPos)
{
	CObjBase* pObj;
	D3DXVECTOR3 vSize;

	// �A�j�}���X�C�b�`
	if(nID >= WK_OBJ3D_NEZU && nID <= WK_OBJ3D_URI)
		pObj = Req3DSwtAnimaru(nID, nTexID, vPos);

	switch(nID)
	{
	case WK_OBJ3D_MOON:
		pObj = m_Moon.Create(nID, nTexID, vPos);
		break;

	case WK_OBJ3D_TESTBILL:
		pObj = m_TestBill.Create(nID, nTexID, vPos);
		break;

	case WK_OBJ3D_PLAYER:
		pObj = m_Player.Create(nID, nTexID, vPos);
		break;

	case WK_OBJ3D_MPSQUARE:
		vSize = D3DXVECTOR3(64.0f, 64.0f, 0.0f);
		pObj = m_MapParts.Create(nID, nTexID, vPos, vSize, MAPPARTS_SQUARE);
		break;

	case WK_OBJ3D_MPRUP:
		vSize = D3DXVECTOR3(256.0f, 64.0f, 0.0f);
		pObj = m_MapParts.Create(nID, nTexID, vPos, vSize, MAPPARTS_RUP);
		break;

	case WK_OBJ3D_MPRDOWN:
		vSize = D3DXVECTOR3(256.0f, 64.0f, 0.0f);
		pObj = m_MapParts.Create(nID, nTexID, vPos, vSize, MAPPARTS_RDOWN);
		break;

	default:
		// �o�^�O

		break;
	}

	// �I�u�W�F�}�l�[�W���֓o�^
	CSceneBase::GetCurScene()->GetObjMgr()->EntryObj3D(pObj);

	return pObj;
}

// �A�j�}���p���N�G�X�g
CObjBase* CWkFactory::Req3DSwtAnimaru(int nID, int nTexID, D3DXVECTOR3 vPos)
{
	CObjBase* pObj;

	switch(nID)
	{
	case WK_OBJ3D_NEZU:
		pObj = m_Nezu.Create(OBJ3DGROUP_ANIMARU, nID, WK_TEX_NEZU, vPos);
		break;

	case WK_OBJ3D_USHI:
		pObj = m_Ushi.Create(OBJ3DGROUP_ANIMARU, nID, WK_TEX_USHI, vPos);

		break;

	case WK_OBJ3D_TORA:
		pObj = m_Tora.Create(OBJ3DGROUP_ANIMARU, nID, WK_TEX_TORA, vPos);

		break;

	case WK_OBJ3D_MIMI:
		pObj = m_Mimi.Create(OBJ3DGROUP_ANIMARU, nID, WK_TEX_MIMI, vPos);

		break;

	case WK_OBJ3D_TATSU:
		pObj = m_Tatsu.Create(OBJ3DGROUP_ANIMARU, nID, WK_TEX_TATSU, vPos);

		break;

	case WK_OBJ3D_HEBI:
		pObj = m_Hebi.Create(OBJ3DGROUP_ANIMARU, nID, WK_TEX_HEBI, vPos);

		break;

	case WK_OBJ3D_UMA:
		pObj = m_Hosu.Create(OBJ3DGROUP_ANIMARU, nID, WK_TEX_UMA, vPos);

		break;

	case WK_OBJ3D_MERRY:
		pObj = m_Moko.Create(OBJ3DGROUP_ANIMARU, nID, WK_TEX_MERRY, vPos);

		break;

	case WK_OBJ3D_SARU:
		pObj = m_Saru.Create(OBJ3DGROUP_ANIMARU, nID, WK_TEX_SARU, vPos);

		break;

	case WK_OBJ3D_TORI:
		pObj = m_Tori.Create(OBJ3DGROUP_ANIMARU, nID, WK_TEX_TORI, vPos);

		break;

	case WK_OBJ3D_INU:
		pObj = m_Inu.Create(OBJ3DGROUP_ANIMARU, nID, WK_TEX_INU, vPos);

		break;

	case WK_OBJ3D_URI:
		pObj = m_Uri.Create(OBJ3DGROUP_ANIMARU, nID, WK_TEX_URI, vPos);

		break;

	default:

		break;
	}

	return pObj;
}



//eof