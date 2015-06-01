//2Dオブジェクトクラス宣言
#pragma once
#include "ObjBase.h"



class CObject2D :
	public CObjBase
{
protected:
	//CObject2D* m_pNext;		// 次
	//CObject2D* m_pPrev;		// 前

	//int		m_nObjTypeID;	// オブジェ種類のID

	//D3DXVECTOR3 m_vPos;
	// 2D情報
	CBoard2D			m_Board;	// ２Dボード情報
public:
	CObject2D(void);
	CObject2D(int nID, int nTexNum);
	virtual ~CObject2D(void);

	//CObject2D* Create();
	CObject2D* Create(int nID, int nTexNum, D3DXVECTOR3 vPos);
	void Initilaize(){};
	virtual void Update();
	virtual void DrawSetUp();
	virtual void DrawEnd();
	virtual void Draw();
	virtual void Release(){};

	//void Hit(CObject3D* pObj){};

	


};

