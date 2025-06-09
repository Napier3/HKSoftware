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
	CEdgeDatas::XmlReadOwn(oNode, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeLinkState::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeDatas::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeLinkState::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CEdgeDatas::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CEdgeLinkState::InitAfterRead()
{
}

BOOL CEdgeLinkState::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEdgeDatas::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEdgeLinkState *p = (CEdgeLinkState*)pObj;

	return TRUE;
}

BOOL CEdgeLinkState::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeDatas::CopyOwn(pDest);

	CEdgeLinkState *p = (CEdgeLinkState*)pDest;

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
