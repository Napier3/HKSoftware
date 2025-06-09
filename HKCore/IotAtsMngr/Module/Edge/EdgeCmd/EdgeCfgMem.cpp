//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeCfgMem.cpp  CEdgeCfgMem


#include "stdafx.h"
#include "EdgeCfgMem.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeCfgMem::CEdgeCfgMem()
{
	//初始化属性
	m_nMemory = 0;
	m_nMemLmt = 0;

	//初始化成员变量
}

CEdgeCfgMem::~CEdgeCfgMem()
{
}

long CEdgeCfgMem::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMemoryKey, oNode, m_nMemory);
	xml_GetAttibuteValue(pXmlKeys->m_strMemLmtKey, oNode, m_nMemLmt);

	AddErrorInfo(pXmlKeys->m_strMemoryKey, oNode, CJSON_Int);
	AddErrorInfo(pXmlKeys->m_strMemLmtKey, oNode, CJSON_Int);
	return 0;
}

long CEdgeCfgMem::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMemoryKey, oElement, m_nMemory);
	xml_SetAttributeValue(pXmlKeys->m_strMemLmtKey, oElement, m_nMemLmt);
	return 0;
}

long CEdgeCfgMem::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEdgeCfgMem::InitAfterRead()
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

BOOL CEdgeCfgMem::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeCfgMem *p = (CEdgeCfgMem*)pObj;

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

BOOL CEdgeCfgMem::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeCfgMem *p = (CEdgeCfgMem*)pDest;

	p->m_nMemory = m_nMemory;
	p->m_nMemLmt = m_nMemLmt;
	return TRUE;
}

CBaseObject* CEdgeCfgMem::Clone()
{
	CEdgeCfgMem *p = new CEdgeCfgMem();
	Copy(p);
	return p;
}

CBaseObject* CEdgeCfgMem::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeCfgMem *p = new CEdgeCfgMem();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeCfgMem::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeCfgMem::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeCfgMem::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
