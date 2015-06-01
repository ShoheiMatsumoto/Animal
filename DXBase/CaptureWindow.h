#pragma once
#include "Object3D.h"

class CCaptureWindow
{
private:
	static CCaptureWindow* m_pThis;
	LPDIRECT3DTEXTURE9 m_pRendTex; //レンダリング先のテクスチャ
	LPDIRECT3DSURFACE9 m_pRendTexSurface; //テクスチャから取得するサーフェース
	LPDIRECT3DSURFACE9 m_pRendTexZ; //テクスチャ用のZ バッファー
	LPDIRECT3DSURFACE9 m_pBackbuffer; //バックバッファー
	LPDIRECT3DSURFACE9 m_pBackZ;
 D3DVIEWPORT9 viewport1;

	bool m_bShot; 
public:
	CCaptureWindow(void);
	

	virtual ~CCaptureWindow(void);

	CCaptureWindow* Create();
	bool Initialize();

	bool ScreenShot();
	void		PreservedWindow();
	void		ChangeTex();
	void		Draw();
	void Release(){SAFE_RELEASE(m_pThis);};
	void SetScrShot(){m_bShot = true;};
	static CCaptureWindow* GetThis(){return m_pThis;};
};

