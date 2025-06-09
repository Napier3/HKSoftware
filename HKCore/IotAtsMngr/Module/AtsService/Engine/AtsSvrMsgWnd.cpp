//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AtsSvrService.cpp  CAtsSvrService


#include "stdafx.h"
#include "AtsSvrMsgWnd.h"
#include "../../../../SttStudio/Module/Engine/SttEngineInterface.h"
#include "../../../../Module/XFileHttpClient/XFileHttpClient.h"
#include "../../SttMqttClientEngineConfig.h"

CAtsSvrMsgWnd::CAtsSvrMsgWnd()
{
	m_pAtsService = NULL;
	m_pDestBuffer = new char [4096];
}

CAtsSvrMsgWnd::~CAtsSvrMsgWnd()
{
	delete m_pDestBuffer;
}

void CAtsSvrMsgWnd::CreateAtsSvrMsgWnd(CSttAtsSvrMqttImpBase *pService)
{
	m_pAtsService = pService;

	CreateEx(0, AfxRegisterWndClass(0), _T("_Ats_Svr_Wnd_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);

	//��������ʱ�ӣ��������״̬���������ӷ�����
	SetTimer(ATS_SVR_WATCH_TIMER_ID, 5000, NULL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CreateTestָ�������ز����ļ��Ĵ��룬�ƶ�����CSttSmartTestCom  20230605
/*
<ats-cmd name="" id="CreateTest" testor="">
	<paras>
		<data name="����̨��ʶ" id="TestID" value="����̨SN/"/>
		<data name="����ģ��" id="gbxml-file" value="SZNR-TTU.gbexe"/>
		<data name="����ģ��" id="gbxml-file_s" value="����������"/>    //e-Report/Template
		<data name="����ģ��" id="doc-file_s" value="����������"/>    //e-Report/Template
		�����²��ּ����ϰ汾���ݸ�ʽ��
		<data name="" id="DeviceID" data-type="" value="SZNR-TTU"/>
		<data name="�����ļ�" id="ppxml-file" value="SZNR-TTU.ppxml"/>
		<data name="ģ���ļ�" id="dvm-file" value="SZNR-TTU.xml"/>
		<data name="�����¼�ļ�" id="gbrpt-file" value="SZNR-TTU202012131427"/>
		<data name="����װ������" id="EngineProgID" value="PpEngine"/>
		<group name="" id="comm-config" data-type="" value="">
			<data name="" id="tcp-client" data-type="" value="">
				<value name="" id="local-ip" data-type="" value="192.168.10.10"/>
				<value name="" id="local-port" data-type="" value="20183"/>
				<value name="" id="remote-ip" data-type="" value="192.168.10.101"/>
				<value name="" id="remote-port" data-type="" value="2404"/>
			</data>
		</group>
		�����²���Ϊ���������豸�Լ������豸��Ϣ��
		<group id="devices">
			<group id="device">
				<data id="SN" value="123456789"/>
				<data id="EngineProgID" value="PpEngine"/>
				<data name="�����ļ�" id="ppxml-file" value="SZNR-TTU.ppxml"/>
				<data name="�����ļ�" id="ppxml-file_s" value="���� "/>  //e-Protocol/Template
				<data id="dvm-file" value="SZNR-TTU.xml"/>
				<data id="dvm-file_s" value="���� "/>   //e-Protocol/Library;[�̶���·�����������ԡ��༭ģ�嶼�����·����]
				<data id="remote-ip" value="127.0.0.1"/>
				<data id="remote-port" value="9988"/>
			</group>
			����
		</group>
		<group id="test-apps">
			<group id="test-app">
				<data id="SN" value="123456789"/>
				<data id="EngineProgID" value="IotVm"/>
				<data id="dvm-file" value="MacroTest.xml"/>
				<data id="dvm-file_s" value="���� "/>   //�����ǲ���Ҫ���
				<data id="remote-ip" value="127.0.0.1"/>
				<data id="remote-port" value="9988"/>
			</group>
			����
		</group>
	</paras>
</ats-cmd>
*/
/*
#define XPARA_ID_GBXMLFILE_S  _T("gbxml-file_s")
#define XPARA_ID_DVMFILE_S    _T("dvm-file_s")
#define XPARA_ID_PPXMLFILE_S   _T("ppxml-file_s")
#define XPARA_ID_DOCRPTFILE_S  _T("doc-file_s")
*/
/*
BOOL CAtsSvrMsgWnd::DownLoadAllFiles(CSttAtsCmd *pAtsCmd)
{
	CString strHttpUrlHead,strUrl; 
	CSttMqttClientEngineConfig::GetHttpUrlHead(strHttpUrlHead);
	CString strFile, strFile_s, strRootPath;
	CSttParas *pParas = (CSttParas *)pAtsCmd->GetSttParas();
	CString strFileDownLoad;
	BOOL bRet1 = TRUE;
	BOOL bRet2 = TRUE;
	strRootPath = _P_GetInstallPath();
	strRootPath += _T("e-Report\\Template\\");

	//���ز���ģ���ļ�
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE, strFile);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE_S, strFile_s);
	
	if (strFile_s.IsEmpty())
	{
		//����ģ���ļ��Ǳ�����������ڣ�ֱ�ӷ�������ʧ��
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("����ģ���ļ���%s��Ϊ�գ�����ʧ�ܣ�"), strFile);
		bRet1 = FALSE;
	}
	else
	{
		strFileDownLoad = strRootPath + strFile;
		strUrl = strHttpUrlHead + strFile_s;

		if (IsFileExist(strFileDownLoad))
		{
			bRet1 = TRUE;
		}
		else
		{
		bRet1 = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
	}
	}

	//���ر���ģ���ļ�
	strFile_s.Empty();
	pAtsCmd->GetParasDataValueByID(XPARA_ID_DOCRPTFILE_S, strFile_s);
	strFile = ChangeFilePostfix(strFile, _T("doc"));

	if (strFile_s.IsEmpty())
	{
		//����ģ���ļ��Ǳ�����������ڣ�ֱ�ӷ�������ʧ��
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("����ģ���ļ���%s��Ϊ�գ�����ʧ�ܣ�"), strFile);
		bRet2 = FALSE;
	}
	else
	{
		strFileDownLoad = strRootPath + strFile;
		strUrl = strHttpUrlHead + strFile_s;

		if (IsFileExist(strFileDownLoad))
		{
			bRet2 = TRUE;
		}
		else
		{
		bRet2 = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
		}
	}	

	//������չ����ģ���ļ�
	strFile_s.Empty();
	pAtsCmd->GetParasDataValueByID(XPARA_ID_DOCRPTFILE_EX_S, strFile_s);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_DOCRPTFILE_EX, strFile);
	BOOL bRet3 = TRUE;

	if (!strFile_s.IsEmpty())
	{
		strFileDownLoad = strRootPath + strFile;
		strUrl = strHttpUrlHead + strFile_s;

		if (!IsFileExist(strFileDownLoad))
		{
			bRet3 = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
		}
	}	

	//���ز����������ļ����̶���׺Ϊiecfg������Ŀ¼Ϊe-Report\Template���Ǳ�����
	BOOL bRet4 = TRUE;
	strFile_s.Empty();
	pAtsCmd->GetParasDataValueByID(XPARA_ID_IECFGFILE, strFile);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_IECFGFILE_S, strFile_s);
	
	if (!strFile_s.IsEmpty())
	{
		strFileDownLoad = strRootPath + strFile;
		strUrl = strHttpUrlHead + strFile_s;

		if (IsFileExist(strFileDownLoad))
		{
			bRet4 = TRUE;
		}
		else
		{
			bRet4 = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
	}
	}

	//���ر���װ����ص��ļ�
	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID(XPARA_ID_devices);
	BOOL bRet5 = TRUE;

	if (pDevices != NULL)
	{
		bRet5 = DownLoadFiles_Devices(pDevices);
	}

// 	CDataGroup *pApps = (CDataGroup *)pParas->FindByID(XPARA_ID_test_apps);
// 	BOOL bRet4 = TRUE;
// 
// 	if (pApps != NULL)
// 	{
// 		bRet4 = DownLoadFiles_TestApps(pApps);
// 	}

	return bRet3&&bRet2&&bRet1&&bRet4&&bRet5;
}

BOOL CAtsSvrMsgWnd::DownLoadFiles_Devices(CDataGroup *pDevices)
{
	CString strHttpUrlHead,strUrl; 
	CSttMqttClientEngineConfig::GetHttpUrlHead(strHttpUrlHead);
	CString strFile, strFile_s, strRootPath;
	CString strFileDownLoad;

	POS pos = pDevices->GetHeadPosition();
	CString strDvmRoot, strPpRoot;
	strRootPath = _P_GetInstallPath();
	strDvmRoot = strRootPath + _T("e-Protocol\\Library\\");
	strPpRoot = strRootPath + _T("e-Protocol\\Template\\");
	BOOL bReturn = TRUE;

	while (pos != NULL)
	{
		CDataGroup *pDevice = (CDataGroup *)pDevices->GetNext(pos);

		//����ģ���ļ�
		strFile_s.Empty();
		pDevice->GetDataValue(XPARA_ID_DVMFILE_S, strFile_s);
		pDevice->GetDataValue(XPARA_ID_DVMFILE, strFile);
		BOOL bRet = TRUE;

		if (strFile_s.IsEmpty())
		{
			//ģ���ļ��Ǳ�����������ڣ�ֱ�ӷ�������ʧ��
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�����豸ģ���ļ���%s��Ϊ�գ�����ʧ�ܣ�"), strFile);
			//���׮�Զ����ԣ����Բ���ģ�ͣ��ʴ˴��޸�Ϊ�Ǳ��룬����ʧ�ܲ�����ʧ��
			//2021 12 28 shaolei
			//bRet = FALSE;
		}
		else
		{	
			strFileDownLoad = strDvmRoot + strFile;
			strUrl = strHttpUrlHead + strFile_s;

			if (IsFileExist(strFileDownLoad))
			{
				bRet = TRUE;
			}
			else
			{
				bRet = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
			}
		}

		if (!bRet)
		{
			bReturn = FALSE;
		}

		//���ع�Լģ���ļ�
		strFile_s.Empty();
		pDevice->GetDataValue(XPARA_ID_PPXMLFILE_S, strFile_s);
		pDevice->GetDataValue(XPARA_ID_PPXMLFILE, strFile);

		if (!strFile_s.IsEmpty())
		{
			//��Լģ���ļ����Ǳ�����������ڣ�����������
			strFileDownLoad = strPpRoot + strFile;
			strUrl = strHttpUrlHead + strFile_s;

			if (IsFileExist(strFileDownLoad))
			{
				bRet = TRUE;
			}
			else
			{
				bRet = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
			}

			if (!bRet)
			{
				bReturn = FALSE;
			}
		}
	}

	return bReturn;
}

BOOL CAtsSvrMsgWnd::DownLoadFiles_TestApps(CDataGroup *pTestApps)
{
	BOOL bReturn = TRUE;
	return bReturn;
}
*/

BEGIN_MESSAGE_MAP(CAtsSvrMsgWnd, CWnd)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ON_STT_ENGINE_CMD_RCV, &CAtsSvrMsgWnd::OnSttEngineCmdRcv)
	ON_MESSAGE(WM_ON_STT_ENGINE_CMD_RCV_JSON, &CAtsSvrMsgWnd::OnSttEngineCmdRcv_JSON)
	ON_MESSAGE(WM_ON_STT_ENGINE_CMD_RCV_IOTCMD, &CAtsSvrMsgWnd::OnSttEngineCmdRcv_IotCmd)
	ON_MESSAGE(WM_ON_STT_ENGINE_CMD_RCV_TESTCMD, &CAtsSvrMsgWnd::OnSttEngineCmdRcv_TestCmd)
	ON_MESSAGE(WM_ON_STT_ENGINE_CMD_RCV_SYSSTATE, &CAtsSvrMsgWnd::OnSttEngineCmdRcv_SysState)
END_MESSAGE_MAP()


void CAtsSvrMsgWnd::OnTimer(UINT nIDEvent)
{

}

//��Ϣ��Դ�μ���
//long CSttAtsSvrMqttImpBase::OnTestMsg()
//	m_pServiceWnd->PostMessage(WM_ON_STT_ENGINE_CMD_RCV, (WPARAM)this, (LPARAM)pAtsCmd);
LRESULT CAtsSvrMsgWnd::OnSttEngineCmdRcv(WPARAM wParam, LPARAM lParam)
{
	CSttAtsSvrMqttImpBase *pAtsSvrMattImp = (CSttAtsSvrMqttImpBase*)wParam;

	//CSttAtsSvrMqttImpBase::OnTestMsg �Ѿ� oDriver.AddRef();���˴�ֱ�ӹ�������
	CXObjectRefDriver oAtsCmdDrv((CSttAtsCmd*)lParam);


	//�ڴ˴�������ص�ģ�͡�ģ�塢��Լģ���ļ�
	/*  �ƶ���CSttSmartTestCom��  shaolei  20230605
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();

	if (pAtsCmd->m_strID == STT_CMD_TYPE_ATS_CreateTest)
	{
		BOOL bRet = DownLoadAllFiles(pAtsCmd);
		CString strDeviceSN;
		pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);

		CSttSysState oSysState;
		CSttParas *pParasReturn = oSysState.GetSttParas();
		pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceSN);
		pAtsSvrMattImp->ReturnSysState_REPLY((CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_CreateTest, STT_CMD_SYSSTATE_ATS);

		if (!bRet)
		{
			pAtsSvrMattImp->ReturnSysState_REPLY((CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest, STT_CMD_SYSSTATE_ATS);
			return 0;
		}
	}
	*/

	pAtsSvrMattImp->Process_Cmd_Ats(oAtsCmdDrv);

	return 0;
}

/************************
{
"id": "UploadReportFinished",
"time": "2021-3-24 10:10:10",
"paras": {
	"data": [
		{
			"id": "test_name",
			"value": "��������"
		},
		{
			"id": "testuser",
			"value": "�û���¼��"
		},
		{
			"id": "DeviceSN",
			"value": "123456123456"
		},
		{
			"id": "tm_begin",
			"value": "2021-3-24 10:10:10"
		},
		{
			"id": "tm_end",
			"value": "2021-3-24 10:10:10"
		},
		{
			"id": "doc_file",
			"value": "�����ļ���.doc"
		},
		{
			"id": "doc_file_s",
			"value": " doc_file  http�ļ����䷵�صķ�����·��fileName"
		},
		{
			"id": "doc_ex_file",
			"value": "ԭʼ��¼�ļ���.doc"
		},
		{
			"id": "doc_ex_file_s",
			"value": " doc_file  http�ļ����䷵�صķ�����·��fileName"
		},
		{
			"id": "pcap_file",
			"value": "�����ļ���_pcap.rar"
		},
		{
			"id": "pcap_file_s",
			"value": " pcap_file  http�ļ����䷵�صķ�����·��fileName"
		}
			]
	}
}
*************************/
LRESULT CAtsSvrMsgWnd::OnSttEngineCmdRcv_JSON(WPARAM wParam, LPARAM lParam)
{
	CSttAtsSvrMqttImpBase *pAtsSvrMattImp = (CSttAtsSvrMqttImpBase*)wParam;
	char *pszMsg = (char *)lParam;
	int nLen = strlen(pszMsg);
	//CJSON *pJson = CJSON_Parse(pszMsg);

	CSttSysState oSysState;
// 	if(pszMsg[0] == '<')
// 		PraseCmdBuf(&oSysState, pszMsg, nLen, MQTT_DATA_FORMAT_XML);
// 	else
// 		PraseCmdBuf(&oSysState, pszMsg, nLen, MQTT_DATA_FORMAT_JSON);

	if (*pszMsg == '<')
	{
		oSysState.PraseCmdBuf(const_cast<char*>(pszMsg),
			nLen, m_pDestBuffer,MQTT_DATA_FORMAT_XML);
	}
	else
	{
		oSysState.PraseCmdBuf(const_cast<char*>(pszMsg),
			nLen, m_pDestBuffer,MQTT_DATA_FORMAT_JSON);
	}

	pAtsSvrMattImp->Process_Cmd_Ats_Event_UploadFinish(&oSysState);

	return 0;
}

LRESULT CAtsSvrMsgWnd::OnSttEngineCmdRcv_IotCmd(WPARAM wParam, LPARAM lParam)
{
	CSttAtsSvrMqttImpBase *pAtsSvrMattImp = (CSttAtsSvrMqttImpBase*)wParam;

	CXObjectRefDriver oIotCmdDrv((CSttIotCmd *)lParam);

	pAtsSvrMattImp->Process_Cmd_Iot(oIotCmdDrv);
	return 0;
}

LRESULT CAtsSvrMsgWnd::OnSttEngineCmdRcv_TestCmd(WPARAM wParam, LPARAM lParam)
{
	CSttAtsSvrMqttImpBase *pAtsSvrMattImp = (CSttAtsSvrMqttImpBase*)wParam;

	CXObjectRefDriver oTestCmdDrv((CSttTestCmd *)lParam);

	pAtsSvrMattImp->Process_Cmd_Iot(oTestCmdDrv);
	return 0;
}

LRESULT CAtsSvrMsgWnd::OnSttEngineCmdRcv_SysState(WPARAM wParam, LPARAM lParam)
{
	CSttAtsSvrMqttImpBase *pAtsSvrMattImp = (CSttAtsSvrMqttImpBase*)wParam;

	CXObjectRefDriver oSysStateDrv((CSttSysState *)lParam);

	pAtsSvrMattImp->Process_Cmd_SysState(oSysStateDrv);
	return 0;
}