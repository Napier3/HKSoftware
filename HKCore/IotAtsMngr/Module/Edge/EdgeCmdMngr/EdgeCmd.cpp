//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeCmd.cpp  CEdgeCmd


#include "stdafx.h"
#include "EdgeCmd.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeCmd::CEdgeCmd()
{
	//初始化属性

	//初始化成员变量
}

CEdgeCmd::~CEdgeCmd()
{
}

long CEdgeCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return CEdgeGroup::XmlReadOwn(oNode,pXmlRWKeys);
}

long CEdgeCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return CEdgeGroup::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
}

long CEdgeCmd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CEdgeCmd::InitAfterRead()
{
}

BOOL CEdgeCmd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeCmd *p = (CEdgeCmd*)pObj;

	return TRUE;
}

BOOL CEdgeCmd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeCmd *p = (CEdgeCmd*)pDest;

	return TRUE;
}

CBaseObject* CEdgeCmd::Clone()
{
	CEdgeCmd *p = new CEdgeCmd();
	Copy(p);
	return p;
}

CBaseObject* CEdgeCmd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeCmd *p = new CEdgeCmd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeCmd::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CEDGEPARAM)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGEDATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEdgeCmd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEdgeParamKey)
	{
		pNew = new CEdgeParam();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeDataKey)
	{
		pNew = new CEdgeData();
	}

	return pNew;
}

CExBaseObject* CEdgeCmd::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CEDGEPARAM)
	{
		pNew = new CEdgeParam();
	}
	else if (nClassID == MNGRCLASSID_CEDGEDATA)
	{
		pNew = new CEdgeData();
	}

	return pNew;
}
