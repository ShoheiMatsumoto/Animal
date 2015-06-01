#pragma once

#include "object3d.h"
#include "Billboard.h"
#include "MyMath.h"
#include "PoliLine.h"

class CPoliLine3D :
	public CObject3D
{
protected:
	CPoliLine*	m_pPoliLine;		// ポリラインに使用するデータ群
	D3DXVECTOR3 m_vCameraVec[LINEPOINT_MAX];	// カメラへのベクトル
	D3DXVECTOR3 m_vDiffVec[LINEPOINT_MAX];		// 広げる方向

public:
	CPoliLine3D(void);
	virtual ~CPoliLine3D(void);

	CPoliLine3D* Create(D3DXVECTOR3 vInitPos, D3DXVECTOR3 vDestPos, float fWidth);
	void Initialize();

	virtual void Update(){};
	virtual void Draw(){};
	virtual void Release(){};
	//void DrawSetUp();
	//void DrawEnd();

	//void CalcLine();		// ライン計算
	//void CalcDirVec();		// 進行方向計算
	//void CalcCameraVec();	// カメラへのベクトル計算
	//void CalcDiffVec();		// 拡散方向計算
	//void CalcSquare();		// 四角計算

	//// セッター
	//void SetPosLine();

};

