//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeMemLmt.cpp  CEdgeMemLmt


#include "stdafx.h"
#include "EdgeMemLmt.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeMemLmt::CEdgeMemLmt()
{
	//初始化属性
	m_nMemory = 0;
	m_nMemLmt = 0;

	//初始化成员变量
}

CEdgeMemLmt::~CEdgeMemLmt()
{
}

long CEdgeMemLmt::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMemoryKey, oNode, m_nMemory);
	xml_GetAttibuteValue(pXmlKeys->m_strMemLmtKey, oNode, m_nMemLmt);
	return 0;
}

long CEdgeMemLmt::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMemoryKey, oElement, m_nMemory);
	xml_SetAttributeValue(pXmlKeys->m_strMemLmtKey, oElement, m_nMemLmt);
	return 0;
}

long CEdgeMemLmt::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nMemory);
		BinarySerializeCalLen(oBinaryBuffer, m_nMemLmt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nMemory);
		BinarySerializeRead(oBinaryBuffer, m_nMemLmt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nMemory);
		BinarySerializeWrite(oBinaryBuffer, m_nMemLmt);
	}
	return 0;
}

void CEdgeMemLmt::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pUnit = new CExBaseList;
	pUnit->m_strID = CEdgeCmdMngrXmlRWKeys::MemoryKey();
	pUnit->m_strName.Format("%d", m_nMemory);
	AddNewChild(pUnit);

	CExBaseList* pLmt = new CExBaseList;
	pLmt->m_strID = CEdgeCmdMngrXmlRWKeys::MemLmtKey();
	pLmt->m_strName.Format("%d", m_nMemLmt);
	AddNewChild(pLmt);
}

BOOL CEdgeMemLmt::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeMemLmt *p = (CEdgeMemLmt*)pObj;

	if(m_nMemory != p->m_nMemory)
	{
		return FALSE;
	}

	if(m_nMemLmt != p->m_nMemLmt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeMemLmt::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeMemLmt *p = (CEdgeMemLmt*)pDest;

	p->m_nMemory = m_nMemory;
	p->m_nMemLmt = m_nMemLmt;
	return TRUE;
}

CBaseObject* CEdgeMemLmt::Clone()
{
	CEdgeMemLmt *p = new CEdgeMemLmt();
	Copy(p);
	return p;
}

CBaseObject* CEdgeMemLmt::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeMemLmt *p = new CEdgeMemLmt();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeMemLmt::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeMemLmt::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeMemLmt::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
