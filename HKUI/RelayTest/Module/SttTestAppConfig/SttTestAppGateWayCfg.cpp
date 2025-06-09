#include "stdafx.h"
#include "SttTestAppGateWayCfg.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/API/FileApi.h"
#include "../SttGlobalDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BSTR CSttTestAppGateWayCfg::m_strSubIPKey = L"subIP";
BSTR CSttTestAppGateWayCfg::m_strTestAppGateWayCfgKey = L"stt-testapp-gateway-cfg";
BSTR CSttTestAppGateWayCfg::m_strMaskKey = L"mask";
BSTR CSttTestAppGateWayCfg::m_strGateWayKey = L"gateway";
BSTR CSttTestAppGateWayCfg::m_strAutoRegisterKey = L"auto-register";

CSttTestAppGateWayCfg* CSttTestAppGateWayCfg::g_pSttTestAppGateWayCfg = NULL;
long CSttTestAppGateWayCfg::g_nSttTestAppGateWayCfgRef = 0;

CSttTestAppGateWayCfg* CSttTestAppGateWayCfg::Create()
{
	g_nSttTestAppGateWayCfgRef++;

	if (g_nSttTestAppGateWayCfgRef == 1)
	{
		g_pSttTestAppGateWayCfg = new CSttTestAppGateWayCfg();

		if (!g_pSttTestAppGateWayCfg->Open())
		{
			g_pSttTestAppGateWayCfg->Save();
		}
	}

    return g_pSttTestAppGateWayCfg;
}

void CSttTestAppGateWayCfg::Release()
{
	g_nSttTestAppGateWayCfgRef--;

	if (g_nSttTestAppGateWayCfgRef == 0)
	{
		g_pSttTestAppGateWayCfg->Save();
		delete g_pSttTestAppGateWayCfg;
		g_pSttTestAppGateWayCfg = NULL;
	}
}

CSttTestAppGateWayCfg::CSttTestAppGateWayCfg()
{
    m_nAutoRegister = 0;
	m_strSubIP = _T("192.168.1.10");
	m_strGateWay = _T("192.168.1.1");
	m_strMask = _T("255.255.255.0");
}

CSttTestAppGateWayCfg::~CSttTestAppGateWayCfg()
{
	Save();
}

long CSttTestAppGateWayCfg::Open()
{
	m_strFile = (CString)_P_GetConfigPath();
	m_strFile += _T("SttTestAppGateWayCfg.xml");

	if (!IsFileExist(m_strFile))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("测试仪网关配置文件：%s 找不到！"),m_strFile.GetString());
		return 0;
	}

	return OpenXmlFile(m_strFile, m_strTestAppGateWayCfgKey, NULL);
}

long CSttTestAppGateWayCfg::Save()
{
#ifdef _PSX_QT_LINUX_
    return 1;
#endif

	SaveXmlFile(m_strFile, NULL);
	return 1;
}

long CSttTestAppGateWayCfg::XmlReadOwn(CXmlRWNodeBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetElementText(m_strSubIPKey, oElement, m_strSubIP);
	xml_GetElementText(m_strMaskKey, oElement, m_strMask);
	xml_GetElementText(m_strGateWayKey, oElement, m_strGateWay);
    xml_GetAttibuteValue(m_strAutoRegisterKey, oElement, m_nAutoRegister);

	return 0;
}

long CSttTestAppGateWayCfg::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetElementText(m_strSubIPKey, oXMLDoc, oElement, m_strSubIP);
	xml_SetElementText(m_strMaskKey, oXMLDoc, oElement, m_strMask);
	xml_SetElementText(m_strGateWayKey, oXMLDoc, oElement, m_strGateWay);
    xml_SetAttributeValue(m_strAutoRegisterKey, oElement, m_nAutoRegister);

	return 0;
}
