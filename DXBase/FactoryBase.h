// ファクトリベースクラス宣言
#pragma once
#include "main.h"
#include "Test2D.h"
#include "TestBill.h"



// ゲームに使用するオブジェクトの種類
enum
{
	OBJ2D_TEST2D = 0,
	OBJ2D_TEST0,
	OBJ2D_TEST1,
	OBJ2D_TEST2,
	OBJ2D_TEST3,

	OBJ2D_MAX,
};

enum
{
	OBJ3D_MOON = 0,
	OBJ3D_TESTBILL,

	OBJ3D_MAX,
};

// ファクトリベースクラス
class CFactoryBase
{
protected:
	

public:
	CFactoryBase(void);
	virtual ~CFactoryBase(void);

	// 基本機能
	void Initialize();		// 初期化
	CFactoryBase* Create();			// 生成（自身）
	void Release();			// 解放
	virtual void Request2D(int nID, D3DXVECTOR3 vPos);//生成依頼
	virtual void Request3D(int nID, D3DXVECTOR3 vPos);//生成依頼

	// 拡張機能

private:


};

