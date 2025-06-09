//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TestMacroRptTemplateGlobal.h

//PowerTest7.0�汾�ĵ������Զ��������������XML��ʽ�ı��漰����word��
//�����õ�XML��ʽ�ı�������á���Ӧ��TestMacroRptTemplate.xsd

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

#define MNGRCLASSID_CRPTTEMP_NEWPAGE       (RptTemplateMngrCLASSID_BASECLASS + 0X00000032)  //ftt 2024.12.9

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
	//����key�����ڸ�������ģ���XML���������ļ���ģ���elementԪ�ض��塣
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

	//����key��ͨ����XML��������ģ���ʵ����XML��������Զ���
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
	BSTR m_strHAlignTypeKey; //halign-type  //ftt 2024.12.10
	BSTR m_strVAlignTypeKey; //valign-type  //ftt 2024.12.24
	BSTR m_strHeadHeightKey;  //head-height  //ftt 2024.12.23
	BSTR m_strColWidthKey;  //col-width  //ftt 2024.12.23
	BSTR m_strRowHeightKey;  //row-height  //ftt 2024.12.23

	BSTR m_strPrecisionKey;  //precision
	BSTR m_strProcessKey;   //process
	BSTR m_strPngPathKey;   //png-path
	BSTR m_strPngCharKey;   //png-char
	BSTR m_strXLangKey;   //xlang

	//����key��ͨ����XML��������ģ���ʵ����XML�����elementԪ�ض���
	BSTR m_strCRptTemp_MacroTestKey; //macrotest
	BSTR m_strCRptTemp_MacroCharItemsKey; //macro-char-items
	BSTR m_strCRptTemp_ColKey; //col
	BSTR m_strCRptTemp_RowKey; //row
	BSTR m_strCRptTemp_CellKey; //cell
	BSTR m_strCRptTemp_HeadKey; //head

	//����key������ʵ������XML�����elementԪ��
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
	BSTR m_strCRptTemp_NewPageKey; //newpage  //ftt 2024.12.9

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
	static BSTR CRptTemp_NewPageKey()  {   return g_pXmlKeys->m_strCRptTemp_NewPageKey;  }   //ftt 2024.12.9
	static BSTR CRptTemp_HAlignTypeKey()  {   return g_pXmlKeys->m_strHAlignTypeKey;  }  //ftt 2024.12.10
	static BSTR CRptTemp_VAlignTypeKey()  {   return g_pXmlKeys->m_strVAlignTypeKey;  }  //ftt 2024.12.24
	static BSTR CRptTemp_HeadHeightKey()  {   return g_pXmlKeys->m_strHeadHeightKey;  }
	static BSTR CRptTemp_ColWidthKey()  {   return g_pXmlKeys->m_strColWidthKey;  }  //ftt 2024.12.23
	static BSTR CRptTemp_RowHeightKey()  {   return g_pXmlKeys->m_strRowHeightKey;  }  //ftt 2024.12.23
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
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};

//���浼��ģʽ��
//1��item����ʾһ����������Ŀ����������һ��word������ڶ���ʱ�䡢����ֵ����
//2��items����ʾ��С��Ҷ��CItems�ڵ㣬�������еĵ�������Ŀ������һ��ͳһ�ı��
#define RPT_TEMPLATE_RPT_MODE_ITEM     _T("item")
#define RPT_TEMPLATE_RPT_MODE_ITEMS    _T("items")

//�����дģʽ��
/*1��row-item����Ϊ������Ŀ����Ե�����ԣ�һ�ж�Ӧһ��������Ŀ����������macrotest����
  2��col-item����Ϊ������Ŀ�����ݲ�ʵ�֣�
  3��row-rpt����Ϊ���Ա��档����ظ����ԣ�һ�ж�Ӧһ��report-def
  4��col-rpt����Ϊ���Ա��档���ݲ�ʵ�֣�
*/
#define RPT_TEMPLATE_DATAMODE_ROW_ITEM    _T("row-item")
#define RPT_TEMPLATE_DATAMODE_COL_ITEM    _T("col-item")
#define RPT_TEMPLATE_DATAMODE_ROW_RPT     _T("row-rpt")
#define RPT_TEMPLATE_DATAMODE_COL_RPT     _T("col-rpt")
#define RPT_TEMPLATE_DATAMODE_NOT_DEF     _T("not-def")   //δ���壬�Ƿ�

//����ж��壬��������Դ������
//��type���壬��cell��type���干�ã�
/*
1��data-id�����е�������ԴΪ��������
2��test-index�����е�������ԴΪ��� or ���
3��text��������дΪ�̶����ı����ı�ֱ��ȡ��cell��text����
*/
#define RPT_TEMPLATE_COL_DEF_TYPE_DATA_ID      _T("data-id")   
#define RPT_TEMPLATE_COL_DEF_TYPE_TEST_INDEX   _T("test-index")
#define RPT_TEMPLATE_COL_DEF_TYPE_TEXT   _T("text")

//��������ͼ����Ҫ�������в���ͼƬ�ģ�value-def��id���Թ̻�ΪPng
#define RPT_TEMPLATE_VALUE_ID_PNG   _T("Png")

#define STT_ITEMS_ID_BEFORETEST   _T("_BeforeTest_")	
#define STT_ITEMS_ID_AFTERTEST   _T("_AfterTest_")

//XML�ļ��ĺ�׺
/*
1��XML�ı��������ļ���datxml
2��XML��word�ṹ�ļ���docxml
*/
#define XML_FILE_POSTFIX_DATXML   _T("datxml")
#define XML_FILE_POSTFIX_DOCXML   _T("docxml")

//ʹ��ģʽ���롢�򡢷�
#define RPT_TEMPLATE_ENABLE_MODE_AND  _T("and")
#define RPT_TEMPLATE_ENABLE_MODE_OR   _T("or")

//ʹ���߼������ڡ�������
#define RPT_TEMPLATE_ENABLE_OPTR_EQL  _T("eql")
#define RPT_TEMPLATE_ENABLE_OPTR_UNEQL  _T("uneql")