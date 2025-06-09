//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SetsFileXml_HashInfo.cpp  CSetsFileXml_HashInfo


#include "stdafx.h"
#include "SetsFileXml_HashInfo.h"
#include "..\..\..\..\..\Module\xml\XmlRW_Pugi.h"
#include "..\..\..\..\..\Module\xml\PugiXML\pugixml.hpp"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSetsFileXml_HashInfo::CSetsFileXml_HashInfo()
{
	//初始化属性
	m_nItemNum = 0;
	m_pNode = NULL;

	//初始化成员变量
}

CSetsFileXml_HashInfo::~CSetsFileXml_HashInfo()
{
}

long CSetsFileXml_HashInfo::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	CXmlRWNode_Pugi *pNode = (CXmlRWNode_Pugi *)&oNode;
	m_pNode = &(pNode->m_oPugiXmlNode);

	xml_GetAttibuteValue(pXmlKeys->m_strItemNumKey, oNode, m_nItemNum);
	return 0;
}

long CSetsFileXml_HashInfo::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strItemNumKey, oElement, m_nItemNum);
	return 0;
}

long CSetsFileXml_HashInfo::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSetsFileXml_HashInfo::InitAfterRead()
{
}

BOOL CSetsFileXml_HashInfo::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSetsFileXml_HashInfo *p = (CSetsFileXml_HashInfo*)pObj;

	if(m_nItemNum != p->m_nItemNum)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSetsFileXml_HashInfo::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSetsFileXml_HashInfo *p = (CSetsFileXml_HashInfo*)pDest;

	p->m_nItemNum = m_nItemNum;
	return TRUE;
}

CBaseObject* CSetsFileXml_HashInfo::Clone()
{
	CSetsFileXml_HashInfo *p = new CSetsFileXml_HashInfo();
	Copy(p);
	return p;
}

CBaseObject* CSetsFileXml_HashInfo::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSetsFileXml_HashInfo *p = new CSetsFileXml_HashInfo();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSetsFileXml_HashInfo::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSETSFILEXML_HI)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSetsFileXml_HashInfo::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSetsFileXml_HIKey)
	{
		pNew = new CSetsFileXml_HI();
	}

	return pNew;
}

CExBaseObject* CSetsFileXml_HashInfo::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSETSFILEXML_HI)
	{
		pNew = new CSetsFileXml_HI();
	}

	return pNew;
}

void CSetsFileXml_HashInfo::GetMd5_FromFile(const CString &strClass, CString &strMd5)
{
	CSetsFileXml_HI *pFind = FindHIByClass(strClass);

	if (pFind != NULL)
	{
		strMd5 = pFind->m_strmd5;
	}
}

CSetsFileXml_HI* CSetsFileXml_HashInfo::FindHIByClass(const CString &strClass)
{
	POS pos = GetHeadPosition();
	CSetsFileXml_HI *pFind = NULL;

	while (pos != NULL)
	{
		CSetsFileXml_HI *pHI = (CSetsFileXml_HI *)GetNext(pos);

		if (pHI->m_strClass == strClass)
		{
			pFind = pHI;
			break;
		}
	}

	return pFind;
}

void CSetsFileXml_HashInfo::SetItemNum(long nNum)
{
	m_nItemNum = nNum;

	if (m_pNode != NULL)
	{
		pugi::xml_attribute attr = m_pNode->attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strItemNumKey);
		attr.set_value(nNum);
	}
}

void CSetsFileXml_HashInfo::ClearAllXmlNode()
{
	if (m_pNode == NULL)
	{
		return;
	}

	pugi::xml_node nd = m_pNode->last_child();

	while (! nd.empty())
	{
		m_pNode->remove_child(nd);
		nd = m_pNode->last_child();
	}
}
