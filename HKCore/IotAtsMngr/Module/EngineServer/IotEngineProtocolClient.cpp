#include "stdafx.h"
#include "IotEngineProtocolClient.h"
#include "SttProtoClientMqttClient.h"
#include "../../../SttStudio/Module/SttCmd/SttIotCmd.h"
#include "../IotEngineGlobalDef.h"
#include "../ProtocolBase/PxProtocolImpInterface.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotEngineProtocolClient::CIotEngineProtocolClient()
{
	m_hMsgWnd = NULL;
	m_nMsg = NULL;
	m_hSysMsgWnd = NULL;
	m_nSysMsg = NULL;

	m_pCurDataset = NULL;
	m_nTestState = IOT_TEST_STATE_IDLE;

	//�������ڶ���
	m_oXCommSvrWnd.CreateXCommSvrWnd(this);
}

CIotEngineProtocolClient::~CIotEngineProtocolClient()
{
	
}

void CIotEngineProtocolClient::OnXTimer(UINT nIDEvent)
{
	CString strTempCmd = m_strCurCmd;
	InitTestState();

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("----OnXTimer::[%s]���ʱ"),strTempCmd);

	if (strTempCmd == STT_CMD_TYPE_IOT_CreateDevice)
	{
		PostDeviceSysMessage(0, engineConnectDeviceFailed);
	}
	else if (strTempCmd == STT_CMD_TYPE_IOT_RunProcedure)
	{
		PostDeviceCommCmdMessage(0, engineCommError);
	}
}

//mqtt���Ӷ���
void CIotEngineProtocolClient::OnClose(char *pszErr)
{
	m_bConnected = FALSE;
	FreePxCmmInterface();
}

BOOL CIotEngineProtocolClient::Init(const char *pszIP,long nPort)
{
	FreePxCmmInterface();

	CSttProtoClientMqttClient *pProtocolMqttClient = new CSttProtoClientMqttClient();
	pProtocolMqttClient->InitTopicSrcInfo(_T(""),m_strDeviceID);
	m_bConnected = pProtocolMqttClient->Connect(pszIP,nPort, _T("IotEngine"));

	if (m_bConnected)
	{
		m_strIP = pszIP;
		m_nPort = nPort;

		pProtocolMqttClient->SetMqttEngineRef(this);
		AttachPxCmmInterface(pProtocolMqttClient);
	}
	else
	{
		delete pProtocolMqttClient;
	}

	return m_bConnected;
}

/************************
���⣺
�����SN/DeviceID/IotState/PkgParse/REPLY
�����SN/DeviceID/IotState/PkgProduce/REPLY
�����SN/DeviceID/IotState/RunProcedure/REPLY
�����SN/DeviceID/IotState/GetDataset/REPLY
�����SN/DeviceID/IotState/ConfigDevice/REPLY
�����SN/DeviceID/IotState/CloseDevice/REPLY

�����SN/DeviceID/IotState/RunProcedure/EVENT/�¼�ID
�����SN/DeviceID/IotState/EngineEvent/EVENT/DeviceClosed
**************************/
long CIotEngineProtocolClient::OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface,const CString &strFromSN,  char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType)
{
	CSttSysState oSysState;
	BufToCmd(&oSysState,pBuf,nLen,MQTT_DATA_FORMAT_XML);

	long nRet = 0;

	if (!strcmp(pszRetType,MQTT_SYSSTATE_TYPE_REPLY))
	{
		nRet = Process_SysState_Reply(oSysState);
	}
	else if (!strcmp(pszRetType,MQTT_SYSSTATE_TYPE_EVENT))
	{//ppszCmdID����ΪEventID

		if (!strcmp(pszCmdID,RUNPROCEDURE_EVENT_CommFinish))
		{
			nRet = Process_SysState_Event_CommFinish(oSysState);
		}
		else if (!strcmp(pszCmdID,RUNPROCEDURE_EVENT_CommError))
		{
			nRet = Process_SysState_Event_CommError(oSysState);
		}
		else if (!strcmp(pszCmdID,_T("DeviceClosed")))
		{
			nRet = Process_SysState_Event_DeviceClosed(oSysState);
		}
		else
		{
			nRet = Process_SysState_Event_CommOverTime(oSysState);
		}
	}
	else if (!strcmp(pszCmdID, STT_CMD_TYPE_IOT_UpdateDataset))
	{
		nRet = Process_SysState_UpdateDataset(oSysState);
	}

	return nRet;
}

long CIotEngineProtocolClient::Process_SysState_Reply(CSttSysState &oSysState)
{
	if (oSysState.m_strID != m_strCurCmd)
	{//�����ڴ�������
		return 0;
	}

	long nCmdExecState = oSysState.Get_ExecStatus();
	if (Stt_Is_ExecStatus_Ack(nCmdExecState))
	{//ACK
		return nCmdExecState;
	}

	if (oSysState.m_strID == STT_CMD_TYPE_IOT_CreateDevice)
	{
		nCmdExecState = Process_SysState_CreateDevice(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_IOT_RunProcedure)
	{
		nCmdExecState = Process_SysState_RunProcedure(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_IOT_CloseDevice)
	{
		nCmdExecState = Process_SysState_CloseDevice(oSysState);
	}

	if (Stt_Is_ExecStatus_Timeout(nCmdExecState))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("----[%s]ִ�г�ʱ"),oSysState.m_strID);
	}
	else if (Stt_Is_ExecStatus_Failure(nCmdExecState))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("----[%s]ִ��ʧ��"),oSysState.m_strID);
	}

	return nCmdExecState;
}

void CIotEngineProtocolClient::InitTestState()
{
	m_oXCommSvrWnd.KillTimer(1);
	m_nTestState = IOT_TEST_STATE_IDLE;
	m_strCurCmd = _T("");
}

long CIotEngineProtocolClient::Process_SysState_CreateDevice(CSttSysState &oSysState)
{
	long nCmdExecState = oSysState.Get_ExecStatus();

	InitTestState();

	//����Ϣ���Զ�����
	if (Stt_Is_ExecStatus_Success(nCmdExecState))
	{//ִ�гɹ�
		PostDeviceSysMessage(0, engineConnectDeviceSuccessful);
		
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("----CreateDeviceִ�гɹ�"));
	}
	else
	{
		PostDeviceSysMessage(0, engineConnectDeviceFailed);
	}
	
	return nCmdExecState;
}

long CIotEngineProtocolClient::Process_SysState_RunProcedure(CSttSysState &oSysState)
{
	long nCmdExecState = oSysState.Get_ExecStatus();

	m_oXCommSvrWnd.KillTimer(1);

	//����Ϣ���Զ�����
	if (Stt_Is_ExecStatus_Success(nCmdExecState))
	{//ִ�гɹ�
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("----RunProcedureִ�гɹ����ȴ��������"));
		m_nTestState = IOT_TEST_STATE_WAITRESULT;
	}
	else
	{
		InitTestState();

		//����Ϣ
		PostDeviceCommCmdMessage(0, engineCommError);
	}

	return nCmdExecState;
}

long CIotEngineProtocolClient::Process_SysState_CloseDevice(CSttSysState &oSysState)
{
	long nCmdExecState = oSysState.Get_ExecStatus();
	m_oXCommSvrWnd.KillTimer(1);

	//����Ϣ���Զ�����
	if (Stt_Is_ExecStatus_Success(nCmdExecState))
	{//ִ�гɹ�
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("----CloseDeviceִ�гɹ����ȴ��������"));
		m_nTestState = IOT_TEST_STATE_WAITRESULT;
	}
	else
	{
		InitTestState();
	}

	return nCmdExecState;
}

long CIotEngineProtocolClient::Process_SysState_Event_CommFinish(CSttSysState &oSysState)
{//�������ݼ���������Ϣ���Զ����ԣ��������״̬
	CDvmDataset *pDataset = oSysState.GetDataset();
	if(pDataset == NULL)
		pDataset = oSysState.GetDatasetGroup();
	if (m_pCurDataset != NULL)
	{
		if(NeedClearDataset(m_pCurDataset->m_strID))
		{
			m_pCurDataset->DeleteAll();
		}
		m_pCurDataset->UpdateDataValue(pDataset, TRUE);
	}

	InitTestState();

	//����Ϣ
	PostDeviceCommCmdMessage(0, engineCommFinish);

	return 0;
}

long CIotEngineProtocolClient::Process_SysState_Event_CommError(CSttSysState &oSysState)
{
	InitTestState();

	//����Ϣ
	PostDeviceCommCmdMessage(0, engineCommError);

	return 0;
}

long CIotEngineProtocolClient::Process_SysState_Event_DeviceClosed(CSttSysState &oSysState)
{
	InitTestState();

	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("----CloseDeviceִ�гɹ�"));

	return 0;
}

long CIotEngineProtocolClient::Process_SysState_Event_CommOverTime(CSttSysState &oSysState)
{
	InitTestState();

	//����Ϣ
	PostDeviceCommCmdMessage(0, engineCommError);

	return 0;
}

long CIotEngineProtocolClient::Process_SysState_UpdateDataset(CSttSysState &oSysState)
{
	//yzj 2021-10-5
	CDvmDataset *pDataset = oSysState.GetDataset();
	if(pDataset == NULL)
		pDataset = oSysState.GetDatasetGroup();
	CDvmDataset *pUpdateDataset = m_oDvmDevice.FindDataset(pDataset->m_strID);
	if(pUpdateDataset)
	{
		pUpdateDataset->UpdateDataValue(pDataset, TRUE);
	}

	return 0;
}

long CIotEngineProtocolClient::GetCmdTimeOverLong()
{
	long nTimeOut = 30000;
	CDvmData *pAttrData = m_oDvmDevice.GetAttr(MODEL_Attr_PkgUpTmInterval);
	if (pAttrData != NULL)
	{
		if (!pAttrData->m_strValue.IsEmpty())
		{
			nTimeOut = CString_To_long(pAttrData->m_strValue);
		}
	}

	return nTimeOut;
}

long CIotEngineProtocolClient::SendCmd(CSttCmdBase *pCmd)
{
	long nRet = Send(pCmd);

	if (nRet > 0)
	{//���ͳɹ�
		m_nTestState = IOT_TEST_STATE_TESTING;
		m_strCurCmd = pCmd->m_strID;
		m_oXCommSvrWnd.SetTimer(1,GetCmdTimeOverLong(),NULL);
	}

	return nRet;//�������ݳ���
}

BOOL CIotEngineProtocolClient::IsConnectSuccessful()
{
	return m_bConnected;
}

BOOL CIotEngineProtocolClient::ConnectDevice()
{
	if (IsConnectSuccessful())
	{
		return TRUE;
	}

	return Init(m_strIP,m_nPort);
}

void CIotEngineProtocolClient::AttachSystemWndMsg(long hWnd, long nMsgID)
{
	m_hSysMsgWnd = hWnd;
	m_nSysMsg = nMsgID;
}

void CIotEngineProtocolClient::RegisterProcedureWndMsg(const CString &strProcedureID, long hWnd, long nMsgID)
{
	m_hMsgWnd = hWnd;
	m_nMsg = nMsgID;
}

void CIotEngineProtocolClient::UnRegisterProcedureWndMsg(const CString &strProcedureID, long hWnd, long nMsgID)
{
	m_hMsgWnd = NULL;
	m_nMsg = 0;
}

long CIotEngineProtocolClient::CreateDevice(const CString &strCmmConfig)
{
	CDataGroup oGroup;
	//�����ϰ汾
	if(strCmmConfig.Find(_T("<dataset")) >= 0)
	{
		CDvmDataset oDataset;
		BSTR bstrText = strCmmConfig.AllocSysString();
		oDataset.SetXml(bstrText, CDataMngrXmlRWKeys::g_pXmlKeys);
		SysFreeString(bstrText);// �����ͷ�

		oGroup.AppendEx(oDataset);
		oDataset.RemoveAll();	
	}
	else
	{
		oGroup.SetDvmDataXml(strCmmConfig);
	}

	CSttIotCmd oIotCmd;
	oIotCmd.m_strID = STT_CMD_TYPE_IOT_CreateDevice;
	oIotCmd.AddNewParasData(STT_CMD_PARA_DeviceSN,m_strDeviceID);
	oIotCmd.AddNewParasData(XPARA_ID_DVMFILE,m_strDvmFile);
	oIotCmd.AddNewParasData(XPARA_ID_PPXMLFILE,m_strPpxmlFile);
	oIotCmd.AddNewParas(&oGroup);

	long nRet = SendCmd(&oIotCmd);

	if (nRet <= 0)
	{
		PostDeviceSysMessage(0,engineConnectDeviceFailed);
	}

	return nRet;
}

long CIotEngineProtocolClient::RunProcedure(const CString &strProcedureID
		, const CString &strDatasetPath,CExBaseList &listDataInterface,const CString &strRecordMode)
{
	CString strDsID = GetIDFromPath(strDatasetPath);
	if (strDsID == MODEL_DEVICE_ID_Attr)
	{//��������
		m_pCurDataset = m_oDvmDevice.GetDeviceAttrs();
	}
	else
	{
		m_pCurDataset = m_oDvmDevice.FindDataset(strDsID);
	}

	CSttIotCmd oIotCmd;
	oIotCmd.m_strID = STT_CMD_TYPE_IOT_RunProcedure;
	oIotCmd.AddNewParasData(STT_CMD_PARA_DeviceSN,m_strDeviceID);
	oIotCmd.AddNewParasData(STT_CMD_PARA_RecordMode,strRecordMode);

	CDvmData *pDataInterface = oIotCmd.AddNewParasData(STT_CMD_PARA_ProcedureID,strProcedureID);
	pDataInterface->AppendCloneEx(listDataInterface);

	//2021-9-28 yzj ����topoIDʱû�ж�Ӧ�����ݼ�
	if(m_pCurDataset)
	{
		m_pCurDataset->m_strID = strDatasetPath;
		oIotCmd.AddNewParas(m_pCurDataset);
		m_pCurDataset->m_strID = strDsID;
	}
	
	long nRet = SendCmd(&oIotCmd);

	if (nRet <= 0)
	{
		PostDeviceCommCmdMessage(0, engineCommError);
	}

	return nRet;	
}

long CIotEngineProtocolClient::GetDataset(const CString &strDatasetPath)
{
	return 0;
}

long CIotEngineProtocolClient::ConfigDevice(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile)
{
	return 0;
}

long CIotEngineProtocolClient::CloseDevice()
{
	CSttIotCmd oIotCmd;
	oIotCmd.m_strID = STT_CMD_TYPE_IOT_CloseDevice;
	oIotCmd.AddNewParasData(STT_CMD_PARA_DeviceSN,m_strDeviceID);

	return SendCmd(&oIotCmd);
}

BOOL CIotEngineProtocolClient::InitParas(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile)
{
	if (strDeviceID.IsEmpty())
	{
		return FALSE;
	}
	if (!IsFileExist(strDvmFile))
	{
		return FALSE;
	}

	if (!m_oDvmDevice.OpenXmlFile(strDvmFile,CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��ģ���ļ���%s��ʧ�ܡ�"), strDvmFile);
		return FALSE;
	}

	m_strDeviceID = strDeviceID;
	m_strDvmFile = strDvmFile;
	m_strPpxmlFile = strPpxmlFile;

	return TRUE;
}

CDvmDataset *CIotEngineProtocolClient::GetDeviceAttrs()
{
	return m_oDvmDevice.GetDeviceAttrs();
}

CDvmDataset *CIotEngineProtocolClient::FindDataset(const CString &strDsID)
{
	return m_oDvmDevice.FindDataset(strDsID);
}

//������Щ��̬���������ݼ���ÿ��ִ��ָ���Ҫ����������ݼ�
BOOL CIotEngineProtocolClient::NeedClearDataset(const CString& strDatasetID)
{
	if(strDatasetID == _T("ContainerCfg")
		|| strDatasetID == _T("ContainerState")
		|| strDatasetID == _T("AppResourcesRead")
		|| strDatasetID == _T("AppState")
		|| strDatasetID == _T("jsonpackage")
		|| strDatasetID == _T("httppackage")
		|| strDatasetID == _T("Linkpackage")
		|| strDatasetID == _T("ReadCmdRslt"))
	{
		return TRUE;
	}
	return FALSE;
}

void CIotEngineProtocolClient::PostDeviceSysMessage(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = (HWND)m_hSysMsgWnd;

	if (!::IsWindow((hWnd)))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("���Ͳ��������Ϣ ��%08x�� ���Ǵ��ڡ�Sys��"), m_hSysMsgWnd);
		return;
	}

	::PostMessage(hWnd, m_nSysMsg, wParam, lParam);
}

void CIotEngineProtocolClient::PostDeviceCommCmdMessage(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = (HWND)m_hMsgWnd;

	if (!::IsWindow((hWnd)))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("���Ͳ��������Ϣ ��%08x�� ���Ǵ��ڡ�CommCmd��"), m_hMsgWnd);
		return;
	}

	::PostMessage(hWnd, m_nMsg, wParam, lParam);
}