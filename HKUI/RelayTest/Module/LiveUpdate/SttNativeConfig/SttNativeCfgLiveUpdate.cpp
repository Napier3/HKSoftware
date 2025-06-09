// SttNativeCfgLiveUpdate.cpp
//

#include "stdafx.h"
#include "SttNativeCfgLiveUpdate.h"

// CSttNativeCfgLiveUpdate

CSttNativeCfgLiveUpdate::CSttNativeCfgLiveUpdate()
{
	//初始化属性
	m_pCfgHisVer = NULL;
}

CSttNativeCfgLiveUpdate::~CSttNativeCfgLiveUpdate()
{
}

long CSttNativeCfgLiveUpdate::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttNativeCfgXmlRWKeys *pXmlKeys = (CSttNativeCfgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strID_SystemKey, oNode, m_strID_System);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_SystemKey, oNode, m_nIndex_System);

	return 0;
}

long CSttNativeCfgLiveUpdate::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttNativeCfgXmlRWKeys *pXmlKeys = (CSttNativeCfgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strID_SystemKey, oElement, m_strID_System);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_SystemKey, oElement, m_nIndex_System);

	return 0;
}

long CSttNativeCfgLiveUpdate::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID_System);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_System);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID_System);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_System);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID_System);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_System);
	}

	return 0;
}

CExBaseObject* CSttNativeCfgLiveUpdate::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttNativeCfgXmlRWKeys *pXmlKeys = (CSttNativeCfgXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strHisVerKey)
	{
		pNew = new CSttNativeCfgHisVer();
	}

	return pNew;
}

CExBaseObject* CSttNativeCfgLiveUpdate::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == STTNATIVECFGCLASSID_HISVER)
	{
		pNew = new CSttNativeCfgHisVer();
	}
	
	return pNew;
}

void CSttNativeCfgLiveUpdate::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == STTNATIVECFGCLASSID_HISVER)
		{
			m_pCfgHisVer = (CSttNativeCfgHisVer*)p;
		}
	}

	if (m_pCfgHisVer == NULL)
	{
		m_pCfgHisVer = (CSttNativeCfgHisVer*)AddNewChild(new CSttNativeCfgHisVer());
	}

	//清空所有的历史记录，只保留最后一条记录
	pos = GetHeadPosition();
	while (pos != NULL)
	{
		p = GetNext(pos);
		if (p)
		{
			if (p==m_pCfgHisVer)
			{
				continue;
			}
			
			Delete(p);
		}
	}
}

void CSttNativeCfgLiveUpdate::UpdateHisVer(const CString& strDateTime,int nIndex_Sys,int nCurrVerIdx,const CString& strCurVer)
{
	m_pCfgHisVer->m_strDateTime = strDateTime;

	m_nIndex_System = nIndex_Sys;

	m_pCfgHisVer->m_nPrevVerIdx = m_pCfgHisVer->m_nCurrVerIdx;
	m_pCfgHisVer->m_nCurrVerIdx = nCurrVerIdx;
	
	m_pCfgHisVer->m_strPrevVer = m_pCfgHisVer->m_strCurrVer;
	m_pCfgHisVer->m_strCurrVer = strCurVer;

	m_pCfgHisVer->m_nUpdateDeviceXml = 1;
}
