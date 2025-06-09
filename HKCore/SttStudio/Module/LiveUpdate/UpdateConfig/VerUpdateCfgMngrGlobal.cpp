// VerUpdateCfgMngrGlobal.cpp : 实现文件
//

#include "stdafx.h"
#include "VerUpdateCfgMngrGlobal.h"

CVerUpdateCfgXmlRWKeys* CVerUpdateCfgXmlRWKeys::g_pXmlKeys = NULL;
long CVerUpdateCfgXmlRWKeys::g_nVERUPDATECFGXMLRef = 0;

// CVerUpdateCfgXmlRWKeys

CVerUpdateCfgXmlRWKeys::CVerUpdateCfgXmlRWKeys()
{
	m_strVerUpdateCfgKey = L"ver-update-cfg";
	m_strYunKey = L"yun";
	m_strIPKey = L"ip";
	m_strPortKey = L"port";
	m_strFtpPortKey = L"ftpport";
	m_strSysesKey = L"syses";
	m_strSysKey = L"sys";
	m_strIdxSysKey = L"idx";
	m_strTypeKey = L"type";
	m_strRunPathKey = L"run_path";
	m_strVerPathKey = L"ver_path";
	m_strBackupPathKey = L"bk_path";
	m_strTimeOutKey = L"time_out";
	m_strShellPathKey = L"shell_path";
	m_strLocalKey = L"local";
}

CVerUpdateCfgXmlRWKeys::~CVerUpdateCfgXmlRWKeys()
{
}

CVerUpdateCfgXmlRWKeys* CVerUpdateCfgXmlRWKeys::Create()
{
	g_nVERUPDATECFGXMLRef++;

	if (g_nVERUPDATECFGXMLRef == 1)
	{
		g_pXmlKeys = new CVerUpdateCfgXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CVerUpdateCfgXmlRWKeys::Release()
{
	g_nVERUPDATECFGXMLRef--;

	if (g_nVERUPDATECFGXMLRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}