#include "StdAfx.h"
#include "TestTasksMngrExcel.h"

#include "..\..\..\Module\Office\ExcelReadWrite.h"
#include "..\..\..\Module\QRCode\QRCodeRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CTestTasksMngrExcelTool
const CString CTestTasksMngrExcelTool::g_strExcelFileFilter = _T("Excel File (*.xls;*.xlsx)|*.xls;*.xlsx|Excel File (*.xls)|*.xls|Excel File (*.xlsx)|*.xlsx||");

CTestTasksMngrExcelTool::CTestTasksMngrExcelTool()
{
	m_strDvIDKey = _T("ID");
}

CTestTasksMngrExcelTool::~CTestTasksMngrExcelTool()
{
	
}

BOOL CTestTasksMngrExcelTool::PopupOpenFileDialog_Excel(CWnd *pParentWnd, CString &strFile)
{
	return PopupOpenFileDialog(pParentWnd, strFile, g_strExcelFileFilter, _T("xls"));
}

BOOL CTestTasksMngrExcelTool::PopupSaveFileDialog_Excel(CWnd *pParentWnd, CString &strFile)
{
	return PopupSaveAsFileDialog(pParentWnd, strFile, g_strExcelFileFilter, _T("xls"));
}

BOOL CTestTasksMngrExcelTool::ImportFromExcel(CTestTasksMngr *pTestTasksMngr, const CString &strExcelFile)
{
	pTestTasksMngr->m_strTasksMngrSrcFile = strExcelFile;
	CQRCodeRead::Create();
	CQRCodeRead::InitQRCodeReadParser('=', ';');
	CExcelReadWrite oExcel;
	long nRow = 1;
	CString strValue;
	CDvmDataset *pNewDvmDs = NULL;
	CDvmData *pData = NULL;

	try
	{
		if (!oExcel.InitExcel())
		{
			return FALSE;
		}

		oExcel.ShowInExcel(FALSE);

		if (!oExcel.OpenExcelFile(strExcelFile))
		{
			return FALSE;
		}

		oExcel.LoadSheet(1, TRUE);
		strValue = oExcel.GetCellString(nRow, 1);
		CQRCodeRead::ValidateSepChars(strValue);

		while (TRUE)
		{
			strValue = oExcel.GetCellString(nRow, 1);

			if (strValue.GetLength() <= 5)
			{
				break;
			}

			pNewDvmDs = new CDvmDataset();
			CQRCodeRead::InputQRCodeString(strValue);
			CQRCodeRead::NewDatas(pNewDvmDs);
#ifdef USE_IN_XTESTDB_XTU_
			long nTmp = oExcel.GetColumnCount();

			if (nTmp >= 5)
			{
				strValue = oExcel.GetCellString(nRow, 2);
				pData = pNewDvmDs->AddNewData();
				pData->m_strID = _TestTasksExcel_TitleID_ChannelNum;
				pData->m_strName = _T("间隔数");
				pData->m_strValue = strValue;
				strValue = oExcel.GetCellString(nRow, 3);
				pData = pNewDvmDs->AddNewData();
				pData->m_strID = _TestTasksExcel_TitleID_CityCompany;
				pData->m_strName = _T("市公司");
				pData->m_strValue = strValue;
				strValue = oExcel.GetCellString(nRow, 4);
				pData = pNewDvmDs->AddNewData();
				pData->m_strID = _TestTasksExcel_TitleID_CountyCompany;
				pData->m_strName = _T("县公司");
				pData->m_strValue = strValue;
				strValue = oExcel.GetCellString(nRow, 5);
				pData = pNewDvmDs->AddNewData();
				pData->m_strID = _TestTasksExcel_TitleID_ProjectName;
				pData->m_strName = _T("项目名称");
				pData->m_strValue = strValue;

				pData = pNewDvmDs->AddNewData();
				pData->m_strID = _TestTasksExcel_TitleID_SoftwareVersion;
				pData->m_strName = _T("软件版本号");
				pData->m_strValue = _T("");

				pData = pNewDvmDs->AddNewData();
				pData->m_strID = _TestTasksExcel_TitleID_TestDate;
				pData->m_strName = _T("检测日期");
				SYSTEMTIME tm;
				::GetLocalTime(&tm);
				strValue.Format(_T("%04d.%02d.%02d"),tm.wYear,tm.wMonth,tm.wDay);
				pData->m_strValue = strValue;
			}
#endif

			pTestTasksMngr->AddNewChild(pNewDvmDs);
			pData = (CDvmData*)pNewDvmDs->FindByID(m_strDvIDKey);

			if (pData != NULL)
			{
				pNewDvmDs->m_strName = pData->m_strValue;
				pNewDvmDs->m_strID = pData->m_strValue;
			}

			nRow++;
		}
	}
	catch (...)
	{
		
	}

	CQRCodeRead::Release();

	return FALSE;
}

CTestTasksMngr* CTestTasksMngrExcelTool::ImportFromExcel(const CString &strExcelFile)
{
	CTestTasksMngr *pCTestTasksMngr = new CTestTasksMngr();

	ImportFromExcel(pCTestTasksMngr, strExcelFile);
	
	return pCTestTasksMngr;
}

