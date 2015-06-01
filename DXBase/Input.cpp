#include "Input.h"

CInput* CInput::m_pThis = new CInput();

LPDIRECTINPUT8			CInput::m_pDInput = NULL;					// IDirectInput8インターフェースへのポインタ
LPDIRECTINPUTDEVICE8	CInput::m_pDIDevKeyboard = NULL;			// IDirectInputDevice8インターフェースへのポインタ(キーボード)
LPDIRECTINPUTDEVICE8	CInput::m_pDIDevMouse = NULL;				// IDirectInputDevice8インターフェースへのポインタ(マウス)
LPDIRECTINPUTDEVICE8	CInput::m_pDIDevJoypad[MAX_CONTROLER];		// IDirectInputDevice8インターフェースへのポインタ(ジョイパッド)
int						CInput::m_nNumCont = 0;						// コントローラの数


CInput::CInput(void)
{

}


CInput::~CInput(void)
{

}

//==============================
// 入力処理の初期化
//==============================
HRESULT CInput::InitInput(HINSTANCE hInst, HWND hWnd)
{
	// DirectInputオブジェクトの作成
	if(FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION,
					IID_IDirectInput8, (void**)&m_pDInput, NULL)))
		return E_FAIL;

	// キーボードの初期化
	if(FAILED(InitKeyboard(hWnd)))
		return E_FAIL;

	// マウスの初期化
	if(FAILED(InitMouse(hWnd)))
		return E_FAIL;

	// ゲームパッドの初期化
	if(FAILED(InitJoypad(hWnd)))
		return E_FAIL;

	return S_OK;
}

//==============================
// 入力処理の終了処理
//==============================
void CInput::UninitInput(void)
{
	// キーボードの終了処理
	UninitKeyboard();

	// マウスの終了処理
	UninitMouse();

	// ゲームパッドの終了処理
	UninitJoypad();

	// オブジェクトの後始末
	SAFE_RELEASE(m_pDInput);
}

//==============================
// 入力処理の更新処理
//==============================
void CInput::UpdateInput(void)
{
	// キーボードの更新
	UpdateKeyboard();

	// マウスの更新
	UpdateMouse();

	// ゲームパッドの更新
	UpdateJoypad();
}

//==============================
// キーボードの初期化
//==============================
HRESULT CInput::InitKeyboard(HWND hWnd)
{
	// デバイスオブジェクトを作成
	if(FAILED(m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevKeyboard, NULL)) || m_pDIDevKeyboard == NULL)
		return E_FAIL;

	// データフォーマットを設定
	if(FAILED(m_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
		return E_FAIL;

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if(FAILED(m_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		return E_FAIL;

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDIDevKeyboard->Acquire();

	return S_OK;
}

//==============================
// キーボードの終了処理
//==============================
void CInput::UninitKeyboard(void)
{
	SAFE_RELEASE(m_pDIDevKeyboard);
}

//==============================
// キーボードの更新処理
//==============================
void CInput::UpdateKeyboard(void)
{
	// デバイスからデータを取得。失敗したらキーボードへのアクセス権を取得
	if(FAILED(m_pDIDevKeyboard->GetDeviceState(sizeof(m_KeyState), m_KeyState)))
		m_pDIDevKeyboard->Acquire();

	// トリガーとリリース用データ取得
	for(DWORD dwCnt = 0; dwCnt < 256; dwCnt ++)
	{
		m_KeyStateTrg[dwCnt] = (m_KeyStatePrev[dwCnt] ^ m_KeyState[dwCnt]) & m_KeyState[dwCnt];
		m_KeyStateRls[dwCnt] = (m_KeyStatePrev[dwCnt] ^ m_KeyState[dwCnt]) & m_KeyStatePrev[dwCnt];
		m_KeyStatePrev[dwCnt] = m_KeyState[dwCnt];
	}

	// 直前キー情報のバックアップ
	//memcpy(m_KeyStatePrev, m_KeyState, sizeof(m_KeyState));


}

// キーボードの入力判定
bool CInput::GetKey(KEY_TYPE eKeyType, DWORD dwKey)
{
	switch(eKeyType)
	{
	case KEY_PRS:		// プレス
		if(m_KeyState[dwKey] & 0x80)
			return true;
		break;

	case KEY_TRG:		// トリガー
		if(m_KeyStateTrg[dwKey] & 0x80)
			return true;
		break;

	case KEY_RLS:		// リリース
		if(m_KeyStateRls[dwKey] & 0x80)
			return true;
		break;
	}
	return false;
}

//==============================
// マウスの初期化
//==============================
HRESULT CInput::InitMouse(HWND hWnd)
{
	// デバイスオブジェクトを作成
	if(FAILED(m_pDInput->CreateDevice(GUID_SysMouse, &m_pDIDevMouse, NULL)) || m_pDIDevMouse == NULL)
		return E_FAIL;

	// データフォーマットを設定
	if(FAILED(m_pDIDevMouse->SetDataFormat(&c_dfDIMouse2)))
		return E_FAIL;

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if(FAILED(m_pDIDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		return E_FAIL;

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDIDevMouse->Acquire();

	return S_OK;
}

//==============================
// マウスの終了処理
//==============================
void CInput::UninitMouse(void)
{
	SAFE_RELEASE(m_pDIDevMouse);
}

//==============================
// マウスの更新処理
//==============================
void CInput::UpdateMouse(void)
{
	// 直前マウス情報のバックアップ
	m_mouseStatePrev = m_mouseState;

	// デバイスからデータを取得。失敗したらマウスへのアクセス権を取得
	if(FAILED(m_pDIDevMouse->GetDeviceState(sizeof(m_mouseState), &m_mouseState)))
		m_pDIDevMouse->Acquire();
}

//===============================
// マウスの座標取得(2D）
//===============================
void CInput::SetPosCursor(POINT pt)
{
	m_mouseState.lX = pt.x;
	m_mouseState.lY = pt.y;
}

//==============================
// ジョイパッドの初期化
//==============================
HRESULT CInput::InitJoypad(HWND hWnd)
{
	int nLoop;

	// 初期化
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
		m_pDIDevJoypad[nLoop] = NULL;

	// デバイスオブジェクトを作成(接続されているジョイパッドを列挙する)
	if(FAILED(m_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallback, NULL, DIEDFL_ATTACHEDONLY)))
		return E_FAIL;

	// ジョイパッドの数だけ処理
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
	{
		// ジョイパッドがない場合はすっ飛ばす
		if(m_pDIDevJoypad[nLoop] == NULL)
			continue;

		// データフォーマットの設定
		if(FAILED(m_pDIDevJoypad[nLoop]->SetDataFormat(&c_dfDIJoystick)))
			return E_FAIL;

		// 協調レベルの設定
		if(FAILED(m_pDIDevJoypad[nLoop]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
			return E_FAIL;

		// デバイスへの入力制御開始
		m_pDIDevJoypad[nLoop]->Acquire();	
	}

	return S_OK;
}

//==============================
// ジョイパッド問い合わせ用コールバック関数
//==============================
BOOL CALLBACK CInput::EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef)
{
	DIDEVCAPS	diDevCaps;			// デバイス情報

	// ジョイパッド用デバイスオブジェクトを作成
	if(FAILED(m_pDInput->CreateDevice(lpddi->guidInstance, &m_pDIDevJoypad[m_nNumCont], NULL)))
		return DIENUM_CONTINUE;		// 列挙を続ける

	// ジョイパッドの能力を調べる
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	if(FAILED(m_pDIDevJoypad[m_nNumCont]->GetCapabilities(&diDevCaps)))
	{
		if(m_pDIDevJoypad[m_nNumCont])
			m_pDIDevJoypad[m_nNumCont]->Release();
		m_pDIDevJoypad[m_nNumCont] = NULL;
		return DIENUM_CONTINUE;		// 列挙を続ける
	}

	// 規定数に達したら終了
	m_nNumCont++;
	if(m_nNumCont == MAX_CONTROLER)
		return DIENUM_STOP;		// 列挙を終了する
	else
		return DIENUM_CONTINUE;		// 列挙を続ける
}

//==============================
// ジョイパッドの終了処理
//==============================
void CInput::UninitJoypad(void)
{
	for(int nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
		SAFE_RELEASE(m_pDIDevJoypad[nLoop]);
}

//==============================
// ジョイパッドの更新処理
//==============================
void CInput::UpdateJoypad(void)
{
	int nLoop;
	
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
	{
		// 直前ジョイパッド情報のバックアップ
		m_joyStatePrev[nLoop] = m_joyState[nLoop];

		if(m_pDIDevJoypad[nLoop])
		{
			// デバイスからデータを取得
			if(FAILED(m_pDIDevJoypad[nLoop]->GetDeviceState(sizeof(DIJOYSTATE), &m_joyState[nLoop])))
				m_pDIDevJoypad[nLoop]->Acquire();
		}
	}
}


//=================================================================
// EOF
//===================================================================
