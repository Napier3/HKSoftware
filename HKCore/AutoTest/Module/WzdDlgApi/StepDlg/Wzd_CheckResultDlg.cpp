// Wzd_CheckResultDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "iSmartTestWzd.h"
#include "Wzd_CheckResultDlg.h"
#include "HeaderCtrlEx.h"

// CWzd_CheckResultDlg 对话框

IMPLEMENT_DYNAMIC(CWzd_CheckResultDlg, CDialog)

CWzd_CheckResultDlg::CWzd_CheckResultDlg(CWnd* pParent /*=NULL*/)
	: CWzdDlgBase(CWzd_CheckResultDlg::IDD, pParent)
{

}

CWzd_CheckResultDlg::~CWzd_CheckResultDlg()
{
}

void CWzd_CheckResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_RESULT_LIST, m_ctrlItemResutList);
	DDX_Control(pDX, IDC_CHECK_COUNT_COMBO, m_ctrlCBBChectCount);
	DDX_Control(pDX, IDC_STATIC3, m_Static3);
}


BEGIN_MESSAGE_MAP(CWzd_CheckResultDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_CHECK_COUNT_COMBO, &CWzd_CheckResultDlg::OnCbnSelchangeCheckCountCombo)
END_MESSAGE_MAP()


void CWzd_CheckResultDlg::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
	//具体移动
	XUI_AddWnd(&m_ctrlItemResutList, 0, 0, 1, 1);
	XUI_AddWnd(&m_Static3, 0, 0, 1, 0);
	CXUIAdjItem_Area::XUI_OnSize();
}

// CWzd_CheckResultDlg 消息处理程序
void CWzd_CheckResultDlg::InitCheckResultInfo()
{
	m_ImageList.Create(1,24,ILC_MASK|ILC_COLOR32,4,4);
	m_ImageList.SetBkColor(CLR_NONE);
	CString strImg = _P_GetResourcePath();
	strImg += "iSmartTestWzd/test/";
	CString strImg1 = strImg+ "fail.ico";
	HICON IcImage1 = (HICON)LoadImage(NULL, strImg1, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	m_ImageList.Add(IcImage1);


	m_ctrlItemResutList.SetImageList(&m_ImageList,LVSIL_SMALL);
	m_ctrlItemResutList.SetExtendedStyle(m_ctrlItemResutList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP/*|LVS_EX_GRIDLINES*/);
	m_ctrlItemResutList.SetIsShowLine(true);
	CHeaderCtrlEx* pHeader = new CHeaderCtrlEx();
	pHeader->SubclassWindow(m_ctrlItemResutList.GetHeaderCtrl()->GetSafeHwnd());
	pHeader->ModifyStyle(WS_CAPTION,0,SWP_DRAWFRAME);
	pHeader->SetHeaderCtrlBKColor(RGB(242,248,248));

	//m_ctrlItemResutList.SetColumnWidth(1, LVSCW_AUTOSIZE);

	CRect rect;
	m_ctrlItemResutList.GetClientRect(&rect);
	m_ctrlItemResutList.InsertColumn(0, _T("数据名称"), LVCFMT_LEFT, rect.Width()/2);
	m_ctrlItemResutList.InsertColumn(1, _T("值"), LVCFMT_LEFT, rect.Width()/2);

	
	InitCheckBoxInfo();
}

void CWzd_CheckResultDlg::InitCheckBoxInfo()
{
	//m_ctrlItemResutList.
	m_ctrlCBBChectCount.InitUI(COLOR_LIGHTGRAY, COLOR_LIGHTGREEN);
	m_ctrlCBBChectCount.AddString("无检测报告");
	m_ctrlCBBChectCount.SetCurSel(0);
}

void CWzd_CheckResultDlg::SetCheckResultInfo(CReports* pReports)
{
	if (pReports == NULL)
	{
		m_ctrlCBBChectCount.ResetContent();
		m_ctrlCBBChectCount.AddString("无检测报告");
		m_ctrlCBBChectCount.SetCurSel(0);
		m_ctrlItemResutList.DeleteAllItems();
		return;
	}

	int nCount = pReports->GetCount();
	if(nCount <= 0)
	{
		m_ctrlCBBChectCount.ResetContent();
		m_ctrlCBBChectCount.AddString("无检测报告");
		m_ctrlCBBChectCount.SetCurSel(0);
		m_ctrlItemResutList.DeleteAllItems();
		return;
	}

	m_ctrlCBBChectCount.ResetContent();
	int nn = m_ctrlCBBChectCount.GetCount();
	int nItemIndex = 0;
	POS ReportsPos  = pReports->GetHeadPosition();
	CReport *pReport = NULL;
	while (ReportsPos != NULL)
	{
		pReport = (CReport*)pReports->GetNext(ReportsPos);
		CString strPos = "";
		strPos.Format("%d",nItemIndex+1);
		int nItem = m_ctrlCBBChectCount.AddString(strPos);
		m_ctrlCBBChectCount.SetItemData(nItem,(DWORD)pReport);
		nItemIndex++;
	}
	m_ctrlCBBChectCount.SetCurSel(0);

	m_ctrlItemResutList.DeleteAllItems();

	//默认显示第一个报告
	int nRowIndex = 0;
	POS ReportsPos1  = pReports->GetHeadPosition();
	CReport *pReport1 = NULL;
	pReport1 = (CReport*)pReports->GetNext(ReportsPos1);
	SetCurrentCheckResultInfo(pReport1);
	
}

void CWzd_CheckResultDlg::ClearResult()
{
	m_ctrlCBBChectCount.Clear();
	m_ctrlCBBChectCount.AddString(_T("无检测报告"));
	m_ctrlCBBChectCount.SetCurSel(0);
	m_ctrlItemResutList.DeleteAllItems();
}

void CWzd_CheckResultDlg::SetCurrentCheckResultInfo(CReport* pReport)
{
	int nRowIndex = 0;
	CValues* pValues = pReport->GetValues();
	POS ValuesPos  = pValues->GetHeadPosition();
	CValue *pValue = NULL;
	while(ValuesPos)
	{
		pValue = (CValue*)pValues->GetNext(ValuesPos);
		if(pValue->m_strID == "Unqualified_Analysis")
		{
			continue;
		}
		m_ctrlItemResutList.InsertItem(nRowIndex,pValue->m_strName,-1);
		m_ctrlItemResutList.SetItemText(nRowIndex,1,pValue->m_strValue);
		nRowIndex++;
	}
}


////////////////////////
void CWzd_CheckResultDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
	if(m_ctrlItemResutList.GetSafeHwnd() == NULL)
	{
		return;
	}
	CRect rect;
	m_ctrlItemResutList.GetClientRect(&rect);
	//m_ctrlItemResutList.SetColumnWidth(0,rect.Width() -100);
	m_ctrlItemResutList.SetColumnWidth(0,rect.Width()/2);
	m_ctrlItemResutList.SetColumnWidth(1,rect.Width()/2);
}

void CWzd_CheckResultDlg::OnCbnSelchangeCheckCountCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	int nItem = m_ctrlCBBChectCount.GetCurSel();
	if(nItem < 0)
	{
		return;
	}
	CString strText0 = "";
	m_ctrlCBBChectCount.GetLBText(nItem,strText0);
	if(strText0 == "无检测报告")
	{
		return;
	}
	CReport* pReport = NULL;
	pReport = (CReport*)m_ctrlCBBChectCount.GetItemData(nItem);
	if(pReport == NULL)
	{
		return;
	}

	SetCurrentCheckResultInfo(pReport);
}

HBRUSH CWzd_CheckResultDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CWzdDlgBase::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
		HBRUSH aBrush;
		aBrush = CreateSolidBrush(RGB(242,248,248));
		hbr = aBrush;
		break;
	case CTLCOLOR_STATIC:
		if(pWnd->GetDlgCtrlID() == IDC_STATIC2 || pWnd->GetDlgCtrlID() == IDC_STATIC3)
		{
			pDC->SetTextColor(RGB(0,0,0));
			pDC->SetBkColor(RGB(255,255,255));
			HBRUSH b=CreateSolidBrush(RGB(255,255,255));
			return b;
		}
		else
		{
			pDC->SetBkMode(TRANSPARENT);   
			pDC->SetTextColor(RGB(0,0,0));   
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
		}
		
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

