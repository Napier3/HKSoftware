// Wzd_DetailInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Wzd_DetailInfoDlg.h"


// CWzd_DetailInfoDlg �Ի���

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


// Wzd_DetailInfoDlg ��Ϣ�������
void CWzd_DetailInfoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
}

BOOL CWzd_DetailInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_treeTestStep.AttachOptrInterface(this);

	m_tabTestStep.InsertItem(0, _T("���Բ���"));
	m_tabReportData.InsertItem(0, _T("��������1"));
	m_tabReportData.InsertItem(1, _T("��������2"));
	SetDataTable(0);	

	m_gridReportData1.InitGrid();
	m_gridReportData2.InitGrid();

	m_btnOK.InitUI("normalȷ��.png", "hoverȷ��.png");
	m_btnCancel.InitUI("normalȡ��.png", "hoverȡ��.png");

	InitUI(COLOR_LIGHTGREEN, COLOR_DEEPBLUE);
	SetWindowTitle("��ϸ��Ϣ");

	m_tabTestStep.InitUI(COLOR_LIGHTGREEN, COLOR_DEEPGREEN, COLOR_GRAY);
	m_tabReportData.InitUI(COLOR_LIGHTGREEN, COLOR_DEEPGREEN, COLOR_GRAY);

	m_tabTestStep.AddItem(_T("���Բ���"));
	m_tabReportData.AddItem(_T("��������1"));
	m_tabReportData.AddItem(_T("��������2"));

	m_comboxIndex.InitUI(COLOR_LIGHTGRAY, COLOR_LIGHTGREEN);
 	m_treeTestStep.InitUI("Enable�۵�.png", "Disable�۵�.png",
 		"Enableչ��.png", "Disableչ��.png");

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
	// �쳣: OCX ����ҳӦ���� FALSE
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

	//�������������ComBox
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

	HTREEITEM hSelItem;	//����Ĭ��ѡ��Item

	//��Tree���������
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
		//����Ĭ�ϲ������ʾ��������
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

	//����m_pSelectBaseItem��m_iReportTime��ʾ��Ӧ����
	if(m_iReportTime >= m_pReports->GetCount())
		m_iReportTime = 0;	//������Χ��ʹ�õ�һ��

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int cursel = m_tabReportData.GetCurSel();
	SetDataTable(cursel);
	*pResult = 0;
}