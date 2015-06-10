#pragma once
#include "factorybase.h"
#include "Test2D.h"
#include "TestBill.h"
#include "Moon.h"
#include "Player.h"
#include "MapPartsBase.h"

// �Q�[���Ɏg�p����I�u�W�F�N�g�̎��
enum
{
	WK_OBJ2D_TEST2D = 0,
	WK_OBJ2D_TEST0,
	WK_OBJ2D_TEST1,
	WK_OBJ2D_TEST2,
	WK_OBJ2D_TEST3,

	WK_OBJ2D_MAX,
};

enum
{
	WK_OBJ3D_MOON = 0,
	WK_OBJ3D_TESTBILL,
	WK_OBJ3D_PLAYER,
	WK_OBJ3D_MPSQUARE,
	WK_OBJ3D_MPRUP,
	WK_OBJ3D_MPRDOWN,

	WK_OBJ3D_MAX,
};

class CWkFactory :
	public CFactoryBase
{
protected:
	CTest2D		m_Test2D;
	CTestBill	m_TestBill;
	CMoon		m_Moon;
	CPlayer		m_Player;
	CMapPartsBase m_MapParts;

public:
	CWkFactory(void);
	virtual ~CWkFactory(void);

	// ��{�@�\
	void Initialize();		// ������
	static CWkFactory* Create();			// �����i���g�j
	void Release();			// ���
	void Request2D(int nID, int nTexID, D3DXVECTOR3 vPos);//�����˗�
	void Request3D(int nID, int nTexID, D3DXVECTOR3 vPos);//�����˗�

	// �g���@�\

};

