//=======================================================================================
//
//	シェーダ定義
//
//=======================================================================================
#ifndef _H_SHADER
#define _H_SHADER

//-------- ヘッダ
#include "main.h"
#include "define.h"
//

#define GETSHADER (CShader::GetThis())

// テクニック列挙
enum
{
	SHADER_NONE = 0, // 使わない（普通の）

	SHADER_1,

	SHADER_ALL
};

//-------- シェーダクラス
class CShader
{
protected:


private:
	static CShader*		m_pThis;

	LPD3DXEFFECT	m_pFX;		// エフェクト オブジェクト
	D3DXHANDLE		m_hMatWVP;	// ワールド×ビュー×射影
	D3DXHANDLE		m_hMatW;	// ワールド マトリックス
	D3DXHANDLE		m_hCamera;	// 視点座標
	D3DXHANDLE		m_hLight;	// 光源ベクトル
	D3DXHANDLE		m_hDiffuse;	// (マテリアル)拡散色
	D3DXHANDLE		m_hSpecular;// (マテリアル)鏡面反射色
	D3DXHANDLE		m_hPower;	// (マテリアル)鏡面反射指数
	D3DXHANDLE		m_hAmbient;	// (マテリアル)環境色
	D3DXHANDLE		m_hTexture;	// テクスチャ
	D3DXHANDLE		m_hTexEnable;// テクスチャ有無
	D3DXHANDLE		m_hTech;	// テクニック

	D3DXHANDLE		m_hTexNormal;	// 法線マップテクスチャ
	LPDIRECT3DTEXTURE9 m_pTex;
	LPDIRECT3DTEXTURE9 m_pTexNorm;

	static D3DXVECTOR3	m_vLight;
	static D3DXVECTOR3	m_vCamera;
	static D3DXMATRIX	m_mView;
	static D3DXMATRIX	m_mProj;

	int m_nTech;

public:
	CShader();
	~CShader();

	void Create();

	HRESULT InitShader();	// 初期化
	void UpdateShader();
	void BeginShader();		// シェーダ開始
	void SetCamera(LPD3DXVECTOR3 pCamera,
	LPD3DXMATRIX pView, LPD3DXMATRIX pProj);
	void SetLight(LPD3DXVECTOR3 pLight);
	void SetWorldMatrix(LPD3DXMATRIX pWorld);
	void SetMaterial(D3DMATERIAL9* pMaterial,
	LPDIRECT3DTEXTURE9 pTexture);
	void EndShader();		// シェーダ終了
	void FinShader();		// 解放

	// ゲッター
	static CShader* GetThis(){return m_pThis;};
};


#endif

//=======================================================================================
//	End of File
//=======================================================================================