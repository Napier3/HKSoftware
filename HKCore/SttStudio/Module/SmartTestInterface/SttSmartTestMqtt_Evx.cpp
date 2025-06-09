#include "stdafx.h"
#include "SttSmartTestMqtt_Evx.h"
#include "../../../IotAtsMngr/Module/SttMqttClientEngineConfig.h"
#include "../../../Module/XFileHttpClient/XFileHttpClient.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// IMPLEMENT_DYNCREATE(CSttSmartTesMqtt, CWnd)

CSttSmartTestMqtt_Evx::CSttSmartTestMqtt_Evx()
{
	m_pDevices = NULL;
	InitSmartTestMqtt();
}

CSttSmartTestMqtt_Evx::~CSttSmartTestMqtt_Evx()
{
	if (m_pDevices != NULL)
	{
		delete m_pDevices;
		m_pDevices = NULL;
	}

	ExitSmartTestMqtt();
}

// void CSttSmartTesMqtt::CreateWnd()
// {
// 	CreateEx(0, AfxRegisterWndClass(0), _T("_Stt_SmartTest_Com_Wnd_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
// }

void CSttSmartTestMqtt_Evx::InitSmartTestMqtt()
{
}

void CSttSmartTestMqtt_Evx::ExitSmartTestMqtt()
{

}

//������վ��MQTTָ���ϳɴ�������������Ҫ����Ϣ��������ļ�����ͨ�������в���������SmartTest
/*
ѡ����Щ����С���Ҫ�Զ����Է���ȥ��ѯ���ݿ��iot_type_task_test_item_gen��ͬʱ��Ҫ���ݶ�̬���ɵ���Ŀ��ά����iot_type_task_test_item
��������ʱ���ȸ������õĲ�����Ŀ����ģ���н������ɡ����ɺ󱣴�ģ�壬Ȼ�󴴽����ԡ�
*/
long CSttSmartTestMqtt_Evx::Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttParas *pParas = pAtsCmd->GetSttParas();
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_BenchSN, m_strBenchSN);

	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
	ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
	BOOL bRet = DownLoadAllFiles(pAtsCmd);

	if (!bRet)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
		return -1;
	}

	CString strGbxmlFile, strItemsSN;
	CExBaseList *pListItems = NULL;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE, strGbxmlFile);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_ItemsSN, strItemsSN);

	if (!bRet)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
		return -2;
	}

	//д��������Լ�¼�����Լ�¼�����
	delete pListItems;
	pListItems = NULL;

	if (!bRet)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
		return -3;
	}

	if (!bRet)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
		return -4;
	}

	//����������CreateTest.atscmd�������Զ����ԣ����Զ���ʼ����
	bRet = Ats_CreateTest_StartSmartTest(pAtsCmd);

	if (!bRet)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
		return -5;
	}

	return 0;
}

/*
<sys-state name="" id="ItemStateChanged" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
		<data id="TestID" data-type="string" value="" unit=""/>
		<data id="ReportIndex" data-type="long" value="0" unit=""/>
		<data id="ItemIndex" data-type="long" value="2" unit=""/>
		<data id="ItemPath" data-type="string" value="MacroTest1" unit=""/>
		<data id="State" data-type="string" value="TESTING" unit=""/>
	</paras>
</sys-state>
*/
long CSttSmartTestMqtt_Evx::Process_Cmd_SysState_ItemStateChanged(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttSysState *pSysState = (CSttSysState *)oSysStateDrv.GetXObjectRef();
	CString strDeviceSN, strItemPath, strItemState;
	pSysState->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pSysState->GetParasDataValueByID(STT_CMD_PARA_ItemPath, strItemPath);
	pSysState->GetParasDataValueByID(STT_CMD_PARA_State, strItemState);

	return 0;
}

/*
<sys-state name="" id="TestFinished" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
  		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
	</paras>
</sys-state>
*/
long CSttSmartTestMqtt_Evx::Process_Cmd_SysState_TestFinished(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttSysState *pSysState = (CSttSysState *)oSysStateDrv.GetXObjectRef();
	CString strDeviceSN;

	return 0;
}

/*
<sys-state name="" id="TestStarted" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
  		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
	</paras>
</sys-state>
*/
long CSttSmartTestMqtt_Evx::Process_Cmd_SysState_TestStarted(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttSysState *pSysState = (CSttSysState *)oSysStateDrv.GetXObjectRef();
	CString strDeviceSN;

	return 0;
}

/*
<sys-state name="" id="TestStoped" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
  		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
	</paras>
</sys-state>
*/
long CSttSmartTestMqtt_Evx::Process_Cmd_SysState_TestStoped(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttSysState *pSysState = (CSttSysState *)oSysStateDrv.GetXObjectRef();
	CString strDeviceSN;

	return 0;
}

long CSttSmartTestMqtt_Evx::Process_Cmd_SysState_OnReport(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)
{
	return 0;
}

long CSttSmartTestMqtt_Evx::Process_Cmd_SysState_ExportReport(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)
{
	return 0;
}

long CSttSmartTestMqtt_Evx::ReturnSysState_REPLY(CSttProtocolInterface *pSttProtocol, CSttCmmOptrInterface *pCmmOptrInterface, long nCmdExecStatus, CSttCmdData *pRetData, char *pszEventID)
{
	if (pSttProtocol == NULL)
	{
		return 0;
	}

	return pSttProtocol->ReturnSysState_REPLY(pCmmOptrInterface, nCmdExecStatus, pRetData, pszEventID, STT_CMD_SYSSTATE_ATS);
}

long CSttSmartTestMqtt_Evx::ReturnSysState_EVENT(CSttProtocolInterface *pSttProtocol, CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszEventID)
{
	if (pSttProtocol == NULL)
	{
		return 0;
	}

	return pSttProtocol->ReturnSysState_EVENT(pCmmOptrInterface, pRetData, pszEventID, STT_CMD_SYSSTATE_ATS);
}

BOOL CSttSmartTestMqtt_Evx::DownLoadAllFiles(CSttAtsCmd *pAtsCmd)
{
	CSttParas *pParas = (CSttParas *)pAtsCmd->GetSttParas();
	//���ر���װ����ص��ļ�
	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID(XPARA_ID_devices);
	BOOL bRet1 = TRUE;

	if (pDevices != NULL)
	{
		bRet1 = DownLoadFiles_Devices(pDevices);
	}

 	CDataGroup *pApps = (CDataGroup *)pParas->FindByID(XPARA_ID_test_apps);
 	BOOL bRet2 = TRUE;
 
 	if (pApps != NULL)
 	{
 		bRet2 = DownLoadFiles_TestApps(pApps);
 	}

	return bRet1 && bRet2;
}

//����ģ���ļ��͹�Լģ��
BOOL CSttSmartTestMqtt_Evx::DownLoadFiles_Devices(CDataGroup *pDevices)
{
	if (pDevices == NULL)
	{
		return FALSE;
	}

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

		strFileDownLoad = strDvmRoot + strFile;
		if (IsFileExist(strFileDownLoad))
		{
			bRet = TRUE;
		}
		else
		{
			if (strFile_s.IsEmpty())
			{
				//ģ���ļ��Ǳ�����������ڣ�ֱ�ӷ�������ʧ��
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�����豸ģ���ļ���%s��Ϊ�գ�����ʧ�ܣ�"), strFile);
				bRet = FALSE;
			}
			else
			{	

				strUrl = strHttpUrlHead + strFile_s;
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

		strFileDownLoad = strPpRoot + strFile;

		if (IsFileExist(strFileDownLoad))
		{
			bRet = TRUE;
		}
		else
		{
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
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�����豸��Լģ���ļ���%s��Ϊ�գ�����ʧ�ܣ�"), strFile);
			}
		}
	}

	return bReturn;
}

//���ز��Թ����ļ�
BOOL CSttSmartTestMqtt_Evx::DownLoadFiles_TestApps(CDataGroup *pTestApps)
{
	if (pTestApps == NULL)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttSmartTestMqtt_Evx::Ats_CreateTest_StartSmartTest(CSttAtsCmd *pAtsCmd)
{
	if (pAtsCmd == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	CString strFile, strBenchSN, strDeviceSN, strFileName;
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_BenchSN, strBenchSN);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);

	CString strBenchDeviceCmd;
	strBenchDeviceCmd.Format(_T("DeviceSN:%s;"), strDeviceSN.GetString());

	if (strBenchSN.GetLength() > 0)
	{
		strBenchDeviceCmd.AppendFormat(_T("BenchSN:%s;"), strBenchSN.GetString());
	}

	strFileName = strDeviceSN + _T(".atscmd");
	strFile = _P_GetInstallPath();
	strFile += _T("e-Report/DB/");
	strFile += strFileName;

	bRet = pAtsCmd->SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	if (!bRet)
	{
		return FALSE;
	}

	//�����������Զ����Խ��̣�SmartTest.exe��
	CString strSmartTestExe, strCmdLine;
	strSmartTestExe = _P_GetInstallPath();

	strSmartTestExe += _T("e-Report/Bin/SmartTestCore.exe");
	strCmdLine.Format(_T("SmartTestServer:1;MQTT:1;CreateTest:%s;"), strFileName.GetString());
	strCmdLine = strBenchDeviceCmd + strCmdLine;
	CLogPrint::LogString(XLOGLEVEL_TRACE, strCmdLine);
	
	ExecuteFile(strSmartTestExe, strCmdLine, _T(""));

	return bRet;
}