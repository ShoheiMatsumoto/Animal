// 音再生クラス宣言
#pragma once
#include "main.h"

// SE用列挙
typedef enum
{
	SE_TEST = 0,
	
	SE_MAX
};


// BGM用列挙
typedef enum
{
	BGM_TEST = 0,
	
	BGM_MAX
};

#define PLAYSOUND_MAX (20)		// 同時再生SE数

class CSound
{
protected:
	static CSound*					m_pThis;	// こいつ自身
	// int						m_EntryNum;		// 登録数
	
	LPDIRECTSOUND8				m_pDirectSound;

public:
	CSound(void);
	virtual ~CSound();

	// 基本
	CSound*				Create();
	void				Initialize();
	virtual void		Release();

	HRESULT InitSound(HWND hWnd);				// サウンド関連初期化
	LPDIRECTSOUNDBUFFER8 LoadSound(LPTSTR file);		// サウンドのロード

	
	// 拡張
	static CSound*		GetThis(){return m_pThis;};
};

//=======================================================================================
//	End of File
//=======

