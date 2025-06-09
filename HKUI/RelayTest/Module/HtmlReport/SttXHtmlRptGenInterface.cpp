#include "SttXHtmlRptGenInterface.h"
#include "../UI/Webkit/SttReportViewHtml.h"

CSttXHtmlRptGenInterface::CSttXHtmlRptGenInterface()
{
	m_pHtmlBuffer = NULL;
	m_pReportView = NULL;
	m_pDataTypes = NULL;
}

CSttXHtmlRptGenInterface::~CSttXHtmlRptGenInterface()
{
 
}

void CSttXHtmlRptGenInterface::SetDataTypes(CDataTypes *pDataTypes)
{
	m_pDataTypes = pDataTypes;
}

void CSttXHtmlRptGenInterface::FillReport()  //向测试报告HTML文本中填测试参数
{

}

void CSttXHtmlRptGenInterface::InsertRptHtml()
{
	GenHtml();

	CString strParentPath = "";
	CString strItemsID = _P_GetMoudleFileName();
	char* pstrGbDatas = NULL;

	//20230217zhangyq
	m_pReportView->SetRptFileData((char*)m_pHtmlBuffer->GetDataBuffer());
	m_pReportView->InsertRptHtml(strParentPath,strItemsID,pstrGbDatas,"");
}

void CSttXHtmlRptGenInterface::UpdateRptHtml()
{
	m_pHtmlBuffer->PosMoveByUsedLen(HTML_BUFFER_SIZE_INIT);
	memset((char*)m_pHtmlBuffer->GetDataBuffer(), 0, HTML_BUFFER_SIZE_INIT);
	GenHtml();

	CString strParentPath = "";
	CString strItemsID = _P_GetMoudleFileName();
	char* pstrGbDatas = NULL;

	m_pReportView->SetRptFileData((char*)m_pHtmlBuffer->GetDataBuffer());
	//m_pReportView->UpdateRptHtml(strParentPath,strItemsID,strGbDatas);
	m_pReportView->DeleteRptHtml(strParentPath, strItemsID);
	m_pReportView->InsertRptHtml(strParentPath,strItemsID,pstrGbDatas,_T(""));
}
void CSttXHtmlRptGenInterface::OpenHead()  //打开报告头ReportHeader.html
{
	ASSERT(m_pReportView);
	if(m_pReportView == NULL)
	{
		return;
	}

	m_pReportView->OpenReportFile(STT_REPORT_HEAD_HTML_FILE);
}

void CSttXHtmlRptGenInterface::FillHead()  //使用ReportHead_Paras.xml填充报告头html
{
	CString strReportHeaderCfg;
	strReportHeaderCfg = _P_GetDBPath();
	strReportHeaderCfg += "atsgen/";
	strReportHeaderCfg += ("ReportHead_Paras.xml");

	CDataGroup oReportHeader_Paras;

	dvm_IncGroupUseDvmData(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oReportHeader_Paras.OpenXmlFile(strReportHeaderCfg,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	dvm_DecGroupUseDvmData(CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	if(m_pReportView)
	{
		((QSttReportViewHtml*)m_pReportView)->UpdateReportHead( &oReportHeader_Paras );
	}
}

//生成测试报告HTML文本
void CSttXHtmlRptGenInterface::GenHtml() 
{
	
}

void CSttXHtmlRptGenInterface::FillReportData(const CString &strParentItemsPath, const CString &strItemID, const CString &strState, char *pszReport)
{
	m_pReportView->FillReportData(strParentItemsPath, strItemID, strState, pszReport);
}


//////////////////////////////////////////////////////////////////////////
void CSttXHtmlRptGenInterface::GenModule_RootDiv(const CString &strModuleID)
{
	GenModule_RootDiv(strModuleID.GetString());
}

void CSttXHtmlRptGenInterface::GenModule_Table_th(const CString &strModuleID)
{
	GenModule_Table_th(strModuleID.GetString());
}
void CSttXHtmlRptGenInterface::GenModule_RootDiv(const char *strModuleID)
{
	m_pHtmlBuffer->AppendString("<div id=\"");
	m_pHtmlBuffer->AppendString(strModuleID);
	m_pHtmlBuffer->AppendString("\" class=\"stt_rpt\"");
	m_pHtmlBuffer->AppendString(" type=\"stt_items\">");
}

void CSttXHtmlRptGenInterface::GenModule_Table_th(const char *strModuleID)
{
	m_pHtmlBuffer->AppendString("<table id=\"");
	m_pHtmlBuffer->AppendString(strModuleID);
	m_pHtmlBuffer->AppendString("_Table\"");

	m_pHtmlBuffer->AppendString(" border=\"1\"");
	m_pHtmlBuffer->AppendString(" cellspacing=\"0\"");
	m_pHtmlBuffer->AppendString(" cellpadding=\"0\"");

	m_pHtmlBuffer->AppendString(" type=\"stt_table\" style=\"text-align:center;\">");

}

void CSttXHtmlRptGenInterface::GenModule_Table_th(CDataGroup *pColsTitle, BOOL bUseIndex)
{
	if (pColsTitle == NULL)
	{
		return;
	}

	POS pos = pColsTitle->GetHeadPosition();
	CDvmData *pData = NULL;
	m_pHtmlBuffer->AppendString("<tr>");

	if (bUseIndex)
	{
		m_pHtmlBuffer->AppendString("<th>编号</th>");
	}

	while (pos)
	{
		pData = (CDvmData*)pColsTitle->GetNext(pos);
		m_pHtmlBuffer->AppendString("<th>");
		m_pHtmlBuffer->AppendString(pData->m_strName.GetString());
		m_pHtmlBuffer->AppendString("</th>");
	}

	m_pHtmlBuffer->AppendString("</tr>");
}

void CSttXHtmlRptGenInterface::Gen_Table_th(const char *pszColTitle)
{
	m_pHtmlBuffer->AppendString("<th>");
	m_pHtmlBuffer->AppendString(pszColTitle);
	m_pHtmlBuffer->AppendString("</th>");
}

void CSttXHtmlRptGenInterface::Gen_Table_td(const char *pszColTitle)
{
	m_pHtmlBuffer->AppendString("<td>");
	m_pHtmlBuffer->AppendString(pszColTitle);
	m_pHtmlBuffer->AppendString("</td>");
}

void CSttXHtmlRptGenInterface::Gen_Table_td(float fValue, long ndecimal)
{
	char pszValue[32];
	switch (ndecimal)
	{
	case 1:
		sprintf(pszValue, "%.1f", fValue);
		break;
	case 2:
		sprintf(pszValue, "%.2f", fValue);
		break;
	case 3:
		sprintf(pszValue, "%.3f", fValue);
		break;
	case 4:
		sprintf(pszValue, "%.4f", fValue);
		break;

	default:
		sprintf(pszValue, "%f", fValue);
		break;
	}

	Gen_Table_td(pszValue);
}

void CSttXHtmlRptGenInterface::Gen_Table_td(CString strValue, long ndecimal)
{
	char pszValue[32];

	if ((strValue=="inf")||(strValue=="nan"))
	{
		strcpy(pszValue, "---");
	} 
	else
	{
		double dValue = CString_To_double(strValue);
		switch (ndecimal)
		{
		case 1:
			sprintf(pszValue, "%.01lf", dValue);
			break;
		case 2:
			sprintf(pszValue, "%.02lf", dValue);
			break;
		case 3:
			sprintf(pszValue, "%.03lf", dValue);
			break;

		default:
			sprintf(pszValue, "%lf", dValue);
			break;
		}
	}

	Gen_Table_td(pszValue);
}

void CSttXHtmlRptGenInterface::Gen_Table_td(long nValue)
{
	char pszValue[32];
	sprintf(pszValue, "%d", nValue);
	Gen_Table_td(pszValue);
}

void CSttXHtmlRptGenInterface::GenModule_Table_th(const char *strModuleID, CDataGroup *pColsTitle, BOOL bUseIndex)
{
	GenModule_Table_th(strModuleID);
	GenModule_Table_th(pColsTitle, TRUE);
}

void CSttXHtmlRptGenInterface::GenModule_Table_th(const CString &strModuleID, CDataGroup *pColsTitle, BOOL bUseIndex)
{
	GenModule_Table_th(strModuleID.GetString());
	GenModule_Table_th(pColsTitle, TRUE);
}

void CSttXHtmlRptGenInterface::GenModule_Table_te()
{
	m_pHtmlBuffer->AppendString("</table>");
}



//////////////////////////////////////////////////////////////////////////
void CSttXHtmlRptGenInterface::FormatDataValue(CDvmData *pData, long nDecimal)
{
	if (pData == NULL)
	{
		return;
	}

	double d = CString_To_double(pData->m_strValue);

	switch (nDecimal)
	{
	case 1:
		pData->m_strValue.Format(_T("%.1f"), d);
		break;

	case 2:
		pData->m_strValue.Format(_T("%.2f"), d);
		break;

	case 3:
		pData->m_strValue.Format(_T("%.3f"), d);
		break;

	case 4:
		pData->m_strValue.Format(_T("%.4f"), d);
		break;

	case 5:
		pData->m_strValue.Format(_T("%.5f"), d);
		break;

	case 6:
		pData->m_strValue.Format(_T("%.6f"), d);
		break;
	}
}

void CSttXHtmlRptGenInterface::FormatDataValue(CDataGroup *pDatas, const CString &strDataID, long nDecimal)
{
	CDvmData* pData = (CDvmData*)pDatas->FindByID(strDataID);
	FormatDataValue(pData, nDecimal);
}

void CSttXHtmlRptGenInterface::FormatDataValue(CDvmData *pData, const CString &strDataTypeID)
{
	if (pData == NULL)
	{
		return;
	}

	if (m_pDataTypes == NULL)
	{
		return;
	}

	CDataType *pDataType = (CDataType*)m_pDataTypes->FindByID(strDataTypeID);

	if (pDataType == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("FormatDataValue : [%s] >> datatype[%s] error")
			, pData->m_strID.GetString(), strDataTypeID.GetString());
		return;
	}

	CDataTypeValue *pVal = pDataType->FindByIndex(pData->m_strValue);

	if (pVal != NULL)
	{
		pData->m_strValue = pVal->m_strName;
	}
}

void CSttXHtmlRptGenInterface::FormatDataValue(CDataGroup *pDatas, const CString &strDataID, const CString &strDataTypeID)
{
	CDvmData *pData = (CDvmData*)pDatas->FindByID(strDataID);
	FormatDataValue(pData, strDataTypeID);
}

CString CSttXHtmlRptGenInterface::GetDataValueString(CDvmValue *pValue, const CString &strDataTypeID)
{
	if ((pValue == NULL)||(m_pDataTypes == NULL))
	{
		return _T("");
	}

	CDataType *pDataType = (CDataType*)m_pDataTypes->FindByID(strDataTypeID);

	if (pDataType == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("GetDataValueString : [%s] >> datatype[%s] error")
			, pValue->m_strID.GetString(), strDataTypeID.GetString());
		return pValue->m_strValue;
	}

	CDataTypeValue *pVal = pDataType->FindByIndex(pValue->m_strValue);

	if (pVal == NULL)
	{
		return pValue->m_strValue;
	}

	return pVal->m_strName;
}

void CSttXHtmlRptGenInterface::ShowData_td_ByDataType(CDvmData *pData, const CString &strChildID, const CString &strDataType)
{
	CString strID;
	strID = pData->m_strID + "$" + strChildID;
	CDvmValue *pValue = (CDvmValue *)pData->FindByID(strID);

	if (pValue == NULL)
	{
		return;
	}

	CString strTmp;
	strTmp = GetDataValueString(pValue,strDataType);
	Gen_Table_td(strTmp.GetString());
}

void CSttXHtmlRptGenInterface::ShowData_td_ByDataType(CDvmData *pData, const CString &strChildID1, const CString &strChildID2,
													  const CString &strDataType)
{
	CString strID;
	strID = pData->m_strID + "$" + strChildID1;
	CDvmValue *pValue = (CDvmValue *)pData->FindByID(strID);

	if (pValue == NULL)
	{
		return;
	}

	strID.AppendFormat(_T("$%s"),strChildID2.GetString());
	CDvmValue *pAttr = (CDvmValue *)pValue->FindByID(strID);

	if (pAttr == NULL)
	{
		return;
	}

	CString strTmp;
	strTmp = GetDataValueString(pAttr,strDataType);
	Gen_Table_td(strTmp.GetString());
}

void CSttXHtmlRptGenInterface::ShowData_td_ByDataType(long nIndex ,const CString &strDataType)
{
	if (m_pDataTypes == NULL)
	{
		return;
	}

	CDataType *pDataType = (CDataType*)m_pDataTypes->FindByID(strDataType);

	if (pDataType == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("ShowData_td_ByDataType : datatype[%s] error")
			,  strDataType.GetString());
		return;
	}

	CString strTmp;
	CDataTypeValue *pVal = pDataType->FindByIndex(nIndex);

	if (pVal != NULL)
	{
		strTmp = pVal->m_strName;
	}
	else
	{
		strTmp.Format(_T("%ld"),nIndex);
	}

	Gen_Table_td(strTmp.GetString());
}
