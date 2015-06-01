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


// 初期化
void CWkFactoryN::Initialize()
{

}

// 生成（自身）
CWkFactoryN* CWkFactoryN::Create()
{
	CWkFactoryN* pFac = new CWkFactoryN();

	pFac->Initialize();

	return pFac;
}

// 解放
void CWkFactoryN::Release()
{

}

//生成依頼
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
		// 登録外
		// エラー処理
		break;
	}

	// オブジェマネージャへ登録
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
		// 登録外

		break;
	}

	// オブジェマネージャへ登録
	CSceneBase::GetCurScene()->GetObjMgr()->EntryObj3D(pObj);
}





//eof