//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SetsFileXml_Val.cpp  CSetsFileXml_Val


#include "stdafx.h"
#include "SetsFileXml_Val.h"
#include "..\..\..\..\..\Module\xml\XmlRW_Pugi.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSetsFileXml_Val::CSetsFileXml_Val()
{
	//初始化属性
	//由于装置参数和压板数据集，是单区定值。没有定义定值区号；
	//此处需要将定值区号默认为0或-1；
	m_nGrp = 0;
	m_pNode = NULL;

	//初始化成员变量
}

CSetsFileXml_Val::~CSetsFileXml_Val()
{
}

long CSetsFileXml_Val::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	CXmlRWNode_Pugi *pNode = (CXmlRWNode_Pugi *)&oNode;
	m_pNode = &(pNode->m_oPugiXmlNode);

	xml_GetAttibuteValue(pXmlKeys->m_strGrpKey, oNode, m_nGrp);
	xml_GetCDATA(oNode, m_strVal);
	return 0;
}

long CSetsFileXml_Val::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	if (m_nGrp > 0)
	{
		xml_SetAttributeValue(pXmlKeys->m_strGrpKey, oElement, m_nGrp);
	}

	//xml_SetCDATA(oXMLDoc,oElement, m_strVal);
	xml_SetElementOwnText(NULL, oXMLDoc, oElement, m_strVal);
	return 0;
}

long CSetsFileXml_Val::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nGrp);
		BinarySerializeCalLen(oBinaryBuffer, m_strVal);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nGrp);
		BinarySerializeRead(oBinaryBuffer, m_strVal);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nGrp);
		BinarySerializeWrite(oBinaryBuffer, m_strVal);
	}
	return 0;
}

void CSetsFileXml_Val::InitAfterRead()
{
}

BOOL CSetsFileXml_Val::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSetsFileXml_Val *p = (CSetsFileXml_Val*)pObj;

	if(m_nGrp != p->m_nGrp)
	{
		return FALSE;
	}

	if(m_strVal != p->m_strVal)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSetsFileXml_Val::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSetsFileXml_Val *p = (CSetsFileXml_Val*)pDest;

	p->m_nGrp = m_nGrp;
	p->m_strVal = m_strVal;
	return TRUE;
}

CBaseObject* CSetsFileXml_Val::Clone()
{
	CSetsFileXml_Val *p = new CSetsFileXml_Val();
	Copy(p);
	return p;
}

CBaseObject* CSetsFileXml_Val::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSetsFileXml_Val *p = new CSetsFileXml_Val();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

void CSetsFileXml_Val::SetVal( const CString &strValue )
{
	m_strVal = strValue;

	m_dwReserved = 1;
	CExBaseObject *pSI = (CExBaseObject *)GetParent();
	pSI->m_dwReserved = 1;

	CExBaseObject* pInfoGrp = (CExBaseObject*)pSI->GetParent();
	pInfoGrp->m_dwReserved = 1;

	CExBaseObject* pSetting = (CExBaseObject*)pInfoGrp->GetParent();
	pSetting->m_dwReserved = 1;

	if (m_pNode != NULL)
	{
		wchar_t *pstr = strValue.AllocSysString();
		m_pNode->text().set(pstr);
		::SysFreeString(pstr);
	}
}

