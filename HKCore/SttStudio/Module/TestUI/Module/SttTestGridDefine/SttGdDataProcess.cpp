//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdDataProcess.cpp  CSttGdDataProcess


#include "stdafx.h"
#include "SttGdDataProcess.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdDataProcess::CSttGdDataProcess()
{
	//初始化属性

	//初始化成员变量
}

CSttGdDataProcess::~CSttGdDataProcess()
{
}

long CSttGdDataProcess::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdDataProcess::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdDataProcess::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttGdDataProcess::InitAfterRead()
{
}

BOOL CSttGdDataProcess::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttGdDataProcess *p = (CSttGdDataProcess*)pObj;

	return TRUE;
}

BOOL CSttGdDataProcess::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttGdDataProcess *p = (CSttGdDataProcess*)pDest;

	return TRUE;
}

CBaseObject* CSttGdDataProcess::Clone()
{
	CSttGdDataProcess *p = new CSttGdDataProcess();
	Copy(p);
	return p;
}

CBaseObject* CSttGdDataProcess::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdDataProcess *p = new CSttGdDataProcess();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttGdDataProcess::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTGDDATACAL)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttGdDataProcess::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttGdDataCalKey)
	{
		pNew = new CSttGdDataCal();
	}

	return pNew;
}

CExBaseObject* CSttGdDataProcess::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTGDDATACAL)
	{
		pNew = new CSttGdDataCal();
	}

	return pNew;
}
