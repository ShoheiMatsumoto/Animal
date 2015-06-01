#include "Object3D.h"
#include "Shader.h"
#include "SceneBase.h"
#include "ObjMgr.h"

// コンストラクタ
CObject3D::CObject3D()
{
	// 共通ステータス初期化
	m_nDrawType = DRAWTYPE_2D_NORMAL;
	m_nObjStatus = OBJST_NONE;

	m_bSphere = false;
	m_bBox = false;

	// メッシュ クラス初期化
	m_pMesh = NULL;

	// 描画タイプ
	m_nDrawType = DRAWTYPE_3D_NORMAL;

	// 投影法
	m_nViewProjType = VIEWPROJ_PERS;

	// 現在シーンからオブジェマネージャを取得
	//CObjMgr* pMgr = CSceneBase::GetCurScene()->GetObjMgr();

	// マネージャからトップを取得
	//CObject3D* pTop = pMgr->GetListTop3D(m_nObjTypeID);

	// 連結
	//if(pTop->GetNext())		// 次があれば
	//	pTop->GetNext()->SetPrev(this);// トップのNextのオブジェのPrevに生成するオブジェを登録
	//SetNext(pTop->GetNext());		   // トップのNextを生成するオブジェのNextにする
	//SetPrev(pTop);				// 生成するオブジェの前をトップに設定
	//pTop->SetNext(this);		// トップのNextに生成するオブジェを登録

	//if(pTop->m_pNext)		// 次があれば
	//	pTop->m_pNext->SetPrev(this);// トップのNextのオブジェのPrevに生成するオブジェを登録
	//m_pNext = pTop->m_pNext;		   // トップのNextを生成するオブジェのNextにする
	//m_pPrev = pTop;;				// 生成するオブジェの前をトップに設定
	//pTop->m_pNext = this;		// トップのNextに生成するオブジェを登録

}

CObject3D::CObject3D(int nID) : CObjBase(nID)
{
	// 共通ステータス初期化
	m_nDrawType = DRAWTYPE_2D_NORMAL;
	m_nObjStatus = OBJST_NONE;

	m_bSphere = false;
	m_bBox = false;

	// メッシュ クラス初期化
	m_pMesh = NULL;

	// 描画タイプ
	m_nDrawType = DRAWTYPE_3D_NORMAL;

	// 投影法
	m_nViewProjType = VIEWPROJ_PERS;
}

// デストラクタ
CObject3D::~CObject3D(void)
{
	
}

// 更新
void CObject3D::Update(void)
{
	
}

// 不透明部分描画
void CObject3D::Draw(void)
{
	if (!m_pMesh) return;

	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &m_world);
	m_pMesh->DrawNoAlpha(m_world);
}

// 半透明部分描画
void CObject3D::DrawAlpha(void)
{
	if (!m_pMesh) return;

	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &m_world);
	m_pMesh->Draw(m_world,m_fAlpha);
	
	//CObject3D::DrawAlpha();
	/*D3DCOLORVALUE red = {1.0f, 0.0f, 0.0f, 0.3f};
	D3DCOLORVALUE green = {0.0f, 1.0f, 0.0f, 0.3f};
	if (m_bHit)
		m_pMesh->DrawBox(m_world, red);
	else
		m_pMesh->DrawBox(m_world, green);*/
}

// ワールドマトリックスへの座標セット
void CObject3D::SetPosToMatrix()
{
	m_world._41 = m_vPos.x;
	m_world._42 = m_vPos.y;
	m_world._43 = m_vPos.z;
}

//void CObject3D::SetViewProj()
//{
//	switch(m_nViewProjType)
//	{
//	case VIEWPROJ_PERS:
//
//		break;
//
//	case VIEWPROJ_ORT:
//
//		break;
//	}
//}


void CObject3D::DrawSetUp()
{
	// アルファ ブレンド有効化
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


}

void CObject3D::DrawEnd()
{
		// アルファ ブレンド有効化
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	 // アルファ ブレンド無効化
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

}