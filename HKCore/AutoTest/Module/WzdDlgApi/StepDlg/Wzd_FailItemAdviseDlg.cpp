// Wzd_FailItemAdviseDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "iSmartTestWzd.h"
#include "Wzd_FailItemAdviseDlg.h"


// CWzd_FailItemAdviseDlg 对话框

IMPLEMENT_DYNAMIC(CWzd_FailItemAdviseDlg, CDialog)

CWzd_FailItemAdviseDlg::CWzd_FailItemAdviseDlg(CWnd* pParent /*=NULL*/)
	: CUIDialog(CWzd_FailItemAdviseDlg::IDD, pParent)
{
	m_strAdvise = "";
}

CWzd_FailItemAdviseDlg::~CWzd_FailItemAdviseDlg()
{
}

void CWzd_FailItemAdviseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_INFO_STATIC, m_txtAdvise);
}


BEGIN_MESSAGE_MAP(CWzd_FailItemAdviseDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CWzd_FailItemAdviseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWzd_FailItemAdviseDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CWzd_FailItemAdviseDlg 消息处理程序
void CWzd_FailItemAdviseDlg::InitFailItemAdvise(CString strAdvise)
{
	m_strAdvise = strAdvise;
	if(m_strAdvise == "")
	{
		m_strAdvise = _T("暂时没有建议");
	}
	GetDlgItem(IDC_INFO_STATIC)->SetWindowText(m_strAdvise);

	m_btnOK.InitUI("normal确定.png", "hover确定.png");
	m_btnCancel.InitUI("normal取消.png", "hover取消.png");
}

void CWzd_FailItemAdviseDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CWzd_FailItemAdviseDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
