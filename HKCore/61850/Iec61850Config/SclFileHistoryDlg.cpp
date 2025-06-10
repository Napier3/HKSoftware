// SclFileHistoryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "SclFileHistoryDlg.h"

#include "..\..\Module\XLanguage\XLangWndAdjust.h"//20161014-


// CSclFileHistoryDlg 对话框

IMPLEMENT_DYNAMIC(CSclFileHistoryDlg, CDialog)

CSclFileHistoryDlg::CSclFileHistoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSclFileHistoryDlg::IDD, pParent)
{

}

CSclFileHistoryDlg::~CSclFileHistoryDlg()
{
}

void CSclFileHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SCL_HIS, m_listSclFileHis);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_BTN_BROWSE, m_btnIecBrowse);
	DDX_Control(pDX, IDCANCEL, m_btnIecCancel);
}


BEGIN_MESSAGE_MAP(CSclFileHistoryDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_BROWSE, &CSclFileHistoryDlg::OnBnClickedBtnBrowse)
	ON_LBN_SELCHANGE(IDC_LIST_SCL_HIS, &CSclFileHistoryDlg::OnLbnSelchangeListSclHis)
	ON_LBN_DBLCLK(IDC_LIST_SCL_HIS, &CSclFileHistoryDlg::OnLbnDblclkListSclHis)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CSclFileHistoryDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CSclFileHistoryDlg 消息处理程序
void CSclFileHistoryDlg::xlang_InitAndAdjust()   //2016.10.14
{
	if (xlang_IsCurrXLanguageChinese())   //2016.10.14
	{
		return;    //2016.10.14
	}

	m_btnIecBrowse.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_btnIecBrowse);//2016.10.14
	m_btnDelete.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLangID_Delete);//2016.10.14
	m_btnOK.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_btnOK);//2016.10.14
	m_btnIecCancel.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_btnIecCancel);//2016.10.14

	CXLangWndAdjMngr oWndAdjMngr;//2016.10.14
	oWndAdjMngr.RegisterCols();//2016.10.14   注册（添加）一个列集合对象（即行的概念）
	oWndAdjMngr.RegisterXCol(&m_btnIecBrowse);//2016.10.14
	oWndAdjMngr.RegisterXCol(&m_btnDelete);//2016.10.14
	oWndAdjMngr.RegisterXCol(&m_btnOK);//2016.10.14
	oWndAdjMngr.RegisterXCol(&m_btnIecCancel);//2016.10.14

	oWndAdjMngr.Adjust(this, TRUE);//2016.10.14

	xlang_InitByLgugStr(CXLanguageResourceIec_61850Cfg::g_sLangID_SclRecord, this);
	
}

BOOL CSclFileHistoryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	xlang_InitAndAdjust(); //2016.10.13   【此句放在下列窗口调整之前】

	CSclFiles *pSclFiles = CIecCfgTool::GetSclFiles();
	POS pos = pSclFiles->GetHeadPosition();
	CSclFile *pSclFile = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		pSclFile = (CSclFile *)pSclFiles->GetNext(pos);
		nIndex = m_listSclFileHis.AddString(pSclFile->m_strID);
		m_listSclFileHis.SetItemDataPtr(nIndex, pSclFile);
	}
	
	m_listSclFileHis.SetCurSel(0);
	EnableOKButton();

	return TRUE;
}

void CSclFileHistoryDlg::OnBnClickedBtnBrowse()
{
	CSclFiles *pSclFiles = CIecCfgTool::GetSclFiles();
	CSclFile *pSclFile = pSclFiles->Open();

	if (pSclFile != NULL)
	{
		m_strSclFile = pSclFile->m_strID;
		CDialog::OnOK();
	}
}

void CSclFileHistoryDlg::EnableOKButton()
{
	long nSel = m_listSclFileHis.GetCurSel();
	CSclFile *pFile = NULL;
	
	if (nSel != LB_ERR)
	{
		pFile = (CSclFile*)m_listSclFileHis.GetItemDataPtr(nSel);
		m_strSclFile = pFile->m_strID;
	}
	else
	{
		m_strSclFile.Empty();
	}

	if (m_strSclFile.GetLength() > 0)
	{
		m_btnOK.EnableWindow(IsFileExist(m_strSclFile));
	}
	else
	{
		m_btnOK.EnableWindow(FALSE);
	}

	m_btnDelete.EnableWindow(pFile != NULL);
}


void CSclFileHistoryDlg::OnLbnSelchangeListSclHis()
{
	EnableOKButton();
}

void CSclFileHistoryDlg::OnLbnDblclkListSclHis()
{
	long nSel = m_listSclFileHis.GetCurSel();
	CSclFile *pFile = (CSclFile*)m_listSclFileHis.GetItemDataPtr(nSel);
	m_strSclFile = pFile->m_strID;
	CDialog::OnOK();
}

void CSclFileHistoryDlg::OnBnClickedButtonDelete()
{
	long nSel = m_listSclFileHis.GetCurSel();
	CSclFile *pFile = (CSclFile*)m_listSclFileHis.GetItemDataPtr(nSel);
	CSclFiles *pSclFiles = CIecCfgTool::GetSclFiles();

	if (pFile == NULL)
	{
		return;
	}

	CString strMsg;
	strMsg.Format(CXLanguageResourceIec_61850Cfg::g_sLangTxt_CheckDelHistory/*_T("你确实要删除历史记录：\r\n\r\n%s")*/, pFile->m_strID);

	if (MessageBox(strMsg, CXLanguageResourceIec_61850Cfg::g_sLangTxt_Message/*_T("提示")*/, MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		return;
	}

	m_listSclFileHis.DeleteString(nSel);
	pSclFiles->Delete(pFile);
	EnableOKButton();
}
