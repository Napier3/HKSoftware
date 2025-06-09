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

	//初始化成员变量
}

CEdgeMemUsed::~CEdgeMemUsed()
{
}

long CEdgeMemUsed::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeDatas::XmlReadOwn(oNode, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeMemUsed::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeDatas::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeMemUsed::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEdgeMemUsed::InitAfterRead()
{
}

BOOL CEdgeMemUsed::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEdgeDatas::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEdgeMemUsed *p = (CEdgeMemUsed*)pObj;

	return TRUE;
}

BOOL CEdgeMemUsed::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeDatas::CopyOwn(pDest);

	CEdgeMemUsed *p = (CEdgeMemUsed*)pDest;

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
