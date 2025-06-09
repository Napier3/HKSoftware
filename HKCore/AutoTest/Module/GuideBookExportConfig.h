#pragma once

/*
	功能描述：自动测试GuideBook的xml文件导出配置；
	关联文件：GuideBookExportConfig.xml
*/
#include "../../Module/BaseClass/ExBaseObject.h"
#include "AutoTestXMLRWKeys.h"


class CGuideBookExportConfig : public CExBaseObject
{
private:
	CGuideBookExportConfig();
	virtual ~CGuideBookExportConfig();

public:
	//guidebook
	long m_nExportGlobalDatas; //全局数据  已实现
	long m_nExportJobGuide; //作业指导   已实现
	long m_nExportExtendRptDef;  //扩展报告  已实现

	//guidebook-属性配置
	long m_nExportGuideBookAttrGbxml; //测试模板文件信息  需要在CGuideBook类增加属性
	long m_nExportGuideBookAttrPpxml; //规约模板信息
	long m_nExportGuideBookAttrDvmxml;  //模型文件信息（device-model-file）

	//device
	long m_nExportDeviceModule; //设备模型   已实现
	long m_nExportSysParas;  //系统参数      已实现

	//Item
	long m_nExportRptMap; //报告映射    已实现
	long m_nExportReports; //报告数据   已实现

	//Item-属性配置
	long m_nExportItemAttrSimplify; //CItems、CSafety、CMacroTest、CCommCmd、CSysParaEdit属性简化，仅保留name、id    已实现

	//sysparaedit
	long m_nExportSysParaEditValues; //系统参数编辑项目的参数   已实现

	//safety
	long m_nExportSafetyDatas; //数据定义    已实现
	long m_nExportSafetyDllCall;   //动态库调用   已实现
	long m_nExportSafetyMsg; //提示信息   已实现

	//commoncmd
	long m_nExportCmdPara;  //命令参数            已实现
	long m_nExportCmdDatas; //命令定义的数据      已实现
	long m_nExportCmdDsvScript; //模型验证脚本    已实现

	//macrotest
	long m_nExportMacroTestParas;  //电气量功能参数   已实现

	//report
	long m_nExportRptmapNotSaveNull;   //当报告映射为空时，不保存报告映射对象   已实现
	long m_nExportRptOnlySaveBkmk;   //CReport的m_pValues中只保存有书签的数据
	long m_nExportRptOnlySaveLast;   //只保存最后一次的报告数据   已实现
	
	//script
	long m_nExportScriptExprScript;  //结果判断表达式   已实现
	long m_nExportScriptName;     //script-name   已实现
	long m_nExportScriptInit;     //初始化脚本    已实现
	long m_nExportScriptRslt;     //结果脚本      已实现

	CString m_strFile;

public:
	static CGuideBookExportConfig* g_pGuideBookExportConfig;
	static long g_nGuideBookExportConfigRef;

	static CGuideBookExportConfig* Create();
	static void Release();

public:


public:
	long Save();
	long Open();

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strGuideBookExportConfigKey;	}

};
