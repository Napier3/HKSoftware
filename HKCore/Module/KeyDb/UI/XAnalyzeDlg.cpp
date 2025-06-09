// BaseKeyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XBaseKeyDlg.h"
#include "XAnalyzeDlg.h"


// CBaseKeyDlg 对话框

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


// CBaseKeyDlg 消息处理程序


void CXAnalyzeDlg::OnBnClickedBtnBasekeySave()
{
	
	CDialog::OnOK();
}


BOOL CXAnalyzeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateControls();  //创建控件

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CXAnalyzeDlg::CreateControls()    //创建控件  name、 size、 ID、 this    //继续增加各个控件的属性，字体啊什么的
{
	CreateButton(m_btnSave, _T("保存"), CRect(220, 50, 290, 70),XIDC_BTN_SAVE , this);

	CFont *pFont = GetFont();
	m_btnSave.SetFont(pFont);
}


int CXAnalyzeDlg::DoModal()   //弹出对话框
{   
	CRect rect(40,50,250,150);   
	SetDlgRect(rect);
	//	AddDlgControl(_T("LISTBOX"), _T("ListboxText"), STYLE_LISTBOX, EXSTYLE_LISTBOX, &rect, &m_lstBox, IDC_LIST1);   
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   



