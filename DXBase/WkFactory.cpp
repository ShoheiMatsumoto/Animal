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
void CWkFactory::Request2D(int nID, D3DXVECTOR3 vPos)
{
	CObjBase* pObj;

	switch(nID)
	{
	case WK_OBJ2D_TEST2D:
		pObj = m_Test2D.Create(nID, WK_TEX_0, vPos);
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

void CWkFactory::Request3D(int nID, D3DXVECTOR3 vPos)
{
	CObjBase* pObj;

	switch(nID)
	{
	case WK_OBJ3D_MOON:
		pObj = m_Moon.Create(nID, WK_TEX_MOON, vPos);
		break;

	case WK_OBJ3D_TESTBILL:
		pObj = m_TestBill.Create(nID, WK_TEX_0, vPos);
		break;

	case WK_OBJ3D_PLAYER:
		pObj = m_Player.Create(nID, WK_TEX_SQUARE, vPos);
		break;
	default:
		// 登録外

		break;
	}

	// オブジェマネージャへ登録
	CSceneBase::GetCurScene()->GetObjMgr()->EntryObj3D(pObj);
}





//eof