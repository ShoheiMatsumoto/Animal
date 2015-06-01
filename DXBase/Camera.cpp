// カメラ クラス
#include "Camera.h"
#include "Graphics.h"
#include "Input.h"

CCamera* CCamera::m_pThis = NULL;

CCamera::CCamera(void)
{
	m_vPos  = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	m_vLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vUp   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_nType = CT_FIXED;
	m_vNewPos = D3DXVECTOR3(0.0f, 10.0f, -1000.0f);
	m_vAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vAdPos = D3DXVECTOR3(0.0f, 5.0f, 1000.0f);
	m_vAdLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nEffectType = C_EFFECT_NORMAL;

	m_pThis = this;
}

CCamera::~CCamera(void)
{
}

// 更新
void CCamera::Update(D3DXMATRIX* pBase)
{
	// エフェクト更新
	UpdateEffect();

	switch (m_nType) {
	case CT_FIRSTPERSON:
		D3DXVec3TransformCoord(&m_vNewPos,
			&D3DXVECTOR3(0.0f, 0.6f, 6.0f),
			pBase);
		D3DXVec3TransformCoord(&m_vNewLook,
			&D3DXVECTOR3(0.0f, 0.6f, 1000.0f),
			pBase);
		m_vNewUp.x = pBase->_21;
		m_vNewUp.y = pBase->_22;
		m_vNewUp.z = pBase->_23;
		break;
	case CT_THIRDPERSON:
		D3DXVec3TransformCoord(&m_vNewPos,
			&D3DXVECTOR3(0.0f, 5.0f, -30.0f),
			pBase);
		D3DXVec3TransformCoord(&m_vNewLook,
			&D3DXVECTOR3(0.0f, 0.0f, 1000.0f),
			pBase);
		m_vNewUp.x = pBase->_21;
		m_vNewUp.y = pBase->_22;
		m_vNewUp.z = pBase->_23;
		break;
	default:	// CT_FIXED
		
		/*if(GETINPUT->GetKey(KEY_PRS, DIK_A))
			m_vAngle.x = D3DXToRadian(1);
		if(GETINPUT->GetKey(KEY_PRS, DIK_D))
			m_vAngle.x = D3DXToRadian(1);
		if(GETINPUT->GetKey(KEY_PRS, DIK_W))
			m_vAngle.y = D3DXToRadian(1);
		if(GETINPUT->GetKey(KEY_PRS, DIK_S))
			m_vAngle.y = D3DXToRadian(1);
		if(GETINPUT->GetKey(KEY_PRS, DIK_R))
			m_vNewPos.z += 100;
		if(GETINPUT->GetKey(KEY_PRS, DIK_F))
			m_vNewPos.z -= 100;*/

		m_vNewPos = D3DXVECTOR3(pBase->_41 + m_vAdPos.x, pBase->_42 + m_vAdPos.y, pBase->_43 - m_vAdPos.z);

		m_vNewLook.x = pBase->_41 + m_vAdLook.x;
		m_vNewLook.y = pBase->_42 + m_vAdLook.y;
		m_vNewLook.z = pBase->_43 + m_vAdLook.z;
		
		m_vNewUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		
		D3DXMATRIX  matRot;
		D3DXMatrixRotationYawPitchRoll(&matRot,
			m_vAngle.y, m_vAngle.x, m_vAngle.z);
		D3DXVec3TransformCoord(&m_vNewPos, &m_vNewPos, &matRot);
		D3DXVec3TransformCoord(&m_vNewLook, &m_vNewLook, &matRot);
		D3DXVec3TransformCoord(&m_vNewUp, &m_vNewUp, &matRot);
		break;
	}

	m_vPos = (m_vPos + m_vNewPos) / 2.0f;
	m_vLook = (m_vLook + m_vNewLook) / 2.0f;
	m_vUp = (m_vUp + m_vNewUp) / 2.0f;
	D3DXVec3Normalize(&m_vUp, &m_vUp);
}

// 反映
void CCamera::Draw(void)
{
	D3DXMatrixLookAtLH(&m_matView,
		&m_vPos,	// 視点
		&m_vLook,	// 注視点
		&m_vUp);	// 上方向
	CGraphics::GetDevice()->SetTransform(
		D3DTS_VIEW, &m_matView);
}

// エフェクト更新まとめ
void CCamera::UpdateEffect()
{
	switch(m_nEffectType)
	{
	case C_EFFECT_NORMAL:

		break;

	case C_EFFECT_ROUND:
		Round();
		break;
	}
}

// 回転
void CCamera::Round()
{
	m_vAngle.y += D3DXToRadian(1.0f);
}

