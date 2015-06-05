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


// 初期化
void CWkFactoryI::Initialize()
{

}

// 生成（自身）
CWkFactoryI* CWkFactoryI::Create()
{
	CWkFactoryI* pFac = new CWkFactoryI();

	pFac->Initialize();

	return pFac;
}

// 解放
void CWkFactoryI::Release()
{

}

//生成依頼
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
		// 登録外
		// エラー処理
		break;
	}

	// オブジェマネージャへ登録
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
		// 登録外

		break;
	}

	// オブジェマネージャへ登録
	CSceneBase::GetCurScene()->GetObjMgr()->EntryObj3D(pObj);
}





//eof