//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeDisk.cpp  CEdgeDisk


#include "stdafx.h"
#include "EdgeDisk.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeDisk::CEdgeDisk()
{
	//初始化属性
	m_nDisk = 0;
	m_nDiskLmt = 0;

	//初始化成员变量
}

CEdgeDisk::~CEdgeDisk()
{
}

long CEdgeDisk::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDiskKey, oNode, m_nDisk);
	xml_GetAttibuteValue(pXmlKeys->m_strDiskLmtKey, oNode, m_nDiskLmt);

	AddErrorInfo(pXmlKeys->m_strDiskKey, oNode, CJSON_Int);
	AddErrorInfo(pXmlKeys->m_strDiskLmtKey, oNode, CJSON_Int);
	return 0;
}

long CEdgeDisk::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDiskKey, oElement, m_nDisk);
	xml_SetAttributeValue(pXmlKeys->m_strDiskLmtKey, oElement, m_nDiskLmt);
	return 0;
}

long CEdgeDisk::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEdgeDisk::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pDisk = new CExBaseList;
	pDisk->m_strID = CEdgeCmdMngrXmlRWKeys::DiskKey();
	pDisk->m_strName.Format("%d", m_nDisk);
	AddNewChild(pDisk);

	CExBaseList* pDiskLmt = new CExBaseList;
	pDiskLmt->m_strID = CEdgeCmdMngrXmlRWKeys::DiskLmtKey();
	pDiskLmt->m_strName.Format("%d", m_nDiskLmt);
	AddNewChild(pDiskLmt);
}

BOOL CEdgeDisk::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeDisk *p = (CEdgeDisk*)pObj;

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

BOOL CEdgeDisk::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeDisk *p = (CEdgeDisk*)pDest;

	p->m_nDisk = m_nDisk;
	p->m_nDiskLmt = m_nDiskLmt;
	return TRUE;
}

CBaseObject* CEdgeDisk::Clone()
{
	CEdgeDisk *p = new CEdgeDisk();
	Copy(p);
	return p;
}

CBaseObject* CEdgeDisk::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeDisk *p = new CEdgeDisk();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeDisk::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeDisk::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeDisk::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
