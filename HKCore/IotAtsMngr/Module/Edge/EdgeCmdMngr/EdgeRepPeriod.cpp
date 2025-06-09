//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeRepPeriod.cpp  CEdgeRepPeriod


#include "stdafx.h"
#include "EdgeRepPeriod.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeRepPeriod::CEdgeRepPeriod()
{
	//初始化属性

	//初始化成员变量
}

CEdgeRepPeriod::~CEdgeRepPeriod()
{
}

long CEdgeRepPeriod::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeDatas::XmlReadOwn(oNode, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeRepPeriod::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeDatas::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeRepPeriod::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEdgeRepPeriod::InitAfterRead()
{
}

BOOL CEdgeRepPeriod::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEdgeDatas::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEdgeRepPeriod *p = (CEdgeRepPeriod*)pObj;

	return TRUE;
}

BOOL CEdgeRepPeriod::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeDatas::CopyOwn(pDest);

	CEdgeRepPeriod *p = (CEdgeRepPeriod*)pDest;

	return TRUE;
}

CBaseObject* CEdgeRepPeriod::Clone()
{
	CEdgeRepPeriod *p = new CEdgeRepPeriod();
	Copy(p);
	return p;
}

CBaseObject* CEdgeRepPeriod::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeRepPeriod *p = new CEdgeRepPeriod();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeRepPeriod::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeRepPeriod::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeRepPeriod::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
