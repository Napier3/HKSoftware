//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeOs.cpp  CEdgeOs


#include "stdafx.h"
#include "EdgeOs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeOs::CEdgeOs()
{
	//初始化属性

	//初始化成员变量
}

CEdgeOs::~CEdgeOs()
{
}

long CEdgeOs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDistroKey, oNode, m_strDistro);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_strVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strKernelKey, oNode, m_strKernel);
	xml_GetAttibuteValue(pXmlKeys->m_strSoftVersionKey, oNode, m_strSoftVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strPatchVersionKey, oNode, m_strPatchVersion);

	AddErrorInfo(pXmlKeys->m_strDistroKey, oNode, CJSON_String);
	AddErrorInfo(pXmlKeys->m_strVersionKey, oNode, CJSON_String);
	AddErrorInfo(pXmlKeys->m_strKernelKey, oNode, CJSON_String);
	AddErrorInfo(pXmlKeys->m_strSoftVersionKey, oNode, CJSON_String);
	AddErrorInfo(pXmlKeys->m_strPatchVersionKey, oNode, CJSON_String);
	return 0;
}

long CEdgeOs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDistroKey, oElement, m_strDistro);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_strVersion);
	xml_SetAttributeValue(pXmlKeys->m_strKernelKey, oElement, m_strKernel);
	xml_SetAttributeValue(pXmlKeys->m_strSoftVersionKey, oElement, m_strSoftVersion);
	xml_SetAttributeValue(pXmlKeys->m_strPatchVersionKey, oElement, m_strPatchVersion);
	return 0;
}

long CEdgeOs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDistro);
		BinarySerializeCalLen(oBinaryBuffer, m_strVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strKernel);
		BinarySerializeCalLen(oBinaryBuffer, m_strSoftVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strPatchVersion);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDistro);
		BinarySerializeRead(oBinaryBuffer, m_strVersion);
		BinarySerializeRead(oBinaryBuffer, m_strKernel);
		BinarySerializeRead(oBinaryBuffer, m_strSoftVersion);
		BinarySerializeRead(oBinaryBuffer, m_strPatchVersion);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDistro);
		BinarySerializeWrite(oBinaryBuffer, m_strVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strKernel);
		BinarySerializeWrite(oBinaryBuffer, m_strSoftVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strPatchVersion);
	}
	return 0;
}

void CEdgeOs::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pDistro = new CExBaseList;
	pDistro->m_strID = CEdgeCmdMngrXmlRWKeys::DistroKey();
	pDistro->m_strName = m_strDistro;
	AddNewChild(pDistro);

	CExBaseList* pVersion = new CExBaseList;
	pVersion->m_strID = CEdgeCmdMngrXmlRWKeys::VersionKey();
	pVersion->m_strName = m_strVersion;
	AddNewChild(pVersion);

	CExBaseList* pKernel = new CExBaseList;
	pKernel->m_strID = CEdgeCmdMngrXmlRWKeys::KernelKey();
	pKernel->m_strName = m_strKernel;
	AddNewChild(pKernel);

	CExBaseList* pSoftVersion = new CExBaseList;
	pSoftVersion->m_strID = CEdgeCmdMngrXmlRWKeys::SoftVersionKey();
	pSoftVersion->m_strName = m_strSoftVersion;
	AddNewChild(pSoftVersion);

	CExBaseList* pPatchVersion = new CExBaseList;
	pPatchVersion->m_strID = CEdgeCmdMngrXmlRWKeys::PatchVersionKey();
	pPatchVersion->m_strName = m_strPatchVersion;
	AddNewChild(pPatchVersion);
}

BOOL CEdgeOs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeOs *p = (CEdgeOs*)pObj;

	if(m_strDistro != p->m_strDistro)
	{
		return FALSE;
	}

	if(m_strVersion != p->m_strVersion)
	{
		return FALSE;
	}

	if(m_strKernel != p->m_strKernel)
	{
		return FALSE;
	}

	if(m_strSoftVersion != p->m_strSoftVersion)
	{
		return FALSE;
	}

	if(m_strPatchVersion != p->m_strPatchVersion)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeOs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeOs *p = (CEdgeOs*)pDest;

	p->m_strDistro = m_strDistro;
	p->m_strVersion = m_strVersion;
	p->m_strKernel = m_strKernel;
	p->m_strSoftVersion = m_strSoftVersion;
	p->m_strPatchVersion = m_strPatchVersion;
	return TRUE;
}

CBaseObject* CEdgeOs::Clone()
{
	CEdgeOs *p = new CEdgeOs();
	Copy(p);
	return p;
}

CBaseObject* CEdgeOs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeOs *p = new CEdgeOs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeOs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeOs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeOs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
