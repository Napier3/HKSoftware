//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeDiskLmt.cpp  CEdgeDiskLmt


#include "stdafx.h"
#include "EdgeDiskLmt.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeDiskLmt::CEdgeDiskLmt()
{
	//初始化属性
	m_nDisk = 0;
	m_nDiskLmt = 0;

	//初始化成员变量
}

CEdgeDiskLmt::~CEdgeDiskLmt()
{
}

long CEdgeDiskLmt::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDiskKey, oNode, m_nDisk);
	xml_GetAttibuteValue(pXmlKeys->m_strDiskLmtKey, oNode, m_nDiskLmt);
	return 0;
}

long CEdgeDiskLmt::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDiskKey, oElement, m_nDisk);
	xml_SetAttributeValue(pXmlKeys->m_strDiskLmtKey, oElement, m_nDiskLmt);
	return 0;
}

long CEdgeDiskLmt::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nDisk);
		BinarySerializeCalLen(oBinaryBuffer, m_nDiskLmt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nDisk);
		BinarySerializeRead(oBinaryBuffer, m_nDiskLmt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nDisk);
		BinarySerializeWrite(oBinaryBuffer, m_nDiskLmt);
	}
	return 0;
}

void CEdgeDiskLmt::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pUnit = new CExBaseList;
	pUnit->m_strID = CEdgeCmdMngrXmlRWKeys::DiskKey();
	pUnit->m_strName.Format("%d", m_nDisk);
	AddNewChild(pUnit);

	CExBaseList* pLmt = new CExBaseList;
	pLmt->m_strID = CEdgeCmdMngrXmlRWKeys::DiskLmtKey();
	pLmt->m_strName.Format("%d", m_nDiskLmt);
	AddNewChild(pLmt);
}

BOOL CEdgeDiskLmt::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeDiskLmt *p = (CEdgeDiskLmt*)pObj;

	if(m_nDisk != p->m_nDisk)
	{
		return FALSE;
	}

	if(m_nDiskLmt != p->m_nDiskLmt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeDiskLmt::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeDiskLmt *p = (CEdgeDiskLmt*)pDest;

	p->m_nDisk = m_nDisk;
	p->m_nDiskLmt = m_nDiskLmt;
	return TRUE;
}

CBaseObject* CEdgeDiskLmt::Clone()
{
	CEdgeDiskLmt *p = new CEdgeDiskLmt();
	Copy(p);
	return p;
}

CBaseObject* CEdgeDiskLmt::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeDiskLmt *p = new CEdgeDiskLmt();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeDiskLmt::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeDiskLmt::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeDiskLmt::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
