#include "StdAfx.h"
#include "ReportSNGen.h"
#include "TestTask.h"

#include "..\TCtrlCntrConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CReportSNGen::CReportSNGen(void)
{
	m_nReportSNGenIndex = 1;
	m_pDataset = NULL;
	m_pCurrTestProject = NULL;
	m_bUseReportSNGenIndex = FALSE;
	m_nReportIndex = 1;
}

CReportSNGen::~CReportSNGen(void)
{

}

long CReportSNGen::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetElementText(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strReportSNGenIndexKey,oNode,m_nReportSNGenIndex);
	xml_GetElementText(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strReportSNGenDateKey,oNode,m_strLastDate);

	return 0;
}

long CReportSNGen::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetElementText(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strReportSNGenIndexKey, oXMLDoc,oElement,m_nReportSNGenIndex);
	xml_SetElementText(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strReportSNGenDateKey, oXMLDoc,oElement,m_strLastDate);

	return 0;
}

BSTR CReportSNGen::GetXmlElementKey()
{
	return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strReportSNGenKey;
}


BOOL CReportSNGen::OpenConfigFile()
{
	CString strFile = GetReportSnGenFile();
	return OpenXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strReportSNGenKey, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
}

BOOL CReportSNGen::SaveConfigFile()
{
	CString strFile = GetReportSnGenFile();
	return SaveXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
}

CString CReportSNGen::GetReportSnGenFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile.AppendFormat(_T("%s_ReportSNGen.xml"), m_strMacroFileID);

	return strFile;
}

void CReportSNGen::ReportSNGen(CExBaseList &listProjects, CDvmDataset *pReportSNGen, const CString &strMacroFileID)
{
	m_strMacroFileID = strMacroFileID;

	if (m_strMacroFileID.GetLength() > 0)
	{
		OpenConfigFile();

		if (CTCtrlCntrConfig::IsFacBatchTestMode())
		{
			m_nReportSNGenIndex = 1;
		}

		ReportSNGen(listProjects, pReportSNGen);
		SaveConfigFile();
	}
	else
	{
		m_nReportSNGenIndex = 1;
		ReportSNGen(listProjects, pReportSNGen);
	}
}

void CReportSNGen::ReportSNGen(CExBaseList &listProjects, CDvmDataset *pReportSNGen)
{
	InitGenIndex();
	CString strReportSN;

	POS pos = listProjects.GetHeadPosition();
	CTestRrptSnGenInterface *pProject = NULL;
	//CTestTask *pTask = NULL;
	CString strFirstReportSN;

	while (pos != NULL)
	{
		pProject = (CTestRrptSnGenInterface *)listProjects.GetNext(pos);

		if (pProject->m_strReportSN.GetLength() > 0)
		{
			continue;
		}

		if (!pProject->CanGenSN())
		{
			continue;
		}
// 		pTask = (CTestTask *)pProject->GetParent();
// 
// 		if (pTask != NULL)
// 		{
// 			m_pDataset = pTask->GetDeviceAttr(FALSE);
// 		}

		m_pDataset = pProject->GetDeviceAttr(FALSE);
		m_bUseReportSNGenIndex = FALSE;
		m_pCurrTestProject = pProject;
		ReportSNGen(pReportSNGen, strReportSN);

		if (strFirstReportSN.GetLength() == 0)
		{
			strFirstReportSN = strReportSN;
		}

// 		pProject->m_strReportSN = strReportSN;
// 		pProject->m_strID = strReportSN;
// 		pProject->m_strLocalID = strReportSN;
// 		pProject->m_strLocation = GetPathFromFilePathName(pProject->m_strLocation);
// 		pProject->m_strLocation.AppendFormat(_T("%s.%s"), strReportSN, g_strGuideBookBinaryPostfix);
		pProject->SetReportSN(strReportSN);

		if (m_bUseReportSNGenIndex)
		{
			m_nReportSNGenIndex++;
		}
	}

	//2018-3-3
	//避免没有获得报告编号导致的ID相同而做的处理
	//做好的做法是逐一比较，后续改进
	pos = listProjects.GetHeadPosition();

	if (pos == NULL)
	{
		return;
	}

	listProjects.GetNext(pos);

	while (pos != NULL)
	{
		pProject = (CTestRrptSnGenInterface *)listProjects.GetNext(pos);

		if (pProject->m_strReportSN == strFirstReportSN)
		{
			strReportSN.Format(_T("%s%03d"), m_strLastDate, m_nReportSNGenIndex);
			m_nReportSNGenIndex++;
			strReportSN += pProject->m_strReportSN;
			pProject->SetReportSN(strReportSN);
		}
	}
}

void CReportSNGen::InitGenIndex()
{
	CString strTime;
	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	strTime.Format(_T("%d%02d%02d"), tm.wYear, tm.wMonth, tm.wDay);

	if (strTime != m_strLastDate)
	{
		m_strLastDate = strTime;
		m_nReportSNGenIndex = 1;
	}
}

void CReportSNGen::ReportSNGen(CDvmDataset *pRptSnGen, CString &strReportSN)
{
	strReportSN.Empty();

	if (pRptSnGen == NULL)
	{
		strReportSN.Format(_T("%s%03d"), m_strLastDate, m_nReportSNGenIndex);
		m_bUseReportSNGenIndex = TRUE;
		return;
	}

	POS pos = pRptSnGen->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	::GetLocalTime(&m_tmCurrReport);

	while (pos != NULL)
	{
		pDvmData = (CDvmData *)pRptSnGen->GetNext(pos);
		ReportSNGen(pDvmData, strReportSN);
	}

	//报告编号异常
	if (strReportSN.GetLength() == 0)
	{
		strReportSN.Format(_T("%s%03d"), m_strLastDate, m_nReportSNGenIndex);
		m_bUseReportSNGenIndex = TRUE;
	}
}

void CReportSNGen::ReportSNGen(CDvmData *pDvmData, CString &strReportSN)
{
	//时间参数
	if (pDvmData->m_strID == _T("Year"))
	{
		strReportSN += m_strLastDate.Left(4);
	}
	else if (pDvmData->m_strID == _T("Month"))
	{
		strReportSN += m_strLastDate.Mid(4, 2);
	}
	else if (pDvmData->m_strID == _T("Day"))
	{
		strReportSN += m_strLastDate.Right(2);
	}
	else if (pDvmData->m_strID == _T("Hour"))
	{
		strReportSN.AppendFormat(_T("%02d"), m_tmCurrReport.wHour);
	}
	else if (pDvmData->m_strID == _T("Minute"))
	{
		strReportSN.AppendFormat(_T("%02d"), m_tmCurrReport.wMinute);
	}
	else if (pDvmData->m_strID == _T("Second"))
	{
		strReportSN.AppendFormat(_T("%02d"), m_tmCurrReport.wSecond);
	}

	//编号和索引
	else if (pDvmData->m_strDataType == _T("index"))
	{
		if (pDvmData->m_strFormat.GetLength() > 3)
		{
			strReportSN.AppendFormat(pDvmData->m_strFormat, m_nReportSNGenIndex);
		}
		else
		{
			strReportSN.AppendFormat(_T("%03d"), m_nReportSNGenIndex);
		}

		m_bUseReportSNGenIndex = TRUE;
	}
	else if (pDvmData->m_strDataType == _T("rpt-idx"))
	{
		if (pDvmData->m_strFormat.GetLength() > 3)
		{
			strReportSN.AppendFormat(pDvmData->m_strFormat, m_nReportIndex);
		}
		else
		{
			strReportSN.AppendFormat(_T("%03d"), m_nReportIndex);
		}

		m_nReportIndex++;
	}

	//数据集
	else if (pDvmData->m_strDataType == _T("dataset"))
	{
		if (m_pDataset != NULL)
		{
			CDvmData *pGenData = (CDvmData*)m_pDataset->FindByID(pDvmData->m_strID);

			if (pGenData != NULL)
			{
				strReportSN += pGenData->m_strValue;
			}
		}
	}

	//模板及相关的文件
	else if (pDvmData->m_strDataType == _T("template-file"))
	{
		//strReportSN += ParseFileName(((CTestProject*)m_pCurrTestProject)->m_strTemplateFile);
		strReportSN += ParseFileName(m_pCurrTestProject->GetTemplateFile());
	}
	else if (pDvmData->m_strDataType == _T("dvm-file"))
	{
		//strReportSN += ParseFileName(((CTestProject*)m_pCurrTestProject)->m_strPpDeviceFile);
		strReportSN += ParseFileName(m_pCurrTestProject->GetPpDeviceFile());
	}
	else if (pDvmData->m_strDataType == _T("test-type"))
	{
		//strReportSN += ((CTestProject*)m_pCurrTestProject)->m_strTestType;
		strReportSN += m_pCurrTestProject->GetTestType();
	}

	//字符串
	else if (pDvmData->m_strDataType == _T("string"))
	{
		strReportSN += pDvmData->m_strValue;
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("ReportSNGen Error: [%s][%s] data type=[%s]"), pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType);
	}
}

