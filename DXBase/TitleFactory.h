// �^�C�g���t�@�N�g���N���X�錾
#pragma once
#include "factorybase.h"
#include "Test2D.h"
#include "TestBill.h"
#include "Moon.h"

// �^�C�g���t�@�N�g��
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

	// ��{�@�\
	void Initialize();		// ������
	static CTitleFactory* Create();			// �����i���g�j
	void Release();			// ���
	CObjBase* Request2D(int nID, int nTexID, D3DXVECTOR3 vPos);//�����˗�
	CObjBase* Request3D(int nID, int nTexID, D3DXVECTOR3 vPos);//�����˗�

	// �g���@�\
};

