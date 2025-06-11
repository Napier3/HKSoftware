#pragma once

#include "../../../Module/DataMngr/DataMaps.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/DataMngr/DvmValues.h"
#include "../../../Module/DataMngr/DvmDatasetGroup.h"
#include "../../SttCmd/GuideBook/SttGuideBook.h"
//#include "../Webkit/SttReportViewHtml.h"
#include "../../SttTest/Common/tmt_result_def.h"

#define MACRO_EDIT_VIEW_TYPE_BASE   0
#define MACRO_EDIT_VIEW_TYPE_HTML   1
#define MACRO_EDIT_VIEW_TYPE_ORIGINAL   2

class CSttMacroParaEditInterface
{
public:
	CSttMacroParaEditInterface()
	{
		m_pMacroParaEditWnd = NULL;
		m_pSttItems = NULL;
		m_oDvmDataMaps.DeleteAll();		//20240715 huangliang
	};

    virtual ~CSttMacroParaEditInterface(void);

  //2024-7-12 lijunqing
      virtual void InitUI(const CString &strGridFile);

 	//APP ==>> HTML
	virtual void SysConfig(CDataGroup *pSysConfig){}/* = 0*/;
	virtual void SysConfig(CDvmDataset *pSysConfig){}/* = 0*/;
	virtual void SysConfig(const CString &strSysConfig ){}/* = 0*/;
	virtual void SetDatas(CDvmDataset *pDataset){}/* = 0*/;
	virtual void SetDatas(CDataGroup *pParas){}/* = 0*/;
	virtual void SetDatas(const CString &strDataset){}/* = 0*/;
	virtual void GetDatas(CDvmDataset *pParas){}/* = 0*/;
	virtual void GetDatas(CDataGroup *pParas){}/* = 0*/;
	virtual void GetDatas(CString& strParas){}/* = 0*/;

	virtual void UpdateEventMsg(CEventResult *pCurrEventResult){}//测试功能更新参数
	virtual void ShowReport(CDvmValues *pValues){};
	virtual void UpdateTestResource(BOOL bCreateChMaps){}// 20220317 zhouhj
//	virtual void UpdateRtSyncTime(CDataGroup *pRtSycTime){}//20220920 zhouhj 更新对时、守时同步时间
	virtual void Debug(){};
	virtual BOOL IsHtmlView()	{	return FALSE;	}
	virtual long GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml)	{	return 0;	}
	virtual UINT GetMacroEditViewType()	{	return MACRO_EDIT_VIEW_TYPE_BASE;	}
	virtual CString GetMacroTestResultUnit(){ return _T(""); }//dingxy 20241127 获取测试模块的结果单位
	virtual void UpdateDCParasByCurrModulePower(BOOL bCurrModulePowerHigh){}//根据电流档位设置更新直流状态

	//2023-2-4  lijunqing 提高程序界面初始化打开的速度，将矢量图、状态图等的初始化放到线程
	virtual void InitSpyToolWidget()	{};

	//20230210 zhangyq  
    virtual void ProcessGbAfterGenTemplate(CSttGuideBook *pSttGuideBook);  //测试模板
    //virtual void ProcessRptAfterGenTemplate(QSttReportViewHtml *pSttReportViewHtml);  //报告模板
    virtual CString ProcessItemID(const CString & strItemID,long nLoopIndex);  //根据当前测试的重复次数编号，动态生成ID
    virtual BOOL IsInternationalMode();

    virtual CExBaseList* GetCurrentMacroDatas(){ return NULL;}/* = 0*/;  //20240716 wanmj 单功能多点的测试功能获取当前测试项的数据
	virtual void RecordDvmDataMap(CDataMaps *pDvmDataMaps);//20240619 huangliang 记录Map关系

	virtual QWidget* GetWaveWidget(){ return NULL; }//2024-8-5 wuxinyi 获取模块中的波形图窗口指针
	virtual QWidget* GetSystemDiagramWidget(){ return NULL; }//获取模块中的系统图窗口指针
	virtual QWidget* GetWiringDiagramWidget(){ return NULL; }//获取模块中的接线图窗口指针

	virtual void UpdatePrimParaSetUI(){}//20240918 suyang 更新界面一次值/二次值显示
	virtual BOOL IsUseSecondParaSet(){ return TRUE; }//20240918 suyang 是否显示二次值

public:
	void* m_pMacroParaEditWnd;
	CExBaseObject *m_pSttItems;  //指向对应的rootnode的CSttItems对象。方便删除项目是查找视图，并关闭模板视图。

	CDataMaps m_oDvmDataMaps;	//20240619 huangliang 用于不同界面记录Map对象，原地址数据被改做他用
};

class CSttMacroParaEditMsgRcvInterface
{
public:
	CSttMacroParaEditMsgRcvInterface(){};
	virtual ~CSttMacroParaEditMsgRcvInterface(void){};

	//HTML ==>> APP
	virtual void UpdateDatas(CDvmDataset *pParas){}/* = 0*/;
	virtual void OnItemsChanged(CDvmDataset *pParas){}/* = 0*/;
	virtual void UI_ExecCmd(const CString &strCmd, CDvmDataset *pParas){}/* = 0*/;
	virtual void UI_OK_Click(const CString &strHtmlFileName, CDvmDataset *pParas){}/* = 0*/;
	virtual void UI_Cancel_Click(const CString &strHtmlFileName){}/* = 0*/;

};

/*//模板结构
单功能：
	HdConfig     IEC61850Config   SystemConfig    MacroTest(MacroID)

单Web功能
	HdConfig     IEC61850Config   SystemConfig    MacroUI.id(Items)
*/
