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


// 初期化
void CWkFactory::Initialize()
{

}

// 生成（自身）
CWkFactory* CWkFactory::Create()
{
	CWkFactory* pFac = new CWkFactory();

	pFac->Initialize();

	return pFac;
}

// 解放
void CWkFactory::Release()
{

}

//生成依頼
void CWkFactory::Request2D(int nID, int nTexID, D3DXVECTOR3 vPos)
{
	CObjBase* pObj;

	switch(nID)
	{
	case WK_OBJ2D_TEST2D:
		pObj = m_Test2D.Create(nID, nTexID, vPos);
		//pObj = m_Test2D.Create(nID, WK_TEX_0);
		break;

	default:
		// 登録外
		// エラー処理
		break;
	}

	// オブジェマネージャへ登録
	CSceneBase::GetCurScene()->GetObjMgr()->EntryObj2D(pObj);
}

void CWkFactory::Request3D(int nID, int nTexID, D3DXVECTOR3 vPos)
{
	CObjBase* pObj;
	D3DXVECTOR3 vSize;

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
		// 登録外

		break;
	}

	// オブジェマネージャへ登録
	CSceneBase::GetCurScene()->GetObjMgr()->EntryObj3D(pObj);
}





//eof