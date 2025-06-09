// MessageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MessageDlg.h"


// MessageDlg 对话框

IMPLEMENT_DYNAMIC(MessageDlg, CDialog)

MessageDlg::MessageDlg(CWnd* pParent /*=NULL*/)
	: CUIDialog(MessageDlg::IDD, pParent)
{

}

MessageDlg::~MessageDlg()
{
}

void MessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDOK2, m_btnOK2);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_txtText);
	DDX_Control(pDX, IDC_BTN_ICON, m_btnIcon);
}

void MessageDlg::SetMessage(CString strTitle, CString strText, tagMode nMode)
{
	m_nMode = nMode;
	m_strText = strText;
	m_strTitle = strTitle;
}

INT_PTR MessageDlg::MessageBox(CString strTitle, CString strText, tagMode nMode)
{
	MessageDlg dlg;
	dlg.SetMessage(strTitle, strText, nMode);
	return dlg.DoModal();
}

BOOL MessageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_btnOK.InitUI("normal确定.png", "hover确定.png");
	m_btnOK2.InitUI("normal确定.png", "hover确定.png");
	m_btnCancel.InitUI("normal取消.png", "hover取消.png");

	m_btnOK.ShowWindow(SW_HIDE);
	m_btnOK2.ShowWindow(SW_HIDE);
	m_btnCancel.ShowWindow(SW_HIDE);

	switch(m_nMode)
	{
	case YES:
		m_btnOK2.ShowWindow(SW_SHOW);
		m_btnIcon.InitUI("Info.png", "Info.png");
		break;
	case YESANDNO:
		m_btnOK.ShowWindow(SW_SHOW);
		m_btnCancel.ShowWindow(SW_SHOW);
		m_btnIcon.InitUI("Info.png", "Info.png");
		break;
	case ERRYES:
		m_btnOK2.ShowWindow(SW_SHOW);
		m_btnIcon.InitUI("ErrorInfo.png", "ErrorInfo.png");
		break;
	case ERRYESANDNO:
		m_btnOK.ShowWindow(SW_SHOW);
		m_btnCancel.ShowWindow(SW_SHOW);
		m_btnIcon.InitUI("ErrorInfo.png", "ErrorInfo.png");
		break;
	default:
		break;
	}

	SetWindowTitle(m_strTitle);
	m_txtText.SetWindowText(m_strText);
	InitUI(COLOR_LIGHTGREEN, COLOR_DEEPBLUE);

	CRect rc, rcText;
	GetClientRect(rc);
	m_txtText.GetWindowRect(rcText);
	long nWidth = rcText.Width();
	long nHeight = rcText.Height();
	CDC* pDC = m_txtText.GetDC();
	pDC->DrawText(m_strText, rcText, DT_WORDBREAK | DT_CALCRECT | DT_EDITCONTROL);
	m_txtText.SetWindowPos(NULL, 0, 0, nWidth, rcText.Height(), SWP_NOMOVE);
	SetWindowPos(NULL, 0, 0, rc.Width(), rc.Height() + rcText.Height() - nHeight, SWP_NOMOVE);

	CRect rcOK, rcOK2, rcCancel;
	m_btnOK.GetWindowRect(rcOK);
	ScreenToClient(rcOK);
	m_btnOK2.GetWindowRect(rcOK2);
	ScreenToClient(rcOK2);
	m_btnCancel.GetWindowRect(rcCancel);
	ScreenToClient(rcCancel);
	m_btnOK.SetWindowPos(NULL, rcOK.left, rcOK.top + rcText.Height() - nHeight, 0, 0, SWP_NOSIZE);
	m_btnOK2.SetWindowPos(NULL, rcOK2.left, rcOK2.top + rcText.Height() - nHeight, 0, 0, SWP_NOSIZE);
	m_btnCancel.SetWindowPos(NULL, rcCancel.left, rcCancel.top + rcText.Height() - nHeight, 0, 0, SWP_NOSIZE);

	return TRUE;
}

BEGIN_MESSAGE_MAP(MessageDlg, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDOK2, &MessageDlg::OnOK)
END_MESSAGE_MAP()


// MessageDlg 消息处理程序
