//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXuiDataGlobal.cpp  CSttXuiDataGlobal


#include "stdafx.h"
#include "SttXuiDataGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttXuiDataGlobal::CSttXuiDataGlobal()
{
	//初始化属性

	//初始化成员变量
}

CSttXuiDataGlobal::~CSttXuiDataGlobal()
{
}

long CSttXuiDataGlobal::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttXuiDataGlobal::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttXuiDataGlobal::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttXuiDataGlobal::InitAfterRead()
{
}

BOOL CSttXuiDataGlobal::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttXuiDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttXuiDataGlobal *p = (CSttXuiDataGlobal*)pObj;

	return TRUE;
}

BOOL CSttXuiDataGlobal::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttXuiDataBase::CopyOwn(pDest);

	CSttXuiDataGlobal *p = (CSttXuiDataGlobal*)pDest;

	return TRUE;
}

CBaseObject* CSttXuiDataGlobal::Clone()
{
	CSttXuiDataGlobal *p = new CSttXuiDataGlobal();
	Copy(p);
	return p;
}

CBaseObject* CSttXuiDataGlobal::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttXuiDataGlobal *p = new CSttXuiDataGlobal();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttXuiDataGlobal::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTXUIDATAFONT)
	{
		return TRUE;
	}
	else if (nClassID == MNGRCLASSID_CSTTXUIDATATEXT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttXuiDataGlobal::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttXuiDataFontKey)
	{
		pNew = new CSttXuiDataFont();
	}
	else if (strClassID == pXmlKeys->m_strCSttXuiDataTextKey)
	{
		pNew = new CSttXuiDataText();
	}

	return pNew;
}

CExBaseObject* CSttXuiDataGlobal::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTXUIDATAFONT)
	{
		pNew = new CSttXuiDataFont();
	}
	else if (nClassID == MNGRCLASSID_CSTTXUIDATATEXT)
	{
		pNew = new CSttXuiDataText();
	}

	return pNew;
}
