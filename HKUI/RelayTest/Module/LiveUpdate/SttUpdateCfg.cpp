// SttUpdateCfg.cpp
//

#include "stdafx.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "SttUpdateCfg.h"

// CSttUpdateCfg
BSTR CSttUpdateCfg::m_strVerUpdateCfgKey = L"ver-update-cfg";
BSTR CSttUpdateCfg::m_strSysIDKey = L"sys-id";
BSTR CSttUpdateCfg::m_strVerIDKey = L"ver-id";
BSTR CSttUpdateCfg::m_strVerIdxKey = L"ver-idx";
BSTR CSttUpdateCfg::m_strTestAppIDKey = L"testapp-id";

CSttUpdateCfg* CSttUpdateCfg::g_pVerUpdateCfg = NULL;
long CSttUpdateCfg::g_nVerUpdateCfgRef = 0;

CSttUpdateCfg* CSttUpdateCfg::Create()
{
	g_nVerUpdateCfgRef++;

	if (g_nVerUpdateCfgRef == 1)
	{
		g_pVerUpdateCfg = new CSttUpdateCfg();
		if (!g_pVerUpdateCfg->Open())
		{
			g_pVerUpdateCfg->Save();
		}
	}

	return g_pVerUpdateCfg;
}

void CSttUpdateCfg::Release()
{
	g_nVerUpdateCfgRef--;

	if (g_nVerUpdateCfgRef == 0)
	{
		delete g_pVerUpdateCfg;
		g_pVerUpdateCfg = NULL;
	}
}

CSttUpdateCfg::CSttUpdateCfg()
{
	m_strSysID = _T("");
	m_strVerID = _T("");
	m_nVerIdx = 0;
	m_strTestAppID = _T("");
}

CSttUpdateCfg::~CSttUpdateCfg()
{
	
}

long CSttUpdateCfg::XmlReadOwn(CXmlRWNodeBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetElementText(m_strSysIDKey, oElement, m_strSysID);
	xml_GetElementText(m_strVerIDKey, oElement, m_strVerID);
	xml_GetElementText(m_strVerIdxKey, oElement, m_nVerIdx);
	xml_GetElementText(m_strTestAppIDKey, oElement, m_strTestAppID);

	return 1;
}

long CSttUpdateCfg::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetElementText(m_strSysIDKey, oXMLDoc, oElement, m_strSysID);
	xml_SetElementText(m_strVerIDKey, oXMLDoc, oElement, m_strVerID);
	xml_SetElementText(m_strVerIdxKey, oXMLDoc, oElement, m_nVerIdx);
	xml_SetElementText(m_strTestAppIDKey, oXMLDoc, oElement, m_strTestAppID);
	
	return 1;
}

BOOL CSttUpdateCfg::Open(const CString& strPath)
{
	if (strPath.IsEmpty())
	{
		m_strFile = _P_GetConfigPath();
		m_strFile += _T("VerUpdateCfg.xml");
	}
	else
	{
		m_strFile = strPath;
	}

	if (!IsFileExist(m_strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("版本更新配置文件：%s 不存在"),m_strFile.GetString());
		return FALSE;
	}

	return CExBaseObject::OpenXmlFile(m_strFile, m_strVerUpdateCfgKey, NULL);
}

BOOL CSttUpdateCfg::Save()
{
	return SaveXmlFile(m_strFile, NULL);
}
