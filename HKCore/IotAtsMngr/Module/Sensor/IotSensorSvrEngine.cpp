#include "stdafx.h"
#include "IotSensorSvrEngine.h"
#include "IotSensorSvrEngineMqttClient.h"
#include "../../../Module/System/TickCount32.h"
#include "SensorProtocol/SttGlobalSensorDef.h"
#include "../Iot_AtsMngrDB/Iot_Device.h"
#include "../Iot_AtsMngrDB/Iot_RtDeviceData.h"
#include "../../../SttStudio/Module/SttGlobalDef.h"
#include "../SttMqttClientEngineConfig.h"
#include "../ProtocolBase/XEngineProtoSrvrBaseApp.h"
#include "../Iot_AtsMngrDB/Iot_Monitors.h"
#include "../Iot_AtsMngrDB/Iot_RTDeviceHisDataTitles.h"
#include "../Iot_AtsMngrDB/Iot_Warning.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotSensorSvrEngine *g_pIotSensorSvrEngine = NULL;
long g_nIotSensorSvrEngineRef = 0;

CIotSensorSvrEngine::CIotSensorSvrEngine()
{
	m_pProcedureRunThread = NULL;
	m_bExitEngineThread = FALSE;
	m_bInsertHisDataTimer = FALSE;
	m_pMsgWnd = NULL;
}

CIotSensorSvrEngine::~CIotSensorSvrEngine()
{//析构时退出线程
	ExitEngineThread();
}

CIotSensorSvrEngine *CIotSensorSvrEngine::Create()
{
	g_nIotSensorSvrEngineRef++;

	if (g_nIotSensorSvrEngineRef == 1)
	{
		g_pIotSensorSvrEngine = new CIotSensorSvrEngine;

		//数据库初始化
		g_pIotSensorSvrEngine->InitMySql();
	}

	return g_pIotSensorSvrEngine;
}

void CIotSensorSvrEngine::Release()
{
	g_nIotSensorSvrEngineRef--;

	if (g_nIotSensorSvrEngineRef == 0)
	{
		//断开数据库连接
		g_pIotSensorSvrEngine->DisconnectDB();
		
		delete g_pIotSensorSvrEngine;
		g_pIotSensorSvrEngine = NULL;
	}
}

void CIotSensorSvrEngine::InitMySql()
{
// 	CDBServerInfoBase oServerInfo;
// 	oServerInfo.m_strHostIp = _T("121.41.92.56");//IP
// 	oServerInfo.m_strDbName = _T("tyh");//数据库名称
// 	oServerInfo.m_strUserName = _T("root");
// 	oServerInfo.m_strPasswd = _T("tyh12345678");
// 	oServerInfo.m_iPort = 3306;
// 	InitMySqlDB(oServerInfo);

	CDBServerInfoBase oServerInfo;
	long nPort = 0;

	CSttMqttClientEngineConfig::GetMysqlServerIP(oServerInfo.m_strHostIp);
	CSttMqttClientEngineConfig::GetMysqlServerPort(nPort);
	oServerInfo.m_strDbName = _T("tyh");
	oServerInfo.m_strUserName = _T("root");
	/*oServerInfo.m_strPasswd = _T("123456");*/
	CSttMqttClientEngineConfig::GetMysqlServerPassword(oServerInfo.m_strPasswd);
	oServerInfo.m_iPort = nPort;
	oServerInfo.m_strEncoding = _T("utf8mb4");

	InitMySqlDB(oServerInfo);
}

CRTDeviceCtrl *CIotSensorSvrEngine::FindRTDeviceCtrl(const CString &strDeviceID)
{
	return (CRTDeviceCtrl *)m_listRTDevice.FindByID(strDeviceID);
}

//获取RTDeviceCtrl,没有则创建
CRTDeviceCtrl *CIotSensorSvrEngine::GetRTDeviceCtrl(const CString &strDeviceID
							   ,const CString &strPpxmlFile,const CString &strDvmFile)
{
	if (strDeviceID.IsEmpty() || strPpxmlFile.IsEmpty() || strDvmFile.IsEmpty())
	{
		return NULL;
	}

	if ((!IsFileExist(g_strPpxmlFilePath + strPpxmlFile)) || (!IsFileExist(g_strDvmFilePath + strDvmFile)))
	{
		return NULL;
	}

	CRTDeviceCtrl *pFind = (CRTDeviceCtrl *)m_listRTDevice.FindByID(strDeviceID);
	if (pFind != NULL)
	{
		return pFind;
	}

	//实时装置对象，添加到m_listRTDevice链表中
	pFind = new CRTDeviceCtrl();
	pFind->InitProtocol(strDeviceID,g_strDvmFilePath + strDvmFile,g_strPpxmlFilePath + strPpxmlFile,_T(""),NULL);
	m_listRTDevice.AddNewChild(pFind);

	return pFind;
}

//查找规约模板对象,没有则创建
CIotPpTemplate *CIotSensorSvrEngine::GetIotTemplate(const CString &strPpxmlFile)
{
	CIotPpTemplate *pFind = (CIotPpTemplate *)m_listTemplate.FindByID(strPpxmlFile);
	
	if (pFind != NULL)
	{
		return pFind;
	}

	if (!IsFileExist(strPpxmlFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("GetIotTemplate:[%s]文件不存在"),strPpxmlFile);
		return NULL;
	}

	pFind = new CIotPpTemplate;
	if (!pFind->OpenXmlFile(strPpxmlFile,CIOTPPXmlRWKeys::g_pXmlKeys))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("GetIotTemplate:[%s]解析文件失败"),strPpxmlFile);
		delete pFind;
		pFind = NULL;
	}

	m_listTemplate.AddNewChild(pFind);

	return pFind;
}

void CIotSensorSvrEngine::AddProcedureRun(CRTDeviceCtrl *pRTDeviceCtrlRef,CIotPpProcedure *pProcedure
					 , CExBaseList *pInterface,CDvmDataset *pDataset,const CString &strRecordMode)
{//添加到临时链表m_listTempPrcdr中，在Engine_Thread中循环开头，将m_listTempPrcdr，添加到m_listPrcdr中
	CAutoSimpleLock oLock(&m_oPrcdrTmpCriticSection);
	CIotPpProcedureRun *pProcedureRun = new CIotPpProcedureRun(pRTDeviceCtrlRef,pProcedure,pInterface,pDataset,strRecordMode);
	m_listTempPrcdr.AddTail(pProcedureRun);
}

//Mqtt客户端初始化
BOOL CIotSensorSvrEngine::Init(const char *pszIP,long nPort)
{
	FreePxCmmInterface();

	CIotSensorSvrEngineMqttClient *pProtocolMqttClient = new CIotSensorSvrEngineMqttClient();

	BOOL bRet = pProtocolMqttClient->Connect(pszIP,nPort, "SensorSvrEngine");

	if (bRet)
	{
		pProtocolMqttClient->SetMqttEngineRef(this);
		AttachPxCmmInterface(pProtocolMqttClient);

		//连接服务器成功后，创建过程执行线程
		StartEngineThread();
	}
	else
	{
		delete pProtocolMqttClient;
	}

	return bRet;
}

/*******************************
主题：/accnode/net/up/data
{
	"eid": "123",
	"timestamp": 1588055726772,
	"rawdata":"QTkyRTA4MkQxRjAyMzAyMDAwNDhFNkQwNDEyNTAwMDIzQzAwMEMwMDNGNTU2NDQwNTkxOA=="
}

主题：192.168.1.61/Monitor
{
	"eventid":"c2e4b225-af2f-4387-af68-af45cd6b5255",
	"eid":"A92E082D1F02",
	"rawdata":"qS4ILR8CMCAA0OPDQSUAAioADAB/A2RAk8o=",
	"version":2,
	"timestamp":1634891712784
}

Topic: /v1/09988a010000339/service/data
{
	"param":{
		"data":	{
		"sensorCode":	"03009a010130425",
		"timestamp":	"2022-08-15 16:36:17",
		"temp":	"23.259964",
		"humidity":	"59",
		"elecQuantity":	"3.644893"
		},
		"cmd":	" ",
		"deviceId":	"03009a010130425"
	},
	"type":	"CMD_REPORTDATA",
	"mid":	1660552577925,
	"deviceId":	"03009a010130425",
	"timestamp":	1660552577925,
	"expire":	-1,
	"sensortype":	2
}

*////////////////////////////
#include "../../../Module/API/Base64.h"
long CIotSensorSvrEngine::OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN,char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType)
{
	//shaolei 20211007
	CJSON * pJson = CJSON_Parse(pBuf);

	CJSON* pData = CJSON_GetObjectItem(pJson, "rawdata");
	if (pData == NULL)
	{
		CJSON_Delete(pJson);
		return 0;
	}

	if (pData->type != CJSON_String)
	{
		CJSON_Delete(pJson);
		return 0;
	}

	CString strValue = pData->valuestring;
	char *pszenc = NULL;
	CString_to_char(strValue, &pszenc);
	int len = strlen(pszenc); 
	//最新的报文，是加密的，需要解密
	int ret_len;
	char *pszdec = base64_decode(pszenc, len, ret_len);
	
	CString strSensorID = sensor_pkg_get_sensorid_ex((BYTE*)pszdec);

	CRTDeviceCtrl *pDeviceCtrl = (CRTDeviceCtrl *)m_listRTDevice.FindByID(strSensorID);

	if (pDeviceCtrl != NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T(">>[%s]  %s"), strSensorID, strValue);
		//解析报文，更新数据集，数据库,添加到接收链表中
		//调试用
		pDeviceCtrl->ProcessSensorPkg((char *)pszdec, ret_len);
	}
	else
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("找不到传感器【SensorID = %s】，业务报文解析失败！"), strSensorID);

	free(pszdec);
	delete pszenc;
	CJSON_Delete(pJson);
	return 0;
}

//连接断链事件接口
void CIotSensorSvrEngine::OnClose(char *pszErr)
{
	FreePxCmmInterface();

	//结束所有装置过程
//	CloseDevice(NULL);
}

//删除装置之前,删除所有该装置的过程
void CIotSensorSvrEngine::DeleteDeviceProcedureRun(CRTDeviceCtrl *pRTDeviceCtrl)
{
	POS pos = m_listPrcdr.GetHeadPosition();
	CIotPpProcedureRun *p = NULL;

	while(pos != NULL)
	{
		p = (CIotPpProcedureRun *)m_listPrcdr.GetNext(pos);

		if (p->GetRTDeviceCtrlRef() == pRTDeviceCtrl)
		{
			p->DeleteProcedureRun();
		}
	}
}

void CIotSensorSvrEngine::StartEngineThread()
{
	ExitEngineThread();

	m_listPrcdr.DeleteAll();
	m_listTempPrcdr.DeleteAll();

	m_bExitEngineThread = FALSE;

	m_pProcedureRunThread = AfxBeginThread(Engine_ProcedureRunThread,this);
	m_pProcedureRunThread->m_bAutoDelete = TRUE;
}

void CIotSensorSvrEngine::ExitEngineThread() 
{
	m_bExitEngineThread = TRUE;

	CTickCount32 oTick;

	while(m_pProcedureRunThread != NULL)
	{
		oTick.DoEvents(5);
	}
}

void CIotSensorSvrEngine::OnRunProcedure()
{
	while(!m_bExitEngineThread)
	{
		//遍历装置列表，删除已经标记为“删除”的装置
		//遍历装置列表，循环开始初删除所有装置的无效报文
		DeleteUnvalidDeviceAndPkgs();

		{
			//一次循环后，将这段时间内过程添加到总的过程链表中
			CAutoSimpleLock oLock(&m_oPrcdrTmpCriticSection);
			m_listPrcdr.AppendEx(m_listTempPrcdr);
			m_listTempPrcdr.RemoveAll();
		}
		
		POS pos = m_listPrcdr.GetHeadPosition();
		POS prePos = NULL;
		CIotPpProcedureRun *pProcedureRun = NULL;

		while(pos != NULL)
		{
			prePos = pos;
			pProcedureRun = (CIotPpProcedureRun *)m_listPrcdr.GetNext(pos);

			if (pProcedureRun->Run())
			{//过程非正常、正常结束

				//协议过程事件返回
				CRTDeviceCtrl *pRTDeviceCtrlRef = pProcedureRun->GetRTDeviceCtrlRef();
				if(pRTDeviceCtrlRef != NULL)
				{
					//过程结束，返回结束事件
					pRTDeviceCtrlRef->OnPrcdrFinished(pProcedureRun->GetResultEvent()
						,pProcedureRun->GetDatasetRef());
				}

				//清空过程接收报文，只是设置删除标志
				pProcedureRun->DeletePkgList();
				
				//删除过程节点
				m_listPrcdr.DeleteAt(prePos);
			}
		}
	}

	m_pProcedureRunThread = NULL;
}

UINT CIotSensorSvrEngine::Engine_ProcedureRunThread(LPVOID pParam)
{
	CIotSensorSvrEngine *pProtocol = (CIotSensorSvrEngine *)pParam;

	pProtocol->OnRunProcedure();

	return 0;
}

//检查数据库实时装置表，不存在则插入，存在则更新
BOOL CIotSensorSvrEngine::UpdateRTDeviceData(const CString &strDeviceID,CDvmDataset *pDataset,BOOL bWarning)
{
	CString strSql,strRtDeviceDataTable,strSNKey;
	strRtDeviceDataTable = CIot_AtsMngrXmlRWKeys::CIot_RTDeviceDataKey();
	strSNKey = CIot_AtsMngrXmlRWKeys::SnKey();

	CIot_RTDeviceData oRtDeviceData;
	strSql.Format(_T("select * from %s where %s=\"%s\" limit 1"),strRtDeviceDataTable,strSNKey,strDeviceID);
	BOOL bRet = oRtDeviceData.DB_Select_OwnEx(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys,strSql);

	oRtDeviceData.m_strSn = strDeviceID;
	oRtDeviceData.m_nIs_Warning = bWarning;
	oRtDeviceData.m_strData_Format = MQTT_DATA_FORMAT_XML;

	//将数据集参数列表解析为等式
	GetEqualExprFromDataset(pDataset,oRtDeviceData.m_strData);
//	pDataset->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, oRtDeviceData.m_strData);
	GetLocalTime(&oRtDeviceData.m_tmTm_Update);

	if (bRet)
	{
		oRtDeviceData.DB_Update(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}
	else
	{
		//不存在，则查询装置表，得到Index_device
		CString strDeviceTable;
		strDeviceTable = CIot_AtsMngrXmlRWKeys::CIot_DeviceKey();

		CIot_Device oDevice;
		strSql.Format(_T("select * from %s where %s=\"%s\" limit 1"),strDeviceTable,strSNKey,strDeviceID);

		bRet = oDevice.DB_Select_OwnEx(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys,strSql);
		if (!bRet)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("UpdateRTDeviceData:查询装置信息[%s]失败！"),strDeviceID);
			return FALSE;
		}

		oRtDeviceData.m_nIndex_Device = oDevice.m_nIndex_Device;
		oRtDeviceData.DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL);
	}

	return TRUE;
}

//查询测试曲线数据表，写入对应的历史实时数据
BOOL CIotSensorSvrEngine::UpdateRTDeviceHisData(const CString &strDeviceID,CDvmDataset *pDataset)
{
	if (pDataset == NULL)
	{
		return FALSE;
	}
	//先根据SN，查询对应的被测设备
	CIot_Device oDevice;
	BOOL bRet = oDevice.QueryByDeviceSN(g_pTheMySqlApp, strDeviceID);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("++++++CIotSensorSvrEngine::UpdateRTDeviceHisData++++++oDevice.QueryByDeviceSN failed![%s]"),strDeviceID);
		return FALSE;
	}

	//从曲线定义表中，查询该设备类型的曲线的数据定义
	CIot_RTDeviceHisDataTitles oDataTitles;
	bRet = oDataTitles.QueryRTDeviceHisDataTitlesByDeviceType(g_pTheMySqlApp, oDevice.m_nIndex_Device_Type);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("++++++CIotSensorSvrEngine::UpdateRTDeviceHisData++++++oDataTitles.QueryRTDeviceHisDataTitlesByDeviceType failed![%d]")
			,oDevice.m_nIndex_Device_Type);
		return FALSE;
	}

	bRet = oDataTitles.InsertRtDeviceHisData(g_pTheMySqlApp, strDeviceID, pDataset);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("++++++CIotSensorSvrEngine::UpdateRTDeviceHisData++++++oDataTitles.InsertRtDeviceHisData failed![%s]"), strDeviceID);
		return FALSE;
	}

	return TRUE;
}

//查询装置表，判断是环境监测设备时，更新监测数据
//环境监测数据表中的记录是手动填写数据库的，只需要更新实时数据即可
BOOL CIotSensorSvrEngine::UpdateMonitorData(const CString &strDeviceID, CDvmDataset *pDataset)
{
	CIot_Device oDevice;
	BOOL bRet = FALSE;
	bRet = oDevice.QueryByDeviceSN(g_pTheMySqlApp, strDeviceID);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("++++++CIotSensorSvrEngine::UpdateMonitorData++++++oDevice.QueryByDeviceSN failed![%s]")
			, strDeviceID);
		return FALSE;
	}

	if (!oDevice.IsMonitorDevice())
	{
		return FALSE;
	}

	CIot_Monitors oMonitors;

	//根据手动配置的数据库，查找是否配置该设备的监测数据
	bRet = oMonitors.QueryMonitorssByIndexDevice(g_pTheMySqlApp, oDevice.m_nIndex_Device);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("++++++CIotSensorSvrEngine::UpdateMonitorData++++++oMonitor.QueryByDeviceIndex failed![%d]")
			, oDevice.m_nIndex_Device);
		return FALSE;
	}

	POS pos = oMonitors.GetHeadPosition();
	CIot_Monitor *pMonitor = NULL;

	while (pos != NULL)
	{
		pMonitor = (CIot_Monitor *)oMonitors.GetNext(pos);

		//数据库中的监测数据的标识，需要与设备数据模型中的ID一致
		CDvmData *pData = (CDvmData *)pDataset->FindByID(pMonitor->m_strDataID);

		if (pData == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("++++++CIotSensorSvrEngine::UpdateMonitorData+++++ update failed! 数据集不存在数据【%s】")
				, pMonitor->m_strDataID);
			continue;
		}

		pMonitor->m_strValue = pData->m_strValue;

		if (oDevice.m_strName == _T("IRW-S1071"))
		{
			//Name记录的是型号，此处为烟感传感器
			if (pData->m_strID == _T("smokeDetector"))
			{
				if (pData->m_strValue == _T("1"))
				{
					pMonitor->m_strValue = _T("有烟");
				}
				else
				{
					pMonitor->m_strValue = _T("无烟");
				}
			}
		}
		CString strUnit = pData->m_strUnit;

		if (strUnit.IsEmpty())
		{
			CDvmValue *pValue = (CDvmValue *)pData->FindByID(_T("Unit"));

			if (pValue != NULL)
			{
				strUnit = pValue->m_strValue;
			}
		}

		if (!strUnit.IsEmpty())
		{
			pMonitor->m_strUnit = strUnit;
		}

		pMonitor->DB_Update(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);;
	}

	return TRUE;
}

BOOL CIotSensorSvrEngine::UpdateWarningEvent(const CString &strDeviceType, const CString &strDeviceID, CDvmDataset *pDataset)
{
	CIot_Device oDevice;
	BOOL bRet = FALSE;
	bRet = oDevice.QueryByDeviceSN(g_pTheMySqlApp, strDeviceID);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("++++++CIotSensorSvrEngine::UpdateWarningEvent++++++oDevice.QueryByDeviceSN failed![%s]")
			, strDeviceID);
		return FALSE;
	}

	if (!oDevice.IsMonitorDevice())
	{
		//报警事件只针对环境监测设备
		return FALSE;
	}

	CIot_Warning oWarning;
	oWarning.m_strSn = strDeviceID;
	oWarning.m_nIndex_Device = oDevice.m_nIndex_Device;

	//根据设备类型，判断是哪个指标告警
	//（也可以从oDevice的m_nIndex_Device_Type查询iot_device_classify_type表，判断code字段，
	//目前没iot_device_classify_type表的类，暂时先用规约模板的ID进行设备类型判断）

	//无线温湿度传感器
	if (strDeviceType == DEVICE_CLASSIFY_TYPE_WSD)
	{
		//可能存在一个设备，监测了多个指标
		//从告警报文中，无法判断是哪个指标报警
		//无线温湿度传感器直接默认是温度告警
		CDvmData *pData = (CDvmData *)pDataset->FindByID(_T("TEMP"));

		if (pData == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("++++++设备【%s】+++CIotSensorSvrEngine::UpdateWarningEvent  failed! 数据集不包含【TEMP】")
				, strDeviceID);
			return FALSE;
		}

		oWarning.m_fVal_Warning = CString_To_double(pData->m_strValue);
		oWarning.m_strEvent.Format(_T("温度告警！"));
	}
	//烟感传感器
	if (strDeviceType == DEVICE_CLASSIFY_TYPE_YG)
	{
		//可能存在一个设备，监测了多个指标
		//从告警报文中，无法判断是哪个指标报警
		//无线温湿度传感器直接默认是温度告警
		CDvmData *pData = (CDvmData *)pDataset->FindByID(_T("smokeDetector"));

		if (pData == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("++++++设备【%s】+++CIotSensorSvrEngine::UpdateWarningEvent  failed! 数据集不包含【smokeDetector】")
				, strDeviceID);
			return FALSE;
		}

		oWarning.m_fVal_Warning = CString_To_double(pData->m_strValue);
		oWarning.m_strEvent.Format(_T("烟感告警！"));
	}
	//噪声传感器
	if (strDeviceType == DEVICE_CLASSIFY_TYPE_ZS)
	{
		//可能存在一个设备，监测了多个指标
		//从告警报文中，无法判断是哪个指标报警
		//无线温湿度传感器直接默认是温度告警
		CDvmData *pData = (CDvmData *)pDataset->FindByID(_T("Noise"));

		if (pData == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("++++++设备【%s】+++CIotSensorSvrEngine::UpdateWarningEvent  failed! 数据集不包含【Noise】")
				, strDeviceID);
			return FALSE;
		}

		oWarning.m_fVal_Warning = CString_To_double(pData->m_strValue);
		oWarning.m_strEvent.Format(_T("噪声告警！"));
	}

	return oWarning.DB_Insert(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
}

void CIotSensorSvrEngine::PostRTDeviceHisDataMessage(CRTDeviceCtrl *pDeviceCtrl)
{
	if (m_pMsgWnd == NULL)
	{
		return;
	}

	pDeviceCtrl->m_bInsertHisDataTimer = TRUE;

	if (m_bInsertHisDataTimer)
	{
		return;
	}

	m_bInsertHisDataTimer = TRUE;
	m_pMsgWnd->PostMessage(WM_ID_INSERT_RTDEVICEHISDATA, 0, 0);
}

void CIotSensorSvrEngine::DeleteUnvalidDeviceAndPkgs()
{
	//约定半个小时未处理数据丢弃
	long nValidTimeLong = 1800000;
	SYSTEMTIME tmCur;
	GetLocalTime(&tmCur);

	POS pos = m_listRTDevice.GetHeadPosition();
	POS prePos = NULL;
	CRTDeviceCtrl *p = NULL;
	
	while(pos != NULL)
	{
		prePos = pos;
		p = (CRTDeviceCtrl *)m_listRTDevice.GetNext(pos);

		if (p->m_bCanDelete)
		{
			//删除装置前，删除该装置关联的过程
			DeleteDeviceProcedureRun(p);

			m_listRTDevice.DeleteAt(prePos);
		}
		else
		{
			//删除该装置无效报文
			p->DeleteUnvalidPkgs(tmCur,nValidTimeLong);
		}
	}
}