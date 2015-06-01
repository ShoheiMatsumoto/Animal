#pragma once
#include "object2d.h"
#include "PoliLine.h"

class CPoliLine2D :
	public CObject2D
{
protected:
	CPoliLine* m_pPoliLine;

public:
	CPoliLine2D(void);
	virtual ~CPoliLine2D(void);

	CPoliLine2D* Create(D3DXVECTOR3 vInitPos, D3DXVECTOR3 vDestPos, float fWidth);
	void Initialize();
	void Release();
	//void Update();
	//void Draw();
	//void DrawSetUp();
	//void DrawEnd();

	//void CalcLine();		// ライン計算
	//void CalcDirVec();		// 進行方向計算
	//void CalcCameraVec();	// カメラへのベクトル計算
	//void CalcDiffVec();		// 拡散方向計算
	//void CalcSquare();		// 四角計算

	// セッター
	//void SetPosLine();

};

