// BaseKeyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XBaseKeyDlg.h"
#include "XAnalyzeDlg.h"


// CBaseKeyDlg �Ի���

IMPLEMENT_DYNAMIC(CXAnalyzeDlg, CDialog)

CXAnalyzeDlg::CXAnalyzeDlg(CWnd* pParent /*=NULL*/)
:CDynDialogEx(pParent)
{
	
}

CXAnalyzeDlg::~CXAnalyzeDlg()
{
}

void CXAnalyzeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	if (!::IsWindow(m_btnSave.m_hWnd))
	{
		return;
	}
}


BEGIN_MESSAGE_MAP(CXAnalyzeDlg, CDialog)
	ON_BN_CLICKED(XIDC_BTN_SAVE, &CXAnalyzeDlg::OnBnClickedBtnBasekeySave)
END_MESSAGE_MAP()


// CBaseKeyDlg ��Ϣ�������


void CXAnalyzeDlg::OnBnClickedBtnBasekeySave()
{
	
	CDialog::OnOK();
}


BOOL CXAnalyzeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateControls();  //�����ؼ�

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CXAnalyzeDlg::CreateControls()    //�����ؼ�  name�� size�� ID�� this    //�������Ӹ����ؼ������ԣ����尡ʲô��
{
	CreateButton(m_btnSave, _T("����"), CRect(220, 50, 290, 70),XIDC_BTN_SAVE , this);

	CFont *pFont = GetFont();
	m_btnSave.SetFont(pFont);
}


int CXAnalyzeDlg::DoModal()   //�����Ի���
{   
	CRect rect(40,50,250,150);   
	SetDlgRect(rect);
	//	AddDlgControl(_T("LISTBOX"), _T("ListboxText"), STYLE_LISTBOX, EXSTYLE_LISTBOX, &rect, &m_lstBox, IDC_LIST1);   
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   



