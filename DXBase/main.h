// メインヘッダ
#pragma once


#include <d3d9.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION 0x0800		// DirectInputの警告防止
#include <dinput.h>					// DirectInput
#define DIRECTSOUND_VERSION	(0x0800)
#include <dsound.h>					// DirectSound
#include "define.h"



//-------- ライブラリのリンク（こう記述しておけば別途リンク設定が不要となる）
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib,"dsound")			// DirectSound
#pragma comment(lib, "dxguid.lib")



// EOF