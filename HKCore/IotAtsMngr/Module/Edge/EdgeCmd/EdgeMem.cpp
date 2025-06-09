//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeMem.cpp  CEdgeMem


#include "stdafx.h"
#include "EdgeMem.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeMem::CEdgeMem()
{
	//初始化属性
	m_nPhy = 0;
	m_nVirt = 0;
	m_nMemLmt = 0;

	//初始化成员变量
}

CEdgeMem::~CEdgeMem()
{
}

long CEdgeMem::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPhyKey, oNode, m_nPhy);
	xml_GetAttibuteValue(pXmlKeys->m_strVirtKey, oNode, m_nVirt);
	xml_GetAttibuteValue(pXmlKeys->m_strMemLmtKey, oNode, m_nMemLmt);

	AddErrorInfo(pXmlKeys->m_strPhyKey, oNode, CJSON_Int);
	AddErrorInfo(pXmlKeys->m_strVirtKey, oNode, CJSON_Int);
	AddErrorInfo(pXmlKeys->m_strMemLmtKey, oNode, CJSON_Int);
	return 0;
}

long CEdgeMem::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPhyKey, oElement, m_nPhy);
	xml_SetAttributeValue(pXmlKeys->m_strVirtKey, oElement, m_nVirt);
	xml_SetAttributeValue(pXmlKeys->m_strMemLmtKey, oElement, m_nMemLmt);
	return 0;
}

long CEdgeMem::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nPhy);
		BinarySerializeCalLen(oBinaryBuffer, m_nVirt);
		BinarySerializeCalLen(oBinaryBuffer, m_nMemLmt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nPhy);
		BinarySerializeRead(oBinaryBuffer, m_nVirt);
		BinarySerializeRead(oBinaryBuffer, m_nMemLmt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nPhy);
		BinarySerializeWrite(oBinaryBuffer, m_nVirt);
		BinarySerializeWrite(oBinaryBuffer, m_nMemLmt);
	}
	return 0;
}

void CEdgeMem::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pPhy = new CExBaseList;
	pPhy->m_strID = CEdgeCmdMngrXmlRWKeys::PhyKey();
	pPhy->m_strName.Format("%d", m_nPhy);
	AddNewChild(pPhy);

	CExBaseList* pVirt = new CExBaseList;
	pVirt->m_strID = CEdgeCmdMngrXmlRWKeys::VirtKey();
	pVirt->m_strName.Format("%d", m_nVirt);
	AddNewChild(pVirt);

	CExBaseList* pMemLmt = new CExBaseList;
	pMemLmt->m_strID = CEdgeCmdMngrXmlRWKeys::MemLmtKey();
	pMemLmt->m_strName.Format("%d", m_nMemLmt);
	AddNewChild(pMemLmt);
}

BOOL CEdgeMem::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeMem *p = (CEdgeMem*)pObj;

	if(m_nPhy != p->m_nPhy)
	{
		return FALSE;
	}

	if(m_nVirt != p->m_nVirt)
	{
		return FALSE;
	}

	if(m_nMemLmt != p->m_nMemLmt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeMem::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeMem *p = (CEdgeMem*)pDest;

	p->m_nPhy = m_nPhy;
	p->m_nVirt = m_nVirt;
	p->m_nMemLmt = m_nMemLmt;
	return TRUE;
}

CBaseObject* CEdgeMem::Clone()
{
	CEdgeMem *p = new CEdgeMem();
	Copy(p);
	return p;
}

CBaseObject* CEdgeMem::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeMem *p = new CEdgeMem();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeMem::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeMem::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeMem::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
