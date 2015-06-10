#pragma once
#include "factorybase.h"
#include "Test2D.h"
#include "TestBill.h"
#include "Moon.h"
#include "Player.h"
#include "MapPartsBase.h"

// ゲームに使用するオブジェクトの種類
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

	// 基本機能
	void Initialize();		// 初期化
	static CWkFactory* Create();			// 生成（自身）
	void Release();			// 解放
	void Request2D(int nID, int nTexID, D3DXVECTOR3 vPos);//生成依頼
	void Request3D(int nID, int nTexID, D3DXVECTOR3 vPos);//生成依頼

	// 拡張機能

};

