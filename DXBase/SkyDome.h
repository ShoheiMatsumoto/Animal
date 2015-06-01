#pragma once
#include "object3d.h"


class CSkyDome :
	public CObject3D
{
protected:
	D3DXVECTOR3 m_vCameraPos;		// カメラ座標
private:


public:
	CSkyDome(void);
	virtual ~CSkyDome(void);

	// 基本機能
	CObjBase* Create(int nID, int nTexNum);
	//virtual void Initialize(){};
	//virtual void Update(){};
	void Draw();
	//virtual void DrawSetUp();
	//virtual void DrawEnd();
	void Release();

	void InitializeSkyDome();
	void DrawAlpha(){};
};

