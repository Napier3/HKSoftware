//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacroRptTemplateGlobal.h

//PowerTest7.0版本的单机及自动测试软件，生成XML格式的报告及导出word。
//对配置的XML格式的报告的配置。对应的TestMacroRptTemplate.xsd

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"
#include "../../../Module/DataMngr/DataMngrGlobal.h"

#define RptTemplateMngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00060000)
#define RptTemplateMngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00060000)

#define MNGRCLASSID_CRPTTEMP_GUIDEBOOK       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CRPTTEMP_ITEMS       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000001)
#define MNGRCLASSID_CRPTTEMP_MACROCHARITEMS       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000002)
#define MNGRCLASSID_CRPTTEMP_MACROTEST       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000003)
#define MNGRCLASSID_CRPTTEMP_REPORTTEMPLATEDEF       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000004)
#define MNGRCLASSID_CRPTTEMP_TESTMACROUIRPTDEF       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000005)
#define MNGRCLASSID_CRPTTEMP_REPORTDEF       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000006)
#define MNGRCLASSID_CRPTTEMP_VALUEDEF       (RptTemplateMngrCLASSID_BASECLASS + 0X00000007)
#define MNGRCLASSID_CRPTTEMP_REPORTSDEF       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000008)
#define MNGRCLASSID_CRPTTEMP_TITLEDEF       (RptTemplateMngrCLASSID_BASECLASS + 0X00000009)
#define MNGRCLASSID_CRPTTEMP_TEXTDEF       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X0000000A)
#define MNGRCLASSID_CRPTTEMP_GRIDDEF       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X0000000B)
#define MNGRCLASSID_CRPTTEMP_COLSDEF       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X0000000C)
#define MNGRCLASSID_CRPTTEMP_COLDEF       (RptTemplateMngrCLASSID_BASECLASS + 0X0000000D)
#define MNGRCLASSID_CRPTTEMP_ROWSDEF       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X0000000E)
#define MNGRCLASSID_CRPTTEMP_ROWDEF       (RptTemplateMngrCLASSID_BASECLASS + 0X0000000F)
#define MNGRCLASSID_CRPTTEMP_HEAD       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000010)
#define MNGRCLASSID_CRPTTEMP_CELL       (RptTemplateMngrCLASSID_BASECLASS + 0X00000011)
#define MNGRCLASSID_CRPTTEMP_ROW       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000012)
#define MNGRCLASSID_CRPTTEMP_COL       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000013)

#define MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000014)
#define MNGRCLASSID_CRPTTEMP_TESTMACROUIRPT       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000015)
#define MNGRCLASSID_CRPTTEMP_REPORT       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000016)
#define MNGRCLASSID_CRPTTEMP_VALUE       (RptTemplateMngrCLASSID_BASECLASS + 0X00000017)
#define MNGRCLASSID_CRPTTEMP_REPORTS       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000018)
#define MNGRCLASSID_CRPTTEMP_TITLE       (RptTemplateMngrCLASSID_BASECLASS + 0X00000019)
#define MNGRCLASSID_CRPTTEMP_TEXT       (RptTemplateMngrCLASSID_BASECLASS + 0X0000002A)
#define MNGRCLASSID_CRPTTEMP_GRID       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X0000002B)
#define MNGRCLASSID_CRPTTEMP_ENABLE       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X0000002C)
#define MNGRCLASSID_CRPTTEMP_PARAOPTR       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X0000002D)

#define MNGRCLASSID_CRPTTEMP_PNG       (RptTemplateMngrCLASSID_BASECLASS + 0X0000002E)
#define MNGRCLASSID_CRPTTEMP_PNGDEF       (RptTemplateMngrCLASSID_BASECLASS + 0X0000002F)
#define MNGRCLASSID_CRPTTEMP_GROUP       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000030)
#define MNGRCLASSID_CRPTTEMP_DATA       (RptTemplateMngrCLASSID_EXLISTCLASS + 0X00000031)

class CTestMacroRptTemplateXmlRWKeys : public CDataMngrXmlRWKeys
{
protected:
	CTestMacroRptTemplateXmlRWKeys();
	virtual ~CTestMacroRptTemplateXmlRWKeys();
	static long g_nMngrRef;

public:
	static CTestMacroRptTemplateXmlRWKeys* g_pXmlKeys;
	static CTestMacroRptTemplateXmlRWKeys* Create();
	static void Release();

public:
	//以下key，用于各个测试模块的XML报告数据文件的模板的element元素定义。
	BSTR m_strCRptTemp_RowDefKey; //row-def
	BSTR m_strCRptTemp_RowsDefKey; //rows-def
	BSTR m_strCRptTemp_ColDefKey; //col-def
	BSTR m_strCRptTemp_ColsDefKey; //cols-def
	BSTR m_strCRptTemp_GridDefKey; //grid-def
	BSTR m_strCRptTemp_TextDefKey; //text-def
	BSTR m_strCRptTemp_TitleDefKey; //title-def
	BSTR m_strCRptTemp_ReportsDefKey; //reports-def
	BSTR m_strCRptTemp_ValueDefKey; //value-def
	BSTR m_strCRptTemp_ReportDefKey; //report-def
	BSTR m_strCRptTemp_PngDefKey; //png-def
	BSTR m_strCRptTemp_TestMacroUiRptDefKey; //test-macro-ui-rpt-def
	BSTR m_strCRptTemp_ReportTemplateDefKey; //report-template-def
	BSTR m_strCRptTemp_EnableKey; //enable
	BSTR m_strCRptTemp_ParaOptrKey; //para-optr

	//以下key，通用于XML报告数据模板和实例化XML报告的属性定义
	BSTR m_strRpt_TitleKey; //rpt-title
	BSTR m_strTitle_LevelKey; //title-level
	BSTR m_strMacro_IdKey; //macro-id
	BSTR m_strRpt_ModeKey; //rpt-mode
	BSTR m_strIndexKey; //index
	BSTR m_strValKey; //val
	BSTR m_strLevelKey; //level
	BSTR m_strTextKey; //text
	BSTR m_strItem_IdKey; //item-id
	BSTR m_strItem_LevelKey; //item-level
	BSTR m_strItem_Level_2Key; //item-level-2
	BSTR m_strItem_Level_3Key; //item-level-3
	BSTR m_strData_IdKey; //data-id
	BSTR m_strData1_IdKey; //data1-id
	BSTR m_strData2_IdKey; //data2-id
	BSTR m_strData3_IdKey; //data3-id
	BSTR m_strData4_IdKey; //data4-id
	BSTR m_strData5_IdKey; //data5-id
	BSTR m_strData6_IdKey; //data6-id
	BSTR m_strData_ModeKey; //data-mode
	BSTR m_strShow_BordersKey;  //show-borders
	BSTR m_strTypeKey; //type
	BSTR m_strRow_SpanKey; //row-span
	BSTR m_strCol_SpanKey; //col-span
	BSTR m_strData_PathKey; //data-path
	BSTR m_strModeKey;    //mode
	BSTR m_strOptrKey;    //optr
	BSTR m_strFontKey; //font
	BSTR m_strSizeKey;    //size
	BSTR m_strBoldKey;    //bold
	BSTR m_strItemPathKey;   //item-path
	BSTR m_strTextFormatKey;   //text-format

	BSTR m_strPrecisionKey;  //precision
	BSTR m_strProcessKey;   //process
	BSTR m_strPngPathKey;   //png-path

	//以下key，通用于XML报告数据模板和实例化XML报告的element元素定义
	BSTR m_strCRptTemp_MacroTestKey; //macrotest
	BSTR m_strCRptTemp_MacroCharItemsKey; //macro-char-items
	BSTR m_strCRptTemp_ColKey; //col
	BSTR m_strCRptTemp_RowKey; //row
	BSTR m_strCRptTemp_CellKey; //cell
	BSTR m_strCRptTemp_HeadKey; //head

	//以下key，用于实例化的XML报告的element元素
	BSTR m_strCRptTemp_ItemsKey; //items
	BSTR m_strCRptTemp_GuideBookKey; //guidebook
	BSTR m_strCRptTemp_GridKey; //grid
	BSTR m_strCRptTemp_TextKey; //text
	BSTR m_strCRptTemp_TitleKey; //title
	BSTR m_strCRptTemp_ReportsKey; //reports
	BSTR m_strCRptTemp_ValueKey; //value
	BSTR m_strCRptTemp_ReportKey; //report
	BSTR m_strCRptTemp_TestMacroUiRptKey; //test-macro-ui-rpt
	BSTR m_strCRptTemp_ReportTemplateKey; //report-template
	BSTR m_strCRptTemp_PngKey; //png

public:
	static BSTR CRptTemp_ColKey()  {   return g_pXmlKeys->m_strCRptTemp_ColKey;  }
	static BSTR CRptTemp_RowKey()  {   return g_pXmlKeys->m_strCRptTemp_RowKey;  }
	static BSTR CRptTemp_CellKey()  {   return g_pXmlKeys->m_strCRptTemp_CellKey;  }
	static BSTR CRptTemp_HeadKey()  {   return g_pXmlKeys->m_strCRptTemp_HeadKey;  }
	static BSTR CRptTemp_RowDefKey()  {   return g_pXmlKeys->m_strCRptTemp_RowDefKey;  }
	static BSTR CRptTemp_RowsDefKey()  {   return g_pXmlKeys->m_strCRptTemp_RowsDefKey;  }
	static BSTR CRptTemp_ColDefKey()  {   return g_pXmlKeys->m_strCRptTemp_ColDefKey;  }
	static BSTR CRptTemp_ColsDefKey()  {   return g_pXmlKeys->m_strCRptTemp_ColsDefKey;  }
	static BSTR CRptTemp_GridDefKey()  {   return g_pXmlKeys->m_strCRptTemp_GridDefKey;  }
	static BSTR CRptTemp_TextDefKey()  {   return g_pXmlKeys->m_strCRptTemp_TextDefKey;  }
	static BSTR CRptTemp_TitleDefKey()  {   return g_pXmlKeys->m_strCRptTemp_TitleDefKey;  }
	static BSTR CRptTemp_ReportsDefKey()  {   return g_pXmlKeys->m_strCRptTemp_ReportsDefKey;  }
	static BSTR CRptTemp_ValueDefKey()  {   return g_pXmlKeys->m_strCRptTemp_ValueDefKey;  }
	static BSTR CRptTemp_ReportDefKey()  {   return g_pXmlKeys->m_strCRptTemp_ReportDefKey;  }
	static BSTR CRptTemp_PngDefKey()  {   return g_pXmlKeys->m_strCRptTemp_PngDefKey;  }
	static BSTR CRptTemp_TestMacroUiRptDefKey()  {   return g_pXmlKeys->m_strCRptTemp_TestMacroUiRptDefKey;  }
	static BSTR CRptTemp_ReportTemplateDefKey()  {   return g_pXmlKeys->m_strCRptTemp_ReportTemplateDefKey;  }
	static BSTR CRptTemp_MacroTestKey()  {   return g_pXmlKeys->m_strCRptTemp_MacroTestKey;  }
	static BSTR CRptTemp_MacroCharItemsKey()  {   return g_pXmlKeys->m_strCRptTemp_MacroCharItemsKey;  }
	static BSTR CRptTemp_ItemsKey()  {   return g_pXmlKeys->m_strCRptTemp_ItemsKey;  }
	static BSTR CRptTemp_GuideBookKey()  {   return g_pXmlKeys->m_strCRptTemp_GuideBookKey;  }
	static BSTR Rpt_TitleKey()  {   return g_pXmlKeys->m_strRpt_TitleKey;  }
	static BSTR Title_LevelKey()  {   return g_pXmlKeys->m_strTitle_LevelKey;  }
	static BSTR Macro_IdKey()  {   return g_pXmlKeys->m_strMacro_IdKey;  }
	static BSTR Rpt_ModeKey()  {   return g_pXmlKeys->m_strRpt_ModeKey;  }
	static BSTR IndexKey()  {   return g_pXmlKeys->m_strIndexKey;  }
	static BSTR ValKey()  {   return g_pXmlKeys->m_strValKey;  }
	static BSTR LevelKey()  {   return g_pXmlKeys->m_strLevelKey;  }
	static BSTR TextKey()  {   return g_pXmlKeys->m_strTextKey;  }
	static BSTR TextFormatKey()  {   return g_pXmlKeys->m_strTextFormatKey;  }
	static BSTR Item_IdKey()  {   return g_pXmlKeys->m_strItem_IdKey;  }
	static BSTR Item_LevelKey()  {   return g_pXmlKeys->m_strItem_LevelKey;  }
	static BSTR Item_Level_2Key()  {   return g_pXmlKeys->m_strItem_Level_2Key;  }
	static BSTR Item_Level_3Key()  {   return g_pXmlKeys->m_strItem_Level_3Key;  }
	static BSTR Data_IdKey()  {   return g_pXmlKeys->m_strData_IdKey;  }
	static BSTR Data1_IdKey()  {   return g_pXmlKeys->m_strData1_IdKey;  }
	static BSTR Data2_IdKey()  {   return g_pXmlKeys->m_strData2_IdKey;  }
	static BSTR Data3_IdKey()  {   return g_pXmlKeys->m_strData3_IdKey;  }
	static BSTR Data4_IdKey()  {   return g_pXmlKeys->m_strData4_IdKey;  }
	static BSTR Data5_IdKey()  {   return g_pXmlKeys->m_strData5_IdKey;  }
	static BSTR Data6_IdKey()  {   return g_pXmlKeys->m_strData6_IdKey;  }
	static BSTR Data_ModeKey()  {   return g_pXmlKeys->m_strData_ModeKey;  }
	static BSTR Show_BordersKey()  {   return g_pXmlKeys->m_strShow_BordersKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR Row_SpanKey()  {   return g_pXmlKeys->m_strRow_SpanKey;  }
	static BSTR Col_SpanKey()  {   return g_pXmlKeys->m_strCol_SpanKey;  }
	static BSTR Data_PathKey()  {   return g_pXmlKeys->m_strData_PathKey;  }

	static BSTR CRptTemp_GridKey()  {   return g_pXmlKeys->m_strCRptTemp_GridKey;  }
	static BSTR CRptTemp_TextKey()  {   return g_pXmlKeys->m_strCRptTemp_TextKey;  }
	static BSTR CRptTemp_TitleKey()  {   return g_pXmlKeys->m_strCRptTemp_TitleKey;  }
	static BSTR CRptTemp_ReportsKey()  {   return g_pXmlKeys->m_strCRptTemp_ReportsKey;  }
	static BSTR CRptTemp_ValueKey()  {   return g_pXmlKeys->m_strCRptTemp_ValueKey;  }
	static BSTR CRptTemp_ReportKey()  {   return g_pXmlKeys->m_strCRptTemp_ReportKey;  }
	static BSTR CRptTemp_TestMacroUiRptKey()  {   return g_pXmlKeys->m_strCRptTemp_TestMacroUiRptKey;  }
	static BSTR CRptTemp_ReportTemplateKey()  {   return g_pXmlKeys->m_strCRptTemp_ReportTemplateKey;  }
	static BSTR CRptTemp_EnableKey()  {   return g_pXmlKeys->m_strCRptTemp_EnableKey;  }
	static BSTR CRptTemp_ParaOptrKey()  {   return g_pXmlKeys->m_strCRptTemp_ParaOptrKey;  }
	static BSTR CRptTemp_PngKey()  {   return g_pXmlKeys->m_strCRptTemp_PngKey;  }
	static BSTR CRptTemp_FontKey()  {   return g_pXmlKeys->m_strFontKey;  }
	static BSTR CRptTemp_SizeKey()  {   return g_pXmlKeys->m_strSizeKey;  }
	static BSTR CRptTemp_BoldKey()  {   return g_pXmlKeys->m_strBoldKey;  }
	static BSTR CRptTemp_ItemPathKey()  {   return g_pXmlKeys->m_strItemPathKey;  }
};



class CTestMacroRptTemplateConstGlobal
{
private:
	CTestMacroRptTemplateConstGlobal();
	virtual ~CTestMacroRptTemplateConstGlobal();

public:
	static CTestMacroRptTemplateConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CTestMacroRptTemplateConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

//报告导出模式：
//1、item：表示一个电气量项目，单独生成一个word表格。用于动作时间、动作值测试
//2、items：表示最小的叶子CItems节点，下面所有的电气量项目，生成一个统一的表格
#define RPT_TEMPLATE_RPT_MODE_ITEM     _T("item")
#define RPT_TEMPLATE_RPT_MODE_ITEMS    _T("items")

//表格填写模式：
/*1、row-item：行为测试项目。针对单点测试，一行对应一个测试项目（电气量，macrotest）。
  2、col-item：列为测试项目。（暂不实现）
  3、row-rpt：行为测试报告。针对重复测试，一行对应一个report-def
  4、col-rpt：列为测试报告。（暂不实现）
*/
#define RPT_TEMPLATE_DATAMODE_ROW_ITEM    _T("row-item")
#define RPT_TEMPLATE_DATAMODE_COL_ITEM    _T("col-item")
#define RPT_TEMPLATE_DATAMODE_ROW_RPT     _T("row-rpt")
#define RPT_TEMPLATE_DATAMODE_COL_RPT     _T("col-rpt")
#define RPT_TEMPLATE_DATAMODE_NOT_DEF     _T("not-def")   //未定义，非法

//表格列定义，列数据来源的类型
//该type定义，与cell的type定义共用；
/*
1、data-id：该列的数据来源为报告数据
2、test-index：该列的数据来源为测次 or 编号
3、text：该列填写为固定的文本。文本直接取自cell的text属性
*/
#define RPT_TEMPLATE_COL_DEF_TYPE_DATA_ID      _T("data-id")   
#define RPT_TEMPLATE_COL_DEF_TYPE_TEST_INDEX   _T("test-index")
#define RPT_TEMPLATE_COL_DEF_TYPE_TEXT   _T("text")

//对于特性图，需要往报告中插入图片的，value-def的id属性固化为Png
#define RPT_TEMPLATE_VALUE_ID_PNG   _T("Png")

#define STT_ITEMS_ID_BEFORETEST   _T("_BeforeTest_")	
#define STT_ITEMS_ID_AFTERTEST   _T("_AfterTest_")

//XML文件的后缀
/*
1、XML的报告数据文件：datxml
2、XML的word结构文件：docxml
*/
#define XML_FILE_POSTFIX_DATXML   _T("datxml")
#define XML_FILE_POSTFIX_DOCXML   _T("docxml")

//使能模式：与、或、非
#define RPT_TEMPLATE_ENABLE_MODE_AND  _T("and")
#define RPT_TEMPLATE_ENABLE_MODE_OR   _T("or")

//使能逻辑：等于、不等于
#define RPT_TEMPLATE_ENABLE_OPTR_EQL  _T("eql")
#define RPT_TEMPLATE_ENABLE_OPTR_UNEQL  _T("uneql")