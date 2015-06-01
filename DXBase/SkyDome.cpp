#include "SkyDome.h"
#include "Camera.h"

CSkyDome::CSkyDome(void)
{
}

CSkyDome::~CSkyDome(void)
{

}

// スカイドーム初期化
void CSkyDome::InitializeSkyDome()
{

}

void CSkyDome::Draw()
{
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	D3DXMATRIX matWorld;

	D3DXMatrixTranslation(&matWorld,
		m_vCameraPos.x,
		m_vCameraPos.y,
		m_vCameraPos.z);
	if (!m_pMesh) return;
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &m_world);
	m_pMesh->DrawNoAlpha(m_world);

	CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);

}

void CSkyDome::Release()
{

}
