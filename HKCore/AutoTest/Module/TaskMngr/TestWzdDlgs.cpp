#include "StdAfx.h"
#include "TestWzdDlgs.h"

#include "..\..\..\Module\DataMngr\DataMngrTrans.h"
#include "..\..\..\Module\API\GloblaDrawFunctions.h"

#include "..\..\..\Module\XLanguage\XLanguageResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CTestWzdDvHistory
CTestWzdDvHistory::CTestWzdDvHistory()
{
	m_pTestAppHis = NULL;
	m_pDeviceAttrHis = NULL;
}

CTestWzdDvHistory::~CTestWzdDvHistory()
{

}

void CTestWzdDvHistory::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CDvmLogicDevice *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmLogicDevice *)GetNext(pos);

		if (p->m_strID == DSID_TESTAPP)
		{
			m_pTestAppHis = p;
		}
		else if (p->m_strID == DSID_DEVICEATTR)
		{
			m_pDeviceAttrHis = p;
		}
	}

	if (m_pTestAppHis == NULL)
	{
		m_pTestAppHis = new CDvmLogicDevice();
		m_pTestAppHis->m_strID = DSID_TESTAPP;
		m_pTestAppHis->m_strName = DSID_TESTAPP;
		AddNewChild(m_pTestAppHis);
	}

	if (m_pDeviceAttrHis == NULL)
	{
		m_pDeviceAttrHis = new CDvmLogicDevice();
		m_pDeviceAttrHis->m_strID = DSID_DEVICEATTR;
		m_pDeviceAttrHis->m_strName = DSID_DEVICEATTR;
		AddNewChild(m_pDeviceAttrHis);
	}
}

void CTestWzdDvHistory::OpenHisFile()
{
	CString strFile = GetHisFile();
	BOOL bRet = OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	if (!bRet)
	{
		InitAfterRead();
		SaveHisFile();
	}
}

void CTestWzdDvHistory::SaveHisFile()
{
	CString strFile = GetHisFile();
	SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

CString CTestWzdDvHistory::GetHisFile()
{
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("TestWzdDvHis.xml");

	return strFile;
}

//////////////////////////////////////////////////////////////////////////
//CTestWzdDeviceEditGrid
#define TESTWZD_DEVICE_GRID_COLS   4

CTestWzdDeviceEditGrid::CTestWzdDeviceEditGrid()
{

}

CTestWzdDeviceEditGrid::~CTestWzdDeviceEditGrid()
{

}

void CTestWzdDeviceEditGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(TESTWZD_DEVICE_GRID_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CTestWzdDeviceEditGrid::InitGridTitle()
{
	CString astrGridTitle[TESTWZD_DEVICE_GRID_COLS] = {/*_T("编号")*/g_sLangTxt_Index
		,/*_T("名称")*/g_sLangTxt_Name
		, _T("ID")
		,g_sLangTxt_Data
	};

	int iGridWidth[TESTWZD_DEVICE_GRID_COLS]={50, 140, 100, 250};

	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, TESTWZD_DEVICE_GRID_COLS);
}

void CTestWzdDeviceEditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pWzdData = (CDvmData*)pData;

	Show_Index(pWzdData, nRow, 0);
	Show_StaticString(pWzdData, nRow, 1, &pWzdData->m_strName);
	Show_StaticString(pWzdData, nRow, 2, &pWzdData->m_strID);
	Show_String(pWzdData, nRow, 3, &pWzdData->m_strValue);

	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CTestWzdDeviceEditDlg
#define IDC_TESTWZD_CMB_HISTORY           1616
#define IDC_TESTWZD_DEVICE_EDIT_GRID   1617

CTestWzdDeviceEditDlg::CTestWzdDeviceEditDlg(CWnd* pParent)
{
	m_pTestWzdDvHis = NULL;
	m_pTestWzdDeviceDef = NULL;
	m_oTestWzdDvHistory.OpenHisFile();
}

CTestWzdDeviceEditDlg::~CTestWzdDeviceEditDlg()
{
	
}


void CTestWzdDeviceEditDlg::EnableOkButton()
{
	
}

void CTestWzdDeviceEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);

	if (!m_bHasInitDialog)
	{
		return;
	}

	//DDX_Text(pDX, XFIDC_EDIT_IECFGFILE, m_strIecfgFile);
}


BEGIN_MESSAGE_MAP(CTestWzdDeviceEditDlg, CDynDialogEx)
	ON_CBN_SELCHANGE(IDC_TESTWZD_CMB_HISTORY, &CTestWzdDeviceEditDlg::OnCbnSelchangeCmbHistory)
END_MESSAGE_MAP()


void CTestWzdDeviceEditDlg::OnCbnSelchangeCmbHistory()
{
	CExBaseObject *pDvmObj = m_cmbHishory.GetSelectObject();
	OnCmbHistoryChanged(pDvmObj);
}

BOOL CTestWzdDeviceEditDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();


	CreateComboBox_DropList(m_cmbHishory,   CRect(10, 10, 580, 430), IDC_TESTWZD_CMB_HISTORY, this);
	
	m_gridTestWzdDeviceEdit.Create(CRect(10, 40, 580, 240), this, IDC_TESTWZD_DEVICE_EDIT_GRID);
	m_gridTestWzdDeviceEdit.InitGrid();

	CreateButton(m_btnOK,_T("确定"),     CRect(210,250,282,273), IDOK, this);
	CreateButton(m_btnCancel,_T("取消"), CRect(291,250,363,273), IDCANCEL, this);

	CFont *pFont = g_pGlobalFont;
	m_cmbHishory.SetFont(pFont);
	m_gridTestWzdDeviceEdit.SetFont(pFont);
	m_btnOK.SetFont(pFont);
	m_btnCancel.SetFont(pFont);

	MoveWindow(CRect( 0, 0, 600, 310), TRUE);
	CenterWindow();
	SetWindowText(m_strTestWzdTitle);
	ASSERT (m_pTestWzdDeviceDef != NULL);
	m_oTestWzdDevice.AppendCloneEx(*m_pTestWzdDeviceDef);

	if ( (m_pTestWzdDeviceDef->m_strID == DSID_TESTAPP_DEF)
		|| (m_pTestWzdDeviceDef->m_strID == DSID_TESTAPP) )
	{
		m_pTestWzdDvHis = m_oTestWzdDvHistory.m_pTestAppHis;
		SetWindowText(_T("录入测试仪信息"));
	}
	else if ( m_pTestWzdDeviceDef->m_strID == DSID_DEVICEATTR)
	{
		m_pTestWzdDvHis = m_oTestWzdDvHistory.m_pDeviceAttrHis;
		SetWindowText(_T("录入被测装置信息"));
	}

	if (m_pTestWzdDvHis != NULL)
	{
		m_pTestWzdDvHis->InsertChildreComboBox(&m_cmbHishory);
		//m_cmbHishory.SetCurSel(0);
		//OnCmbHistoryChanged(m_pTestWzdDvHis->GetHead());
	}
	
	m_gridTestWzdDeviceEdit.ShowDatas(&m_oTestWzdDevice);
	UpdateData(FALSE);
	EnableOkButton();

	return TRUE;
}

void CTestWzdDeviceEditDlg::OnOK()
{
	SaveHisFile();

	CDynDialogEx::OnOK();
}

void CTestWzdDeviceEditDlg::OnCmbHistoryChanged(CExBaseObject *pDvObj)
{
	if (pDvObj != NULL)
	{
		CDvmDataset *pDataset = (CDvmDataset*)pDvObj;
		m_oTestWzdDevice.InitValue(pDataset);
	}

	m_gridTestWzdDeviceEdit.ShowDatas(&m_oTestWzdDevice);
}

void CTestWzdDeviceEditDlg::SaveHisFile()
{
	CDvmDataset *pFind = dvm_FindDsByDatas(m_pTestWzdDvHis, &m_oTestWzdDevice);

	if (pFind != NULL)
	{
		return;
	}

	pFind = (CDvmDataset*)m_oTestWzdDevice.Clone();
	CDvmData *pData = (CDvmData*)pFind->FindByID(_T("Name"));

	if (pData != NULL)
	{
		pFind->m_strName = pData->m_strValue;
	}

	pData = (CDvmData*)pFind->FindByID(_T("Model"));

	if (pData != NULL)
	{
		if (pFind->m_strName.GetLength() > 0)
		{
			pFind->m_strName.AppendFormat(_T("[%s]"), pData->m_strValue);
		}
		else
		{
			pFind->m_strName = pData->m_strValue;
		}
	}

	pData = (CDvmData*)pFind->FindByID(_T("SN"));

	if (pData != NULL)
	{
		pFind->m_strID = pData->m_strValue;
	}

	m_pTestWzdDvHis->AddNewChild(pFind);

	m_oTestWzdDvHistory.SaveHisFile();
}