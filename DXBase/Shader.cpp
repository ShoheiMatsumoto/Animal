//=======================================================================================
//
//	シェーダ処理
//
//=======================================================================================

//-------- ヘッダ
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include "Shader.h"
#include "Window.h"
#include "Graphics.h"
//-------- 定数
#define PATH_FXTEST		_T("../data/shader/test.fx")
//#define PATH_TEXDIFFUSE	_T("../data/texture/earth.bmp")
//#define PATH_TEXNORMAL	_T("../data/texture/earthnormal.bmp")

D3DXVECTOR3	CShader::m_vLight = D3DXVECTOR3(0, 0, 0);
D3DXVECTOR3	CShader::m_vCamera = D3DXVECTOR3(0, 0, 0);
D3DXMATRIX	CShader::m_mView;
D3DXMATRIX	CShader::m_mProj;
//-------- グローバル変数

CShader* CShader::m_pThis = NULL;

CShader::CShader()
{
	
}

CShader::~CShader()
{

}

// シェーダ生成
void CShader::Create()
{
	m_pThis = new CShader();

	m_pThis->InitShader();
}

//---------------------------------------------------------------------------------------
// シェーダ初期化
//---------------------------------------------------------------------------------------
HRESULT CShader::InitShader()
{
	m_nTech = 0;
	// シェーダ読み込み
	HRESULT hr = D3DXCreateEffectFromFile(CGraphics::GetDevice(),
		PATH_FXTEST, NULL, NULL, 0, NULL, &m_pFX, NULL);
	if (FAILED(hr)) {
		TCHAR szMsg[1024];
		_stprintf(szMsg, _T("シェーダ(%s)読み込みエラー"),
			PATH_FXTEST);
		MessageBox(GETWND, szMsg, _T("error"), MB_OK);
		return hr;
	}
	// テクスチャ読み込み
	/*hr = D3DXCreateTextureFromFile(m_pDevice,
			PATH_TEXDIFFUSE, &m_pTex);
	hr = D3DXCreateTextureFromFile(m_pDevice,
			PATH_TEXNORMAL, &m_pTexNorm);*/


	// ハンドル取得
	struct _param {
		LPCSTR		pszName;
		D3DXHANDLE*	pHandle;
	} paramS[] = {
		{"WORLDVIEWPROJECTION", &m_hMatWVP},
		{"WORLD",				&m_hMatW},
		{"CAMERAPOSITION",		&m_hCamera},
		{"MATERIALDIFFUSE",		&m_hDiffuse},
		{"MATERIALSPECULAR",	&m_hSpecular},
		{"MATERIALPOWER",		&m_hPower},
		{"MATERIALAMBIENT",		&m_hAmbient},
		{"MATERIALTEXTURE",		&m_hTexture},
		{"MATERIALTEXTUREVALID", &m_hTexEnable},
	};
	for (int i = 0; i < _countof(paramS); i++) {
		*paramS[i].pHandle =
			m_pFX->GetParameterBySemantic(NULL,
									paramS[i].pszName);
	}
	/*struct _param paramG[] =
	{
		{"light", &m_hLight},
		{"texNormal", &m_hTexNormal}
	};
	for(int i = 0; i < _countof(paramG); i++)
	{
		*paramG[i].pHandle = 
			m_pFX->GetParameterByName(NULL, paramG[i].pszName);
	}*/
	m_hLight = m_pFX->GetParameterByName(NULL, "light");
	m_hTech = m_pFX->GetTechnique(0);

	return hr;
}

//---------------------------------------------------------------------------------------
// カメラ情報設定
//---------------------------------------------------------------------------------------
void CShader::SetCamera(LPD3DXVECTOR3 pCamera,
	LPD3DXMATRIX pView, LPD3DXMATRIX pProj)
{
	m_vCamera = *pCamera;
	m_mView = *pView;
	m_mProj = *pProj;
}

//---------------------------------------------------------------------------------------
// 光源ベクトル設定
//---------------------------------------------------------------------------------------
void CShader::SetLight(LPD3DXVECTOR3 pLight)
{
	m_vLight = *pLight;
}

//---------------------------------------------------------------------------------------
// シェーダ開始
//---------------------------------------------------------------------------------------
void CShader::BeginShader()
{
	// テクニック設定
	m_pFX->SetTechnique(m_hTech);
	m_pFX->Begin(NULL, 0);
	// パス開始
	m_pFX->BeginPass(0);
}

//---------------------------------------------------------------------------------------
// ワールド変換行列設定(&シェーダへ設定)
//---------------------------------------------------------------------------------------
void CShader::SetWorldMatrix(LPD3DXMATRIX pWorld)
{
	m_pFX->SetMatrix(m_hMatWVP,
		&(*pWorld * m_mView * m_mProj));		// 掛けた奴
	m_pFX->SetMatrix(m_hMatW, pWorld);			// 単独の
	m_pFX->SetFloatArray(m_hLight, &m_vLight.x, 3);
	m_pFX->SetFloatArray(m_hCamera, &m_vCamera.x, 3);
}

//---------------------------------------------------------------------------------------
// マテリアル設定(&コミット)
//---------------------------------------------------------------------------------------
void CShader::SetMaterial(D3DMATERIAL9* pMaterial,
	LPDIRECT3DTEXTURE9 pTexture)
{
	m_pFX->SetVector(m_hDiffuse,
		(LPD3DXVECTOR4)&pMaterial->Diffuse);
	m_pFX->SetVector(m_hSpecular,
		(LPD3DXVECTOR4)&pMaterial->Specular);
	m_pFX->SetFloat(m_hPower, pMaterial->Power);
	m_pFX->SetVector(m_hAmbient,
		(LPD3DXVECTOR4)&pMaterial->Ambient);
	if (pTexture) {
		m_pFX->SetTexture(m_hTexture, pTexture);
		m_pFX->SetBool(m_hTexEnable, TRUE);
	} else {
		m_pFX->SetBool(m_hTexEnable, FALSE);
	}
	/*m_pFX->SetTexture(m_hTexture, m_pTex);
	m_pFX->SetTexture(m_hTexNormal, m_pTexNorm);*/
	m_pFX->CommitChanges();
}

//---------------------------------------------------------------------------------------
// シェーダ終了
//---------------------------------------------------------------------------------------
void CShader::EndShader()
{
	// パス終了
	m_pFX->EndPass();
	// テクニック終了
	m_pFX->End();
}

//---------------------------------------------------------------------------------------
// シェーダ解放
//---------------------------------------------------------------------------------------
void CShader::FinShader()
{
	SAFE_RELEASE(m_pFX);
	SAFE_DELETE(m_pTex);
	SAFE_DELETE(m_pTexNorm);
}


void CShader::UpdateShader()
{
	if((GetAsyncKeyState(VK_RETURN) & 0x0001) ||
		(GetAsyncKeyState('Q') & 0x0001))
	{
		m_nTech = (m_nTech + 1) % 4;
		m_hTech = m_pFX->GetTechnique(m_nTech);
	}
}


//=======================================================================================
//	End of File
//=======================================================================================