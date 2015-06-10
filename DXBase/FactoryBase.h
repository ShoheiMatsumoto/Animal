// �t�@�N�g���x�[�X�N���X�錾
#pragma once
#include "main.h"
#include "Test2D.h"
#include "TestBill.h"



// �Q�[���Ɏg�p����I�u�W�F�N�g�̎��
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

// �t�@�N�g���x�[�X�N���X
class CFactoryBase
{
protected:
	

public:
	CFactoryBase(void);
	virtual ~CFactoryBase(void);

	// ��{�@�\
	void Initialize();		// ������
	CFactoryBase* Create();			// �����i���g�j
	void Release();			// ���
	virtual void Request2D(int nID, int nTexID, D3DXVECTOR3 vPos);//�����˗�
	virtual void Request3D(int nID, int nTexID, D3DXVECTOR3 vPos);//�����˗�

	// �g���@�\

private:


};

