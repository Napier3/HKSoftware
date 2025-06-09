//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeSign.cpp  CEdgeSign


#include "stdafx.h"
#include "EdgeSign.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeSign::CEdgeSign()
{
	//初始化属性
	m_nSize = -1;
	//初始化成员变量
}

CEdgeSign::~CEdgeSign()
{
}

long CEdgeSign::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strUrlKey, oNode, m_strUrl);
	xml_GetAttibuteValue(pXmlKeys->m_strMd5Key, oNode, m_strMd5);
	xml_GetAttibuteValue(pXmlKeys->m_strSizeKey, oNode, m_nSize);
	return 0;
}

long CEdgeSign::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	if(m_strName.GetLength())
		xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	if(m_strUrl.GetLength())
		xml_SetAttributeValue(pXmlKeys->m_strUrlKey, oElement, m_strUrl);
	if(m_strMd5.GetLength())
		xml_SetAttributeValue(pXmlKeys->m_strMd5Key, oElement, m_strMd5);
	if(m_nSize >= 0)
		xml_SetAttributeValue(pXmlKeys->m_strSizeKey, oElement, m_nSize);
	return 0;
}

long CEdgeSign::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strUrl);
		BinarySerializeCalLen(oBinaryBuffer, m_strMd5);
		BinarySerializeCalLen(oBinaryBuffer, m_nSize);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strUrl);
		BinarySerializeRead(oBinaryBuffer, m_strMd5);
		BinarySerializeRead(oBinaryBuffer, m_nSize);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strUrl);
		BinarySerializeWrite(oBinaryBuffer, m_strMd5);
		BinarySerializeWrite(oBinaryBuffer, m_nSize);
	}
	return 0;
}

void CEdgeSign::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pName = new CExBaseList;
	pName->m_strID = _T("name");
	pName->m_strName = m_strName;
	AddNewChild(pName);

	CExBaseList* pUrl = new CExBaseList;
	pUrl->m_strID = CEdgeCmdMngrXmlRWKeys::UrlKey();
	pUrl->m_strName = m_strUrl;
	AddNewChild(pUrl);

	CExBaseList* pMd5 = new CExBaseList;
	pMd5->m_strID = CEdgeCmdMngrXmlRWKeys::Md5Key();
	pMd5->m_strName = m_strMd5;
	AddNewChild(pMd5);

	CExBaseList* pSize = new CExBaseList;
	pSize->m_strID = CEdgeCmdMngrXmlRWKeys::SizeKey();
	pSize->m_strName.Format("%d", m_nSize);
	AddNewChild(pSize);
}

BOOL CEdgeSign::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeSign *p = (CEdgeSign*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strUrl != p->m_strUrl)
	{
		return FALSE;
	}

	if(m_strMd5 != p->m_strMd5)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeSign::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeSign *p = (CEdgeSign*)pDest;

	p->m_strName = m_strName;
	p->m_strUrl = m_strUrl;
	p->m_strMd5 = m_strMd5;
	return TRUE;
}

CBaseObject* CEdgeSign::Clone()
{
	CEdgeSign *p = new CEdgeSign();
	Copy(p);
	return p;
}

CBaseObject* CEdgeSign::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeSign *p = new CEdgeSign();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeSign::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeSign::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeSign::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
