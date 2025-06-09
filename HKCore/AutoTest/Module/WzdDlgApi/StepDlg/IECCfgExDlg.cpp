#include "stdafx.h"
#include "IECCfgExDlg.h"
#include "../../../../Module/API/MathApi.h"

CIECCfgSmvRateGrid::CIECCfgSmvRateGrid()
{

}


CIECCfgSmvRateGrid::~CIECCfgSmvRateGrid(void)
{

}

void CIECCfgSmvRateGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_COLS_SMVRATE);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIECCfgSmvRateGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_COLS_SMVRATE]={_T("序号"),_T("名称"),_T("比例因子")};

	int iWidth[IECCFG_COLS_SMVRATE]={60,180,160};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_SMVRATE);
}


void CIECCfgSmvRateGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (nClassID != CFGCLASSID_CIECCFGSMVRATE)
	{
		return;
	}

	Show_Index(pData, nRow, 0);

	CIecCfgSmvRate *pSmvRate = (CIecCfgSmvRate*)pData;

	Show_StaticString(pData, nRow, IECCFG_COL_ID_SMVRATE_NAME, &pSmvRate->m_strName);
	Show_Float(pData, nRow, IECCFG_COL_ID_SMVRATE_RATE, 4,  &pSmvRate->m_fRate, TRUE, EndEditCell_Value_Precision);

	nRow++;
}

void CIECCfgSmvRateGrid::EndEditCell_Value_Precision(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	ASSERT (pVellData->pString != NULL);
	ASSERT (pVellData->nVt == VCD_FLOAT);

	*(pVellData->pfValue) = math_GetValueFromString(pCell->szText);
	pCell->szText.Format(_T("%.4f"), *(pVellData->pfValue));
	pGrid->RedrawCell(nRow, nCol);
}

IMPLEMENT_DYNAMIC(CIECCfgExDlg, CDialog)

CIECCfgExDlg::CIECCfgExDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIECCfgExDlg::IDD, pParent)
{
	m_pIecSMV = NULL;
	m_pCommon = NULL;
	m_pIecCfgSmvRates = NULL;
}

CIECCfgExDlg::~CIECCfgExDlg()
{

}

void CIECCfgExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_GRID_EX, m_gridEx);
	DDX_Control(pDX, IDC_CBB_ASDU, m_cbbASDU);
	DDX_Control(pDX, IDC_EDIT_RATE, m_editRate);
}

void CIECCfgExDlg::SetIecCfg(CIecCfgDatasSMV* pIecCfg)
{
	m_pIecSMV = pIecCfg;
	CIecCfgSmvRates* pSmvRates = pIecCfg->GetIecCfgSmvRates();
	pSmvRates->TransSmvRateID();
	m_pIecCfgSmvRates = (CIecCfgSmvRates*)pSmvRates->Clone();
	m_pCommon = pIecCfg->GetCommonData();
}

BOOL CIECCfgExDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	for (int i = 1; i < 9; i++)
	{
		CString strNum;
		strNum.Format("%d", i);
		m_cbbASDU.AddString(strNum);
	}

	CString strRate, strASDU;
	strRate.Format("%d", m_pCommon->m_nSampleRate);
	m_editRate.SetWindowText(strRate);

	strASDU.Format("%d", m_pCommon->m_nAsduNum);
	m_cbbASDU.SelectString(0, strASDU);

	m_gridEx.InitGrid();
	m_gridEx.SetColumnWidth(1, m_gridEx.GetColumnWidth(1) - 10);
	m_gridEx.ShowDatas(m_pIecCfgSmvRates);
	return TRUE;
}

void CIECCfgExDlg::ClearClone()
{
	if (m_pIecCfgSmvRates)
	{
		delete m_pIecCfgSmvRates;
		m_pIecCfgSmvRates = NULL;
	}
}

BEGIN_MESSAGE_MAP(CIECCfgExDlg, CDialog)
END_MESSAGE_MAP()

void CIECCfgExDlg::OnOK()
{
	CString strRate;
	m_editRate.GetWindowText(strRate);
	CString strASDU;
	m_cbbASDU.GetWindowText(strASDU);
	m_pCommon->m_nAsduNum = CString_To_long(strASDU);
	m_pCommon->m_nBaudRate = CString_To_long(strRate);

	CDialog::OnOK();
}
