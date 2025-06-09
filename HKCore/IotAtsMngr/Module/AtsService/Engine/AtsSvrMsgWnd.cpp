//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

	//启动监视时钟，检测连接状态，定期连接服务器
	SetTimer(ATS_SVR_WATCH_TIMER_ID, 5000, NULL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CreateTest指令，下载相关测试文件的代码，移动到类CSttSmartTestCom  20230605
/*
<ats-cmd name="" id="CreateTest" testor="">
	<paras>
		<data name="测试台标识" id="TestID" value="测试台SN/"/>
		<data name="测试模板" id="gbxml-file" value="SZNR-TTU.gbexe"/>
		<data name="测试模板" id="gbxml-file_s" value="……………"/>    //e-Report/Template
		<data name="报告模板" id="doc-file_s" value="……………"/>    //e-Report/Template
		【以下部分兼容老版本数据格式】
		<data name="" id="DeviceID" data-type="" value="SZNR-TTU"/>
		<data name="规则文件" id="ppxml-file" value="SZNR-TTU.ppxml"/>
		<data name="模型文件" id="dvm-file" value="SZNR-TTU.xml"/>
		<data name="报告记录文件" id="gbrpt-file" value="SZNR-TTU202012131427"/>
		<data name="被测装置引擎" id="EngineProgID" value="PpEngine"/>
		<group name="" id="comm-config" data-type="" value="">
			<data name="" id="tcp-client" data-type="" value="">
				<value name="" id="local-ip" data-type="" value="192.168.10.10"/>
				<value name="" id="local-port" data-type="" value="20183"/>
				<value name="" id="remote-ip" data-type="" value="192.168.10.101"/>
				<value name="" id="remote-port" data-type="" value="2404"/>
			</data>
		</group>
		【以下部分为物联测试设备以及被测设备信息】
		<group id="devices">
			<group id="device">
				<data id="SN" value="123456789"/>
				<data id="EngineProgID" value="PpEngine"/>
				<data name="规则文件" id="ppxml-file" value="SZNR-TTU.ppxml"/>
				<data name="规则文件" id="ppxml-file_s" value="…… "/>  //e-Protocol/Template
				<data id="dvm-file" value="SZNR-TTU.xml"/>
				<data id="dvm-file_s" value="…… "/>   //e-Protocol/Library;[固定此路径，创建测试、编辑模板都从这个路径下]
				<data id="remote-ip" value="127.0.0.1"/>
				<data id="remote-port" value="9988"/>
			</group>
			……
		</group>
		<group id="test-apps">
			<group id="test-app">
				<data id="SN" value="123456789"/>
				<data id="EngineProgID" value="IotVm"/>
				<data id="dvm-file" value="MacroTest.xml"/>
				<data id="dvm-file_s" value="…… "/>   //测试仪不需要这个
				<data id="remote-ip" value="127.0.0.1"/>
				<data id="remote-port" value="9988"/>
			</group>
			……
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

	//下载测试模板文件
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE, strFile);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE_S, strFile_s);
	
	if (strFile_s.IsEmpty())
	{
		//测试模板文件是必须项，若不存在，直接返回下载失败
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("测试模板文件【%s】为空，下载失败！"), strFile);
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

	//下载报告模板文件
	strFile_s.Empty();
	pAtsCmd->GetParasDataValueByID(XPARA_ID_DOCRPTFILE_S, strFile_s);
	strFile = ChangeFilePostfix(strFile, _T("doc"));

	if (strFile_s.IsEmpty())
	{
		//报告模板文件是必须项，若不存在，直接返回下载失败
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("报告模板文件【%s】为空，下载失败！"), strFile);
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

	//下载扩展报告模板文件
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

	//下载测试仪配置文件（固定后缀为iecfg），根目录为e-Report\Template，非必须项
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

	//下载被测装置相关的文件
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

		//下载模型文件
		strFile_s.Empty();
		pDevice->GetDataValue(XPARA_ID_DVMFILE_S, strFile_s);
		pDevice->GetDataValue(XPARA_ID_DVMFILE, strFile);
		BOOL bRet = TRUE;

		if (strFile_s.IsEmpty())
		{
			//模型文件是必须项，若不存在，直接返回下载失败
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("被测设备模型文件【%s】为空，下载失败！"), strFile);
			//充电桩自动测试，可以不用模型，故此处修改为非必须，下载失败不返回失败
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

		//下载规约模板文件
		strFile_s.Empty();
		pDevice->GetDataValue(XPARA_ID_PPXMLFILE_S, strFile_s);
		pDevice->GetDataValue(XPARA_ID_PPXMLFILE, strFile);

		if (!strFile_s.IsEmpty())
		{
			//规约模板文件不是必须项，若不存在，则跳过下载
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

//消息来源参见：
//long CSttAtsSvrMqttImpBase::OnTestMsg()
//	m_pServiceWnd->PostMessage(WM_ON_STT_ENGINE_CMD_RCV, (WPARAM)this, (LPARAM)pAtsCmd);
LRESULT CAtsSvrMsgWnd::OnSttEngineCmdRcv(WPARAM wParam, LPARAM lParam)
{
	CSttAtsSvrMqttImpBase *pAtsSvrMattImp = (CSttAtsSvrMqttImpBase*)wParam;

	//CSttAtsSvrMqttImpBase::OnTestMsg 已经 oDriver.AddRef();，此处直接关联即可
	CXObjectRefDriver oAtsCmdDrv((CSttAtsCmd*)lParam);


	//在此处下载相关的模型、模板、规约模板文件
	/*  移动到CSttSmartTestCom类  shaolei  20230605
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
			"value": "测试名称"
		},
		{
			"id": "testuser",
			"value": "用户登录名"
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
			"value": "报告文件名.doc"
		},
		{
			"id": "doc_file_s",
			"value": " doc_file  http文件传输返回的服务器路径fileName"
		},
		{
			"id": "doc_ex_file",
			"value": "原始记录文件名.doc"
		},
		{
			"id": "doc_ex_file_s",
			"value": " doc_file  http文件传输返回的服务器路径fileName"
		},
		{
			"id": "pcap_file",
			"value": "报告文件名_pcap.rar"
		},
		{
			"id": "pcap_file_s",
			"value": " pcap_file  http文件传输返回的服务器路径fileName"
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