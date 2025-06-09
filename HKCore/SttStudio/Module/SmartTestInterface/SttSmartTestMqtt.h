#pragma once

#include "XSmartTestEventInterface.h"
#include "../SttCmd/GuideBook/SttGuideBook.h"
#include "../../../IotAtsMngr/Module/Iot_AtsMngrDB/Iot_TypeTaskTestItemGen.h"
#include "../../../AutoTest/Module/GuideBook/Items.h"
#include "../../../IotAtsMngr/Module/Iot_AtsMngrDB/Iot_TypeTaskTest.h"

//MQTTģʽ�£��Զ����Է���ֻ����CreateTestָ��
//StartTest��StopTest��CloseTestָ��ŵ�SmartTest�ж���
class CSttSmartTestMqtt : public CXSttSmartTestXInterface
{
	//DECLARE_DYNCREATE(CSttSmartTesMqtt)

public:
	static CSttSmartTestMqtt * CreateSmartTest()
	{
		CSttSmartTestMqtt *pSttSmartTestMqtt = new CSttSmartTestMqtt();
		pSttSmartTestMqtt->InitSmartTestMqtt();
		//pSttSmartTestMqtt->CreateWnd();
		//pSttSmartTestMqtt->ShowWindow(SW_HIDE);
		return pSttSmartTestMqtt;
	}

public:
    CSttSmartTestMqtt();
    virtual ~CSttSmartTestMqtt();

	CDataGroup *m_pDevices;   //��¼����װ��  shaolei  20210.8.02
	
//	void CreateWnd();
	void InitSmartTestMqtt();
	void ExitSmartTestMqtt();

public:
	//���º���������0��ʾ�ɹ������ط���ֵ��ʾʧ��
    virtual long Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);

	virtual long Ats_StartTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_StopTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_CloseTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_TestItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_TestFrom(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_TestAllFailedItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_GetItemReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_GetReportFile(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_GetSystemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_FinishInputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_SetItemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_InputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
	virtual long Ats_ExportReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)     {    return 0;    }
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
	//���ش���������Ҫ����ص��ļ���ģ���ļ�����Լģ���ļ������Թ����ļ�
	BOOL DownLoadAllFiles(CSttAtsCmd *pAtsCmd);
	BOOL DownLoadFiles_Devices(CDataGroup *pDevices);  //����ģ���ļ��͹�Լģ��
	BOOL DownLoadFiles_TestApps(CDataGroup *pTestApps);  //���ز��Թ����ļ�

	//�������ݿ⣬��̬����ģ����������ɲ�����Ŀ��
	//�������������Ƿ�װһ��Tool��
	BOOL GenerateTemplate(const CString &strGbxmlFile, const CString &strItemsSN, CExBaseList *pListItems);
	BOOL GenerateTemplate(const CString &strGbxmlFile, CIot_TypeTaskTestItemGens* pItemGens, CExBaseList *pListItems);
	BOOL GenerateTemplate_UpdateParas(CItems *pChildItems, CIot_TypeTaskTestItemGen* pItemGen);

	//���ݿ��ά��
	//д������Լ�¼��
	BOOL DB_InsertTypeTaskTest(CSttAtsCmd *pAtsCmd, CExBaseList *pListItems);
	CIot_TypeTaskTest* DB_InsertTypeTaskTest(const CString &strUserName, const CString &strItemsSN, CDataGroup *pDevice);
	BOOL DB_InsertTypeTaskTest_Item(const CString &strHumidity, const CString &strTempreture, CIot_TypeTaskTest* pTypeTaskTest, CExBaseList *pListItems);
	BOOL DB_InsertTypeTask_TestApps(CSttAtsCmd *pAtsCmd);

	//�����Զ�����
	BOOL Ats_CreateTest_StartSmartTest(CSttAtsCmd *pAtsCmd);
};
