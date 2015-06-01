//=======================================================================================
//
//	  メッシュ クラス
//
//=======================================================================================
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <stdio.h>
#include "define.h"

#include "Mesh.h"
#include "Graphics.h"

//---------------------------------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------------------------------
CMesh::CMesh()
{
	m_pD3DMesh = NULL;
	m_dwNumMaterial = 0;
	m_pMaterial = NULL;
	m_ppTexture = NULL;

	m_pAttr = NULL;
	m_dwAttr = 0;
	m_dwVtx = 0;
	m_pVtx = NULL;
	m_dwIdx = 0;
	m_pIdx = NULL;

	m_vHalf = D3DXVECTOR3(0, 0, 0);
	m_vCenter = D3DXVECTOR3(0, 0, 0);
	m_fRadius = 0;
	m_pSphere = NULL;

	m_pPiece = NULL;
	m_pPieceVtx = NULL;
	m_nBombCnt = 0;

	
}

//---------------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------------
CMesh::~CMesh()
{
	//Finalize();
}

bool CMesh::Initialize(LPCTSTR pszFName, int nType)
{
	switch(nType)
	{
	case MESH_N:
		InitializeNorm(pszFName);
		break;

	case MESH_S:
		InitializeSkin(pszFName);
		break;
	}

	return true;
}

//---------------------------------------------------------------------------------------
// メッシュ初期化
//---------------------------------------------------------------------------------------
bool CMesh::InitializeNorm(LPCTSTR pszFName)
{
	TCHAR			szMsg[MAX_PATH + 32];
	TCHAR			szDir[_MAX_DIR];
	TCHAR			szCurrentDir[_MAX_PATH];

	LPD3DXBUFFER	pD3DXMtrlBuffer = NULL;

	// メッシュタイプの設定
	m_nMeshType = MESH_N;

	// フォルダ名を抽出
	_tsplitpath(pszFName, NULL, szDir, NULL, NULL);

	

	// Ｘファイルからメッシュデータを読み込む
	HRESULT hr = D3DXLoadMeshFromX(pszFName, D3DXMESH_SYSTEMMEM, CGraphics::GetDevice(),
		NULL, &pD3DXMtrlBuffer, NULL, &m_dwNumMaterial, &m_pD3DMesh);
	
	
	
	if (FAILED(hr)) {
		_stprintf(szMsg, _T("Xファイル(%s)の読み込みに失敗しました。"), pszFName);
		MessageBox(NULL, szMsg, NULL, MB_OK);
		return false;
	}

	// FVF形式を補正(頂点フォーマットを変換)
	LPD3DXMESH pMeshTmp;
	DWORD dwFVF = m_pD3DMesh->GetFVF();
	if (dwFVF != FVF_BVERTEX) {
		hr = m_pD3DMesh->CloneMeshFVF(m_pD3DMesh->GetOptions(), FVF_BVERTEX,
			CGraphics::GetDevice(), &pMeshTmp);
		SAFE_RELEASE(m_pD3DMesh);
		if (FAILED(hr)) {
			SAFE_RELEASE(pD3DXMtrlBuffer);
			return false;
		}
		// 法線が無い場合は強制的に追加
		if ((dwFVF & D3DFVF_NORMAL) == 0) {
			D3DXComputeNormals(pMeshTmp, NULL);
		}
		m_pD3DMesh = pMeshTmp;
	}

	// 属性テーブルを生成するための最適化
	hr = m_pD3DMesh->Optimize(D3DXMESHOPT_ATTRSORT, NULL, NULL, NULL, NULL, &pMeshTmp);
	if (SUCCEEDED(hr)) {
		m_pD3DMesh->Release();
		m_pD3DMesh = pMeshTmp;
	} else {
		SAFE_RELEASE(pD3DXMtrlBuffer);
		return false;
	}
	// 属性テーブル取得
	hr = m_pD3DMesh->GetAttributeTable(NULL, &m_dwAttr);
	if (FAILED(hr)) {
		SAFE_RELEASE(pD3DXMtrlBuffer);
		SAFE_RELEASE(m_pD3DMesh);
		return false;
	}
	m_pAttr = new D3DXATTRIBUTERANGE[m_dwAttr];
	hr = m_pD3DMesh->GetAttributeTable(m_pAttr, &m_dwAttr);
	// 頂点バッファ/インデックスバッファ固定
	LPVOID pVtx;
	m_pD3DMesh->LockVertexBuffer(D3DLOCK_READONLY, &pVtx);
	LPVOID pIdx;
	m_pD3DMesh->LockIndexBuffer(D3DLOCK_READONLY, &pIdx);
	// 抽出場所の確保
	m_dwVtx = m_pD3DMesh->GetNumVertices();
	m_pVtx = new BVERTEX[m_dwVtx];
	m_dwFace = m_pD3DMesh->GetNumFaces();
	m_dwIdx = m_dwFace * 3;
	m_pIdx = new WORD[m_dwIdx];
	m_pPiece = new PARTICLE[m_dwFace];
	m_pPieceVtx = new BVERTEX[m_dwIdx];
	// コピー
	CopyMemory(m_pVtx, pVtx, sizeof(BVERTEX) * m_dwVtx);
	CopyMemory(m_pIdx, pIdx, sizeof(WORD) * m_dwIdx);
	// 頂点バッファ/インデックスバッファ解放
	m_pD3DMesh->UnlockVertexBuffer();
	m_pD3DMesh->UnlockIndexBuffer();

	// カレントディレクトリを変更
	if (szDir[0]) {
		GetCurrentDirectory(_MAX_PATH, szCurrentDir);
		SetCurrentDirectory(szDir);
	}

	// マテリアル読み込み
	D3DXMATERIAL* pD3DMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMaterial = new D3DMATERIAL9[m_dwNumMaterial];
	m_ppTexture = new LPDIRECT3DTEXTURE9[m_dwNumMaterial];
	for (DWORD i = 0; i < m_dwNumMaterial; i++) { 
		m_pMaterial[i] = pD3DMaterials[i].MatD3D;
		m_pMaterial[i].Ambient = m_pMaterial[i].Diffuse;
		m_ppTexture[i] = NULL;
		if (pD3DMaterials[i].pTextureFilename && pD3DMaterials[i].pTextureFilename[0]) {
			// テクスチャファイルを読み込む
			if (FAILED(D3DXCreateTextureFromFileA(CGraphics::GetDevice(),
				pD3DMaterials[i].pTextureFilename, &m_ppTexture[i]))) {
				_stprintf(szMsg, _T("テクスチャ(%hs)の読み込みに失敗しました。"),
					pD3DMaterials[i].pTextureFilename);
				MessageBox(NULL, szMsg, NULL, MB_OK);
			}
		}
	}

	// カレントディレクトリを元に戻す
	if (szDir[0])
		SetCurrentDirectory(szCurrentDir);

	pD3DXMtrlBuffer->Release();

	// 境界ボックス生成
	D3DXVECTOR3 vMin = m_pVtx[0].pos;
	D3DXVECTOR3 vMax = vMin;
	BVERTEX* pBVtx = m_pVtx + 1;
	for (DWORD i = 1; i < m_dwVtx; i++, pBVtx++) {
		if (vMin.x > pBVtx->pos.x)
			vMin.x = pBVtx->pos.x;
		if (vMin.y > pBVtx->pos.y)
			vMin.y = pBVtx->pos.y;
		if (vMin.z > pBVtx->pos.z)
			vMin.z = pBVtx->pos.z;
		if (vMax.x < pBVtx->pos.x)
			vMax.x = pBVtx->pos.x;
		if (vMax.y < pBVtx->pos.y)
			vMax.y = pBVtx->pos.y;
		if (vMax.z < pBVtx->pos.z)
			vMax.z = pBVtx->pos.z;
	}
	m_vHalf = (vMax - vMin) / 2.0f;
	m_vCenter = (vMax + vMin) / 2.0f;

	// 境界球の生成
	m_fRadius = 0.0f;
	float fR;
	for (DWORD i = 0; i < m_dwVtx; i++) {
		fR = D3DXVec3Length(&(m_pVtx[i].pos - m_vCenter));
		if (m_fRadius < fR)
			m_fRadius = fR;
	}

	// 境界球イメージの生成
	D3DXCreateSphere(CGraphics::GetDevice(),
 		m_fRadius, 32, 16, &m_pSphere, NULL);

	// 境界ボックスイメージの生成
	D3DXCreateBox(CGraphics::GetDevice(),
		vMax.x - vMin.x, vMax.y - vMin.y, vMax.z - vMin.z, &m_pBox, NULL);

	return true;
}

//----------------------------------------------
// スキンメッシュアニメ用初期化
//--------------------------------------------------
bool CMesh::InitializeSkin(LPCTSTR pszFName)
{
	// ディレクトリ抽出
	TCHAR szDir[_MAX_PATH];
	TCHAR szDirWk[_MAX_DIR];
	_tsplitpath(pszFName, szDir, szDirWk, NULL, NULL);
	lstrcat(szDir, szDirWk);
	m_Hierarchy.SetDirectory(szDir);

	// メッシュタイプの設定
	m_nMeshType = MESH_S;

	// アニメーション入りメッシュ読み込み
	// 階層構造メッシュの読み込み
	HRESULT hr = D3DXLoadMeshHierarchyFromX(pszFName,
		D3DXMESH_MANAGED, CGraphics::GetDevice(),
		&m_Hierarchy, NULL,
		&m_pFrameRoot, &m_pAnimCtrl);
	if (FAILED(hr)) return false;
	//if (!m_pAnimCtrl) return false;
	// ボーンとフレームの関連付け
	hr = AllocAllBoneMatrix(m_pFrameRoot);
	if (FAILED(hr)) return false;

	// アニメーションセット取得
	m_uNumAnimSet = 0;
	if (m_pAnimCtrl)
	{
		m_uNumAnimSet = m_pAnimCtrl->GetNumAnimationSets();
		
		if (m_uNumAnimSet > 0) 
		{
			//m_ppAnimSet = new LPD3DXANIMATIONSET[m_uNumAnimSet];
			m_pAnim = new HLANIM_DESC[m_uNumAnimSet];

			for (DWORD u = 0; u < m_uNumAnimSet; ++u) {
				//m_pAnimCtrl->GetAnimationSet(u, &m_ppAnimSet[u]);
				m_pAnimCtrl->GetAnimationSet(u, &m_pAnim[u].pAnimSet);
				m_pAnim[u].m_uiAnimID = u;
				m_pAnim[u].fCurWeightTime = 0.0f;
				m_pAnim[u].fLoopTime = 1.0f;
				m_pAnim[u].fShiftTime = 120.0f;
				m_pAnim[u].fTrackSpeed = 1.0f;
				m_uiCurID = u;
			}
		}
	}



	// 経過時間計測用時刻設定
	m_dwPrev = ::timeGetTime();
	return SUCCEEDED(hr);
	//*********************************************
}


//---------------------------------------------------------------------------------------
// メッシュ解放
//---------------------------------------------------------------------------------------
void CMesh::Finalize()
{
	if(m_nMeshType == MESH_N)
	{
		// 境界球イメージの解放
		SAFE_RELEASE(m_pSphere);

		SAFE_DELETE_ARRAY(m_pPiece);
		SAFE_DELETE_ARRAY(m_pPieceVtx);

		SAFE_DELETE_ARRAY(m_pVtx);
		SAFE_DELETE_ARRAY(m_pIdx);

		SAFE_DELETE_ARRAY(m_pAttr);

		// テクスチャ オブジェクトを解放
		if (m_ppTexture) {
			for (DWORD i = 0; i < m_dwNumMaterial; i++) {
				SAFE_RELEASE(m_ppTexture[i]);
			}
			SAFE_DELETE_ARRAY(m_ppTexture);
		}
		SAFE_DELETE_ARRAY(m_pMaterial);

		SAFE_RELEASE(m_pD3DMesh);	// メッシュ オブジェクトを解放
	}
	
	if(m_nMeshType == MESH_S)
	{
		if (m_pAnim) {
		for (DWORD u = 0; u < m_uNumAnimSet; ++u) {
			SAFE_RELEASE(m_pAnim[u].pAnimSet);
		}
		SAFE_DELETE_ARRAY(m_pAnim);
	}

	SAFE_RELEASE(m_pAnimCtrl);

	// メッシュ破棄
	if (m_pFrameRoot) {
		D3DXFrameDestroy(m_pFrameRoot, &m_Hierarchy);
		m_pFrameRoot = NULL;
	}
	}
	
}

//---------------------------------------------------------------------------------------
// メッシュ描画
//---------------------------------------------------------------------------------------
void CMesh::Draw(D3DXMATRIX& world)
{
	// ワールド マトリックス設定
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
    pDevice->SetTransform(D3DTS_WORLD, &world);

	for (DWORD i = 0; i < m_dwAttr; i++) {
		DWORD id = m_pAttr[i].AttribId;
        // アルファ値をチェック
        D3DMATERIAL9 mtrl = m_pMaterial[id];
		if (mtrl.Diffuse.a < 1.0f)
			continue;
		pDevice->SetMaterial(&mtrl);
		pDevice->SetTexture(0, m_ppTexture[id]);	// テクスチャを設定
//		m_pD3DMesh->DrawSubset(id);								// 描画を実行
		pDevice->SetFVF(FVF_BVERTEX);
		pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0,
			m_dwVtx, m_pAttr[i].FaceCount, &m_pIdx[m_pAttr[i].FaceStart * 3],
			D3DFMT_INDEX16, m_pVtx, sizeof(BVERTEX));
	}

	// アルファ ブレンド有効化
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	for (DWORD i = 0; i < m_dwAttr; i++) {
		DWORD id = m_pAttr[i].AttribId;
        // アルファ値をチェック
        D3DMATERIAL9 mtrl = m_pMaterial[id];
		if (mtrl.Diffuse.a >= 1.0f)
			continue;
		pDevice->SetMaterial(&mtrl);
		pDevice->SetTexture(0, m_ppTexture[id]);	// テクスチャを設定
		
//		m_pD3DMesh->DrawSubset(id);								// 描画を実行
		pDevice->SetFVF(FVF_BVERTEX);
		pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0,
			m_dwVtx, m_pAttr[i].FaceCount, &m_pIdx[m_pAttr[i].FaceStart * 3],
			D3DFMT_INDEX16, m_pVtx, sizeof(BVERTEX));
	}

    // アルファ ブレンド無効化
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CMesh::Draw(D3DXMATRIX& world, float fAlpha)
{
    // ワールド マトリックス設定
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
    pDevice->SetTransform(D3DTS_WORLD, &world);

    // アルファ ブレンド有効化
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    for (DWORD i = 0; i < m_dwAttr; i++) {
        DWORD id = m_pAttr[i].AttribId;

        // アルファ値を変更
        D3DMATERIAL9 mtrl = m_pMaterial[id];
        mtrl.Diffuse.a *= fAlpha;
        pDevice->SetMaterial(&mtrl);

        pDevice->SetTexture(0, m_ppTexture[id]);
        pDevice->SetFVF(FVF_BVERTEX);
//		pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0,
//			m_dwVtx, m_pAttr[i].FaceCount, &m_pIdx[m_pAttr[i].FaceStart * 3],
//			D3DFMT_INDEX16, m_pVtx, sizeof(BVERTEX));
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_pAttr[i].FaceCount,
			&m_pPieceVtx[m_pAttr[i].FaceStart * 3],
			sizeof(BVERTEX));
    }

    // アルファ ブレンド無効化
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
// 断片の初期化
void CMesh::InitParticle()
{
	// 頂点座標、テクスチャ座標をコピー
	for (DWORD i = 0; i < m_dwIdx; ++i) {
		m_pPieceVtx[i].pos = m_pVtx[m_pIdx[i]].pos;
		m_pPieceVtx[i].tex = m_pVtx[m_pIdx[i]].tex;
	}
	D3DXVECTOR3 v0, v1, n;
	for (DWORD i = 0; i < m_dwFace; ++i) {
		// 法線ベクトルを生成
		v0 = m_pPieceVtx[i * 3 + 1].pos
			- m_pPieceVtx[i * 3 + 0].pos;
		v1 = m_pPieceVtx[i * 3 + 2].pos
			- m_pPieceVtx[i * 3 + 1].pos;
		D3DXVec3Cross(&n, &v0, &v1);
		D3DXVec3Normalize(&n, &n);
		m_pPieceVtx[i * 3 + 0].nor = n;
		m_pPieceVtx[i * 3 + 1].nor = n;
		m_pPieceVtx[i * 3 + 2].nor = n;
		// 速度、加速度の初期化
		m_pPiece[i].spd = n * INIT_SPD;
		m_pPiece[i].acl =
			D3DXVECTOR3(0.0f, -GRAVITY, 0.0f);
	}
}

// 断片の移動
bool CMesh::UpdateParticle()
{
	for (DWORD i = 0; i < m_dwFace; ++i) {
		m_pPieceVtx[i * 3 + 0].pos += m_pPiece[i].spd;
		m_pPieceVtx[i * 3 + 1].pos += m_pPiece[i].spd;
		m_pPieceVtx[i * 3 + 2].pos += m_pPiece[i].spd;
		m_pPiece[i].spd += m_pPiece[i].acl;
	}
	m_nBombCnt ++;

	if(m_nBombCnt == 120)
		return true;;

	return false;
}

// 境界球の描画
void CMesh::DrawSphere(D3DXMATRIX& world, D3DCOLORVALUE color)
{
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	// ワールド マトリックス設定
	D3DXMATRIX m;
	D3DXMatrixTranslation(&m, m_vCenter.x, m_vCenter.y, m_vCenter.z);
	m *= world;
    pDevice->SetTransform(D3DTS_WORLD, &m);

    // アルファ ブレンド有効化
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    //pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    //pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// メッシュ描画
	D3DMATERIAL9 mtrl = {
		color,//Diffuse
		color,//Ambient
		{1.0f, 1.0f, 1.0f, 1.0f},//Specular
		{0.0f, 0.0f, 0.0f, 1.0f},//Emissive
		1.0f//Power
	};
	pDevice->SetMaterial(&mtrl);
	pDevice->SetTexture(0, NULL);
	pDevice->SetFVF(D3DFVF_XYZ |
		D3DFVF_NORMAL | D3DFVF_TEX1);
	m_pSphere->DrawSubset(0);

    // アルファ ブレンド無効化
    //pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

// 境界ボックスの描画
void CMesh::DrawBox(D3DXMATRIX& world, D3DCOLORVALUE color)
{
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	// ワールド マトリックス設定
	D3DXMATRIX m;
	D3DXMatrixTranslation(&m, m_vCenter.x, m_vCenter.y, m_vCenter.z);
	m *= world;
    pDevice->SetTransform(D3DTS_WORLD, &m);

    // アルファ ブレンド有効化
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// メッシュ描画
	D3DMATERIAL9 mtrl = {
		color,//Diffuse
		color,//Ambient
		{1.0f, 1.0f, 1.0f, 1.0f},//Specular
		{0.0f, 0.0f, 0.0f, 1.0f},//Emissive
		1.0f//Power
	};
	pDevice->SetMaterial(&mtrl);
	pDevice->SetTexture(0, NULL);
	pDevice->SetFVF(D3DFVF_XYZ |
		D3DFVF_NORMAL | D3DFVF_TEX1);
	m_pBox->DrawSubset(0);

    // アルファ ブレンド無効化
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

//---------------------------------------------------------------------------------------
// メッシュ不透明部分のみ描画
//---------------------------------------------------------------------------------------
void CMesh::DrawNoAlpha(D3DXMATRIX& world)
{
	// ワールド マトリックス設定
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
    pDevice->SetTransform(D3DTS_WORLD, &world);

	for (DWORD i = 0; i < m_dwAttr; i++) {
		DWORD id = m_pAttr[i].AttribId;
        // アルファ値をチェック
        D3DMATERIAL9 mtrl = m_pMaterial[id];
		if (mtrl.Diffuse.a < 1.0f)
			continue;
		pDevice->SetMaterial(&mtrl);
		pDevice->SetTexture(0, m_ppTexture[id]);	// テクスチャを設定
		m_pD3DMesh->DrawSubset(id);								// 描画を実行
	}
}

//---------------------------------------------------------------------------------------
// メッシュ半透明部分のみ描画 (アルファ有効化/無効化なし)
//---------------------------------------------------------------------------------------
void CMesh::DrawAlpha(D3DXMATRIX& world)
{
	// ワールド マトリックス設定
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
    pDevice->SetTransform(D3DTS_WORLD, &world);

	for (DWORD i = 0; i < m_dwAttr; i++) {
		DWORD id = m_pAttr[i].AttribId;
        // アルファ値をチェック
        D3DMATERIAL9 mtrl = m_pMaterial[id];
		if (mtrl.Diffuse.a >= 1.0f)
			continue;
		pDevice->SetMaterial(&mtrl);
		pDevice->SetTexture(0, m_ppTexture[id]);	// テクスチャを設定
		m_pD3DMesh->DrawSubset(id);					// 描画を実行
	}
}

// レイとメッシュの交点を求める
// true…交点あり、false…交点なし
//bool CMesh::Intersect(
//	LPD3DXVECTOR3 pPos,		//始点
//	LPD3DXVECTOR3 pDir,		//向き
//	LPD3DXVECTOR3 pCross,	//交点
//	LPD3DXVECTOR3 pNormal)	//交点の法線
//{
//	// 全ての三角形を探索
//	for (DWORD i = 0; i < m_dwIdx; ) {
//		// 三角形の3頂点を取得
//		D3DXVECTOR3& v0 = m_pVtx[m_pIdx[i++]].pos;
//		D3DXVECTOR3& v1 = m_pVtx[m_pIdx[i++]].pos;
//		D3DXVECTOR3& v2 = m_pVtx[m_pIdx[i++]].pos;
//		// 三角形の法線ベクトルを求める
//		D3DXVECTOR3 n;
//		D3DXVec3Cross(&n, &(v1 - v0), &(v2 - v1));
//		D3DXVec3Normalize(&n, &n);
//		// 向きのチェック
//		float base = D3DXVec3Dot(&n, pDir);
//		if (base >= 0.0f) continue;
//		// 三角形の内外判定(レイに平行な三角柱で)
//		D3DXVECTOR3 np;
//		D3DXVec3Cross(&np, &(v1 - v0), pDir);
//		if (D3DXVec3Dot(&np, &(*pPos - v0)) < 0.0f)
//			continue;//柱の外
//		D3DXVec3Cross(&np, &(v2 - v1), pDir);
//		if (D3DXVec3Dot(&np, &(*pPos - v1)) < 0.0f)
//			continue;//柱の外
//		D3DXVec3Cross(&np, &(v0 - v2), pDir);
//		if (D3DXVec3Dot(&np, &(*pPos - v2)) < 0.0f)
//			continue;//柱の外
//		// 交点の計算
//		float t = D3DXVec3Dot(&n, &(v0 - *pPos)) / base;
//		//if (t < 0.0f) continue;//レイより手前
//		//if (t > 1.0f) continue;//レイより先
//		// 交点と法線ベクトルを返す
//		if (pCross) *pCross = *pPos + t * *pDir;
//		if (pNormal) *pNormal = n;
//		return true;	// 交点あり
//	}
//	return false;	// 交点なし
//}

// アニメ関連
//---------------------------------------------------------------------------------------
// フレームのマトリックスを更新
//---------------------------------------------------------------------------------------
void CMesh::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	// 親のマトリックスを掛け合わせる
	if (pParentMatrix) {
		pFrame->CombinedTransformationMatrix =
			pFrame->TransformationMatrix * *pParentMatrix;
	} else {
		pFrame->CombinedTransformationMatrix =
			pFrame->TransformationMatrix;
	}
	// 兄弟フレームがあればマトリックスを更新
	if (pFrame->pFrameSibling) {
		UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
	}
	// 子フレームがあればマトリックスを更新
	if (pFrame->pFrameFirstChild) {
		// 自分が親となるので、自分のマトリックスを渡す
		UpdateFrameMatrices(pFrame->pFrameFirstChild,
			&pFrame->CombinedTransformationMatrix);
	}
}

//---------------------------------------------------------------------------------------
// フレームの描画
//---------------------------------------------------------------------------------------
void CMesh::DrawFrame(LPD3DXFRAME pFrame)
{
	LPD3DXMESHCONTAINER pMeshContainer = pFrame->pMeshContainer;
	while (pMeshContainer) {
		// メッシュコンテナの描画
		RenderMeshContainer(pMeshContainer, pFrame);
		// 次のメッシュコンテナ
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}
	// 兄弟フレームがあれば兄弟フレームを描画
	if (pFrame->pFrameSibling)
		DrawFrame(pFrame->pFrameSibling);
	// 子フレームがあれば子フレームを描画
	if (pFrame->pFrameFirstChild)
		DrawFrame(pFrame->pFrameFirstChild);
}

//---------------------------------------------------------------------------------------
// メッシュコンテナの描画
//---------------------------------------------------------------------------------------
void CMesh::RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase)
{
	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	if (pMeshContainer->pSkinInfo) {
		// スキンメッシュモデル
		LPD3DXBONECOMBINATION pBoneCombi =
			(LPD3DXBONECOMBINATION)
			pMeshContainer->pBoneBuffer->GetBufferPointer();

		DWORD dwPrevBoneID = UINT_MAX;
		DWORD dwBlendMatrix;
		for (DWORD i = 0; i < pMeshContainer->dwBone; ++i) {
			dwBlendMatrix = 0;
			for (DWORD k = 0; k < pMeshContainer->dwWeight; ++k) {
				if (pBoneCombi[i].BoneId[k] != UINT_MAX)
					dwBlendMatrix = k;
			}
			CGraphics::GetDevice()->SetRenderState(
				D3DRS_VERTEXBLEND, dwBlendMatrix);	// 頂点ブレンディング
			for (DWORD k = 0; k < pMeshContainer->dwWeight; ++k) {
				DWORD id = pBoneCombi[i].BoneId[k];
				if (id != UINT_MAX) {
					CGraphics::GetDevice()->SetTransform(
						D3DTS_WORLDMATRIX(k),
						&(pMeshContainer->pBoneOffsetMatrix[id] *
						*pMeshContainer->ppBoneMatrix[id]));
				}
			}
			CGraphics::GetDevice()->SetMaterial(
&pMeshContainer->pMaterials[pBoneCombi[i].AttribId].MatD3D);
			CGraphics::GetDevice()->SetTexture(0,
pMeshContainer->ppTextures[pBoneCombi[i].AttribId]);
			dwPrevBoneID = pBoneCombi[i].AttribId;
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}
		return;
	}
	// スキン無しモデル
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);
	for (DWORD iAttrib = 0; iAttrib < pMeshContainer->NumMaterials; ++iAttrib) {
		DWORD dwAttrib = pMeshContainer->pAttributeTable[iAttrib].AttribId;
		CGraphics::GetDevice()->SetMaterial(&pMeshContainer->pMaterials[dwAttrib].MatD3D);
		CGraphics::GetDevice()->SetTexture(0, pMeshContainer->ppTextures[dwAttrib]);
		pMeshContainer->MeshData.pMesh->DrawSubset(dwAttrib);
	}
}

//---------------------------------------------------------------------------------------
// ボーン用ワールド・マトリックス領域確保
//---------------------------------------------------------------------------------------
HRESULT CMesh::AllocBoneMatrix(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	if (pMeshContainer->pSkinInfo == NULL)
		return S_OK;	// スキン情報が無ければ何もしない
	DWORD dwBoneNum = pMeshContainer->pSkinInfo->GetNumBones();
	pMeshContainer->ppBoneMatrix = new LPD3DXMATRIX[dwBoneNum];
	for (DWORD i = 0; i < dwBoneNum; ++i) {
		MYFRAME* pFrame = (MYFRAME*)D3DXFrameFind(m_pFrameRoot,
			pMeshContainer->pSkinInfo->GetBoneName(i));
		if (pFrame == NULL)
			return E_FAIL;
		pMeshContainer->ppBoneMatrix[i] =
			&pFrame->CombinedTransformationMatrix;
	}
	return S_OK;
}

HRESULT CMesh::AllocAllBoneMatrix(LPD3DXFRAME pFrameBase)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	HRESULT hr = S_OK;
	if (pFrame->pMeshContainer) {
		hr = AllocBoneMatrix(pFrame->pMeshContainer);
		if (FAILED(hr))
			return hr;
	}
	if (pFrame->pFrameSibling) {
		hr = AllocAllBoneMatrix(pFrame->pFrameSibling);
		if (FAILED(hr))
			return hr;
	}
	if (pFrame->pFrameFirstChild) {
		hr = AllocAllBoneMatrix(pFrame->pFrameFirstChild);
	}
	return hr;
}

//---------------------------------------------------------------------------------------
// アニメーション切替
//---------------------------------------------------------------------------------------
void CMesh::SwitchAnimSet(UINT uAnimSet)
{
	if (uAnimSet >= m_uNumAnimSet || m_pAnimCtrl == NULL) return;
	m_pAnimCtrl->SetTrackAnimationSet(0, m_ppAnimSet[uAnimSet]);
}

//---------------------------------------------------------------------------------------
// アニメーション開始時間設定
//---------------------------------------------------------------------------------------
void CMesh::SetTime(double dTime)
{
	if (m_pAnimCtrl == NULL) return;
	for (DWORD i = 0;i < m_pAnimCtrl->GetMaxNumTracks(); ++i) {
		m_pAnimCtrl->SetTrackPosition(i, 0);
	}
	m_pAnimCtrl->ResetTime();
	m_pAnimCtrl->AdvanceTime(dTime, NULL);
}

//---------------------------------------------------------------------------------------
// アニメーションコントローラを取得
//---------------------------------------------------------------------------------------
void CMesh::GetAnimationController( ID3DXAnimationController **ppAnimCont )
{
		
}

//---------------------------------------------------------------------------------------
// アニメーションスピード設定設定(引数：アニメのNo,　秒 )
//---------------------------------------------------------------------------------------
void CMesh::SetLoopTime(int nNo, float fSec)
{
	//float fAdj = m_ppAnimSet[nNo]->GetPeriod();
	float fAdj = (float)m_pAnim[nNo].pAnimSet->GetPeriod();

	fAdj /= fSec;
	
	m_pAnimCtrl->SetTrackSpeed(nNo, fAdj);	
}

//---------------------------------------------------------------------------------------
// 動作開始にかかる時間を設定
//---------------------------------------------------------------------------------------
void CMesh::SetShiftTime( UINT animID, FLOAT interval )
{
	// シフト時間を登録
	m_pAnim[animID].fShiftTime = interval;

}

//---------------------------------------------------------------------------------------
// アニメーションを切り替え
//---------------------------------------------------------------------------------------
void CMesh::ChangeAnimation( UINT animID )
{
   // 異なるアニメーションであるかをチェック
   if( m_uiCurID == animID )
       return;

    // 現在のアニメーションセットの設定値を取得
   D3DXTRACK_DESC TD;   // トラックの能力
   m_pAnimCtrl->GetTrackDesc( 0, &TD );

    // 今のアニメーションをトラック1に移行し
   // トラックの設定値も移行
   m_pAnimCtrl->SetTrackAnimationSet( 1, m_pAnim[m_uiCurID].pAnimSet);
   m_pAnimCtrl->SetTrackDesc( 1, &TD );

    // 新しいアニメーションセットをトラック0に設定
   m_pAnimCtrl->SetTrackAnimationSet( 0, m_pAnim[animID].pAnimSet );

    // トラック0のスピードの設定
   m_pAnimCtrl->SetTrackSpeed( 0, m_pAnim[animID].fTrackSpeed );

    // トラックの合成を許可
   m_pAnimCtrl->SetTrackEnable( 0, true );
   m_pAnimCtrl->SetTrackEnable( 1, true );

    // ウェイト時間を初期化
   m_pAnim[animID].fCurWeightTime = 0.0f;

    // 現在のアニメーション番号を切り替え
   m_uiPreID = m_uiCurID;
   m_uiCurID = animID;

	
}

//---------------------------------------------------------------------------------------
// アニメーションを更新
//---------------------------------------------------------------------------------------
void CMesh::AdvanceTime( FLOAT time )
{
	// 合成中か否かを判定
   m_pAnim[m_uiCurID].fCurWeightTime += time;
    if( m_pAnim[m_uiCurID].fCurWeightTime <= m_pAnim[m_uiCurID].fShiftTime )
    {
       // 合成中。ウェイトを算出
      FLOAT Weight = m_pAnim[m_uiCurID].fCurWeightTime / m_pAnim[m_uiCurID].fShiftTime;
       // ウェイトを登録
      m_pAnimCtrl->SetTrackWeight( 0, Weight );       // 現在のアニメーション
     m_pAnimCtrl->SetTrackWeight( 1, 1 - Weight );   // 前のアニメーション
   }
    else
    {
       // 合成終了中。通常アニメーションをするTrack0のウェイトを最大値に
      m_pAnimCtrl->SetTrackWeight( 0, 1.0f );       // 現在のアニメーション
	  m_pAnimCtrl->SetTrackEnable( 1, false );      // 前のアニメーションを無効にする
   }

    // 時間を更新
	m_pAnimCtrl->AdvanceTime( time, NULL );

}

//---------------------------------------------------------------------------------------
// メッシュ描画
//---------------------------------------------------------------------------------------
void CMesh::DrawSkin(D3DXMATRIX& world)
{
	// アニメーション更新
	DWORD dwNow = ::timeGetTime();
	double d = (dwNow - m_dwPrev) / 1000.0;
	m_dwPrev = dwNow;
	//if(m_pAnimCtrl)
		//m_pAnimCtrl->AdvanceTime(d, NULL);
	AdvanceTime((float)d);

	// マトリックス更新
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &world);
	if (m_pFrameRoot) {
		UpdateFrameMatrices(m_pFrameRoot, &world);
		// フレーム描画
		DrawFrame(m_pFrameRoot);
	}
}

// レイとメッシュの交点を求める
// true…交点あり、false…交点なし
bool CMesh::Intersect(
	LPD3DXVECTOR3 pPos,		//始点
	LPD3DXVECTOR3 pDir,		//向き
	LPD3DXVECTOR3 pCross,	//交点
	LPD3DXVECTOR3 pNormal)	//交点の法線
{
	// 全ての三角形を探索
	for (DWORD i = 0; i < m_dwIdx; ) {
		// 三角形の3頂点を取得
		D3DXVECTOR3& v0 = m_pVtx[m_pIdx[i++]].pos;
		D3DXVECTOR3& v1 = m_pVtx[m_pIdx[i++]].pos;
		D3DXVECTOR3& v2 = m_pVtx[m_pIdx[i++]].pos;
		// 三角形の法線ベクトルを求める
		D3DXVECTOR3 n;
		D3DXVec3Cross(&n, &(v1 - v0), &(v2 - v1));
		D3DXVec3Normalize(&n, &n);
		// 向きのチェック
		float base = D3DXVec3Dot(&n, pDir);
		if (base >= 0.0f) continue;
		// 三角形の内外判定(レイに平行な三角柱で)
		D3DXVECTOR3 np;
		D3DXVec3Cross(&np, &(v1 - v0), pDir);
		if (D3DXVec3Dot(&np, &(*pPos - v0)) < 0.0f)
			continue;//柱の外
		D3DXVec3Cross(&np, &(v2 - v1), pDir);
		if (D3DXVec3Dot(&np, &(*pPos - v1)) < 0.0f)
			continue;//柱の外
		D3DXVec3Cross(&np, &(v0 - v2), pDir);
		if (D3DXVec3Dot(&np, &(*pPos - v2)) < 0.0f)
			continue;//柱の外
		// 交点の計算
		float t = D3DXVec3Dot(&n, &(v0 - *pPos)) / base;
		//if (t < 0.0f) continue;//レイより手前
		//if (t > 1.0f) continue;//レイより先
		// 交点と法線ベクトルを返す
		if (pCross) *pCross = *pPos + t * *pDir;
		if (pNormal) *pNormal = n;
		return true;	// 交点あり
	}
	return false;	// 交点なし
}

//=======================================================================================
//	End of File
//=======================================================================================