#pragma once

#include "billboard.h"
#include "MyMath.h"

// パーティクルステータス構造体
typedef struct 
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSpd;
	D3DXVECTOR3 vAngle;
	D3DXVECTOR3 vSize;

	KEY					BezierKey[4];		// ベジエ用制御点
	KEY					HermiteKey[2];		// エルミート用
	KEY					HermiteVecKey[2];	// エルミート用ベクトル

	int			nLife;		// 消滅までの時間
	int			nType;		// 種類

}MYPARTICLE;

class CParticle :
	public CBillboard
{
protected:
	MYPARTICLE m_Particle;

private:

public:
	CParticle(void);
	virtual ~CParticle(void);

	void Release();
	void InitializeParticle(){};
	virtual void Update(){};
};

