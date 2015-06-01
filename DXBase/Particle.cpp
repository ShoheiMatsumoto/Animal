#include "Particle.h"

#define DEFO_LIFE 300
CParticle::CParticle()
{
	m_Particle.vPos = D3DXVECTOR3(0,0,0);
	m_Particle.vSpd = D3DXVECTOR3(0,0,0);
	m_Particle.vAngle = D3DXVECTOR3(0,0,0);
	m_Particle.vSize = D3DXVECTOR3(0,0,0);

	m_Particle.BezierKey[4];		// ベジエ用制御点
	m_Particle.HermiteKey[2];		// エルミート用
	m_Particle.HermiteVecKey[2];	// エルミート用ベクトル
	m_Particle.nLife = DEFO_LIFE;		// 消滅までの時間
	m_Particle.nType = 0;		// 種類
}


CParticle::~CParticle(void)
{
}

void CParticle::Release()
{

}

