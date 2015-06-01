// カメラ クラス定義
#pragma once

#include <d3d9.h>	// DirectX Graphics 関連のヘッダ
#include <d3dx9.h>	// DirectX Graphics 関連のヘッダ

// カメラ種別
enum ECameraType {
	CT_FIXED = 0,		// 定点
	CT_FIRSTPERSON,		// 一人称
	CT_THIRDPERSON,		// 三人称

	MAX_CT				// カメラ種別数
};

// カメラ演出タイプ
enum
{
	C_EFFECT_NORMAL = 0,
	C_EFFECT_ROUND,

	C_EFFECT_ALL
};

// カメラ
class CCamera
{
public:
	CCamera(void);
	virtual ~CCamera(void);

private:
	static CCamera* m_pThis;

	int			m_nEffectType;

	D3DXVECTOR3	m_vPos;		// 視点座標
	D3DXVECTOR3	m_vLook;	// 注視座標
	D3DXVECTOR3	m_vUp;		// 上方向
	int			m_nType;	// カメラ種別
	D3DXVECTOR3	m_vNewPos;	// 次視点座標
	D3DXVECTOR3	m_vNewLook;	// 次注視座標
	D3DXVECTOR3	m_vNewUp;	// 次上方向
	D3DXVECTOR3 m_vAngle;	// 角度

	D3DXMATRIX  m_matView;	// ビューマトリックス

	D3DXVECTOR3 m_vAdPos;	// カメラ位置調整
	D3DXVECTOR3	m_vAdLook;

public:
	void Update(D3DXMATRIX* pBase);
	void Draw(void);
	D3DXVECTOR3& GetPos() {return m_vPos;};
	D3DXMATRIX GetMatView(){return m_matView;};

	// セッター
	void SetAdjustPos(D3DXVECTOR3 vPos){m_vAdPos = vPos;};		// カメラ座標セット
	void SetLookPos(D3DXVECTOR3 vPos){m_vAdLook = vPos;};
	void SetEffect(int nType){m_nEffectType = nType;};

	void UpdateEffect();		// エフェクト更新まとめ
	void Round();				// 回転

	// ゲッター
	static CCamera* GetThis(){return m_pThis;};
};

