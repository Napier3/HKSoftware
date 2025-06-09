#pragma once

#include "SttHtmlViewApi.h"
#include "../../../../Module/DataMngr/DvmValues.h"

#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
#include "../../SttCmd/GuideBook/SttGuideBook.h"
#endif

#ifdef STT_MACRO_TEST_UI_USE_GUIDEBOOK
#include "../../../../AutoTest/Module/GuideBook/Reports.h"
#endif

#define SttHtmlRptCmd_Insert    "insert"
#define SttHtmlRptCmd_Update  "update"
#define SttHtmlRptCmd_FillTitle  "fill_title"

#define STT_REPORTHEAD_NomSettings            "NomSettings"    //额定值
#define STT_REPORTHEAD_TestAppInfor           "TestAppInfor"    //测试设备信息

#define STT_REPORTHEAD_Vnom                     "Vnom"    //额定电压
#define STT_REPORTHEAD_Inom                     "Inom"    //额定电流
#define STT_REPORTHEAD_Fnom                     "Fnom"    //额定频率
#define STT_REPORTHEAD_SureTime                 "SureTime"    //开入防抖时间

#define STT_REPORTHEAD_AppModel                 "AppModel"    //型号
#define STT_REPORTHEAD_AppSN                    "AppSN"    //序列号
#define STT_REPORTHEAD_Imax                    "Imax"    //电流最大值
#define STT_REPORTHEAD_Vmax                    "Vmax"    //电压最大值
#define STT_REPORTHEAD_TestStartTime            "TestStartTime"//测试开始时间
#define STT_REPORTHEAD_TestEndTime              "TestEndTime"//测试终止时间

//2022-10-3  lijunqing
#define ID_STT_RPT_FILL_MODE_RPT_DATA_PATH   "rpt-data-path"
#define ID_STT_RPT_FILL_MODE_RPT_MAP_DATAS   "rpt-map-datas"
#define ID_STT_RPT_FILL_MODE_RPT_SYSTEM        "rpt-system"
#define STT_RPT_FILL_MODE_RPT_SYSTEM        0
#define STT_RPT_FILL_MODE_RPT_MAP_DATAS   1
#define STT_RPT_FILL_MODE_RPT_DATA_PATH   2


class CSttHtmlRptCmd
{
public:
	CSttHtmlRptCmd();
	virtual ~CSttHtmlRptCmd();

public:
	CString m_strHtmlRptCmd;
	CString m_strParentPath;
	CString m_strItemsID;
	CSttMacroTestUI_TestMacroUI *m_pTestMacroUI;
	char *m_strGbDatas;
	BOOL m_bIsFinish;

	//2023-2-16 lijunqing/zhangyanqi 因报告视图循环时用同一个Data，Insert和Update不对应，把下面Interface里的移动到Cmd
	CString m_strCurrRptFileData;  //当前使用的Html报告数据文件
};

class CSttHtmlReportVIewInterface : public CTLinkListEx<CSttHtmlRptCmd> 
{
public:
	CSttHtmlReportVIewInterface();
	virtual ~CSttHtmlReportVIewInterface(void);

	CSttHtmlRptCmd* AddInsertHeadCmd(const CString &strParentItemsPath, const CString &strItemsID,  BOOL bExec=TRUE);
	CSttHtmlRptCmd* AddInsertCmd(CSttMacroTestUI_TestMacroUI *pTestMacroUI, const CString &strParentItemsPath, const CString &strItemsID, const char *strGbDatas, BOOL bExec=TRUE);
	CSttHtmlRptCmd* AddUpdateCmd(CSttMacroTestUI_TestMacroUI *pTestMacroUI, const CString &strParentItemsPath, const CString &strItemsID, const char *strGbDatas, BOOL bExec=TRUE);
	CSttHtmlRptCmd* AddFillRptTitleCmd(const CString &strItemsID, const char *strGbDatas, BOOL bExec=TRUE);

	virtual void ExcuteNextCmd();

	//2022-10-3  lijunqing报告填写模式
	void SetRptFillModeByID(const CString &strRptFillModeID);
	BOOL IsRptFillMode_SYSTEM()	{	return m_nRptFillMode == STT_RPT_FILL_MODE_RPT_SYSTEM;	}
	BOOL IsRptFillMode_MAP_DATAS()	{	return m_nRptFillMode == STT_RPT_FILL_MODE_RPT_MAP_DATAS;	}
	BOOL IsRptFillMode_DATA_PATH()	{	return m_nRptFillMode == STT_RPT_FILL_MODE_RPT_DATA_PATH;	}

protected:
	CSttMacroTestUI_TestMacroUI *m_pTestMacroUI;
	CDataGroup *m_pTestMacroUI_Paras;  //当前测试功能页面的参数
	CString m_strCurrHtmlRptFileData;   //当前使用的HTML报告数据文件

	POS m_posCurrHtmlRptCmd;
	CSttHtmlRptCmd *m_pCurrHtmlRptCmd;
	BOOL m_bCanExecCmd;
	
	//2022-10-3  lijunqing报告填写模式
	long m_nRptFillMode;

	void ExecCmd();
	void ExecCmd(CSttHtmlRptCmd *pSttHtmlRptCmd);

public:
	//20230217 zhangyq 增加strRptFileData，避免函数调用全局变量m_strCurrRptFileData
	virtual void InsertRptHtml(const CString &strParentItemsPath, const CString &strItemsID, const char *strGbDatas, const CString &strRptFileData) = 0;
	virtual void UpdateRptHtml(const CString &strParentItemsPath, const CString &strItemsID, const CString &strGbDatas, const CString &strRptFileData) = 0;
	virtual void UpdateRptHtml(const CString &strParentItemsPath, const CString &strItemsID, const char *strGbDatas, const CString &strRptFileData) = 0;

	virtual void DeleteRptHtml(const CString &strParentItemsPath, const CString &strItemsID) = 0;
	virtual void ItemStateChanged(const CString &strParentItemsPath, const CString &strItemID, const CString &strState) = 0;
	virtual void FillReportData(const CString &strParentItemsPath, const CString &strItemID, const CString &strState, char *pszReport) = 0;
	virtual void FillReportImg(const CString &strParentItemsPath, const CString &strItemID, const CString &strImgBase64) = 0;
	virtual void OpenReportFile(const CString &strReportFile) = 0;
	virtual void FillReportDataset(const CString &strParentItemsPath, const CString &strItemID, const char *pszDataset) = 0;
	virtual void FillRptMapDatas(const char *pszRptMapDatas, const CString &strState) = 0;
	virtual void QueryReportFillMode() = 0;
	virtual void FillReportTitle(const CString &strItemsID,const char *pszGroupData) = 0;

public:
 	virtual void InitReport(const CString &strReportFile);
	//20230217 zhangyq
	virtual void AddMacroTestReport(const CString &strParentPath, const CString &strItemsID, CSttMacroTestUI_TestMacroUI *pTestMacroUI, const char *strGbDatas, const CString &strRptFileData);
	virtual void DeleteMacroTestReport(const CString &strParentPath, const CString &strItemsID);
	virtual void UpdateMacroTestReport(const CString &strParentPath, const CString &strItemsID, const CString &strGbDatas, const CString &strRptFileData);
	
	virtual void FillReport(const CString &strParentPath, const CString &strItemID, CDvmValues *pValues);
	virtual void FillReport(const CString &strParentPath, const CString &strItemID, CDvmDataset *pDataset);
	
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
	virtual void FillReport(const CString &strParentPath, const CString &strItemID, CSttReports *pSttReports);
#endif

#ifdef STT_MACRO_TEST_UI_USE_GUIDEBOOK
	virtual void FillReport(const CString &strParentPath, const CString &strItemID, CReports *pReports);
#endif

public:
	void SetRptFileData(char* pstrRptFileData){ m_strCurrHtmlRptFileData = pstrRptFileData;};
};

//report headhtml file
#define STT_REPORT_HEAD_HTML_FILE   "ReportHead.html"
