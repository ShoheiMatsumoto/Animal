#include "Morphing.h"

#define STOP_CNT (120)
#define MORPH_TIME (300)
CMorphing::CMorphing(void)
{
}

CMorphing::~CMorphing(void)
{
}

//----------------------------
// 初期化
// -------------------------------
void CMorphing::InitializeMorph(int nMeshNum)
{
	// 変形スタート地点
	m_nPrevID = 0;
	m_nNextID = 1;


	// 位置の初期化
	m_Obj.x  = m_world._41;		m_Obj.y  = m_world._42;		m_Obj.z  = m_world._43;
	// 回転角の初期化
	m_Obj.rotx = 0.0;		m_Obj.roty = 0.0;		m_Obj.rotz = 0.0;
	// モーフィング用変数の初期化
	m_Obj.morph_dir = 0;
	m_Obj.morph_count = 0;
	m_Obj.morph_time[0] = 0;
	m_Obj.morph_time[1] = MORPH_TIME;	// ここで変形時間が決まる
	m_Obj.status = 1;
	m_Obj.StopCnt = STOP_CNT;
		// THRU

	LPD3DXMESH				mesh;			// メッシュオブジェクト
	LPDIRECT3DVERTEXBUFFER9	vertex_buffer;	// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9	index_buffer;	// インデックスバッファ

	DWORD			dwNumMaterials = 0L;
//    LPD3DXBUFFER	pD3DXMtrlBuffer, pD3DXEffectInst;
	MORPH_VERTEX*	pVertices;		// 頂点データへのポインタ
	WORD*			pIndices;		// ポリゴン構成（頂点リンク）データへのポインタ
	MORPH_VERTEX*	pVertices_2;
	WORD*			pIndices_2;

	//static LPCTSTR filename[] = {
	//	_T("box.x"), _T("box1.x")		// モデル（Ｘファイル）のファイル名（２個）
	//};
	int			i;

	for (i = 0; i < nMeshNum; i++) {
	    // Ｘファイルからメッシュデータを読み込む
		//D3DXLoadMeshFromX(filename[i], D3DXMESH_SYSTEMMEM, g_pD3DDevice, NULL,	// ここでＸファイルを指定
			//&pD3DXMtrlBuffer, &pD3DXEffectInst, &dwNumMaterials, &mesh);
		
		// ベースメッシュ取得
		mesh = m_pMorpMesh[i].GetBaseMesh();


		mesh->GetVertexBuffer(&vertex_buffer);	// 頂点バッファオブジェクトへのポインタをゲット
		mesh->GetIndexBuffer(&index_buffer);	// インデックスバッファオブジェクトへのポインタをゲット
		m_nVertexNum[i] = m_pMorpMesh[i].GetNumVertex();	// 頂点数をゲット
		m_nFaceNum[i]  = m_pMorpMesh[i].GetFaceNum();		// 面数をゲット

		// 頂点データ、インデックスデータをメモリにコピー
		m_pVertex[i] = new MORPH_VERTEX[m_nVertexNum[i]];						// 頂点ワーク領域を確保
		m_dwIndex[i]  = new WORD[m_nFaceNum[i]*3];							// インデックスワーク領域を確保
		
		pVertices_2 = m_pVertex[i];
		vertex_buffer->Lock(0, 0, (void**)&pVertices, 0);				// 頂点バッファをロック
		memcpy(pVertices_2, pVertices, sizeof(MORPH_VERTEX)*m_nVertexNum[i]);	// 頂点データをワークにコピー
		vertex_buffer->Unlock();										// 頂点バッファをアンロック

		pIndices_2 = m_dwIndex[i];
		index_buffer ->Lock(0, 0, (void**)&pIndices , 0);				// インデックスバッファをロック
		memcpy(pIndices_2, pIndices, sizeof(WORD)*m_nFaceNum[i]*3);		// インデックスデータをワークにコピー
		index_buffer ->Unlock();										// インデックスバッファをアンロック
	}

	// モーフィング用に頂点バッファ、インデックスバッファを作成
	m_pMorph_Vertex = new MORPH_VERTEX[m_nVertexNum[0]];						// モーフィング用頂点ワーク領域を確保
	m_pwMorph_Index  = new WORD[m_nFaceNum[0]*3];							// モーフィング用インデックスワーク領域を確保

	vertex_buffer->Lock(0, 0, (void**)&pVertices, 0);				// 頂点バッファをロック
	memcpy(m_pMorph_Vertex, pVertices, sizeof(MORPH_VERTEX)*m_nVertexNum[0]);	// 頂点データをワークにコピー
	vertex_buffer->Unlock();										// 頂点バッファをアンロック
	index_buffer ->Lock(0, 0, (void**)&pIndices , 0);				// インデックスバッファをロック
	memcpy(m_pwMorph_Index, pIndices, sizeof(WORD)*m_nFaceNum[0]*3);		// インデックスデータをワークにコピー
	index_buffer ->Unlock();										// インデックスバッファをアンロック

}

//----------------------------------------
// モーフィング中間データ作成
//----------------------------------------
void CMorphing::UpdateMorph()
{
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;	// 回転マトリックス（３種）
	D3DXMATRIX	matTrans;							// 平行移動マトリックス
	MORPH_OBJECT*		pt;									// オブジェクトへのポインタ

	//　（１）変形前モデルの頂点へのポインタ（pt_vertex[0]）
	//　　　　変形後モデルの頂点へのポインタ（pt_vertex[1]）
	//　　　　計算後モデルの頂点へのポインタ（morph_vertex）をワーク変数にセット
	MORPH_VERTEX* pt1		= m_pVertex[m_nPrevID];
	MORPH_VERTEX* pt2		= m_pVertex[m_nNextID];
	MORPH_VERTEX* ptWk		= m_pMorph_Vertex;

	//----- 処理本体
	pt = &m_Obj;
	

#define ROTATE_SPEED (0.04f)
	// キー入力による回転
	//if (GetAsyncKeyState(VK_UP   ) & 0x8000)
		pt->rotx += ROTATE_SPEED;	// カーソル（上）
	if (GetAsyncKeyState(VK_DOWN ) & 0x8000) 
		pt->rotx -= ROTATE_SPEED;	// カーソル（下）
	//if (GetAsyncKeyState(VK_LEFT ) & 0x8000)
		pt->roty -= ROTATE_SPEED * 2;	// カーソル（左）
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) 
		pt->roty += ROTATE_SPEED;	// カーソル（右）
	//if (GetAsyncKeyState(VK_PRIOR) & 0x8000) 
		pt->rotz += ROTATE_SPEED;	// Page Up
	if (GetAsyncKeyState(VK_NEXT ) & 0x8000) 
		pt->rotz -= ROTATE_SPEED;	// Page Down
	// マトリックスを合成
	D3DXMatrixRotationX(&matRotateX, pt->rotx);							// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, pt->roty);							// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, pt->rotz);							// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, pt->x, pt->y, pt->z);				// 平行移動マトリックスを生成
	m_world = matRotateX * matRotateY * matRotateZ * matTrans;		// マトリックスを合成（順序に注意！）

	//**************************************************************************
	//
	//　ここにモーフィングの計算処理を追加する。
	//
	
		

	for(int i = 0; i < m_nVertexNum[m_nPrevID]; i ++)
	{
		//　（２）変形前の時間と変形後の時間と現在の時間から割合を求める
		float t = (float)m_Obj.morph_count;
		float t0 = (float)m_Obj.morph_time[0];
		float t1 = (float)m_Obj.morph_time[1]; 
		float trate = (float)((t - t0) / (t1 - t0));
			

		//　（３）割合と変形前後の座標の差分から変形量を求める
		float x, y, z;
		x = pt1->x + (pt2->x - pt1->x) * trate;
		y = pt1->y + (pt2->y - pt1->y) * trate;
		z = pt1->z + (pt2->z - pt1->z) * trate;

		//　（４）計算後モデルの頂点ワークに格納
		ptWk->x = x;
		ptWk->y = y;
		ptWk->z = z;
			
		//　（５）ポインタをそれぞれ＋１
		pt1 ++;
		pt2 ++;
		ptWk ++;

		//　（６）以上の処理を頂点数だけループして全ての頂点を処理する

	}
	//
	//　＊補足
	//　　変形前の時間    g_Object.morph_time[0]
	//　　変形後の時間    g_Object.morph_time[1]
	//　　現在の時間      g_Object.morph_count
	//
	//**************************************************************************



	switch (pt->morph_dir) 
	{
	case 0:			// 0 > 1
		if(++(pt->morph_count) >= pt->morph_time[1]) 
		{
			pt->morph_dir = 1;	// 方向を反転
			/*m_nPrevID = (m_nPrevID + 1) % m_nMorpMeshNum;
			m_nNextID = (m_nNextID + 1) % m_nMorpMeshNum;
			pt->morph_count = 0;*/
		}
		break;
	case 1:			// 1 > 0
		if(--(pt->StopCnt) <= 0                ) 
		{
			pt->morph_dir = 0;	// 方向を反転
			m_nPrevID = (m_nPrevID + 1) % m_nMorpMeshNum;
			m_nNextID = (m_nNextID + 1) % m_nMorpMeshNum;
			pt->morph_count = 0;
			pt->StopCnt = STOP_CNT;
		}
		break;
	}

}


//-------------------------------------
// モーフィング更新
//--------------------------------------
void CMorphing::Update()
{

}

//-------------------------------
// モーフィング描画
//------------------------------
void CMorphing::Draw()
{
	CGraphics::GetDevice()->SetFVF(FVF_VERTEX);							// 頂点フォーマット指定
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &m_world);	// ワールドマトリクスをセット

	//if (g_Wireframe) {
	//	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);				// ライト無効化
	//	g_pD3DDevice->SetTexture(0, NULL);									// テクスチャ無し
	//	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);	// ワイヤーフレーム描画
	//} else {
	//	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);					// ライト有効化
	//	g_pD3DDevice->SetTexture(0, g_pD3DTexture);							// テクスチャ設定
	//	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);		// ソリッド描画
	//}

	CGraphics::GetDevice()->SetTexture(0, m_pD3DTexture);							// テクスチャ設定
	CGraphics::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);		// ソリッド描画

	CGraphics::GetDevice()->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,		// モーフィングモデルを描画
				0, m_nVertexNum[0], m_nFaceNum[0], m_pwMorph_Index,
				D3DFMT_INDEX16, m_pMorph_Vertex, sizeof(MORPH_VERTEX));
}