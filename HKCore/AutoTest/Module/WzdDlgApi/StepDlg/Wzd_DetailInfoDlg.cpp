// Wzd_DetailInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Wzd_DetailInfoDlg.h"


// CWzd_DetailInfoDlg 对话框

IMPLEMENT_DYNAMIC(CWzd_DetailInfoDlg, CDialog)

CWzd_DetailInfoDlg::CWzd_DetailInfoDlg(CWnd* pParent /*=NULL*/)
	: CUIDialog(CWzd_DetailInfoDlg::IDD, pParent)
{
	m_pShowTestItem = NULL;
	m_pReports = NULL;
	m_iReportTime = -1;
}

CWzd_DetailInfoDlg::~CWzd_DetailInfoDlg()
{
}

void CWzd_DetailInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_TESTSTEP, m_tabTestStep);
	DDX_Control(pDX, IDC_TAB_REPORTDATA, m_tabReportData);
	DDX_Control(pDX, IDC_TREE_TESTSTEP, m_treeTestStep);
	DDX_Control(pDX, IDD_DATA_REPORTDATA1, m_gridReportData1);
	DDX_Control(pDX, IDD_DATA_REPORTDATA2, m_gridReportData2);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_STATIC_WORD1, m_wordTiShi1_Head);
	DDX_Control(pDX, IDC_STATIC_WORD2, m_wordTiShi1_Tail);
	DDX_Control(pDX, IDC_COMBO_INDEX, m_comboxIndex);
}

BEGIN_MESSAGE_MAP(CWzd_DetailInfoDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
	ON_CBN_SELCHANGE(IDC_COMBO_INDEX, &CWzd_DetailInfoDlg::OnCbnSelchangeComboxIndex)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_REPORTDATA, &CWzd_DetailInfoDlg::OnSelchangeTabReportData)
END_MESSAGE_MAP()


// Wzd_DetailInfoDlg 消息处理程序
void CWzd_DetailInfoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
}

BOOL CWzd_DetailInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_treeTestStep.AttachOptrInterface(this);

	m_tabTestStep.InsertItem(0, _T("测试步骤"));
	m_tabReportData.InsertItem(0, _T("报告数据1"));
	m_tabReportData.InsertItem(1, _T("报告数据2"));
	SetDataTable(0);	

	m_gridReportData1.InitGrid();
	m_gridReportData2.InitGrid();

	m_btnOK.InitUI("normal确定.png", "hover确定.png");
	m_btnCancel.InitUI("normal取消.png", "hover取消.png");

	InitUI(COLOR_LIGHTGREEN, COLOR_DEEPBLUE);
	SetWindowTitle("详细信息");

	m_tabTestStep.InitUI(COLOR_LIGHTGREEN, COLOR_DEEPGREEN, COLOR_GRAY);
	m_tabReportData.InitUI(COLOR_LIGHTGREEN, COLOR_DEEPGREEN, COLOR_GRAY);

	m_tabTestStep.AddItem(_T("测试步骤"));
	m_tabReportData.AddItem(_T("报告数据1"));
	m_tabReportData.AddItem(_T("报告数据2"));

	m_comboxIndex.InitUI(COLOR_LIGHTGRAY, COLOR_LIGHTGREEN);
 	m_treeTestStep.InitUI("Enable折叠.png", "Disable折叠.png",
 		"Enable展开.png", "Disable展开.png");

	m_gridReportData1.UseImage(FALSE, COLOR_LIGHTGREEN);
	m_gridReportData2.UseImage(FALSE, COLOR_LIGHTGREEN);


	MoveChildWindow(&m_btnOK);
	MoveChildWindow(&m_btnCancel);
	MoveChildWindow(&m_tabTestStep);
	MoveChildWindow(&m_tabReportData);
	MoveChildWindow(&m_treeTestStep);
	MoveChildWindow(&m_gridReportData1);
	MoveChildWindow(&m_gridReportData2);
	MoveChildWindow(&m_wordTiShi1_Head);
	MoveChildWindow(&m_wordTiShi1_Tail);
	MoveChildWindow(&m_comboxIndex);

	ShowTreeData();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CWzd_DetailInfoDlg::ShowItemDetailInfo(CItems* pTestItem)
{
	m_pShowTestItem = pTestItem;
}

void CWzd_DetailInfoDlg::SetDataTable(int iIndex)
{
	m_tabReportData.SetCurSel(iIndex);

	m_gridReportData1.ShowWindow(SW_HIDE);
	m_gridReportData2.ShowWindow(SW_HIDE);
	switch(iIndex)
	{
	case 0:
		m_gridReportData1.ShowWindow(SW_SHOW);
		break;
	case 1:
		m_gridReportData2.ShowWindow(SW_SHOW);
		break;
	}
}

void CWzd_DetailInfoDlg::AddComBoxData(int iCount)
{
	m_comboxIndex.ResetContent();

	//依据数据来添加ComBox
	for(int i=0; i<iCount; i++)
	{
		CString strName;
		strName.Format(_T("%d"), i+1);
		m_comboxIndex.InsertString(i, strName);
	}

	m_iReportTime = 0;
	m_comboxIndex.SetCurSel(0);
}

void CWzd_DetailInfoDlg::ShowTreeData()
{
	if(m_pShowTestItem == NULL)
		return;

	HTREEITEM hSelItem;	//设置默认选择Item

	//向Tree中添加数据
 	m_treeTestStep.AddClassID(GBCLASSID_COMMCMD);
 	m_treeTestStep.AddClassID(GBCLASSID_DEVICE);
 	m_treeTestStep.AddClassID(GBCLASSID_GUIDEBOOK);
 	m_treeTestStep.AddClassID(GBCLASSID_ITEMS);
 	m_treeTestStep.AddClassID(GBCLASSID_JOBGUIDE);
 	m_treeTestStep.AddClassID(GBCLASSID_MACROCHARITEMS);
 	m_treeTestStep.AddClassID(GBCLASSID_MACROTEST);
 	m_treeTestStep.AddClassID(GBCLASSID_SAFETY);
 	m_treeTestStep.AddClassID(GBCLASSID_SYSPARAEDIT);
	//m_treeTestStep.AddClassID(GBCLASSID_ITEMBASE);

 	m_treeTestStep.ShowBaseList(m_pShowTestItem);
	hSelItem = m_treeTestStep.GetRootItem();
	if(hSelItem != NULL)
	{
		//设置默认步骤后显示报告数据
		SetSelectReports((CGbItemBase*)m_treeTestStep.GetItemData(hSelItem));
	}	
}

void CWzd_DetailInfoDlg::ClearReportDataShow()
{
	m_iReportTime = -1;
	m_pReports = NULL;

	m_comboxIndex.ResetContent();
	m_gridReportData1.ShowDatas(NULL);
	m_gridReportData2.ShowDatas(NULL);
}
void CWzd_DetailInfoDlg::SetSelectReports(CGbItemBase* pSelectBaseItem)
{
	ClearReportDataShow();

	if(pSelectBaseItem == NULL)
		return ;

	m_pReports = pSelectBaseItem->m_pReports;
	if(m_pReports == NULL)
		return ;

	int iCount = m_pReports->GetCount();
	if(iCount <= 0)
		return ;
	AddComBoxData(iCount);
	
	ShowReportData();
}
void CWzd_DetailInfoDlg::ShowReportData()
{
	m_gridReportData1.ShowDatas(NULL);
	m_gridReportData2.ShowDatas(NULL);
	if(m_pReports == NULL || m_iReportTime == -1)
		return ;

	//依据m_pSelectBaseItem和m_iReportTime显示对应报告
	if(m_iReportTime >= m_pReports->GetCount())
		m_iReportTime = 0;	//超出范围就使用第一个

	CReport* pReport = (CReport*)m_pReports->GetAt(m_iReportTime);
	if(pReport == NULL)
		return ;

	m_gridReportData1.ShowDatas(pReport->m_pValues);	
	m_gridReportData2.ShowDatas(pReport->m_pRptDvmDataset);
} 

void CWzd_DetailInfoDlg::OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)
{
	SetSelectReports((CGbItemBase*)pSelObj);
}
void CWzd_DetailInfoDlg::OnCbnSelchangeComboxIndex()
{
	m_iReportTime = m_comboxIndex.GetCurSel();
	ShowReportData();
}
void CWzd_DetailInfoDlg::OnSelchangeTabReportData(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int cursel = m_tabReportData.GetCurSel();
	SetDataTable(cursel);
	*pResult = 0;
}