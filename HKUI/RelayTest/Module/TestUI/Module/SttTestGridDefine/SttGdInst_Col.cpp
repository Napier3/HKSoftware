//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdInst_Col.cpp  CSttGdInst_Col


#include "stdafx.h"
#include "SttGdInst_Col.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdInst_Col::CSttGdInst_Col()
{
	//初始化属性

	//初始化成员变量
	m_pSttGdColDef_Ref = NULL;
}

CSttGdInst_Col::~CSttGdInst_Col()
{
}

long CSttGdInst_Col::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIdKey, oNode, m_strID);
	return 0;
}

long CSttGdInst_Col::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIdKey, oElement, m_strID);
	return 0;
}

long CSttGdInst_Col::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
	}
	return 0;
}

void CSttGdInst_Col::InitAfterRead()
{
}

BOOL CSttGdInst_Col::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttGdInst_Col *p = (CSttGdInst_Col*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttGdInst_Col::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttGdInst_Col *p = (CSttGdInst_Col*)pDest;

	p->m_strID = m_strID;
	return TRUE;
}

CBaseObject* CSttGdInst_Col::Clone()
{
	CSttGdInst_Col *p = new CSttGdInst_Col();
	Copy(p);
	return p;
}

CBaseObject* CSttGdInst_Col::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdInst_Col *p = new CSttGdInst_Col();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

