#include "TexMgr.h"

#define NULL_ID (9999)

CTexMgr::CTexMgr(void)
{
}


CTexMgr::~CTexMgr(void)
{
}


// マネージャ生成
CTexMgr*		CTexMgr::Create(int nTexNum)
{
	CTexMgr* pMgr = new CTexMgr();

	pMgr->Initialize(nTexNum);

	return pMgr;
}

// 初期処理
void		CTexMgr::Initialize(int nTexNum)
{
	m_nEntryNum = nTexNum;		// 登録数
	

	InitList();		
}

// マネージャ解放
void		CTexMgr::Release()
{
	InitList();
	delete this;
}

// リスト初期化
void		CTexMgr::InitList()		
{
	// リスト生成
	m_ppTexList = (CImage **)malloc(sizeof(CImage) * m_nEntryNum);		// リスト初期化
	m_pnIDArray = (int *)malloc(sizeof(int) * m_nEntryNum);				// エントリーID入れ

	// リスト内初期化
	for(int i = 0; i < m_nEntryNum; i++)
	{
		m_ppTexList[i] = NULL;
		m_pnIDArray[i] = NULL_ID;
	}
}

// テクスチャエントリー
void		CTexMgr::Entry(int nID, LPCTSTR pszfName, int nPattern)
{
	// 使えるとこの走査
	int nEntry = CheckRunID(nID);

	if(nEntry != NULL_ID)
	{	// 登録済みでない場合
		// テクスチャ情報読み込み
		m_ppTexList[nEntry]		= CImage::Create(pszfName, nPattern);
	}
	

}

// ID登録走査
int			CTexMgr::CheckRunID(int nID)
{
	// IDが登録済みか走査
	for(int i = 0; i < m_nEntryNum; i++)
	{
		// 登録してあったら
		if(m_pnIDArray[i] == nID)
		{
			return NULL_ID;
		}

		// 空の配列に行き当たる
		if(m_pnIDArray[i] == NULL_ID)
		{
			m_pnIDArray[i] = nID;		// 新規登録ID
			return i;
		}
	}

	// エラー
	// リスト超過とか？
	// リストの追加
	m_nEntryNum ++;
	m_pnIDArray = (int *)realloc(m_pnIDArray, sizeof(int) * m_nEntryNum);
	m_pnIDArray[m_nEntryNum - 1] = nID;
	m_ppTexList = (CImage **)realloc(m_ppTexList, sizeof(CImage) * m_nEntryNum);
	
	return m_nEntryNum - 1;
}

// リストの解放
void		CTexMgr::ReleaseList()
{
	// リスト内解放
	for(int i = 0; i < m_nEntryNum; i++)
	{
		m_ppTexList[i]->Release();
	}

	// 入れ物解放
	free(m_ppTexList);
	free(m_pnIDArray);
}

// テクスチャデータの取得
CImage*		CTexMgr::GetTex(int nTexID)
{
	int nEntry = NULL_ID;
	// ID登録登録リスト走査
	for(int i = 0; i < m_nEntryNum; i++)
	{
		if(m_pnIDArray[i] == nTexID)
		{	// 一致
			nEntry = m_pnIDArray[i];
			break;
		}
	}

	if(nEntry == NULL_ID)
	{	// 該当なし
		// エラー処理

	}

	// 該当テクスチャデータを返す
	return m_ppTexList[nEntry];
}




// eof