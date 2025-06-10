//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdGridInsts.cpp  CSttGdGridInsts


#include "stdafx.h"
#include "SttGdGridInsts.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdGridInsts::CSttGdGridInsts()
{
	//初始化属性

	//初始化成员变量
}

CSttGdGridInsts::~CSttGdGridInsts()
{
}

long CSttGdGridInsts::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdGridInsts::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdGridInsts::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttGdGridInsts::InitAfterRead()
{
}

BOOL CSttGdGridInsts::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttGdGridInsts *p = (CSttGdGridInsts*)pObj;

	return TRUE;
}

BOOL CSttGdGridInsts::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttGdGridInsts *p = (CSttGdGridInsts*)pDest;

	return TRUE;
}

CBaseObject* CSttGdGridInsts::Clone()
{
	CSttGdGridInsts *p = new CSttGdGridInsts();
	Copy(p);
	return p;
}

CBaseObject* CSttGdGridInsts::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdGridInsts *p = new CSttGdGridInsts();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttGdGridInsts::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTGDGRIDINST)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttGdGridInsts::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttGdGridInstKey)
	{
		pNew = new CSttGdGridInst();
	}

	return pNew;
}

CExBaseObject* CSttGdGridInsts::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTGDGRIDINST)
	{
		pNew = new CSttGdGridInst();
	}

	return pNew;
}
