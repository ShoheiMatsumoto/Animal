#include "TexMgr.h"

#define NULL_ID (9999)

CTexMgr::CTexMgr(void)
{
}


CTexMgr::~CTexMgr(void)
{
}


// �}�l�[�W������
CTexMgr*		CTexMgr::Create(int nTexNum)
{
	CTexMgr* pMgr = new CTexMgr();

	pMgr->Initialize(nTexNum);

	return pMgr;
}

// ��������
void		CTexMgr::Initialize(int nTexNum)
{
	m_nEntryNum = nTexNum;		// �o�^��
	

	InitList();		
}

// �}�l�[�W�����
void		CTexMgr::Release()
{
	InitList();
	delete this;
}

// ���X�g������
void		CTexMgr::InitList()		
{
	// ���X�g����
	m_ppTexList = (CImage **)malloc(sizeof(CImage) * m_nEntryNum);		// ���X�g������
	m_pnIDArray = (int *)malloc(sizeof(int) * m_nEntryNum);				// �G���g���[ID����

	// ���X�g��������
	for(int i = 0; i < m_nEntryNum; i++)
	{
		m_ppTexList[i] = NULL;
		m_pnIDArray[i] = NULL_ID;
	}
}

// �e�N�X�`���G���g���[
void		CTexMgr::Entry(int nID, LPCTSTR pszfName, int nPattern)
{
	// �g����Ƃ��̑���
	int nEntry = CheckRunID(nID);

	if(nEntry != NULL_ID)
	{	// �o�^�ς݂łȂ��ꍇ
		// �e�N�X�`�����ǂݍ���
		m_ppTexList[nEntry]		= CImage::Create(pszfName, nPattern);
	}
	

}

// ID�o�^����
int			CTexMgr::CheckRunID(int nID)
{
	// ID���o�^�ς݂�����
	for(int i = 0; i < m_nEntryNum; i++)
	{
		// �o�^���Ă�������
		if(m_pnIDArray[i] == nID)
		{
			return NULL_ID;
		}

		// ��̔z��ɍs��������
		if(m_pnIDArray[i] == NULL_ID)
		{
			m_pnIDArray[i] = nID;		// �V�K�o�^ID
			return i;
		}
	}

	// �G���[
	// ���X�g���߂Ƃ��H
	// ���X�g�̒ǉ�
	m_nEntryNum ++;
	m_pnIDArray = (int *)realloc(m_pnIDArray, sizeof(int) * m_nEntryNum);
	m_pnIDArray[m_nEntryNum - 1] = nID;
	m_ppTexList = (CImage **)realloc(m_ppTexList, sizeof(CImage) * m_nEntryNum);
	
	return m_nEntryNum - 1;
}

// ���X�g�̉��
void		CTexMgr::ReleaseList()
{
	// ���X�g�����
	for(int i = 0; i < m_nEntryNum; i++)
	{
		m_ppTexList[i]->Release();
	}

	// ���ꕨ���
	free(m_ppTexList);
	free(m_pnIDArray);
}

// �e�N�X�`���f�[�^�̎擾
CImage*		CTexMgr::GetTex(int nTexID)
{
	int nEntry = NULL_ID;
	// ID�o�^�o�^���X�g����
	for(int i = 0; i < m_nEntryNum; i++)
	{
		if(m_pnIDArray[i] == nTexID)
		{	// ��v
			nEntry = i;
			break;
		}
	}

	if(nEntry == NULL_ID)
	{	// �Y���Ȃ�
		// �G���[����

	}

	// �Y���e�N�X�`���f�[�^��Ԃ�
	return m_ppTexList[nEntry];
}




// eof