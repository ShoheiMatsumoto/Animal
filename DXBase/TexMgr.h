#pragma once
#include "main.h"
#include "Image.h"

// テクスチャ管理クラス
class CTexMgr
{
public:
	CTexMgr(void);
	virtual ~CTexMgr(void);

	CTexMgr*		Create(int nTexNum);
	void		Initialize(int nTexNum);
	void		Release();		// 解放

	void		InitList();		// リスト初期化
	void		Entry(int nID, LPCTSTR pszfName, int nPattern);		// 登録
	int			CheckRunID(int nID);		// 登録走査

	void		ReleaseList();		// リストの解放
	
	// ゲッター
	CImage*		GetTex(int nTexID);

private:
	CImage**		m_ppTexList;		// 動的リスト
	int*			m_pnIDArray;		// ID格納配列（動的）
	int				m_nEntryNum;		// エントリー最大数
};

