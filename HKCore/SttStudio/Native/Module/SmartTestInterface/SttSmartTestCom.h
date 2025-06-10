#pragma once

#include "XSmartTestEventInterface.h"
#include "../../../AutoTest/Module/XSmartTestClient.h"
#include "../SttCmd/GuideBook/SttGuideBook.h"
#include "..\..\..\Module\Office\msword9.h"

//2021-7-27   lijunqing 由  CDynDialogEx  改为 CWnd，简化基类的引用
//2021-8-3  lijunqing 总的接口CXSttSmartTestXInterface，方便访问
class CSttSmartTestCom : public CXSttSmartTestXInterface, public CWnd
{
	DECLARE_DYNCREATE(CSttSmartTestCom)

public:
	static CSttSmartTestCom * CreateSmartTest()
	{
		CSttSmartTestCom *pSttSmartTestCom = new CSttSmartTestCom();
		pSttSmartTestCom->CreateWnd();
		pSttSmartTestCom->ShowWindow(SW_HIDE);
		return pSttSmartTestCom;
	}

public:
    CSttSmartTestCom();
    virtual ~CSttSmartTestCom();

	CXSmartTestClient *m_pXSmartTestClient;
	CDataGroup *m_pDevices;   //记录被测装置  shaolei  20210.8.02
	
	void CreateWnd();
	void InitSmartTestCom();
	void ExitSmartTestCom();

	//shaolei 20210927
	//该两个变量用于记录外部系统上传的报告文件和原始记录文件的全路径
	//由于自动测试结束后，先导出博电的报告，后进行合并，需要对文件名进行记录
	//合并结束后，清空记录的文件名
	CString m_strDocFile;
	CString m_strDocFileEx;

public:
	//以下函数，返回0表示成功，返回非零值表示失败
    virtual long Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_StartTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_StopTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_CloseTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_TestItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_TestFrom(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_TestAllFailedItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//GetItemReport，该命令是以被测设备为单位，查看选定装置的某个项目的报告
    virtual long Ats_GetItemReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//GetReportFile，该命令是以被测设备为单位，获取选定装置的报告文件
    virtual long Ats_GetReportFile(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_GetSystemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//FinishInputData，多装置时，每个装置调用一次
    virtual long Ats_FinishInputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//SetItemState，该命令是以被测设备为单位，设定选定装置的某个项目的状态
    virtual long Ats_SetItemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//InputData，多装置时，每个装置调用一次
	virtual long Ats_InputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//以测试台为单位，导出所有被测设备的测试报告
	virtual long Ats_ExportReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//SetItemsReport，该命令是以被测设备为单位，设置选定装置的某个项目的报告
	virtual long Ats_SetItemsReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//QueryItems，该命令是以被测设备为单位，查询选定装置的某个测试项目
	virtual long Ats_QueryItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);

	virtual long Ats_ConfigTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_QueryTestParas(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_SetTestParas(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_GenerateItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_GenerateMacroTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_SetItemPara(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_ManualTrigger(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_SaveTemplate(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_SaveTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_OpenTemplate(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_OpenGbrptFile(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_AdjustMainWnd(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_UpdateItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_AdjustReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual CString Ats_QueryItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return _T("");	}

	//shaolei 20210927
	virtual long Process_Cmd_Ats_Event_UploadFinish(CSttCmdBase* pSttCmdBase);

	virtual long Process_Cmd_SysState_ItemStateChanged(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Process_Cmd_SysState_TestFinished(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Process_Cmd_SysState_TestStarted(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)  {	return 0;	}
	virtual long Process_Cmd_SysState_TestStoped(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Process_Cmd_SysState_OnReport(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Process_Cmd_SysState_ExportReport(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}

public:
	virtual long OnItemStateChanged(const CString& strDeviceID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString& strItemID, const CString& strState, long nSelect);
	virtual long OnTestFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex);
	virtual long OnTestStoped(const CString& strDeviceID, long nDeviceIndex, long nReportIndex);
	virtual long OnExportRptEvent(const CString& strDeviceID, const CString &strEventID, long nDeviceIndex, long nReportIndex);
	virtual long OnTestAppEvent(const CString& strDeviceID, const CString& strEvent);
	virtual long OnEngineEvent(const CString& strDeviceID, long nDeviceIndex, const CString& strEvent);
	virtual long OnTestCreated(const CString& strDeviceID);
	virtual long OnOpenGbrptFileFailed(const CString& strDeviceID);
	virtual long OnTestProcess(const CString& strDeviceID, const CString& strTestID, long nTotalItems, long nCurrItem, long nTotalTime, long nRemainTime, const CString& strDeviceState);
	virtual long OnTestProcess(CExBaseList* pSttParas) {	return 0;	}
	virtual long OnReTestFinished(CExBaseList* pSttParas)  {	return 0;	}
	virtual long OnTestStarted(const CString& strDeviceID, long nDeviceIndex, long nReportIndex);
	virtual long OnUploadRptFile(const CString& strDeviceID, const CString &strFiles){	return 0;	}

	virtual long OnInputData(const CString& strDatas, const CString& strMsgs){	return 0;	}
	virtual long OnInputData(CExBaseList *pSttParas, CExBaseList *pSttMsgs){	return 0;	} //lijunqing 2022-6-27  直接传入数据对象，方便处理对象转换为XML或者JSON等不同的格式
	virtual long On_Ats_CreateTest(const CString &strGbrptFile)	{	return 0;	}  //shaolei 20220707  CreateTest的REPLY，返回gbrptfile的全路径
	virtual long On_Ats_AdjustMainWnd(LONG nMainWnd)	{	return 0;	}  //shaolei 20220718  AdjustMainWnd的REPLY，返回SmartTest的MainWnd
public:
	virtual long ReturnSysState_REPLY(CSttProtocolInterface *pSttProtocol, CSttCmmOptrInterface *pCmmOptrInterface, long nCmdExecStatus, CSttCmdData *pRetData, char *pszEventID);
	virtual long ReturnSysState_EVENT(CSttProtocolInterface *pSttProtocol, CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszEventID);

	//2021-8-6  lijunqing
	virtual long ReturnSysState_REPORT(CSttProtocolInterface *pSttProtocol, CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData);

	CDataGroup* GetReportFiles(const CString &strDeviceID);
	//跟word相关的操作 先放在这边，后面需要封装
	MSWord::_Application m_WordApp;
	MSWord::_Application GetWordApp(BOOL bShow=FALSE);
	//目前CWordRptEdit相关的类，包含了CGuideBook模块
	BOOL wordOptr_ActiveWindow(MSWord::_Application	&oWordApp, const CString &strTitle);
	CString CombineWordFile(const CString &strFile1, const CString &strFile2, BOOL bToPdf = FALSE);
	//BOOL UploadAllRptFiles(CDataGroup* pFiles);
private:
	void word_close_doc(MSWord::_Document &oDoc, MSWord::_Document &oDoc2);
	BOOL word_insert_doc_bkmk(MSWord::_Document &oDoc, MSWord::_Document &oDoc2, const CString &strFile1, const CString &strFile2);
	BOOL word_insert_doc_tail(MSWord::_Document &oDoc, MSWord::_Document &oDoc2, const CString &strFile1, const CString &strFile2);

public:
	BOOL DownLoadAllFiles(CSttAtsCmd *pAtsCmd);
	BOOL DownLoadFiles_Devices(CDataGroup *pDevices);  //下载模型文件和规约模板
	BOOL DownLoadFiles_TestApps(CDataGroup *pTestApps);  //下载测试仪配置文件
};
