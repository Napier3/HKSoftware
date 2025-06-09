//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AinExpandMngr.cpp  CAinExpandMngr


#include "stdafx.h"
#include "AinExpandMngr.h"

const CString CAinExpandMngr::g_strAinExpandConfigFile = _T("AinExpandConfig.xml");

CAinExpandMngr::CAinExpandMngr()
{
	//初始化属性

	//初始化成员变量
}

CAinExpandMngr::~CAinExpandMngr()
{
}

long CAinExpandMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	return 0;
}

long CAinExpandMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	return 0;
}

long CAinExpandMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CAinExpandMngr::InitAfterRead()
{
}

BOOL CAinExpandMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAinExpandMngr *p = (CAinExpandMngr*)pObj;

	return TRUE;
}

BOOL CAinExpandMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAinExpandMngr *p = (CAinExpandMngr*)pDest;

	return TRUE;
}

CBaseObject* CAinExpandMngr::Clone()
{
	CAinExpandMngr *p = new CAinExpandMngr();
	Copy(p);
	return p;
}

BOOL CAinExpandMngr::CanPaste(UINT nClassID)
{
	if (nClassID == GBCLASSID_CAINEXPAND)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAinExpandMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAinExpandKey)
	{
		pNew = new CAinExpand();
	}

	return pNew;
}

CExBaseObject* CAinExpandMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBCLASSID_CAINEXPAND)
	{
		pNew = new CAinExpand();
	}

	return pNew;
}


CString CAinExpandMngr::GetAinExpandConfigFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += g_strAinExpandConfigFile;

	return strFile;
}


void CAinExpandMngr::OpenAinExpandConfigFile()
{
	DeleteAll();
	CString strFile = GetAinExpandConfigFile();
	OpenXmlFile(strFile, CGbXMLKeys::g_pGbXMLKeys);
}