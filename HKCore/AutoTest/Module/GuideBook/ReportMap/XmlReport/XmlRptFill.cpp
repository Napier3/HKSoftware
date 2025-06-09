#include "StdAfx.h"
#include "XmlRptFill.h"

CXmlRptFill::CXmlRptFill(void)
{
}

CXmlRptFill::~CXmlRptFill(void)
{
}

long CXmlRptFill::OpenRptTemplateFile(const CString &strReportFile)
{
	if (!IsFileExist(strReportFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("[%s] error!"), strReportFile.GetString());
		return FALSE;
	}

	m_oXmlDoc.load_file(strReportFile.GetString());
	return (m_oXmlDoc != NULL);
}

long CXmlRptFill::SaveRptFile(const CString &strRptFile)
{
	return m_oXmlDoc.save_file(strRptFile.GetString());
}

long CXmlRptFill::FillRpt(CGuideBook* pGuideBook)
{
	m_pGuideBook = pGuideBook;

	Cal(&m_oXmlDoc);

	return 0;
}

void CXmlRptFill::Cal(BDNode *xmlNode)
{	
	Cal_Attribute(xmlNode);

	BDNode cur = xmlNode->first_child();			
	while (cur && cur != *xmlNode)
	{
		Cal(&cur);

		cur = cur.next_sibling();
	}
}

void CXmlRptFill::Cal_Attribute(BDNode *xmlNode)
{
	BDAttB attrTmp = xmlNode->first_attribute();
	for (; attrTmp; attrTmp = attrTmp.next_attribute())
	{
		CString strKey(attrTmp.value());
		if(strKey == _T(""))
	{
			continue;
	}

		CValue *pValue = FindRptDataByPath(strKey);
		if (pValue == NULL)
	{
			continue;
		}

		wchar_t *pstr = pValue->m_strValue.AllocSysString();
		attrTmp.set_value(pstr);
	}
}
