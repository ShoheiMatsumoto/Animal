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

	// ��{�@�\
	void Initialize();		// ������
	static CWkFactory* Create();			// �����i���g�j
	void Release();			// ���
	void Request2D(int nID, D3DXVECTOR3 vPos);//�����˗�
	void Request3D(int nID, D3DXVECTOR3 vPos);//�����˗�

	// �g���@�\

};

