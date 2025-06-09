// BaseKeyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XXScriptEditDlg.h"
#include "TCtrlCntrBaseApp.h"
#include "..\..\Module\API\GloblaDrawFunctions.h"

// CBaseKeyDlg �Ի���

IMPLEMENT_DYNAMIC(CXScriptEditDlg, CDialog)

CXScriptEditDlg::CXScriptEditDlg(CWnd* pParent /*=NULL*/)
:CDynDialogEx(pParent)
{
	
}

CXScriptEditDlg::~CXScriptEditDlg()
{
}

void CXScriptEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CXScriptEditDlg, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CBaseKeyDlg ��Ϣ�������



BOOL CXScriptEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateControls();  //�����ؼ�
	CenterWindow();

	CTCtrlCntrBaseApp *pApp = (CTCtrlCntrBaseApp*)AfxGetApp();
	CString strText;
	strText.Format(_T("��ȡ¼���ļ�ǰ��ʱ0��,��%d��"), pApp->GetRecorderDelay()/1000);
	m_editMsg.SetWindowText(strText);
	m_nTimerLong = 0;

	CRect rc;
	GetWindowRect(&rc);
	SetWindowPos(&CWnd::wndTopMost, rc.left, rc.top, rc.Width(), rc.Height(),SWP_SHOWWINDOW);
	SetTimer(100, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CXScriptEditDlg::CreateControls()    //�����ؼ�  name�� size�� ID�� this    //�������Ӹ����ؼ������ԣ����尡ʲô��
{
	//240, 290
	CRect rc(5, 5, 293, 262);
	CreateTreeCtrl(m_editScript, rc, IDC_GBSELDLG_TREE_ITEMS, this);
	
	CRect rc;
	rc.top = 270;
	rc.left = 15;
	rc.right = 100;
	rc.bottom = 270 + 25;

	CreateButton(m_btnOK, _T("ȷ��"), rc, IDOK, this);

	rc.left = 110;
	rc.right = 195;
	CreateButton(m_btnCancel, _T("ȡ��"), rc, IDCANCEL, this);

	m_btnCancel.SetFont(g_pGlobalFont12);
	m_btnOK.SetFont(g_pGlobalFont12);
	m_treeItemsAncester.SetFont(g_pGlobalFont12);
	m_editScript.SetFont(g_pGlobalFont14);
}


int CXScriptEditDlg::DoModal()   //�����Ի���
{   
	CRect rect(0,0,256,30);   
	SetDlgRect(rect);
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   



void CXScriptEditDlg::OnOK()
{

}

void CXScriptEditDlg::OnCancel()
{
	
}


void CXScriptEditDlg::OnTimer(UINT_PTR nIDEvent)
{
	CTCtrlCntrBaseApp *pApp = (CTCtrlCntrBaseApp*)AfxGetApp();
	m_nTimerLong += 1000;

	if (m_nTimerLong <pApp->GetRecorderDelay() )
	{
		CString strText;
		strText.Format(_T("��ȡ¼���ļ�ǰ��ʱ%d��,��%d��"), m_nTimerLong/1000, pApp->GetRecorderDelay()/1000);
		m_editMsg.SetWindowText(strText);
		CDialog::OnTimer(nIDEvent);
		return;
	}

	KillTimer(100);

	CMacroTest *pMacroTest = m_pMacroTest;
// 	CString strPath = m_strProjectName;
// 	CString strRecordFile;
// 	strRecordFile = pMacroTest->GetNamePathEx(GBCLASSID_DEVICE, FALSE);
// 	strRecordFile = m_strProjectName + _T("\\") + strRecordFile;
// 
// 	if (pMacroTest->m_nTestTimes > 0)
// 	{
// 		strRecordFile.AppendFormat(_T("%d"), pMacroTest->m_nTestTimes+1);
// 	}
// 
// 	pMacroTest->m_nTestTimes++;

	DWORD dwRet = 0;

	try
	{
		Recorder::CRecorder oRecorder = pApp->GetRecorder();
		dwRet = oRecorder.SaveRecorder(m_strRecordFile);
	}
	catch(...)
	{

	}

	if (dwRet != Recorder::rcdStateRecordSuccess)
	{
		CDialog::OnCancel();
	}
	else
	{
		CDialog::OnOK();
	}
}
