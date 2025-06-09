#include "stdafx.h"
#include "../../Module/api/GlobalConfigApi.h"
#include "GuideBookExportConfig.h"

#include "../../Module/Api/FileApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define g_strGuideBookExportConfigFile  _T("GuideBookExportConfig.xml")

CGuideBookExportConfig* CGuideBookExportConfig::g_pGuideBookExportConfig = NULL;
long CGuideBookExportConfig::g_nGuideBookExportConfigRef = 0;

CGuideBookExportConfig* CGuideBookExportConfig::Create()
{
	g_nGuideBookExportConfigRef++;

	if (g_nGuideBookExportConfigRef == 1)
	{
		CAutoTestXMLRWKeys::Create();
		g_pGuideBookExportConfig = new CGuideBookExportConfig();
		g_pGuideBookExportConfig->Open();
	}

	return g_pGuideBookExportConfig;
}

void CGuideBookExportConfig::Release()
{
	g_nGuideBookExportConfigRef--;

	if (g_nGuideBookExportConfigRef == 0)
	{
		CAutoTestXMLRWKeys::Release();
		delete g_pGuideBookExportConfig;
		g_pGuideBookExportConfig = NULL;
	}
}

CGuideBookExportConfig::CGuideBookExportConfig()
{
	//guidebook
	m_nExportGlobalDatas = 0; //ȫ������
	m_nExportJobGuide = 0; //��ҵָ��
	m_nExportExtendRptDef = 0;  //��չ����

	//guidebook-��������
	m_nExportGuideBookAttrGbxml = 0; //����ģ���ļ���Ϣ
	m_nExportGuideBookAttrPpxml = 0; //��Լģ����Ϣ
	m_nExportGuideBookAttrDvmxml = 0;  //ģ���ļ���Ϣ��device-model-file��

	//device
	m_nExportDeviceModule = 0; //�豸ģ��
	m_nExportSysParas = 0;  //ϵͳ����

	//Item
	m_nExportRptMap = 0; //����ӳ��
	m_nExportReports = 0; //��������

	//Item-��������
	m_nExportItemAttrSimplify = 0; //���Լ򻯣�������name��id

	//sysparaedit
	m_nExportSysParaEditValues = 0; //ϵͳ�����༭��Ŀ�Ĳ���

	//safety
	m_nExportSafetyDatas = 0; //���ݶ���
	m_nExportSafetyDllCall = 0;   //��̬�����
	m_nExportSafetyMsg = 0; //��ʾ��Ϣ

	//commoncmd
	m_nExportCmdPara = 0;  //�������
	m_nExportCmdDatas = 0; //����������
	m_nExportCmdDsvScript = 0; //ģ����֤�ű�

	//macrotest
	m_nExportMacroTestParas = 0;  //���������ܲ���

	//report
	m_nExportRptmapNotSaveNull = 0;   //������ӳ��Ϊ��ʱ�������汨��ӳ�����
	m_nExportRptOnlySaveBkmk = 0;   //ֻ��������ǩ������
	m_nExportRptOnlySaveLast = 0;   //ֻ�������һ�εı�������

	//script
	m_nExportScriptExprScript = 0;  //����жϱ��ʽ
	m_nExportScriptName = 0;     //script-name
	m_nExportScriptInit = 0;     //��ʼ���ű�
	m_nExportScriptRslt = 0;     //����ű�
}

CGuideBookExportConfig::~CGuideBookExportConfig()
{

}

long CGuideBookExportConfig::Open()
{
	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);

	m_strFile = (CString)_P_GetConfigPath();
	m_strFile += g_strGuideBookExportConfigFile;

	return OpenXmlFile(m_strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strGuideBookExportConfigKey, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
}

long CGuideBookExportConfig::Save()
{
#ifdef _PSX_QT_LINUX_
    return 1;
#endif

	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);

	CString strFile = (CString)_P_GetConfigPath();
	strFile += g_strGuideBookExportConfigFile;
	ClearFileReadOnlyAttr(strFile);
	SaveXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);

	return 1;
}

long CGuideBookExportConfig::XmlReadOwn(CXmlRWNodeBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAutoTestXMLRWKeys* pXmlKeys = (CAutoTestXMLRWKeys*)pXmlRWKeys;

	xml_GetElementText(pXmlKeys->m_strGuideBookExportGlobalDatasKey, oElement, m_nExportGlobalDatas);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportJobGuideKey, oElement, m_nExportJobGuide);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportExtendRptDefKey, oElement, m_nExportExtendRptDef);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportAttrGbxmlKey, oElement, m_nExportGuideBookAttrGbxml);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportAttrDvmxmlKey, oElement, m_nExportGuideBookAttrDvmxml);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportAttrPpxmlKey, oElement, m_nExportGuideBookAttrPpxml);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportDeviceModelKey, oElement, m_nExportDeviceModule);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportSysParasKey, oElement, m_nExportSysParas);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportRptMapKey, oElement, m_nExportRptMap);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportReportsKey, oElement, m_nExportReports);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportAttrSimplifyKey, oElement, m_nExportItemAttrSimplify);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportSysParaEditKey, oElement, m_nExportSysParaEditValues);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportSafetyDatasKey, oElement, m_nExportSafetyDatas);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportSafetyDllCallKey, oElement, m_nExportSafetyDllCall);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportSafetyMsgKey, oElement, m_nExportSafetyMsg);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportCmdParaKey, oElement, m_nExportCmdPara);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportCmdDatasKey, oElement, m_nExportCmdDatas);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportCmdDsvScriptKey, oElement, m_nExportCmdDsvScript);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportMacroTestParasKey, oElement, m_nExportMacroTestParas);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportRptMapNotSaveNullKey, oElement, m_nExportRptmapNotSaveNull);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportRptMapOnlySaveLastKey, oElement, m_nExportRptOnlySaveLast);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportReportOnlySaveBkmkKey, oElement, m_nExportRptOnlySaveBkmk);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportExprScriptKey, oElement, m_nExportScriptExprScript);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportScriptNameKey, oElement, m_nExportScriptName);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportScriptInitKey, oElement, m_nExportScriptInit);
	xml_GetElementText(pXmlKeys->m_strGuideBookExportScriptRsltKey, oElement, m_nExportScriptRslt);

	return 0;
}

long CGuideBookExportConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	CAutoTestXMLRWKeys* pXmlKeys = (CAutoTestXMLRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_strGuideBookExportGlobalDatasKey, oXMLDoc, oElement, m_nExportGlobalDatas);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportJobGuideKey, oXMLDoc, oElement, m_nExportJobGuide);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportExtendRptDefKey, oXMLDoc, oElement, m_nExportExtendRptDef);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportAttrGbxmlKey, oXMLDoc, oElement, m_nExportGuideBookAttrGbxml);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportAttrDvmxmlKey, oXMLDoc, oElement, m_nExportGuideBookAttrDvmxml);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportAttrPpxmlKey, oXMLDoc, oElement, m_nExportGuideBookAttrPpxml);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportDeviceModelKey, oXMLDoc, oElement, m_nExportDeviceModule);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportSysParasKey, oXMLDoc, oElement, m_nExportSysParas);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportRptMapKey, oXMLDoc, oElement, m_nExportRptMap);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportReportsKey, oXMLDoc, oElement, m_nExportReports);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportAttrSimplifyKey, oXMLDoc, oElement, m_nExportItemAttrSimplify);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportSysParaEditKey, oXMLDoc, oElement, m_nExportSysParaEditValues);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportSafetyDatasKey, oXMLDoc, oElement, m_nExportSafetyDatas);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportSafetyDllCallKey, oXMLDoc, oElement, m_nExportSafetyDllCall);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportSafetyMsgKey, oXMLDoc, oElement, m_nExportSafetyMsg);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportCmdParaKey, oXMLDoc, oElement, m_nExportCmdPara);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportCmdDatasKey, oXMLDoc, oElement, m_nExportCmdDatas);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportCmdDsvScriptKey, oXMLDoc, oElement, m_nExportCmdDsvScript);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportMacroTestParasKey, oXMLDoc, oElement, m_nExportMacroTestParas);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportRptMapNotSaveNullKey, oXMLDoc, oElement, m_nExportRptmapNotSaveNull);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportRptMapOnlySaveLastKey, oXMLDoc, oElement, m_nExportRptOnlySaveLast);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportReportOnlySaveBkmkKey, oXMLDoc, oElement, m_nExportRptOnlySaveBkmk);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportExprScriptKey, oXMLDoc, oElement, m_nExportScriptExprScript);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportScriptNameKey, oXMLDoc, oElement, m_nExportScriptName);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportScriptInitKey, oXMLDoc, oElement, m_nExportScriptInit);
	xml_SetElementText(pXmlKeys->m_strGuideBookExportScriptRsltKey, oXMLDoc, oElement, m_nExportScriptRslt);

	return 0;
}