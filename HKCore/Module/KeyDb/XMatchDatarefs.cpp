//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMatchDatarefs.cpp  CXMatchDatarefs


#include "stdafx.h"
#include "XMatchDatarefs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CXMatchDatarefs::CXMatchDatarefs()
{
	//初始化属性

	//初始化成员变量
}

CXMatchDatarefs::~CXMatchDatarefs()
{
}

long CXMatchDatarefs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CXMatchDatarefs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject* CXMatchDatarefs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCXMatchDatarefKey)
	{
		pNew = new CXMatchDataref();
	}

	return pNew;
}

CExBaseObject* CXMatchDatarefs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == XMCFGCLASSID_CXMATCHDATAREF)
	{
		pNew = new CXMatchDataref();
	}

	return pNew;
}

CXMatchDataref* CXMatchDatarefs::FindBySrcPath(const CString &strPath)
{
	POS pos = GetHeadPosition();
	CXMatchDataref *p = NULL;
	CXMatchDataref *pFind = NULL;

	while (pos != NULL)
	{
		p = (CXMatchDataref*)GetNext(pos);

		if (p->m_strSrcPath == strPath)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CXMatchDataref* CXMatchDatarefs::FindByDestPath(const CString &strPath)
{
	POS pos = GetHeadPosition();
	CXMatchDataref *p = NULL;
	CXMatchDataref *pFind = NULL;

	while (pos != NULL)
	{
		p = (CXMatchDataref*)GetNext(pos);

		if (p->m_strDestPath == strPath)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CXMatchDataref* CXMatchDatarefs::AddNewDataRef(const CString &strSrcIDPath, const CString &strDestIDPath)
{
	CXMatchDataref *pNew = new CXMatchDataref();
	pNew->m_strSrcPath = strSrcIDPath;
	pNew->m_strDestPath = strDestIDPath;
	AddNewChild(pNew);

	return pNew;
}

