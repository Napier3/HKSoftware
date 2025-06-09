// SetsImportEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SetsImportEditDlg.h"
#include "../../../../Module/API/GloblaDrawFunctions.h"

//////////////////////////////////////////////////////////////////////////
//CSetsImportEditGrid_File
CSetsImportEditGrid_File::CSetsImportEditGrid_File()
{

}

CSetsImportEditGrid_File::~CSetsImportEditGrid_File()
{

}

void CSetsImportEditGrid_File::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(3);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CSetsImportEditGrid_File::InitGridTitle()
{
	CString astrGridTitle[3] = {_T("编号"),_T("名称"), _T("数值")};
	int iGridWidth[3]={50,200,80};
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, 3);
}

void CSetsImportEditGrid_File::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pDvmData = (CDvmData*)pData;

	Show_Index(pDvmData, nRow, 0);
	Show_StaticString(pDvmData, nRow, 1, &pDvmData->m_strName);
	Show_StaticString(pDvmData, nRow, 2, &pDvmData->m_strValue);
	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CSetsImportEditGrid_Gb
CSetsImportEditGrid_Gb::CSetsImportEditGrid_Gb()
{

}

CSetsImportEditGrid_Gb::~CSetsImportEditGrid_Gb()
{

}

void CSetsImportEditGrid_Gb::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(3);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CSetsImportEditGrid_Gb::InitGridTitle()
{
	CString astrGridTitle[3] = {_T("编号"),_T("名称"), _T("数值")};
	int iGridWidth[3]={50,200,80};
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, 3);
}

void CSetsImportEditGrid_Gb::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDataObj *pDataObj = (CDataObj*)pData;

	Show_Index(pDataObj, nRow, 0);
	Show_StaticString(pDataObj, nRow, 1, &pDataObj->m_strName);
	Show_String(pDataObj, nRow, 2, &pDataObj->m_strValue);   //修改为可编辑。shaolei 20220219

	if (pDataObj->m_strValue.IsEmpty() || !IsStringNumber(pDataObj->m_strValue))
	{
		SetItemBkColour(nRow, 2, RGB(255, 0, 0));
	}
	
	nRow++;
}

//////////////////////////////////////////////////////////////////////////
// CSetsImportEditDlg 对话框

CSetsImportEditDlg::CSetsImportEditDlg(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent, TRUE)
{
	m_nSetsType = 0;
	m_pStesFileTool = NULL;
}

CSetsImportEditDlg::~CSetsImportEditDlg()
{
}

void CSetsImportEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSetsImportEditDlg, CDialog)
	ON_BN_CLICKED(XIDC_DS_SEL_SETS, &CSetsImportEditDlg::OnBnClickedDsSelSets)
	ON_BN_CLICKED(XIDC_DS_SEL_ENA, &CSetsImportEditDlg::OnBnClickedDsSelEna)
	ON_BN_CLICKED(XIDC_DS_SEL_DEV_PARAS, &CSetsImportEditDlg::OnBnClickedDsSelDevParas)
	ON_BN_CLICKED(XIDC_DS_SEL_CTRL_WORD, &CSetsImportEditDlg::OnBnClickedDsSelCtrlWord)
	ON_BN_CLICKED(XIDC_DS_SEL_OUT_MATR, &CSetsImportEditDlg::OnBnClickedDsSelOutMatr)
	ON_BN_CLICKED(XIDC_BTN_TIME_S_TO_MS, &CSetsImportEditDlg::OnBnClickedTime_S_to_ms)
END_MESSAGE_MAP()


// CSetsImportEditDlg 消息处理程序

void CSetsImportEditDlg::OnBnClickedDsSelSets()
{
	m_nSetsType = 0;
	ShowSets();
}

void CSetsImportEditDlg::OnBnClickedDsSelEna()
{
	m_nSetsType = 1;
	ShowSets();
}

void CSetsImportEditDlg::OnBnClickedDsSelDevParas()
{
	m_nSetsType = 2;
	ShowSets();
}

void CSetsImportEditDlg::OnBnClickedDsSelCtrlWord()
{
	m_nSetsType = 3;
	ShowSets();
}

void CSetsImportEditDlg::OnBnClickedDsSelOutMatr()
{
	m_nSetsType = 4;
	ShowSets();
}

void CSetsImportEditDlg::OnBnClickedTime_S_to_ms()
{
	m_pStesFileTool->Time_S_to_ms();
	ShowSets();
}

BOOL CSetsImportEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
/*
BEGIN
    CONTROL         "定值",XIDC_DS_SEL_SETS,"Button",BS_AUTORADIOBUTTON,7,7,32,10
    CONTROL         "压板",XIDC_DS_SEL_ENA,"Button",BS_AUTORADIOBUTTON,55,7,32,10
    CONTROL         "装置参数",XIDC_DS_SEL_DEV_PARAS,"Button",BS_AUTORADIOBUTTON,103,7,48,10
    CONTROL         "控制字",XIDC_DS_SEL_CTRL_WORD,"Button",BS_AUTORADIOBUTTON,167,7,40,10
    DEFPUSHBUTTON   "确定",IDOK,453,266,50,14
    PUSHBUTTON      "取消",IDCANCEL,514,266,50,14
    CONTROL         "自定义1",XIDC_GRID_FILE,"MFCGridCtrl",WS_BORDER | WS_TABSTOP,7,22,276,240
    CONTROL         "自定义1",XIDC_GRID_GB,"MFCGridCtrl",WS_BORDER | WS_TABSTOP,289,22,275,239
END

*/
	CreateRadioBoxGroup(m_btnSets, _T("定值"), CRect(5,5,95,25), XIDC_DS_SEL_SETS, this);
	CreateRadioBox(m_btnEna, _T("压板"), CRect(100,5,195,25), XIDC_DS_SEL_ENA, this);
	CreateRadioBox(m_btnParameter, _T("装置参数"), CRect(200,5,295,25), XIDC_DS_SEL_DEV_PARAS, this);
	CreateRadioBox(m_btnCtrl, _T("控制字"), CRect(300,5,395,25), XIDC_DS_SEL_CTRL_WORD, this);
	CreateRadioBox(m_btnOutMatr, _T("跳闸矩阵"), CRect(400,5,495,25), XIDC_DS_SEL_OUT_MATR, this);
	CreateButton(m_btnTimeToMs, _T("时间定值为ms"), CRect(750,507,850,532), XIDC_BTN_TIME_S_TO_MS, this);
	CreateButton(m_btnOK, _T("确定"), CRect(870,507,970,532), IDOK, this);

	m_btnSets.SetCheck(1);
	m_btnSets.SetFont(g_pGlobalFont11);
	m_btnEna.SetFont(g_pGlobalFont11);
	m_btnParameter.SetFont(g_pGlobalFont11);
	m_btnCtrl.SetFont(g_pGlobalFont11);
	m_btnOutMatr.SetFont(g_pGlobalFont11);
	m_btnOK.SetFont(g_pGlobalFont11);
	m_btnTimeToMs.SetFont(g_pGlobalFont11);

	m_gridDsFile.Create(CRect(5,30,485,505),this,XIDC_GRID_FILE);
	m_gridDsGb.Create(CRect(490,30,970,505),this,XIDC_GRID_GB);

	m_gridDsFile.InitGrid();
	m_gridDsGb.InitGrid();

	ShowSets();

	CRect rcDlg;
	GetWindowRect(rcDlg);
	rcDlg.right = rcDlg.left + 990;
	rcDlg.bottom = rcDlg.top + 565;
	MoveWindow(rcDlg);
	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSetsImportEditDlg::ShowSets()
{
	ASSERT (m_pStesFileTool != NULL);
	CDvmDataset *pSrcDatast = NULL;
	CDataSet *pGbDataset = NULL;

	switch (m_nSetsType )
	{
	case 0:
		m_pStesFileTool->GetDataset(SETS_TITLE_ID_SETTING, SETS_TITLE_ID_SETTING, &pSrcDatast, &pGbDataset);
		break;

	case 1:
		m_pStesFileTool->GetDataset(SETS_TITLE_ID_ENA, SETS_TITLE_ID_ENA, &pSrcDatast, &pGbDataset);
		break;

	case 2:
		m_pStesFileTool->GetDataset(SETS_TITLE_ID_PARAMETER, SETS_TITLE_ID_PARAMETER, &pSrcDatast, &pGbDataset);
		break;

	case 3:
		m_pStesFileTool->GetDataset(SETS_TITLE_ID_CTRL, SETS_TITLE_ID_SETTING, &pSrcDatast, &pGbDataset);
		break;

	case 4:
		m_pStesFileTool->GetDataset(SETS_TITLE_ID_MATRIX, SETS_TITLE_ID_SETTING, &pSrcDatast, &pGbDataset);
		break;

	default:
		break;
	}

	m_gridDsFile.ShowDatas(pSrcDatast);
	m_gridDsGb.ShowDatas(pGbDataset);
}

