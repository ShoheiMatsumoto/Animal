// タイトルファクトリクラス宣言
#pragma once
#include "factorybase.h"
#include "Test2D.h"
#include "TestBill.h"
#include "Moon.h"

// タイトルファクトリ
class CTitleFactory :
	public CFactoryBase
{
protected:
	CTest2D		m_Test2D;
	CTestBill	m_TestBill;
	CMoon		m_Moon;

public:
	CTitleFactory(void);
	virtual ~CTitleFactory(void);

	// 基本機能
	void Initialize();		// 初期化
	static CTitleFactory* Create();			// 生成（自身）
	void Release();			// 解放
	CObjBase* Request2D(int nID, int nTexID, D3DXVECTOR3 vPos);//生成依頼
	CObjBase* Request3D(int nID, int nTexID, D3DXVECTOR3 vPos);//生成依頼

	// 拡張機能
};

