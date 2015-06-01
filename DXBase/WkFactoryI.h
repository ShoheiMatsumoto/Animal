#pragma once
#include "factorybase.h"
#include "Test2D.h"
#include "TestBill.h"
#include "Moon.h"

class CWkFactoryI :
	public CFactoryBase
{
protected:
	CTest2D		m_Test2D;
	CTestBill	m_TestBill;
	CMoon		m_Moon;

public:
	CWkFactoryI(void);
	virtual ~CWkFactoryI(void);

	// 基本機能
	void Initialize();		// 初期化
	static CWkFactoryI* Create();			// 生成（自身）
	void Release();			// 解放
	void Request2D(int nID, D3DXVECTOR3 vPos);//生成依頼
	void Request3D(int nID, D3DXVECTOR3 vPos);//生成依頼

	// 拡張機能

};

