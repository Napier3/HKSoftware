#include "StdAfx.h"
#include "SmartCapCtrl.h"
#include "../../Module/SmartCap/XSmartCapMngr.h"

#include "../../Module/Socket/XPing.h"
#include "../../RelayTest/Module/SttTestAppConfig/SttTestAppCfg.h"
#include "../../RelayTest/Module/SttTestAppConfig/SttTestAppConfigTool.h"

#define MACROID_STTTIMEMEASURETEST _T("SttTimeMeasureTest")
#define MACROID_STTIECDETECTTEST   _T("Iec61850Detect")
#define MACROID_STTMUTIMETEST      _T("MUTimeTest")
#define MACROID_STTIEDTEST         _T("IEDTest")


CSmartCapCtrl* g_theSmartCapCtrl = NULL;
long CSmartCapCtrl::g_nSmartCapCtrlRef = 0;

CSmartCapCtrl* CSmartCapCtrl::Create()
{
	g_nSmartCapCtrlRef++;

	if (g_nSmartCapCtrlRef == 1)
	{
		g_theSmartCapCtrl = new CSmartCapCtrl();
	}

	return g_theSmartCapCtrl;
}

void CSmartCapCtrl::Release()
{
	g_nSmartCapCtrlRef--;

	if (g_nSmartCapCtrlRef == 0)
	{
		delete g_theSmartCapCtrl;
		g_theSmartCapCtrl = NULL;
	}
}

BOOL CSmartCapCtrl::g_bConnected = FALSE;

CSmartCapCtrl::CSmartCapCtrl(void)
{
	m_pSttTestAppCfg = NULL;
	m_hMsgWnd = 0;
	m_nMsg = 0;
	m_hSysMsgWnd = 0;
	m_nSysMsg = 0;

	m_strTemplateFile = _T("");
	m_strDeviceFile = _T("");

	m_pXSttCap_61850 = NULL;
	m_pCurrDataset = NULL;

	m_bLoadedIecfg = FALSE;
	m_pThread = NULL;
	m_nSwitchIndex = 0;
	m_nSwitchCount = 0;
	m_nMinBoutToGseNum = 10000;
	m_nMinGseToBinNum = 10000;
	m_nBinaryCount = 0;
	m_bDelayReset = FALSE;
	m_bStop_PostMsg = FALSE;
#ifndef _PSX_QT_LINUX_
    m_pSttMulticastClientSocket = NULL;
#endif
}

CSmartCapCtrl::~CSmartCapCtrl(void)
{
}

void CSmartCapCtrl::CreateAt02dCmdThread()   //lijunqing 2022-4-8
{
#ifndef  _PSX_IDE_QT_
	m_pThread = AfxBeginThread(At02dCmdThread, this);
	m_pThread->m_bAutoDelete = TRUE;
#else
	m_pThread = new CWinThread(At02dCmdThread, this);
	m_pThread->ResumeThread();
#endif
}

BOOL CSmartCapCtrl::ConnectDevice()
{
	if (g_bConnected)
	{
		//m_pXSttCap_61850->DisConnectServer();
		return TRUE;
	}

	m_nCurrCmd = 4;
	CreateAt02dCmdThread();
	return TRUE;
}


BOOL CSmartCapCtrl::IsTestAppExist()
{
	char* pszIP = NULL;
	CString strTestAppIP = m_pSttTestAppCfg->GetTestAppIP();
	CString_to_char(strTestAppIP,&pszIP);

	BOOL bConnect = xping(pszIP);
	delete pszIP;

	if (!bConnect)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("测试仪：%s 网络连接不通！"),strTestAppIP.GetString());
	}

	return bConnect;
}

BOOL CSmartCapCtrl::ConnectDevice_Cmd(BOOL bPostMsg)
{
	if (g_nXSmartCapDebugMode)
	{
		SmartCap_PostDeviceSysMessage(this,0,engineConnectDeviceSuccessful);
		return TRUE;
	}
	// 	m_pXSttCap_61850->FreeClientTestEngine();
	// 	g_oSttTestAppConfigTool.GetSttTestEngineClientData(&(m_pXSttCap_61850->m_pSttClientTestEngine));

	if(! IsTestAppExist())
	{
		SmartCap_PostDeviceSysMessage(this,0,engineConnectDeviceFailed);
		return FALSE;
	}

	//组播告知底层切换程序
	MultiCast();

	if(m_pXSttCap_61850->ConnectServer())
	{
		g_bConnected = TRUE;
		g_theCapDeviceMngrMsgRcvWnd->XSetTimer(HEART_BEAT_TIMER, 5000, NULL);
	}
	else
	{
		m_pXSttCap_61850->DisConnectServer();
		g_bConnected = FALSE;
	}

	if (!bPostMsg)
	{
		return g_bConnected;
	}

	if (m_hSysMsgWnd != 0)
	{
		if (g_bConnected)
		{
			CTickCount32 oTick;
			oTick.DoEvents(500);
			SmartCap_PostDeviceSysMessage(this,0,engineConnectDeviceSuccessful);
		} 
		else
		{
			//以下两行，调试用
			//g_bConnected = TRUE;
			//SmartCap_PostDeviceSysMessage(this,0,engineConnectDeviceSuccessful);
			SmartCap_PostDeviceSysMessage(this,0,engineConnectDeviceFailed);
		}
	}

	return g_bConnected;
}

BOOL CSmartCapCtrl::IecDetect_Cmd(long nMode)
{
	if (m_pXSttCap_61850 == NULL)
	{
		return FALSE;
	}

	if (nMode == 0)
	{
		m_pXSttCap_61850->IecDetect(0);
	}
	else
	{
		CDvmData *pData = NULL;
		pData = FindDataByAppID_IecDetect(m_strCurrAppID);
		CString strCRC;

		if (pData != NULL)
		{
			CDvmValue *pValue = (CDvmValue *)pData->FindByID(_T("CRC"));//MYM Crc  2020-10-31
			strCRC = pValue->m_strValue;
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CRC = %s"), strCRC.GetString());
		}
		else
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++CSmartCapCtrl::IecDetect_Cmd+++++Find CRC fail, APPID=%s")
                                       , m_strCurrAppID.GetString());
		}

		m_pXSttCap_61850->IecDetect(1, strCRC);

		if (g_theCapDeviceMngrMsgRcvWnd != NULL)
		{
			g_theCapDeviceMngrMsgRcvWnd->XKillTimer(g_nOscillographTimeID);
			g_theCapDeviceMngrMsgRcvWnd->XSetTimer(g_nOscillographTimeID, g_dwOscillographRefreshTime, 0);
		}

	}
	return TRUE;
}

BOOL CSmartCapCtrl::WriteIecRcdStep_Cmd()
{
	if (m_pXSttCap_61850 == NULL)
	{
		return FALSE;
	}

	m_pXSttCap_61850->WriteIecRcdStep(CAP_DATASET_MAP_ID_RcdStep6U6I);

	return TRUE;
}

BOOL CSmartCapCtrl::MUTimeTest_Cmd()
{
	if (m_pXSttCap_61850 == NULL)
	{
		return FALSE;
	}

	m_pXSttCap_61850->MUTimeTest(CAP_DATASET_MAP_ID_MUTime);

	return TRUE;
}

BOOL CSmartCapCtrl::IEDTest_Cmd()
{
	if (m_pXSttCap_61850 == NULL)
	{
		return FALSE;
	}

	if (m_bDelayReset)
	{
		//AfterLoadDvmFile();
		ResetTestMode_IEDTest();
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("智能终端测试---->>>>复归"));
	}

	UpdateBinaryMapValue_IEDTest(m_nSwitchIndex, m_strSwitchState);
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("当前变位：【%d】,m_nSwitchIndex=%ld;m_strSwitchState=%s;")
                               , m_nSwitchCount,m_nSwitchIndex,m_strSwitchState.GetString());
	m_pXSttCap_61850->IEDTest(CAP_DATASET_MAP_ID_IEDTest);

	if (m_bDelayReset)
	{
		SmartCap_PostDeviceCommCmdMessage(this, 0, engineCommFinish);
	}

	return TRUE;
}

CDvmData* CSmartCapCtrl::FindDataByAppID_IecDetect(const CString &strAppID)
{
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++CSmartCapCtrl::FindDataByAppID_IecDetect+++++%s"), strAppID);
	CDvmData *pData = NULL;
	CDvmData *pFind = NULL;
	POS pos = m_oDataset_IecDetect.GetHeadPosition();
	CDvmValue *pAppID = NULL;

	if (pos == NULL)
	{
		//表示此时是没有经过探测，直接测试的；
		CString strPath;
		strPath = _P_GetLibraryPath();
		strPath += _T("PNI302_DetectInfo.xml");
		m_oDataset_IecDetect.OpenXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
		pos = m_oDataset_IecDetect.GetHeadPosition();
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++CSmartCapCtrl::FindDataByAppID_IecDetect+++++open DetectInfo File"));
	}

	while (pos != NULL)
	{
		pData = (CDvmData *)m_oDataset_IecDetect.GetNext(pos);
		pAppID = (CDvmValue *)pData->FindByID(_T("AppID"));//MYMAppid

		if (pAppID != NULL)
		{
			if (pAppID->m_strValue == strAppID)
			{
				pFind = pData;
				break;
			}
		}
	}

	return pFind;
}

BOOL CSmartCapCtrl::DisConnectDevice()
{
	if (m_pXSttCap_61850)
	{
		m_pXSttCap_61850->m_pSttClientTestEngine->DisConnect();
	}

	g_bConnected = FALSE;

	return TRUE;
}

BOOL CSmartCapCtrl::CloseSmartCap()
{
	m_pXSttCap_61850->LoadCapDevices(&m_oIecCfgDevice);
	m_pXSttCap_61850->RecordAllDevice();
	m_pXSttCap_61850->BeginRecord();
	m_pXSttCap_61850->CreateCapTrhead();
	return true;
}

BOOL CSmartCapCtrl::LoadDvmFile(const CString &strDeviceFile)
{
	if (!IsFileExist(strDeviceFile))
	{
		return FALSE;
	}

	m_oDeviceModel.DeleteAll();
	m_pCurrDataset = NULL;
	m_strDeviceFile = strDeviceFile;
	BOOL b = m_oDeviceModel.OpenXmlFile(m_strDeviceFile,CDataMngrXmlRWKeys::CDvmDeviceKey(), CDataMngrXmlRWKeys::g_pXmlKeys);	
	AddReportDataset();

	if (b)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("打开模型文件【%s】成功"), m_strDeviceFile.GetString());
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("打开模型文件【%s】失败"), m_strDeviceFile.GetString());
	}

	if (m_pXSttCap_61850 != NULL)
	{
		m_pXSttCap_61850->SetDvmDevice(&m_oDeviceModel);
	}

	return b;
}

void CSmartCapCtrl::AfterLoadDvmFile()
{
	//智能终端测试时，需要将GOOSE发布、GOOSE订阅的映射关系反馈给单机软件；
	//因此，此函数用于整理映射关系，并保存到智能终端测试数据集；
	CDvmDataset *pIEDTest = (CDvmDataset *)m_oDeviceModel.FindDataset(CAP_DATASET_MAP_ID_IEDTest);

	if (pIEDTest == NULL)
	{
		return;
	}

	CDvmData *pGin = (CDvmData *)pIEDTest->FindByID(_T("Gin"));  //GOOSE订阅
	POS pos = NULL;

	if (pGin != NULL)
	{
		pos = pGin->GetHeadPosition();
		while (pos != NULL)
		{
			CDvmValue *pValue = (CDvmValue *)pGin->GetNext(pos);
			pValue->m_strValue = _T("-1");
		}

		AfterLoadDvmFile_BinaryMap(pGin, _T("Bin"));
	}

	CDvmData *pGout = (CDvmData *)pIEDTest->FindByID(_T("Gout"));  //GOOSE发布

	if (pGout != NULL)
	{
		pos = pGout->GetHeadPosition();
		while (pos != NULL)
		{
			CDvmValue *pValue = (CDvmValue *)pGout->GetNext(pos);
			pValue->m_strValue = _T("-1");
		}

		AfterLoadDvmFile_BinaryMap(pGout, _T("Bout"));
	}

	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("PNI302_Config_dsIEDTest.xml");
	pIEDTest->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void CSmartCapCtrl::ResetBinaryMap()
{
	CDvmDataset *pIEDTest = (CDvmDataset *)m_oDeviceModel.FindDataset(CAP_DATASET_MAP_ID_IEDTest);

	if (pIEDTest == NULL)
	{
		return;
	}

	if (m_pXSttCap_61850 == NULL)
	{
		return;
	}

	CDvmData *pGin = (CDvmData *)pIEDTest->FindByID(_T("Gin"));  //GOOSE订阅

	if (pGin != NULL)
	{
		m_pXSttCap_61850->ResetBinaryMap_Data(pGin);
	}

	CDvmData *pGout = (CDvmData *)pIEDTest->FindByID(_T("Gout"));  //GOOSE发布

	if (pGout != NULL)
	{
		m_pXSttCap_61850->ResetBinaryMap_Data(pGout);
	}
}

//智能终端数据集下的Gin和Gout数据（pData）下的CDvmValue，按照最大化配置,ID分别为bin001……bin064;bout001……bout064，value初始值为-1；
void CSmartCapCtrl::AfterLoadDvmFile_BinaryMap(CDvmData *pData, const CString &strType)
{
	if (pData == NULL)
	{
		return; 
	}

	CString strIDMap, strDatasetID;

	if (strType == _T("Bin"))
	{
		strDatasetID = CAP_DATASET_MAP_ID_GIN1;
		strIDMap = _T("bin");
	}
	else
	{
		strDatasetID = CAP_DATASET_MAP_ID_GOUT1;
		strIDMap = _T("bout");
	}

	//映射关系数据集 dsGout1  或者dsGin1
	CDvmDataset *pSrc = (CDvmDataset *)m_oDeviceModel.FindDataset(strDatasetID);

	if (pSrc == NULL)
	{
		return;
	}

	POS pos = pSrc->GetHeadPosition();
	CDvmData *pSrcData = NULL;
	CDvmValue *pValue = NULL;
	CDvmValue *pNew = NULL;
	CString strValueID;

	while (pos != NULL)
	{
		pSrcData = (CDvmData *)pSrc->GetNext(pos);
        strValueID.Format(_T("%s$map"), pSrcData->m_strID.GetString());
		pValue = (CDvmValue *)pSrcData->FindByID(strValueID);

		if (pValue != NULL)
		{
			CString strValue;
			strValue = pValue->m_strValue;
			//如果有映射关系，则映射数据集下CDvmVaue的m_strValue值包含bin; 或者bout;
			//且此处不考虑GOOSE订阅，映射多个开入的情况
			if (strValue.Find(strIDMap) >= 0)
			{
				//去除末尾分号
				long nPos = strValue.Find(';');
				if (nPos >= 0)
				{
					strValue = strValue.Left(nPos);
				}

				//考虑映射时，映射的是扩展开关量；
				CString strID;
				long nIndex = 0;
				nIndex = SortBinID(strValue, strIDMap);
                strID.Format(_T("%s%03ld"), strIDMap.GetString(), nIndex);

				pNew = (CDvmValue *)pData->FindByID(strID);

				if (pNew != NULL)
				{				
					pNew->m_strValue = _T("0");
					pNew->m_strName = pSrcData->m_strName;
				}

				//记录最小的编号
				if (strType == _T("Bin"))
				{
					if (m_nMinBoutToGseNum > nIndex)
					{
						m_nMinBoutToGseNum = nIndex;
					}
				}
				else
				{
					if (m_nMinGseToBinNum > nIndex)
					{
						m_nMinGseToBinNum = nIndex;
					}
				}
			}
		}	
	}
}

long CSmartCapCtrl::SortBinID(const CString &strSrcID, const CString &strIDMap)
{
	CString strID, strIndex;
	long nIndex = 0;
	strID = strSrcID;
	long nPos = strID.Find(';');
	long nLen = 0;

	if (nPos >= 0)
	{
		strID = strID.Left(nPos);
	}

	CString strIDMapEx;
    strIDMapEx.Format(_T("%sex"), strIDMap.GetString());
	//扩展开入开出
	nPos = strID.Find(strIDMapEx);

	if (nPos >= 0)
	{
		nLen = strIDMapEx.GetLength();
		strIndex = strID.Mid(nPos+nLen);
		strID = strIDMap;
		nIndex = CString_To_long(strIndex) + 8;
	}
	else
	{
		nPos = strID.Find(strIDMap);

		if (nPos >= 0)
		{
			nLen = strIDMap.GetLength();
			strIndex = strID.Mid(nPos+nLen);
			nIndex = CString_To_long(strIndex);
		}
	}

	return nIndex;
}


void CSmartCapCtrl::AddReportDataset()
{
	CDvmLogicDevice *pLdReport = (CDvmLogicDevice*)m_oDeviceModel.FindByID(CAP_DATASET_MAP_ID_Report);

	if (pLdReport == NULL)
	{
		pLdReport = new CDvmLogicDevice();
		pLdReport->m_strName = CAP_DATASET_MAP_ID_Report;
		pLdReport->m_strID = CAP_DATASET_MAP_ID_Report;
		m_oDeviceModel.AddNewChild(pLdReport);
	}

	CDvmDataset *pDsReport = (CDvmDataset*)pLdReport->FindByID(CAP_DATASET_MAP_ID_Report);

	if (pDsReport == NULL)
	{
		pDsReport = new CDvmDataset();
		pDsReport->m_strName = CAP_DATASET_MAP_ID_Report;
		pDsReport->m_strID = CAP_DATASET_MAP_ID_Report;
		pLdReport->AddNewChild(pDsReport);
	}
}

void CSmartCapCtrl::CreateUpdateDvmDeviceDatasThread()
{
	if (m_pXSttCap_61850 != NULL)
	{
		m_pXSttCap_61850->CreateUpdateDvmDeviceDatasThread();
	}
}

BOOL CSmartCapCtrl::LoadIecCfgFile(const CString &strIecCfgFile)
{
	if (!IsFileExist(strIecCfgFile))
	{
		m_bLoadedIecfg = FALSE;
		return FALSE;
	}

	if (m_oIecCfgDevice.GetCount() > 0)
	{
		m_bLoadedIecfg = TRUE;
		return TRUE;
	}

	m_strIecCfgFile = strIecCfgFile;
	BOOL bRet = m_oIecCfgDevice.OpenIecCfgFile(strIecCfgFile);

	//载入同名的设备数据模型文件  lijunqing 2020-6-18
	CString strDvmFile/*, strPath*/;
	//strDvmFile = GetFileNameFromFilePath(strIecCfgFile);
	strDvmFile = ChangeFilePostfix(strIecCfgFile, _T("xml"));
	LoadDvmFile(strDvmFile);
	AfterLoadDvmFile();
	// 	strPath = _P_GetInstallPath();
	// 	LoadDvmFile(strPath + _T("e-Report\\Library\\") + strDvmFile);
	ASSERT (m_pXSttCap_61850 != NULL);
	// 	if (m_pXSttCap_61850 != NULL)
	// 	{
	// 		m_pXSttCap_61850->RecordDevice_Reset();
	// 	}

	//根据Iecfg文件配置Device
	LoadDevices();

	if (m_pXSttCap_61850 != NULL)
	{
		m_pXSttCap_61850->Init_SV_Channels();
		m_pXSttCap_61850->Init_GS_Channels();
	}

	//2020-06-23  lijunqing   添加报告数据集，事件数据集保存于g_pSmartCapSoeCycleArray
	g_pSmartCapSoeCycleArray->SetMaxCount(1000);
	g_pSmartCapBinCycleArray->SetMaxCount(1000);

	m_bLoadedIecfg = bRet;

	return bRet;
}

void CSmartCapCtrl::BeginSmartCapThread()
{
// 	m_pXSttCap_61850->LoadCapDevices(&m_oIecCfgDevice);
// 	m_pXSttCap_61850->RecordAllDevice();
	m_pXSttCap_61850->SetDvmDevice(&m_oDeviceModel);
	m_pXSttCap_61850->BeginRecord();
	m_pXSttCap_61850->CreateCapTrhead();
	m_pXSttCap_61850->CreateUpdateDvmDeviceDatasThread();
}

CString CSmartCapCtrl::GetCurrDatasMngrID()
{
	CString strDatasMngrID;

	if (m_oIecCfgDevice.m_pCurrDatasMngr == NULL)
	{
		strDatasMngrID = _T("");
	}
	else
	{
		strDatasMngrID = m_oIecCfgDevice.m_pCurrDatasMngr->m_strID;
	}

	return strDatasMngrID;
}

BOOL CSmartCapCtrl::IsInStateOutput()
{ 
	if (m_pXSttCap_61850 == NULL)
	{
		return FALSE;
	}

	return m_pXSttCap_61850->m_bInStateTest; 
}

BOOL CSmartCapCtrl::IsStartedTest()
{	
	if (m_pXSttCap_61850 == NULL)
	{
		return FALSE;
	}

	return m_pXSttCap_61850->m_bTestStarted;	
}

BOOL CSmartCapCtrl::IsEnableStartOutput()
{
	if (m_pCurrDataset == NULL)
	{
		return FALSE;
	}

	if (m_pCurrDataset->m_strID != CAP_DATASET_MAP_ID_State)
	{
		return FALSE;
	}

	if (!m_bLoadedIecfg)
	{
		return FALSE;
	}

	if (GetCurrDatasMngrID() != _T("TimeMeasureTest"))
	{
		return FALSE;
	}

	return !IsInStateOutput();
}

BOOL CSmartCapCtrl::IsEnableStopOutput()
{
	// 	if (m_pCurrDataset == NULL)
	// 	{
	// 		return FALSE;
	// 	}
	// 
	// 	if (m_pCurrDataset->m_strID != CAP_DATASET_MAP_ID_State)
	// 	{
	// 		return FALSE;
	// 	}

	return IsStartedTest();
}

void CSmartCapCtrl::LoadDevices()
{
	m_pXSttCap_61850->LoadCapDevices(&m_oIecCfgDevice);
	m_pXSttCap_61850->RecordAllDevice();
	m_pXSttCap_61850->BeginRecord();
	m_pXSttCap_61850->CreateCapTrhead();
}

//通讯命令执行
//读测量值
void CSmartCapCtrl::ReadAin()          
{

}

//读畸变率、读SV同步差
void CSmartCapCtrl::ReadDin() 
{

}

//读瞬时值
void CSmartCapCtrl::ReadInst(const CString &strChannelID)
{
	m_pXSttCap_61850->UpdateDvmDeviceDatas_SvInst(strChannelID);
}

//读畸变率
void CSmartCapCtrl::ReadTHD()
{

}

//读离散值
void CSmartCapCtrl::ReadDiscrete()
{

}

//读SV延时
void CSmartCapCtrl::ReadSvDelay()
{

}

//读SV同步差
void CSmartCapCtrl::ReadSVSyn()
{

}

//读GOOSE同步差
void CSmartCapCtrl::ReadGooseSyn()
{

}

//状态序列输出
void CSmartCapCtrl::WriteState()
{
	m_nCurrCmd = 3;
	CreateAt02dCmdThread();}
void CSmartCapCtrl::WriteState_Cmd()
{
	if (m_pXSttCap_61850 != NULL)
	{
		m_pXSttCap_61850->StateTest(CAP_DATASET_MAP_ID_State);
	}
}

//SV报文一致性
void CSmartCapCtrl::ReadSVCstc()
{

}

//GOOSE报文一致性
void CSmartCapCtrl::ReadGoCstc()
{

}

//SV报文异常模拟
void CSmartCapCtrl::ReadSVErr()
{

}

//GGOSE报文异常模拟
void CSmartCapCtrl::ReadGooseErr()
{

}

//启动抓包
BOOL CSmartCapCtrl::StartCap()
{
	if (g_theCapDeviceMngrMsgRcvWnd == NULL)
	{
		return FALSE;
	}

	g_theCapDeviceMngrMsgRcvWnd->XPostMessage(WM_BEGIN_CAP_MSG, 0, 0);
	return TRUE;
}

//停止抓包
BOOL CSmartCapCtrl::StopCap(BOOL bPostMsg)
{
	if (m_pXSttCap_61850 == NULL)
	{
		return FALSE;
	}

	if (m_nCurrCmd == 2)
	{
		//已经停止了  就不再停了
		if (bPostMsg)
		{
			SmartCap_PostDeviceCommCmdMessage(this, 0, engineCommFinish);
		}
		return TRUE;
	}

	// 	if (m_nCurrCmd == 9)
	// 	{
	// 		//如果是智能终端测试，需要将相关的定时器关掉
	// 		//g_theCapDeviceMngrMsgRcvWnd->XKillTimer(IEDTEST_AUTOTEST_DELAY_TIMER);
	// 		//g_theCapDeviceMngrMsgRcvWnd->XKillTimer(IEDTEST_STORM_SOE_TIMER);
	// 		m_nSwitchCount = m_nBinaryCount;
	// 	}

	m_bStop_PostMsg = bPostMsg;
	m_nCurrCmd = 2;
	CreateAt02dCmdThread();
	return TRUE;
}

BOOL CSmartCapCtrl::StartCap_Cmd()
{
	if (g_theCapDeviceMngrMsgRcvWnd == NULL)
	{
		return FALSE;
	}

	g_theCapDeviceMngrMsgRcvWnd->XPostMessage(WM_BEGIN_CAP_MSG, 0, 0);
	return TRUE;
}

//停止抓包
BOOL CSmartCapCtrl::StopCap_Cmd()
{
	if (m_pXSttCap_61850 == NULL)
	{
		return FALSE;
	}

	long nRet = m_pXSttCap_61850->StopCap();

	if (nRet)
	{
		if (g_theCapDeviceMngrMsgRcvWnd != NULL)
		{
			g_theCapDeviceMngrMsgRcvWnd->XKillTimer(g_nOscillographTimeID);
		}

		if (m_bStop_PostMsg)
		{
			SmartCap_PostDeviceCommCmdMessage(this, 0, engineCommFinish);
		}		
	}
	else
	{
		if (m_bStop_PostMsg)
		{
			SmartCap_PostDeviceCommCmdMessage(this, 0, engineCommError);
		}	
	}

	return nRet;
}

UINT CSmartCapCtrl::At02dCmdThread(LPVOID pPara)
{
	CSmartCapCtrl *pCtrl = (CSmartCapCtrl*)pPara;

	switch (pCtrl->m_nCurrCmd)
	{
	case 1:
		pCtrl->DownIecfgData_Cmd();
		break;

	case 2:
		pCtrl->StopCap_Cmd();
		break;

	case 3:
		pCtrl->WriteState_Cmd();
		break;

	case 4:
		pCtrl->ConnectDevice_Cmd();
		break;

	case 5:
		pCtrl->IecDetect_Cmd(0);
		break;

	case 6:
		pCtrl->IecDetect_Cmd(1);
		break;

	case 7:
		pCtrl->WriteIecRcdStep_Cmd();
		break;
	case 8:
		pCtrl->MUTimeTest_Cmd();
		break;
	case 9:
		pCtrl->IEDTest_Cmd();
		break;
	}

	pCtrl->m_pThread = NULL;
	return 0;
}


//下载配置
BOOL CSmartCapCtrl::DownIecfgData(const CString &strIecfgDataID)
{
	m_strCurrIecfgDataID = strIecfgDataID;
	g_oCapAnalysisConfig.m_bSmvSyncDelt = TRUE;//mym 改成TRUE, 原来是FALSE2020-12-15

	if (strIecfgDataID == _T("SVSnyTest"))
	{
		g_oCapAnalysisConfig.m_bAnalysisData_DelayTime = TRUE;
		g_oCapAnalysisConfig.m_bSmvSyncDelt = TRUE;
	}

	if (strIecfgDataID == _T("GooseSnyTest"))
	{
		g_oCapAnalysisConfig.m_bGsAnalysis = TRUE;
	}

	if (strIecfgDataID == _T("SVDelayTest"))
	{
		g_oCapAnalysisConfig.m_bAnalysisData_DelayTime = TRUE;
	}

	if (m_pThread != NULL)
	{
		return FALSE;
	}

	m_nCurrCmd = 1;
	CreateAt02dCmdThread();
	return TRUE;
}

BOOL CSmartCapCtrl::DownIecfgData_Cmd_Debug()
{
	if (m_pXSttCap_61850 == NULL)
	{
		return FALSE;
	}

	CString strIecfgDataID = m_strCurrIecfgDataID;

	//兼容调试模式，不管如何开启显示报文模式
	CIecCfgDatasMngr *pIecfgDataMngr = (CIecCfgDatasMngr*)m_oIecCfgDevice.FindByID(strIecfgDataID);
	if (g_theCapDeviceMngrMsgRcvWnd != NULL)
	{
		g_theCapDeviceMngrMsgRcvWnd->XPostMessage(WM_UPDATETITLE,(WPARAM)pIecfgDataMngr,(LPARAM)pIecfgDataMngr);
		g_theCapDeviceMngrMsgRcvWnd->XKillTimer(g_nOscillographTimeID);
		g_theCapDeviceMngrMsgRcvWnd->XSetTimer(g_nOscillographTimeID, g_dwOscillographRefreshTime, 0);
	}

	m_pXSttCap_61850->DownIecfgData(strIecfgDataID, m_strSwitchFlag);
	SmartCap_PostDeviceCommCmdMessage(this, 0, engineCommFinish);

	return TRUE;
}


BOOL CSmartCapCtrl::DownIecfgData_Cmd()
{
	if (g_nXSmartCapDebugMode)
	{
		return DownIecfgData_Cmd_Debug();
	}

	CString strIecfgDataID = m_strCurrIecfgDataID;

	//兼容调试模式，不管如何开启显示报文模式
	if (m_pXSttCap_61850 != NULL)
	{
		CIecCfgDatasMngr *pIecfgDataMngr = (CIecCfgDatasMngr*)m_oIecCfgDevice.FindByID(strIecfgDataID);

		if (g_theCapDeviceMngrMsgRcvWnd != NULL)
		{
			g_theCapDeviceMngrMsgRcvWnd->XPostMessage(WM_UPDATETITLE,(WPARAM)pIecfgDataMngr,(LPARAM)pIecfgDataMngr);
		}

	}

	if (g_theCapDeviceMngrMsgRcvWnd != NULL)
	{
		g_theCapDeviceMngrMsgRcvWnd->XKillTimer(g_nOscillographTimeID);
		g_theCapDeviceMngrMsgRcvWnd->XSetTimer(g_nOscillographTimeID, g_dwOscillographRefreshTime, 0);
	}

	if (!m_pXSttCap_61850->ConnectServerEx())
	{
		SmartCap_PostDeviceCommCmdMessage(this, 0, engineCommError);
		return FALSE;
	}

	BOOL b = FALSE;

	if (m_pXSttCap_61850 != NULL)
	{
		if (m_pXSttCap_61850->m_bTestStarted)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(">>>DownIecfgData::StopCap"));
			b = m_pXSttCap_61850->StopCap();
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DownIecfgData::StopCap>>>"));

			if (!b)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("下载配置前，停止测试失败"));
				return b;  //停止失败，则直接返回FALSE
			}
		}
	}

	CTickCount32 oTick;
	oTick.DoEvents(2000);

	if (m_pXSttCap_61850 != NULL)
	{
		b = m_pXSttCap_61850->DownIecfgData(strIecfgDataID, m_strSwitchFlag);
	}

	if (!b)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DownIecfgData::参数下发失败, ID=%s"), strIecfgDataID.GetString());
		SmartCap_PostDeviceCommCmdMessage(this, 0, engineCommError);
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DownIecfgData::参数下发成功, ID=%s"), strIecfgDataID.GetString());
		SmartCap_PostDeviceCommCmdMessage(this, 0, engineCommFinish);
	}

	return b;
}

void CSmartCapCtrl::ReadSoe()
{
	if (m_pXSttCap_61850 != NULL)
	{
		m_pXSttCap_61850->ReadSoe();
	}
}

void CSmartCapCtrl::Reset()
{
	if (m_pXSttCap_61850 != NULL)
	{
		m_pXSttCap_61850->Reset();
	}
}

void CSmartCapCtrl::IecDetect(long nMode)
{
	if (m_pXSttCap_61850 == NULL)
	{
		return;
	}

	if (nMode == 0)
	{
		m_nCurrCmd = 5;
		m_oDataset_IecDetect.DeleteAll();
	}
	else
	{
		m_nCurrCmd = 6;
	}

	CreateAt02dCmdThread();}

void CSmartCapCtrl::WriteIecRcdStep()
{
	if (m_pXSttCap_61850 == NULL)
	{
		return;
	}

	m_nCurrCmd = 7;
	CreateAt02dCmdThread();}

//读结果，直接返回即可，数据已经在数据集
void CSmartCapCtrl::ReadResponseTime()
{

}

void CSmartCapCtrl::MUTimeTest()
{
	if (m_pXSttCap_61850 == NULL)
	{
		return;
	}

	m_nCurrCmd = 8;
	CreateAt02dCmdThread();}

void CSmartCapCtrl::IEDTest(BOOL bReset)
{
	if (m_pXSttCap_61850 == NULL)
	{
		return;
	}

	m_bDelayReset = bReset;
	m_nCurrCmd = 9;
	CreateAt02dCmdThread();}

void CSmartCapCtrl::IEDTest_Stop_Reset()
{
	StopCap();
	IEDTest(TRUE);
}

//读结果，直接返回即可，数据已经在数据集
void CSmartCapCtrl::ReadIEDTestRslt()
{
	CDvmDataset *pDataset = (CDvmDataset *)m_oDeviceModel.FindDataset(CAP_DATASET_MAP_ID_IEDTest);
	CDvmData *pGin = (CDvmData *)pDataset->FindByID(_T("Gin"));
	CDvmData *pGout = (CDvmData *)pDataset->FindByID(_T("Gout"));

	POS pos = pGin->GetHeadPosition();
	CDvmValue *pBIO = NULL;
	CDvmValue *pTime1 = NULL;
	CDvmValue *pTime2 = NULL;

	while (pos != NULL)
	{
		pBIO = (CDvmValue *)pGin->GetNext(pos);

		if (pBIO->m_strValue == _T("-1"))
		{
			continue;
		}

		pTime1 = (CDvmValue *)pBIO->FindByID(_T("Time1"));
		pTime2 = (CDvmValue *)pBIO->FindByID(_T("Time2"));

		CString strTime1, strTime2;
		strTime1 = pTime1->m_strValue;
		strTime2 = pTime2->m_strValue;

		double dTime1, dTime2, dTime;
		dTime1 = CString_To_double(strTime1);
		dTime2 = CString_To_double(strTime2);
		dTime = dTime1 - dTime2;

		pBIO->m_strValue.Format(_T("%11.9f"), dTime);
	}

	pos = pGout->GetHeadPosition();
	while (pos != NULL)
	{
		pBIO = (CDvmValue *)pGout->GetNext(pos);

		if (pBIO->m_strValue == _T("-1"))
		{
			continue;
		}

		pTime1 = (CDvmValue *)pBIO->FindByID(_T("Time1"));
		pTime2 = (CDvmValue *)pBIO->FindByID(_T("Time2"));

		CString strTime1, strTime2;
		strTime1 = pTime1->m_strValue;
		strTime2 = pTime2->m_strValue;

		double dTime1, dTime2, dTime;
		dTime1 = CString_To_double(strTime1);
		dTime2 = CString_To_double(strTime2);
		dTime = dTime1 - dTime2;

		pBIO->m_strValue.Format(_T("%11.9f"), dTime);
	}
}

void CSmartCapCtrl::ReadMUTimeTestRslt()
{
	CDvmDataset *pDataset = (CDvmDataset *)m_oDeviceModel.FindDataset(CAP_DATASET_MAP_ID_MUTime);
	CDvmData *pRslt = (CDvmData *)pDataset->FindByID(_T("TestRslt"));

	POS pos = pRslt->GetHeadPosition();
	CDvmValue *pMax = (CDvmValue *)pRslt->FindByID(_T("MaxRslt"));
	CDvmValue *pMin = (CDvmValue *)pRslt->FindByID(_T("MinRslt"));
	CDvmValue *pCurr = (CDvmValue *)pRslt->FindByID(_T("CurrRslt"));

	double dMax = 0;
	double dMin = 100000;

	while (pos != NULL)
	{
		CDvmValue *pValue = (CDvmValue *)pRslt->GetNext(pos);

		if (pValue->m_strID == _T("MaxRslt") || pValue->m_strID == _T("MinRslt") ||pValue->m_strID == _T("CurrRslt"))
		{
			continue;
		}

		double dValue = CString_To_double(pValue->m_strValue);

		if (dValue >= dMax)
		{
			dMax = dValue;
		}

		if (dValue <= dMin)
		{
			dMin = dValue;
		}
	}

	pMax->m_strValue.Format(_T("%f"), dMax);
	pMin->m_strValue.Format(_T("%f"), dMin);

	if (pRslt->m_strValue.IsEmpty())
	{
		CDvmValue *p = (CDvmValue *)pRslt->GetTail();
		pRslt->m_strValue = p->m_strValue;
	}

	pCurr->m_strValue = pRslt->m_strValue;
}

BOOL CSmartCapCtrl::IsRecordTestCalThreadCreated()
{
	if (m_pXSttCap_61850 == NULL)
	{
		return FALSE;
	}

	return m_pXSttCap_61850->IsRecordTestCalThreadCreated();
}

void CSmartCapCtrl::UpdateDvmDeviceDatas()
{
	if (m_pXSttCap_61850 == NULL)
	{
		return;
	}

	m_pXSttCap_61850->UpdateDvmDeviceDatas();
}

void CSmartCapCtrl::SetTestEventInterface()
{	
	if (m_pXSttCap_61850 == NULL)
	{
		return;
	}

	if (m_pXSttCap_61850->m_pSttClientTestEngine == NULL)
	{
		return;
	}

	m_pXSttCap_61850->m_pSttClientTestEngine->SetTestEventInterface(this);
}

//获取状态序列的执行时间
long CSmartCapCtrl::GetStateTestTime_Long( const CString &strDatasetID )
{
	long nTime = 0;

	if (strDatasetID != CAP_DATASET_MAP_ID_State)
	{
		return nTime;
	}

	CDvmDataset *pDataset = (CDvmDataset *)m_oDeviceModel.FindDataset(strDatasetID);
	CDvmData *pDvmData = (CDvmData*)pDataset->FindByID(_T("StateCount"));
	long nStateCount = CString_To_long(pDvmData->m_strValue);
	CString strState_Long;
	long nState_Long = 0;
	long nStateIdx = 0;

	for (nStateIdx=0;nStateIdx<nStateCount;nStateIdx++)
	{
		strState_Long.Format(_T("State%d_Long"),nStateIdx+1);
		pDvmData = (CDvmData*)pDataset->FindByID(strState_Long);
		nState_Long = CString_To_long(pDvmData->m_strValue);
		nTime += nState_Long;
	}

	return nTime;
}

void CSmartCapCtrl::OnTestStarted(const CString &strMacroID, CDataGroup *pParas)
{
	CTickCount32 oTick;

	if (m_strCurrTest == MACROID_STTIEDTEST)
	{
		CDvmDataset *pDataset = (CDvmDataset *)m_oDeviceModel.FindDataset(CAP_DATASET_MAP_ID_IEDTest);
		CDvmData *pCtrlMode = (CDvmData *)pDataset->FindByID(_T("CtrlMode"));   //控制方式：0-手动测试；1-自动测试
		CString strCtrlMode = pCtrlMode->m_strValue;
		CDvmData *pTestType = (CDvmData *)pDataset->FindByID(_T("TestProject")); //测试类型 0-延时测试；1-SOE测试；2-风暴测试
		CString strTestType = pTestType->m_strValue;
		CDvmData *pTestMode = (CDvmData *)pDataset->FindByID(_T("TestMode"));   //测试模式 0-gse2bin; 1-bout2gse；2-gse2bin复归；3-bout2gse复归
		CString strTestMode = pTestMode->m_strValue;

		if (strCtrlMode == IEDTEST_CONTROLMODE_AUTOTEST && (strTestType == IEDTEST_TESTTYPE_DELAY))
		{
			//索引号从0开始，从映射的最小的开始变化
			if (strTestMode == IEDTEST_TESTMODE_GSE2BIN)
			{
				m_nSwitchIndex = m_nMinGseToBinNum - 1;
			}
			else if(strTestMode == IEDTEST_TESTMODE_BOUT2GSE)
			{
				m_nSwitchIndex = m_nMinBoutToGseNum - 1;
			}

			m_strSwitchState = _T("1");
			m_nSwitchCount = 1;
			oTick.DoEvents(5000); //延时五秒钟开始

			m_nBinaryCount = GetBinaryMapCount_IEDTest(pDataset);

			while (m_nSwitchCount <= m_nBinaryCount)
			{
				IEDTest();
				oTick.DoEvents(5000);
				m_nSwitchCount++;
				m_nSwitchIndex++;
			}

			StopCap(TRUE);
		}
	}
}

void CSmartCapCtrl::OnTestStoped(const CString &strMacroID, CDataGroup *pParas)
{
	CTickCount32 oTick;
	m_pXSttCap_61850->m_bTestStarted = FALSE;
	m_pXSttCap_61850->m_bInStateTest = FALSE;

	// 	if (m_strCurrTest == MACROID_STTIEDTEST)
	// 	{
	// 		//停止后复归
	// 		oTick.DoEvents(3000);
	// 		IEDTest(TRUE);
	// 	}
}

void CSmartCapCtrl::OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)
{
	if (m_strCurrTest == MACROID_STTTIMEMEASURETEST)
	{

	}
	else if (m_strCurrTest == MACROID_STTMUTIMETEST)
	{
		StopCap(FALSE);   //需要手动发送一个停止，底层用于清除相关数据
	}

	SmartCap_PostDeviceCommCmdMessage(this, 0, engineCommFinish);
	m_pXSttCap_61850->m_bTestStarted = FALSE;
	m_pXSttCap_61850->m_bInStateTest = FALSE;
}

void CSmartCapCtrl::OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)	
{

}

void CSmartCapCtrl::OnTestState(const CString &strMacroID, CDataGroup *pParas)
{
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CSmartCapCtrl::OnTestState:::::::m_strCurrTest = %s")
                               , m_strCurrTest.GetString());
	if (m_strCurrTest == MACROID_STTIECDETECTTEST)
	{
		OnTestEvent_SttIecDetectTest(pParas);
	}
	else if (m_strCurrTest == MACROID_STTMUTIMETEST)
	{
		OnTestEvent_SttMUTimeTest(pParas);
	}
	else if (m_strCurrTest == MACROID_STTIEDTEST)
	{
		OnTestEvent_SttIEDTest(pParas);
	}
}

void CSmartCapCtrl::OnReport(CSttSysState &oSysState)
{
	CSttMacro *pMacro = oSysState.GetSttMacro();
	if (pMacro != NULL)
	{
		CSttParas *pParas = pMacro->GetParas();
		CSttResults *pResult = pMacro->GetResults();
		OnTestReport(pParas, SYS_STATE_RETTYPE_REPORT);
	}
}

void CSmartCapCtrl::OnException(CDataGroup *pParas)
{
	if (pParas->m_strID == _T("UTC"))
	{
		OnException_UTC(pParas);
	}
}

long CSmartCapCtrl::OnTestReport( CSttParas *pParas, CString strRetType )
{
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CSmartCapCtrl::OnTestRetTypeState，strRetType = %s"), strRetType);
	//根据返回的paras状态，确定是否发送消息给自动测试
	if (strRetType != SYS_STATE_RETTYPE_REPORT)
	{
		return 0;
	}

	if (pParas->m_strID == _T("SttTimeMeasureTest"))
	{
		return OnTestEvent_SttTimeMeasureTest(pParas);
	}

	if (pParas->m_strID == _T("SttIecDetectTest"))
	{
		return OnTestEvent_SttIecDetectTest(pParas);
	}

	if (pParas->m_strID == _T("SttMUTimeTest"))
	{
		return OnTestEvent_SttMUTimeTest(pParas);
	}

	if (pParas->m_strID == _T("SttIEDTest"))
	{
		return OnTestEvent_SttIEDTest(pParas);
	}

	return 0;
}

long CSmartCapCtrl::OnTestEvent_SttTimeMeasureTest(CSttParas *pParas)
{
	CDvmData *pData = NULL;
	POS pos = pParas->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pParas->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != DVMCLASSID_CDVMDATA)
		{
			continue;
		}

		pData = (CDvmData *)pObj;

		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CSmartCapCtrl::OnTestRetTypeState，pData的ID = %s"), pData->m_strID);
		//执行结束
		if (pData->m_strID == _T("TestStop"))
		{
			// 			SmartCap_PostDeviceCommCmdMessage(this, 0, engineCommFinish);
			// 			m_pXSttCap_61850->m_bTestStarted = FALSE;
			// 			m_pXSttCap_61850->m_bInStateTest = FALSE;
		}
		else if (pData->m_strID == _T("TestStart"))
		{
			//测试开始，不处理
		}
		else if(pData->m_strID.Find(_T("Bin")) >= 0)
		{
			CString strValue = pData->m_strTime;
			struct timeval ts;
			EPTIME64EX tm;
			CString strTime;   //转换后的绝对时刻
			double dTime = CString_To_double(strValue);
			ts.tv_sec = (long)dTime;   //秒
			double dNs = dTime - ts.tv_sec;  //纳秒
			ts.tv_usec = dNs * 1000000;
			ep_cap_timeval_to_64timeex(ts, tm);

			Ep_EPTIME64Ex_To_String(tm, strTime);

			CString strValueID;
			strValueID = pData->m_strID + _T("$") + _T("stVal");
			pData->AddValue(_T("通道值"), strValueID, pData->m_strValue);

			strValueID = pData->m_strID + _T("$") + _T("q");
			pData->AddValue(_T("品质"), strValueID, 0);

			strValueID = pData->m_strID + _T("$") + _T("t");
			pData->AddValue(_T("时间"), strValueID, strTime);
		}

		g_pSmartCapBinCycleArray->AddExBaseObject(pData);
	}

	return 0;
}

long CSmartCapCtrl::OnTestEvent_SttIecDetectTest(CDataGroup *pParas)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("OnTestEvent_SttIecDetectTest"));
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CString strTime;
	//strTime.Format(_T("%d-%d-%d-%d-%d-%d"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile = strFile + strTime + _T("SttIecDetectTest_rslt.xml");
	pParas->SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	CDvmData *pMode = (CDvmData *)m_oDataset_IecDetect.FindByID(_T("Mode"));

	if (pMode == NULL)
	{
		pMode = new CDvmData;
		pMode->m_strID = _T("Mode");
		pMode->m_strName = _T("模式");
		m_oDataset_IecDetect.AddNewChild(pMode);
	}

	pMode->m_strValue = _T("0");
	CDvmData *pData = NULL;
	POS pos = pParas->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	long nIndex = 1;

	while (pos != NULL)
	{
		pObj = pParas->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != DVMCLASSID_CDVMDATA)
		{
			continue;
		}

		if (pObj->m_strID != _T("IEC_DETECT"))
		{
			continue;
		}

		pData = (CDvmData *)pObj;
		nIndex = GetIecDetect_CBCount() + 1;
		pData->m_strID.Format(_T("CB%d"), nIndex);

		CDvmValue *pAppID = (CDvmValue *)pData->FindByID(_T("AppID"));//Appid MYM
		if (pAppID != NULL)
		{
			CString strAppID = pAppID->m_strValue;
			long nAppID = CString_To_long(strAppID);
			strAppID.Format(_T("%x"), nAppID);

			long nLen = strAppID.GetLength();
			CString strBULING;  //补零
			if (nLen < 4)
			{
				for (int i=0; i<4-nLen;i++)
				{
					strBULING.AppendFormat(_T("0"));  //不足四位，前面补零
				}

				strAppID = strBULING+strAppID;
			}

			strAppID  = _T("0x") + strAppID;
			pAppID->m_strValue = strAppID;
		}

		CDvmValue *pIecType = (CDvmValue *)pData->FindByID(_T("IecType"));

		if (pIecType != NULL)
		{
			CString strValue = pIecType->m_strValue;

			if (strValue == _T("1"))
			{
				pIecType->m_strValue = _T("9-2");
			}
			else if (strValue == _T("2"))
			{
				pIecType->m_strValue = _T("GOOSE");
			}
			else if(strValue == _T("3"))
			{
				pIecType->m_strValue = _T("FT3");
			}
		}

		m_oDataset_IecDetect.AddNewChild((CDvmData *)pData->Clone());
	}

	return 0;
}

long CSmartCapCtrl::OnTestEvent_SttMUTimeTest(CDataGroup *pParas)
{
	CDvmData *pData = NULL;
	POS pos = pParas->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CDvmDataset *pDataset = (CDvmDataset *)m_oDeviceModel.FindDataset(CAP_DATASET_MAP_ID_MUTime);
	CDvmData *pRslt = (CDvmData *)pDataset->FindByID(_T("TestRslt"));
	CDvmValue *pRsltVal = NULL;

	while (pos != NULL)
	{
		pObj = pParas->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != DVMCLASSID_CDVMDATA)
		{
			continue;
		}

		pData = (CDvmData *)pObj;

		if (pData->m_strID == _T("RealTime") || pData->m_strID == _T("Time"))
		{
			continue;
		}

		pRsltVal = (CDvmValue *)pRslt->FindByID(pData->m_strID);

		if (pRsltVal == NULL)
		{
			pRsltVal = new CDvmValue;
			pRslt->AddNewChild(pRsltVal);
			pRsltVal->m_strID = pData->m_strID;
			pRsltVal->m_strName = pData->m_strName;
		}

		pRsltVal->m_strValue = pData->m_strValue;   //这个时间值，单位为ns
		pRslt->m_strValue = pData->m_strValue;
	}

	ReadMUTimeTestRslt();
	return 0;
}

long CSmartCapCtrl::OnTestEvent_SttIEDTest(CDataGroup *pParas)
{
	// 	CTickCount32 oTick;
	// 	oTick.DoEvents(500);   //延迟一会处理，等SUCCESS处理结束；

	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile = strFile + _T("OnTestEvent_SttIEDTest.xml");
	pParas->SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	CDvmData *pData = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CDvmDataset *pDataset = (CDvmDataset *)m_oDeviceModel.FindDataset(CAP_DATASET_MAP_ID_IEDTest);
	CDvmData *pGoutMap = (CDvmData *)pDataset->FindByID(_T("Gout"));
	CDvmData *pGinMap = (CDvmData *)pDataset->FindByID(_T("Gin"));
	CDvmData *pCtrlMode = (CDvmData *)pDataset->FindByID(_T("CtrlMode"));   //控制方式：0-手动测试；1-自动测试
	CString strCtrlMode = pCtrlMode->m_strValue;
	CDvmData *pTestType = (CDvmData *)pDataset->FindByID(_T("TestProject")); //测试类型 0-延时测试；1-SOE测试；2-风暴测试
	CString strTestType = pTestType->m_strValue;
	CDvmData *pTestMode = (CDvmData *)pDataset->FindByID(_T("TestMode"));   //测试模式 0-gse2bin; 1-bout2gse；2-gse2bin复归；3-bout2gse复归
	CString strTestMode = pTestMode->m_strValue;
	CDvmValue *pRsltVal = NULL;

	POS pos = pParas->GetHeadPosition();
	CString strRslt;

	while (pos != NULL)
	{
		pObj = pParas->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != DVMCLASSID_CDVMDATA)
		{
			continue;
		}

		pData = (CDvmData *)pObj;
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("OnTestEvent_SttIEDTest %s=%s")
                                   , pData->m_strID.GetString(), pData->m_strValue.GetString());

		if (pData->m_strID == _T("Time"))
		{
			//先计算时间
			strRslt = pData->m_strValue;
			continue;
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("OnTestEvent_SttIEDTest Time: =%s")
                                       , strRslt.GetString());
		}
		else if(pData->m_strID == _T("RealTime"))
		{
			continue;
		}

		if (pData->m_strValue == _T("0"))
		{
			//TRUE->FALSE变位时，不记录变位时间
			continue;
		}

		pData->m_strID.MakeLower();

		if (strTestType == IEDTEST_TESTTYPE_DELAY)
		{
			if (strTestMode == IEDTEST_TESTMODE_GSE2BIN)
			{
				CString strID = pData->m_strID;
				strID.Replace(_T("bin"), _T("bout"));
				pRsltVal = (CDvmValue *)pGoutMap->FindByID(strID);

				CDvmValue *pTime1 = (CDvmValue *)pRsltVal->FindByID(_T("Time1"));
				CDvmValue *pTime2 = (CDvmValue *)pRsltVal->FindByID(_T("Time2"));

				//最后的转换延时：Time1-Time2
				if (pData->m_strID.Find(_T("bin")) >= 0)
				{
					pTime1->m_strValue = strRslt;
				}
				else if (pData->m_strID.Find(_T("bout")) >= 0)
				{
					pTime2->m_strValue = strRslt;
				}
			}
			else if (strTestMode == IEDTEST_TESTMODE_BOUT2GSE)
			{
				pData->m_strID.Replace(_T("bout"), _T("bin"));
				pRsltVal = (CDvmValue *)pGinMap->FindByID(pData->m_strID);
				CDvmValue *pTime2 = (CDvmValue *)pRsltVal->FindByID(_T("Time2"));
				//最后的转换延时：Time1-Time2
				pTime2->m_strValue = strRslt;
			}
		}
		else if (strTestType == IEDTEST_TESTTYPE_SOE)
		{
			if (strTestMode == IEDTEST_TESTMODE_GSE2BIN)
			{
				pData->m_strID.Replace(_T("bin"), _T("bout"));
				pRsltVal = (CDvmValue *)pGoutMap->FindByID(pData->m_strID);

				CDvmValue *pTime1 = (CDvmValue *)pRsltVal->FindByID(_T("Time1"));
				CDvmValue *pTime2 = (CDvmValue *)pRsltVal->FindByID(_T("Time2"));

				//最后的转换延时：Time1-Time2
				// 					if (pData->m_strValue == _T("0"))
				// 					{
				// 						pTime1->m_strValue = strRslt;
				// 					}
				// 					else 
				if (pData->m_strValue == _T("1"))
				{
					pTime1->m_strValue = strRslt;
				}
			}
			else if (strTestMode == IEDTEST_TESTMODE_BOUT2GSE)
			{
				//两个时间 都需要通过GOOSE报文来解析得到
			}
		}
	}


	//ReadIEDTestRslt();

	//改为收到TestStarted的EVENT之后，通过循环来下发命令
	//  	if (strCtrlMode == IEDTEST_CONTROLMODE_AUTOTEST && strTestType == IEDTEST_TESTTYPE_DELAY)
	//  	{
	//  		if (m_nSwitchCount >= m_nBinaryCount)
	//  		{
	//  			StopCap(TRUE);
	//  		}
	//  		else
	//  		{
	//  			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++++++++++++++++++++++EVENT+++++++%d"), m_nSwitchIndex );
	// //  			m_nSwitchCount++;
	// //  			m_nSwitchIndex++;    //这种递增的方式，要求映射是连续的
	// //  			m_strSwitchState = _T("1");
	// //  			CTickCount32 oTick;
	// //  			oTick.DoEvents(500);  //稍微延迟变下一个
	// //  			IEDTest();
	//  		}	
	//  	}

	// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s = %s"), pData->m_strID, pData->m_strValue);

	// 		if (pData->m_strID == _T("TestStart"))
	// 		{
	// // 			if (strCtrlMode == IEDTEST_CONTROLMODE_AUTOTEST && (strTestType == IEDTEST_TESTTYPE_DELAY))
	// // 			{
	// // 				//索引号从0开始，从映射的最小的开始变化
	// // 				if (strTestMode == IEDTEST_TESTMODE_GSE2BIN)
	// // 				{
	// // 					m_nSwitchIndex = m_nMinGseToBinNum - 1;
	// // 				}
	// // 				else if(strTestMode == IEDTEST_TESTMODE_BOUT2GSE)
	// // 				{
	// // 					m_nSwitchIndex = m_nMinBoutToGseNum - 1;
	// // 				}
	// // 
	// // 				m_strSwitchState = _T("1");
	// // 				m_nSwitchCount = 1;
	// // 				oTick.DoEvents(5000); //延时五秒钟开始
	// // 				IEDTest();
	// // 			}
	// 		}
	// 
	// 		else if (pData->m_strID == _T("TestStop"))
	// 		{
	// // 			m_pXSttCap_61850->m_bTestStarted = FALSE;
	// // 			m_pXSttCap_61850->m_bInStateTest = FALSE;
	// // 			//停止后复归
	// // 			oTick.DoEvents(3000);
	// // 			IEDTest(TRUE);
	// 			continue;
	// 		}
	// 		else if(pData->m_strID == _T("TestReturn"))
	// 		{
	// 			//StopCap();
	// 			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("IEDTest----REPORT----TestReturn"));
	// 		}
	// 		else

	return 0;
}

long CSmartCapCtrl::OnException_UTC(CDataGroup *pParas)
{
	CDvmData *pData = NULL;
	POS pos = pParas->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CDvmDataset *pDataset = (CDvmDataset *)m_oDeviceModel.FindDataset(CAP_DATASET_MAP_ID_RcdStepResponse);
	CString strValue;
	CDvmData *pDataUTC = NULL;

	if (pDataset != NULL)
	{
		pDataUTC = (CDvmData *)pDataset->GetHead();
	}

	while (pos != NULL)
	{
		pObj = pParas->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != DVMCLASSID_CDVMDATA)
		{
			continue;
		}

		pData = (CDvmData *)pObj;
		strValue = pData->m_strValue;

		//对时时间
		if(pData->m_strID == _T("Time"))
		{
			CString strTime;   //转换后的绝对时刻
			double dTime = CString_To_double(strValue);
			if (dTime <= 0.0)
			{
				continue;
			}
			ep_cap_timeval_to_string_ns(dTime, strTime);

			if (pDataUTC != NULL)
			{
				CDvmValue *pValue = (CDvmValue *)pDataUTC->FindByID(_T("StdUTCTime"));

				if (pValue != NULL)
				{
					pValue->m_strValue = strTime;
				}
			}
		}
		//是否对时
		else if (pData->m_strID == _T("Sync"))
		{
			if (pDataUTC != NULL)
			{
				CDvmValue *pValue = (CDvmValue *)pDataUTC->FindByID(_T("StdUTCSync"));

				if (pValue != NULL)
				{
					pValue->m_strValue = strValue;   //0-无对时。1-有对时
				}
			}
		}
	}

	return 0;
}

void CSmartCapCtrl::UpdateBinaryMapValue_IEDTest(long nSwitchIndex, const CString &strSwitchState)
{
	CDvmDataset *pDataset = (CDvmDataset *)m_oDeviceModel.FindDataset(CAP_DATASET_MAP_ID_IEDTest);
	CDvmData *pTestMode = (CDvmData *)pDataset->FindByID(_T("TestMode"));   //测试模式 0-gse2bin; 1-bout2gse；2-gse2bin复归；3-bout2gse复归
	CString strTestMode = pTestMode->m_strValue;
	CDvmData *pCtrlMode = (CDvmData *)pDataset->FindByID(_T("CtrlMode"));   //控制方式：0-手动测试；1-自动测试
	CString strCtrlMode = pCtrlMode->m_strValue;
	CDvmData *pTestType = (CDvmData *)pDataset->FindByID(_T("TestProject")); //测试类型 0-延时测试；1-SOE测试；2-风暴测试
	CString strTestType = pTestType->m_strValue;

	CDvmData *pGinIndex1 = (CDvmData *)pDataset->FindByID(_T("GinIndex1"));   //GOOSE订阅索引号1
	CString strGinIndex1 = pGinIndex1->m_strValue;
	CDvmData *pGinIndex2 = (CDvmData *)pDataset->FindByID(_T("GinIndex2"));   //GOOSE订阅索引号2
	CString strGinIndex2 = pGinIndex2->m_strValue;
	CDvmData *pGinIndex3 = (CDvmData *)pDataset->FindByID(_T("GinIndex3"));   //GOOSE订阅索引号3
	CString strGinIndex3 = pGinIndex3->m_strValue;

	//自动测试时，传递过来的值不是整型；
	long nTestMode = CString_To_long(strTestMode);
	pTestMode->m_strValue.Format(_T("%d"), nTestMode);
	long nCtrlMode = CString_To_long(strCtrlMode);
	pCtrlMode->m_strValue.Format(_T("%d"), nCtrlMode);
	long nTestType = CString_To_long(strTestType);
	pTestType->m_strValue.Format(_T("%d"), nTestType);

	long nGinIndex1 = CString_To_long(strGinIndex1);
	pGinIndex1->m_strValue.Format(_T("%d"), nGinIndex1);
	long nGinIndex2 = CString_To_long(strGinIndex2);
	pGinIndex2->m_strValue.Format(_T("%d"), nGinIndex2);
	long nGinIndex3 = CString_To_long(strGinIndex3);
	pGinIndex3->m_strValue.Format(_T("%d"), nGinIndex3);

	if (nSwitchIndex < 0)
	{
		return;
	}

	//先根据传递的变位的索引号和状态，对数据集进行更新
	CString strIDMap;
	CDvmData *pBinaryMap = NULL;
	if (strTestMode == IEDTEST_TESTMODE_GSE2BIN)
	{
		strIDMap = _T("Gout");
	}
	else if(strTestMode == IEDTEST_TESTMODE_BOUT2GSE)
	{
		strIDMap = _T("Gin");
	}
	else
	{
		return;
	}
	pBinaryMap = (CDvmData *)pDataset->FindByID(strIDMap);
	CDvmValue *pMap = (CDvmValue *)pBinaryMap->GetAt(nSwitchIndex);

	if (pMap != NULL)
	{
		pMap->m_strValue = strSwitchState;
	}

	m_nBinaryCount = GetBinaryMapCount_IEDTest(pDataset);
}

void CSmartCapCtrl::ResetTestMode_IEDTest()
{
	CDvmDataset *pDataset = (CDvmDataset *)m_oDeviceModel.FindDataset(CAP_DATASET_MAP_ID_IEDTest);
	CDvmData *pTestMode = (CDvmData *)pDataset->FindByID(_T("TestMode"));   //测试模式 0-gse2bin; 1-bout2gse；2-gse2bin复归；3-bout2gse复归
	CString strTestMode = pTestMode->m_strValue;

	if (strTestMode == IEDTEST_TESTMODE_BOUT2GSE)
	{
		strTestMode = IEDTEST_TESTMODE_BOUT2GSE_RESET;
	}
	else if (strTestMode == IEDTEST_TESTMODE_GSE2BIN)
	{
		strTestMode = IEDTEST_TESTMODE_GSE2BIN_RESET;
	}

	pTestMode->m_strValue = strTestMode;
}

long CSmartCapCtrl::GetBinaryMapCount_IEDTest( CDvmDataset *pDataset)
{
	if (pDataset == NULL)
	{
		return 0;
	}

	if (m_pXSttCap_61850 == NULL)
	{
		return 0;
	}
	return m_pXSttCap_61850->GetBinaryMapCount_IEDTest(pDataset);
}

long CSmartCapCtrl::GetIecDetect_CBCount()
{
	POS pos = m_oDataset_IecDetect.GetHeadPosition();
	CDvmData *pData = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_oDataset_IecDetect.GetNext(pos);

		if (pData->m_strID.Find(_T("CB")) >= 0)
		{
			nCount++;
		}
	}

	return nCount;
}

long CSmartCapCtrl::OnDisConnect()
{
	if (m_pXSttCap_61850 == NULL)
	{
		return 0;
	}

	m_pXSttCap_61850->DisConnectServer();

	return 0;
}

void CSmartCapCtrl::OnRecvSttDebugData(CSttSysState &oSysState)
{

}

void CSmartCapCtrl::MultiCast()
{
#ifndef _PSX_QT_LINUX_
    if (m_pSttMulticastClientSocket == NULL)
	{
		m_pSttMulticastClientSocket = new CSttMulticastClientSocket;

		if(!m_pSttMulticastClientSocket->Create(m_pSttTestAppCfg->GetMulticastIP(),m_pSttTestAppCfg->GetMulticastPort(),0))
		{
			return;
		}

		//发送报文
		BYTE *pSendBuf = new BYTE;
		pSendBuf[0] = 0x0B;
		m_pSttMulticastClientSocket->SendBuffer(pSendBuf, 1, NULL);
		delete pSendBuf;
		pSendBuf = NULL;

		CTickCount32 oTick;
		oTick.DoEvents(1000);  //等待组播成功时间，由6S改为1S   20201221 shaolei
	}
	else
	{
		delete m_pSttMulticastClientSocket;
		m_pSttMulticastClientSocket = NULL;
	}
#endif
}

void CSmartCapCtrl::LOG_DEBUG_INFOR()
{
	if (m_pXSttCap_61850 == NULL)
	{
		return;
	}

	if (m_pXSttCap_61850->m_pSttClientTestEngine == NULL)
	{
		return;
	}

	m_pXSttCap_61850->LOG_DEBUG_INFOR();
}

//2022-5-2  lijunqing 
void CSmartCapCtrl::InitSmartCapCtrl()
{
	m_pXSttCap_61850->ClearCap();
}

//////////////////////////////////////////////////////////////////////////
//

void SmartCap_PostDeviceSysMessage(CSmartCapCtrl *pSmartCapCtrl, WPARAM wParam, LPARAM lParam)
{
	if (g_nXSmartCapDebugMode)
	{
		lParam = engineConnectDeviceSuccessful;
	}

	ASSERT(pSmartCapCtrl != NULL);

	HWND hWnd = (HWND)pSmartCapCtrl->m_hSysMsgWnd;

	if (!::IsWindow((hWnd)))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("发送测试完成消息 【%08x】 不是窗口【Sys】"), pSmartCapCtrl->m_hSysMsgWnd);
		return;
	}

	::PostMessage(hWnd, pSmartCapCtrl->m_nSysMsg, wParam, lParam);
}

void SmartCap_PostDeviceCommCmdMessage(CSmartCapCtrl *pSmartCapCtrl, WPARAM wParam, LPARAM lParam)
{
	if (g_nXSmartCapDebugMode)
	{
		lParam = engineCommFinish;
	}

	ASSERT(pSmartCapCtrl != NULL);

	HWND hWnd = (HWND)pSmartCapCtrl->m_hMsgWnd;

	if (!::IsWindow((hWnd)))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("发送测试完成消息 【%08x】 不是窗口【CommCmd】"), pSmartCapCtrl->m_hMsgWnd);
		return;
	}

	// 	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("发送测试完成消息 WND=【%08x】 MSG=【%08x】wParam=%08x lParam=%08x")
	// 		, (DWORD)hWnd, pSmartCapCtrl->m_nMsg, wParam, lParam);
	::PostMessage(hWnd, pSmartCapCtrl->m_nMsg, wParam, lParam);
}


/*

<?xml version="1.0" encoding="UTF-8" ?> 
- <dataset name="Dataset" id="dataset" data-type="" write-mode="0" index="0">
- <data name="" id="CB1" data-type="" value="" unit="" min="" max="" format="" index="0" time="" change="0" step="">
<value name="AppID" id="AppID" data-type="long" value="0x4004" /> 
<value name="CRC" id="CRC" data-type="long" value="34035" /> 
<value name="FiberIndex" id="FiberIndex" data-type="long" value="2" /> 
<value name="IecType" id="IecType" data-type="long" value="9-2" /> 
</data>
</dataset>
*/


//butance
/*
<?xml version="1.0" encoding="UTF-8" ?> 
- <dataset name="Dataset" id="dataset" data-type="" write-mode="0" index="0">
- <data name="" id="CB1" data-type="" value="" unit="" min="" max="" format="" index="0" time="" change="0" step="">
<value name="AppID" id="AppID" data-type="long" value="0x4004" /> 
<value name="CRC" id="CRC" data-type="long" value="34035" /> 
<value name="FiberIndex" id="FiberIndex" data-type="long" value="2" /> 
<value name="IecType" id="IecType" data-type="long" value="9-2" /> 
</data>
</dataset>
*/
