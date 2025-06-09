//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeLinkState.cpp  CEdgeLinkState


#include "stdafx.h"
#include "EdgeLinkState.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeLinkState::CEdgeLinkState()
{
	//初始化属性

	//初始化成员变量
}

CEdgeLinkState::~CEdgeLinkState()
{
}

long CEdgeLinkState::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strStatusKey, oNode, m_strStatus);

	AddErrorInfo(pXmlKeys->m_strNameKey, oNode, CJSON_String);
	AddErrorInfo(pXmlKeys->m_strStatusKey, oNode, CJSON_String);
	return 0;
}

long CEdgeLinkState::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strStatusKey, oElement, m_strStatus);
	return 0;
}

long CEdgeLinkState::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strStatus);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strStatus);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strStatus);
	}
	return 0;
}

void CEdgeLinkState::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pStatus = new CExBaseList;
	pStatus->m_strID = CEdgeCmdMngrXmlRWKeys::StatusKey();
	pStatus->m_strName = m_strStatus;
	AddNewChild(pStatus);

	CExBaseList* pName = new CExBaseList;
	pName->m_strID = _T("name");
	pName->m_strName = m_strName;
	AddNewChild(pName);
}

BOOL CEdgeLinkState::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeLinkState *p = (CEdgeLinkState*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strStatus != p->m_strStatus)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeLinkState::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeLinkState *p = (CEdgeLinkState*)pDest;

	p->m_strName = m_strName;
	p->m_strStatus = m_strStatus;
	return TRUE;
}

CBaseObject* CEdgeLinkState::Clone()
{
	CEdgeLinkState *p = new CEdgeLinkState();
	Copy(p);
	return p;
}

CBaseObject* CEdgeLinkState::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeLinkState *p = new CEdgeLinkState();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeLinkState::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeLinkState::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeLinkState::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
