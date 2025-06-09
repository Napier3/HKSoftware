#include "stdafx.h"
#include "IotTestCtrl.h"

CIotTestCtrl::CIotTestCtrl():CIotTestCtrlBase()
{
	m_strFormat = MQTT_DATA_FORMAT_JSON;
}

CIotTestCtrl::~CIotTestCtrl()
{

}

void CIotTestCtrl::OnProcessOverTime()
{
	if ((m_strCurrCmd == STT_CMD_TYPE_TEST_QueryDeviceState)
		|| (m_strCurrCmd == STT_CMD_TYPE_TEST_SendSensorModel)
		|| (m_strCurrCmd == STT_CMD_TYPE_TEST_GetTestMacros)
		|| (m_strCurrCmd == STT_CMD_TYPE_TEST_GetTopo))
	{
		ClearTestState();
	}
	else
	{
		CIotTestCtrlBase::OnProcessOverTime();
	}
}

void CIotTestCtrl::SetIotDevice(const CString &strDeviceSN,long nDeviceType)
{
	m_oSttIotDevices.DeleteAll();

	m_strDeviceSN = strDeviceSN;
	m_nDeviceType = nDeviceType;

	CSttIotDevice *pDevice = new CSttIotDevice;
	pDevice->m_strID = strDeviceSN;
	pDevice->m_nDevType = nDeviceType;
	m_oSttIotDevices.AddNewChild(pDevice);
}

/***************************
{
	"mid":2, "id":"Reply","time":"2021-3-24 10:10:10",
	"paras":{
		"data":[
			{"name":" ", "id":"status", "value":"0"},
			{"name":" ", "id":"curCase", "value":" MacroID "}
		]
	}
}
***************************/
long CIotTestCtrl::Process_SysState_Reply_QueryDeviceState(CSttSysState &oSysState)
{
	CString strCurCase = _T("");
	long nCmdExecState = oSysState.GetParaValue(_T("status"), 0);

	ClearTestState();

	if (nCmdExecState == 0)
	{//ִ�гɹ�
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("----QueryDeviceStateִ�гɹ�:�����ǿ���"));
	}
	else
	{
		oSysState.GetParasDataValueByID(_T("curCase"),strCurCase);
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("----QueryDeviceStateִ�гɹ�:������æ[%d],[%s]"),nCmdExecState,strCurCase);
	}

	return 1;
}

/***************************
{
	"mid":2,"id":"Reply","time":"2021-3-24 10:10:10",
	"paras":{
		"data":[
			{"name":"","id":"status","value":"0"}
		]
	}
}
***************************/
long CIotTestCtrl::Process_SysState_Reply_SendSensorModel(CSttSysState &oSysState)
{
	CString strCurCase = _T("");
	long nCmdExecState = oSysState.GetParaValue(_T("status"), 0);

	ClearTestState();

	if (nCmdExecState == 0)
	{//ִ�гɹ�
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("----SendSensorModelִ�гɹ�"));
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("----SendSensorModelִ��ʧ��[%d]"),nCmdExecState);
	}

	return 1;
}

/***************************************
������Ӧ�𣺲�����SN/JSON/TestState/GetTestMacros/Reply
{
	"mid":2, "id":"Reply", "time":"2021-3-24 10:10:10",
	"macro":[
		{"name":"����1", "id":"MacroID1","priority":1 , "type":"0",
			"paras" :{
				"data":[
					{"name":"����1", "id":" dataID1", "unit":"", "index":1, "data-type":"1", "value":"0"},
					{"name":"����2", "id":" dataID2", "unit":"", "index":1, "data-type":"1", "value":"1"}
				]
			},
			"results" :{
				"data":[
					{"name":"����ж�", "id":"RsltJdg", "unit":"", "index":1, "data-type":"1", "value":"0"},
					{"name":"�������", "id":"RsltDsc", "unit":"", "index":1, "data-type":"1", "value":""}
				]
			}
		},
		{"name":"����2", "id":"MacroID2","priority":1 , "type":"0",
			"paras" :{
				"data":[
					{"name":"����1", "id":" dataID1", "unit":"", "index":1, "data-type":"1", "value":"0"},
					{"name":"����2", "id":" dataID2", "unit":"", "index":1, "data-type":"1", "value":"1"}
				]
			},
			"results" :{
				"data":[
					{"name":"����ж�", "id":"RsltJdg", "unit":"", "index":1, "data-type":"1", "value":"0"},
					{"name":"�������", "id":"RsltDsc", "unit":"", "index":1, "data-type":"1", "value":""}
				]
			}
		}
	]
}
***************************************/
long CIotTestCtrl::Process_SysState_Reply_GetTestMacros(CSttSysState &oSysState)
{
	FreeTestMacros();

	m_pTestMacros = new CTestMacros;

	POS pos = oSysState.GetHeadPosition();
	CSttMacro *pSttMacro = NULL;

	while(pos != NULL)
	{
		pSttMacro = (CSttMacro *)oSysState.GetNext(pos);
		if (pSttMacro->GetClassID() != STTCMDCLASSID_CSTTMACRO)
		{
			continue;
		}

		m_pTestMacros->AddNewChild(GenerateMacroParas(pSttMacro));
	}

	//����Ϣˢ�½���
	PostUpdateMacroMsg(IOTVM_MACRO_MSG_TYPE_MACROS);

	ClearTestState();

	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("----GetTestMacrosִ�гɹ�"));

	return 1;
}

/****************************
{
"mid":2, "id":"Reply", "time":"2021-3-24 10:10:10",
	"topo":{
		"node":[
			{"SN":"���", "type":2, "cat":2, "parent":"ParentDeviceSN", "state":0},
			{"SN":"DeviceSN", "type":2, "cat":2, "parent":"ParentDeviceSN", "state":0},
			{"SN":"DeviceSN", "type":2, "cat":2, "parent":"ParentDeviceSN", "state":0},
			{"SN":"DeviceSN", "type":2, "cat":2, "parent":"ParentDeviceSN", "state":0}
		]
	}
}
*****************************/
long CIotTestCtrl::Process_SysState_Reply_GetTopo(CSttSysState &oSysState)
{
	CSttIotTopo *pTopo = oSysState.GetSttIotTopo();
	CString strTopo;
	pTopo->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys,strTopo);

	ClearTestState();

	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("----GetTopoִ�гɹ�"));

	//��ӡtopo����
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������ݣ�\n\r%s"),strTopo);
	return 1;
}

/*******************************
{
"mid":2, "id":"Reply","time":"2021-3-24 10:10:10",
	"paras":{
		"data":[
			{"name":" ", "id":"status", "value":"0"}
		]
	}
}
*******************************/
long CIotTestCtrl::Process_SysState_Reply_StartTest(CSttSysState &oSysState)
{
	//shaolei 20211023
	return CIotTestCtrlBase::Process_SysState_Reply_StartTest(oSysState);

	long nCmdExecState = oSysState.GetParaValue(_T("status"), 0);
	KillXTimer(1);

	if (nCmdExecState == 0)
	{//ִ�гɹ�,�ȴ�Finish�¼�
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("----StartTestִ�гɹ����ȴ��������"));
		m_nTestState = IOT_TEST_STATE_WAITRESULT;
		return nCmdExecState;
	}
	else
	{//ʧ��
		PostTestWndMsg(MTMSG_CommError,0);

		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("----StartTestִ��ʧ��[%d]"),nCmdExecState);
		ClearTestState();
	}

	return nCmdExecState;
}

long CIotTestCtrl::Process_SysState_Reply_StopTest(CSttSysState &oSysState)
{
	//shaolei 20211023
	return CIotTestCtrlBase::Process_SysState_Reply_StopTest(oSysState);

	long nCmdExecState = oSysState.GetParaValue(_T("status"), 0);
	KillXTimer(1);

	ClearTestState();

	if (nCmdExecState == 0)
	{//ִ�гɹ�
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("----StopTestִ�гɹ�"));
	}
	else
	{//ʧ��
		PostTestWndMsg(MTMSG_CommError,0);

		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("----StopTestִ��ʧ��[%d]"),nCmdExecState);
	}

	return nCmdExecState;
}


long CIotTestCtrl::Process_SysState_Event_OnTestStarted(CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Event_OnTestStarted"));
	return 1;
}

long CIotTestCtrl::Process_SysState_Event_OnTestStoped(CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Event_OnTestStoped"));
	return 1;
}

long CIotTestCtrl::Process_SysState_Event_OnTestFinished(CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Event_OnTestFinished"));
	if (m_pTestMacro == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Event_OnTestFinished,m_pTestMacro==NULL"));
		return 0;
	}

	CSttMacro *pMacro = oSysState.GetSttMacro();
	CSttMsgs *pMsgs = oSysState.GetSttMsgs();

	if (pMacro->m_strID != m_pTestMacro->m_strID)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Event_OnTestFinished,m_pTestMacro[%s]!=pMacro[%s]")
			,m_pTestMacro->m_strID,pMacro->m_strID);
		return 0;
	}

	//SttResult����TestMacro�ڵ�
	UpdateMacroResultBySttMacroResult(m_pTestMacro,pMacro);

	//msgs��Ϊ�������̱���

	ClearTestState();

	//����Ϣˢ�½���
	PostUpdateMacroMsg(IOTVM_MACRO_MSG_TYPE_MACRO);

	//����Ϣ��com����
	PostTestWndMsg(MTMSG_TestFinished,0);

	//��ӡmsgs����
	CString strMsgs;
	pMsgs->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys,strMsgs);
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("���̽������ݣ�\r\n%s"),strMsgs);

	return 1;
}

long CIotTestCtrl::Test_QueryDeviceState()
{
	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_QueryDeviceState;

	return PublicCmdEx(&oTestCmd);
}

long CIotTestCtrl::Test_SendSensorModel(const CString &strSensorType
										,const CString &strSensorTypeID,CDataGroup *pParas)
{
	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_SendSensorModel;
	oTestCmd.AddNewParasData(_T("SensorType"), strSensorType);
	oTestCmd.AddNewParasData(_T("SensorTypeID"), strSensorTypeID);
	oTestCmd.AddNewParas(pParas);

	return PublicCmdEx(&oTestCmd);
}

long CIotTestCtrl::Test_GetTestMacros()
{
	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_GetTestMacros;
	oTestCmd.AddNewParasData(_T("devType"), m_nDeviceType);

	return PublicCmdEx(&oTestCmd);
}

long CIotTestCtrl::Test_GetTopo()
{
	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_GetTopo;

	return PublicCmdEx(&oTestCmd);
}

long CIotTestCtrl::Test_StartTest()
{
	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_StartTest;

	CSttMacro *pSttMacro = GenerateSttMacroParas(m_pTestMacro);
	CSttIotDevices *pDevices = oTestCmd.GetSttIotDevices();
	oTestCmd.AddNewChild(pSttMacro);
	pDevices->AppendClone(m_oSttIotDevices);

	//�����еĲ���������λĬ��ֵ
	m_pTestMacro->SetParasToDefault();

	return PublicCmdEx(&oTestCmd);
}

long CIotTestCtrl::Test_StopTest()
{
	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_StopTest;

	CSttMacro *pSttMacro = oTestCmd.GetSttMacro();
	pSttMacro->m_strID = m_pTestMacro->m_strID;
	CSttIotDevices *pDevices = oTestCmd.GetSttIotDevices();
	pDevices->AppendClone(m_oSttIotDevices);

	return PublicCmdEx(&oTestCmd);
}