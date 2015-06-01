#include "PoliLine.h"
#include "SceneBase.h"
#include "Camera.h"

#define ADD_RATE (1.0f / LINEPOINT_MAX)

CPoliLine::CPoliLine(void)
{
}


CPoliLine::~CPoliLine(void)
{
}

CPoliLine* CPoliLine::Create(int nTexNum, D3DXVECTOR3 vInitPos, D3DXVECTOR3 vDestPos, float fWidth)
{
	CPoliLine*	pLine = new CPoliLine();

	pLine->m_vInitPos = vInitPos;
	pLine->m_vDestPos = vDestPos;
	pLine->m_fLineWidth = fWidth;

	pLine->Initialize(nTexNum);
	
	return pLine;
}

void CPoliLine::Initialize(int nImage)
{
	// テクスチャ設定
	m_Board.Initialize(nImage);

	// ステータス初期化

	// 中間点
	CalcLine();

	// 進行方向ベクトル
	CalcDirVec();

	// カメラへの方向ベクトル
	CalcCameraVec();

	// 広げる方向のベクトル
	CalcDiffVec();

	// 四角形へと広げる
	CalcSquare();

	D3DXMatrixIdentity(&m_world);

}

// 更新
void CPoliLine::Update()
{
	SetPosLine();
}

void CPoliLine::DrawSetUp()
{
	// カリングオフ
	CGraphics::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ライトオフ
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	if(m_bAlphaBlend)
	{
		CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Zバッファを更新

		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		CGraphics::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		CGraphics::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	
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
}

void CPoliLine::DrawEnd()
{
	// ライトオン
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);

	CGraphics::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		// Zバッファを更新する

	//CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

// 描画
void CPoliLine::Draw()
{
	//// ワールドマトリックスをセット
	if (m_world) 
		CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &m_world);

	// 描画
	CGraphics::GetDevice()->SetFVF(FVF_DVERTEX);
	CGraphics::GetDevice()->SetTexture(0, m_Board.m_pImage->GetTexture());						// テクスチャを登録

	CGraphics::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, (LINEPOINT_MAX * 2) - 2, m_verWk, sizeof(DVERTEX));// ポリゴン描画

}

// ライン計算
void CPoliLine::CalcLine()
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vVec = m_vDestPos - m_vInitPos;		// 方向ベクトル

	// 始点終点から中間点計算
	for(int i = 0; i < LINEPOINT_MAX; i ++)
	{
		vPos = vVec * m_fRate;					// 移動量
		m_vLinePos[i] = m_vInitPos + vPos;		// 移動
		m_fRate += ADD_RATE;					// レート更新
	}
}

// 進行方向計算
void CPoliLine::CalcDirVec()
{
	D3DXVECTOR3 vVec;		// ワーク

	// 進行方向のベクトルを取得
	for(int i = 0; i < LINEPOINT_MAX - 1; i ++)
	{
		vVec = m_vLinePos[i + 1] - m_vLinePos[i];		// 方向ベクトル計算
		D3DXVec3Normalize(&vVec, &vVec);		// 単位化
		m_vDirVec[i] = vVec;		
	}

	// 終点には一個前と同じものを
	m_vDirVec[LINEPOINT_MAX - 1] = m_vDirVec[LINEPOINT_MAX - 2];
}

// カメラへのベクトル計算
void CPoliLine::CalcCameraVec()
{
	// カメラの座標を取得
	D3DXVECTOR3 vCamPos = CCamera::GetThis()->GetPos();
	D3DXVECTOR3 vVec;
	// 各点からカメラの方向へのベクトルを計算
	for(int i = 0; i < LINEPOINT_MAX; i ++)
	{
		vVec = vCamPos - m_vLinePos[i];
		D3DXVec3Normalize(&vVec, &vVec);		// 単位化
		m_vCameraVec[i] = vVec;
	}

}

// 拡散方向計算
void CPoliLine::CalcDiffVec()
{
	D3DXVECTOR3 vVec;

	// 進行方向とカメラ方向のベクトルの外積から垂直のベクトルを計算
	for(int i = 0; i < LINEPOINT_MAX; i ++)
	{
		D3DXVec3Cross(&vVec, &m_vDirVec[i], &m_vCameraVec[i]);
		D3DXVec3Normalize(&vVec, &vVec);		// 単位化
		m_vDiffVec[i] = vVec;
	}
}

// 四角形計算
void CPoliLine::CalcSquare()
{
	float fW = m_fLineWidth;
	float fU = 1.0f / (float)((LINEPOINT_MAX -1));
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vMov;
	D3DXVECTOR3 vMovDir, vMovDiff, vVec;

	vPos = m_vLinePos[0];

	for(int i = 0; i < LINEPOINT_MAX; i ++)
	{
		
		vMovDir.x = fW * m_vDirVec[i].x;
		vMovDir.y = fW * m_vDirVec[i].y;
		vMovDir.z = fW * m_vDirVec[i].z;
		
		vMovDiff.x = fW * m_vDiffVec[i].x;
		vMovDiff.y = fW * m_vDiffVec[i].y;
		vMovDiff.z = fW * m_vDiffVec[i].z;

		// 二つ分の移動量
		vVec = /*vMovDir +*/ vMovDiff;
		
		m_verWk[i * 2    ].x = vPos.x + vVec.x;
		m_verWk[i * 2    ].y = vPos.y + vVec.y;
		m_verWk[i * 2    ].z = vPos.z + vVec.z;
		
		m_verWk[i * 2 + 1].x = vPos.x - vVec.x;
		m_verWk[i * 2 + 1].y = vPos.y - vVec.y;
		m_verWk[i * 2 + 1].z = vPos.z - vVec.z;

		m_verWk[i * 2    ].nx = 0.0f;
		m_verWk[i * 2    ].ny = 0.0f;
		m_verWk[i * 2    ].nz = -1.0f;
		
		m_verWk[i * 2 + 1].nx = 0.0f;
		m_verWk[i * 2 + 1].ny = 0.0f;
		m_verWk[i * 2 + 1].nz = -1.0f;
		
		

		//頂点カラー・αチャンネルの設定
		m_verWk[i * 2    ].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		m_verWk[i * 2 + 1].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		//m_vLineWk[i * 4 + 2].diffuse = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		//m_vLineWk[i * 4 + 3].diffuse = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

		//テクスチャ座標の設定
		
		m_verWk[i * 2    ].tu = fU * i;
		m_verWk[i * 2    ].tv = 0.0f;
		m_verWk[i * 2 + 1].tu = fU * i;
		m_verWk[i * 2 + 1].tv = 1.0f;
		//m_vLineWk[i * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//m_vLineWk[i * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 動き出すまでの時間を設定
		m_Point[i * 2    ].m_nTimer = 20 * i;
		m_Point[i * 2 + 1].m_nTimer = 20 * i;
		
	}

	// 
}

void CPoliLine::SetPosLine()
{
	for(int i = 0; i < LINEPOINT_MAX * 2; i++)
	{
		m_verWk[i].x = m_verWk[i].x + 1.0f;
	}
}
