//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMatchDatasetRefs.cpp  CXMatchDatasetRefs


#include "stdafx.h"
#include "XMatchDatasetRefs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CXMatchDatasetRefs::CXMatchDatasetRefs()
{
	//初始化属性

	//初始化成员变量
}

CXMatchDatasetRefs::~CXMatchDatasetRefs()
{
}

long CXMatchDatasetRefs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMmsDvmFileKey, oNode, m_strMmsDvmFile);
	return 0;
}

long CXMatchDatasetRefs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMmsDvmFileKey, oElement, m_strMmsDvmFile);
	return 0;
}

CExBaseObject* CXMatchDatasetRefs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCXMatchDatasetRefKey)
	{
		pNew = new CXMatchDatasetRef();
	}

	return pNew;
}

CExBaseObject* CXMatchDatasetRefs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == XMCFGCLASSID_CXMATCHDATASETREF)
	{
		pNew = new CXMatchDatasetRef();
	}

	return pNew;
}

CXMatchDatasetRef* CXMatchDatasetRefs::AddNewDataset(const CString &strID)
{
	CXMatchDatasetRef *pNew = new CXMatchDatasetRef();

	pNew->m_strName = strID;
	pNew->m_strID = strID;
	AddNewChild(pNew);
	
	return pNew;
}

