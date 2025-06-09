//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXuiDataFileTypes.cpp  CSttXuiDataFileTypes


#include "stdafx.h"
#include "SttXuiDataFileTypes.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttXuiDataFileTypes::CSttXuiDataFileTypes()
{
	//初始化属性

	//初始化成员变量
}

CSttXuiDataFileTypes::~CSttXuiDataFileTypes()
{
}

long CSttXuiDataFileTypes::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttXuiDataFileTypes::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttXuiDataFileTypes::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttXuiDataBase::SerializeOwn(oBinaryBuffer);
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

void CSttXuiDataFileTypes::InitAfterRead()
{
}

BOOL CSttXuiDataFileTypes::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttXuiDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttXuiDataFileTypes *p = (CSttXuiDataFileTypes*)pObj;

	return TRUE;
}

BOOL CSttXuiDataFileTypes::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttXuiDataBase::CopyOwn(pDest);

	CSttXuiDataFileTypes *p = (CSttXuiDataFileTypes*)pDest;

	return TRUE;
}

CBaseObject* CSttXuiDataFileTypes::Clone()
{
	CSttXuiDataFileTypes *p = new CSttXuiDataFileTypes();
	Copy(p);
	return p;
}

CBaseObject* CSttXuiDataFileTypes::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttXuiDataFileTypes *p = new CSttXuiDataFileTypes();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttXuiDataFileTypes::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTXUIDATAFILETYPE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttXuiDataFileTypes::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttXuiDataFileTypeKey)
	{
		pNew = new CSttXuiDataFileType();
	}

	return pNew;
}

CExBaseObject* CSttXuiDataFileTypes::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTXUIDATAFILETYPE)
	{
		pNew = new CSttXuiDataFileType();
	}

	return pNew;
}
