#include "MapPartsBase.h"


CMapPartsBase::CMapPartsBase(void)
{
}

CMapPartsBase::CMapPartsBase(int nID, int nTexNum, D3DXVECTOR3 vPos, int nPartsType) : CBillboard(nID, nTexNum)
{
	m_nObjGroupID = OBJ3DGROUP_MAP;		// グループタイプ設定
	m_nObjTypeID = nPartsType;			// タイプ設定

	m_vPos = vPos;		// 後でベースに移したい

	m_bBillBoard = false;	// ビルボード処理オフ
	m_bAlphaBlend = false;	// アルファブレンドオフ
	m_nCollBasePoint = COLLBASEPOINT_CENTER;		// あたり判定基準点
}

CMapPartsBase::~CMapPartsBase(void)
{
}

// 生成
CMapPartsBase*	CMapPartsBase::Create(int nID, int nTexNum, D3DXVECTOR3 vPos, D3DXVECTOR3 vSize, int nPartsType)
{
	CMapPartsBase* p = new CMapPartsBase(nID, nTexNum, vPos, nPartsType);

	p->Initialize(nPartsType, vSize);

	return p;
}

// 初期化
void		CMapPartsBase::Initialize(int nPartsType, D3DXVECTOR3 vSize)
{
	m_nPartsType = nPartsType;		// パーツタイプセット
	


	m_Board.ReSize(D3DXVECTOR2(vSize.x, vSize.y));		
	SetSize(D3DXVECTOR3(vSize.x, vSize.y, 0.0f));
	SetPosToMatrix();		// マトリックスへの座標セット

	// ビルボード初期化
	InitializeBillboard();

	if(nPartsType == MAPPARTS_RDOWN)// テクスチャ反転
		ReverseLR(TEX_LRREV);
}

// 更新
void		CMapPartsBase::Update()
{
	// ビルボード更新
	UpdateBillBoard();
}

// 判定後更新
void		CMapPartsBase::HitUpdate()
{

}

// 解放
void		CMapPartsBase::Release()
{
	delete this;
}



// eof
