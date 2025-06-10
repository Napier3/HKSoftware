// VerUpdateCfgMaps.cpp : 实现文件
//

#include "stdafx.h"
#include "VerUpdateCfgMaps.h"

// CVerUpdateCfgMaps

CVerUpdateCfgMaps::CVerUpdateCfgMaps()
{
}

CVerUpdateCfgMaps::~CVerUpdateCfgMaps()
{
}

CExBaseObject* CVerUpdateCfgMaps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CVerUpdateCfgXmlRWKeys *pXmlKeys = (CVerUpdateCfgXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strMapKey)
	{
		pNew = new CVerUpdateCfgMap();
	}

	return pNew;
}

CExBaseObject* CVerUpdateCfgMaps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == VERUPDATECFGCLASSID_MAP)
	{
		pNew = new CVerUpdateCfgMap();
	}

	return pNew;
}

CVerUpdateCfgMap* CVerUpdateCfgMaps::AddMap(const CString& strShellPath,int nIdxSys)
{
	if (strShellPath.IsEmpty() || nIdxSys<=0)
	{
		return NULL;
	}

	CVerUpdateCfgMap* pCfgMap = FindByShellPath(strShellPath);

	if (pCfgMap)
	{
		pCfgMap->SetIdxSys(nIdxSys);
	}
	else
	{
		pCfgMap = new CVerUpdateCfgMap;
		pCfgMap->SetShellPath(strShellPath);
		pCfgMap->SetIdxSys(nIdxSys);

		AddNewChild(pCfgMap);
	}

	return pCfgMap;
}

CVerUpdateCfgMap* CVerUpdateCfgMaps::FindByShellPath(const CString& strShellPath)
{
	CVerUpdateCfgMap* pCfgMap = NULL;

	POS pos = GetHeadPosition();

	while (pos)
	{
		pCfgMap = (CVerUpdateCfgMap*)GetNext(pos);

		if (pCfgMap->GetShellPath().CompareNoCase(strShellPath)==0)
		{
			return pCfgMap;
		}
	}

	return NULL;
}

void CVerUpdateCfgMaps::DeleteByShellPath(const CString& strShellPath)
{
	CVerUpdateCfgMap* pCfgMap = NULL;

	POS pos = GetHeadPosition();
	while (pos)
	{
		pCfgMap = (CVerUpdateCfgMap*)GetNext(pos);
		
		if (pCfgMap->GetShellPath().CompareNoCase(strShellPath)==0)
		{
			Delete(pCfgMap);
		}
	}
}