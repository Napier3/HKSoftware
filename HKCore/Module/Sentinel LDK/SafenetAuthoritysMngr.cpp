// XSafenetBase.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SafenetAuthoritysMngr.h"
#include "..\XLanguage\XLanguageResource.h"
#include "..\TestMacro\TestMacrosFileMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//

CSafenetAuthority::CSafenetAuthority()
{
	//初始化属性
	m_nEnable = 0;

	//初始化成员变量
}

CSafenetAuthority::~CSafenetAuthority()
{
}

long CSafenetAuthority::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSafenetAuthorityXmlRWKeys *pXmlKeys = (CSafenetAuthorityXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strEnableKey, oNode, m_nEnable);

	return 0;
}

long CSafenetAuthority::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSafenetAuthorityXmlRWKeys *pXmlKeys = (CSafenetAuthorityXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strEnableKey, oElement, m_nEnable);

	return 0;
}

BOOL CSafenetAuthority::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSafenetAuthority *p = (CSafenetAuthority*)pDest;
	p->m_nEnable = m_nEnable;
	p->m_strAuthorityType = m_strAuthorityType;

	return TRUE;
}

CBaseObject* CSafenetAuthority::Clone()
{
	CSafenetAuthority *p = new CSafenetAuthority();
	Copy(p);
	return p;
}

//////////////////////////////////////////////////////////////////////////
//CSafenetAuthoritys
CSafenetAuthoritys::CSafenetAuthoritys()
{

}

CSafenetAuthoritys::~CSafenetAuthoritys()
{

}

CExBaseObject* CSafenetAuthoritys::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSafenetAuthorityXmlRWKeys *pXmlKeys = (CSafenetAuthorityXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCSafenetAuthorityKey)
	{
		pNew = new CSafenetAuthority();
	}

	return pNew;
}


BOOL CSafenetAuthoritys::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSafenetAuthoritys *p = (CSafenetAuthoritys*)pDest;

	return TRUE;
}

CBaseObject* CSafenetAuthoritys::Clone()
{
	CSafenetAuthoritys *p = new CSafenetAuthoritys();
	Copy(p);
	return p;
}

void CSafenetAuthoritys::ClearAuthority()
{
	POS pos = GetHeadPosition();
	CSafenetAuthority *p = NULL;

	while (pos != NULL)
	{
		p = (CSafenetAuthority *)GetNext(pos);
		p->m_nEnable = 0;
	}
}

void CSafenetAuthoritys::InitByAuthoritys(CSafenetAuthoritys *pSrcAuthoritys)
{
	if (pSrcAuthoritys == NULL)
	{
		ClearAuthority();
		return;
	}

	POS pos = GetHeadPosition();
	CSafenetAuthority *p = NULL;
	CSafenetAuthority *pFind = NULL;

	while (pos != NULL)
	{
		p = (CSafenetAuthority *)GetNext(pos);
		pFind = (CSafenetAuthority *)pSrcAuthoritys->FindByName(p->m_strName);

		if (pFind != NULL)
		{
			p->m_nEnable = pFind->m_nEnable;
		}
		else
		{
			p->m_nEnable = 0;
		}
	}
}

void CSafenetAuthoritys::InitByAuthoritys(const CString &strAuthoritys)
{
	POS pos = GetHeadPosition();
	CSafenetAuthority *p = NULL;

	while (pos != NULL)
	{
		p = (CSafenetAuthority*)GetNext(pos);
		p->m_nEnable = safenet_has_authority(strAuthoritys, p->m_strID);
	}
}

void CSafenetAuthoritys::GetAuthoritys(CString &strAuthoritys)
{
	strAuthoritys.Empty();
	POS pos = GetHeadPosition();
	CSafenetAuthority *p = NULL;

	while (pos != NULL)
	{
		p = (CSafenetAuthority*)GetNext(pos);
		
		if (p->m_nEnable == 1)
		{
			strAuthoritys.AppendFormat(_T("%s$"), p->m_strID);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//CSafenetAuthoritysMngr
long CSafenetAuthoritysMngr::g_nSafenetAuthoritysMngr = 0;
CSafenetAuthoritysMngr* CSafenetAuthoritysMngr::g_pSafenetAuthoritysMngr = NULL;

CSafenetAuthoritysMngr* CSafenetAuthoritysMngr::Create()
{
	g_nSafenetAuthoritysMngr++;

	if (g_nSafenetAuthoritysMngr == 1)
	{
		g_pSafenetAuthoritysMngr = new CSafenetAuthoritysMngr();
		g_pSafenetAuthoritysMngr->OpenAuthorityConfigFile();
	}

	return g_pSafenetAuthoritysMngr;
}

void CSafenetAuthoritysMngr::Release()
{
	g_nSafenetAuthoritysMngr--;

	if (g_nSafenetAuthoritysMngr == 0)
	{
		delete g_pSafenetAuthoritysMngr;
		g_pSafenetAuthoritysMngr = NULL;
	}
}

CSafenetAuthoritysMngr* CSafenetAuthoritysMngr::GetSafenetAuthoritysMngr()
{
	ASSERT (g_pSafenetAuthoritysMngr != NULL);
	return g_pSafenetAuthoritysMngr;
}

CSafenetAuthoritys* CSafenetAuthoritysMngr::GetAuthoritys_Test()
{
	ASSERT (g_pSafenetAuthoritysMngr != NULL);
	return g_pSafenetAuthoritysMngr->m_pTest;
}

CSafenetAuthoritys* CSafenetAuthoritysMngr::GetAuthoritys_TestApp()
{
	ASSERT (g_pSafenetAuthoritysMngr != NULL);
	return g_pSafenetAuthoritysMngr->m_pTestApp;
}

CSafenetAuthoritys* CSafenetAuthoritysMngr::GetAuthoritys_HaspInfo()
{
	ASSERT (g_pSafenetAuthoritysMngr != NULL);
	return g_pSafenetAuthoritysMngr->m_pHaspInfo;
}

CSafenetAuthoritys* CSafenetAuthoritysMngr::GetAuthoritys_TestMacros()
{
	ASSERT (g_pSafenetAuthoritysMngr != NULL);
	return g_pSafenetAuthoritysMngr->m_pTestMacro;
}

void CSafenetAuthoritysMngr::ClearAuthoritys_Test()
{
	ASSERT (g_pSafenetAuthoritysMngr != NULL);
	g_pSafenetAuthoritysMngr->m_pTest->ClearAuthority();
}

void CSafenetAuthoritysMngr::ClearAuthoritys_TestApp()
{
	ASSERT (g_pSafenetAuthoritysMngr != NULL);
	g_pSafenetAuthoritysMngr->m_pTestApp->ClearAuthority();
}

void CSafenetAuthoritysMngr::ClearAuthoritys_HaspInfo()
{
	ASSERT (g_pSafenetAuthoritysMngr != NULL);
	g_pSafenetAuthoritysMngr->m_pHaspInfo->ClearAuthority();
}

void CSafenetAuthoritysMngr::ClearAuthoritys_TestMacro()
{
	ASSERT (g_pSafenetAuthoritysMngr != NULL);
	g_pSafenetAuthoritysMngr->m_pTestMacro->ClearAuthority();
}

CSafenetAuthoritysMngr::CSafenetAuthoritysMngr()
{
	m_pTest = NULL;
	m_pTestApp = NULL;
	m_pHaspInfo = NULL;
	m_pTestMacro = NULL;
}

CSafenetAuthoritysMngr::~CSafenetAuthoritysMngr()
{

}

CExBaseObject* CSafenetAuthoritysMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSafenetAuthorityXmlRWKeys *pXmlKeys = (CSafenetAuthorityXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCSafenetAuthoritysKey)
	{
		pNew = new CSafenetAuthoritys();
	}

	return pNew;
}

void CSafenetAuthoritysMngr::InitAfterRead()
{
	m_pTest = (CSafenetAuthoritys*)FindByID(SafenetAuthoritysID_Test);
	m_pTestApp = (CSafenetAuthoritys*)FindByID(SafenetAuthoritysID_TestApp);
	m_pHaspInfo = (CSafenetAuthoritys*)FindByID(SafenetAuthoritysID_hasp_info);
	m_pTestMacro = (CSafenetAuthoritys*)FindByID(SafenetAuthoritysID_TestMacros);
}


void CSafenetAuthoritysMngr::OpenAuthorityConfigFile()
{
	CString strFile;
	strFile = _P_GetCommonConfigPath();
	strFile += _T("SafenetAuthority.xml");
	OpenXmlFile(strFile, CSafenetAuthorityXmlRWKeys::g_pXmlKeys);
}

