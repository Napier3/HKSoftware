//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SclFile.cpp  CSclFile


#include "stdafx.h"
#include "SclFile.h"
#include "..\..\..\Module\API\FileApi.h"

CSclFile::CSclFile()
{
#ifndef _PSX_IDE_QT_
	m_pRefFrameWnd = NULL;
#endif
	//初始化属性

	//初始化成员变量
}

CSclFile::~CSclFile()
{
	FreeSclFileRead();
}

long CSclFile::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecCfgToolXmlRWKeys *pXmlKeys = (CIecCfgToolXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strTscdNameKey, oNode, m_strtscdName);

	return 0;
}

long CSclFile::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecCfgToolXmlRWKeys *pXmlKeys = (CIecCfgToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CSclFile::InitAfterRead()
{
}

BOOL CSclFile::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSclFile *p = (CSclFile*)pObj;

	return TRUE;
}

BOOL CSclFile::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSclFile *p = (CSclFile*)pDest;

	return TRUE;
}

CBaseObject* CSclFile::Clone()
{
	CSclFile *p = new CSclFile();
	Copy(p);
	return p;
}

BOOL CSclFile::Open(const CString &strFile)
{
	m_strID = strFile;
	m_strName = GetPathFileNameFromFilePathName(strFile);
	return TRUE;
}

void CSclFile::FreeSclFileRead()
{
#ifndef _PSX_IDE_QT_
	m_pRefFrameWnd = NULL;
#endif
}

