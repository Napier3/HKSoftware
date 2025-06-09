#pragma once
#include "../GuideBook/GuideBook.h"
#include "RptTemp_GuideBook.h"
#include "RptTemp_TestMacroUiRptDef.h"
#include "RptTemp_TestMacroUiRpt.h"
#include "../GuideBook/ReportMap/ReportTemplateConfig/ReportTemplateConfig.h"
#include "RptTemp_PngDef.h"
#include "../../../Module/DataMngr/DataTypeValue.h"
#include "../../../Module/BaseClass/ExBaseList.h"

//导出XML报告数据文件：datxml
//导出XML的word结构文件：docxml
class CRptTemplate_GenXmlTool : public CExBaseList
{
public:
	CRptTemplate_GenXmlTool(void);
	virtual ~CRptTemplate_GenXmlTool(void);

	CString m_strXmlFile_Dat; //XML报告数据文件
	CRptTemp_GuideBook *m_pRptTemp_GuideBook;   //导出的XML报告数据文件的根节点
	CGuideBook *m_pGuideBook;  //待导出报告的测试模板（含报告数据）
	CDataGroup *m_pReportHeadParas; //报告头信息

	CString m_strXmlFile_Doc; //XMLword结构文件
	CRptTemp_TestMacroUiRpt *m_pRptTemp_TestMacroUiRpt;   //导出的XML格式的word结构文件，用该文件可以生成word报告
	CReportTemplateConfig m_oRptTemplateCfg;

public:
	void InitRptTemplateCfg();
	void InitGbGenSysPath(const CString &strSysPath);
	CString GetDBPath()		{	return m_strDbPath;		}
	CString GetConfigPath()	{	return m_strConfigPath;	}
	CString GetWorkSpacePath()		{	return m_strWorkSpacePath;		}
	void SetReportHeadParas(CDataGroup *pReportHead)	{	m_pReportHeadParas = pReportHead;	}

private:
	CString m_strDbPath;
	CString m_strConfigPath;
	CString m_strWorkSpacePath;
	BOOL m_bCurrentItems_Ain;  //当前导出的CItems，是否是遥测功能；因为导出是单线程，按照模板结构顺序导出，因此可以用标记处理

public:
	//以下是生成XML格式的报告数据文件的
	BOOL GenRpt_Xml_Dat(const CString &strXmlFile, CGuideBook *pGuideBook);
	BOOL GenRpt_Xml_Dat_Device(CRptTemp_GuideBook *pRptTemp_GuideBook, CDevice *pDevice);
	BOOL GenRpt_Xml_Dat_Items(CExBaseList *pParent, CItems *pItems);
	BOOL GenRpt_Xml_Items_Dat_Normal(CExBaseList *pParent, CItems *pItems);
	BOOL GenRpt_Xml_Items_Dat_RootNode(CExBaseList *pParent, CItems *pItems);
	BOOL GenRpt_Xml_Items_Dat_RootNode_Items(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems, CItems *pItems);
	BOOL GenRpt_Xml_Items_Dat_RootNode_UpdateItemsTec(CRptTemp_TestMacroUiRptDef *pRptDef, const CString &strItemPath);  //更新“技术要求” + “报告数据保留小数位数”数据接口
	//处理父项目是CItems的电气量
	BOOL GenRpt_Xml_Items_Dat_RootNode_MacroTest(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems, CMacroTest *pMacroTest);
	//处理父项目是CMacroCharItems的电气量
	BOOL GenRpt_Xml_Items_Dat_RootNode_MacroTest(CRptTemp_MacroCharItems *pMacroCharItemsDef, CRptTemp_MacroCharItems *pNewMacroCharItems, CMacroTest *pMacroTest);
	BOOL GenRpt_Xml_Items_Dat_RootNode_MacroCharItems(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems, CMacroCharItems *pMacroCharItems);
	BOOL GenRpt_Xml_MacroCharItems_Dat_Report_Value(CRptTemp_ReportDef* pRptDef, CRptTemp_Report* pNewRpt, CReport* pReport, const CString &strItemPath);
	//处理电气量项目的报告数据
	BOOL GenRpt_Xml_MacroTest_Dat_Reports(CRptTemp_ReportsDef* pRptDef, CExBaseList *pRptLists, CRptTemp_MacroTest* pRptMacroTestNew, CMacroTest *pMacroTest);
	BOOL GenRpt_Xml_MacroTest_Dat_Report(CRptTemp_ReportDef* pRptDef, CExBaseList *pParent, CExBaseList* pRptLists, CMacroTest *pMacroTest);
	BOOL GenRpt_Xml_MacroTest_Dat_Report_Value(CRptTemp_ReportDef* pRptDef, CRptTemp_Report* pNewRpt, CReport* pReport, CMacroTest *pMacroTest);

	//以下是生成XML格式的doc结构文件的
	BOOL GenRpt_Xml_Doc(const CString &strXmlFile, CGuideBook *pGuideBook);
	void GenRpt_Xml_Doc_ProcessReportHead();  //处理报告头
	void GenRpt_Xml_Doc_ProcessReportHead_Grid(CDataGroup *pGrp, CExBaseList *pParent);  //处理报告头
	BOOL GenRpt_Xml_Doc_Device(CRptTemp_TestMacroUiRpt *pRptTemp_TestMacroUiRpt, CDevice *pDevice);
	BOOL GenRpt_Xml_Doc_Items(CExBaseList *pParent, CItems *pItems);
	BOOL GenRpt_Xml_Items_Doc_Normal(CExBaseList *pParent, CItems *pItems);
	BOOL GenRpt_Xml_Items_Doc_RootNode(CExBaseList *pParent, CItems *pItems);
	BOOL GenRpt_Xml_Items_Doc_RootNode_Items(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems, CItems *pItems);
	BOOL GenRpt_Xml_Items_Doc_RootNode_MacroTest(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems, CMacroTest *pMacroTest);
	BOOL GenRpt_Xml_Items_Doc_RootNode_MacroCharItems(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems,  CMacroCharItems *pMacroCharItems);
	BOOL GenRpt_Xml_Items_Doc_RootNode_UpdateItemsTec(CRptTemp_TestMacroUiRptDef *pRptDef, const CString &strItemPath);  //更新“技术要求” + “报告数据保留小数位数”数据接口

	BOOL GenRpt_Xml_Items_Doc_RootNode_MacroTest_RptMode_Item(CRptTemp_MacroTest *pMacroTestDef, CRptTemp_Items *pRptItems, CMacroTest *pMacroTest);
	BOOL GenRpt_Xml_Items_Doc_RootNode_MacroTest_RptMode_Items(CRptTemp_MacroTest *pMacroTestDef, CRptTemp_Items *pRptItems, CItems *pItems);

	//以下四个，只处理test-macro-ui-rpt-def根节点定义的report-template-def节点，若定义该节点，说明当前模块导出的报告是固化的，不随项目变化而改变
	BOOL GenRpt_Xml_Doc_ReportTemplateDef_Head(CRptTemp_TestMacroUiRptDef *pRptDef, CExBaseList *pParent_RptTemp, CGbItemBase *pItemBase);
	BOOL GenRpt_Xml_Doc_TitleDef_Head(CRptTemp_TitleDef *pTitleDef, CRptTemp_ReportTemplate *pParent, CGbItemBase *pItemBase);
	BOOL GenRpt_Xml_Doc_TextDef_Head(CRptTemp_TextDef *pTextDef, CRptTemp_ReportTemplate *pParent, CGbItemBase *pItemBase);
	BOOL GenRpt_Xml_Doc_TextDef_GetContext(CString &strText, CString &strTextContext, CGbItemBase *pItemBase, CDataGroup *pItemsTec
		, const CString &strData1_Id,  const CString &strData2_Id, const CString &strData3_Id
		, const CString &strData4_Id, const CString &strData5_Id, const CString &strData6_Id);  //获取text对象实例化后的文本。形参2是出参
	BOOL GenRpt_Xml_Doc_GridDef_Head(CRptTemp_GridDef *pGridDef, CRptTemp_ReportTemplate *pParent, CGbItemBase *pItemBase);
	BOOL GenRpt_Xml_Doc_GridDef_Head_FillRow(CRptTemp_Row *pRow, CGbItemBase *pItemBase, CRptTemp_TestMacroUiRptDef *pRptTempUiDef=NULL);
	BOOL GenRpt_Xml_Doc_GridDef_Head_FillCell(CRptTemp_Cell *pCell, CItems *pItems, CRptTemp_TestMacroUiRptDef *pRptTempUiDef=NULL);
	BOOL GenRpt_Xml_Doc_GridDef_Head_FillCell_ProcessVal(const CString& strSrcVal, CString &strVal, const CString &strProcess, long nPrecision); //处理报告数据结果，修约，比例系数等

	//以下四个，只处理macrotest节点定义的report-template-def。且rpt-mode=item
	BOOL GenRpt_Xml_Doc_ReportTemplateDef_MacroTest(CRptTemp_ReportTemplateDef *pReportTemplateDef, CExBaseList *pParent_RptTemp, CMacroTest *pMacroTest);
	BOOL GenRpt_Xml_Doc_TitleDef_MacroTest(CRptTemp_TitleDef *pTitleDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroTest *pMacroTest);
	BOOL GenRpt_Xml_Doc_TextDef_MacroTest(CRptTemp_TextDef *pTextDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroTest *pMacroTest);
	BOOL GenRpt_Xml_Doc_GridDef_MacroTest(CRptTemp_GridDef *pGridDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroTest *pMacroTest);

	//以下五个，只处理macro-char-items节点定义的report-template-def
	BOOL GenRpt_Xml_Doc_ReportTemplateDef_MacroTestCharItems(CRptTemp_ReportTemplateDef *pReportTemplateDef, CExBaseList *pParent_RptTemp, CMacroCharItems *pMacroCharItems);
	BOOL GenRpt_Xml_Doc_TitleDef_MacroCharItems(CRptTemp_TitleDef *pTitleDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroCharItems *pMacroCharItems);
	BOOL GenRpt_Xml_Doc_TextDef_MacroCharItems(CRptTemp_TextDef *pTextDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroCharItems *pMacroCharItems);
	BOOL GenRpt_Xml_Doc_PngDef_MacroCharItems(CRptTemp_PngDef *pPngDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroCharItems *pMacroCharItems);
	BOOL GenRpt_Xml_Doc_GridDef_MacroCharItems(CRptTemp_GridDef *pGridDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroCharItems *pMacroCharItems);

	//以下四个，只处理macro节点定义的report-template-def。且rpt-mode=items
	BOOL GenRpt_Xml_Doc_ReportTemplateDef_Items(CRptTemp_ReportTemplateDef *pReportTemplateDef, CExBaseList *pParent_RptTemp, CItems *pItems, const CString &strMacroID);
	BOOL GenRpt_Xml_Doc_TitleDef_Items(CRptTemp_TitleDef *pTitleDef, CRptTemp_ReportTemplate *pParent_RptTemp, CItems *pItems);
	BOOL GenRpt_Xml_Doc_TextDef_Items(CRptTemp_TextDef *pTextDef, CRptTemp_ReportTemplate *pParent_RptTemp, CItems *pItems);
	BOOL GenRpt_Xml_Doc_GridDef_Items(CRptTemp_GridDef *pGridDef, CRptTemp_ReportTemplate *pParent_RptTemp, CItems *pItems, const CString &strMacroID);

	BOOL GenRpt_Xml_GridDef_RowItem(CRptTemp_Grid *pNewGrid, CRptTemp_GridDef *pGridDef, CGbItemBase *pItemBase, const CString &strMacroID);
	BOOL GenRpt_Xml_GridDef_RowRpt(CRptTemp_Grid *pNewGrid, CRptTemp_GridDef *pGridDef, CMacroTest *pMacroTest);
	BOOL GenRpt_Xml_GridDef_NewRow(CRptTemp_Grid *pNewGrid, CRptTemp_ColsDef *pColsDef, CReport *pReport, long nIndex, CGbItemBase *pItem);
	BOOL GenRpt_Xml_GridDef_FillRow(CRptTemp_Row *pNewRow, CRptTemp_ColsDef *pColsDef, CReport *pReport, long nTestIndex);
	BOOL GenRpt_Xml_GridDef_FillRow_ProcessVal(const CString& strSrcVal, CString &strVal, const CString &strProcess, long nPrecision); //处理报告数据结果，修约，比例系数等

public:
	CRptTemp_Items* GenRpt_Xml_NewItems(CExBaseList *pParent, CItems *pItems);
	CRptTemp_MacroTest* GenRpt_Xml_NewMacroTest(CExBaseList *pParent, CMacroTest *pMacroTest);
	CRptTemp_MacroCharItems* GenRpt_Xml_NewMacroCharItems(CExBaseList *pParent, CMacroCharItems *pMacroCharItems);
	CRptTemp_Report* GenRpt_Xml_NewReport(CExBaseList *pParent, CReport *pReport);
	BOOL GenRpt_Xml_NewValue(CExBaseList *pParent, CRptTemp_ValueDef* pValueDef, const CString &strItemPath);  //仅用于处理特性图
	BOOL GenRpt_Xml_NewValue(CExBaseList *pParent, CRptTemp_ValueDef* pValueDef, CValues *pValues);  //考虑从结果判断脚本中查找结果值。形参可能需要修改
	BOOL GenRpt_Xml_NewValue(CExBaseList *pParent, CRptTemp_ValueDef* pValueDef, CReport *pReport);
	BOOL GenRpt_Xml_NewValue_ProcessVal(const CString& strSrcVal, CString &strVal, const CString &strProcess, long nPrecision); //处理报告数据结果，修约，比例系数等
	void GenRpt_Xml_NewValue_ProcessVal_AdjustVal(CString &strVal);
	BOOL GenRpt_Xml_ProcessRptValue(CString &strRptValue, const CString &strDataID, CReport *pReport);  //处理报告数据：m_pValues，m_pRptDvmDataset
	BOOL GenRpt_Xml_ProcessRptValue_GetValue(CString &strRptValue, const CString &strDataID, CReport *pReport, CGbItemBase *pGbItem, const CString& strProcess, long nPrecision);  //获取报告值，并处理修约
	void GenRpt_Xml_ProcessVal_AinRatios(CDvmData *pAinDataMap, CDataGroup *pAinRatios, CString &strRptValue);  //处理遥测数据，根据采样值变比，进行换算
	void GenRpt_Xml_ProcessVal_AinRatios_I(CDataGroup *pAinRatios, CString &strRptValue);
	void GenRpt_Xml_ProcessVal_AinRatios_U(CDataGroup *pAinRatios, CString &strRptValue);
	void GenRpt_Xml_ProcessVal_AinRatios_PQ(CDataGroup *pAinRatios, CString &strRptValue);
	CRptTemp_ReportTemplate* GenRpt_Xml_NewReportTemplate(CExBaseList *pParent);
	CRptTemp_Title* GenRpt_Xml_NewTitle(CExBaseList *pParent);
	CRptTemp_Text* GenRpt_Xml_NewText(CExBaseList *pParent);
	CRptTemp_Grid* GenRpt_Xml_NewGrid(CExBaseList *pParent, CRptTemp_GridDef *pGridDef);

public:
	CString GetItemName(CGbItemBase *pItemBase, long nItemLevel);
	CString GetItemReportValue(CGbItemBase *pItemBase, const CString &strDataID);
	CString GetItemsTec(CRptTemp_TextDef *pTextDef, const CString &strDataID);
	CString GetItemsTec(CDataGroup *pItemsTec, const CString &strDataID);
	void GetItemReports(CExBaseList *pRptLists, CGbItemBase *pItemBase);
	void GetPngFilePath(const CString &strItemPath, CString &strPngFile);

	void GetMacroTest_AllParas(CExBaseList *pParas, CItems *pRootNode);
	void GetMacroTest_AllParas(CExBaseList *pParas, CMacroTest *pMacroTest);
	void GetMacroCharItems_AllParas(CExBaseList *pParas, CMacroCharItems *pMacroCharItems);
	void GetMacroTest_AllParas_UIParas(CExBaseList *pParas, CDataGroup *pUIParas, CExBaseList *pRoot);

	CBkmkDataProcess* FindDataProcessByID(const CString &strID);
	BOOL IsCurrentItemsAin(const CString &strItemsID);
	CDataTypeValue* GetDataTypeValue(const CString &strIDPath, CGbItemBase *pItemBase, const CString &strValue);
};
