#pragma once
#include "GuideBook.h"
#include "../GuideBookExportConfig.h"

class CGuideBookExportTool : public CExBaseList
{
public:
	CGuideBookExportTool(void);
	virtual ~CGuideBookExportTool(void);

// 	//guidebook
// 	long m_nExportGlobalDatas; //全局数据
// 	long m_nExportJobGuide; //作业指导
// 	long m_nExportExtendRptDef;  //扩展报告
// 
// 	//device
// 	long m_nExportDeviceModule; //设备模型
// 	long m_nExportSysParas;  //系统参数
// 
// 	//Item
// 	long m_nExportRptMap; //报告映射
// 	long m_nExportReports; //报告数据
// 
// 	//sysparaedit
// 	long m_nExportSysParaEditValues; //系统参数编辑项目的参数
// 
// 	//safety
// 	long m_nExportSafetyDatas; //数据定义
// 	long m_nExportSafetyDllCall;   //动态库调用
// 	long m_nExportSafetyMsg; //提示信息
// 
// 	//commoncmd
// 	long m_nExportCmdPara;  //命令参数
// 	long m_nExportCmdDatas; //命令定义的数据
// 	long m_nExportCmdDsvScript; //模型验证脚本
// 
// 	//macrotest
// 	long m_nExportMacroTestParas;  //电气量功能参数

public:
	void ExportGuideBook(CGuideBook *pGuideBook, const CString &strXmlFile);
	void ExportGuideBook(CGuideBook *pGuideBook, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportTest(CGuideBook *pGuideBook);

	//shaolei 20210724 
	void ExportItems(CItems *pItems, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);

protected:
	BOOL ExportItemChild(CExBaseObject *p, UINT nClassID, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	BOOL ExportItemsChild(CExBaseObject *p, UINT nClassID, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CDevice *pDevice, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CJobGuide *pJobGuide, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CItems *pItems, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CSysParaEdit *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CSafety *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CMacroTest *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CCommCmd *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void Export(CMacroCharItems *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);

// 	void Export(CReportMap *pRptMap, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
// 	void Export(CReports *pReorts, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);

};
