#include "Sky.h"


CSky::CSky(void)
{
}

CSky::~CSky(void)
{
	
}

//---------------------------------------------
// 生成
// --------------------------------------------
CSky* CSky::Create(CMesh* pMesh)
{
	CSky* pSky;
	pSky = new CSky();

	// オブジェクトにメッシュセット
	pSky->SetMesh(pMesh);

	// 初期化処理
	pSky->Initialize();

	return pSky;
}

//------------------------------------------------
// 初期化処理
//-------------------------------------------------
void CSky::Initialize(void)
{
	// ステータス初期化
	m_vPos.x = m_world._41;
	m_vPos.y = m_world._42;
	m_vPos.z = m_world._43;

	m_vLocalVec[0] = D3DXVECTOR3(m_world._11, m_world._12, m_world._13);
	m_vLocalVec[1] = D3DXVECTOR3(m_world._21, m_world._22, m_world._23);
	m_vLocalVec[2] = D3DXVECTOR3(m_world._31, m_world._32, m_world._33);

	//m_vSpeed.y = 0.2;
}

