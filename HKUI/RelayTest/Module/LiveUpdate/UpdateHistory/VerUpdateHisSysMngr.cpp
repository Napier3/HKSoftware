// VerUpdateHisSysMngr.cpp : 实现文件
//

#include "stdafx.h"

#include "VerUpdateHisSysMngr.h"
#include "VerUpdateHisSysVers.h"
#include "../../../../Module/API/FileApi.h"
#include "../../../../Module/API/GlobalConfigApi.h"

#include "../SttLiveUpdateDef.h"

// CVerUpdateHisSysMngr

CVerUpdateHisSysMngr::CVerUpdateHisSysMngr()
{
	m_nMaxEntries = 5;
}

CVerUpdateHisSysMngr::~CVerUpdateHisSysMngr()
{
}

long CVerUpdateHisSysMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateHisXmlRWKeys *pXmlKeys = (CVerUpdateHisXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strMaxEntriesKey, oNode, m_nMaxEntries);
	
	return 0;
}

long CVerUpdateHisSysMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateHisXmlRWKeys *pXmlKeys = (CVerUpdateHisXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strMaxEntriesKey, oElement, m_nMaxEntries);
	
	return 0;
}

CExBaseObject* CVerUpdateHisSysMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CVerUpdateHisXmlRWKeys *pXmlKeys = (CVerUpdateHisXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strSysVersionsKey)
	{
		pNew = new CVerUpdateHisSysVers();
	}

	return pNew;
}

CExBaseObject* CVerUpdateHisSysMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == VERUPDATEHISCLASSID_SYSVERS)
	{
		pNew = new CVerUpdateHisSysVers();
	}

	return pNew;
}

CString CVerUpdateHisSysMngr::GetHistoryFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += LIVEUPDATE_CFG_HIS;

	return strFile;
}

BOOL CVerUpdateHisSysMngr::Open()
{
	CString strFile = GetHistoryFile();

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("版本更新记录文件：%s 不存在"),strFile.GetString());
		return FALSE;
	}

	return CExBaseObject::OpenXmlFile(strFile, CVerUpdateHisXmlRWKeys::SysMngrKey(), CVerUpdateHisXmlRWKeys::g_pXmlKeys);
}

BOOL CVerUpdateHisSysMngr::Save()
{
	CString strFile = GetHistoryFile();
	return CExBaseObject::SaveXmlFile(strFile, CVerUpdateHisXmlRWKeys::g_pXmlKeys);
}

int CVerUpdateHisSysMngr::GetSysLocalVerIdx(const CString& strSysName)
{
	CVerUpdateHisSysVers* pHisSysVers = (CVerUpdateHisSysVers*)FindByName(strSysName);

	if (pHisSysVers != NULL)
	{
		return pHisSysVers->GetLocalCurrVerIdx();
	}
	else
	{
		return 0;
	}
}

CString CVerUpdateHisSysMngr::GetSysLocalVer(const CString& strSysName)
{
	CVerUpdateHisSysVers* pHisSysVers = (CVerUpdateHisSysVers*)FindByName(strSysName);

	if (pHisSysVers != NULL)
	{
		return pHisSysVers->GetLocalCurrVer();
	}
	else
	{
		return _T("初始版");
	}
}

int CVerUpdateHisSysMngr::GetSysLocalVerIdx(int nSysIdx)
{
	CVerUpdateHisSysVers* pHisSysVers = NULL;

	POS pos = GetHeadPosition();
	while (pos)
	{
		pHisSysVers = (CVerUpdateHisSysVers*)GetNext(pos);
		if ( CString_To_long(pHisSysVers->m_strID) == nSysIdx )
		{
			return pHisSysVers->GetLocalCurrVerIdx();
		}
	}

	return 0;
}

CString CVerUpdateHisSysMngr::GetSysLocalVer(int nSysIdx)
{
	CString strLocalVer(_T(""));
	CVerUpdateHisSysVers* pHisSysVers = NULL;

	POS pos = GetHeadPosition();
	while (pos)
	{
		pHisSysVers = (CVerUpdateHisSysVers*)GetNext(pos);
		if ( CString_To_long(pHisSysVers->m_strID) == nSysIdx )
		{
			strLocalVer = pHisSysVers->GetLocalCurrVer();
			break;
		}
	}

	if (strLocalVer == _T(""))
	{
		strLocalVer = _T("初始版");
	}

	return strLocalVer;
}
