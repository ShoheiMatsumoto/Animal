#pragma once
#include "factorybase.h"
#include "Test2D.h"
#include "TestBill.h"
#include "Moon.h"
#include "Player.h"
#include "MapPartsBase.h"

#include "Nezumaru.h"
#include "Ushimaru.h"
#include "Toramaru.h"
#include "Mimimaru.h"
#include "Tatsumaru.h"
#include "Hebimaru.h"
#include "Hosumaru.h"
#include "Mokomaru.h"
#include "Sarumaru.h"
#include "Torimaru.h"
#include "Inumaru.h"
#include "Urimaru.h"


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

	WK_OBJ3D_NEZU,
	WK_OBJ3D_USHI,
	WK_OBJ3D_TORA,
	WK_OBJ3D_MIMI,
	WK_OBJ3D_TATSU,
	WK_OBJ3D_HEBI,
	WK_OBJ3D_UMA,
	WK_OBJ3D_MERRY,
	WK_OBJ3D_SARU,
	WK_OBJ3D_TORI,
	WK_OBJ3D_INU,
	WK_OBJ3D_URI,

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

	CNezumaru	m_Nezu;
	CUshimaru	m_Ushi;
	CToramaru	m_Tora;
	CMimimaru	m_Mimi;
	CTatsumaru	m_Tatsu;
	CHebimaru	m_Hebi;
	CHosumaru	m_Hosu;
	CMokomaru	m_Moko;
	CSarumaru	m_Saru;
	CTorimaru	m_Tori;
	CInumaru	m_Inu;
	CUrimaru	m_Uri;


public:
	CWkFactory(void);
	virtual ~CWkFactory(void);

	// ��{�@�\
	void Initialize();		// ������
	static CWkFactory* Create();			// �����i���g�j
	void Release();			// ���
	CObjBase* Request2D(int nID, int nTexID, D3DXVECTOR3 vPos);//�����˗�
	CObjBase* Request3D(int nID, int nTexID, D3DXVECTOR3 vPos);//�����˗�
	CObjBase* Req3DSwtAnimaru(int nID, int nTexID, D3DXVECTOR3 vPos);
	
	// �g���@�\

};

