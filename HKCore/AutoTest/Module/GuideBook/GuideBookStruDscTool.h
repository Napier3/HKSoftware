#pragma once
#include "GuideBook.h"

 //导出初报告：0 = 不导出报告； 1 = 导出初始化报告（ID = STT_REPORT_ID_INIT）；2 = 导出全部报告
#define EXPROT_RPT_NONE   0
#define EXPROT_RPT_INIT   1
#define EXPROT_RPT_ALL    2

class CGuideBookStruDscTool : public CExBaseList
{
public:
	CGuideBookStruDscTool(void);
	virtual ~CGuideBookStruDscTool(void);

	BOOL m_bExportDsvScript;
	BOOL m_bExportMacroUIParas;  //导出电气量的界面参数节点
	BOOL m_bExportRsltExpr; //导出结果判断
	long m_nExportRpt;
	BOOL m_bExportGlobalDatas;  //导出全局数据
	BOOL m_bExportSysParas;   //导出系统参数
	BOOL m_bExportCharacteristic;   //导出特性曲线
	BOOL m_bExportCmd;   //导出通讯命令的参数CCmd
	BOOL m_bExportItemDatas; //是否导出项目的数据定义
	BOOL m_bExportItemsTecs;  //导出项目技术要求+报告数据保留小数位数配置
	CGuideBook *m_pGuideBook;

public:
	//2021-8-5  lijunqing
	void ExportGuideBookStruDscToString(CGuideBook *pGuideBook, CString &strXml);
	void ExportGuideBookStruDscToString_UTF8(CGuideBook *pGuideBook, char **ppszBuffer, long &nLen);

	void ExportGuideBookStruDsc(CGuideBook *pGuideBook, const CString &strXmlFile);
	void ExportGuideBookStruDsc(CGuideBook *pGuideBook, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CItems *pItems, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);

protected:
	void ExportStruDscItemsChild(CExBaseList *pList, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	BOOL ExportStruDscItemsChild(CExBaseObject *p, UINT nClassID, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CDevice *pDevice, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CTestGlobalDatasMngr *pDataMngr, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CJobGuide *pJobGuide, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CDvmDataset*pDataset, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CDataGroup *pGrp, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CSysParas *pSysParas, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	//void ExportStruDsc(CItems *pItems, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);  //2023-9-9  lijunqing 改为public
	void ExportStruDsc(CSysParaEdit *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CSafety *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CMacroTest *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CCommCmd *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CMacroCharItems *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CTestMacroUiParas *pUIParas, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CTestMacroCharParas *pCharParas, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CMacroTestPara *pMacroTestPara, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CItemRsltExprRun *pRsltExprRun, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CReports *pReports, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CCharacteristic *pCharacteristic, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ExportStruDsc(CShortDatas *pDatas, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent);
	void ProcessReportsBack_BF_Export(CGbItemBase *pGbItemBase);
};
