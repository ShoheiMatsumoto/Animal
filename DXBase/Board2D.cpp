// インクルード
#include "Board2D.h"
#include "SceneBase.h"


CBoard2D::CBoard2D(void)
{

}


CBoard2D::~CBoard2D(void)
{
	//SAFE_RELEASE(m_Image->pTexture);			// テクスチャオブジェクトを解放
	
}

//==============================
//初期処理
//==============================
void CBoard2D::Initialize(DWORD dwImageType)
{
	// テクスチャがなかったらエラー処理
	/*if(dwImageType == 0)
		return E_FAIL;*/

	//2Dポリゴン用テクスチャのロード
	
	m_nImageType = dwImageType;
	m_pImage = CSceneBase::GetCurScene()->GetTexMgr()->GetTex(dwImageType);	// シーンからイメージデータを入手
	
	//頂点の設定
	D3DXVECTOR2* pv = m_pImage->GetSize();
	m_vSize = *pv;							// サイズ取得
	m_vHalfSize = m_vSize / 2.0f;			// 半径取得

	m_verWk[0].vtx = D3DXVECTOR4(-pv->x / 2.0f,	-pv->y / 2.0f,	0.0f, 0.0f);
	m_verWk[1].vtx = D3DXVECTOR4( pv->x / 2.0f,	-pv->y / 2.0f,	0.0f, 0.0f);
	m_verWk[2].vtx = D3DXVECTOR4(-pv->x / 2.0f,	 pv->y / 2.0f,	0.0f, 0.0f);
	m_verWk[3].vtx = D3DXVECTOR4( pv->x / 2.0f,	 pv->y / 2.0f,	0.0f, 0.0f);

	//頂点カラー・αチャンネルの設定
	m_verWk[0].diffuse = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	m_verWk[1].diffuse = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	m_verWk[2].diffuse = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
	m_verWk[3].diffuse = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	//テクスチャ座標の設定
	int nMaxNum = m_pImage->GetPattern();
	m_verWk[0].tex = D3DXVECTOR2(0.0f				, 0.0f);
	m_verWk[1].tex = D3DXVECTOR2(1.0f / nMaxNum	, 0.0f);
	m_verWk[2].tex = D3DXVECTOR2(0.0f				, 1.0f);
	m_verWk[3].tex = D3DXVECTOR2(1.0f / nMaxNum	, 1.0f);

	m_nMaxPlain		= nMaxNum;
	/*m_bScrollFlag	= false;
	m_fScrollSpdX	= 0.0f;
	m_fScrollSpdY	= 0.0f;
	m_fScrollPosX	= 0.0f;
	m_fScrollPosY	= 0.0f;*/

	// 半径計算？(とりあえず短い方を半径に)
	D3DXVECTOR2* pV = m_pImage->GetHalfSize();
	m_fRadius		= pV->x < pV->y ? pV->x : pV->y;

	for(int i = 0; i < 4; i++)
		m_nColor[i] = 255;

	m_nR = 255;
	m_nG = 255;
	m_nB = 255;
	m_nAlpha = 255;
	m_nCurDivNum = 0;
	m_ntexLR = 0;
	m_ntexTB = 0;
	//return S_OK;
}

//==============================
//更新処理
//==============================
//void CBoard2D::Update(void)
//{

	//D3DXMATRIX mWorld, mT, mR, mS;

	////行列計算
	//D3DXMatrixTranslation(&mT, (float)m_Data.x, (float)m_Data.y, 0.0f);
	//D3DXMatrixScaling(&mS, (float)m_Data.sx, (float)m_Data.sy, 0.0f);
	//D3DXMatrixRotationZ(&mR , D3DXToRadian(m_Data.angle));

	//mWorld = mS * mR * mT;

	//if(m_Data.alpha > 255 || m_Data.alpha < 0)
	//	int a = 0;

	//m_verPos[0].diffuse = D3DCOLOR_RGBA(m_nColor[0], m_nColor[1], m_nColor[2], m_Data.alpha);
	//m_verPos[1].diffuse = D3DCOLOR_RGBA(m_nColor[0], m_nColor[1], m_nColor[2], m_Data.alpha);
	//m_verPos[2].diffuse = D3DCOLOR_RGBA(m_nColor[0], m_nColor[1], m_nColor[2], m_Data.alpha);
	//m_verPos[3].diffuse = D3DCOLOR_RGBA(m_nColor[0], m_nColor[1], m_nColor[2], m_Data.alpha);

	////アフィン変換
	//for(int nCntVer = 0 ; nCntVer < 4 ; nCntVer ++)
	//{
	//	m_verCopy[nCntVer] = m_verPos[nCntVer];
	//	D3DXVec2TransformCoord((D3DXVECTOR2 *)&m_verCopy[nCntVer].vtx , (D3DXVECTOR2 *)&m_verPos[nCntVer].vtx , &mWorld);
	//}

	//if(m_bScrollFlag)
	//{
	//	m_fScrollPosX += m_fScrollSpdX;
	//	m_fScrollPosY += m_fScrollSpdY;

	//	m_verPos[0].tex = D3DXVECTOR2(m_fScrollPosX        , m_fScrollPosY);
	//	m_verPos[1].tex = D3DXVECTOR2(m_fScrollPosX + 1.0f , m_fScrollPosY);
	//	m_verPos[2].tex = D3DXVECTOR2(m_fScrollPosX        , m_fScrollPosY + 1.0f);
	//	m_verPos[3].tex = D3DXVECTOR2(m_fScrollPosX + 1.0f , m_fScrollPosY + 1.0f);
	//}
//}


//==============================
//描画処理
//==============================
//void CBoard2D::Draw(void)
//{
//	// テクスチャが貼られていなかったらエラー処理
//	if(m_Data.type == 0)
//		return;
//
//	//頂点フォーマットの設定
//	GetGraph->GetDevice()->SetFVF(FVF_VERTEX_2D);
//
//	// レンダリングステートの設定
//	CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,	(m_Data.flag & FLAG_ALPHA) ? TRUE:FALSE);						// アルファブレンド無効
//	CGraphics::GetDevice()->SetRenderState(D3DRS_DESTBLEND,			(m_Data.flag & FLAG_ONE) ? D3DBLEND_ONE:D3DBLEND_INVSRCALPHA);	// 加算合成無効
////	CGraphics::GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);	// 拡大用(バイリニア・フィルタリング)
////	CGraphics::GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);	// 縮小用(バイリニア・フィルタリング)
//
//	//テクスチャの設定
//	if(m_nImageType != NULL)	//←これ外さないと1個前のテクスチャのまま
//		GetGraph->GetDevice()->SetTexture(0 , CScene::GetThis()->GetImage(m_nImageType)->GetTexture());
//
//	//ポリゴンの描画
//	GetGraph->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP , 2 , m_verCopy , sizeof(VERTEX_2D));
//
//}


//==============================
//位置を変えるC
//==============================
void CBoard2D::SetPosC(D3DXVECTOR3 vPos)
{
	D3DXVECTOR2 vS = m_vHalfSize;

	m_verWk[0].vtx = D3DXVECTOR4(vPos.x - vS.x,	vPos.y - vS.y, vPos.z, 1.0f); 
	m_verWk[1].vtx = D3DXVECTOR4(vPos.x + vS.x, vPos.y - vS.y, vPos.z, 1.0f);
	m_verWk[2].vtx = D3DXVECTOR4(vPos.x - vS.x,	vPos.y + vS.y, vPos.z, 1.0f);
	m_verWk[3].vtx = D3DXVECTOR4(vPos.x + vS.x, vPos.y + vS.y, vPos.z, 1.0f);
}

//==============================
//位置を変えるL
//==============================
void CBoard2D::SetPosL(D3DXVECTOR3 vPos)
{
	D3DXVECTOR2 vS = m_vSize;

	m_verWk[0].vtx = D3DXVECTOR4(vPos.x       ,	vPos.y, vPos.z, 1.0f); 
	m_verWk[1].vtx = D3DXVECTOR4(vPos.x + vS.x, vPos.y, vPos.z, 1.0f);
	m_verWk[2].vtx = D3DXVECTOR4(vPos.x       ,	vPos.y + vS.y, vPos.z, 1.0f);
	m_verWk[3].vtx = D3DXVECTOR4(vPos.x + vS.x, vPos.y + vS.y, vPos.z, 1.0f);
}

//==============================
//表示する絵を変える
//==============================
void CBoard2D::SetNum(int nNum)
{
	//変数宣言
	float a = 1.0f / m_nMaxPlain;	//式省略用変数
	float sub;

	if(nNum >= m_nMaxPlain)
		return;
	
	sub = (nNum - m_nCurDivNum) * a;	// 移動差分

	m_nCurDivNum = nNum;		// 現在分割位置更新

	m_verWk[0].tex = D3DXVECTOR2(m_verWk[0].tex.x + sub     , 0.0f);
	m_verWk[1].tex = D3DXVECTOR2(m_verWk[1].tex.x + sub , 0.0f);
	m_verWk[2].tex = D3DXVECTOR2(m_verWk[2].tex.x + sub     , 1.0f);
	m_verWk[3].tex = D3DXVECTOR2(m_verWk[3].tex.x + sub , 1.0f);
}


//==============================
//透過度を変える
//==============================
void CBoard2D::SetAlpha(float fAlpha)
{
	int nAlpha = (int)(255 * fAlpha);
	m_nAlpha = nAlpha;

	m_verWk[0].diffuse = D3DCOLOR_RGBA(m_nR , m_nG , m_nB , nAlpha);
	m_verWk[1].diffuse = D3DCOLOR_RGBA(m_nR , m_nG , m_nB , nAlpha);
	m_verWk[2].diffuse = D3DCOLOR_RGBA(m_nR , m_nG , m_nB , nAlpha);
	m_verWk[3].diffuse = D3DCOLOR_RGBA(m_nR , m_nG , m_nB , nAlpha);
}

//==============================
// 板ポリのリサイズ
//==============================
void CBoard2D::ReSize(D3DXVECTOR2 vSize)
{
	D3DXVECTOR2 vPos;
	D3DXVECTOR2 v = m_vHalfSize;		// 元ハーフサイズ取得

	// 中心座標
	vPos.x = m_verWk[0].vtx.x + v.x;
	vPos.y = m_verWk[0].vtx.y + v.y;

	m_verWk[0].vtx = D3DXVECTOR4(vPos.x + (-vSize.x / 2.0f), vPos.y + (-vSize.y / 2.0f),	0.0f, 0.0f);
	m_verWk[1].vtx = D3DXVECTOR4(vPos.x + (vSize.x / 2.0f),  vPos.y + (-vSize.y / 2.0f),	0.0f, 0.0f);
	m_verWk[2].vtx = D3DXVECTOR4(vPos.x + (-vSize.x / 2.0f), vPos.y + (vSize.y / 2.0f),	0.0f, 0.0f);
	m_verWk[3].vtx = D3DXVECTOR4(vPos.x + (vSize.x / 2.0f),  vPos.y + (vSize.y / 2.0f),	0.0f, 0.0f);

	// サイズ更新
	m_vSize = vSize;
	m_vHalfSize = vSize / 2.0f;
	m_fRadius = m_vHalfSize.x;
}

//==============================
// 板ポリを左を基準にリサイズ
//==============================
void CBoard2D::SetLength(float fLength)
{
	float fPos = 	m_verWk[0].vtx.x;

	m_verWk[1].vtx.x = fPos + fLength;
	m_verWk[3].vtx.x = fPos + fLength;
}

// サイズの変更
void CBoard2D::SetSize(D3DXVECTOR2 vSize)
{
	m_vSize = vSize;
	m_vHalfSize = vSize / 2.0f;
}

// カラーの変更
void CBoard2D::SetColor(int nR, int nG, int nB)
{
	m_nR = nR;
	m_nG = nG;
	m_nB = nB;

	//頂点カラー・αチャンネルの設定
	m_verWk[0].diffuse = D3DCOLOR_RGBA(nR , nG , nB , m_nAlpha);
	m_verWk[1].diffuse = D3DCOLOR_RGBA(nR , nG , nB , m_nAlpha);
	m_verWk[2].diffuse = D3DCOLOR_RGBA(nR , nG , nB , m_nAlpha);
	m_verWk[3].diffuse = D3DCOLOR_RGBA(nR , nG , nB , m_nAlpha);

}

// 左右反転
void CBoard2D::ReverseLR(int nType)
{
	//変数宣言
	float a = 1.0f / m_nMaxPlain;	//式省略用変数

	if(nType >= TEX_LRALL || nType < 0)
		return;

	m_ntexLR = nType;

	if(nType == TEX_LRNORMAL)
	{
		m_verWk[0].tex = D3DXVECTOR2(a * m_nCurDivNum     , 0.0f);
		m_verWk[1].tex = D3DXVECTOR2(a * m_nCurDivNum + a , 0.0f);
		m_verWk[2].tex = D3DXVECTOR2(a * m_nCurDivNum     , 1.0f);
		m_verWk[3].tex = D3DXVECTOR2(a * m_nCurDivNum + a , 1.0f);
	}
	else
	{
		m_verWk[1].tex = D3DXVECTOR2(a * m_nCurDivNum     , 0.0f);
		m_verWk[0].tex = D3DXVECTOR2(a * m_nCurDivNum + a , 0.0f);
		m_verWk[3].tex = D3DXVECTOR2(a * m_nCurDivNum     , 1.0f);
		m_verWk[2].tex = D3DXVECTOR2(a * m_nCurDivNum + a , 1.0f);
	}

	
}

// 上下反転
void CBoard2D::ReverseTB(int nType)
{

}
