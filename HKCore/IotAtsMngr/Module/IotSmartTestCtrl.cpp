#include "stdafx.h"
#include "IotSmartTestCtrl.h"
#include "SttMqttClientTool.h"



CIotSmartTestCtrl::CIotSmartTestCtrl()
{
	m_pszXmlBuffer = NULL;
	m_nXmlBufferLen = 0;
	SetXmlBufferLen(1048576); //1M

	m_oTestAppMngr = NULL;
}

CIotSmartTestCtrl::~CIotSmartTestCtrl()
{
	if (m_oTestAppMngr != NULL)
	{
		try
		{
			m_oTestAppMngr.CloseTest(m_strID);
		}
		catch (...)
		{

		}
		m_oTestAppMngr = NULL;
	}

	if (m_pszXmlBuffer != NULL)
	{
		delete m_pszXmlBuffer;
		m_pszXmlBuffer = NULL;
	}
}

void CIotSmartTestCtrl::SetXmlBufferLen(long nLen)
{
	if (nLen <= m_nXmlBufferLen)
	{
		return;
	}

	if (m_pszXmlBuffer != NULL)
	{
		delete m_pszXmlBuffer;
		m_pszXmlBuffer = NULL;
	}

	m_pszXmlBuffer = new char [nLen+10];
	m_nXmlBufferLen = nLen;
}

void CIotSmartTestCtrl::OnXTimer(DWORD dwTimerID)
{//���ʱ�����߼�

}

void CIotSmartTestCtrl::PraseBuf2CmdObject(CSttCmdBase *pCmdBase,char *pBuf,long nLen)
{
	if (m_strFormat == MQTT_DATA_FORMAT_JSON)
	{
		pCmdBase->PraseCmdBuf(pBuf,nLen,NULL,MQTT_DATA_FORMAT_JSON);
	}
	else
	{//XML
		SetXmlBufferLen(nLen * 2);
		pCmdBase->PraseCmdBuf(pBuf,nLen,m_pszXmlBuffer,MQTT_DATA_FORMAT_XML);
	}
}

/************************
�Զ��������⣺
"����̨SN/XML/AtsCmd/+";
"����̨SN/����װ��SN/XML/AtsCmd/FinishInputData";
"����̨SN/����װ��SN/XML/AtsState/InputData/Reply"
**************************/
void CIotSmartTestCtrl::OnMqttMsgRecieve(CStringTokenizer &oToken,char *pBuf,long nLen)
{
	long nPathCnt = oToken.GetStringsCount();
	m_strCmd = oToken.GetToken(nPathCnt-1);
	long nRet = 0;
	CSttAtsCmd oAtsCmd;

	if (m_strCmd == STT_CMD_TYPE_ATS_FinishInputData)
	{//  ����̨SN/����װ��SN/XML/AtsCmd/FinishInputData
		m_strDeviceSN = oToken.GetToken(1);
		m_strFormat = oToken.GetToken(2);
		PraseBuf2CmdObject(&oAtsCmd,pBuf,nLen);

		// ����̨SN/����װ��SN/XML/AtsState/FinishInputData/Reply
		m_strReplyTopic.Format(_T("/%s/%s/%s/AtsState/%s/Reply"),m_strID,m_strDeviceSN,m_strFormat,m_strCmd);
		long nRet = ReturnSysState(m_strReplyTopic,m_strFormat,&oAtsCmd,STT_CMD_ExecStatus_SUCCESS);
		if (nRet != 0)
		{
			return;
		}

		Process_Cmd_Ats_FinishInputData(oAtsCmd);
	}
	else if (m_strCmd == _T("Reply"))
	{// ����̨SN/����װ��SN/XML/AtsState/InputData/Reply
		CSttSysState oSysState;
		m_strDeviceSN = oToken.GetToken(1);
		m_strFormat = oToken.GetToken(2);
		PraseBuf2CmdObject(&oSysState,pBuf,nLen);


	}
	else
	{// ����̨SN/XML/AtsCmd/+
		m_strFormat = oToken.GetToken(1);
		PraseBuf2CmdObject(&oAtsCmd,pBuf,nLen);

		// ����̨SN/XML/AtsState/��������/Reply
		m_strReplyTopic.Format(_T("/%s/%s/AtsState/%s/Reply"),m_strID,m_strFormat,m_strCmd);
		long nRet = ReturnSysState(m_strReplyTopic,m_strFormat,&oAtsCmd,STT_CMD_ExecStatus_ACK);
		if (nRet != 0)
		{
			return;
		}

		if (m_strCmd == STT_CMD_TYPE_ATS_CreateTest)
		{//  ����̨SN/XML/AtsCmd/CreateTest	
			Process_Cmd_Ats_CreateTest(oAtsCmd);	
		}
		else if (m_strCmd == STT_CMD_TYPE_ATS_StartTest)
		{//  ����̨SN/XML/AtsCmd/StartTest
			Process_Cmd_Ats_BeginTest(oAtsCmd);
		}
		else if (m_strCmd == STT_CMD_TYPE_ATS_StopTest)
		{//  ����̨SN/XML/AtsCmd/StopTest
			Process_Cmd_Ats_StopTest(oAtsCmd);
		}
		else if (m_strCmd == STT_CMD_TYPE_ATS_CloseTest)
		{//  ����̨SN/XML/AtsCmd/CloseTest
			Process_Cmd_Ats_CloseTest(oAtsCmd);
		}
		else if (m_strCmd == STT_CMD_TYPE_ATS_TestItem)
		{//  ����̨SN/XML/AtsCmd/TestItem
			Process_Cmd_Ats_TestItem(oAtsCmd);
		}
		else if (m_strCmd == STT_CMD_TYPE_ATS_TestFrom)
		{//  ����̨SN/XML/AtsCmd/TestFrom
			Process_Cmd_Ats_TestFrom(oAtsCmd);
		}
		else if (m_strCmd == STT_CMD_TYPE_ATS_TestAllFailedItems)
		{//  ����̨SN/XML/AtsCmd/TestAllFailedItems
			Process_Cmd_Ats_TestAllFailedItems(oAtsCmd);
		}
		else if (m_strCmd == STT_CMD_TYPE_ATS_SetItemState)
		{//  ����̨SN/XML/AtsCmd/SetItemState
			Process_Cmd_Ats_SetItemState(oAtsCmd);
		}
		else if (m_strCmd == STT_CMD_TYPE_ATS_ConfigDevice)
		{//  ����̨SN/XML/AtsCmd/ConfigDevice
			Process_Cmd_Ats_ConfigDevice(oAtsCmd);
		}
		else if (m_strCmd == STT_CMD_TYPE_ATS_ConnectDevice)
		{//  ����̨SN/XML/AtsCmd/ConnectDevice
			Process_Cmd_Ats_ConnectDevice(oAtsCmd);
		}
		else if (m_strCmd == STT_CMD_TYPE_ATS_CloseDevice)
		{//  ����̨SN/XML/AtsCmd/CloseDevice
			Process_Cmd_Ats_CloseDevice(oAtsCmd);
		}
		else if (m_strCmd == STT_CMD_TYPE_ATS_ConfigEngine)
		{//  ����̨SN/XML/AtsCmd/ConfigEngine
			Process_Cmd_Ats_ConfigEngine(oAtsCmd);
		}
		else if (m_strCmd == STT_CMD_TYPE_ATS_GetDataset)
		{//  ����̨SN/XML/AtsCmd/GetDataset
			Process_Cmd_Ats_GetDataset(oAtsCmd);
		}
		else if (m_strCmd == STT_CMD_TYPE_ATS_SetDataset)
		{//  ����̨SN/XML/AtsCmd/SetDataset
			Process_Cmd_Ats_SetDataset(oAtsCmd);
		}
		else if (m_strCmd == STT_CMD_TYPE_ATS_RunProcedure)
		{//  ����̨SN/XML/AtsCmd/RunProcedure
			Process_Cmd_Ats_RunProcedure(oAtsCmd);
		}
		else if (m_strCmd == STT_CMD_TYPE_ATS_QueryAtsFile)
		{//  ����̨SN/XML/AtsCmd/QueryAtsFile
			Process_Cmd_Ats_QueryAtsFile(oAtsCmd);
		}
// 		else if (m_strCmd == STT_CMD_TYPE_ATS_ExportReport)
// 		{//  ����̨SN/XML/AtsCmd/ExportReport
// 			Process_Cmd_Ats_ExportReport(oAtsCmd);
// 		}
// 		else if (m_strCmd == STT_CMD_TYPE_ATS_QueryItems)
// 		{//  ����̨SN/XML/AtsCmd/QueryItems
// 			Process_Cmd_Ats_QueryItems(oAtsCmd);
// 		}
// 		else if (m_strCmd == STT_CMD_TYPE_ATS_SetItemsReport)
// 		{//  ����̨SN/XML/AtsCmd/SetItemsReport
// 			Process_Cmd_Ats_SetItemsReport(oAtsCmd);
// 		}
// 		else if (m_strCmd == STT_CMD_TYPE_ATS_ConfigTest)
// 		{//  ����̨SN/XML/AtsCmd/ConfigTest
// 			Process_Cmd_Ats_ConfigTest(oAtsCmd);
// 		}
	}
}

//��������׼��������������ģ�塢ģ�ͺ͹�Լ�ļ��Ƿ���ڣ���������ӷ���������
BOOL CIotSmartTestCtrl::CheckCreateTest(CSttAtsCmd &oAtsCmd)
{
	CString strGbxmlFile,strDvmFile,strPpxmlFile,strDocFile;
	oAtsCmd.GetParasDataValueByID(XPARA_ID_GBXMLFILE, strGbxmlFile);
	oAtsCmd.GetParasDataValueByID(XPARA_ID_DVMFILE, strDvmFile);
	oAtsCmd.GetParasDataValueByID(XPARA_ID_PPXMLFILE, strPpxmlFile);

	if (!IsFileExist(strGbxmlFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ģ���ļ�[%s]�����ڣ�"),strGbxmlFile);
		return FALSE;
	}
	if (!IsFileExist(strDvmFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ģ���ļ�[%s]�����ڣ�"),strDvmFile);
		return FALSE;
	}
	if (!IsFileExist(strPpxmlFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�����ļ�[%s]�����ڣ�"),strPpxmlFile);
		return FALSE;
	}

	strDocFile = ParseFileName(strGbxmlFile);
	strDocFile.AppendFormat(_T(".doc"));
	if (!IsFileExist(strDocFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("����ģ���ļ�[%s]�����ڣ�"),strDocFile);
		return FALSE;
	}

	CSttParas *pParas = oAtsCmd.GetSttParas();
	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID("devices");
	if (pDevices == NULL)
	{
		return FALSE;
	}

	m_oDevices.DeleteAll();
	m_oDevices.AppendClone(*pDevices);

	return TRUE;
}

BOOL CIotSmartTestCtrl::GetDeviceSNByIndex(long nDeviceIndex,CString &strDeviceSN)
{
	long nDeviceCnt = m_oDevices.GetCount();
	if (nDeviceCnt <= nDeviceIndex + 1)
	{
		return FALSE;
	}

	CDataGroup *pDevice = (CDataGroup *)m_oDevices.GetAtIndex(nDeviceIndex);
	return pDevice->GetDataValue(_T("SN"), strDeviceSN);
}

BOOL CIotSmartTestCtrl::GetDeviceIndexBySN(const CString &strDeviceSN,long &nDeviceIndex)
{
	if (strDeviceSN.IsEmpty())
	{
		return FALSE;
	}

	POS pos = m_oDevices.GetHeadPosition();
	CDataGroup *pDevice = NULL;
	CString strSN = _T("");
	long nIndex = 0;

	while(pos != NULL)
	{
		pDevice = (CDataGroup *)m_oDevices.GetNext(pos);

		pDevice->GetDataValue(_T("SN"), strSN);
		if (strSN == strDeviceSN)
		{
			nDeviceIndex = nIndex;
			return TRUE;
		}

		nIndex++;
	}

	return FALSE;
}

SmartTest::CTestAppMngr CIotSmartTestCtrl::GetTestAppMngr()
{
	if (m_oTestAppMngr != NULL)
	{
		return m_oTestAppMngr;
	}

	m_oTestAppMngr.CreateDispatch(_T("SmartTest.TestAppMngr"));
	return m_oTestAppMngr;
}

BOOL CIotSmartTestCtrl::Process_Cmd_Ats_CreateTest(CSttAtsCmd &oAtsCmd)
{
	if (CheckCreateTest(oAtsCmd))
	{
		ReturnSysState(m_strReplyTopic,m_strFormat,&oAtsCmd,STT_CMD_ExecStatus_FAILURE);
		return FALSE;
	}
	
	SmartTest::CTestAppMngr oTestAppMngr = GetTestAppMngr();

	if (oTestAppMngr == NULL)
	{
		ReturnSysState(m_strReplyTopic,m_strFormat,&oAtsCmd,STT_CMD_ExecStatus_FAILURE);
		AfxMessageBox(_T("û��ע��SmartTest"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	//��ô��ȡgbrpt·��
	ReturnSysState(m_strReplyTopic,m_strFormat,&oAtsCmd,STT_CMD_ExecStatus_SUCCESS);

	//���ò���
	CString strParas;
	oAtsCmd.GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strParas);

	try
	{
		m_oTestAppMngr.CreateTest(strParas);
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestCtrl::CreateTest������m_oTestAppMngr.CreateTest(strParas);"));
	}
	catch (...)
	{

	}
	return TRUE;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_BeginTest(CSttAtsCmd &oAtsCmd)
{
	if (m_oTestAppMngr == NULL)
	{
		ReturnSysState(m_strReplyTopic,m_strFormat,&oAtsCmd,STT_CMD_ExecStatus_FAILURE);
		AfxMessageBox(_T("û��ע��SmartTest"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	ReturnSysState(m_strReplyTopic,m_strFormat,&oAtsCmd,STT_CMD_ExecStatus_SUCCESS);

	try
	{
		m_oTestAppMngr.BeginTest(m_strID);

		//  /����̨SN /XML/ AtsState /TestStarted
		CString strEventTopic;
		strEventTopic.Format(_T("/%s/%s/AtsState/%s"),m_strID,m_strFormat,SYS_STATE_EVENT_OnTestStarted);

		CSttSysState oSysState;
		oSysState.m_strID = SYS_STATE_EVENT_OnTestStarted;
		oSysState.SetEvent();
		oSysState.AddNewParasData(STT_CMD_PARA_DeviceIndex,0);

		PublicCmd(strEventTopic,m_strFormat,&oSysState);
	}
	catch (...)
	{

	}
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_StopTest(CSttAtsCmd &oAtsCmd)
{
	ReturnSysState(m_strReplyTopic,m_strFormat,&oAtsCmd,STT_CMD_ExecStatus_SUCCESS);

	try
	{
		m_oTestAppMngr.StopTest(m_strID);
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("       �� CSmartTestCtrl::StopTest������ֹͣ�������"));
	}
	catch (...)
	{

	}
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_CloseTest(CSttAtsCmd &oAtsCmd)
{
	ReturnSysState(m_strReplyTopic,m_strFormat,&oAtsCmd,STT_CMD_ExecStatus_SUCCESS);

	try
	{
		m_oTestAppMngr.CloseTest(m_strID);
	}
	catch (...)
	{

	}
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_TestItem(CSttAtsCmd &oAtsCmd)
{
	try
	{
		//		m_oTestAppMngr.TestPoint(m_strID, nDeviceIndex);
	}
	catch (...)
	{

	}
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_TestFrom(CSttAtsCmd &oAtsCmd)
{
	try
	{
		//		m_oTestAppMngr.TestBelow(m_strID, nDeviceIndex);
	}
	catch (...)
	{

	}
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_TestAllFailedItems(CSttAtsCmd &oAtsCmd)
{
	try
	{
		m_oTestAppMngr.TestAllInlegibleItems(m_strID);
	}
	catch (...)
	{

	}
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_SetItemState(CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_ConfigDevice(CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_ConnectDevice(CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_CloseDevice(CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_ConfigEngine(CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_GetDataset(CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_SetDataset(CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_RunProcedure(CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_QueryAtsFile(CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_FinishInputData(CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_ExportReport(CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_QueryItems(CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_SetItemsReport(CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CIotSmartTestCtrl::Process_Cmd_Ats_ConfigTest(CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CIotSmartTestCtrl::Ats_InputData(const CString &strDeviceID,CDataGroup *pDatas
									  ,CExBaseList *pMsgs,const CString &strFormat)
{
	CSttAtsCmd oAtsCmd(STT_CMD_TYPE_ATS_InputData);

	//  ����̨SN/����װ��SN/XML/AtsCmd/InputData
	CString strTopic;
	strTopic.Format(_T("/%s/%s/%s/AtsCmd/%s"),m_strID,strDeviceID,m_strFormat,STT_CMD_TYPE_ATS_InputData);

	if (pDatas != NULL)
	{
		oAtsCmd.AppendParas2(*pDatas);
	}

	if (pMsgs != NULL)
	{
		oAtsCmd.AppendMsgs(*pMsgs);
	}

	oAtsCmd.Set_Xml_Pkg_With_Name(TRUE);   //2020-12-09  lijunqing  return data with name

	return PublicCmd(strTopic,strFormat,&oAtsCmd);
}

//�¼�����ӿ�
long CIotSmartTestCtrl::TES_OnItemStateChanged(long nDeviceIndex, long nReportIndex, long nItemIndex
							, const CString &strItemID, const CString &strState)
{
	CString strDeviceSN;
	BOOL bRet = GetDeviceSNByIndex(nDeviceIndex,strDeviceSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnItemStateChanged:[%s][%d]:δ�ҵ�װ��SN"),m_strID,nDeviceIndex);
		return 1;
	}

	//  /����̨SN/����װ��SN/XML/ AtsState/ ItemStateChanged
	CString strEventTopic;
	strEventTopic.Format(_T("/%s/%s/%s/AtsState/%s"),m_strID,strDeviceSN,m_strFormat,SYS_STATE_EVENT_OnItemStateChanged);

	CSttSysState oSysState;
	oSysState.m_strID = SYS_STATE_EVENT_OnItemStateChanged;
	oSysState.SetEvent();
	oSysState.AddNewParasData(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
	oSysState.AddNewParasData(STT_CMD_PARA_Test_ID,m_strID);
	oSysState.AddNewParasData(STT_CMD_PARA_ReportIndex,nReportIndex);
	oSysState.AddNewParasData(STT_CMD_PARA_ItemIndex,nItemIndex);
	oSysState.AddNewParasData(STT_CMD_PARA_ItemID,strItemID);
	oSysState.AddNewParasData(STT_CMD_PARA_State,strState);

	PublicCmd(strEventTopic,m_strFormat,&oSysState);
	return 0;
}

long CIotSmartTestCtrl::TES_OnTestFinished(long nDeviceIndex, long nReportIndex)
{
	//  /����̨SN /XML/ AtsState /TestFinished
	CString strEventTopic;
	strEventTopic.Format(_T("/%s/%s/AtsState/%s"),m_strID,m_strFormat,SYS_STATE_EVENT_OnTestFinished);

	CSttSysState oSysState;
	oSysState.m_strID = SYS_STATE_EVENT_OnTestFinished;
	oSysState.SetEvent();
	oSysState.AddNewParasData(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
//	oSysState.AddNewParasData(STT_CMD_PARA_ReportIndex,nReportIndex);

	PublicCmd(strEventTopic,m_strFormat,&oSysState);
	return 0;
}

long CIotSmartTestCtrl::TES_OnTestStoped(long nDeviceIndex, long nReportIndex)
{
	//  /����̨SN /XML/ AtsState /TestStoped
	CString strEventTopic;
	strEventTopic.Format(_T("/%s/%s/AtsState/%s"),m_strID,m_strFormat,SYS_STATE_EVENT_OnTestStoped);

	CSttSysState oSysState;
	oSysState.m_strID = SYS_STATE_EVENT_OnTestStoped;
	oSysState.SetEvent();
	oSysState.AddNewParasData(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
//	oSysState.AddNewParasData(STT_CMD_PARA_ReportIndex,nReportIndex);

	PublicCmd(strEventTopic,m_strFormat,&oSysState);
	return 0;
}

long CIotSmartTestCtrl::TES_OnExportRptFinished(long nDeviceIndex, long nReportIndex)
{
	return 0;
}

long CIotSmartTestCtrl::TES_OnTestAppEvent(const CString &strEvent)
{
	return 0;
}

long CIotSmartTestCtrl::TES_OnEngineEvent(long nDeviceIndex, const CString &strEvent)
{
	
	return 0;
}

long CIotSmartTestCtrl::TES_OnTestCreated()
{
	//  /����̨SN/XML/AtsState/ TestCreated
	return 0;
}

long CIotSmartTestCtrl::TES_OnOpenGbrptFileFailed()
{
	return 0;
}


///////////////////////////////////////////
long PublicCmd(const CString &strTopic,const CString &strFormat,CSttCmdBase *pSttCmd)
{
	ASSERT(pSttCmd != NULL);

	char *pszBuf = NULL;
	long nLen = 0;
	if (strFormat == MQTT_DATA_FORMAT_JSON)
	{
		nLen = pSttCmd->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszBuf,0,_JSON_TYPE_);
		//����Ҫ�ϲ���ͬ�ڵ�����
	}
	else
	{
		nLen = pSttCmd->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszBuf,0);
	}

	if (pszBuf == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("PublicCmd::pszBuf==NULL"));
		return 2;
	}

	CSttMqttClientTool::PublicTopic(strTopic,pszBuf,nLen);
	delete pszBuf;
	return 0;
}

long ReturnSysState(const CString &strTopic,const CString &strFormat,CSttCmdBase *pSttCmd
						, long nCmdExecStatus,CSttCmdData *pRetData)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(pSttCmd);

	if (pRetData != NULL)
	{//���ؽ������
		oSysState.AppendParas(*pRetData);
	}

	oSysState.Set_ExecStatus(nCmdExecStatus);

	return PublicCmd(strTopic,strFormat,&oSysState);
}
