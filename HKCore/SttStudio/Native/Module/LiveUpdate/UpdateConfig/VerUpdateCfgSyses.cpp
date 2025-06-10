// VerUpdateCfgSyses.cpp : 实现文件
//

#include "stdafx.h"
#include "VerUpdateCfgSyses.h"

// CVerUpdateCfgSyses

CVerUpdateCfgSyses::CVerUpdateCfgSyses()
{
}

CVerUpdateCfgSyses::~CVerUpdateCfgSyses()
{
}

CExBaseObject* CVerUpdateCfgSyses::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CVerUpdateCfgXmlRWKeys *pXmlKeys = (CVerUpdateCfgXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strSysKey)
	{
		pNew = new CVerUpdateCfgSys();
	}

	return pNew;
}

CExBaseObject* CVerUpdateCfgSyses::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == VERUPDATECFGCLASSID_SYS)
	{
		pNew = new CVerUpdateCfgSys();
	}

	return pNew;
}

CVerUpdateCfgSys* CVerUpdateCfgSyses::FindByIdxSys(int nIdxSys)
{
	CVerUpdateCfgSys* pCfgSys = NULL;

	POS pos = GetHeadPosition();

	while (pos)
	{
		pCfgSys = (CVerUpdateCfgSys*)GetNext(pos);
		if (pCfgSys->GetIdxSys() == nIdxSys)
		{
			return pCfgSys;
		}
	}

	return NULL;
}

CVerUpdateCfgSys* CVerUpdateCfgSyses::FindByRunPath(const CString& strRunPath)
{
	CVerUpdateCfgSys* pCfgSys = NULL;

	POS pos = GetHeadPosition();

	while (pos)
	{
		pCfgSys = (CVerUpdateCfgSys*)GetNext(pos);
		if (pCfgSys->GetRunPath().CompareNoCase(strRunPath)==0)
		{
			return pCfgSys;
		}
	}

	return NULL;
}

void CVerUpdateCfgSyses::DeleteInvalidCfgSys(CExBaseList& oValidList)
{
	CVerUpdateCfgSys *pCfgSys = NULL;
	CExBaseObject *pObj = NULL;

	POS pos = GetHeadPosition();
	while (pos)
	{
		pCfgSys = (CVerUpdateCfgSys*)GetNext(pos);
		
		if (pCfgSys == NULL)
		{
			return;
		}

		POS pos1 = oValidList.GetHeadPosition();
		while (pos1)
		{
			pObj = oValidList.GetNext(pos1);
			if (pCfgSys == pObj)
			{
				break;
			}
		}

		if (pCfgSys == pObj)
			continue;
		else
		{
			Delete(pCfgSys);
		}
	}
}

void CVerUpdateCfgSyses::DeleteInvalidCfgSys(CVerUpdateCfgSys* pCfgSys)
{
	CVerUpdateCfgSys* pTempCfgSys = NULL;

	CExBaseList oValidList;
	POS pos = GetHeadPosition();

	while (pos)
	{
		pTempCfgSys = (CVerUpdateCfgSys*)GetNext(pos);
		if (pTempCfgSys == pCfgSys)
		{
			continue;
		}

		if (pTempCfgSys->GetIdxSys()==pCfgSys->GetIdxSys())
		{
			oValidList.AddTail(pTempCfgSys);
		}
	}

	CExBaseObject *pObj = NULL;
	POS pos1 = oValidList.GetHeadPosition();
	while (pos1)
	{
		pObj = oValidList.GetNext(pos1);
		Delete(pObj);
	}

	oValidList.RemoveAll();
}