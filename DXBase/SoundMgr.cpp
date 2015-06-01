#include "SoundMgr.h"

#define NULL_ID (9999)

CSoundMgr::CSoundMgr(void)
{
}


CSoundMgr::~CSoundMgr(void)
{
	//UnInitWave();
}

// 生成
CSoundMgr* CSoundMgr::Create(int nSoundNum)
{
	CSoundMgr* pSFB = new CSoundMgr();

	pSFB->Initialize(nSoundNum);

	return pSFB;
}

void CSoundMgr::Initialize(int nSoundNum)
{
	m_nEntryNum = nSoundNum;
	InitBuffer(nSoundNum);		// バッファの初期化
}

void CSoundMgr::Release()
{
	// バッファ解放
	for(int i = 0; i < m_nEntryNum; i++)
	{
		SAFE_RELEASE(m_lppSound[i]);
	}

	// 入れ物解放
	SAFE_DELETE_ARRAY(m_lppSound);
	SAFE_DELETE_ARRAY(m_pnIDArray);

	delete this;
}

void CSoundMgr::InitBuffer(int nSoundNum)
{
	// 変数宣言
	// 動的確保
	m_lppSound = new LPDIRECTSOUNDBUFFER8[nSoundNum];
	m_pnIDArray = new int[nSoundNum];
	// サウンドセカンダリバッファ初期化
	for(int i = 0; i < nSoundNum; i ++)
	{
		m_lppSound[i] = NULL;
		m_pnIDArray[i] = NULL_ID;		// 登録IDを初期化
	}

	m_nEntryNum = nSoundNum;		// 最大数を登録

}
void CSoundMgr::LoadWave(void)
{
	// wavファイルのロード
	//g_pSound[BGM_WAVE] = LoadSound(_T("SE/nami.wav"));

	//g_pSE_gogo = LoadSound(_T("gogo.wav"));
	//g_pSound[nNum] = LoadSound(_T("SE/%s", szFile));
}

void CSoundMgr::PlayWave(int nNum, int nLoop)
{
	m_lppSound[nNum]->Play(0, 0, nLoop);
}

//void CSoundFactryBase::UnInitWave(void)
//{
//	// 変数宣言
//
//	for(int i = 0; i < m_nEntryNum; i ++)
//	{
//		SAFE_RELEASE(m_lppSound[i]);
//	}
//
//	// 入れ物解放
//	SAFE_DELETE_ARRAY(m_lppSound);
//	SAFE_DELETE_ARRAY(m_pnIDArray);
//}

// 音再生のリクエスト
void CSoundMgr::RequestSound(int nID, int nLoop)
{
	// 登録されている添え字を取得
	int nEntry = RequestEntryNum(nID);

	// 種類ごとにswitch
	switch(nID)
	{
	case SOUND_TEST:
		PlayWave(nEntry, nLoop);
		break;

	default:

		break;
	}

}

// 登録されているかの走査
int	CSoundMgr::CheckRunEntry(int nID)
{
	// IDが登録済みか走査
	for(int i = 0; i < m_nEntryNum; i++)
	{
		// 登録してあったら
		if(m_pnIDArray[i] == nID)
		{
			return i;		// その配列の番号を返す
		}

		// 空の配列に行き当たる
		if(m_pnIDArray[i] == NULL_ID)
		{
			m_pnIDArray[i] = nID;		// 新規登録オブジェID
			return i;		// 新しく登録する配列の添え字を返す
		}
	}

	// エラー
	// リスト超過とか？
	return NULL_ID;
}

// 音楽データの登録(IDはシーンのヘッダではなく、ファクトリのヘッダに記入した方を記述)
void CSoundMgr::Entry(int nID, LPTSTR file)
{
	// 走査
	int nEntry = CheckRunEntry(nID);

	// ダイレクトサウンドへ読み込み要求
	// セカンダリバッファを取得
	m_lppSound[nEntry] = CSound::GetThis()->LoadSound(file);
}

// 音楽が登録されている配列の添え字をもらう
int CSoundMgr::RequestEntryNum(int nID)
{
	// IDが登録済みか走査
	for(int i = 0; i < m_nEntryNum; i++)
	{
		// 登録してあったら
		if(m_pnIDArray[i] == nID)
		{
			return i;		// その配列の番号を返す
		}

		// 空の配列に行き当たる
		if(m_pnIDArray[i] == NULL_ID)
			continue;
	}

	// エラー
	// 登録されてない
	return NULL_ID;
}

// eof