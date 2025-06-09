// Wzd_ConfigSetDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "iSmartTestWzd.h"
#include "Wzd_ConfigSetDlg.h"

CConfigSetGrid::CConfigSetGrid(void)
{
}

CConfigSetGrid::~CConfigSetGrid(void)
{
}

void CConfigSetGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(3);
	SetFixedRowCount(1);
	SetFixedColumnCount(0);
	InitGridTitle();
}

void CConfigSetGrid::InitGridTitle()
{
	CString astrGridTitle[3] = {_T("名称"),_T("值"), _T("单位")};
	int iGridWidth[3]={150,150,150};
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, 3);
}
void CConfigSetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDataObj *pDataObj = (CDataObj *)pData;
	Show_StaticString(pDataObj, nRow, 0, &pDataObj->m_strName);	
	Show_String(pDataObj, nRow, 1, &pDataObj->m_strValue,EndEditCell_String);
	Show_StaticString(pDataObj, nRow, 2, &pDataObj->m_strUnit);

	nRow++;
}

// CWzd_ConfigSetDlg 对话框

IMPLEMENT_DYNAMIC(CWzd_ConfigSetDlg, CDialog)

CWzd_ConfigSetDlg::CWzd_ConfigSetDlg(CWnd* pParent /*=NULL*/)
	: CUIDialog(CWzd_ConfigSetDlg::IDD, pParent)
{
	m_pDatas = NULL;
	m_pGridDatas = NULL;
	m_strTestParas = "";
}

CWzd_ConfigSetDlg::~CWzd_ConfigSetDlg()
{
}

void CWzd_ConfigSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CWzd_ConfigSetDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CWzd_ConfigSetDlg::OnBnClickedOk)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CWzd_ConfigSetDlg 消息处理程序
BOOL CWzd_ConfigSetDlg::OnInitDialog()
{
	CUIDialog::OnInitDialog();

	CRect rc;
	GetClientRect(rc);
	m_ConfigSetGrid.Create(CRect(5,5,rc.Width() - 10,240),this,XIDC_SET_GRID);
	m_ConfigSetGrid.UseImage(FALSE, COLOR_LIGHTGREEN);
	m_ConfigSetGrid.InitGrid();
	m_ConfigSetGrid.ShowDatas(m_pGridDatas);

	m_btnOK.InitUI("normal确定.png", "hover确定.png");
	m_btnCancel.InitUI("normal取消.png", "hover取消.png");

	InitUI(COLOR_LIGHTGREEN, COLOR_DEEPBLUE);
	SetWindowTitle("系统参数配置");

	MoveChildWindow(&m_btnOK);
	MoveChildWindow(&m_btnCancel);
	MoveChildWindow(&m_ConfigSetGrid);

	return TRUE; 
}
//弹窗中点击确定后，将参数转成XML文本，格式为：
	/*
	<group name="" id="Paras">  //ID固定
		<data name="参数1" id="Para1" value="0.25" />
		<data name="参数2" id="Para2" value="0.25999999" />
		<data name="参数3" id="Para3" value="0.75" />
		……
	</group>
	*/
void CWzd_ConfigSetDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int ncount = 1;
	CDataGroup savexml;
	savexml.m_strID = "Paras";
	POS pos = m_pGridDatas->GetHeadPosition();//如点击取消则不保存修改内容
	while(pos != NULL)
	{
		CString strID;
		strID.Format("%s%d",savexml.m_strID,ncount);
		ncount++;
		CDataObj *pGridData = (CDataObj *)m_pGridDatas->GetNext(pos);
		savexml.AddNewData(pGridData->m_strName,strID,"",pGridData->m_strValue);
		if(m_pDatas == NULL)
			continue;
		CDataObj*pData = (CDataObj *)m_pDatas->FindByID(pGridData->m_strID);
		pData->m_strValue = pGridData->m_strValue;
	}
	m_strTestParas = (CString)savexml.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys);//将最新系统配置信息转换成xml格式
	OnOK();
}

void CWzd_ConfigSetDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}
void CWzd_ConfigSetDlg::SetGridData(CExBaseList *pDatas)
{
	if(pDatas == NULL)
	{
		return;
	}
	m_pDatas = pDatas;
	m_pGridDatas = (CExBaseList *)pDatas->Clone();
}
