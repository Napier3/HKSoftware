#include "stdafx.h"
#include "SensorEngineProtoSvrBase.h"
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

CString g_strDvmFilePath = _T("");
CString g_strPpxmlFilePath = _T("");

CSensorEngineProtoSvrBase *g_pSensorEngineProtoSvrBase = NULL;

CSensorEngineProtoSvrBase::CSensorEngineProtoSvrBase()
{

}

CSensorEngineProtoSvrBase::~CSensorEngineProtoSvrBase()
{

}

void CSensorEngineProtoSvrBase::InitSensorEngineProtoSvrBase()
{
	CDataMngrXmlRWKeys::Create();
	CCfgDataMngrXmlRWKeys::Create();
	CCfgDataMngrConstGlobal::Create();
	CSttCmdDefineXmlRWKeys::Create();
	CIot_AtsMngrXmlRWKeys::Create();
	CIOTPPXmlRWKeys::Create();
	CEngineToPxFactory::Create();

	//Http文件传输模块初始化
	CXFileHttpClient::InitXFileHttpClient();

	//注册协议转换模块
	CEngineToPxFactory::RegisterEngineToPx(ENGINE_TO_PX_IOTXML,CIotEngineToSensor::CreateEngineToPx);

	//配置文件初始化
	CString strFile = _P_GetConfigPath();
	strFile += _T("SttMqttClientEngineCfg.xml");
	CSttMqttClientEngineConfig::Create(strFile);

	//全局唯一传感器服务引擎
	CIotSensorSvrEngine::Create();

	//规约引擎服务模型文件和规约模板文件管理路径
	g_strDvmFilePath = _P_GetLibraryPath();
	g_strPpxmlFilePath = _P_GetLibraryPath();

	//数据库初始化
	//InitMySql();

	CString strIP;
	long nPort = 0;
	CSttMqttClientEngineConfig::GetMqttServerIP(strIP);
	CSttMqttClientEngineConfig::GetMqttServerPort(nPort);

	//两个Mqtt客户端模块初始化【连接服务器和订阅主题】
	m_oIotEngineMqttServer.Init(strIP,nPort);
	g_pIotSensorSvrEngine->Init(strIP,nPort);
}

void CSensorEngineProtoSvrBase::ExitSensorEngineProtoSvrBase()
{
	CIotSensorSvrEngine::Release();
	CEngineToPxFactory::Release();
	CSttMqttClientEngineConfig::Release();

	CIOTPPXmlRWKeys::Release();
	CIot_AtsMngrXmlRWKeys::Release();
	CSttCmdDefineXmlRWKeys::Release();
	CCfgDataMngrConstGlobal::Release();
	CCfgDataMngrXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();

	//断开连接
	//DisconnectDB();

	CXFileHttpClient::ExitXFileHttpClient();
}

// void CSensorEngineProtoSvrBase::InitMySql()
// {
// // 	CDBServerInfoBase oServerInfo;
// // 	oServerInfo.m_strHostIp = _T("121.41.92.56");//IP
// // 	oServerInfo.m_strDbName = _T("tyh");//数据库名称
// // 	oServerInfo.m_strUserName = _T("root");
// // 	oServerInfo.m_strPasswd = _T("tyh12345678");
// // 	oServerInfo.m_iPort = 3306;
// // 	InitMySqlDB(oServerInfo);
// 
// 	CDBServerInfoBase oServerInfo;
// 	long nPort = 0;
// 
// 	CSttMqttClientEngineConfig::GetMysqlServerIP(oServerInfo.m_strHostIp);
// 	CSttMqttClientEngineConfig::GetMysqlServerPort(nPort);
// 	oServerInfo.m_strDbName = _T("tyh");
// 	oServerInfo.m_strUserName = _T("root");
// 	oServerInfo.m_strPasswd = _T("123456");
// 	oServerInfo.m_iPort = nPort;
// 
// 	InitMySqlDB(oServerInfo);
// }

/*********************************
第一步：检查文件是否存在，若存在，则返回TRUE，若不存在，执行第二步
第二步：查询装置表，及规约引擎表，下载文件
***********************************/
BOOL CSensorEngineProtoSvrBase::CheckDeviceInfo(const CString &strDeviceID
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