#include "stdafx.h"
#include "RdReadConfig.h"
#include "..\..\..\Module\API\FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BSTR CRdReadConfig::m_strRdConfigKey = L"rd-config";
BSTR CRdReadConfig::m_strSerialPortKey = L"serial-port";


// BSTR CRdReadConfig::m_strIaAmpKey[0] = L"Ia-Amp";
// BSTR CRdReadConfig::m_strIaPhaseKey[0] = L"Ia-Phase";
// BSTR CRdReadConfig::m_strIaFreKey[0] = L"Ia-Fre";
// BSTR CRdReadConfig::m_strIbAmpKey[0] = L"Ib-Amp";
// BSTR CRdReadConfig::m_strIbPhaseKey[0] = L"Ib-Phase";
// BSTR CRdReadConfig::m_strIbFreKey[0] = L"Ib-Fre";
// BSTR CRdReadConfig::m_strIcAmpKey[0] = L"Ic-Amp";
// BSTR CRdReadConfig::m_strIcPhaseKey[0] = L"Ic-Phase";
// BSTR CRdReadConfig::m_strIcFreKey[0] = L"Ic-Fre";
// 
// BSTR CRdReadConfig::m_strUaAmpKey[0] = L"Ua-Amp";
// BSTR CRdReadConfig::m_strUaPhaseKey[0] = L"Ua-Phase";
// BSTR CRdReadConfig::m_strUaFreKey[0] = L"Ua-Fre";
// BSTR CRdReadConfig::m_strUbAmpKey[0] = L"Ub-Amp";
// BSTR CRdReadConfig::m_strUbPhaseKey[0] = L"Ub-Phase";
// BSTR CRdReadConfig::m_strUbFreKey[0] = L"Ub-Fre";
// BSTR CRdReadConfig::m_strUcAmpKey[0] = L"Uc-Amp";
// BSTR CRdReadConfig::m_strUcPhaseKey[0] = L"Uc-Phase";
// BSTR CRdReadConfig::m_strUcFreKey[0] = L"Uc-Fre";
// 
// BSTR CRdReadConfig::m_strIaAmpKey[1] = L"Ia-Amp-Harm2";
// BSTR CRdReadConfig::m_strIaPhaseKey[1] = L"Ia-Phase-Harm2";
// BSTR CRdReadConfig::m_strIaFreKey[1] = L"Ia-Dist-Harm2";
// BSTR CRdReadConfig::m_strIbAmpKey[1] = L"Ib-Amp-Harm2";
// BSTR CRdReadConfig::m_strIbPhaseKey[1] = L"Ib-Phase-Harm2";
// BSTR CRdReadConfig::m_strIbFreKey[1] = L"Ib-Dist-Harm2";
// BSTR CRdReadConfig::m_strIcAmpKey[1] = L"Ic-Amp-Harm2";
// BSTR CRdReadConfig::m_strIcPhaseKey[1] = L"Ic-Phase-Harm2";
// BSTR CRdReadConfig::m_strIcFreKey[1] = L"Ic-Dist-Harm2";
// 
// BSTR CRdReadConfig::m_strUaAmpKey[1] = L"Ua-Amp-Harm2";
// BSTR CRdReadConfig::m_strUaPhaseKey[1] = L"Ua-Phase-Harm2";
// BSTR CRdReadConfig::m_strUaFreKey[1] = L"Ua-Dist-Harm2";
// BSTR CRdReadConfig::m_strUbAmpKey[1] = L"Ub-Amp-Harm2";
// BSTR CRdReadConfig::m_strUbPhaseKey[1] = L"Ub-Phase-Harm2";
// BSTR CRdReadConfig::m_strUbFreKey[1] = L"Ub-Dist-Harm2";
// BSTR CRdReadConfig::m_strUcAmpKey[1] = L"Uc-Amp-Harm2";
// BSTR CRdReadConfig::m_strUcPhaseKey[1] = L"Uc-Phase-Harm2";
// BSTR CRdReadConfig::m_strUcFreKey[1] = L"Uc-Dist-Harm2";

BSTR CRdReadConfig::m_strUaTHDKey = L"Ua-THD";
BSTR CRdReadConfig::m_strUbTHDKey = L"Ub-THD";
BSTR CRdReadConfig::m_strUcTHDKey = L"Uc-THD";
BSTR CRdReadConfig::m_strIaTHDKey = L"Ia-THD";
BSTR CRdReadConfig::m_strIbTHDKey = L"Ib-THD";
BSTR CRdReadConfig::m_strIcTHDKey = L"Ic-THD";

	
CRdReadConfig* CRdReadConfig::g_pOAMngrSvrConfig = NULL;
long CRdReadConfig::g_nOAMngrSvrConfigRef = 0;

CRdReadConfig* CRdReadConfig::Create()
{
	g_nOAMngrSvrConfigRef++;

	if (g_nOAMngrSvrConfigRef == 1)
	{
		g_pOAMngrSvrConfig = new CRdReadConfig();

		g_pOAMngrSvrConfig->m_strIaAmpKey[0] = L"Ia-Amp";
		g_pOAMngrSvrConfig->m_strIaPhaseKey[0] = L"Ia-Phase";
		g_pOAMngrSvrConfig->m_strIaFreKey[0] = L"Ia-Fre";
		g_pOAMngrSvrConfig->m_strIbAmpKey[0] = L"Ib-Amp";
		g_pOAMngrSvrConfig->m_strIbPhaseKey[0] = L"Ib-Phase";
		g_pOAMngrSvrConfig->m_strIbFreKey[0] = L"Ib-Fre";
		g_pOAMngrSvrConfig->m_strIcAmpKey[0] = L"Ic-Amp";
		g_pOAMngrSvrConfig->m_strIcPhaseKey[0] = L"Ic-Phase";
		g_pOAMngrSvrConfig->m_strIcFreKey[0] = L"Ic-Fre";
		
		g_pOAMngrSvrConfig->m_strUaAmpKey[0] = L"Ua-Amp";
		g_pOAMngrSvrConfig->m_strUaPhaseKey[0] = L"Ua-Phase";
		g_pOAMngrSvrConfig->m_strUaFreKey[0] = L"Ua-Fre";
		g_pOAMngrSvrConfig->m_strUbAmpKey[0] = L"Ub-Amp";
		g_pOAMngrSvrConfig->m_strUbPhaseKey[0] = L"Ub-Phase";
		g_pOAMngrSvrConfig->m_strUbFreKey[0] = L"Ub-Fre";
		g_pOAMngrSvrConfig->m_strUcAmpKey[0] = L"Uc-Amp";
		g_pOAMngrSvrConfig->m_strUcPhaseKey[0] = L"Uc-Phase";
		g_pOAMngrSvrConfig->m_strUcFreKey[0] = L"Uc-Fre";
		CString strTmp;

		for (int nIndex = 1;nIndex<50;nIndex++)
		{
			strTmp.Format(_T("Ia-Amp-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strIaAmpKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Ia-Phase-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strIaPhaseKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Ia-Dist-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strIaFreKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Ib-Amp-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strIbAmpKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Ib-Phase-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strIbPhaseKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Ib-Dist-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strIbFreKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Ic-Amp-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strIcAmpKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Ic-Phase-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strIcPhaseKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Ic-Dist-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strIcFreKey[nIndex] = strTmp.AllocSysString();

			strTmp.Format(_T("Ua-Amp-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strUaAmpKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Ua-Phase-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strUaPhaseKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Ua-Dist-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strUaFreKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Ub-Amp-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strUbAmpKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Ub-Phase-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strUbPhaseKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Ub-Dist-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strUbFreKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Uc-Amp-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strUcAmpKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Uc-Phase-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strUcPhaseKey[nIndex] = strTmp.AllocSysString();
			strTmp.Format(_T("Uc-Dist-Harm%d"),nIndex+1);
			g_pOAMngrSvrConfig->m_strUcFreKey[nIndex] = strTmp.AllocSysString();
		}

		if (!g_pOAMngrSvrConfig->Open())
		{
			g_pOAMngrSvrConfig->Save();
		}
	}

	return g_pOAMngrSvrConfig;
}

void CRdReadConfig::Release()
{
	g_nOAMngrSvrConfigRef--;

	if (g_nOAMngrSvrConfigRef == 0)
	{
		delete g_pOAMngrSvrConfig;
		g_pOAMngrSvrConfig = NULL;
	}
}

CRdReadConfig::CRdReadConfig()
{
	m_nSerialPort = 1;

	for (int nIndex = 0;nIndex<50;nIndex++)
	{
		if (nIndex == 0)
		{
			m_strIaAmpDesc[0] = "IA幅值";
			m_strIaPhaseDesc[0] = "IA相位";
			m_strIaFreDesc[0] = _T("IA频率");
			m_strIbAmpDesc[0] = "IB幅值";
			m_strIbPhaseDesc[0] = "IB相位";
			m_strIbFreDesc[0] = _T("IB频率");
			m_strIcAmpDesc[0] = "IC幅值";
			m_strIcPhaseDesc[0] = "IC相位";
			m_strIcFreDesc[0] = _T("IC频率");

			m_strUaAmpDesc[0] = "UA幅值";
			m_strUaPhaseDesc[0] = "UA相位";
			m_strUaFreDesc[0] = _T("UA频率");
			m_strUbAmpDesc[0] = "UB幅值";
			m_strUbPhaseDesc[0] = "UB相位";
			m_strUbFreDesc[0] = _T("UB频率");
			m_strUcAmpDesc[0] = "UC幅值";
			m_strUcPhaseDesc[0] = "UC相位";
			m_strUcFreDesc[0] = _T("UC频率");		
		} 
		else
		{
			m_strIaAmpDesc[nIndex].Format(_T("A相电流-%ld次谐波幅值"),nIndex+1);
			m_strIaPhaseDesc[nIndex].Format(_T("A相电流-%ld次谐波相位"),nIndex+1);
			m_strIaFreDesc[nIndex].Format(_T("A相电流-%ld次谐波失真度"),nIndex+1);
			m_strIbAmpDesc[nIndex].Format(_T("B相电流-%ld次谐波幅值"),nIndex+1);
			m_strIbPhaseDesc[nIndex].Format(_T("B相电流-%ld次谐波相位"),nIndex+1);
			m_strIbFreDesc[nIndex].Format(_T("B相电流-%ld次谐波失真度"),nIndex+1);
			m_strIcAmpDesc[nIndex].Format(_T("C相电流-%ld次谐波幅值"),nIndex+1);
			m_strIcPhaseDesc[nIndex].Format(_T("C相电流-%ld次谐波相位"),nIndex+1);
			m_strIcFreDesc[nIndex].Format(_T("C相电流-%ld次谐波失真度"),nIndex+1);

			m_strUaAmpDesc[nIndex].Format(_T("A相电压-%ld次谐波幅值"),nIndex+1);
			m_strUaPhaseDesc[nIndex].Format(_T("A相电压-%ld次谐波相位"),nIndex+1);
			m_strUaFreDesc[nIndex].Format(_T("A相电压-%ld次谐波失真度"),nIndex+1);
			m_strUbAmpDesc[nIndex].Format(_T("B相电压-%ld次谐波幅值"),nIndex+1);
			m_strUbPhaseDesc[nIndex].Format(_T("B相电压-%ld次谐波相位"),nIndex+1);
			m_strUbFreDesc[nIndex].Format(_T("B相电压-%ld次谐波失真度"),nIndex+1);
			m_strUcAmpDesc[nIndex].Format(_T("C相电压-%ld次谐波幅值"),nIndex+1);
			m_strUcPhaseDesc[nIndex].Format(_T("C相电压-%ld次谐波相位"),nIndex+1);
			m_strUcFreDesc[nIndex].Format(_T("C相电压-%ld次谐波失真度"),nIndex+1);		
		}
	}


	m_strUaTHDDesc = _T("Ua总谐波畸变率");
	m_strUbTHDDesc = _T("Ub总谐波畸变率");
	m_strUcTHDDesc = _T("Uc总谐波畸变率");
	m_strIaTHDDesc = _T("Ia总谐波畸变率");
	m_strIbTHDDesc = _T("Ib总谐波畸变率");
	m_strIcTHDDesc = _T("Ic总谐波畸变率");
}

CRdReadConfig::~CRdReadConfig()
{
	
}

long CRdReadConfig::Open()
{
	m_strFile = (CString)_P_GetConfigPath();
	m_strFile += _T("RD33_ReadConfig.xml");

	return OpenXmlFile(m_strFile, m_strRdConfigKey, NULL);
}

long CRdReadConfig::Save()
{
	ClearFileReadOnlyAttr(m_strFile);
	SaveXmlFile(m_strFile, NULL);
		
	return 1;
}

long CRdReadConfig::XmlReadOwn(CXmlRWNodeBase & oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetElementText(m_strSerialPortKey, oElement, m_nSerialPort);

	for (int nIndex = 0;nIndex<30;nIndex++)
	{
		xml_GetElementText(m_strIaAmpKey[nIndex], oElement, m_strIaAmpDesc[nIndex]);
		xml_GetElementText(m_strIaPhaseKey[nIndex], oElement, m_strIaPhaseDesc[nIndex]);
		xml_GetElementText(m_strIaFreKey[nIndex], oElement, m_strIaFreDesc[nIndex]);
		xml_GetElementText(m_strIbAmpKey[nIndex], oElement, m_strIbAmpDesc[nIndex]);
		xml_GetElementText(m_strIbPhaseKey[nIndex], oElement, m_strIbPhaseDesc[nIndex]);
		xml_GetElementText(m_strIbFreKey[nIndex], oElement, m_strIbFreDesc[nIndex]);
		xml_GetElementText(m_strIcAmpKey[nIndex], oElement, m_strIcAmpDesc[nIndex]);
		xml_GetElementText(m_strIcPhaseKey[nIndex], oElement, m_strIcPhaseDesc[nIndex]);
		xml_GetElementText(m_strIcFreKey[nIndex], oElement, m_strIcFreDesc[nIndex]);

		xml_GetElementText(m_strUaAmpKey[nIndex], oElement, m_strUaAmpDesc[nIndex]);
		xml_GetElementText(m_strUaPhaseKey[nIndex], oElement, m_strUaPhaseDesc[nIndex]);
		xml_GetElementText(m_strUaFreKey[nIndex], oElement, m_strUaFreDesc[nIndex]);
		xml_GetElementText(m_strUbAmpKey[nIndex], oElement, m_strUbAmpDesc[nIndex]);
		xml_GetElementText(m_strUbPhaseKey[nIndex], oElement, m_strUbPhaseDesc[nIndex]);
		xml_GetElementText(m_strUbFreKey[nIndex], oElement, m_strUbFreDesc[nIndex]);
		xml_GetElementText(m_strUcAmpKey[nIndex], oElement, m_strUcAmpDesc[nIndex]);
		xml_GetElementText(m_strUcPhaseKey[nIndex], oElement, m_strUcPhaseDesc[nIndex]);
		xml_GetElementText(m_strUcFreKey[nIndex], oElement, m_strUcFreDesc[nIndex]);
	}

	xml_GetElementText(m_strUaTHDKey, oElement, m_strUaTHDDesc);
	xml_GetElementText(m_strUbTHDKey, oElement, m_strUbTHDDesc);
	xml_GetElementText(m_strUcTHDKey, oElement, m_strUcTHDDesc);
	xml_GetElementText(m_strIaTHDKey, oElement, m_strIaTHDDesc);
	xml_GetElementText(m_strIbTHDKey, oElement, m_strIbTHDDesc);
	xml_GetElementText(m_strIcTHDKey, oElement, m_strIcTHDDesc);
	return 0;
}

long CRdReadConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetElementText(m_strSerialPortKey, oXMLDoc, oElement, m_nSerialPort);

	for (int nIndex = 0;nIndex<30;nIndex++)
	{
		xml_SetElementText(m_strIaAmpKey[nIndex], oXMLDoc, oElement, m_strIaAmpDesc[nIndex]);
		xml_SetElementText(m_strIaPhaseKey[nIndex], oXMLDoc, oElement, m_strIaPhaseDesc[nIndex]);
		xml_SetElementText(m_strIaFreKey[nIndex], oXMLDoc, oElement, m_strIaFreDesc[nIndex]);
		xml_SetElementText(m_strIbAmpKey[nIndex], oXMLDoc, oElement, m_strIbAmpDesc[nIndex]);
		xml_SetElementText(m_strIbPhaseKey[nIndex], oXMLDoc, oElement, m_strIbPhaseDesc[nIndex]);
		xml_SetElementText(m_strIbFreKey[nIndex], oXMLDoc, oElement, m_strIbFreDesc[nIndex]);
		xml_SetElementText(m_strIcAmpKey[nIndex], oXMLDoc, oElement, m_strIcAmpDesc[nIndex]);
		xml_SetElementText(m_strIcPhaseKey[nIndex], oXMLDoc, oElement, m_strIcPhaseDesc[nIndex]);
		xml_SetElementText(m_strIcFreKey[nIndex], oXMLDoc, oElement, m_strIcFreDesc[nIndex]);

		xml_SetElementText(m_strUaAmpKey[nIndex], oXMLDoc, oElement, m_strUaAmpDesc[nIndex]);
		xml_SetElementText(m_strUaPhaseKey[nIndex], oXMLDoc, oElement, m_strUaPhaseDesc[nIndex]);
		xml_SetElementText(m_strUaFreKey[nIndex], oXMLDoc, oElement, m_strUaFreDesc[nIndex]);
		xml_SetElementText(m_strUbAmpKey[nIndex], oXMLDoc, oElement, m_strUbAmpDesc[nIndex]);
		xml_SetElementText(m_strUbPhaseKey[nIndex], oXMLDoc, oElement, m_strUbPhaseDesc[nIndex]);
		xml_SetElementText(m_strUbFreKey[nIndex], oXMLDoc, oElement, m_strUbFreDesc[nIndex]);
		xml_SetElementText(m_strUcAmpKey[nIndex], oXMLDoc, oElement, m_strUcAmpDesc[nIndex]);
		xml_SetElementText(m_strUcPhaseKey[nIndex], oXMLDoc, oElement, m_strUcPhaseDesc[nIndex]);
		xml_SetElementText(m_strUcFreKey[nIndex], oXMLDoc, oElement, m_strUcFreDesc[nIndex]);
	}

	xml_SetElementText(m_strUaTHDKey, oXMLDoc, oElement, m_strUaTHDDesc);
	xml_SetElementText(m_strUbTHDKey, oXMLDoc, oElement, m_strUbTHDDesc);
	xml_SetElementText(m_strUcTHDKey, oXMLDoc, oElement, m_strUcTHDDesc);
	xml_SetElementText(m_strIaTHDKey, oXMLDoc, oElement, m_strIaTHDDesc);
	xml_SetElementText(m_strIbTHDKey, oXMLDoc, oElement, m_strIbTHDDesc);
	xml_SetElementText(m_strIcTHDKey, oXMLDoc, oElement, m_strIcTHDDesc);
	return 0;
}

