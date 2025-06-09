// VerUpdateHisSysVers.cpp : 实现文件
//

#include "stdafx.h"
#include "VerUpdateHisSysMngr.h"
#include "VerUpdateHisSysVers.h"
#include "VerUpdateHisVer.h"

// CVerUpdateHisSysVers

CVerUpdateHisSysVers::CVerUpdateHisSysVers()
{
}

CVerUpdateHisSysVers::~CVerUpdateHisSysVers()
{
}

long CVerUpdateHisSysVers::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateHisXmlRWKeys *pXmlKeys = (CVerUpdateHisXmlRWKeys*)pXmlRWKeys;

	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	return 0;
}

long CVerUpdateHisSysVers::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateHisXmlRWKeys *pXmlKeys = (CVerUpdateHisXmlRWKeys*)pXmlRWKeys;

	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

CExBaseObject* CVerUpdateHisSysVers::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CVerUpdateHisXmlRWKeys *pXmlKeys = (CVerUpdateHisXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strVersionKey)
	{
		pNew = new CVerUpdateHisVer();
	}

	return pNew;
}

CExBaseObject* CVerUpdateHisSysVers::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == VERUPDATEHISCLASSID_VER)
	{
		pNew = new CVerUpdateHisVer();
	}

	return pNew;
}

void CVerUpdateHisSysVers::InitAfterRead()
{
	RemoveExtraEntries();
}

long CVerUpdateHisSysVers::GetLocalCurrVerIdx()
{
	CVerUpdateHisVer* pVerUpdateHisVer = (CVerUpdateHisVer*)GetTail();
	if (pVerUpdateHisVer != NULL)
	{
		return pVerUpdateHisVer->m_nCurrVerIdx;
	}

	return 0;
}

CString CVerUpdateHisSysVers::GetLocalCurrVer()
{
	CString strCurrVer(_T(""));
	CVerUpdateHisVer* pVerUpdateHisVer = (CVerUpdateHisVer*)GetTail();
	if (pVerUpdateHisVer != NULL)
	{
		strCurrVer = pVerUpdateHisVer->m_strCurrVer;
	}

	if (strCurrVer == _T(""))
	{
		strCurrVer = _T("初始版");
	}

	return strCurrVer;
}

long CVerUpdateHisSysVers::GetMaxEntries()
{
	CVerUpdateHisSysMngr* pSysMngr = (CVerUpdateHisSysMngr*)GetParent();

	if(pSysMngr && pSysMngr->m_nMaxEntries>DEFAULT_MAXENTRIES)
	{
		return pSysMngr->m_nMaxEntries;
	}

	return DEFAULT_MAXENTRIES;
}

void CVerUpdateHisSysVers::RemoveExtraEntries()
{
	long nMaxCount = GetMaxEntries();
	
	while (GetCount()>nMaxCount)
	{
		delete RemoveHead();
	}
}

void CVerUpdateHisSysVers::AddHisVer(CVerUpdateHisVer* pHisVer)
{
	if (pHisVer == NULL)
	{
		return;
	}

	AddNewChild((CVerUpdateHisVer*)pHisVer->CloneEx(TRUE));

	RemoveExtraEntries();
}

void CVerUpdateHisSysVers::AddHisVer(const CString& strDateTime,int nCurrVerIdx,int nPrevVerIdx,const CString& strCurVer,const CString& strPrevVer)
{
	CVerUpdateHisVer *pVerUpdateHisVer = new CVerUpdateHisVer();
	if (pVerUpdateHisVer != NULL)
	{
		pVerUpdateHisVer->m_strDateTime = strDateTime;
		pVerUpdateHisVer->m_nCurrVerIdx = nCurrVerIdx;
		pVerUpdateHisVer->m_nPrevVerIdx = nPrevVerIdx;
		pVerUpdateHisVer->m_strCurrVer = strCurVer;
		pVerUpdateHisVer->m_strPrevVer = strPrevVer;

		AddNewChild(pVerUpdateHisVer);
		RemoveExtraEntries();
	}
}
