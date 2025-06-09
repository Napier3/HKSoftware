#include "stdafx.h"
#include "SensorEngineProtoSrvrBaseApp.h"
#include "../SttMqttClientEngineConfig.h"

#include "../../../Module/DataMngr/DataMngrGlobal.h"
#include "../../../SttStudio/Module/SttCmd/SttCmdDefineGlobal.h"
#include "../ProtocolBase/Factory/EngineToPxFactory.h"
#include "IotEngineToSensor.h"
#include "../Iot_AtsMngrDB/Iot_DeviceModel.h"
#include "../Iot_AtsMngrDB/Iot_Engine.h"
#include "../../../Module/XFileHttpClient/XFileHttpClient.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CSensorEngineProtoSrvrBaseApp *g_pSensorEngineProtoSvrBaseApp = NULL;

CSensorEngineProtoSrvrBaseApp::CSensorEngineProtoSrvrBaseApp()
{
	m_listDevice.m_strName = _T("传感器管理");
	m_listDevice.m_strID = _T("SensorDeviceMngr");
	g_pSensorEngineProtoSvrBaseApp = this;
}

CSensorEngineProtoSrvrBaseApp::~CSensorEngineProtoSrvrBaseApp()
{

}


static CIotEngineToPxBase* sensor_CreateEngineToPx(CMqttEngineBase_Stt *pServer, CSttCmdBase *pCmd)
{
	CIotEngineProtocolServer *pIotEngineProtocolServer = (CIotEngineProtocolServer*)pServer;
	CString strDeviceID,strPpxml,strDvmFile,strCmmCfgFile;
	pCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceID);
	pCmd->GetParasDataValueByID(XPARA_ID_PPXMLFILE, strPpxml);//规约文件字段，创建不同转换模块
	pCmd->GetParasDataValueByID(XPARA_ID_DVMFILE, strDvmFile);
	pCmd->GetParasDataValueByID(XPARA_ID_CommCfgFile, strCmmCfgFile);

	CIotEngineToPxBase* pIotEngineToPx = CIotEngineToSensor::CreateEngineToPx();

	//针对传感器测试，创建协议转换模块时，协议接口指针为空，协议接口是实时装置，不是mqtt客户端
	CRTDeviceCtrl *pDeviceCtrl = g_pIotSensorSvrEngine->GetRTDeviceCtrl(strDeviceID,strPpxml,strDvmFile);
	pIotEngineToPx->SetPxProtoImpInterface(pDeviceCtrl);
	pIotEngineToPx->SetIotEngineProtocolServer(pIotEngineProtocolServer);

	//2021-8-19  lijunqing  如果设备不存在，则不关联
	if (pDeviceCtrl != NULL)
	{
		pDeviceCtrl->AttachProtoEventInterface(pIotEngineToPx);
	}

	return pIotEngineToPx;
}


void CSensorEngineProtoSrvrBaseApp::InitProtoSvrBaseApp()
{
	CXEngineProtoSrvrBaseApp::InitProtoSvrBaseApp();

	CIot_AtsMngrXmlRWKeys::Create();
	CIOTPPXmlRWKeys::Create();

	//注册协议转换模块
	CEngineToPxFactory::RegisterEngineToPx(ENGINE_TO_PX_IOTXML, sensor_CreateEngineToPx);

	//Http文件传输模块初始化
	CXFileHttpClient::InitXFileHttpClient();

	//全局唯一传感器服务引擎
	CIotSensorSvrEngine::Create();

	CString strIP;
	long nPort = 0;
	CSttMqttClientEngineConfig::GetMqttServerIP(strIP);
	CSttMqttClientEngineConfig::GetMqttServerPort(nPort);
	g_pIotSensorSvrEngine->Init(strIP,nPort);
}

void CSensorEngineProtoSrvrBaseApp::ExitProtoSvrBase()
{
	CXEngineProtoSrvrBaseApp::ExitProtoSvrBaseApp();

	CIotSensorSvrEngine::Release();

	CIOTPPXmlRWKeys::Release();
	CIot_AtsMngrXmlRWKeys::Release();

	CXFileHttpClient::ExitXFileHttpClient();
}

/*********************************
第一步：检查文件是否存在，若存在，则返回TRUE，若不存在，执行第二步
第二步：查询装置表，及规约引擎表，下载文件
***********************************/
BOOL CSensorEngineProtoSrvrBaseApp::CheckDeviceInfo(const CString &strDeviceID
										,CString &strDvmFile,CString &strPpxmlFile)
{
	if (strDeviceID.IsEmpty() || strDvmFile.IsEmpty() || strPpxmlFile.IsEmpty())
	{
		return FALSE;
	}

	BOOL bRet = FALSE;
	CString strHttpUrlHead,strUrl; 
	strDvmFile = GetFileNameFromFilePath(strDvmFile);
	strPpxmlFile = GetFileNameFromFilePath(strPpxmlFile);
	CSttMqttClientEngineConfig::GetHttpUrlHead(strHttpUrlHead);

	CString strSql,strDeviceTable,strDeviceModelTable,strSNKey,strIndex_ModelKey;
	strDeviceTable = CIot_AtsMngrXmlRWKeys::CIot_DeviceKey();
	strDeviceModelTable = CIot_AtsMngrXmlRWKeys::CIot_DeviceModelKey();
	strSNKey = CIot_AtsMngrXmlRWKeys::SnKey();
	strIndex_ModelKey = CIot_AtsMngrXmlRWKeys::Index_ModelKey();
	

	strDvmFile = g_strDvmFilePath + strDvmFile;
	if (!IsFileExist(strDvmFile))
	{
		CIot_DeviceModel oDeviceModel;
		strSql.Format(_T("select * from %s where %s=(select %s from %s where %s=\"%s\" limit 1) limit 1")
			,strDeviceModelTable,strIndex_ModelKey,strIndex_ModelKey,strDeviceTable,strSNKey,strDeviceID);

		bRet = oDeviceModel.DB_Select_OwnEx(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys,strSql);
		if (!bRet)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("CheckDeviceInfo:查询模型文件信息[%s]失败！"),strDeviceID);
			return FALSE;
		}

		//根据DvmFile_s下载文件
		strUrl = strHttpUrlHead + oDeviceModel.m_strPath_Protocol_File;
		bRet = CXFileHttpClient::DownloadFile(strUrl,strDvmFile);
		if (!bRet)
		{
			return FALSE;
		}
	}

	strPpxmlFile = g_strPpxmlFilePath + strPpxmlFile;
	if (!IsFileExist(strDvmFile))
	{
		CIot_Engine oEngine;
		CString strEngineTable,strIndex_EngineKey;
		strEngineTable = CIot_AtsMngrXmlRWKeys::CIot_EngineKey();
		strIndex_EngineKey = CIot_AtsMngrXmlRWKeys::Index_EngineKey();
		strSql.Format(_T("select * from %s where %s=(select %s from %s where %s=\"%s\" limit 1) limit 1")
			,strEngineTable,strIndex_EngineKey,strIndex_EngineKey,strDeviceTable,strSNKey,strDeviceID);

		bRet = oEngine.DB_Select_OwnEx(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys,strSql);
		if (!bRet)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("CheckDeviceInfo:查询规约引擎信息[%s]失败！"),strDeviceID);
			return FALSE;
		}

		//根据PpxmlFile_s下载文件
		strUrl = strHttpUrlHead + oEngine.m_strPath_Protocol_File;
		bRet = CXFileHttpClient::DownloadFile(strUrl,strPpxmlFile);
		if (!bRet)
		{
			return FALSE;
		}
	}

	return TRUE;
}


CExBaseObject* CSensorEngineProtoSrvrBaseApp::FindDevice(const CString &strDeviceSN)
{
	//检查IotSensorSvrEngine中装置列表是否存在，不存在，则创建添加装置，模板
	CRTDeviceCtrl *pRTDeviceCtrl = g_pIotSensorSvrEngine->FindRTDeviceCtrl(strDeviceSN);

	if (pRTDeviceCtrl == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("FindRTDeviceCtrl == NULL"));
		return 0;
	}

	return pRTDeviceCtrl;
}

