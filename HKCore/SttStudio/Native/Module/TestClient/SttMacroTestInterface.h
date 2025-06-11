#pragma once
#include "../SttCmd/SttSysState.h"
#include "../SttCmd/SttAtsCmd.h"

#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../AutoTest/Module/AutoTestGlobalDefine.h"


class CTestEventBaseInterface
{
//2022-8-20  lijunqing
public:
	virtual long Event_OnItemStateChanged(CSttParas *pSttParas){return 0;}
	virtual long Event_OnTestFinished(CSttParas *pSttParas){return 0;}
	virtual long Event_OnTestStarted(CSttParas *pSttParas){return 0;}
	virtual long Event_OnTestStoped(CSttParas *pSttParas){return 0;}
	virtual long Event_OnTestFinished(CSttParas *pSttParas, BOOL& bState){return 0;}////2024.1.8 yzj �ж�test-cmd�Ǵ���ģ���Ҫ�ж�ats-cmd������BOOL&�ı�ats�µ�״̬
	virtual long Event_OnTestStarted(CSttParas *pSttParas, BOOL& bState){return 0;}
	virtual long Event_OnTestStoped(CSttParas *pSttParas, BOOL& bState){return 0;}
	virtual long Event_OnExportRptFinished(CSttParas *pSttParas){return 0;}
	virtual long Event_OnTestAppEvent(CSttParas *pSttParas){return 0;}
	virtual long Event_OnTestCreated(CSttParas *pSttParas){return 0;}
	virtual long Event_OnOpenGbrptFileFailed(CSttParas *pSttParas){return 0;}
	virtual long Event_OnEngineEvent(CSttParas *pSttParas){return 0;}
	virtual long Event_OnSearchPointReport(CSttParas *pSttParas){return 0;}//zhouhj 20210925�������ڷ��ز��Ե㱨��
	virtual long Event_OnSearchPointFinish(CSttParas *pSttParas){return 0;}
	virtual long Event_OnExportRpt(CSttParas *pSttParas){return 0;}  //shaolei 20220718  ���������¼�
	virtual long Event_OnTestProcess(CSttParas *pSttParas){return 0;}  
	//�ز����   ���Բ��ϸ������  shaolei 2022-11-15
	virtual long Event_OnReTestFinished(CSttParas *pSttParas){return 0;}

	//zhouhj 2024.1.23 �������ڱ��ļ���
	virtual long Event_OnPkgSpy(CSttParas *pSttParas){return 0;}

public:
	virtual long Event_OnItemStateChanged(CSttSysState &oSysState)		{	return Event_OnItemStateChanged(oSysState.GetSttParas());	}
	virtual long Event_OnTestFinished(CSttSysState &oSysState)				{	return Event_OnTestFinished(oSysState.GetSttParas());	}
	virtual long Event_OnTestStarted(CSttSysState &oSysState)				{	return Event_OnTestStarted(oSysState.GetSttParas());	}
	virtual long Event_OnTestStoped(CSttSysState &oSysState)				{	return Event_OnTestStoped(oSysState.GetSttParas());	}
	virtual long Event_OnTestFinished(CSttSysState &oSysState, BOOL& bState){	return Event_OnTestFinished(oSysState.GetSttParas(), bState);	}
	virtual long Event_OnTestStarted(CSttSysState &oSysState, BOOL& bState){	return Event_OnTestStarted(oSysState.GetSttParas(), bState);	}
	virtual long Event_OnTestStoped(CSttSysState &oSysState, BOOL& bState){	return Event_OnTestStoped(oSysState.GetSttParas(), bState);	}
	virtual long Event_OnExportRptFinished(CSttSysState &oSysState)		{	return Event_OnExportRptFinished(oSysState.GetSttParas());	}
	virtual long Event_OnTestAppEvent(CSttSysState &oSysState)			{	return Event_OnTestAppEvent(oSysState.GetSttParas());	}
	virtual long Event_OnTestCreated(CSttSysState &oSysState)				{	return Event_OnTestCreated(oSysState.GetSttParas());	}
	virtual long Event_OnOpenGbrptFileFailed(CSttSysState &oSysState)	{	return Event_OnOpenGbrptFileFailed(oSysState.GetSttParas());	}
	virtual long Event_OnEngineEvent(CSttSysState &oSysState)				{	return Event_OnEngineEvent(oSysState.GetSttParas());	}
	virtual long Event_OnEngineReport(CSttParas *pParas){return 0;}
	virtual long Event_OnSearchPointReport(CSttSysState &oSysState)		{	return Event_OnSearchPointReport(oSysState.GetSttParas());	}//zhouhj 20210925�������ڷ��ز��Ե㱨��
	virtual long Event_OnSearchPointFinish(CSttSysState &oSysState)		{	return Event_OnSearchPointFinish(oSysState.GetSttParas());	}
	virtual long Event_OnExportRpt(CSttSysState &oSysState)					{	return Event_OnExportRpt(oSysState.GetSttParas());	}  //shaolei 20220718  ���������¼�
	virtual long Event_OnTestProcess(CSttSysState &oSysState)			{	return Event_OnTestProcess(oSysState.GetSttParas());	}
	//�ز����   ���Բ��ϸ������  shaolei 2022-11-15
	virtual long Event_OnReTestFinished(CSttSysState &oSysState)			{	return Event_OnReTestFinished(oSysState.GetSttParas());	}

	virtual long Event_OnPkgSpy(CSttSysState &oSysState)			{	return Event_OnPkgSpy(oSysState.GetSttParas());	}
	//����Ų�������У������ѻ�����У��ײ��Զ�������Ҫ���¼�ת�����ѻ��������Ų���˴�  shaolei 2022-1-11
	virtual long Event_OnTestState(CSttSysState &oSysState)
	{
		CSttParas *pParas = oSysState.GetSttParas();
		POS pos = pParas->GetHeadPosition();
		CExBaseObject *pCurObj = NULL;

		while(pos)
		{
			pCurObj = pParas->GetNext(pos);

			//shaolei yangyijun zhoulei 20210806
			//Ϊ������λ�����־����Ǻ����¼������¼���Group��ID��ͳһΪ:"Event***";
			//"Evnet"��Ϊ�̶�ǰ׺�����磺EventSwithChanged
			if (pCurObj->m_strID.Find(_T("Event")) >= 0)
			{
				OnTestState(_T(""),(CDataGroup*)pCurObj);
			}
		}

		return 1;
	}

	//zhouhj 2023.11.17 ���Ӵ˽ӿ�,���㵥�����������ʹ�õײ����͵Ĵ�ӡ��Ϣ
	virtual long Process_SysState_Log(CSttSysState &oSysState)
	{
		CSttMsgs *pMsgs = oSysState.GetSttMsgs();
		POS pos = pMsgs->GetHeadPosition();
		CSttMsg *pData = NULL;
		CString strLog;

		while (pos != NULL)
		{
			pData = (CSttMsg *)pMsgs->GetNext(pos);

			if (pData->m_strMsg.Find("[error]") != -1)
			{
				strLog = pData->m_strMsg;
				strLog.Replace("[error]","[tester error]");
				CLogPrint::LogString(XLOGLEVEL_RESULT, strLog);
			}
			else
			{
			strLog = _T("*********************");
			strLog += pData->m_strMsg;
			CLogPrint::LogString(XLOGLEVEL_TRACE, strLog);
		}

		}

		return 0;
	}
	
	virtual long Event_OnProcessInputDataCmd(CSttAtsCmd &oAtsCmd){return 0;}
	virtual long Event_OnProcessComtradeRequstData(long nIndex){return 0;}
	virtual long Event_OnProcessComtradeSendDataStartAck(long nIndex){return 0;}

	virtual void OnException(CDataGroup *pParas){}
	virtual void OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas){}
	virtual void OnReport(CDataGroup *pParas){}
	virtual void OnReport(CSttSysState &oSysState){}
	virtual long OnUpdate(CSttParas *pParas){return 0;}
	virtual long OnViewPackage(CSttParas *pParas){return 0;}
    virtual long OnRtData(CSttParas *pParas){return 0;}//ʵʱ���ݴ���
	virtual long OnMeas(CDataGroup *pParas){return 0;}
	virtual long OnAts_Stop(CDataGroup *pParas){return 0;}
	virtual long OnRecvLiveUpdate(CSttSysState &oSysState){return 0;}
	//shaolei 2022-1-11
	virtual void OnTestState(const CString &strMacroID, CDataGroup *pParas) {	}

	virtual void OnRecvSttDebugData(CSttSysState &oSysState){}
	virtual BOOL OnRecvSttDebugData(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor, char *pszRetCmdType)	{	return FALSE;	}

	//2020-10-22  lijunqing �����豸��Ϣ���ݣ����磺װ����Ϣ��ģ����Ϣ�ȣ��Լ�ϵͳ�Ĳ������õ�
	virtual void OnRecvSttDeviceData(CSttSysState &oSysState){}
	virtual long OnDisConnect(){return 0;}


	virtual void OnRecvSysConfigData(CSttParas *pSttParas){} //chenling 2024.10.11 ����GetSysConfig��IP

	//2020-11-29 lijunqing 
	virtual void OnTestMsg(BYTE *pBuf, long nLen){}

	//2022-01-18  lijunqing
	virtual void On_Ats_Generate(const CString &strAtsCmd, CSttParas *pParas){};
	//2022-04-18  shaolei
	virtual void On_Ats_SaveTest(CSttSysState *pSysState){};
	virtual void On_Ats_SaveTemplate(CSttSysState *pSysState){};
	virtual void On_Ats_CreateTest(CSttSysState *pSysState){};
	virtual void On_Ats_AdjustMainWnd(CSttSysState *pSysState){};

	//2022-06-25  shaolei
	virtual void On_Ats_ExportWordRpt(CSttSysState *pSysState){};
	
	//shaolei 20220812  ����REPLYӦ��
	virtual void On_SysState_Test(CSttSysState *pSysState)	{	}

	//2022-9-13  lijunqing
	virtual void On_Ats_QueryItem(CSttSysState *pSysState){};
	
	//lijunqing 2022-10-8  ����REPLYӦ��-IOT
	virtual void On_SysState_IOT(CSttSysState *pSysState)	{	}
};


class CMacroTestEventInterface : public CTestEventBaseInterface
{
public:
	CMacroTestEventInterface(){};
	virtual ~CMacroTestEventInterface(){};

public:
	virtual long Event_OnTestFinished(CSttSysState &oSysState)
	{
		Event_OnTestState(oSysState);//�Ƚ������Խ���Event�еĿ��������� zhouhj20210603
		CSttMacro *pMacro = oSysState.GetSttMacro();

		if (pMacro != NULL)
		{
/*
			SYSTEMTIME tm;
			::GetLocalTime(&tm);
			CString strTmpPath = _P_GetLibraryPath();
			strTmpPath.AppendFormat(_T("OnTestFinished%d-%d-%d %d-%d-%d.%d.xml"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond,tm.wMilliseconds);
			oSysState.SaveXmlFile(strTmpPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
*/
			CSttParas *pParas = oSysState.GetSttParas();// zhouhj 20210712 ��ΪoSysState.GetParas()��ԭ��ΪpMacro�µģ����صĽ��Ӧ������oSysState�µ�paras
			CSttResults *pResult = pMacro->GetResults();
			OnTestFinished(pMacro->m_strID,pParas,pResult);
		}

		return 1;
	}

	virtual long Event_OnTestStarted(CSttSysState &oSysState)
	{
//		oSysState.SaveXmlFile(_T("D:\\0001.xml"),CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		CString strMacroID;
		CSttParas *pParas = oSysState.GetSttParas();
		CSttMacro *pMacro = oSysState.GetSttMacro();

		if (pMacro != NULL)
		{
			strMacroID = pMacro->m_strID;
		}

		OnTestStarted(strMacroID, pParas);
		return 1;
	}

	virtual long Event_OnTestStoped(CSttSysState &oSysState)
	{
		CString strMacroID;
		CSttParas *pParas = oSysState.GetSttParas();
		CSttMacro *pMacro = oSysState.GetSttMacro();

		if (pMacro != NULL)
		{
			strMacroID = pMacro->m_strID;
		}

		OnTestStoped(strMacroID, pParas);
		return 1;
	}

	virtual long Event_OnTestFinished(CSttSysState &oSysState, BOOL& bState)
	{
		return Event_OnTestFinished(oSysState);
	}

	virtual long Event_OnTestStarted(CSttSysState &oSysState, BOOL& bState)
	{
		return Event_OnTestStarted(oSysState);
	}

	virtual long Event_OnTestStoped(CSttSysState &oSysState, BOOL& bState)
	{
		return Event_OnTestStoped(oSysState);
	}

	virtual long Event_OnSearchPointFinish(CSttSysState &oSysState)//zhouhj 20210925 �������ڷ��ز��Ե㱨��
	{
		CSttMacro *pMacro = oSysState.GetSttMacro();

		if (pMacro != NULL)
		{
			CSttParas *pParas = pMacro->GetParas();
			CSttResults *pResult = pMacro->GetResults();
			OnSearchPointFinish(pMacro->m_strID,pParas,pResult);
		}
		return 1;
	}

	virtual long Event_OnSearchPointReport(CSttSysState &oSysState)
	{
		CSttMacro *pMacro = oSysState.GetSttMacro();

		if (pMacro != NULL)
		{
 			CSttSearchResults *pSearchResults = pMacro->GetSearchResults();
			OnSearchPointReport(pMacro->m_strID,pSearchResults);
		}

		Event_OnTestState(oSysState);
		return 1;
	}

	virtual long Process_SysState_Log(CSttSysState &oSysState)
	{
		return CTestEventBaseInterface::Process_SysState_Log(oSysState);
	}

	//Ų��������  shaolei 2022-1-11
	//virtual long Event_OnTestState(CSttSysState &oSysState)
	
	
public:
	virtual void OnTestStarted(const CString &strMacroID, CDataGroup *pParas) = 0;
	virtual void OnTestStoped(const CString &strMacroID, CDataGroup *pParas) = 0;
	virtual void OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults) = 0;
	virtual void OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults) = 0;	
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults) = 0;
	//Ų��������  shaolei  2022-1-11
	//virtual void OnTestState(const CString &strMacroID, CDataGroup *pParas) = 0;
};

class CTestEventInterface : public CTestEventBaseInterface
{
public:
	virtual BOOL IsAtsRetCmd(CSttParas *pParas)
	{
		return FALSE;
	}

	virtual long Event_OnTestFinished(CSttSysState &oSysState)
	{
		CString strTestID = _T("");
		long nDeviceIndex = 0,nReportIndex = 0;

		CSttParas *pParas = oSysState.GetSttParas();
		oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_ReportIndex,nReportIndex);

		return OnTestFinished(strTestID,nDeviceIndex,nReportIndex,pParas);
	}

	virtual long Event_OnTestFinished(CSttSysState &oSysState, BOOL& bState)
	{
		CString strTestID = _T("");
		long nDeviceIndex = 0,nReportIndex = 0;

		CSttParas *pParas = oSysState.GetSttParas();
		oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_ReportIndex,nReportIndex);

		if(IsAtsRetCmd(pParas))
		{
			bState = FALSE;
		}
		
		return OnTestFinished(strTestID,nDeviceIndex,nReportIndex,pParas);
	}

	virtual long Event_OnItemStateChanged(CSttSysState &oSysState)
	{
		CString strTestID = _T(""),strItemID = _T(""), strState = _T(""), strSelect = _T("");
		long nDeviceIndex = 0,nReportIndex = 0,nItemIndex = 0;

		CSttParas *pParas = oSysState.GetSttParas();
		oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_ReportIndex,nReportIndex);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_ItemIndex,nItemIndex);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_ItemID,strItemID);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_State,strState);
		long nState = GB_GetTestStateByIDEx(strState);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_State,strSelect);

		return OnItemStateChanged(strTestID,nDeviceIndex,nReportIndex,nItemIndex,strItemID,nState,pParas);
	}

	virtual long Event_OnTestStarted(CSttSysState &oSysState)
	{
		CString strTestID = _T("");
		long nDeviceIndex = 0,nReportIndex = 0;

		CSttParas *pParas = oSysState.GetSttParas();
		oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_ReportIndex,nReportIndex);

		return OnTestStarted(strTestID,nDeviceIndex,nReportIndex,pParas);
	}

	virtual long Event_OnTestStarted(CSttSysState &oSysState, BOOL& bState)
	{
		CString strTestID = _T("");
		long nDeviceIndex = 0,nReportIndex = 0;

		CSttParas *pParas = oSysState.GetSttParas();
		oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_ReportIndex,nReportIndex);

		if(IsAtsRetCmd(pParas))
		{
			bState = TRUE;
		}

		return OnTestStarted(strTestID,nDeviceIndex,nReportIndex,pParas);
	}

	virtual long Event_OnTestStoped(CSttSysState &oSysState)
	{
		CString strTestID = _T("");
		long nDeviceIndex = 0,nReportIndex = 0;

		CSttParas *pParas = oSysState.GetSttParas();
		oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_ReportIndex,nReportIndex);

		return OnTestStoped(strTestID,nDeviceIndex,nReportIndex,pParas);
	}

	virtual long Event_OnTestStoped(CSttSysState &oSysState, BOOL& bState)
	{
		CString strTestID = _T("");
		long nDeviceIndex = 0,nReportIndex = 0;

		CSttParas *pParas = oSysState.GetSttParas();
		oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_ReportIndex,nReportIndex);

		if(IsAtsRetCmd(pParas))
		{
			bState = FALSE;
		}

		return OnTestStoped(strTestID,nDeviceIndex,nReportIndex,pParas);
	}

	virtual long Event_OnSearchPointReport(CSttSysState &oSysState)
	{
		CSttMacro *pMacro = oSysState.GetSttMacro();

		if (pMacro != NULL)
		{
			CSttSearchResults *pSearchResults = pMacro->GetSearchResults();
			OnSearchPointReport(pMacro->m_strID,pSearchResults);
		}

		Event_OnTestState(oSysState);
		return 1;
	}


	virtual long Event_OnTestCreated(CSttSysState &oSysState)
	{
		CString strTestID = _T("");

		CSttParas *pParas = oSysState.GetSttParas();
		oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);

		return OnTestCreated(strTestID,pParas);
	}

	virtual long Event_OnEngineEvent(CSttSysState &oSysState)
	{
		CString strTestID = _T(""),strEvent = _T("");
		long nDeviceIndex = 0;

		CSttParas *pParas = oSysState.GetSttParas();
		oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
		oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
		oSysState.GetParasDataValueByID(_T("EventID"),strEvent);

		return OnEngineEvent(strTestID,nDeviceIndex,strEvent,pParas);
	}

	virtual long Event_OnProcessInputDataCmd(CSttAtsCmd &oAtsCmd)
	{
		return OnProcessInputDataCmd(oAtsCmd.GetSttParas(),oAtsCmd.GetSttMsgs());
	}

	virtual long Event_OnTestProcess(CSttSysState &oSysState)
	{
		return OnTestProcess(oSysState.GetSttParas());
	}

	virtual long Event_OnExportRpt(CSttSysState &oSysState)
	{
		CSttParas *pParas = oSysState.GetSttParas();
		return OnExportRptEvent(pParas);
	}

	virtual long Event_OnReTestFinished(CSttSysState &oSysState)
	{
		CSttParas *pParas = oSysState.GetSttParas();
		return OnReTestFinished(pParas);
	}

public:
	virtual long OnItemStateChanged(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas) = 0;
	virtual long OnTestFinished(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas) = 0;
	virtual long OnTestStarted(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas){return 0;}
	virtual long OnTestStoped(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas) = 0;
	virtual long OnTestCreated(const CString &strTestID, CSttParas *pParas) = 0;
	virtual long OnEngineEvent(const CString &strTestID, long nDeviceIndex, const CString & strEvent, CSttParas *pParas) = 0;
	virtual long OnProcessInputDataCmd(CSttParas *pParas,CExBaseList *pMsgs){return 0;}
	virtual long OnTestProcess(CSttParas *pParas) { return 0;}
	virtual long OnExportRptEvent(CSttParas *pParas)	{	return 0;	}
	virtual long OnReTestFinished(CSttParas *pParas)	{	return 0;	}

	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults){ }

	
};

//2022-1-14  lijunqing  Ϊ��ʹ�õķ��㣬�����Զ����ԵĽӿڡ�CTestEventInterface�Ժ���Կ��Ǵ�����Ľӿ�������˫����
class CAtsEventInterface
{
public:
	//2022-6-9  lijunqing��ע��OnUpdateGpsTime������������ص����⣬�˲������ǵĺ�����ʱ��ͬ��SyncTime
	//������������ô��Ĳ����������ο�On_IecDetect��Ӧ����DataGroup�����������ݴ���
	//Error?????????????????
	virtual long OnUpdateSyncTime(CDataGroup *pRtSyncTime)	{	return 0;	}//
	virtual long OnUpdateException(){return 0;}//20220914 zhouhj �����쳣��Ϣ
	//GpsTime(long nSyn, long nSecond,long nNSecend,long n4G, long nWifi, long nBle,
	//	long nPowerAC, long nBatCap,long nUSB){	return 0;	}//����GPSʱ�䡢��ص����Լ�USB״̬��û��ú�����ɶ��������ǰ���� sf 20220228

	virtual long OnConnectStateChanged(bool bState){	 return 0;	} //sf 20220225 ����״̬�ı� 
	virtual long OnItemStateChanged(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas) = 0;
	virtual long OnTestFinished(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas) = 0;
	virtual long OnTestStarted(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas) = 0;
	virtual long OnTestStoped(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas) = 0;
	virtual long OnTestCreated(const CString &strTestID, CSttParas *pParas) = 0;
	virtual long OnEngineEvent(const CString &strTestID, long nDeviceIndex, const CString & strEvent, CSttParas *pParas) = 0;
	virtual long OnProcessInputDataCmd(CSttParas *pParas,CExBaseList *pMsgs) = 0;
	virtual long OnTestProcess(CSttParas *pParas){ return 0; }
	virtual long OnExportRptEvent(CSttParas *pParas) = 0;
	virtual long OnReTestFinished(CSttParas *pParas){	return 0;	}
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults){ }


	virtual void OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas) = 0;
	virtual void OnReport_ReadDevice(CDataGroup *pDeviceGroup){}
	virtual void OnReport_ReadSystemState(const CString &strMacroID, CDataGroup *pParas){}

	//2022-01-18  lijunqing
	virtual void On_Ats_Generate(const CString &strAtsCmd, CSttParas *pParas) = 0;
	//2022-04-18  shaolei
	virtual void On_Ats_SaveTest(CSttSysState *pSysState) = 0;
	virtual void On_Ats_SaveTemplate(CSttSysState *pSysState) = 0;
	virtual void On_Ats_CreateTest(CSttSysState *pSysState) = 0;
	virtual void On_Ats_AdjustMainWnd(CSttSysState *pSysState) = 0;

	//2022-06-25  shaolei
	virtual void On_Ats_ExportWordRpt(CSttSysState *pSysState) = 0;

	//2022-4-13  lijunqing
	virtual void On_IecDetect(CDataGroup *pIecCb) = 0;

	//2022-9-13  lijunqing
	virtual void On_Ats_QueryItem(CSttSysState *pSysState) = 0;

	//2022-10-6  lijunqing
	virtual long On_RtData(CDataGroup *pRtData)	{	return 0;	}

};
