// SttNativeCfgHisVer.cpp
//

#include "stdafx.h"
#include "SttNativeCfgLiveUpdate.h"

// CSttNativeCfgHisVer

CSttNativeCfgHisVer::CSttNativeCfgHisVer()
{
	//³õÊ¼»¯ÊôÐÔ
	m_nCurrVerIdx = 0;
	m_nPrevVerIdx = 0;
	m_strCurrVer = _T("");
	m_strPrevVer = _T("");
	m_nUpdateDeviceXml = 0;
}

CSttNativeCfgHisVer::~CSttNativeCfgHisVer()
{
}

long CSttNativeCfgHisVer::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateHisXmlRWKeys *pXmlKeys = (CVerUpdateHisXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDateTimeKey, oNode, m_strDateTime);
	xml_GetAttibuteValue(pXmlKeys->m_strCurrVerIdxKey, oNode, m_nCurrVerIdx);
	xml_GetAttibuteValue(pXmlKeys->m_strPrevVerIdxKey, oNode, m_nPrevVerIdx);
	xml_GetAttibuteValue(pXmlKeys->m_strCurrVerKey, oNode, m_strCurrVer);
	xml_GetAttibuteValue(pXmlKeys->m_strPrevVerKey, oNode, m_strPrevVer);
	xml_GetAttibuteValue(CSttNativeCfgXmlRWKeys::UpdateDeviceXmlKey(), oNode, m_nUpdateDeviceXml);

	return 0;
}

long CSttNativeCfgHisVer::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateHisXmlRWKeys *pXmlKeys = (CVerUpdateHisXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDateTimeKey, oElement, m_strDateTime);
	xml_SetAttributeValue(pXmlKeys->m_strCurrVerIdxKey, oElement, m_nCurrVerIdx);
	xml_SetAttributeValue(pXmlKeys->m_strPrevVerIdxKey, oElement, m_nPrevVerIdx);
	xml_SetAttributeValue(pXmlKeys->m_strCurrVerKey, oElement, m_strCurrVer);
	xml_SetAttributeValue(pXmlKeys->m_strPrevVerKey, oElement, m_strPrevVer);
	xml_SetAttributeValue(CSttNativeCfgXmlRWKeys::UpdateDeviceXmlKey(), oElement, m_nUpdateDeviceXml);
	
	return 0;
}

long CSttNativeCfgHisVer::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDateTime);
		BinarySerializeCalLen(oBinaryBuffer, m_nCurrVerIdx);
		BinarySerializeCalLen(oBinaryBuffer, m_nPrevVerIdx);
		BinarySerializeCalLen(oBinaryBuffer, m_strCurrVer);
		BinarySerializeCalLen(oBinaryBuffer, m_strPrevVer);
		BinarySerializeCalLen(oBinaryBuffer, m_nUpdateDeviceXml);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDateTime);
		BinarySerializeRead(oBinaryBuffer, m_nCurrVerIdx);
		BinarySerializeRead(oBinaryBuffer, m_nPrevVerIdx);
		BinarySerializeRead(oBinaryBuffer, m_strCurrVer);
		BinarySerializeRead(oBinaryBuffer, m_strPrevVer);
		BinarySerializeRead(oBinaryBuffer, m_nUpdateDeviceXml);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDateTime);
		BinarySerializeWrite(oBinaryBuffer, m_nCurrVerIdx);
		BinarySerializeWrite(oBinaryBuffer, m_nPrevVerIdx);
		BinarySerializeWrite(oBinaryBuffer, m_strCurrVer);
		BinarySerializeWrite(oBinaryBuffer, m_nUpdateDeviceXml);
		
	}

	return 0;
}

BOOL CSttNativeCfgHisVer::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttNativeCfgHisVer *p = (CSttNativeCfgHisVer*)pDest;
	p->m_strDateTime = m_strDateTime;
	p->m_nCurrVerIdx = m_nPrevVerIdx;
	p->m_nPrevVerIdx = m_nCurrVerIdx;
	p->m_strCurrVer = m_strCurrVer;
	p->m_strPrevVer = m_strPrevVer;
	p->m_nUpdateDeviceXml = m_nUpdateDeviceXml;

	return TRUE;
}

CBaseObject* CSttNativeCfgHisVer::CloneEx(BOOL bCopyOwn,BOOL bCopyChildren)
{
	CExBaseObject *pNew = new CSttNativeCfgHisVer();

	if(bCopyOwn)
	{
		CopyOwn(pNew);
	}
	if(bCopyChildren)
	{
		CopyChildren(pNew);
	}	

	return pNew;
}