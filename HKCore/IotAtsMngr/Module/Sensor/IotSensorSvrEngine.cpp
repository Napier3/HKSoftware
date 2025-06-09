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
{//����ʱ�˳��߳�
	ExitEngineThread();
}

CIotSensorSvrEngine *CIotSensorSvrEngine::Create()
{
	g_nIotSensorSvrEngineRef++;

	if (g_nIotSensorSvrEngineRef == 1)
	{
		g_pIotSensorSvrEngine = new CIotSensorSvrEngine;

		//���ݿ��ʼ��
		g_pIotSensorSvrEngine->InitMySql();
	}

	return g_pIotSensorSvrEngine;
}

void CIotSensorSvrEngine::Release()
{
	g_nIotSensorSvrEngineRef--;

	if (g_nIotSensorSvrEngineRef == 0)
	{
		//�Ͽ����ݿ�����
		g_pIotSensorSvrEngine->DisconnectDB();
		
		delete g_pIotSensorSvrEngine;
		g_pIotSensorSvrEngine = NULL;
	}
}

void CIotSensorSvrEngine::InitMySql()
{
// 	CDBServerInfoBase oServerInfo;
// 	oServerInfo.m_strHostIp = _T("121.41.92.56");//IP
// 	oServerInfo.m_strDbName = _T("tyh");//���ݿ�����
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

//��ȡRTDeviceCtrl,û���򴴽�
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

	//ʵʱװ�ö�����ӵ�m_listRTDevice������
	pFind = new CRTDeviceCtrl();
	pFind->InitProtocol(strDeviceID,g_strDvmFilePath + strDvmFile,g_strPpxmlFilePath + strPpxmlFile,_T(""),NULL);
	m_listRTDevice.AddNewChild(pFind);

	return pFind;
}

//���ҹ�Լģ�����,û���򴴽�
CIotPpTemplate *CIotSensorSvrEngine::GetIotTemplate(const CString &strPpxmlFile)
{
	CIotPpTemplate *pFind = (CIotPpTemplate *)m_listTemplate.FindByID(strPpxmlFile);
	
	if (pFind != NULL)
	{
		return pFind;
	}

	if (!IsFileExist(strPpxmlFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("GetIotTemplate:[%s]�ļ�������"),strPpxmlFile);
		return NULL;
	}

	pFind = new CIotPpTemplate;
	if (!pFind->OpenXmlFile(strPpxmlFile,CIOTPPXmlRWKeys::g_pXmlKeys))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("GetIotTemplate:[%s]�����ļ�ʧ��"),strPpxmlFile);
		delete pFind;
		pFind = NULL;
	}

	m_listTemplate.AddNewChild(pFind);

	return pFind;
}

void CIotSensorSvrEngine::AddProcedureRun(CRTDeviceCtrl *pRTDeviceCtrlRef,CIotPpProcedure *pProcedure
					 , CExBaseList *pInterface,CDvmDataset *pDataset,const CString &strRecordMode)
{//��ӵ���ʱ����m_listTempPrcdr�У���Engine_Thread��ѭ����ͷ����m_listTempPrcdr����ӵ�m_listPrcdr��
	CAutoSimpleLock oLock(&m_oPrcdrTmpCriticSection);
	CIotPpProcedureRun *pProcedureRun = new CIotPpProcedureRun(pRTDeviceCtrlRef,pProcedure,pInterface,pDataset,strRecordMode);
	m_listTempPrcdr.AddTail(pProcedureRun);
}

//Mqtt�ͻ��˳�ʼ��
BOOL CIotSensorSvrEngine::Init(const char *pszIP,long nPort)
{
	FreePxCmmInterface();

	CIotSensorSvrEngineMqttClient *pProtocolMqttClient = new CIotSensorSvrEngineMqttClient();

	BOOL bRet = pProtocolMqttClient->Connect(pszIP,nPort, "SensorSvrEngine");

	if (bRet)
	{
		pProtocolMqttClient->SetMqttEngineRef(this);
		AttachPxCmmInterface(pProtocolMqttClient);

		//���ӷ������ɹ��󣬴�������ִ���߳�
		StartEngineThread();
	}
	else
	{
		delete pProtocolMqttClient;
	}

	return bRet;
}

/*******************************
���⣺/accnode/net/up/data
{
	"eid": "123",
	"timestamp": 1588055726772,
	"rawdata":"QTkyRTA4MkQxRjAyMzAyMDAwNDhFNkQwNDEyNTAwMDIzQzAwMEMwMDNGNTU2NDQwNTkxOA=="
}

���⣺192.168.1.61/Monitor
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
	//���µı��ģ��Ǽ��ܵģ���Ҫ����
	int ret_len;
	char *pszdec = base64_decode(pszenc, len, ret_len);
	
	CString strSensorID = sensor_pkg_get_sensorid_ex((BYTE*)pszdec);

	CRTDeviceCtrl *pDeviceCtrl = (CRTDeviceCtrl *)m_listRTDevice.FindByID(strSensorID);

	if (pDeviceCtrl != NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T(">>[%s]  %s"), strSensorID, strValue);
		//�������ģ��������ݼ������ݿ�,��ӵ�����������
		//������
		pDeviceCtrl->ProcessSensorPkg((char *)pszdec, ret_len);
	}
	else
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�Ҳ�����������SensorID = %s����ҵ���Ľ���ʧ�ܣ�"), strSensorID);

	free(pszdec);
	delete pszenc;
	CJSON_Delete(pJson);
	return 0;
}

//���Ӷ����¼��ӿ�
void CIotSensorSvrEngine::OnClose(char *pszErr)
{
	FreePxCmmInterface();

	//��������װ�ù���
//	CloseDevice(NULL);
}

//ɾ��װ��֮ǰ,ɾ�����и�װ�õĹ���
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
		//����װ���б�ɾ���Ѿ����Ϊ��ɾ������װ��
		//����װ���б�ѭ����ʼ��ɾ������װ�õ���Ч����
		DeleteUnvalidDeviceAndPkgs();

		{
			//һ��ѭ���󣬽����ʱ���ڹ�����ӵ��ܵĹ���������
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
			{//���̷���������������

				//Э������¼�����
				CRTDeviceCtrl *pRTDeviceCtrlRef = pProcedureRun->GetRTDeviceCtrlRef();
				if(pRTDeviceCtrlRef != NULL)
				{
					//���̽��������ؽ����¼�
					pRTDeviceCtrlRef->OnPrcdrFinished(pProcedureRun->GetResultEvent()
						,pProcedureRun->GetDatasetRef());
				}

				//��չ��̽��ձ��ģ�ֻ������ɾ����־
				pProcedureRun->DeletePkgList();
				
				//ɾ�����̽ڵ�
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

//������ݿ�ʵʱװ�ñ�����������룬���������
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

	//�����ݼ������б����Ϊ��ʽ
	GetEqualExprFromDataset(pDataset,oRtDeviceData.m_strData);
//	pDataset->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, oRtDeviceData.m_strData);
	GetLocalTime(&oRtDeviceData.m_tmTm_Update);

	if (bRet)
	{
		oRtDeviceData.DB_Update(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}
	else
	{
		//�����ڣ����ѯװ�ñ��õ�Index_device
		CString strDeviceTable;
		strDeviceTable = CIot_AtsMngrXmlRWKeys::CIot_DeviceKey();

		CIot_Device oDevice;
		strSql.Format(_T("select * from %s where %s=\"%s\" limit 1"),strDeviceTable,strSNKey,strDeviceID);

		bRet = oDevice.DB_Select_OwnEx(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys,strSql);
		if (!bRet)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("UpdateRTDeviceData:��ѯװ����Ϣ[%s]ʧ�ܣ�"),strDeviceID);
			return FALSE;
		}

		oRtDeviceData.m_nIndex_Device = oDevice.m_nIndex_Device;
		oRtDeviceData.DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL);
	}

	return TRUE;
}

//��ѯ�����������ݱ�д���Ӧ����ʷʵʱ����
BOOL CIotSensorSvrEngine::UpdateRTDeviceHisData(const CString &strDeviceID,CDvmDataset *pDataset)
{
	if (pDataset == NULL)
	{
		return FALSE;
	}
	//�ȸ���SN����ѯ��Ӧ�ı����豸
	CIot_Device oDevice;
	BOOL bRet = oDevice.QueryByDeviceSN(g_pTheMySqlApp, strDeviceID);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("++++++CIotSensorSvrEngine::UpdateRTDeviceHisData++++++oDevice.QueryByDeviceSN failed![%s]"),strDeviceID);
		return FALSE;
	}

	//�����߶�����У���ѯ���豸���͵����ߵ����ݶ���
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

//��ѯװ�ñ��ж��ǻ�������豸ʱ�����¼������
//����������ݱ��еļ�¼���ֶ���д���ݿ�ģ�ֻ��Ҫ����ʵʱ���ݼ���
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

	//�����ֶ����õ����ݿ⣬�����Ƿ����ø��豸�ļ������
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

		//���ݿ��еļ�����ݵı�ʶ����Ҫ���豸����ģ���е�IDһ��
		CDvmData *pData = (CDvmData *)pDataset->FindByID(pMonitor->m_strDataID);

		if (pData == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("++++++CIotSensorSvrEngine::UpdateMonitorData+++++ update failed! ���ݼ����������ݡ�%s��")
				, pMonitor->m_strDataID);
			continue;
		}

		pMonitor->m_strValue = pData->m_strValue;

		if (oDevice.m_strName == _T("IRW-S1071"))
		{
			//Name��¼�����ͺţ��˴�Ϊ�̸д�����
			if (pData->m_strID == _T("smokeDetector"))
			{
				if (pData->m_strValue == _T("1"))
				{
					pMonitor->m_strValue = _T("����");
				}
				else
				{
					pMonitor->m_strValue = _T("����");
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
		//�����¼�ֻ��Ի�������豸
		return FALSE;
	}

	CIot_Warning oWarning;
	oWarning.m_strSn = strDeviceID;
	oWarning.m_nIndex_Device = oDevice.m_nIndex_Device;

	//�����豸���ͣ��ж����ĸ�ָ��澯
	//��Ҳ���Դ�oDevice��m_nIndex_Device_Type��ѯiot_device_classify_type���ж�code�ֶΣ�
	//Ŀǰûiot_device_classify_type����࣬��ʱ���ù�Լģ���ID�����豸�����жϣ�

	//������ʪ�ȴ�����
	if (strDeviceType == DEVICE_CLASSIFY_TYPE_WSD)
	{
		//���ܴ���һ���豸������˶��ָ��
		//�Ӹ澯�����У��޷��ж����ĸ�ָ�걨��
		//������ʪ�ȴ�����ֱ��Ĭ�����¶ȸ澯
		CDvmData *pData = (CDvmData *)pDataset->FindByID(_T("TEMP"));

		if (pData == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("++++++�豸��%s��+++CIotSensorSvrEngine::UpdateWarningEvent  failed! ���ݼ���������TEMP��")
				, strDeviceID);
			return FALSE;
		}

		oWarning.m_fVal_Warning = CString_To_double(pData->m_strValue);
		oWarning.m_strEvent.Format(_T("�¶ȸ澯��"));
	}
	//�̸д�����
	if (strDeviceType == DEVICE_CLASSIFY_TYPE_YG)
	{
		//���ܴ���һ���豸������˶��ָ��
		//�Ӹ澯�����У��޷��ж����ĸ�ָ�걨��
		//������ʪ�ȴ�����ֱ��Ĭ�����¶ȸ澯
		CDvmData *pData = (CDvmData *)pDataset->FindByID(_T("smokeDetector"));

		if (pData == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("++++++�豸��%s��+++CIotSensorSvrEngine::UpdateWarningEvent  failed! ���ݼ���������smokeDetector��")
				, strDeviceID);
			return FALSE;
		}

		oWarning.m_fVal_Warning = CString_To_double(pData->m_strValue);
		oWarning.m_strEvent.Format(_T("�̸и澯��"));
	}
	//����������
	if (strDeviceType == DEVICE_CLASSIFY_TYPE_ZS)
	{
		//���ܴ���һ���豸������˶��ָ��
		//�Ӹ澯�����У��޷��ж����ĸ�ָ�걨��
		//������ʪ�ȴ�����ֱ��Ĭ�����¶ȸ澯
		CDvmData *pData = (CDvmData *)pDataset->FindByID(_T("Noise"));

		if (pData == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("++++++�豸��%s��+++CIotSensorSvrEngine::UpdateWarningEvent  failed! ���ݼ���������Noise��")
				, strDeviceID);
			return FALSE;
		}

		oWarning.m_fVal_Warning = CString_To_double(pData->m_strValue);
		oWarning.m_strEvent.Format(_T("�����澯��"));
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
	//Լ�����Сʱδ�������ݶ���
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
			//ɾ��װ��ǰ��ɾ����װ�ù����Ĺ���
			DeleteDeviceProcedureRun(p);

			m_listRTDevice.DeleteAt(prePos);
		}
		else
		{
			//ɾ����װ����Ч����
			p->DeleteUnvalidPkgs(tmCur,nValidTimeLong);
		}
	}
}