//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeDeviceInfos.cpp  CEdgeDeviceInfos


#include "stdafx.h"
#include "EdgeDeviceInfos.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeDeviceInfos::CEdgeDeviceInfos()
{
	//初始化属性

	//初始化成员变量
}

CEdgeDeviceInfos::~CEdgeDeviceInfos()
{
}

long CEdgeDeviceInfos::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNodeIdKey, oNode, m_strNodeId);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strDescriptionKey, oNode, m_strDescription);
	xml_GetAttibuteValue(pXmlKeys->m_strMfgInfoKey, oNode, m_strMfgInfo);
	xml_GetAttibuteValue(pXmlKeys->m_strModelKey, oNode, m_strModel);
	xml_GetAttibuteValue(pXmlKeys->m_strModelIdKey, oNode, m_strModelId);
	return 0;
}

long CEdgeDeviceInfos::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNodeIdKey, oElement, m_strNodeId);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strDescriptionKey, oElement, m_strDescription);
	xml_SetAttributeValue(pXmlKeys->m_strMfgInfoKey, oElement, m_strMfgInfo);
	xml_SetAttributeValue(pXmlKeys->m_strModelKey, oElement, m_strModel);
	xml_SetAttributeValue(pXmlKeys->m_strModelIdKey, oElement, m_strModelId);
	return 0;
}

long CEdgeDeviceInfos::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strNodeId);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strDescription);
		BinarySerializeCalLen(oBinaryBuffer, m_strMfgInfo);
		BinarySerializeCalLen(oBinaryBuffer, m_strModel);
		BinarySerializeCalLen(oBinaryBuffer, m_strModelId);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strNodeId);
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strDescription);
		BinarySerializeRead(oBinaryBuffer, m_strMfgInfo);
		BinarySerializeRead(oBinaryBuffer, m_strModel);
		BinarySerializeRead(oBinaryBuffer, m_strModelId);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strNodeId);
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strDescription);
		BinarySerializeWrite(oBinaryBuffer, m_strMfgInfo);
		BinarySerializeWrite(oBinaryBuffer, m_strModel);
		BinarySerializeWrite(oBinaryBuffer, m_strModelId);
	}
	return 0;
}

void CEdgeDeviceInfos::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pNodeId = new CExBaseList;
	pNodeId->m_strID = CEdgeCmdMngrXmlRWKeys::NodeIdKey();
	pNodeId->m_strName = m_strNodeId;
	AddNewChild(pNodeId);

	CExBaseList* pDescription = new CExBaseList;
	pDescription->m_strID = CEdgeCmdMngrXmlRWKeys::DescriptionKey();
	pDescription->m_strName = m_strDescription;
	AddNewChild(pDescription);

	CExBaseList* pMfgInfo = new CExBaseList;
	pMfgInfo->m_strID = CEdgeCmdMngrXmlRWKeys::MfgInfoKey();
	pMfgInfo->m_strName = m_strMfgInfo;
	AddNewChild(pMfgInfo);

	CExBaseList* pMode = new CExBaseList;
	pMode->m_strID = CEdgeCmdMngrXmlRWKeys::ModeKey();
	pMode->m_strName = m_strModel;
	AddNewChild(pMode);

	CExBaseList* pModelId = new CExBaseList;
	pModelId->m_strID = CEdgeCmdMngrXmlRWKeys::ModelIdKey();
	pModelId->m_strName = m_strModelId;
	AddNewChild(pModelId);

	CExBaseList* pName = new CExBaseList;
	pName->m_strID = _T("name");
	pName->m_strName = m_strName;
	AddNewChild(pName);
}

BOOL CEdgeDeviceInfos::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeDeviceInfos *p = (CEdgeDeviceInfos*)pObj;

	if(m_strNodeId != p->m_strNodeId)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strDescription != p->m_strDescription)
	{
		return FALSE;
	}

	if(m_strMfgInfo != p->m_strMfgInfo)
	{
		return FALSE;
	}

	if(m_strModel != p->m_strModel)
	{
		return FALSE;
	}

	if(m_strModelId != p->m_strModelId)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeDeviceInfos::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeDeviceInfos *p = (CEdgeDeviceInfos*)pDest;

	p->m_strNodeId = m_strNodeId;
	p->m_strName = m_strName;
	p->m_strDescription = m_strDescription;
	p->m_strMfgInfo = m_strMfgInfo;
	p->m_strModel = m_strModel;
	p->m_strModelId = m_strModelId;
	return TRUE;
}

CBaseObject* CEdgeDeviceInfos::Clone()
{
	CEdgeDeviceInfos *p = new CEdgeDeviceInfos();
	Copy(p);
	return p;
}

CBaseObject* CEdgeDeviceInfos::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeDeviceInfos *p = new CEdgeDeviceInfos();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeDeviceInfos::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeDeviceInfos::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeDeviceInfos::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
