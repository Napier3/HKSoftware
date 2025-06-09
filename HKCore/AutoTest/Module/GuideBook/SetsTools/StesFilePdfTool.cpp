#include "StdAfx.h"
#include "StesFilePdfTool.h"
#include "..\..\XLanguageResourceAts.h"

CStesFilePdfTool::CStesFilePdfTool(void)
{
	m_bCorrect = false;
}

CStesFilePdfTool::~CStesFilePdfTool(void)
{
	
}

//////////////////////////////////////////////////////////////////////////
//export functions
BOOL CStesFilePdfTool::ExportFile(const CString &strFile, LPDISPATCH lpDispatch)
{
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//import files
BOOL CStesFilePdfTool::ImportFile(const CString &strFile, LPDISPATCH lpDispatch)
{
	m_oLogicDeviceFile.DeleteAll();

	//20230716 huangliang 使用新解析对象
	m_oSetsParse.m_bCorrect = m_bCorrect;
	m_oSetsParse.m_pDestLogicDevice = &m_oLogicDeviceFile;

	//CPdfTextParseSets oSetsParse;
	//oSetsParse.AddDatasetTitle(SETS_TITLE_ID_PARAMETER);
	//oSetsParse.AddDatasetTitle(SETS_TITLE_ID_SETTING);
	//oSetsParse.AddDatasetTitle(SETS_TITLE_ID_ENA);
	////oSetsParse.AddDatasetTitle(SETS_TITLE_ID_CTRL);
	////oSetsParse.AddDatasetTitle(SETS_TITLE_ID_PROT);
	////oSetsParse.AddDatasetTitle(SETS_TITLE_ID_SETTING2);
	////oSetsParse.AddDatasetTitle(SETS_TITLE_ID_MATRIX);

	//oSetsParse.m_pDestLogicDevice = &m_oLogicDeviceFile;

	//oSetsParse.OpenKeyTextFile(_T("PdfToSetsKey.txt"));
	//oSetsParse.OpenInvalidKeyTextFile(_T("PdfToSetsInvalidKey.txt"));
	//oSetsParse.OpenFormatKeyTextFile(_T("PdfToSetsFormatKey.txt"));
	//oSetsParse.OpenMergeKeyTextFile(_T("PdfToSetsMergeKey.txt"));

	m_oSetsParse.ParsePdfFile(strFile);
	CString strTemp;
	strTemp = ChangeFilePostfix(strFile, _T("xml"));
	
	m_oLogicDeviceFile.SaveXmlFile(strTemp, CDataMngrXmlRWKeys::g_pXmlKeys);

	InitGbDataset();

	return FALSE;
}

void CStesFilePdfTool::SetManualConfirmInterface(CSetsFileManualConfirmInterface *pInterface)
{
	m_oSetsParse.m_pManualFrm = pInterface;
}