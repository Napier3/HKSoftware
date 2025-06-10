// VerUpdateHisVer.cpp : 实现文件
//

#include "stdafx.h"
#include "VerUpdateHisVer.h"

// CVerUpdateHisVer

CVerUpdateHisVer::CVerUpdateHisVer()
{
	//初始化属性
	m_nCurrVerIdx = 0;
	m_nPrevVerIdx = 0;
}

CVerUpdateHisVer::~CVerUpdateHisVer()
{
}

long CVerUpdateHisVer::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateHisXmlRWKeys *pXmlKeys = (CVerUpdateHisXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strDateTimeKey, oNode, m_strDateTime);
	xml_GetAttibuteValue(pXmlKeys->m_strCurrVerIdxKey, oNode, m_nCurrVerIdx);
	xml_GetAttibuteValue(pXmlKeys->m_strPrevVerIdxKey, oNode, m_nPrevVerIdx);
	xml_GetAttibuteValue(pXmlKeys->m_strCurrVerKey, oNode, m_strCurrVer);
	xml_GetAttibuteValue(pXmlKeys->m_strPrevVerKey, oNode, m_strPrevVer);
	return 0;
}

long CVerUpdateHisVer::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateHisXmlRWKeys *pXmlKeys = (CVerUpdateHisXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strDateTimeKey, oElement, m_strDateTime);
	xml_SetAttributeValue(pXmlKeys->m_strCurrVerIdxKey, oElement, m_nCurrVerIdx);
	xml_SetAttributeValue(pXmlKeys->m_strPrevVerIdxKey, oElement, m_nPrevVerIdx);
	xml_SetAttributeValue(pXmlKeys->m_strCurrVerKey, oElement, m_strCurrVer);
	xml_SetAttributeValue(pXmlKeys->m_strPrevVerKey, oElement, m_strPrevVer);

	return 0;
}

long CVerUpdateHisVer::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDateTime);
		BinarySerializeCalLen(oBinaryBuffer, m_nCurrVerIdx);
		BinarySerializeCalLen(oBinaryBuffer, m_nPrevVerIdx);
		BinarySerializeCalLen(oBinaryBuffer, m_strCurrVer);
		BinarySerializeCalLen(oBinaryBuffer, m_strPrevVer);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDateTime);
		BinarySerializeRead(oBinaryBuffer, m_nCurrVerIdx);
		BinarySerializeRead(oBinaryBuffer, m_nPrevVerIdx);
		BinarySerializeRead(oBinaryBuffer, m_strCurrVer);
		BinarySerializeRead(oBinaryBuffer, m_strPrevVer);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDateTime);
		BinarySerializeWrite(oBinaryBuffer, m_nCurrVerIdx);
		BinarySerializeWrite(oBinaryBuffer, m_nPrevVerIdx);
		BinarySerializeWrite(oBinaryBuffer, m_strCurrVer);
		BinarySerializeWrite(oBinaryBuffer, m_strPrevVer);
	}
	return 0;
}

BOOL CVerUpdateHisVer::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CVerUpdateHisVer *p = (CVerUpdateHisVer*)pObj;

	if(m_strDateTime != p->m_strDateTime)
	{
		return FALSE;
	}

	if(m_nCurrVerIdx != p->m_nCurrVerIdx)
	{
		return FALSE;
	}

	if(m_nPrevVerIdx != p->m_nPrevVerIdx)
	{
		return FALSE;
	}

	if(m_strCurrVer != p->m_strCurrVer)
	{
		return FALSE;
	}

	if(m_strPrevVer != p->m_strPrevVer)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CVerUpdateHisVer::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CVerUpdateHisVer *p = (CVerUpdateHisVer*)pDest;
	p->m_strDateTime = m_strDateTime;
	p->m_nCurrVerIdx = m_nCurrVerIdx;
	p->m_nPrevVerIdx = m_nPrevVerIdx;
	p->m_strCurrVer = m_strCurrVer;
	p->m_strPrevVer = m_strPrevVer;

	return TRUE;
}

CBaseObject* CVerUpdateHisVer::CloneEx(BOOL bCopyOwn,BOOL bCopyChildren)
{
	CExBaseObject *pNew = new CVerUpdateHisVer();

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

void CVerUpdateHisVer::Init(int nLocalVerIdx,int nDestVerIdx,const CString& strLocalVer,const CString& strDestVer,const CString& strDateTime)
{
	if (strDateTime == _T(""))
	{
		CTime t = CTime::GetCurrentTime();
		m_strDateTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
	}
	else
	{
		m_strDateTime = strDateTime;
	}

	m_nCurrVerIdx = nDestVerIdx;
	m_nPrevVerIdx = nLocalVerIdx;
	m_strCurrVer = strDestVer;
	m_strPrevVer = strLocalVer;
}