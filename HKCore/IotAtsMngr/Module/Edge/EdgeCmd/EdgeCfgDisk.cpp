//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeCfgMem.cpp  CEdgeCfgDisk


#include "stdafx.h"
#include "EdgeCfgDisk.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeCfgDisk::CEdgeCfgDisk()
{
	//初始化属性
	m_nDisk = 0;
	m_nDiskLmt = 0;

	//初始化成员变量
}

CEdgeCfgDisk::~CEdgeCfgDisk()
{
}

long CEdgeCfgDisk::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDiskKey, oNode, m_nDisk);
	xml_GetAttibuteValue(pXmlKeys->m_strDiskLmtKey, oNode, m_nDiskLmt);

	AddErrorInfo(pXmlKeys->m_strDiskKey, oNode, CJSON_Int);
	AddErrorInfo(pXmlKeys->m_strDiskLmtKey, oNode, CJSON_Int);

	return 0;
}

long CEdgeCfgDisk::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDiskKey, oElement, m_nDisk);
	xml_SetAttributeValue(pXmlKeys->m_strDiskLmtKey, oElement, m_nDiskLmt);
	return 0;
}

long CEdgeCfgDisk::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEdgeCfgDisk::InitAfterRead()
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

BOOL CEdgeCfgDisk::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeCfgDisk *p = (CEdgeCfgDisk*)pObj;

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

BOOL CEdgeCfgDisk::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeCfgDisk *p = (CEdgeCfgDisk*)pDest;

	p->m_nDisk = m_nDisk;
	p->m_nDiskLmt = m_nDiskLmt;
	return TRUE;
}

CBaseObject* CEdgeCfgDisk::Clone()
{
	CEdgeCfgDisk *p = new CEdgeCfgDisk();
	Copy(p);
	return p;
}

CBaseObject* CEdgeCfgDisk::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeCfgDisk *p = new CEdgeCfgDisk();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeCfgDisk::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeCfgDisk::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeCfgDisk::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
