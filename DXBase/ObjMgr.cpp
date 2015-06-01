#include "ObjMgr.h"
#include "MySort.h"
#include "SceneBase.h"

#define NULL_ID (9999)

CObjMgr::CObjMgr(void)
{
	
}


CObjMgr::~CObjMgr(void)
{
}

// オブジェマネージャ生成
CObjMgr* CObjMgr::Create()
{
	CObjMgr* pMgr = new CObjMgr();

	pMgr->Initialize();

	return pMgr;
	
}

void CObjMgr::Initialize()
{
	m_nCurDrawType = DRAWTYPE_MAX;
	m_bResetDrawList = false;


	// リストに空のオブジェクトをいれてく
	InitList();
}

// 動的リストの初期設定
void CObjMgr::InitList()
{
	// 2D******************************************************
	// 空のオブジェクトを生成
	for(int i = 0; i < OBJ2DGROUP_MAX; i ++)
	{
		m_pObjListTop2D[i] = (CObject2D*)m_pObj->Create();
		m_pObjListTop2D[i]->SetNext(NULL);		// トップの次をNULLクリア
		m_pObjListTop2D[i]->SetPrev(NULL);		// トップの前をNULLクリア
	}

	// 描画用入れ物初期化
	for(int i = 0; i < DRAWOBJ_MAX; i++)
	{
		m_pObj2DDraw[i] = NULL;
	}

	//***********************************************************

	// 3D
	// 空のオブジェクトを生成
	for(int i = 0; i < OBJ3DGROUP_MAX; i ++)
	{
		m_pObjListTop3D[i] = (CObject3D*)m_pObj->Create();
		m_pObjListTop3D[i]->SetNext(NULL);		// トップの次をNULLクリア
		m_pObjListTop3D[i]->SetPrev(NULL);		// トップの前をNULLクリア
	}

}

// 2D用の描画リストのセット
void CObjMgr::SetDrawList(CObject2D* pObj)
{
	for(int i = 0; i < DRAWOBJ_MAX; i++)
	{
		// 空いてる場所を探す
		if(!m_pObj2DDraw[i])
		{
			m_pObj2DDraw[i] = pObj;
			break;
		}
	}
}

// オブジェを消した際の空きの前詰め
// オブジェの消去があった際に走査
void CObjMgr::ResetDrawList()
{
	if(!m_bResetDrawList)
		return;
	// 
	for(int i = 0; i < DRAWOBJ_MAX; i++)
	{
		// 空いてる場所
		if(!m_pObj2DDraw[i])
		{
			for(int j = i; j < DRAWOBJ_MAX; j++)
			{
				// 登録されてる所を探す
				if(m_pObj2DDraw[j])
				{
					// ずらしていく
					for(int k = 0; k < DRAWOBJ_MAX - j; k++)
					{
						// NULLなら
						if(!m_pObj2DDraw[j + k])
						{
							i = i + k;
							j = j + k;
							break;
						}

						m_pObj2DDraw[i + k] = m_pObj2DDraw[j + k];
					}
				}

				// 見つからなかった
				if(j >= DRAWOBJ_MAX - 1)
					i = DRAWOBJ_MAX;		// iのループを抜けるように
			}
		}
	}

	// リセットフラグ戻し
	m_bResetDrawList = false;
}

// 描画配列のソート 
void CObjMgr::DrawSort()
{
	// 
	CMySort Sort;
	SortData* Data;
	int nCnt = 0;

	// ソート用データ作成
	for(nCnt; nCnt < DRAWOBJ_MAX; nCnt ++)
	{
		if(!m_pObj2DDraw[nCnt])
			break;
	}
	
	Data = new SortData[nCnt];

	// 移す
	for(int i = 0; i < nCnt; i++)
	{
		Data[i].nArrayNum = i;
		Data[i].fData = m_pObj2DDraw[i]->GetPos().z;	// Zの値でソート
	}

	// ソート
	Sort.QuiqSort(Data, nCnt);

	// 並べ直し
	CObject2D* pArray[DRAWOBJ_MAX];
	for(int i = 0; i < nCnt; i++)
	{
		pArray[i] = m_pObj2DDraw[Data[i].nArrayNum];
	}

	for(int i = 0; i < nCnt; i++)
	{
		m_pObj2DDraw[i] = pArray[i];
	}

	// 解放
	SAFE_DELETE_ARRAY(Data);
}

// 2DObjの更新
void CObjMgr::Update2D()
{
	// 2D
	CObjBase* pObj = NULL;

	// 横方向
	for(int i = 0; i < OBJ2DGROUP_MAX; i ++)
	{
		// 縦方向への更新
		pObj = m_pObjListTop2D[i];		// リストのトップを代入

		while(pObj)
		{
			pObj->Update();				// 更新
			pObj = pObj->GetNext();		// 次のオブジェを取得
		}
	}
}

// 3DObjの更新
void CObjMgr::Update3D()
{
	// 3D
	CObjBase* pObj = NULL;

	// 横方向
	for(int i = 0; i < OBJ3DGROUP_MAX; i ++)
	{
		// 縦方向
		pObj = m_pObjListTop3D[i];		// リストのトップを代入

		while(pObj)
		{
			pObj->Update();				// 更新
			pObj = pObj->GetNext();		// 次のオブジェを取得
		}
	}
}

// 全OBJの更新
void CObjMgr::AllUpdate()
{
	Update2D();
	Update3D();

	// 消去走査
	DeleteObj();		

	// 描画用リストリセット
	ResetDrawList();

	// 描画用リストのソート
	DrawSort();
}

// 2DObjの描画
void CObjMgr::Draw2D()
{
	// 2D
	CObjBase* pObj = NULL;
	int nDrawType = m_nCurDrawType;
	int nDrawTypeNext = m_nCurDrawType;

	// 配列を順に描画
	for(int i = 0; m_pObj2DDraw[i]; i ++)
	{
		// 描画タイプ取得
		nDrawType = m_pObj2DDraw[i]->GetDrawType();

		// 違ったら
		if(m_nCurDrawType != nDrawType)
		{
			m_pObj2DDraw[i]->DrawSetUp();
			m_nCurDrawType = nDrawType;		// 現在描画タイプの変更
		}
	
		m_pObj2DDraw[i]->Draw();

		// 次があるなら
		if(m_pObj2DDraw[i + 1])
		{
			// 次のがタイプが違うなら
			if(m_pObj2DDraw[i + 1]->GetDrawType() != m_nCurDrawType)
			{
				m_pObj2DDraw[i]->DrawEnd();
			}
		}
		else
		{		// 次が無いなら終わり
			m_pObj2DDraw[i]->DrawEnd();
			m_nCurDrawType = DRAWTYPE_MAX;		// リセット
		}
		
	}

	
}

// 3DObjの描画
void CObjMgr::Draw3D()
{
	// 3D
	CObject3D* pObj = NULL;
	int nDrawType = m_nCurDrawType;
	int nDrawTypeNext = m_nCurDrawType;
	int nPrevVP = 9999;
	int nCurVP;

	// 横方向
	for(int i = 0; i < OBJ3DGROUP_MAX; i ++)
	{
		// 縦方向
		pObj = m_pObjListTop3D[i];		// リストのトップを代入

		while(pObj)
		{
			// ビュープロジェクションタイプ
			nCurVP = pObj->GetViewType();// 取得
			if(nPrevVP != nCurVP)
			{
				switch(nCurVP)
				{
				case VIEWPROJ_PERS:
					CSceneBase::GetCurScene()->GetGraph()->SetProjection(PROJ_PERS);
					break;

				case VIEWPROJ_ORT:
					CSceneBase::GetCurScene()->GetGraph()->SetProjection(PROJ_ORT);
					break;
				}
				nPrevVP = nCurVP;
			}

			// 描画タイプ取得
			nDrawType = pObj->GetDrawType();

			// 違ったら
			if(m_nCurDrawType != nDrawType)
			{
				pObj->DrawSetUp();
				m_nCurDrawType = nDrawType;		// 現在描画タイプの変更
			}

			pObj->Draw();				// 描画
			
			// 次があるなら
			if(pObj->GetNext())
			{
				// 次のがタイプが違うなら
				if(pObj->GetNext()->GetDrawType() != m_nCurDrawType)
				{
					pObj->DrawEnd();
				}
			}
			else
			{		// 次が無いなら終わり
				pObj->DrawEnd();
				m_nCurDrawType = DRAWTYPE_MAX;		// リセット
			}

			pObj = (CObject3D *)pObj->GetNext();		// 次のオブジェを取得
		}
	}
}

// 全OBJの描画
void CObjMgr::AllDraw()
{
	Draw3D();
	Draw2D();
}

// 解放
void CObjMgr::Release()
{
	// リストの解放
	
	// リスト内オブジェ全開放
	ReleaseList();

	delete this;
}

// オブジェ登録
void CObjMgr::EntryObj2D(CObjBase* pObj)
{
	// 登録ID走査
	int nEntry = pObj->GetGroupID();		// グループID取得

	// リストに登録(連結)
	if(m_pObjListTop2D[nEntry]->GetNext())
		m_pObjListTop2D[nEntry]->GetNext()->SetPrev(pObj);	// トップのNextのオブジェのPrevに生成するオブジェを登録
	pObj->SetNext(m_pObjListTop2D[nEntry]->GetNext());		// トップのNextを生成するオブジェのNextにする
	pObj->SetPrev(m_pObjListTop2D[nEntry]);				// 生成するオブジェの前をトップに設定
	m_pObjListTop2D[nEntry]->SetNext(pObj);		// トップのNextに生成するオブジェを登録

	// 描画用のリストに登録
	SetDrawList((CObject2D*)pObj);
}

// オブジェ登録
void CObjMgr::EntryObj3D(CObjBase* pObj)
{
	// 登録ID走査
	int nEntry = pObj->GetGroupID();

	// リストに登録(連結)
	if(m_pObjListTop3D[nEntry]->GetNext())
		m_pObjListTop3D[nEntry]->GetNext()->SetPrev(pObj);	// トップのNextのオブジェのPrevに生成するオブジェを登録
	pObj->SetNext(m_pObjListTop3D[nEntry]->GetNext());		// トップのNextを生成するオブジェのNextにする
	pObj->SetPrev(m_pObjListTop3D[nEntry]);				// 生成するオブジェの前をトップに設定
	m_pObjListTop3D[nEntry]->SetNext(pObj);		// トップのNextに生成するオブジェを登録
}

// オブジェ消去
void CObjMgr::DeleteObj()
{
	DeleteObj2D();
	DeleteObj3D();
}

void CObjMgr::DeleteObj2D()
{
	CObject2D* pObj;
	CObject2D* pNext;

	for(int i = 0; i < OBJ2DGROUP_MAX; i ++)
	{
		pObj = m_pObjListTop2D[i];

		while(pObj)
		{
			// 消滅フラグが立ってたら
			if(pObj->CheckbeDelete())
			{
				pNext = (CObject2D*)pObj->GetNext();		// 先に移す
				SAFE_DELETE(pObj);		// 消去
				pObj = pNext;			// 次の
				continue;
			}
			pObj = (CObject2D*)pObj->GetNext();	// 次の
		}
	}
}

void CObjMgr::DeleteObj3D()
{
	CObject3D* pObj;
	CObject3D* pNext;

	for(int i = 0; i < OBJ3DGROUP_MAX; i ++)
	{
		pObj = m_pObjListTop3D[i];

		while(pObj)
		{
			// 消滅フラグが立ってたら
			if(pObj->CheckbeDelete())
			{
				pNext = (CObject3D*)pObj->GetNext();		// 先に移す
				SAFE_DELETE(pObj);		// 消去
				pObj = pNext;			// 次の
				continue;
			}
			pObj = (CObject3D*)pObj->GetNext();	// 次の
		}
	}
}

// リストの解放
void CObjMgr::ReleaseList()
{
	ReleaseList2D();
	ReleaseList3D();
}

// リストに残ってるオブジェの全消去
void CObjMgr::ReleaseList2D()
{
	CObject2D* pObj;
	CObject2D* pNext;

	for(int i = 0; i < OBJ2DGROUP_MAX; i ++)
	{
		pObj = m_pObjListTop2D[i];

		while(pObj)
		{
			
			pNext = (CObject2D*)pObj->GetNext();		// 先に移す
			SAFE_DELETE(pObj);		// 消去
			pObj = pNext;			// 次の
		}
	}
}

void CObjMgr::ReleaseList3D()
{
	CObject3D* pObj;
	CObject3D* pNext;

	for(int i = 0; i < OBJ3DGROUP_MAX; i ++)
	{
		pObj = m_pObjListTop3D[i];

		while(pObj)
		{
			
			pNext = (CObject3D*)pObj->GetNext();		// 先に移す
			SAFE_DELETE(pObj);		// 消去
			pObj = pNext;			// 次の
		}
	}
}

CObject2D*	CObjMgr::GetListTop2D(int nGroupID)
{
	return (CObject2D*)m_pObjListTop2D[nGroupID]->GetNext();
}


CObject3D*	CObjMgr::GetListTop3D(int nGroupID)
{
	
	return (CObject3D*)m_pObjListTop3D[nGroupID]->GetNext();
}



// eof