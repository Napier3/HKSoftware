//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptBatchConfig.cpp  CRptBatchConfig


#include "stdafx.h"
#include "RptBatchConfig.h"

CRptBatchConfig::CRptBatchConfig()
{
	//初始化属性
	m_nMode = RPTBATCH_MODE_ROWITEM_COLDATA;

	//初始化成员变量
	m_pDataMaps = NULL;
	m_pItemMaps = NULL;
}

CRptBatchConfig::~CRptBatchConfig()
{
}

long CRptBatchConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CRptBkmkBatchAddXmlRWKeys *pXmlKeys = (CRptBkmkBatchAddXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strModeKey, oNode, m_nMode);
	return 0;
}

long CRptBatchConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CRptBkmkBatchAddXmlRWKeys *pXmlKeys = (CRptBkmkBatchAddXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strModeKey, oElement, m_nMode);
	return 0;
}

CExBaseObject* CRptBatchConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CRptBkmkBatchAddXmlRWKeys *pXmlKeys = (CRptBkmkBatchAddXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptBatchDataMapsKey)
	{
		pNew = new CRptBatchDataMaps();
	}
	else if (strClassID == pXmlKeys->m_strCRptBatchItemMapsKey)
	{
		pNew = new CRptBatchItemMaps();
	}

	return pNew;
}

CExBaseObject* CRptBatchConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == RBACLASSID_CRPTBATCHDATAMAPS)
	{
		pNew = new CRptBatchDataMaps();
	}
	else if (nClassID == RBACLASSID_CRPTBATCHITEMMAPS)
	{
		pNew = new CRptBatchItemMaps();
	}

	return pNew;
}
void CRptBatchConfig::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == RBACLASSID_CRPTBATCHDATAMAPS)
		{
			m_pDataMaps = (CRptBatchDataMaps*)p;
		}
		else if (nClassID == RBACLASSID_CRPTBATCHITEMMAPS)
		{
			m_pItemMaps = (CRptBatchItemMaps*)p;
		}
	}

	if (m_pDataMaps == NULL)
	{
		m_pDataMaps = (CRptBatchDataMaps*)AddNewChild(new CRptBatchDataMaps());
	}

	if (m_pItemMaps == NULL)
	{
		m_pItemMaps = (CRptBatchItemMaps*)AddNewChild(new CRptBatchItemMaps());
	}

}

void CRptBatchConfig::ClearMaps()
{
	m_pDataMaps->ClearMaps();
	m_pItemMaps->ClearMaps();
}


CString wzd_GetRptBatchFilePath()
{
	CString strPath;

	strPath = _P_GetLibraryPath();
	strPath += _T("RptBatchConfigFiles\\");
	return strPath;
}

CString wzd_GetRptBatchFileDlgFilter()
{
	CString strFilter;
	strFilter.Format(_T("%s|(*.%s)||"), g_strRptBatchFileName, g_strRptBatchFilePostFix);
	return strFilter;
}

