//=======================================================================================
//
//	  DirectInput クラス
//
//=======================================================================================
#include <windows.h>
#include <tchar.h>
#include "define.h"
#include "DInput.h"

//---------------------------------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------------------------------
CDInput::CDInput()
{
	m_pDI = NULL;
	m_pDIDeviceKeyboard = NULL;
	ZeroMemory(m_diKeyboardState, sizeof(m_diKeyboardState));
	m_pDIDeviceMouse = NULL;
	ZeroMemory(&m_diMouseState, sizeof(m_diMouseState));
	ZeroMemory(m_pDIDeviceJoystick, sizeof(m_pDIDeviceJoystick));
	ZeroMemory(m_diJoyState, sizeof(m_diJoyState));
	m_nJoystick = 0;
}

//---------------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------------
CDInput::~CDInput()
{
}

//---------------------------------------------------------------------------------------
//  DirectInput の初期化
//---------------------------------------------------------------------------------------
bool CDInput::Initialize(HWND hWnd)
{
	HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

	// DirectInputオブジェクトの作成
	if (FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL))) {
		MessageBox(hWnd, _T("DirectInput オブジェクトの作成に失敗しました！"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	//******** キーボード用
	// DirectInputDeviceオブジェクトの作成
	if (FAILED(m_pDI->CreateDevice(GUID_SysKeyboard, &m_pDIDeviceKeyboard, NULL))) {
		MessageBox(hWnd, _T("DirectInputDevice オブジェクトの作成に失敗しました！"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// データフォーマットの設定
	if (FAILED(m_pDIDeviceKeyboard->SetDataFormat(&c_dfDIKeyboard))) {
		MessageBox(hWnd, _T("DirectInput でデータフォーマットの設定に失敗しました！"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// 協調レベルの設定
	if (FAILED(m_pDIDeviceKeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))) {
		MessageBox(hWnd, _T("DirectInputで協調レベルの設定に失敗しました！"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// デバイスへの入力制御開始
	if (FAILED(m_pDIDeviceKeyboard->Acquire())) {
		MessageBox(hWnd, _T("DirectInput でデバイスへの入力制御開始に失敗しました！"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	//******** マウス用
	// DirectInputDeviceオブジェクトの作成
	if (FAILED(m_pDI->CreateDevice(GUID_SysMouse, &m_pDIDeviceMouse, NULL))) {
		MessageBox(hWnd, _T("DirectInputDevice オブジェクトの作成に失敗しました！"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// データフォーマットの設定
	if (FAILED(m_pDIDeviceMouse->SetDataFormat(&c_dfDIMouse))) {
		MessageBox(hWnd, _T("DirectInput でデータフォーマットの設定に失敗しました！"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// 協調レベルの設定
	if (FAILED(m_pDIDeviceMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))) {
		MessageBox(hWnd, _T("DirectInputで協調レベルの設定に失敗しました！"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// デバイスの設定
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize       = sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = DIPROPAXISMODE_REL;		// 相対値モードに設定
	m_pDIDeviceMouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph);

	// デバイスへの入力制御開始
	if (FAILED(m_pDIDeviceMouse->Acquire())) {
		MessageBox(hWnd, _T("DirectInput でデバイスへの入力制御開始に失敗しました！"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	//******** ジョイスティック用
	// DirectInputDeviceオブジェクトの作成
	m_nJoystick = 0;
	if (FAILED(m_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallback, this, DIEDFL_ATTACHEDONLY))) {
		MessageBox(hWnd, _T("DirectInputDevice オブジェクトの作成に失敗しました！"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}
	if (m_nJoystick == 0) {
//		MessageBox(hWnd, _T("ジョイスティックが見つかりません。"), _T("warning"), MB_OK | MB_ICONINFORMATION);
		return true;
	}

	for (int i = 0; i < m_nJoystick; i++) {
		// データフォーマットの設定
		if (FAILED(m_pDIDeviceJoystick[i]->SetDataFormat(&c_dfDIJoystick))) {
			MessageBox(hWnd, _T("DirectInput でデータフォーマットの設定に失敗しました！"), _T("error"), MB_OK | MB_ICONSTOP);
			return false;
		}

		// 協調レベルの設定
		if (FAILED(m_pDIDeviceJoystick[i]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))) {
			MessageBox(hWnd, _T("DirectInputで協調レベルの設定に失敗しました！"), _T("error"), MB_OK | MB_ICONSTOP);
			return false;
		}

		// デバイスの設定
		DIPROPRANGE diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwObj = DIJOFS_X;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_X;
		diprg.lMax       = JOY_MAX_X;
		m_pDIDeviceJoystick[i]->SetProperty(DIPROP_RANGE, &diprg.diph);	// Ｘ方向の範囲を指定
		diprg.diph.dwObj = DIJOFS_Y;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_Y;
		diprg.lMax       = JOY_MAX_Y;
		m_pDIDeviceJoystick[i]->SetProperty(DIPROP_RANGE, &diprg.diph);	// Ｙ方向の範囲を指定

		// デバイスへの入力制御開始
		if (FAILED(m_pDIDeviceJoystick[i]->Acquire())) {
//			MessageBox(hWnd, _T("DirectInput でデバイスへの入力制御開始に失敗しました！"), _T("error"), MB_OK | MB_ICONSTOP);
			return false;
		}
	}

	return true;
}

//---------------------------------------------------------------------------------------
//    ジョイスティック問い合わせ用コールバック関数
//---------------------------------------------------------------------------------------
BOOL CALLBACK CDInput::EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef)
{
	DIDEVCAPS	diDevCaps;			// デバイス情報
	HRESULT		hRes;
	CDInput*	pDI = (CDInput*)pvRef;

	// ジョイスティック用デバイスオブジェクトを作成
	hRes = pDI->m_pDI->CreateDevice(lpddi->guidInstance, &pDI->m_pDIDeviceJoystick[pDI->m_nJoystick], NULL);
	if (FAILED(hRes))
		return DIENUM_CONTINUE;		// 列挙を続ける
	// ジョイスティックの能力を調べる
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hRes = pDI->m_pDIDeviceJoystick[pDI->m_nJoystick]->GetCapabilities(&diDevCaps);
	if (FAILED(hRes)) {
		SAFE_RELEASE(pDI->m_pDIDeviceJoystick[pDI->m_nJoystick]);
		return DIENUM_CONTINUE;		// 列挙を続ける
	}
	if (++(pDI->m_nJoystick) < MAX_JOY)
		return DIENUM_CONTINUE;		// 列挙を続ける
	return DIENUM_STOP;		// 必要数揃ったので列挙を終了する
}

//---------------------------------------------------------------------------------------
//	DirectInput の終了
//---------------------------------------------------------------------------------------
void CDInput::Finalize(void)
{
	for (int i = 0; i < m_nJoystick; i++) {
		if (m_pDIDeviceJoystick[i])
			m_pDIDeviceJoystick[i]->Unacquire();	// 入力を終了
		SAFE_RELEASE(m_pDIDeviceJoystick[i]);		// DirectInputDevice8 オブジェクトの解放
	}
	if (m_pDIDeviceKeyboard)
		m_pDIDeviceKeyboard->Unacquire();	// 入力を終了
	SAFE_RELEASE(m_pDIDeviceKeyboard);		// DirectInputDevice8 オブジェクトの解放
	if (m_pDIDeviceMouse)
		m_pDIDeviceMouse->Unacquire();		// 入力を終了
	SAFE_RELEASE(m_pDIDeviceMouse);			// DirectInputDevice8 オブジェクトの解放
	SAFE_RELEASE(m_pDI);					// DirectInput8 オブジェクトの解放
}

//---------------------------------------------------------------------------------------
//	DirectInput キーボード／マウス／ジョイスティックからの入力
//---------------------------------------------------------------------------------------
void CDInput::GetCtrlInfo(void)
{
	HRESULT	hRes;

	if (m_pDIDeviceKeyboard) {
		m_pDIDeviceKeyboard->Acquire();		// 要求を出す
		// 現在のキーボードの状態を取得
		hRes = m_pDIDeviceKeyboard->GetDeviceState(256, &m_diKeyboardState);
		if (hRes == DIERR_INPUTLOST)
			m_pDIDeviceKeyboard->Acquire();	// 再度、要求を出す
	}
	if (m_pDIDeviceMouse) {
		m_pDIDeviceMouse->Acquire();		// 要求を出す
		// 現在のマウスの状態を取得
		hRes = m_pDIDeviceMouse->GetDeviceState(sizeof(m_diMouseState), &m_diMouseState);
		if (hRes == DIERR_INPUTLOST)
			m_pDIDeviceMouse->Acquire();	// 再度、要求を出す
	}
	for (int i = 0; i < m_nJoystick; i++) {
		m_pDIDeviceJoystick[i]->Acquire();		// 要求を出す
		m_pDIDeviceJoystick[i]->Poll();		// デバイス上のポーリング対象オブジェクトからデータを取得
		// 現在のジョイスティックの状態を取得
		hRes = m_pDIDeviceJoystick[i]->GetDeviceState(sizeof(m_diJoyState[0]), &m_diJoyState[i]);
		if (hRes == DIERR_INPUTLOST)
			m_pDIDeviceJoystick[i]->Acquire();	// 再度、要求を出す
	}
}

//=======================================================================================
//	End of File
//=======================================================================================