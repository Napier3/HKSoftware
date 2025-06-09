//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeMem.cpp  CEdgeMem


#include "stdafx.h"
#include "EdgeMem.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeMem::CEdgeMem()
{
	//初始化属性

	//初始化成员变量
}

CEdgeMem::~CEdgeMem()
{
}

long CEdgeMem::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeDatas::XmlReadOwn(oNode, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeMem::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeDatas::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeMem::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEdgeMem::InitAfterRead()
{
}

BOOL CEdgeMem::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEdgeDatas::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEdgeMem *p = (CEdgeMem*)pObj;

	return TRUE;
}

BOOL CEdgeMem::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeDatas::CopyOwn(pDest);

	CEdgeMem *p = (CEdgeMem*)pDest;

	return TRUE;
}

CBaseObject* CEdgeMem::Clone()
{
	CEdgeMem *p = new CEdgeMem();
	Copy(p);
	return p;
}

CBaseObject* CEdgeMem::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeMem *p = new CEdgeMem();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeMem::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeMem::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeMem::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
