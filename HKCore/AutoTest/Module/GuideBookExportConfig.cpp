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
	m_nExportGlobalDatas = 0; //全局数据
	m_nExportJobGuide = 0; //作业指导
	m_nExportExtendRptDef = 0;  //扩展报告

	//guidebook-属性配置
	m_nExportGuideBookAttrGbxml = 0; //测试模板文件信息
	m_nExportGuideBookAttrPpxml = 0; //规约模板信息
	m_nExportGuideBookAttrDvmxml = 0;  //模型文件信息（device-model-file）

	//device
	m_nExportDeviceModule = 0; //设备模型
	m_nExportSysParas = 0;  //系统参数

	//Item
	m_nExportRptMap = 0; //报告映射
	m_nExportReports = 0; //报告数据

	//Item-属性配置
	m_nExportItemAttrSimplify = 0; //属性简化，仅保留name、id

	//sysparaedit
	m_nExportSysParaEditValues = 0; //系统参数编辑项目的参数

	//safety
	m_nExportSafetyDatas = 0; //数据定义
	m_nExportSafetyDllCall = 0;   //动态库调用
	m_nExportSafetyMsg = 0; //提示信息

	//commoncmd
	m_nExportCmdPara = 0;  //命令参数
	m_nExportCmdDatas = 0; //命令定义的数据
	m_nExportCmdDsvScript = 0; //模型验证脚本

	//macrotest
	m_nExportMacroTestParas = 0;  //电气量功能参数

	//report
	m_nExportRptmapNotSaveNull = 0;   //当报告映射为空时，不保存报告映射对象
	m_nExportRptOnlySaveBkmk = 0;   //只保存有书签的数据
	m_nExportRptOnlySaveLast = 0;   //只保存最后一次的报告数据

	//script
	m_nExportScriptExprScript = 0;  //结果判断表达式
	m_nExportScriptName = 0;     //script-name
	m_nExportScriptInit = 0;     //初始化脚本
	m_nExportScriptRslt = 0;     //结果脚本
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