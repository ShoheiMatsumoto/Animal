#pragma once
#include "factorybase.h"
#include "Test2D.h"
#include "TestBill.h"
#include "Moon.h"

class CWkFactory :
	public CFactoryBase
{
protected:
	CTest2D		m_Test2D;
	CTestBill	m_TestBill;
	CMoon		m_Moon;

public:
	CWkFactory(void);
	virtual ~CWkFactory(void);

	// 基本機能
	void Initialize();		// 初期化
	static CWkFactory* Create();			// 生成（自身）
	void Release();			// 解放
	void Request2D(int nID, D3DXVECTOR3 vPos);//生成依頼
	void Request3D(int nID, D3DXVECTOR3 vPos);//生成依頼

	// 拡張機能

};

