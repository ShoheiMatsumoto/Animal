// 入力クラス定義
#pragma once
//#define DIRECTINPUT_VERSION 0x0900

// インクルード

#include "main.h"

//******************************
// マクロ定義
///*****************************
#define MAX_CONTROLER		(2)				// コントローラ最大数(使う数に応じて変更すること)

//******************************
// プロトタイプ・extern宣言
//******************************
#include "define.h"

// 列挙
typedef enum
{
	KEY_PRS = 0,
	KEY_TRG,
	KEY_RLS,

	KEY_MAX
}KEY_TYPE;



// 入力クラス
class CInput
{
public:
	CInput(void);
	~CInput(void);

	static CInput* GetThis(){return m_pThis;}

	HRESULT InitInput(HINSTANCE hInst, HWND hWnd);			// Input初期化
	void UninitInput(void);									// Input後始末
	void UpdateInput(void);									// 入力情報更新

	// キーボード関連
	HRESULT InitKeyboard(HWND hWnd);
	void UninitKeyboard(void);
	void UpdateKeyboard(void);
	bool GetKey(KEY_TYPE eKeyType, DWORD dwKey);		// キーボード入力判定

	// マウス関連
	HRESULT InitMouse(HWND hWnd);
	void UninitMouse(void);
	void UpdateMouse(void);
	void SetPosCursor(POINT pt);		// 座標取得

	// ジョイパッド関連
	HRESULT InitJoypad(HWND hWnd);
	void UninitJoypad(void);
	void UpdateJoypad(void);
	
	static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);

private:
	static CInput*					m_pThis;				// 自分自身

	static LPDIRECTINPUT8			m_pDInput;				// IDirectInput8インターフェースへのポインタ
	
	// キーボード関連
	static LPDIRECTINPUTDEVICE8		m_pDIDevKeyboard;		// IDirectInputDevice8インターフェースへのポインタ(キーボード)
	BYTE				m_KeyState[256];					// キーボード情報配列
	BYTE				m_KeyStatePrev[256];				// キーボード情報配列 (直前)
	BYTE				m_KeyStateTrg[256];		// トリガー用
	BYTE				m_KeyStateRls[256];		// リリース用

	// マウス関連
	static LPDIRECTINPUTDEVICE8		m_pDIDevMouse;			// IDirectInputDevice8インターフェースへのポインタ(マウス)
	DIMOUSESTATE2		m_mouseState;						// マウス情報配列
	DIMOUSESTATE2		m_mouseStatePrev;					// マウス情報配列 (直前)
		
	// ジョイパッド関連
	static LPDIRECTINPUTDEVICE8		m_pDIDevJoypad[MAX_CONTROLER];// IDirectInputDevice8インターフェースへのポインタ(ジョイパッド)
	DIJOYSTATE			m_joyState[MAX_CONTROLER];			// ジョイパッド情報配列
	DIJOYSTATE			m_joyStatePrev[MAX_CONTROLER];		// ジョイパッド情報配列 (直前)
	static int						m_nNumCont;				// コントローラの数

	
	
	




};

#define GETINPUT (CInput::GetThis())
