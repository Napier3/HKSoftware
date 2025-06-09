//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdColDef_Para.cpp  CSttGdColDef_Para


#include "stdafx.h"
#include "SttGdColDef_Para.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdColDef_Para::CSttGdColDef_Para()
{
	//初始化属性
	m_nIsRlt = 0;

	//初始化成员变量
}

CSttGdColDef_Para::~CSttGdColDef_Para()
{
}

long CSttGdColDef_Para::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIs_RltKey, oNode, m_nIsRlt);
	return 0;
}

long CSttGdColDef_Para::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIs_RltKey, oElement, m_nIsRlt);
	return 0;
}

long CSttGdColDef_Para::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIsRlt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIsRlt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIsRlt);
	}
	return 0;
}

void CSttGdColDef_Para::InitAfterRead()
{
}

BOOL CSttGdColDef_Para::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttGdColDef_Para *p = (CSttGdColDef_Para*)pObj;

	if(m_nIsRlt != p->m_nIsRlt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttGdColDef_Para::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttGdColDef_Para *p = (CSttGdColDef_Para*)pDest;

	p->m_nIsRlt = m_nIsRlt;
	return TRUE;
}

CBaseObject* CSttGdColDef_Para::Clone()
{
	CSttGdColDef_Para *p = new CSttGdColDef_Para();
	Copy(p);
	return p;
}

CBaseObject* CSttGdColDef_Para::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdColDef_Para *p = new CSttGdColDef_Para();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

