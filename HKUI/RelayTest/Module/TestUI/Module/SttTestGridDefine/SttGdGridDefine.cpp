//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdGridDefine.cpp  CSttGdGridDefine


#include "stdafx.h"
#include "SttGdGridDefine.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdGridDefine::CSttGdGridDefine()
{
	//初始化属性

	//初始化成员变量
}

CSttGdGridDefine::~CSttGdGridDefine()
{
}

long CSttGdGridDefine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdGridDefine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdGridDefine::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttGdGridDefine::InitAfterRead()
{
}

BOOL CSttGdGridDefine::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttGdGridDefine *p = (CSttGdGridDefine*)pObj;

	return TRUE;
}

BOOL CSttGdGridDefine::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttGdGridDefine *p = (CSttGdGridDefine*)pDest;

	return TRUE;
}

CBaseObject* CSttGdGridDefine::Clone()
{
	CSttGdGridDefine *p = new CSttGdGridDefine();
	Copy(p);
	return p;
}

CBaseObject* CSttGdGridDefine::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdGridDefine *p = new CSttGdGridDefine();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttGdGridDefine::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttGdGridDefine::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttGdColDefKey)
	{
		pNew = new CSttGdColDef();
	}

	return pNew;
}

CExBaseObject* CSttGdGridDefine::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF)
	{
		pNew = new CSttGdColDef();
	}

	return pNew;
}
