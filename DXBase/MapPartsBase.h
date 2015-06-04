// マップを構成するオブジェクトのベース宣言部
#pragma once

// インクルード
#include "billboard.h"

// パーツのグループ
enum
{
	MAPPARTS_SQUARE = 0,
	MAPPARTS_RUP,		// 右上がり
	MAPPARTS_RDOWN,		// 右下がり

	MAPPARTS_MAX
};

class CMapPartsBase :
	public CBillboard
{
protected:
	int		m_nPartsType;		// パーツのタイプ

public:
	CMapPartsBase(void);
	CMapPartsBase(int nID, int nTexNum, D3DXVECTOR3 vPos);
	virtual ~CMapPartsBase(void);

	// 基本
	CMapPartsBase*	Create(int nID, int nTexNum, D3DXVECTOR3 vPos, D3DXVECTOR3 vSize, int nPartsType);
	void		Initialize(int nPartsType, D3DXVECTOR3 vSize);
	void		Update();
	void		HitUpdate();
	void		Release();

	// 拡張
	int		GetPartsType(){return m_nPartsType;};
};

