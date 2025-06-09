//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeDev.cpp  CEdgeDev


#include "stdafx.h"
#include "EdgeDev.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeDev::CEdgeDev()
{
	//初始化属性

	//初始化成员变量
}

CEdgeDev::~CEdgeDev()
{
}

long CEdgeDev::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strHardVersionKey, oNode, m_strHardVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strDevTypeKey, oNode, m_strDevType);
	xml_GetAttibuteValue(pXmlKeys->m_strDevNameKey, oNode, m_strDevName);
	xml_GetAttibuteValue(pXmlKeys->m_strMfgInfoKey, oNode, m_strMfgInfo);
	xml_GetAttibuteValue(pXmlKeys->m_strDevStatusKey, oNode, m_strDevStatus);

	AddErrorInfo(pXmlKeys->m_strHardVersionKey, oNode, CJSON_String);
	AddErrorInfo(pXmlKeys->m_strDevTypeKey, oNode, CJSON_String);
	AddErrorInfo(pXmlKeys->m_strDevNameKey, oNode, CJSON_String);
	AddErrorInfo(pXmlKeys->m_strMfgInfoKey, oNode, CJSON_String);
	AddErrorInfo(pXmlKeys->m_strDevStatusKey, oNode, CJSON_String);

	return 0;
}

long CEdgeDev::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strHardVersionKey, oElement, m_strHardVersion);
	xml_SetAttributeValue(pXmlKeys->m_strDevTypeKey, oElement, m_strDevType);
	xml_SetAttributeValue(pXmlKeys->m_strDevNameKey, oElement, m_strDevName);
	xml_SetAttributeValue(pXmlKeys->m_strMfgInfoKey, oElement, m_strMfgInfo);
	xml_SetAttributeValue(pXmlKeys->m_strDevStatusKey, oElement, m_strDevStatus);
	return 0;
}

long CEdgeDev::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strHardVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strDevType);
		BinarySerializeCalLen(oBinaryBuffer, m_strDevName);
		BinarySerializeCalLen(oBinaryBuffer, m_strMfgInfo);
		BinarySerializeCalLen(oBinaryBuffer, m_strDevStatus);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strHardVersion);
		BinarySerializeRead(oBinaryBuffer, m_strDevType);
		BinarySerializeRead(oBinaryBuffer, m_strDevName);
		BinarySerializeRead(oBinaryBuffer, m_strMfgInfo);
		BinarySerializeRead(oBinaryBuffer, m_strDevStatus);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strHardVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strDevType);
		BinarySerializeWrite(oBinaryBuffer, m_strDevName);
		BinarySerializeWrite(oBinaryBuffer, m_strMfgInfo);
		BinarySerializeWrite(oBinaryBuffer, m_strDevStatus);
	}
	return 0;
}

void CEdgeDev::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pHardVersion = new CExBaseList;
	pHardVersion->m_strID = CEdgeCmdMngrXmlRWKeys::HardVersionKey();
	pHardVersion->m_strName = m_strHardVersion;
	AddNewChild(pHardVersion);

	CExBaseList* pDevType = new CExBaseList;
	pDevType->m_strID = CEdgeCmdMngrXmlRWKeys::DevTypeKey();
	pDevType->m_strName = m_strDevType;
	AddNewChild(pDevType);

	CExBaseList* pDevName = new CExBaseList;
	pDevName->m_strID = CEdgeCmdMngrXmlRWKeys::DevNameKey();
	pDevName->m_strName = m_strDevName;
	AddNewChild(pDevName);

	CExBaseList* pMfgInfo = new CExBaseList;
	pMfgInfo->m_strID = CEdgeCmdMngrXmlRWKeys::MfgInfoKey();
	pMfgInfo->m_strName = m_strMfgInfo;
	AddNewChild(pMfgInfo);

	CExBaseList* pDevStatus = new CExBaseList;
	pDevStatus->m_strID = CEdgeCmdMngrXmlRWKeys::DevStatusKey();
	pDevStatus->m_strName = m_strDevStatus;
	AddNewChild(pDevStatus);
}

BOOL CEdgeDev::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeDev *p = (CEdgeDev*)pObj;

	if(m_strHardVersion != p->m_strHardVersion)
	{
		return FALSE;
	}

	if(m_strDevType != p->m_strDevType)
	{
		return FALSE;
	}

	if(m_strDevName != p->m_strDevName)
	{
		return FALSE;
	}

	if(m_strMfgInfo != p->m_strMfgInfo)
	{
		return FALSE;
	}

	if(m_strDevStatus != p->m_strDevStatus)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeDev::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeDev *p = (CEdgeDev*)pDest;

	p->m_strHardVersion = m_strHardVersion;
	p->m_strDevType = m_strDevType;
	p->m_strDevName = m_strDevName;
	p->m_strMfgInfo = m_strMfgInfo;
	p->m_strDevStatus = m_strDevStatus;
	return TRUE;
}

CBaseObject* CEdgeDev::Clone()
{
	CEdgeDev *p = new CEdgeDev();
	Copy(p);
	return p;
}

CBaseObject* CEdgeDev::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeDev *p = new CEdgeDev();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeDev::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeDev::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeDev::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
