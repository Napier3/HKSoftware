//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeData.cpp  CEdgeData


#include "stdafx.h"
#include "EdgeData.h"
#include "EdgeGlobalDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeData::CEdgeData()
{
	//初始化属性
	m_nStatusCode = 0;

	//初始化成员变量
}

CEdgeData::~CEdgeData()
{
}

long CEdgeData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strStatusCodeKey, oNode, m_nStatusCode);
	xml_GetAttibuteValue(pXmlKeys->m_strStatusDescKey, oNode, m_strStatusDesc);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDeviceId);
	xml_GetAttibuteValue(pXmlKeys->m_strNodeIdKey, oNode, m_strNodeId);

	if(oNode.GetXmlRWType() != _JSON_TYPE_)
		return 0;

	CJsonNode *pJsonNode = (CJsonNode *)(&oNode);
	CJSON *pNode = pJsonNode->m_pJsonNode;
	CJSON *pChild = pNode->child;
	CString strValue = _T(""),strID = _T("");

	while(pChild != NULL)
	{
		strID = pChild->string;
		if(pChild->type == CJSON_Number)
		{
			strValue.Format(_T("%d"), pChild->valueint);
		}
		else
		{		
			strValue = pChild->valuestring;		
		}
		AddNewData(strID,strID,EDGE_DATATYPE_STRING,strValue);
		pChild = pChild->next;
	}

	return 0;
}

long CEdgeData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strStatusCodeKey, oElement, m_nStatusCode);
	if(m_strStatusDesc.GetLength())
		xml_SetAttributeValue(pXmlKeys->m_strStatusDescKey, oElement, m_strStatusDesc);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDeviceId);
	if(m_strNodeId.GetLength())
		xml_SetAttributeValue(pXmlKeys->m_strNodeIdKey, oElement, m_strNodeId);
	return 0;
}

long CEdgeData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nStatusCode);
		BinarySerializeCalLen(oBinaryBuffer, m_strStatusDesc);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strNodeId);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nStatusCode);
		BinarySerializeRead(oBinaryBuffer, m_strStatusDesc);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceId);
		BinarySerializeRead(oBinaryBuffer, m_strNodeId);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nStatusCode);
		BinarySerializeWrite(oBinaryBuffer, m_strStatusDesc);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceId);
		BinarySerializeWrite(oBinaryBuffer, m_strNodeId);
	}
	return 0;
}

void CEdgeData::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pStatusDesc = new CExBaseList;
	pStatusDesc->m_strID = CEdgeCmdMngrXmlRWKeys::StatusDescKey();
	pStatusDesc->m_strName = m_strStatusDesc;
	AddNewChild(pStatusDesc);

	CExBaseList* pDeviceId = new CExBaseList;
	pDeviceId->m_strID = CEdgeCmdMngrXmlRWKeys::DeviceIdKey();
	pDeviceId->m_strName = m_strDeviceId;
	AddNewChild(pDeviceId);

	CExBaseList* pNodeId = new CExBaseList;
	pNodeId->m_strID = CEdgeCmdMngrXmlRWKeys::NodeIdKey();
	pNodeId->m_strName = m_strNodeId;
	AddNewChild(pNodeId);

	CExBaseList* pStatusCode = new CExBaseList;
	pStatusCode->m_strID = CEdgeCmdMngrXmlRWKeys::StatusCodeKey();
	pStatusCode->m_strName.Format("%d", m_nStatusCode);
	AddNewChild(pStatusCode);
}

BOOL CEdgeData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeData *p = (CEdgeData*)pObj;

	if(m_nStatusCode != p->m_nStatusCode)
	{
		return FALSE;
	}

	if(m_strStatusDesc != p->m_strStatusDesc)
	{
		return FALSE;
	}

	if(m_strDeviceId != p->m_strDeviceId)
	{
		return FALSE;
	}

	if(m_strNodeId != p->m_strNodeId)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeData *p = (CEdgeData*)pDest;

	p->m_nStatusCode = m_nStatusCode;
	p->m_strStatusDesc = m_strStatusDesc;
	p->m_strDeviceId = m_strDeviceId;
	p->m_strNodeId = m_strNodeId;
	return TRUE;
}

CBaseObject* CEdgeData::Clone()
{
	CEdgeData *p = new CEdgeData();
	Copy(p);
	return p;
}

CBaseObject* CEdgeData::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeData *p = new CEdgeData();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeData::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeData::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
