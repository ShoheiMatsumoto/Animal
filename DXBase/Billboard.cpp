//=======================================================================================
//
//	  ビルボード関連モジュール
//
//=======================================================================================
//-------- インクルードヘッダ
#include "Billboard.h"

D3DXMATRIX matS;


CBillboard::CBillboard(void)
{
	m_nDrawType = DRAWTYPE_BILLBOARD;
	m_bTrueIsZBuffer = true;

	// 投影法
	m_nViewProjType = VIEWPROJ_ORT;

	m_Board.m_pIndexBuffer = NULL;
	m_Board.m_pVertexBuffer = NULL;
}

CBillboard::CBillboard(int nID, int nTexNum) : CObject3D(nID)
{
	m_Board.Initialize(nTexNum);		// テクスチャ登録
	m_nDrawType = DRAWTYPE_2D_NORMAL;
	m_bTrueIsZBuffer = true;
	m_bAlphaBlend = true;

	m_vSize.x = m_Board.GetSize().x;	// テクスチャサイズからサイズ設定
	m_vSize.y = m_Board.GetSize().y;
	m_vRadius.x = m_vSize.x / 2.0f;
	m_vRadius.y = m_vSize.y / 2.0f;

	// 投影法
	m_nViewProjType = VIEWPROJ_ORT;
}

CBillboard::~CBillboard(void)
{
	ReleaseBillboard();
}


#define FVF_DVERTEX		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define RATE_WIDTH (1.0f / ((float)SCREEN_WIDTH / 2.0f))
#define RATE_HEIGHT (1.0f / ((float)SCREEN_HEIGHT / 2.0f))

////---------------------------------------------------------------------------------------
//// ビルボード初期化
////---------------------------------------------------------------------------------------
void CBillboard::InitializeBillboard()
{
	float radius = m_Board.m_fRadius;
	D3DXVECTOR2 v  = m_Board.GetSize();
	v.x /= 2.0f;
	v.y /= 2.0f;
	int nMaxNum = m_Board.GetImage()->GetPattern();

	// ローカル座標設定
	m_verWk[0].x = -v.x;
	m_verWk[0].y = v.y;
	m_verWk[0].z = 0.0f;

	m_verWk[0].nx = 0.0f;
	m_verWk[0].ny = 0.0f;
	m_verWk[0].nz = -1.0f;

	m_verWk[0].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
	m_verWk[0].tu = 0.0f;
	m_verWk[0].tv = 0.0f;

	m_verWk[1].x = v.x;
	m_verWk[1].y = v.y;
	m_verWk[1].z = 0.0f;

	m_verWk[1].nx = 0.0f;
	m_verWk[1].ny = 0.0f;
	m_verWk[1].nz = -1.0f;

	m_verWk[1].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
	m_verWk[1].tu = 1.0f / nMaxNum;
	m_verWk[1].tv = 0.0f;

	m_verWk[2].x = -v.x;
	m_verWk[2].y = -v.y;
	m_verWk[2].z = 0.0f;

	m_verWk[2].nx = 0.0f;
	m_verWk[2].ny = 0.0f;
	m_verWk[2].nz = -1.0f;

	m_verWk[2].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
	m_verWk[2].tu = 0.0f;// / (float)nMaxNum;
	m_verWk[2].tv = 1.0f;
	
	m_verWk[3].x = v.x;
	m_verWk[3].y = -v.y;
	m_verWk[3].z = 0.0f;

	m_verWk[3].nx = 0.0f;
	m_verWk[3].ny = 0.0f;
	m_verWk[3].nz = -1.0f;

	m_verWk[3].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
	m_verWk[3].tu = 1.0f;
	m_verWk[3].tv = 1.0f;

	m_world._41 = m_vPos.x;
	m_world._42 = m_vPos.y;
	m_world._43 = m_vPos.z;

	// 他ステータス初期値
	m_nR = 255;
	m_nG = 255;
	m_nB = 255;

	m_nAlpha = 255;
	m_nAnimNum = 0;
	m_nCurDivNum = 0;
	m_ntexLR = 0;
	m_ntexTB = 0;
}


//---------------------------------------------------------------------------------------
// ビルボード解放
//---------------------------------------------------------------------------------------
void CBillboard::ReleaseBillboard()
{
	SAFE_RELEASE(m_Board.m_pIndexBuffer);		// インデックスバッファオブジェクトを解放
	SAFE_RELEASE(m_Board.m_pVertexBuffer);		// 頂点バッファオブジェクトを解放
}

//---------------------------------------------------------------------------------------
// ビルボード更新
//---------------------------------------------------------------------------------------
void CBillboard::UpdateBillBoard()
{	
	D3DXMatrixTranslation(&m_world, m_vPos.x, m_vPos.y, m_vPos.z);

	if(m_bBillBoard)
	{
		D3DXMATRIX matView = CCamera::GetThis()->GetMatView();		// ビューマトリックス取得

		m_world._11 = matView._11;
		m_world._12 = matView._21;
		m_world._13 = matView._31;

		m_world._21 = matView._12;
		m_world._22 = matView._22;
		m_world._23 = matView._32;

		m_world._31 = matView._13;
		m_world._32 = matView._23;
		m_world._33 = matView._33;
	}
	
}

//---------------------------------------------------------------------------------------
// ビルボード描画開始
//---------------------------------------------------------------------------------------
void CBillboard::DrawSetUp()
{
	// 透過色(抜き色)を可能にする
	CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Zバッファを更新

	if(m_bAlphaBlend)
	{
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);		// αブレンド可
		CGraphics::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		CGraphics::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		//CGraphics::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
		//CGraphics::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
	}

	if (m_bTrueIsZBuffer) {
		// 透過色(抜き色)の部分をバッファに書き込まない
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0);
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	} else {
		CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	// Zバッファを更新しない
		
	}
	// 描画設定
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);			// ライティングしない

	if(m_bCull)
	{
		// カリングオフ
		CGraphics::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}
	

	//:::::::::::::::::::::::::::::::::::::::::::::::
}


//---------------------------------------------------------------------------------------
// ビルボード描画終了
//---------------------------------------------------------------------------------------
void CBillboard::DrawEnd()
{
	if(m_bCull)
	{
		// カリング
		CGraphics::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
	
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);				// ライティングする

	CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			// Zバッファを更新する

	CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);	// αブレンド 不可

}

//---------------------------------------------------------------------------------------
// ビルボード描画
//---------------------------------------------------------------------------------------
void CBillboard::Draw()
{
	//// ワールドマトリックスをセット
	if (m_world) 
		CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &m_world);


	// 描画
	CGraphics::GetDevice()->SetFVF(FVF_DVERTEX);

	CGraphics::GetDevice()->SetTexture(0, m_Board.m_pImage->GetTexture());						// テクスチャを登録
	CGraphics::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_verWk, sizeof(DVERTEX));// ポリゴン描画

}

// 色セット
void CBillboard::SetBillColor(D3DXVECTOR3 vColor)
{
	//DVERTEX*	VBuffer;								// 頂点バッファへのポインタ
	m_nR = (int)vColor.x;
	m_nG = (int)vColor.y;
	m_nB = (int)vColor.z;

	m_verWk[0].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
	m_verWk[1].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
	m_verWk[2].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
	m_verWk[3].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
}

// テクスチャ座標セット
void CBillboard::SetTexBillUV(int nPattern)
{
	//DVERTEX*	VBuffer;								// 頂点バッファへのポインタ
	
	int nMaxNum = m_Board.GetImage()->GetPattern();
	float fUSize = 1.0f / nMaxNum;
	
	float sub;
	sub = (nPattern - m_nCurDivNum) * fUSize;
	m_nCurDivNum = nPattern;

	m_verWk[0].tu += sub;
	m_verWk[0].tv = 0.0f;

	m_verWk[1].tu += sub;
	m_verWk[1].tv = 0.0f;

	m_verWk[2].tu += sub;
	m_verWk[2].tv = 1.0f;
	
	m_verWk[3].tu += sub;
	m_verWk[3].tv = 1.0f;
}

// アルファ値のセット
void CBillboard::SetBillAlpha(float fAlphaRate)
{
	
	//DVERTEX*	VBuffer;								// 頂点バッファへのポインタ
	m_nAlpha = (int)(255 * fAlphaRate);
	//
	
	m_verWk[0].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
	m_verWk[1].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
	m_verWk[2].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
	m_verWk[3].color = D3DCOLOR_ARGB(m_nAlpha,m_nR,m_nG,m_nB);
}



// スクリーン座標でのアクセス用変換
void CBillboard::InverseScreen(D3DXVECTOR3 vPos)
{
	D3DXMATRIX matMove;
	D3DXMATRIX matView = CCamera::GetThis()->GetMatView();;
	
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(FOVY), (float)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_CLIP, FAR_CLIP);

	D3DXMATRIX matScreen = CreateScreenMat();

	D3DXMatrixIdentity(&matMove);
	D3DXMATRIX matViewToScreen = matView * matProj * matScreen;

	D3DXMATRIX matInv;
	D3DXMatrixInverse(&matInv, NULL, &matViewToScreen);

	D3DXVECTOR3 vOut;
	D3DXVec3TransformCoord(&vOut, &vPos, &matInv);

	m_world._41 = vOut.x;
	m_world._42 = vOut.y;
	m_world._43 = vOut.z;

	//m_vPos = vOut;
}

// 中心
void CBillboard::SetLocalWkC()
{
	float radius = m_Board.m_fRadius;
	D3DXVECTOR2 v  = m_Board.GetSize();
	v.x /= 2.0f;
	v.y /= 2.0f;
	
	// ローカル座標設定
	m_verWk[0].x = -v.x;		// 左上
	m_verWk[0].y = v.y;
	m_verWk[0].z = 0.0f;

	m_verWk[1].x = v.x;			// 右上
	m_verWk[1].y = v.y;
	m_verWk[1].z = 0.0f;

	m_verWk[2].x = -v.x;		// 左下
	m_verWk[2].y = -v.y;
	m_verWk[2].z = 0.0f;

	m_verWk[3].x = v.x;			// 右下
	m_verWk[3].y = -v.y;
	m_verWk[3].z = 0.0f;

	m_nCollBasePoint = COLLBASEPOINT_CENTER;
}

// 左上
void CBillboard::SetLocalWkTL()
{
	D3DXVECTOR2 v = m_Board.GetSize();

	// ローカル座標設定
	m_verWk[0].x = 0.0f;		// 左上
	m_verWk[0].y = 0.0f;
	m_verWk[0].z = 0.0f;

	m_verWk[1].x = v.x;			// 右上
	m_verWk[1].y = 0.0f;
	m_verWk[1].z = 0.0f;

	m_verWk[2].x = 0.0f;		// 左下
	m_verWk[2].y = -v.y;
	m_verWk[2].z = 0.0f;

	m_verWk[3].x = v.x;			// 右下
	m_verWk[3].y = -v.y;
	m_verWk[3].z = 0.0f;

	m_nCollBasePoint = COLLBASEPOINT_TOPLEFT;
}

// 下
void CBillboard::SetLocalWkB()
{
	D3DXVECTOR2 v = m_Board.GetSize();
	D3DXVECTOR2 r = v / 2.0f;

	// ローカル座標設定
	m_verWk[0].x = -r.x;		// 左上
	m_verWk[0].y = v.y;
	m_verWk[0].z = 0.0f;

	m_verWk[1].x = r.x;			// 右上
	m_verWk[1].y = v.y;
	m_verWk[1].z = 0.0f;

	m_verWk[2].x = -r.x;		// 左下
	m_verWk[2].y = 0.0f;
	m_verWk[2].z = 0.0f;

	m_verWk[3].x = r.x;			// 右下
	m_verWk[3].y = 0.0f;
	m_verWk[3].z = 0.0f;

	m_nCollBasePoint = COLLBASEPOINT_BOTTOM;
}

// 左右反転
void CBillboard::ReverseLR(int nType)
{
	//変数宣言
	float a = 1.0f / m_Board.m_nMaxPlain;	//式省略用変数

	if(nType >= TEX_LRALL || nType < 0)
		return;

	m_ntexLR = nType;

	if(nType == TEX_LRNORMAL)
	{
		m_verWk[0].tu = a * m_nCurDivNum;//D3DXVECTOR2(     , 0.0f);
		m_verWk[0].tv = 0.0f;
		m_verWk[1].tu = a * m_nCurDivNum + a;//D3DXVECTOR2( , 0.0f);
		m_verWk[1].tv = 0.0f;
		m_verWk[2].tu = a * m_nCurDivNum;//D3DXVECTOR2(     , 1.0f);
		m_verWk[2].tv = 1.0f;
		m_verWk[3].tu = a * m_nCurDivNum + a;//D3DXVECTOR2( , 1.0f);
		m_verWk[3].tv = 1.0f;
	}
	else
	{
		m_verWk[1].tu = a * m_nCurDivNum;//D3DXVECTOR2(     , 0.0f);
		m_verWk[1].tv = 0.0f;
		m_verWk[0].tu = a * m_nCurDivNum + a;//D3DXVECTOR2( , 0.0f);
		m_verWk[0].tv = 0.0f;
		m_verWk[3].tu = a * m_nCurDivNum;//D3DXVECTOR2(     , 1.0f);
		m_verWk[3].tv = 1.0f;
		m_verWk[2].tu = a * m_nCurDivNum + a;//D3DXVECTOR2( , 1.0f);
		m_verWk[2].tv = 1.0f;
	}

	
}

//=======================================================================================
//	End of File
//=======================================================================================

