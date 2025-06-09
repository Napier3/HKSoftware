//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SetsFileXml_DevInfo.cpp  CSetsFileXml_DevInfo


#include "stdafx.h"
#include "SetsFileXml_DevInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSetsFileXml_DevInfo::CSetsFileXml_DevInfo()
{
	//初始化属性
	m_nItemNum = 0;

	//初始化成员变量
}

CSetsFileXml_DevInfo::~CSetsFileXml_DevInfo()
{
}

long CSetsFileXml_DevInfo::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strItemNumKey, oNode, m_nItemNum);
	return 0;
}

long CSetsFileXml_DevInfo::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strItemNumKey, oElement, m_nItemNum);
	return 0;
}

long CSetsFileXml_DevInfo::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nItemNum);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nItemNum);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nItemNum);
	}
	return 0;
}

void CSetsFileXml_DevInfo::InitAfterRead()
{
}

BOOL CSetsFileXml_DevInfo::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSetsFileXml_DevInfo *p = (CSetsFileXml_DevInfo*)pObj;

	if(m_nItemNum != p->m_nItemNum)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSetsFileXml_DevInfo::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSetsFileXml_DevInfo *p = (CSetsFileXml_DevInfo*)pDest;

	p->m_nItemNum = m_nItemNum;
	return TRUE;
}

CBaseObject* CSetsFileXml_DevInfo::Clone()
{
	CSetsFileXml_DevInfo *p = new CSetsFileXml_DevInfo();
	Copy(p);
	return p;
}

CBaseObject* CSetsFileXml_DevInfo::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSetsFileXml_DevInfo *p = new CSetsFileXml_DevInfo();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSetsFileXml_DevInfo::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSETSFILEXML_DI)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSetsFileXml_DevInfo::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSetsFileXml_DIKey)
	{
		pNew = new CSetsFileXml_DI();
	}

	return pNew;
}

CExBaseObject* CSetsFileXml_DevInfo::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSETSFILEXML_DI)
	{
		pNew = new CSetsFileXml_DI();
	}

	return pNew;
}
