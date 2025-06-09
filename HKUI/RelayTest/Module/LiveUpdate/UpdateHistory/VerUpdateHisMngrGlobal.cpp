// VerUpdateHisMngrGlobal.cpp : 实现文件
//

#include "stdafx.h"
#include "VerUpdateHisMngrGlobal.h"

CVerUpdateHisXmlRWKeys* CVerUpdateHisXmlRWKeys::g_pXmlKeys = NULL;
long CVerUpdateHisXmlRWKeys::g_nVERUPDATEHISXMLRef = 0;

// CVerUpdateHisXmlRWKeys

CVerUpdateHisXmlRWKeys::CVerUpdateHisXmlRWKeys()
{
	m_strSysMngrKey = L"sys-mngr";
	m_strSysVersionsKey = L"sys_vers";
	m_strVersionKey = L"ver";
	m_strDateTimeKey = L"datetime";
	m_strCurrVerKey = L"curr_ver";
	m_strPrevVerKey = L"prev_ver";
	m_strCurrVerIdxKey = L"curr_veridx";
	m_strPrevVerIdxKey = L"prev_veridx";
	m_strMaxEntriesKey = L"max_entries";
}

CVerUpdateHisXmlRWKeys::~CVerUpdateHisXmlRWKeys()
{
}

CVerUpdateHisXmlRWKeys* CVerUpdateHisXmlRWKeys::Create()
{
	g_nVERUPDATEHISXMLRef++;

	if (g_nVERUPDATEHISXMLRef == 1)
	{
		g_pXmlKeys = new CVerUpdateHisXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CVerUpdateHisXmlRWKeys::Release()
{
	g_nVERUPDATEHISXMLRef--;

	if (g_nVERUPDATEHISXMLRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}