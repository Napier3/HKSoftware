#pragma once

#include "XSmartTestEventInterface.h"
#include "../SttCmd/GuideBook/SttGuideBook.h"
#include "../../../AutoTest/Module/GuideBook/Items.h"

#define SMART_TEST_CMD_ID_CreateTest  _T("CreateTest")
#define SMART_TEST_CMD_ID_ExportReport  _T("ExportReport")
#define SMART_TEST_CMD_ID_ReTest  _T("ReTest")
#define SMART_TEST_CMD_ID_open_gbrpt  _T("open_gbrpt")
#define SMART_TEST_CMD_ID_MQTT  _T("MQTT")
#define SMART_TEST_CMD_ID_StartTestAfterCreate  _T("StartTestAfterCreate")

//MQTT模式下，自动测试服务只订阅CreateTest指令
//StartTest、StopTest、CloseTest指令都放到SmartTest中订阅
class CSttSmartTestMqttBase : public CXSttSmartTestXInterface
{
	//DECLARE_DYNCREATE(CSttSmartTesMqtt)

public:
	static CSttSmartTestMqttBase * CreateSmartTest()
	{
		CSttSmartTestMqttBase *pBase = new CSttSmartTestMqttBase();
		pBase->InitSmartTestMqtt();
		//pBase->CreateWnd();
		//pBase->ShowWindow(SW_HIDE);
		return pBase;
	}

public:
    CSttSmartTestMqttBase();
    virtual ~CSttSmartTestMqttBase();

	CDataGroup *m_pDevices;   //记录被测装置  shaolei  20210.8.02
	HINSTANCE m_hInstance;
	
//	void CreateWnd();
	void InitSmartTestMqtt();
	void ExitSmartTestMqtt();

public:
	//以下函数，返回0表示成功，返回非零值表示失败
    virtual long Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);

	virtual long Ats_StartTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_StopTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_CloseTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_TestItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_TestFrom(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_TestAllFailedItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_GetItemReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_GetReportFile(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_GetSystemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_FinishInputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_SetItemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_InputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_ExportReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_SetItemsReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_QueryItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_ConfigTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_QueryTestParas(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_SetTestParas(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_GenerateItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_GenerateMacroTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_SetItemPara(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_ManualTrigger(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_SaveTemplate(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_SaveTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_OpenTemplate(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_OpenGbrptFile(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_AdjustMainWnd(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_UpdateItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_AdjustReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual CString Ats_QueryItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Process_Cmd_Ats_Event_UploadFinish(CSttCmdBase* pSttCmdBase)     {    return 0;    }

	virtual long Process_Cmd_SysState_ItemStateChanged(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Process_Cmd_SysState_TestFinished(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Process_Cmd_SysState_TestStarted(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Process_Cmd_SysState_TestStoped(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Process_Cmd_SysState_OnReport(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Process_Cmd_SysState_ExportReport(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol);

public:
	virtual long OnItemStateChanged(const CString& strDeviceID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString& strItemID, const CString& strState, long nSelect){	return 0;	}
	virtual long OnTestFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex){	return 0;	}
	virtual long OnTestStoped(const CString& strDeviceID, long nDeviceIndex, long nReportIndex){	return 0;	}
	virtual long OnExportRptEvent(const CString& strDeviceID, const CString &strEventID, long nDeviceIndex, long nReportIndex){	return 0;	}
	virtual long OnTestAppEvent(const CString& strDeviceID, const CString& strEvent){	return 0;	}
	virtual long OnEngineEvent(const CString& strDeviceID, long nDeviceIndex, const CString& strEvent){	return 0;	}
	virtual long OnTestCreated(const CString& strDeviceID){	return 0;	}
	virtual long OnOpenGbrptFileFailed(const CString& strDeviceID){	return 0;	}
	virtual long OnTestProcess(const CString& strDeviceID, const CString& strTestID, long nTotalItems, long nCurrItem, long nTotalTime, long nRemainTime, const CString& strDeviceState){	return 0;	}
	virtual long OnTestProcess(CExBaseList* pSttParas) {	return 0;	}
	virtual long OnReTestFinished(CExBaseList* pSttParas)  {	return 0;	}
	virtual long OnTestStarted(const CString& strDeviceID, long nDeviceIndex, long nReportIndex){	return 0;	}
	virtual long OnUploadRptFile(const CString& strDeviceID, const CString &strFiles){	return 0;	}

	virtual long OnInputData(const CString& strDatas, const CString& strMsgs){	return 0;	}
	virtual long OnInputData(CExBaseList *pSttParas, CExBaseList *pSttMsgs){	return 0;	} 
	virtual long On_Ats_CreateTest(const CString &strGbrptFile)	{	return 0;	}  
	virtual long On_Ats_AdjustMainWnd(LONG nMainWnd)	{	return 0;	} 

public:
	virtual long ReturnSysState_REPLY(CSttProtocolInterface *pSttProtocol, CSttCmmOptrInterface *pCmmOptrInterface, long nCmdExecStatus, CSttCmdData *pRetData, char *pszEventID);
	virtual long ReturnSysState_EVENT(CSttProtocolInterface *pSttProtocol, CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszEventID);

	CString GetItemType(UINT nClassID);
	//下载创建测试需要的相关的文件：模型文件、规约模板文件、测试功能文件
	BOOL DownLoadAllFiles(CSttAtsCmd *pAtsCmd);
	BOOL DownLoadFiles_Devices(CDataGroup *pDevices);  //下载模型文件和规约模板
	BOOL DownLoadFiles_TestApps(CDataGroup *pTestApps);  //下载测试功能文件

	//拉起自动测试
	BOOL Ats_CreateTest_StartSmartTest(CSttAtsCmd *pAtsCmd, const CString &strSmartTestCmdID);
};
