// DialogPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DialogPage.h"


// CDialogPage �Ի���

IMPLEMENT_DYNAMIC(CDialogPage, CDialog)

CDialogPage::CDialogPage(UINT nIDD, const CString &strCaption, CSize sz, CWnd *pParent)
	: CDialog(nIDD, pParent)
{
	m_strCaption = strCaption;
	m_nIDD = nIDD;
	m_szPage = sz;
}

CDialogPage::~CDialogPage()
{
}

// CDialogPage ��Ϣ�������
void CDialogPage::OnKillActive()
{

}

void CDialogPage::OnSetActive()
{

}

void CDialogPage::CreatePage(CWnd *pParent)
{
	Create(m_nIDD,pParent);
}
