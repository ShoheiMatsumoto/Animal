// 音再生管理
#pragma once

// インクルード
#include "Sound.h"


enum
{
	SOUND_ONE,
	SOUND_LOOP,
};

// ゲーム全体で使う音の列挙
enum
{
	SOUND_TEST = 0,

	SOUND_MAX
};

// 音管理クラス
class CSoundMgr
{
protected:
	static CSoundMgr* m_pThis;		// 自身

	LPDIRECTSOUNDBUFFER8*   m_lppSound;			// サウンドセカンダリバッファ(動的に)

	int*		m_pnIDArray;		// 登録ID格納配列（動的）
	int			m_nEntryNum;		// 登録数
public:
	CSoundMgr(void);
	virtual ~CSoundMgr(void);

	// 基本
	CSoundMgr* Create(int nSoundNum);	// 生成
	void Initialize(int nSoundNum);
	virtual void Release();

	void UninitSound(void);								// サウンド関連後始末
	void InitBuffer(int nSoundNum);
	void LoadWave(void);
	void PlayWave(int nNum, int nLoop);
	// void UnInitWave(void);
	void RequestSound(int nID, int nLoop);		// 音再生のリクエスト

	// 拡張
	int	CheckRunEntry(int nID);
	void Entry(int nID, LPTSTR file);
	// void ReleaseEntry();
	int RequestEntryNum(int nID);		// 音楽が登録されている配列の添え字をもらう

};

