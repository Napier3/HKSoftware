//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeMemUsed.cpp  CEdgeMemUsed


#include "stdafx.h"
#include "EdgeMemUsed.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeMemUsed::CEdgeMemUsed()
{
	//初始化属性
	m_nPhy = 0;
	m_nVirt = 0;

	//初始化成员变量
}

CEdgeMemUsed::~CEdgeMemUsed()
{
}

long CEdgeMemUsed::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPhyKey, oNode, m_nPhy);
	xml_GetAttibuteValue(pXmlKeys->m_strVirtKey, oNode, m_nVirt);

	AddErrorInfo(pXmlKeys->m_strPhyKey, oNode, CJSON_Int);
	AddErrorInfo(pXmlKeys->m_strVirtKey, oNode, CJSON_Int);

	return 0;
}

long CEdgeMemUsed::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPhyKey, oElement, m_nPhy);
	xml_SetAttributeValue(pXmlKeys->m_strVirtKey, oElement, m_nVirt);
	return 0;
}

long CEdgeMemUsed::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nPhy);
		BinarySerializeCalLen(oBinaryBuffer, m_nVirt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nPhy);
		BinarySerializeRead(oBinaryBuffer, m_nVirt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nPhy);
		BinarySerializeWrite(oBinaryBuffer, m_nVirt);
	}
	return 0;
}

void CEdgeMemUsed::InitAfterRead()
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
}

BOOL CEdgeMemUsed::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeMemUsed *p = (CEdgeMemUsed*)pObj;

	if(m_nPhy != p->m_nPhy)
	{
		return FALSE;
	}

	if(m_nVirt != p->m_nVirt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeMemUsed::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeMemUsed *p = (CEdgeMemUsed*)pDest;

	p->m_nPhy = m_nPhy;
	p->m_nVirt = m_nVirt;
	return TRUE;
}

CBaseObject* CEdgeMemUsed::Clone()
{
	CEdgeMemUsed *p = new CEdgeMemUsed();
	Copy(p);
	return p;
}

CBaseObject* CEdgeMemUsed::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeMemUsed *p = new CEdgeMemUsed();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeMemUsed::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeMemUsed::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeMemUsed::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
