#pragma once
#include "factorybase.h"
#include "Test2D.h"
#include "TestBill.h"
#include "Moon.h"

enum
{
	WKI_OBJ2D_TEST2D = 0,
	WKI_OBJ2D_TEST0,
	WKI_OBJ2D_TEST1,
	WKI_OBJ2D_TEST2,
	WKI_OBJ2D_TEST3,

	WKI_OBJ2D_MAX,
};

enum
{
	WKI_OBJ3D_MOON = 0,
	WKI_OBJ3D_TESTBILL,

	WKI_OBJ3D_MAX,
};

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

	// ��{�@�\
	void Initialize();		// ������
	static CWkFactoryI* Create();			// �����i���g�j
	void Release();			// ���
	void Request2D(int nID, D3DXVECTOR3 vPos);//�����˗�
	void Request3D(int nID, D3DXVECTOR3 vPos);//�����˗�

	// �g���@�\

};

