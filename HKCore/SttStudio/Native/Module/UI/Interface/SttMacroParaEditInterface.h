#pragma once

#include "../../Module/DataMngr/DataGroup.h"
#include "../../Module/DataMngr/DvmValues.h"
#include "../../Module/DataMngr/DvmDatasetGroup.h"
#include "../../SttCmd/GuideBook/SttGuideBook.h"
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
	};

	virtual ~CSttMacroParaEditInterface(void){};

 	//APP ==>> HTML
	virtual void SysConfig(CDataGroup *pSysConfig) = 0;
	virtual void SysConfig(CDvmDataset *pSysConfig) = 0;
	virtual void SysConfig(const CString &strSysConfig ) = 0;
	virtual void SetDatas(CDvmDataset *pDataset) = 0;
	virtual void SetDatas(CDataGroup *pParas) = 0;
	virtual void SetDatas(const CString &strDataset) = 0;
	virtual void GetDatas(CDvmDataset *pParas) = 0;
	virtual void GetDatas(CDataGroup *pParas) = 0;
	virtual void GetDatas(CString& strParas) = 0;

	virtual void UpdateEventMsg(CEventResult *pCurrEventResult){}//测试功能更新参数
	virtual void ShowReport(CDvmValues *pValues){};
	virtual void UpdateTestResource(BOOL bCreateChMaps){}// 20220317 zhouhj
//	virtual void UpdateRtSyncTime(CDataGroup *pRtSycTime){}//20220920 zhouhj 更新对时、守时同步时间
	virtual void Debug(){};
	virtual BOOL IsHtmlView()	{	return FALSE;	}
	virtual long GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml)	{	return 0;	}
	virtual UINT GetMacroEditViewType()	{	return MACRO_EDIT_VIEW_TYPE_BASE;	}

	//2023-2-4  lijunqing 提高程序界面初始化打开的速度，将矢量图、状态图等的初始化放到线程
	virtual void InitSpyToolWidget()	{};

	//20230210 zhangyq  
	virtual void ProcessGbAfterGenTemplate(CSttGuideBook *pSttGuideBook){};  //测试模板
	virtual CString ProcessItemID(const CString & strItemID,long nLoopIndex){ return "";};  //根据当前测试的重复次数编号，动态生成ID

public:
	void* m_pMacroParaEditWnd;
	CExBaseObject *m_pSttItems;  //指向对应的rootnode的CSttItems对象。方便删除项目是查找视图，并关闭模板视图。
};

class CSttMacroParaEditMsgRcvInterface
{
public:
	CSttMacroParaEditMsgRcvInterface(){};
	virtual ~CSttMacroParaEditMsgRcvInterface(void){};

	//HTML ==>> APP
	virtual void UpdateDatas(CDvmDataset *pParas) = 0;
	virtual void OnItemsChanged(CDvmDataset *pParas) = 0;
	virtual void UI_ExecCmd(const CString &strCmd, CDvmDataset *pParas) = 0;
	virtual void UI_OK_Click(const CString &strHtmlFileName, CDvmDataset *pParas) = 0;
	virtual void UI_Cancel_Click(const CString &strHtmlFileName) = 0;

};

/*//模板结构
单功能：
	HdConfig     IEC61850Config   SystemConfig    MacroTest(MacroID)

单Web功能
	HdConfig     IEC61850Config   SystemConfig    MacroUI.id(Items)
*/
