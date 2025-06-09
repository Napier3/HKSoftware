#include "stdafx.h"
#include "MqttClientEngineBase.h"
#include "CmdExecRslt/CmdExecGlobal.h"
#include "SttMqttClientEngineConfig.h"

CMqttClientEngineBase *g_pMqttClientEngineBase = NULL;

CMqttClientEngineBase::CMqttClientEngineBase()
{
	m_pMsgWnd = NULL;

	//初始化原始数据备份文件
	InitRawPkgFile();
}

CMqttClientEngineBase::~CMqttClientEngineBase()
{
	if(m_oRawPkgFile.m_hFile != INVALID_HANDLE_VALUE)
	{
		m_oRawPkgFile.Flush();
		m_oRawPkgFile.Close();
	}
}

BOOL CMqttClientEngineBase::InitRawPkgFile()
{
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CString strFile,strRoot;
	strRoot = _P_GetDBPath();
	strRoot = strRoot + _T("RawPkgFolder\\");
	CreateAllDirectories(strRoot);
	strFile.Format(_T("%s_RawPkgFile_%04d%02d%02d%02d%02d%02d.data"),strRoot,tm.wYear,tm.wMonth,tm.wDay,tm.wHour,tm.wMinute,tm.wSecond);

	BOOL bRet = m_oRawPkgFile.Open(strFile,CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("原始报文备份文件[%s]打开失败！"),strFile);
	}
	else
	{
		m_oRawPkgFile.SeekToBegin();
		char arrBuf[4] = {0x5a,0x59,0x5a,0x59};
		m_oRawPkgFile.Write(arrBuf,4);
	}

	return bRet;
}

void CMqttClientEngineBase::WriteRawPkg(char *pBuf,long nLen)
{
	if (m_oRawPkgFile.m_hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}

	SYSTEMTIME tm;
	GetLocalTime(&tm);

	BYTE arrByte[11] = {0};
	long nDataLen = 9 + nLen;
	arrByte[0] = nDataLen & 0xff;
	arrByte[1] = (nDataLen >> 8) & 0xff;
	arrByte[2] = tm.wYear & 0xff;
	arrByte[3] = tm.wYear >> 8;
	arrByte[4] = tm.wMonth & 0xff;
	arrByte[5] = tm.wDay & 0xff;
	arrByte[6] = tm.wHour & 0xff;
	arrByte[7] = tm.wMinute & 0xff;
	arrByte[8] = tm.wSecond & 0xff;
	arrByte[9] = tm.wMilliseconds & 0xff;
	arrByte[10] = tm.wMilliseconds >> 8;

	m_oRawPkgFile.SeekToEnd();
	m_oRawPkgFile.Write(arrByte,11);
	m_oRawPkgFile.Write(pBuf,nLen);
}

void CMqttClientEngineBase::InitMqttClientEngineBase()
{
	CDataMngrXmlRWKeys::Create();
	CMqttPpCfgXmlRWKeys::Create();
	CPpPrjXmlRWKeys::Create();
	CCmdExecXmlRWKeys::Create();

	CString strFile = _P_GetConfigPath();
	strFile += _T("SttMqttClientEngineCfg.xml");
	CSttMqttClientEngineConfig::Create(strFile);

	CSensorFragMngr::Create();
	CSttMqttClientTool::Create();
	CSttMqttClientTool::g_pSttMqttClientTool->AttachSttMqttMsgInterface(this);

// 	SetXTimer(1,1000);
// 	SetXTimer(2,2000);
// 	SetXTimer(3,3000);
// 	SetXTimer(4,4000);
// 	SetXTimer(5,5000);
}

void CMqttClientEngineBase::ExitMqttClientEngineBase()
{
	CSttMqttClientTool::Release();
	CSensorFragMngr::Release();

	CSttMqttClientEngineConfig::Release();

	CCmdExecXmlRWKeys::Release();
	CPpPrjXmlRWKeys::Release();
	CMqttPpCfgXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();
}

void CMqttClientEngineBase::OnXTimer(DWORD dwTimerID)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnXTimer:%d"),dwTimerID);
}

void CMqttClientEngineBase::OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen)
{
// 	if (strTopic == MQTT_TOPIC_Monitor)
// 	{
// 		__int64 nSensorID = sensor_pkg_get_sensorid((BYTE *)pBuf);
// 
// 		CPpPrjDevice *pPrjDevice = NULL;
// 		CSttMqttCmdExec *pFind = FindDevice(nSensorID,&pPrjDevice);
// 
// 		if (pFind != NULL)
// 		{
// 			pFind->OnMqttMsgRecieve(pPrjDevice,pBuf,nLen);
// 		}
// 	}
// 	else if (strTopic == MQTT_TOPIC_RawPkg)
// 	{
// 		WriteRawPkg(pBuf,nLen);
// 	}
}

void CMqttClientEngineBase::OnMqttDisconnected(char *pszErr)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnDisconnected:[ErrInfo=%s]"),pszErr);
}

BOOL CMqttClientEngineBase::SubcribeMqttTopic(int nQos)
{
// 	CSttMqttClientTool::SubscribeTopic(MQTT_TOPIC_Monitor,nQos);
// 	CSttMqttClientTool::SubscribeTopic(MQTT_TOPIC_RawPkg,nQos);
// 	CSttMqttClientTool::SubscribeTopic(MQTT_TOPIC_SensorCmd_Ack,nQos);

	return TRUE;
}

CSttMqttCmdExec *CMqttClientEngineBase::FindDevice(__int64 nSensorID,CPpPrjDevice **ppPrjDevice)
{
	CString strDeviceID;
	strDeviceID.Format(_T("%012X"),nSensorID);

	CPpPrjDevice *pFind = NULL;
	POS pos = m_oMqttCmdExecMngr.GetHeadPosition();
	CSttMqttCmdExec *p = NULL;

	while(pos != NULL)
	{
		p = (CSttMqttCmdExec *)m_oMqttCmdExecMngr.GetNext(pos);

		pFind = (CPpPrjDevice *)p->m_pPrjDevices->FindByID(strDeviceID);

		if (pFind != NULL)
		{
			*ppPrjDevice = pFind;
			return p;
		}
	}

	return NULL;
}

CSttMqttCmdExec *CMqttClientEngineBase::CreatePpEngineDatas(const CString &strProjectFile)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Create PpEngine:[%s]"), strProjectFile);

	//解析装置链表
	CPpPrjDevices *pDevices = new CPpPrjDevices;
	pDevices->OpenXmlFile(strProjectFile, CPpPrjXmlRWKeys::g_pXmlKeys);

	return CreatePpEngineDatas(pDevices);
}

CSttMqttCmdExec *CMqttClientEngineBase::CreatePpEngineDatas(CPpPrjDevices *pPpCfgDevices)
{
	CSttMqttCmdExec *pNew = NULL;
	POS pos = pPpCfgDevices->GetHeadPosition();
	CPpPrjDevice *pDevice = NULL;
	CString strReadAinDsID = _T("");

	while(pos != NULL)
	{
		pDevice = (CPpPrjDevice *)pPpCfgDevices->GetNext(pos);

		if (pNew == NULL)
		{
			pNew = new CSttMqttCmdExec(pDevice->m_strTemplate_File,pDevice->m_strDdvm_File,pPpCfgDevices->m_strID);
			pNew->m_pPrjDevices = pPpCfgDevices;
			strReadAinDsID = pNew->m_oMqttPpTemplate.FindReadAinDsID();
			m_oMqttCmdExecMngr.AddNewChild(pNew);
		}

		pDevice->Init(pNew,strReadAinDsID);
	}

	return pNew;
}

CSttMqttCmdExec* CMqttClientEngineBase::FindEngineData(const CString &strID)
{
	CSttMqttCmdExec *pFind = (CSttMqttCmdExec*)m_oMqttCmdExecMngr.FindByID(strID);

	return pFind;
}

void CMqttClientEngineBase::UpdateRTDevice(CPpPrjDevice *pDevice)
{
	m_pMsgWnd->PostMessage(WM_UPDATE_RTDEVICE_MSG,(WPARAM)pDevice,0);
}

CString CMqttClientEngineBase::GetDeviceReportFile(CPpPrjDevice *pDevice)
{
	CSttMqttCmdExec *pCmdExec = (CSttMqttCmdExec *)pDevice->m_pRefEngineData;

	CString strPath = _P_GetWorkspacePath();
	CString strFile;
	strFile.Format(_T("%s%s\\%s.xml"),strPath,pDevice->m_strID,pCmdExec->m_strCurItemPath);

	return strFile;
}

void CMqttClientEngineBase::ReleaseDevice(const CString &strDeviceID)
{
	m_oMqttCmdExecMngr.DeleteByID(strDeviceID);
}

void CMqttClientEngineBase::ReleaseAllDevice()
{
	m_oMqttCmdExecMngr.DeleteAll();
}