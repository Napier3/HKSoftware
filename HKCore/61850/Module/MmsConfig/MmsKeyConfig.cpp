#include "stdafx.h"
#include "../../../Module/api/GlobalConfigApi.h"
#include "../../../Module/api/GloblaDrawFunctions.h"
#include "../../../Module/api/FileApi.h"
#include "MmsKeyConfig.h"

extern long OptFlds_BP[9];// = {1,1,1,1,1,0,1,0,0};
extern long OptFlds_RP[9];// = {1,1,1,1,1,0,0,0,1};
extern long TrgOps_UI[5];// = {1,0,0,0,0};
extern long g_nSetDeviceCheck;
extern long g_nUseEntryIDUpdate;
extern long g_nIntgPd;

extern ST_CHAR g_strTrgOps[NAMESIZE];
extern ST_CHAR g_strOptFlds[NAMESIZE];
extern long  g_nCanWriteActiveSG;
extern long  g_nWriteCtrlCheckMode;
extern long  g_nEnaWriteWait;
extern long  g_nEnaWriteWaitAfterSel;
extern long g_bMmsReadUseReport; 
extern long g_bResetOnlyClearReport; 

extern long g_nMaxReportCount;


CMmsKeyConfig::CMmsKeyConfig()
{
	strcpy(g_strTrgOps, "TrgOps");
	strcpy(g_strOptFlds, "OptFlds");
	g_nCanWriteActiveSG = 0;
	g_nWriteCtrlCheckMode = 0;
	g_nEnaWriteWait = 200;
	g_nEnaWriteWaitAfterSel = 200;
}

CMmsKeyConfig::~CMmsKeyConfig()
{

}

long CMmsKeyConfig::Open()
{
	m_strFile = (CString)_P_GetConfigPath();
	m_strFile += _T("MmsKeyConfig.xml");

	return OpenXmlFile(m_strFile, CMmsEngineConfigXmlRWKeys::g_pXmlKeys->m_strMmsKeyConfigKey, CMmsEngineConfigXmlRWKeys::g_pXmlKeys);
}

long CMmsKeyConfig::Save()
{
	ASSERT (CMmsEngineConfigXmlRWKeys::g_pXmlKeys != NULL);

	ClearFileReadOnlyAttr(m_strFile);
	SaveXmlFile(m_strFile, CMmsEngineConfigXmlRWKeys::g_pXmlKeys);

	return 1;
}

long CMmsKeyConfig::XmlReadOwn(CXmlRWNodeBase & oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMmsEngineConfigXmlRWKeys* pXmlKeys = (CMmsEngineConfigXmlRWKeys*)pXmlRWKeys;
	CString strTemp;

	xml_GetElementText(pXmlKeys->m_str_OptFlds_Key, oElement, strTemp);

	if (strTemp.GetLength() > 0)
	{
		CString_to_char(strTemp, g_strOptFlds);
	}

	strTemp.Empty();
	xml_GetElementText(pXmlKeys->m_str_TrgOps_Key, oElement, strTemp);

	if (strTemp.GetLength() > 0)
	{
		CString_to_char(strTemp, g_strTrgOps);
	}

	xml_GetElementText(pXmlKeys->m_strCanWriteActiveSGKey, oElement, g_nCanWriteActiveSG);
	xml_GetElementText(pXmlKeys->m_strWriteCtrlCheckModeKey, oElement, g_nWriteCtrlCheckMode);
	xml_GetElementText(pXmlKeys->m_strWriteDataAfterWaitKey, oElement, g_nEnaWriteWait);
	xml_GetElementText(pXmlKeys->m_strWriteDataAfterWaitAfterSelKey, oElement, g_nEnaWriteWaitAfterSel);

	ReadFlag(oElement, pXmlKeys->m_str_OptFlds_BR_Key, OptFlds_BP, 9);
	ReadFlag(oElement, pXmlKeys->m_str_OptFlds_RP_Key, OptFlds_RP, 9);
	ReadFlag(oElement, pXmlKeys->m_str_TrgOps_UI_Key, TrgOps_UI, 5);

	xml_GetElementText(pXmlKeys->m_strMmsReadUseReportKey, oElement, g_bMmsReadUseReport);
	xml_GetElementText(pXmlKeys->m_strMmsResetOnlyClearReportKey, oElement, g_bResetOnlyClearReport);
	xml_GetElementText(pXmlKeys->m_strMaxReportCountKey, oElement, g_nMaxReportCount);
	xml_GetElementText(pXmlKeys->m_strDevCheckKey, oElement, g_nSetDeviceCheck);
	xml_GetElementText(pXmlKeys->m_strUseEntryIDUpdateKey, oElement, g_nUseEntryIDUpdate);
	xml_GetElementText(pXmlKeys->m_strIntgPdKey, oElement, g_nIntgPd);

	if (g_nMaxReportCount > MAX_REPORT_COUNT)
	{
		g_nMaxReportCount = MAX_REPORT_COUNT;
	}

	if (g_nMaxReportCount < 100)
	{
		g_nMaxReportCount = 100;
	}

	return 0;
}

void CMmsKeyConfig::ReadFlag(CXmlRWNodeBase &oNode, BSTR bstrFlagNode, long *pnArrFlag, long nCount)
{
	CXmlRWNodeBase* oElement = oNode.GetChildNode(bstrFlagNode);

	if (oElement == NULL)
	{
		return;
	}

	long nIndex = 0;
	CString strText;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strText.Format(_T("D%d"), nIndex+1);
        oElement->xml_GetElementText(strText, pnArrFlag[nIndex]);
        //xml_GetElementText(strText, *oElement, pnArrFlag[nIndex]);
	}
}

long CMmsKeyConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMmsEngineConfigXmlRWKeys* pXmlKeys = (CMmsEngineConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_str_OptFlds_Key, oXMLDoc, oElement, CString(g_strOptFlds));
	xml_SetElementText(pXmlKeys->m_str_TrgOps_Key, oXMLDoc, oElement, CString(g_strTrgOps));
	xml_SetElementText(pXmlKeys->m_strCanWriteActiveSGKey, oXMLDoc, oElement, g_nCanWriteActiveSG);
	xml_SetElementText(pXmlKeys->m_strWriteCtrlCheckModeKey, oXMLDoc, oElement, g_nWriteCtrlCheckMode);
	xml_SetElementText(pXmlKeys->m_strWriteDataAfterWaitKey, oXMLDoc, oElement, g_nEnaWriteWait);
	xml_SetElementText(pXmlKeys->m_strMmsReadUseReportKey, oXMLDoc, oElement, g_bMmsReadUseReport);
	xml_SetElementText(pXmlKeys->m_strMmsResetOnlyClearReportKey, oXMLDoc, oElement, g_bResetOnlyClearReport);

	WriteFlag(oXMLDoc, oElement, pXmlKeys->m_str_OptFlds_BR_Key, OptFlds_BP, 9);
	WriteFlag(oXMLDoc, oElement, pXmlKeys->m_str_OptFlds_RP_Key, OptFlds_RP, 9);
	WriteFlag(oXMLDoc, oElement, pXmlKeys->m_str_TrgOps_UI_Key, TrgOps_UI, 5);

	xml_SetElementText(pXmlKeys->m_strWriteDataAfterWaitAfterSelKey, oXMLDoc, oElement, g_nEnaWriteWaitAfterSel);
	xml_SetElementText(pXmlKeys->m_strMaxReportCountKey, oXMLDoc, oElement, g_nMaxReportCount);
	xml_SetElementText(pXmlKeys->m_strDevCheckKey, oXMLDoc, oElement, g_nSetDeviceCheck);
	xml_SetElementText(pXmlKeys->m_strUseEntryIDUpdateKey, oXMLDoc, oElement, g_nUseEntryIDUpdate);
	xml_SetElementText(pXmlKeys->m_strIntgPdKey, oXMLDoc, oElement, g_nIntgPd);

	return 0;
}

void CMmsKeyConfig::WriteFlag(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, BSTR bstrFlagNode, long *pnArrFlag, long nCount)
{
	CXmlRWElementBase* oElement = NULL;
	oElement = oXMLDoc.CreateElement(bstrFlagNode,&oParent);
	oParent.AppendChild(*oElement);

	if (oElement == NULL)
	{
		return;
	}

	long nIndex = 0;
	CString strText;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strText.Format(_T("D%d"), nIndex+1);
        oElement->xml_SetElementText(strText, &oXMLDoc, pnArrFlag[nIndex]);
	}
}

