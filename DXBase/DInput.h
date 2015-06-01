//=======================================================================================
//
//	  DirectInput クラス定義
//
//=======================================================================================
#pragma once

#include <dinput.h>						// DirectInput 関連のヘッダ
// #define DIRECTINPUT_VERSION 0x0900		// DirectX8 を明示

//-------- ジョイスティック関係
#define		MAX_JOY			4			// 最大認識接続数
#define		JOY_MIN_X		-128		// Ｘ軸最小値
#define		JOY_MAX_X		127			// Ｘ軸最大値
#define		JOY_MIN_Y		-128		// Ｙ軸最小値
#define		JOY_MAX_Y		127			// Ｙ軸最大値

class CDInput
{
private:
	LPDIRECTINPUT8			m_pDI;					// DirectInput8 オブジェクト
	LPDIRECTINPUTDEVICE8	m_pDIDeviceKeyboard;	// DirectInputDevice8 オブジェクト
	BYTE					m_diKeyboardState[256];	// キーボード情報取得バッファ
	LPDIRECTINPUTDEVICE8	m_pDIDeviceMouse;		// DirectInputDevice8 オブジェクト
	DIMOUSESTATE			m_diMouseState;			// マウス情報取得バッファ
	LPDIRECTINPUTDEVICE8	m_pDIDeviceJoystick[MAX_JOY];	// DirectInputDevice8 オブジェクト
	DIJOYSTATE				m_diJoyState[MAX_JOY];	// ジョイスティック情報取得バッファ
	int						m_nJoystick;			// ジョイスティック接続数

	static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);

public:
	CDInput();
	virtual ~CDInput();

	bool Initialize(HWND hWnd);
	void Finalize(void);
	void GetCtrlInfo(void);
	BYTE GetKey(int nIndex) {return m_diKeyboardState[nIndex];}
	DIMOUSESTATE& GetMouse() {return m_diMouseState;}
	int GetJoyCount() {return m_nJoystick;}
	DIJOYSTATE& GetJoy(int nIndex) {return m_diJoyState[nIndex];}
};

//=======================================================================================
//	End of File
//=======================================================================================