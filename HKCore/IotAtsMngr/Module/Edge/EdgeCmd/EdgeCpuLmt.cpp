//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeCpuLmt.cpp  CEdgeCpuLmt


#include "stdafx.h"
#include "EdgeCpuLmt.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeCpuLmt::CEdgeCpuLmt()
{
	//初始化属性
	m_nCpus = 0;
	m_nCpuLmt = 0;

	//初始化成员变量
}

CEdgeCpuLmt::~CEdgeCpuLmt()
{
}

long CEdgeCpuLmt::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCpusKey, oNode, m_nCpus);
	xml_GetAttibuteValue(pXmlKeys->m_strLmtKey, oNode, m_nCpuLmt);
	return 0;
}

long CEdgeCpuLmt::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCpusKey, oElement, m_nCpus);
	xml_SetAttributeValue(pXmlKeys->m_strLmtKey, oElement, m_nCpuLmt);
	return 0;
}

long CEdgeCpuLmt::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nCpus);
		BinarySerializeCalLen(oBinaryBuffer, m_nCpuLmt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nCpus);
		BinarySerializeRead(oBinaryBuffer, m_nCpuLmt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nCpus);
		BinarySerializeWrite(oBinaryBuffer, m_nCpuLmt);
	}
	return 0;
}

void CEdgeCpuLmt::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pCpus = new CExBaseList;
	pCpus->m_strID = CEdgeCmdMngrXmlRWKeys::CpusKey();
	pCpus->m_strName.Format("%d", m_nCpus);
	AddNewChild(pCpus);

	CExBaseList* pLmt = new CExBaseList;
	pLmt->m_strID = CEdgeCmdMngrXmlRWKeys::CpuLmtKey();
	pLmt->m_strName.Format("%d", m_nCpuLmt);
	AddNewChild(pLmt);
}

BOOL CEdgeCpuLmt::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeCpuLmt *p = (CEdgeCpuLmt*)pObj;

	if(m_nCpus != p->m_nCpus)
	{
		return FALSE;
	}

	if(m_nCpuLmt != p->m_nCpuLmt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeCpuLmt::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeCpuLmt *p = (CEdgeCpuLmt*)pDest;

	p->m_nCpus = m_nCpus;
	p->m_nCpuLmt = m_nCpuLmt;
	return TRUE;
}

CBaseObject* CEdgeCpuLmt::Clone()
{
	CEdgeCpuLmt *p = new CEdgeCpuLmt();
	Copy(p);
	return p;
}

CBaseObject* CEdgeCpuLmt::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeCpuLmt *p = new CEdgeCpuLmt();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeCpuLmt::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeCpuLmt::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeCpuLmt::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
