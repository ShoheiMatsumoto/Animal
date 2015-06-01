#include "Main.h"
#include "Sound.h"
#include "GameWnd.h"

// *************************
// グローバル変数
// *************************

CSound* CSound::m_pThis = new CSound();

CSound::CSound()
{

}

CSound::~CSound()
{
	
}

// 生成
CSound*	CSound::Create()
{
	CSound* pSound = new CSound();

	pSound->Initialize();

	m_pThis = pSound;

	return pSound;
}

// 初期処理
void CSound::Initialize()
{
	
}

// 解放
void CSound::Release()
{
	SAFE_RELEASE(m_pDirectSound);
	SAFE_DELETE(m_pThis);			// 自身の消去
}

//================
// 初期化
// ==============
HRESULT CSound::InitSound(HWND hWnd)
{
	// DirectSoundオブジェクトの作成
	if( FAILED(DirectSoundCreate8(NULL, &m_pDirectSound, NULL)))
		return E_FAIL;

	// 強調レベル設定
	if(FAILED(m_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
		return E_FAIL;

	return S_OK;
}

// ====================
// サウンドのロード
// ===================
LPDIRECTSOUNDBUFFER8 CSound::LoadSound(LPTSTR file)
{
	// MMIO = マルチメディア入出力、の略
	LPDIRECTSOUNDBUFFER  pBaseBuffer = NULL;// 曲データの総合バッファ
	LPDIRECTSOUNDBUFFER8 pBuffer = NULL;	// 曲データのバッファ
	DSBUFFERDESC buff;						// バッファ設定構造体

	HMMIO hMmio = NULL;						// MMIOハンドル
	MMIOINFO mmioInfo;						// マルチメディアデータ構造体

	MMRESULT mmRes;								// MM処理結果格納変数
	MMCKINFO riffChunk, formatChunk, dataChunk;	// チャンクデータ構造体
	DWORD size;									// データサイズ格納用
	WAVEFORMATEX pcm;							// 曲データフォーマット構造体

	LPVOID pBlock;					// セカンダリバッファのデータ書き込み先アドレス
	DWORD dwSize;					// セカンダリバッファのサイズ

	// 1.ハンドルを元にファイルを開く
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen(file, &mmioInfo, MMIO_READ);
	if(!hMmio)
		return NULL;

	// 2.ファイル解析① RIFFチャンク検索
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');				// 検索キーワード
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);	// キーワードを元に検索

	if(mmRes != MMSYSERR_NOERROR)// 見つからなかったら異常終了
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 3. ファイル解析②　フォーマットチャンク検索
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');			// 検索キーワード
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);// キーワードを元に検索

	if(mmRes != MMSYSERR_NOERROR)// 見つからなかったら異常終了
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	size = mmioRead(hMmio, (HPSTR)&pcm, formatChunk.cksize);			// 検索情報を元に読み込み

	if(size != formatChunk.cksize)// 正しく読み込めなかったら異常終了
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	mmioAscend(hMmio, &formatChunk, 0);

	// 4. ファイル解析④　データチャンク検索
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');							// 検索キーワード
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);			// キーワードを元に検索
	
	if(mmRes != MMSYSERR_NOERROR)			// 見つからなかったら異常終了
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	//5. データ読み込み
	char *pData = new char[dataChunk.cksize];				// 必要な領域の大きさを確保して
	size = mmioRead(hMmio, (HPSTR)pData, dataChunk.cksize);	// データを読み込む

	if(size != dataChunk.cksize)			// 正しく読み込めなかったら異常終了
	{
		delete[] pData;
		return NULL;
	}

	// 6. 曲を読み込む「セカンダリバッファ」を用意
	ZeroMemory(&buff, sizeof(DSBUFFERDESC));			// まず初期化
	buff.dwSize = sizeof(DSBUFFERDESC);					// そこから各種設定
	buff.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER;
	buff.dwBufferBytes = size;
	buff.lpwfxFormat = &pcm;

	// 総合バッファを作る
	if(FAILED(m_pDirectSound->CreateSoundBuffer(&buff, &pBaseBuffer, NULL)))
		return NULL;

	// サウンドバッファを取り出す
	if(FAILED(pBaseBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pBuffer)))
		return NULL;

	// 取り出したら総合バッファを捨てる
	pBaseBuffer->Release();

	// 7. 作られたセカンダリバッファにデータを転送
	// まずは書き込みできるようバッファをロック
	if(FAILED(pBuffer->Lock(0, 0, &pBlock, &dwSize, NULL, NULL, DSBLOCK_ENTIREBUFFER)))
		return NULL;

	memcpy(pBlock, pData, dwSize);		// データ転送
	delete[] pData;						// 下の読み込み領域を消す

	// バッファのロック解除
	pBuffer->Unlock(pBlock, dwSize, 0, 0);

	// セカンダリバッファを返してようやく完了
	return pBuffer;
}


//=======================================================================================
//	End of File
//==========================