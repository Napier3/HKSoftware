#pragma once

#include "../../AutoTest/Module/SmartTestInterface.h"

#include "../../SttStudio/Module/SttCmd/SttSysState.h"
#include "../../SttStudio/Module/SttCmd/SttAtsCmd.h"
#include "../../Module/System/StringTokenizer.h"
#include "../../Module/BaseClass/XTimer.h"


class CIotSmartTestCtrl : public CExBaseObject,public CXTimer
{
public:
	CIotSmartTestCtrl();
	virtual ~CIotSmartTestCtrl();

	//m_strID:����̨ID,��TestID
	SmartTest::CTestAppMngr  m_oTestAppMngr;//�Զ�����com����
	CString m_strDeviceSN;
	CString m_strFormat;	//XML | JSON
	CString m_strCmd;
	CString m_strReplyTopic;

public:
	virtual void OnXTimer(DWORD dwTimerID);

public:
	CDataGroup m_oDevices;//����װ���б�,����DeviceSN��DeviceIndex��ת
	BOOL GetDeviceSNByIndex(long nDeviceIndex,CString &strDeviceSN);
	BOOL GetDeviceIndexBySN(const CString &strDeviceSN,long &nDeviceIndex);

public:
	SmartTest::CTestAppMngr GetTestAppMngr();
	void OnMqttMsgRecieve(CStringTokenizer &oToken,char *pBuf,long nLen);

public:
	//��������׼��������������ģ�塢ģ�ͺ͹�Լ�ļ��Ƿ���ڣ���������ӷ���������
	BOOL CheckCreateTest(CSttAtsCmd &oAtsCmd);

	//�����Զ���������
	BOOL Process_Cmd_Ats_CreateTest(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_BeginTest(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_StopTest(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_CloseTest(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_TestItem(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_TestFrom(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_TestAllFailedItems(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_SetItemState(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_ConfigDevice(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_ConnectDevice(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_CloseDevice(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_ConfigEngine(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_GetDataset(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_SetDataset(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_RunProcedure(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_QueryAtsFile(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_FinishInputData(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_ExportReport(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_QueryItems(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_SetItemsReport(CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_ConfigTest(CSttAtsCmd &oAtsCmd);

	//���������������
	long Ats_InputData(const CString &strDeviceID,CDataGroup *pDatas,CExBaseList *pMsgs,const CString &strFormat=MQTT_DATA_FORMAT_XML);

	//�¼�����ӿ�
public:
	long TES_OnItemStateChanged(long nDeviceIndex, long nReportIndex, long nItemIndex, const CString &strItemID, const CString &strState);
	long TES_OnTestFinished(long nDeviceIndex, long nReportIndex);
	long TES_OnTestStoped(long nDeviceIndex, long nReportIndex);
	long TES_OnExportRptFinished(long nDeviceIndex, long nReportIndex);
	long TES_OnTestAppEvent(const CString &strEvent);
	long TES_OnEngineEvent(long nDeviceIndex, const CString &strEvent);
	long TES_OnTestCreated();
	long TES_OnOpenGbrptFileFailed();

	//����xml������ʱ��Ƶ�������ڴ棬ȱʡΪ1M
protected:
	char *m_pszXmlBuffer;
	long m_nXmlBufferLen;
	void SetXmlBufferLen(long nLen);

	void PraseBuf2CmdObject(CSttCmdBase *pCmdBase,char *pBuf,long nLen);
};

/////////////////////
long ReturnSysState(const CString &strTopic,const CString &strFormat,CSttCmdBase *pSttCmd, long nCmdExecStatus,CSttCmdData *pRetData=NULL);
long PublicCmd(const CString &strTopic,const CString &strFormat,CSttCmdBase *pSttCmd);