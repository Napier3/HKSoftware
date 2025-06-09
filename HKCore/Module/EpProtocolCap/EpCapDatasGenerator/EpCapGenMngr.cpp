//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapGenMngr.cpp  CEpCapGenMngr


#include "stdafx.h"
#include "EpCapGenMngr.h"

CEpCapGenMngr::CEpCapGenMngr()
{
	//初始化属性
	m_strName = _T("报文模拟发送管理");
	m_strID = _T("EpCapGenMngr");

	//初始化成员变量
}

CEpCapGenMngr::~CEpCapGenMngr()
{
}

long CEpCapGenMngr::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapDatasGeneratorXmlRWKeys *pXmlKeys = (CEpCapDatasGeneratorXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpCapGenMngr::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapDatasGeneratorXmlRWKeys *pXmlKeys = (CEpCapDatasGeneratorXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CEpCapGenMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapGenMngr *p = (CEpCapGenMngr*)pObj;

	return TRUE;
}

BOOL CEpCapGenMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapGenMngr *p = (CEpCapGenMngr*)pDest;

	return TRUE;
}

CBaseObject* CEpCapGenMngr::Clone()
{
	CEpCapGenMngr *p = new CEpCapGenMngr();
	Copy(p);
	return p;
}

CExBaseObject* CEpCapGenMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapDatasGeneratorXmlRWKeys *pXmlKeys = (CEpCapDatasGeneratorXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapGenSerialKey)
	{
		pNew = new CEpCapGenSerial();
	}
	else if (strClassID == pXmlKeys->m_strCEpCapGenUdpKey)
	{
		pNew = new CEpCapGenUdp();
	}

	return pNew;
}

CExBaseObject* CEpCapGenMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ECGCLASSID_CEPCAPGENSERIAL)
	{
		pNew = new CEpCapGenSerial();
	}
	else if (nClassID == ECGCLASSID_CEPCAPGENUDP)
	{
		pNew = new CEpCapGenUdp();
	}

	return pNew;
}

CString CEpCapGenMngr::GetCapGenFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("EpCapGen.xml");
	return strFile;
}

BOOL CEpCapGenMngr::OpenCapGenFile()
{
	CString strFile = GetCapGenFile();
	return OpenXmlFile(strFile, GetXmlElementKey(), CEpCapDatasGeneratorXmlRWKeys::g_pXmlKeys);
}

BOOL CEpCapGenMngr::SaveCapGenFile()
{
	CString strFile = GetCapGenFile();
	return SaveXmlFile(strFile, CEpCapDatasGeneratorXmlRWKeys::g_pXmlKeys);
}

