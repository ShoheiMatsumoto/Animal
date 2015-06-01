#include "Object2D.h"
#include "SceneBase.h"
#include "ObjMgr.h"

CObject2D::CObject2D(void)
{
	m_nDrawType = DRAWTYPE_2D_NORMAL;
}

CObject2D::CObject2D(int nID, int nTexNum) : CObjBase(nID)
{
	// 現在シーンからオブジェマネージャを取得
	//CObjMgr* pMgr = CSceneBase::GetCurScene()->GetObjMgr();

	//pMgr->EntryObj2D(this, m_nObjTypeID);
	// マネージャからトップを取得
	//CObject2D* pTop = pMgr->GetListTop2D(m_nObjTypeID);

	// 連結
	//if(pTop->GetNext())		// 次があれば
	//	pTop->GetNext()->SetPrev(this);// トップのNextのオブジェのPrevに生成するオブジェを登録
	//SetNext(pTop->GetNext());		   // トップのNextを生成するオブジェのNextにする
	//SetPrev(pTop);				// 生成するオブジェの前をトップに設定
	//pTop->SetNext(this);		// トップのNextに生成するオブジェを登録
	//

	//if(pTop->m_pNext)		// 次があれば
	//	pTop->m_pNext->SetPrev(this);// トップのNextのオブジェのPrevに生成するオブジェを登録
	//m_pNext = pTop->m_pNext;		   // トップのNextを生成するオブジェのNextにする
	//m_pPrev = pTop;;				// 生成するオブジェの前をトップに設定
	//pTop->m_pNext = this;		// トップのNextに生成するオブジェを登録
	//
	//m_nDType = OT_2D;
	m_Board.Initialize(nTexNum);
	
	m_vSize.x = m_Board.GetSize().x;	// テクスチャサイズからサイズ設定
	m_vSize.y = m_Board.GetSize().y;
	m_vRadius.x = m_vSize.x / 2.0f;
	m_vRadius.y = m_vSize.y / 2.0f;
	
	m_nDrawType = DRAWTYPE_2D_NORMAL;
}


CObject2D::~CObject2D(void)
{
	CSceneBase::GetCurScene()->GetObjMgr()->SetbReset();		// 描画用リストリセットフラグON
}

void CObject2D::Update()
{
	m_Board.SetPosC(m_vPos);		// 2D板ポリの更新
}

void CObject2D::Draw()
{
	//DrawSetUp();

	CGraphics::GetDevice()->SetTexture(0, m_Board.m_pImage->GetTexture());
	CGraphics::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_Board.m_verWk, sizeof(VERTEX_2D));// ポリゴン描画

	//DrawEnd();
}

void CObject2D::DrawSetUp()
{
	if(m_bAlphaBlend)
	{
		CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Zバッファを更新

		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		CGraphics::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		CGraphics::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0);
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);			// ライティングしない

	}
	else
	{
		CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	// Zバッファを更新しない

		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);	// αブレンド 不可

		CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);			// ライティングしない
	}
	
	// 頂点フォーマットの設定
	CGraphics::GetDevice()->SetFVF(FVF_VERTEX_2D);

}

void CObject2D::DrawEnd()
{
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);				// ライティングする

	// CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			// Zバッファを更新する

	CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);	// αブレンド 不可

}


//eof