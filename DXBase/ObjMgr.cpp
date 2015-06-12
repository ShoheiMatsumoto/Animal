#include "ObjMgr.h"
#include "MySort.h"
#include "SceneBase.h"

#define NULL_ID (9999)

CObjMgr::CObjMgr(void)
{
	
}


CObjMgr::~CObjMgr(void)
{
}

// �I�u�W�F�}�l�[�W������
CObjMgr* CObjMgr::Create()
{
	CObjMgr* pMgr = new CObjMgr();

	pMgr->Initialize();

	return pMgr;
	
}

void CObjMgr::Initialize()
{
	m_nCurDrawType = DRAWTYPE_MAX;
	m_bResetDrawList = false;


	// ���X�g�ɋ�̃I�u�W�F�N�g������Ă�
	InitList();
}

// ���I���X�g�̏����ݒ�
void CObjMgr::InitList()
{
	// 2D******************************************************
	// ��̃I�u�W�F�N�g�𐶐�
	for(int i = 0; i < OBJ2DGROUP_MAX; i ++)
	{
		m_pObjListTop2D[i] = (CObject2D*)m_pObj->Create();
		m_pObjListTop2D[i]->SetNext(NULL);		// �g�b�v�̎���NULL�N���A
		m_pObjListTop2D[i]->SetPrev(NULL);		// �g�b�v�̑O��NULL�N���A
	}

	// �`��p���ꕨ������
	for(int i = 0; i < DRAWOBJ_MAX; i++)
	{
		m_pObj2DDraw[i] = NULL;
	}

	//***********************************************************

	// 3D
	// ��̃I�u�W�F�N�g�𐶐�
	for(int i = 0; i < OBJ3DGROUP_MAX; i ++)
	{
		m_pObjListTop3D[i] = (CObject3D*)m_pObj->Create();
		m_pObjListTop3D[i]->SetNext(NULL);		// �g�b�v�̎���NULL�N���A
		m_pObjListTop3D[i]->SetPrev(NULL);		// �g�b�v�̑O��NULL�N���A
	}

}

// 2D�p�̕`�惊�X�g�̃Z�b�g
void CObjMgr::SetDrawList(CObject2D* pObj)
{
	for(int i = 0; i < DRAWOBJ_MAX; i++)
	{
		// �󂢂Ă�ꏊ��T��
		if(!m_pObj2DDraw[i])
		{
			m_pObj2DDraw[i] = pObj;
			break;
		}
	}
}

// �I�u�W�F���������ۂ̋󂫂̑O�l��
// �I�u�W�F�̏������������ۂɑ���
void CObjMgr::ResetDrawList()
{
	if(!m_bResetDrawList)
		return;
	// 
	for(int i = 0; i < DRAWOBJ_MAX; i++)
	{
		// �󂢂Ă�ꏊ
		if(!m_pObj2DDraw[i])
		{
			for(int j = i; j < DRAWOBJ_MAX; j++)
			{
				// �o�^����Ă鏊��T��
				if(m_pObj2DDraw[j])
				{
					// ���炵�Ă���
					for(int k = 0; k < DRAWOBJ_MAX - j; k++)
					{
						// NULL�Ȃ�
						if(!m_pObj2DDraw[j + k])
						{
							i = i + k;
							j = j + k;
							break;
						}

						m_pObj2DDraw[i + k] = m_pObj2DDraw[j + k];
					}
				}

				// ������Ȃ�����
				if(j >= DRAWOBJ_MAX - 1)
					i = DRAWOBJ_MAX;		// i�̃��[�v�𔲂���悤��
			}
		}
	}

	// ���Z�b�g�t���O�߂�
	m_bResetDrawList = false;
}

// �`��z��̃\�[�g 
void CObjMgr::DrawSort()
{
	// 
	CMySort Sort;
	SortData* Data;
	int nCnt = 0;

	// �\�[�g�p�f�[�^�쐬
	for(nCnt; nCnt < DRAWOBJ_MAX; nCnt ++)
	{
		if(!m_pObj2DDraw[nCnt])
			break;
	}
	
	Data = new SortData[nCnt];

	// �ڂ�
	for(int i = 0; i < nCnt; i++)
	{
		Data[i].nArrayNum = i;
		Data[i].fData = m_pObj2DDraw[i]->GetPos().z;	// Z�̒l�Ń\�[�g
	}

	// �\�[�g
	Sort.QuiqSort(Data, nCnt);

	// ���ג���
	CObject2D* pArray[DRAWOBJ_MAX];
	for(int i = 0; i < nCnt; i++)
	{
		pArray[i] = m_pObj2DDraw[Data[i].nArrayNum];
	}

	for(int i = 0; i < nCnt; i++)
	{
		m_pObj2DDraw[i] = pArray[i];
	}

	// ���
	SAFE_DELETE_ARRAY(Data);
}

// 2DObj�̍X�V
void CObjMgr::Update2D()
{
	// 2D
	CObjBase* pObj = NULL;

	// ������
	for(int i = 0; i < OBJ2DGROUP_MAX; i ++)
	{
		// �c�����ւ̍X�V
		pObj = m_pObjListTop2D[i];		// ���X�g�̃g�b�v����

		while(pObj)
		{
			if(pObj->GetbUse())
			{
				pObj->SetPostoOldPos();
				pObj->Update();				// �X�V
				pObj = pObj->GetNext();		// ���̃I�u�W�F���擾
			}
		}
	}
}

// 3DObj�̍X�V
void CObjMgr::Update3D()
{
	// 3D
	CObjBase* pObj = NULL;

	// ������
	for(int i = 0; i < OBJ3DGROUP_MAX; i ++)
	{
		// �c����
		pObj = m_pObjListTop3D[i];		// ���X�g�̃g�b�v����

		while(pObj)
		{
			if(pObj->GetbUse())
			{
				pObj->SetPostoOldPos();		// �����W�X�V
				pObj->Update();				// �X�V
			}
			pObj = pObj->GetNext();		// ���̃I�u�W�F���擾
			
		}
	}
}

// �SOBJ�̍X�V
void CObjMgr::AllUpdate()
{
	Update2D();
	Update3D();

	// ��������
	DeleteObj();		

	// �`��p���X�g���Z�b�g
	ResetDrawList();

	// �`��p���X�g�̃\�[�g
	DrawSort();
}

// 2DObj�̕`��
void CObjMgr::Draw2D()
{
	// 2D
	CObjBase* pObj = NULL;
	int nDrawType = m_nCurDrawType;
	int nDrawTypeNext = m_nCurDrawType;

	// �z������ɕ`��
	for(int i = 0; m_pObj2DDraw[i]; i ++)
	{
		// �`��^�C�v�擾
		nDrawType = m_pObj2DDraw[i]->GetDrawType();

		// �������
		if(m_nCurDrawType != nDrawType)
		{
			m_pObj2DDraw[i]->DrawSetUp();
			m_nCurDrawType = nDrawType;		// ���ݕ`��^�C�v�̕ύX
		}
	
		if(m_pObj2DDraw[i]->GetbUse())
			m_pObj2DDraw[i]->Draw();

		// ��������Ȃ�
		if(m_pObj2DDraw[i + 1])
		{
			// ���̂��^�C�v���Ⴄ�Ȃ�
			if(m_pObj2DDraw[i + 1]->GetDrawType() != m_nCurDrawType)
			{
				m_pObj2DDraw[i]->DrawEnd();
			}
		}
		else
		{		// ���������Ȃ�I���
			m_pObj2DDraw[i]->DrawEnd();
			m_nCurDrawType = DRAWTYPE_MAX;		// ���Z�b�g
		}
		
	}

	
}

// 3DObj�̕`��
void CObjMgr::Draw3D()
{
	// 3D
	CObject3D* pObj = NULL;
	int nDrawType = m_nCurDrawType;
	int nDrawTypeNext = m_nCurDrawType;
	int nPrevVP = 9999;
	int nCurVP;

	// ������
	for(int i = 0; i < OBJ3DGROUP_MAX; i ++)
	{
		// �c����
		pObj = m_pObjListTop3D[i];		// ���X�g�̃g�b�v����

		while(pObj)
		{
			// �r���[�v���W�F�N�V�����^�C�v
			nCurVP = pObj->GetViewType();// �擾
			if(nPrevVP != nCurVP)
			{
				switch(nCurVP)
				{
				case VIEWPROJ_PERS:
					CSceneBase::GetCurScene()->GetGraph()->SetProjection(PROJ_PERS);
					break;

				case VIEWPROJ_ORT:
					CSceneBase::GetCurScene()->GetGraph()->SetProjection(PROJ_ORT);
					break;
				}
				nPrevVP = nCurVP;
			}

			// �`��^�C�v�擾
			nDrawType = pObj->GetDrawType();

			// �������
			if(m_nCurDrawType != nDrawType)
			{
				pObj->DrawSetUp();
				m_nCurDrawType = nDrawType;		// ���ݕ`��^�C�v�̕ύX
			}

			if(pObj->GetbUse())
				pObj->Draw();				// �`��
			
			// ��������Ȃ�
			if(pObj->GetNext())
			{
				// ���̂��^�C�v���Ⴄ�Ȃ�
				if(pObj->GetNext()->GetDrawType() != m_nCurDrawType)
				{
					pObj->DrawEnd();
				}
			}
			else
			{		// ���������Ȃ�I���
				pObj->DrawEnd();
				m_nCurDrawType = DRAWTYPE_MAX;		// ���Z�b�g
			}

			pObj = (CObject3D *)pObj->GetNext();		// ���̃I�u�W�F���擾
		}
	}
}

// �SOBJ�̕`��
void CObjMgr::AllDraw()
{
	Draw3D();
	Draw2D();
}

// ���
void CObjMgr::Release()
{
	// ���X�g�̉��
	
	// ���X�g���I�u�W�F�S�J��
	ReleaseList();

	delete this;
}

// �I�u�W�F�o�^
void CObjMgr::EntryObj2D(CObjBase* pObj)
{
	// �o�^ID����
	int nEntry = pObj->GetGroupID();		// �O���[�vID�擾

	// ���X�g�ɓo�^(�A��)
	if(m_pObjListTop2D[nEntry]->GetNext())
		m_pObjListTop2D[nEntry]->GetNext()->SetPrev(pObj);	// �g�b�v��Next�̃I�u�W�F��Prev�ɐ�������I�u�W�F��o�^
	pObj->SetNext(m_pObjListTop2D[nEntry]->GetNext());		// �g�b�v��Next�𐶐�����I�u�W�F��Next�ɂ���
	pObj->SetPrev(m_pObjListTop2D[nEntry]);				// ��������I�u�W�F�̑O���g�b�v�ɐݒ�
	m_pObjListTop2D[nEntry]->SetNext(pObj);		// �g�b�v��Next�ɐ�������I�u�W�F��o�^

	// �`��p�̃��X�g�ɓo�^
	SetDrawList((CObject2D*)pObj);
}

// �I�u�W�F�o�^
void CObjMgr::EntryObj3D(CObjBase* pObj)
{
	// �o�^ID����
	int nEntry = pObj->GetGroupID();

	// ���X�g�ɓo�^(�A��)
	if(m_pObjListTop3D[nEntry]->GetNext())
		m_pObjListTop3D[nEntry]->GetNext()->SetPrev(pObj);	// �g�b�v��Next�̃I�u�W�F��Prev�ɐ�������I�u�W�F��o�^
	pObj->SetNext(m_pObjListTop3D[nEntry]->GetNext());		// �g�b�v��Next�𐶐�����I�u�W�F��Next�ɂ���
	pObj->SetPrev(m_pObjListTop3D[nEntry]);				// ��������I�u�W�F�̑O���g�b�v�ɐݒ�
	m_pObjListTop3D[nEntry]->SetNext(pObj);		// �g�b�v��Next�ɐ�������I�u�W�F��o�^
}

// �I�u�W�F����
void CObjMgr::DeleteObj()
{
	DeleteObj2D();
	DeleteObj3D();
}

void CObjMgr::DeleteObj2D()
{
	CObject2D* pObj;
	CObject2D* pNext;

	for(int i = 0; i < OBJ2DGROUP_MAX; i ++)
	{
		pObj = m_pObjListTop2D[i];

		while(pObj)
		{
			// ���Ńt���O�������Ă���
			if(pObj->CheckbeDelete())
			{
				pNext = (CObject2D*)pObj->GetNext();		// ��Ɉڂ�
				SAFE_DELETE(pObj);		// ����
				pObj = pNext;			// ����
				continue;
			}
			pObj = (CObject2D*)pObj->GetNext();	// ����
		}
	}
}

void CObjMgr::DeleteObj3D()
{
	CObject3D* pObj;
	CObject3D* pNext;

	for(int i = 0; i < OBJ3DGROUP_MAX; i ++)
	{
		pObj = m_pObjListTop3D[i];

		while(pObj)
		{
			// ���Ńt���O�������Ă���
			if(pObj->CheckbeDelete())
			{
				pNext = (CObject3D*)pObj->GetNext();		// ��Ɉڂ�
				SAFE_DELETE(pObj);		// ����
				pObj = pNext;			// ����
				continue;
			}
			pObj = (CObject3D*)pObj->GetNext();	// ����
		}
	}
}

// ���X�g�̉��
void CObjMgr::ReleaseList()
{
	ReleaseList2D();
	ReleaseList3D();
}

// ���X�g�Ɏc���Ă�I�u�W�F�̑S����
void CObjMgr::ReleaseList2D()
{
	CObject2D* pObj;
	CObject2D* pNext;

	for(int i = 0; i < OBJ2DGROUP_MAX; i ++)
	{
		pObj = m_pObjListTop2D[i];

		while(pObj)
		{
			
			pNext = (CObject2D*)pObj->GetNext();		// ��Ɉڂ�
			SAFE_DELETE(pObj);		// ����
			pObj = pNext;			// ����
		}
	}
}

void CObjMgr::ReleaseList3D()
{
	CObject3D* pObj;
	CObject3D* pNext;

	for(int i = 0; i < OBJ3DGROUP_MAX; i ++)
	{
		pObj = m_pObjListTop3D[i];

		while(pObj)
		{
			
			pNext = (CObject3D*)pObj->GetNext();		// ��Ɉڂ�
			SAFE_DELETE(pObj);		// ����
			pObj = pNext;			// ����
		}
	}
}

// ���X�g�̃g�b�v�����炤
CObject2D*	CObjMgr::GetListTop2D(int nGroupID)
{
	return (CObject2D*)m_pObjListTop2D[nGroupID]->GetNext();
}

// ���X�g�̃g�b�v�����炤
CObject3D*	CObjMgr::GetListTop3D(int nGroupID)
{
	
	return (CObject3D*)m_pObjListTop3D[nGroupID]->GetNext();
}

// �ʂ̃I�u�W�F�N�g���擾
CObjBase*	CObjMgr::GetIdentifObj2D(int nGID, int nTID, int nIID)
{
	return NULL;
}

// �ʂ̃I�u�W�F�N�g���擾
CObjBase*	CObjMgr::GetIdentifObj3D(int nGID, int nTID, int nIID)
{
	CObjBase* pObj;
	pObj = m_pObjListTop3D[nGID]->GetNext();		// �O���[�v�̃g�b�v�����炤

	while(pObj)
	{
		if(pObj->GetTypeID() == nTID)
		{
			if(pObj->GetIdentifID() == nIID)
				return pObj;
		}
		pObj = pObj->GetNext(); 
	}

	MessageBox(NULL , _T("GetIdentifObj3D() ����ȃI�u�W�F�Ȃ���") ,"", MB_OK);

	return NULL;
}

// eof