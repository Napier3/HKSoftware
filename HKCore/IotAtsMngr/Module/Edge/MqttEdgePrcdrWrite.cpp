#include "stdafx.h"
#include "MqttEdgePrcdrWrite.h"
#include "EdgeCmd/EdgeGlobalDef.h"
#include "../IotEngineGlobalDef.h"
#include "EdgeCmd/EdgeDeviceInfos.h"
#include "EdgeCmd/EdgeAuth.h"
#include "../../../Module/MySqlApp/MySqlBaseApp.h"
#include "EdgeEngineProtoSvrBaseApp.h"
#include "EdgeCmd/EdgeDeviceStatuses.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CMqttEdgePrcdrWrite::CMqttEdgePrcdrWrite()
{

}

CMqttEdgePrcdrWrite::~CMqttEdgePrcdrWrite()
{

}

BOOL CMqttEdgePrcdrWrite::Run()
{
	BOOL bRet = FALSE;

	switch(m_nProcedureState)
	{
	case PrcdrState_Step_NULL:
		//发送读命令，设置超时，状态置为PrcdrState_Step_1
		RunStepNull();
		break;
	case PrcdrState_Step_1:
		//检查是否超时，若超时，关闭定时器，状态置为PrcdrState_Step_End,EventID
		RunStep1();
		break;
	case PrcdrState_Step_End:
		break;
	default:
		SetProcedureState(PrcdrState_Step_End);
		break; 
	}

	return IsProcedureEnd();
}

BOOL CMqttEdgePrcdrWrite::RunStepNull()
{
	//根据数据集、参数列表，拼报文发送
	if(edge_GetCmdTypeID(m_strID) ==  EDGE_CMD_STR_TYPE_ID_service)
		OnRunProcedure_Service(m_strID);
	else if (edge_GetCmdTypeID(m_strID) == EDGE_CMD_STR_TYPE_ID_device
		|| edge_GetCmdTypeID(m_strID) == EDGE_CMD_STR_TYPE_ID_topo)
		OnRunProcedure_Device(m_strID);
	else if (edge_GetCmdTypeID(m_strID) == EDGE_CMD_STR_TYPE_ID_container)
		OnRunProcedure_Container(m_strID);
	else if (edge_GetCmdTypeID(m_strID) == EDGE_CMD_STR_TYPE_ID_app)
		OnRunProcedure_App(m_strID);
	//重新设置超时
	ResetTimer();


	return FALSE;
}

BOOL CMqttEdgePrcdrWrite::RunStep1()
{
	//检查是否超时
	if (IsTimerOut(GetTickCount()))
	{
		SetResultEvent(RUNPROCEDURE_EVENT_CommOverTime);
		SetProcedureState(PrcdrState_Step_End);
		return TRUE;
	}

	//处理报文列表,若提前应答报文，返回TRUE,否则返回FALSE
	return ProcessRecvPkgs();
}

BOOL CMqttEdgePrcdrWrite::ProcessDeviceUpgrade(CEdgeCmd* pEdgeCmd)
{
// 	if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_DEV_CMD_SYS_UPGRADE
// 		|| pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_DEV_CMD_STATUS_QUERY)
// 	{
// 		//报文是升级回应或者是查询,执行查询
// 		RunProcedure_Cmd_Status_Query(EDGE_PROCEDURE_ID_DEV_CMD_STATUS_QUERY);
// 	}
// 	else if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_DEV_REP_JOB_RESULT)
// 	{
// 		ProcessPackageFinished(pEdgeCmd);
// 		return TRUE;
// 	}
// 
// 	pEdgeCmd->SetPkgState(PX_PKG_STATE_CAN_DELETE);
// 	SetProcedureState(PrcdrState_Step_1);

	if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_DEV_CMD_SYS_UPGRADE)
	{
		//报文是升级回应,执行查询
		RunProcedure_Cmd_Status_Query(EDGE_PROCEDURE_ID_DEV_CMD_STATUS_QUERY);
	}
	else if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_DEV_CMD_STATUS_QUERY)
	{
		//报文是查询回应,结束该过程
		ProcessPackageFinished(pEdgeCmd);
		return TRUE;
	}
	
	pEdgeCmd->SetPkgState(PX_PKG_STATE_CAN_DELETE);
	SetProcedureState(PrcdrState_Step_1);

	return FALSE;
}

BOOL CMqttEdgePrcdrWrite::ProcessContainerUpgrade(CEdgeCmd* pEdgeCmd)
{
// 	if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_CON_CMD_CON_UPGRADE
// 		|| pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_CON_CMD_STATUS_QUERY)
// 	{
// 		//报文是升级回应或者是查询,执行查询
// 		RunProcedure_Cmd_Status_Query(EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY);
// 	}
// 	else if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_CON_REP_JOB_RESULT)
// 	{
// 		ProcessPackageFinished(pEdgeCmd);
// 		return TRUE;
// 	}

	if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_CON_CMD_CON_UPGRADE)
	{
		//报文是升级回应,执行查询
		RunProcedure_Cmd_Status_Query(EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY);
	}
	else if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_CON_CMD_STATUS_QUERY)
	{
		//报文是查询回应,结束该过程
		ProcessPackageFinished(pEdgeCmd);
		return TRUE;
	}

	pEdgeCmd->SetPkgState(PX_PKG_STATE_CAN_DELETE);
	SetProcedureState(PrcdrState_Step_1);
	return FALSE;
}

BOOL CMqttEdgePrcdrWrite::ProcessAppUpgrade(CEdgeCmd* pEdgeCmd)
{
// 	if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_APP_CMD_APP_UPGRADE
// 		|| pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_APP_CMD_STATUS_QUERY)
// 	{
// 		//报文是升级回应或者是查询,执行查询
// 		RunProcedure_Cmd_Status_Query(EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY);
// 	}
// 	else if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_APP_REP_JOB_RESULT)
// 	{
// 		ProcessPackageFinished(pEdgeCmd);
// 		return TRUE;
// 	}

	if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_APP_CMD_APP_UPGRADE)
	{
		//报文是升级回应,执行查询
		RunProcedure_Cmd_Status_Query(EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY);
	}
	else if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_APP_CMD_STATUS_QUERY)
	{
		//报文是查询回应,结束该过程
		ProcessPackageFinished(pEdgeCmd);
		return TRUE;
	}

	pEdgeCmd->SetPkgState(PX_PKG_STATE_CAN_DELETE);
	SetProcedureState(PrcdrState_Step_1);
	return FALSE;
}

BOOL CMqttEdgePrcdrWrite::ProcessContainerInstall(CEdgeCmd* pEdgeCmd)
{
// 	if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_CON_CMD_CON_INSTALL
// 		|| pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_CON_CMD_STATUS_QUERY)
// 	{
// 		//报文是升级回应或者是查询,执行查询
// 		RunProcedure_Cmd_Status_Query(EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY);
// 	}
// 	else if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_CON_REP_JOB_RESULT)
// 	{
// 		ProcessPackageFinished(pEdgeCmd);
// 		return TRUE;
// 	}

	if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_CON_CMD_CON_INSTALL)
	{
		//报文是升级回应,执行查询
		RunProcedure_Cmd_Status_Query(EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY);
	}
	else if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_CON_CMD_STATUS_QUERY)
	{
		//报文是查询回应,结束该过程
		ProcessPackageFinished(pEdgeCmd);
		return TRUE;
	}

	pEdgeCmd->SetPkgState(PX_PKG_STATE_CAN_DELETE);
	SetProcedureState(PrcdrState_Step_1);
	return FALSE;
}

BOOL CMqttEdgePrcdrWrite::ProcessAppInstall(CEdgeCmd* pEdgeCmd)
{
// 	if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_APP_CMD_APP_INSTALL
// 		|| pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_APP_CMD_STATUS_QUERY)
// 	{
// 		//报文是升级回应或者是查询,执行查询
// 		RunProcedure_Cmd_Status_Query(EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY);
// 	}
// 	else if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_APP_REP_JOB_RESULT)
// 	{
// 		ProcessPackageFinished(pEdgeCmd);
// 		return TRUE;
// 	}

	if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_APP_CMD_APP_INSTALL)
	{
		//报文是升级回应,执行查询
		RunProcedure_Cmd_Status_Query(EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY);
	}
	else if(pEdgeCmd->m_strType == EDGE_CMD_INFO_Type_APP_CMD_STATUS_QUERY)
	{
		//报文是查询回应,结束该过程
		ProcessPackageFinished(pEdgeCmd);
		return TRUE;
	}

	pEdgeCmd->SetPkgState(PX_PKG_STATE_CAN_DELETE);
	SetProcedureState(PrcdrState_Step_1);
	return FALSE;
}

BOOL CMqttEdgePrcdrWrite::ProcessPackageDetail(CPxPkgBase *pPkgDetail)
{
	CEdgeCmd* pEdgeCmd = (CEdgeCmd*)pPkgDetail;
	if(pEdgeCmd->m_strDeviceId == m_strDeviceID)
	{
		//确认报文属于当前装置
		//确认流程报文类型
		if(m_pRefDataset->m_strID == EDGE_DATASET_ID_DEV_UpGrade)
		{
			return ProcessDeviceUpgrade(pEdgeCmd);
		}
		else if(m_pRefDataset->m_strID == EDGE_DATASET_ID_CON_Upgrade)
		{
			return ProcessContainerUpgrade(pEdgeCmd);
		}
		else if(m_pRefDataset->m_strID == EDGE_DATASET_ID_APP_Upgrade)
		{
			return ProcessAppUpgrade(pEdgeCmd);
		}
		else if(m_pRefDataset->m_strID == EDGE_DATASET_ID_CON_Install)
		{
			return ProcessContainerInstall(pEdgeCmd);
		}
		else if(m_pRefDataset->m_strID == EDGE_DATASET_ID_APP_Install)
		{
			return ProcessAppInstall(pEdgeCmd);
		}
		else
		{
			//非特殊报文则使用strID做判断即可
			CString strProcedureID = edge_GetProcedureID(edge_CmdTypeID_Idx_To_Str(pEdgeCmd->m_nCmdType) ,pEdgeCmd->m_strType, m_strID);
			if(m_strID == strProcedureID)
			{
				return ProcessPackageFinished(pEdgeCmd);
			}
		}
	}
	return FALSE;
}

BOOL CMqttEdgePrcdrWrite::OnRunProcedure_Service(CString& strProcedureID, CExBaseList* pData /*= NULL*/, CDvmValue* pValue /*= NULL*/)
{
	if(strProcedureID == EDGE_PROCEDURE_ID_parameter_Get		
		||strProcedureID == EDGE_PROCEDURE_ID_parameter_Set		
		||strProcedureID == EDGE_PROCEDURE_ID_parameter_Activate
		||strProcedureID == EDGE_PROCEDURE_ID_parameter_Cancel	
		||strProcedureID == EDGE_PROCEDURE_ID_discrete_Get		
		||strProcedureID == EDGE_PROCEDURE_ID_analog_Get		
		||strProcedureID == EDGE_PROCEDURE_ID_accumulator_Get	
		||strProcedureID == EDGE_PROCEDURE_ID_APPDir_Get		
		||strProcedureID == EDGE_PROCEDURE_ID_APPHFile_Get		
		||strProcedureID == EDGE_PROCEDURE_ID_timeRead			
		||strProcedureID == EDGE_PROCEDURE_ID_timeCheck			
		||strProcedureID == EDGE_PROCEDURE_ID_commad_HZ			
		||strProcedureID == EDGE_PROCEDURE_ID_commad_TZ			
		||strProcedureID == EDGE_PROCEDURE_ID_commad_ModelCtrl	
		||strProcedureID == EDGE_PROCEDURE_ID_APP_CONFIG_Dir_Get
		||strProcedureID == EDGE_PROCEDURE_ID_CMD_GET_APP_CONFIG
		||strProcedureID == EDGE_PROCEDURE_ID_CMD_SET_APP_CONFIG)
		RunProcedure_Svr_Cmd_Service(strProcedureID, pData, pValue);
	else if(strProcedureID == EDGE_PROCEDURE_ID_SVR_CMD_PROFILE)
		RunProcedure_Svr_Cmd_Profile(strProcedureID);
	SetProcedureState(PrcdrState_Step_1);
	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_Svr_Cmd_Profile(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_deviceIds, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_modelData, EDGE_DATATYPE_LONG);
	CDvmData* pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_file);
	pParam->SetEdgeFile(AddEdgeFile(pData));
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);
	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_Svr_Cmd_Service(CString& strProcedureID, CExBaseList* pData /*= NULL*/, CDvmValue* pValue /*= NULL*/)
{	
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);
	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(m_strDeviceID);
	if(pDevice)
	{	
		oCmd.m_strDeviceId = pDevice->m_strTopoID;
		m_strDeviceID = pDevice->m_strTopoID;
	}

	if(CDvmData* pAppData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_app))
	{
		oCmd.m_strApp = pAppData->m_strValue;
	}

	CEdgeParam* pParam = new CEdgeParam;
	pParam->AddNewData(EDGE_PROCEDURE_VAR_cmd, EDGE_PROCEDURE_VAR_cmd,
		EDGE_DATATYPE_STRING, strProcedureID);
	oCmd.SetEdgeParam(pParam);

	if (strProcedureID == EDGE_PROCEDURE_CMD_ID_CMD_SET_APP_CONFIG
		|| strProcedureID == EDGE_PROCEDURE_CMD_ID_CMD_GET_APP_CONFIG)
	{
		CEdgeParas* pParas = new CEdgeParas;
		CEdgeBody* pBody = new CEdgeBody;
		CDvmData* pData = NULL;
		if(pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_fileDir))
			pBody->m_strFileDir = pData->m_strValue;
		if(pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_fileName))
			pBody->m_strFileName = pData->m_strValue;
		if(pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_fileSize))
			pBody->m_nFileSize = CString_To_long(pData->m_strValue);
		if(pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_Content))
			pBody->m_strContent = pData->m_strValue;
		pParam->SetEdgeParas(pParas);
		pParas->SetEdgeBody(pBody);
	}
	else 
	{
		pParam->SetEdgeParas(InitProcedure_Server(TRUE));
	}
	//UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);
	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::OnRunProcedure_Device(CString& strProcedureID, CEdgeCmd* pCmd)
{	
	if (strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_SET_CONFIG)
		RunProcedure_Device_Cmd_Sys_Set_Config(strProcedureID);
	else if(strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_UPGRADE)
		RunProcedure_Device_Cmd_Sys_Upgrade(strProcedureID);
	else if (strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_DATETIME_SYN)
		RunProcedure_Device_Cmd_Datetime_Syn(strProcedureID);
	else if (strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_LOG)
		RunProcedure_Device_Cmd_Sys_Log(strProcedureID);
	else if(strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_ADD)
		RunProcedure_Device_Cmd_Topo_Add(strProcedureID, pCmd);
	else if(strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_DEL)
		RunProcedure_Device_Cmd_Topo_Delete(strProcedureID, pCmd); 
	else if(strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_UPDATE)
		RunProcedure_Device_Cmd_Topo_Update(strProcedureID, pCmd); 
	else if (strProcedureID == EDGE_PROCEDURE_ID_DEV_EVENT_HEARTBEAT)
		RunProcedure_Device_Event_HeartBeat(strProcedureID); 
	SetProcedureState(PrcdrState_Step_1);
	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_Cmd_Status_Query(const CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_jobId, EDGE_DATATYPE_LONG);
	UpdateReport(&oCmd, TRUE);
	m_pPxCmmInterface->Send(&oCmd);

	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_Device_Cmd_Sys_Log(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_url, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_logType, EDGE_DATATYPE_LONG);
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);
	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_Device_Cmd_Sys_Set_Config(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_devName, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_cpuLmt, EDGE_DATATYPE_LONG);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_memLmt, EDGE_DATATYPE_LONG);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_diskLmt, EDGE_DATATYPE_LONG);

	CDvmData* pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_repPeriod);
	pParam->SetEdgeRepPeriod(AddEdgeRepPeriod(pData));
	pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_temperature);
	pParam->SetEdgeTemperature(AddEdgeTemperature(pData));
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);
	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_Device_Cmd_Sys_Upgrade(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_jobId, EDGE_DATATYPE_LONG);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_policy, EDGE_DATATYPE_LONG);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_version, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_upgradeType, EDGE_DATATYPE_LONG);
	CDvmData* pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_file);
	pParam->SetEdgeFile(AddEdgeFile(pData));

	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);
	
	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_Device_Cmd_Datetime_Syn(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_dateTime, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_timeZone, EDGE_DATATYPE_STRING);
	UpdateReport(&oCmd);	
	m_pPxCmmInterface->Send(&oCmd);

	return TRUE;
}


BOOL CMqttEdgePrcdrWrite::RunProcedure_Device_Cmd_Topo_Add(CString& strProcedureID, CEdgeCmd* pCmd)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);
	oCmd.m_nCode = 200;
	oCmd.m_nMid = pCmd->m_nMid;

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	CJSON* pJson = CJSON_CreateArray();
	POS pos = pCmd->GetEdgeParam()->GetHeadPosition();
	while (pos)
	{
		CExBaseList* pChild = (CExBaseList*)pParam->GetNext(pos);
		if(pChild->GetClassID() == EDGECMDCLASSID_CEDGEDEVICEINFOS)
		{
			CEdgeDeviceInfos* pInfos = (CEdgeDeviceInfos*)pChild;
			CEdgeAuth oAuth;
			CString strMappingID = oAuth.QuenryTopoMappingID(pInfos->m_strNodeId, 
				pInfos->m_strModel, g_pTheMySqlApp, CEdgeCmdMngrXmlRWKeys::g_pXmlKeys);
			CEdgeData* pData = new CEdgeData;
			pData->m_strDeviceId = strMappingID;
			pData->m_strNodeId = pInfos->m_strNodeId;
			char* strJson = NULL;
			if(!strMappingID.GetLength())
			{
				pData->m_nStatusCode = 400;
				pData->GetXml_UTF8(CEdgeCmdMngrXmlRWKeys::g_pXmlKeys, &strJson, 0, _JSON_TYPE_);
				CJSON_AddItemToArray(pJson, CJSON_Parse(strJson));
				delete strJson;
				continue;
			}
			
			pData->m_nStatusCode = 200;	
			pData->GetXml_UTF8(CEdgeCmdMngrXmlRWKeys::g_pXmlKeys, &strJson, 0, _JSON_TYPE_);
			CJSON_AddItemToArray(pJson, CJSON_Parse(strJson));
			delete strJson;

			//yzj 2021-9-28 更新边设备内部的端设备ID
			CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(m_strDeviceID);
			pDevice->m_bIsOnline = TRUE;
			pDevice->m_listTopoDevice.AddNew(pData->m_strNodeId, pData->m_strDeviceId);
		}
	}
	pParam->SetDeviceDataJson(pJson);

	UpdateReport_Topo(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);

	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_Device_Cmd_Topo_Delete(CString& strProcedureID, CEdgeCmd* pCmd)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);
	oCmd.m_nCode = 200;
	oCmd.m_nMid = pCmd->m_nMid;

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	CJSON* pChild = pCmd->GetEdgeParam()->GetDeviceIdsJson();
	if(!pChild)
	{
		return FALSE;
	}
	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(m_strDeviceID);
	if(!pDevice)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, ("融合终端[%s]未接入,请重新连接!"), m_strDeviceID);
		return FALSE;
	}

	CJSON* pJson = CJSON_CreateArray();
	pChild = pChild->child;
	while (pChild)
	{
		CExBaseList* pTopo = (CExBaseList*)pDevice->m_listTopoDevice.FindByID(pChild->valuestring);
		if(pTopo)
		{
			CEdgeData oData;
			oData.m_nStatusCode = 200;
			oData.m_strNodeId = pTopo->m_strName;
			oData.m_strDeviceId = pTopo->m_strID;
			pDevice->m_listTopoDevice.DeleteByID(pChild->valuestring);
			char* strJson = NULL;
			oData.GetXml_UTF8(CEdgeCmdMngrXmlRWKeys::g_pXmlKeys, &strJson, 0, _JSON_TYPE_);
			CJSON_AddItemToArray(pJson, CJSON_Parse(strJson));
			delete strJson;
		}

		pChild = pChild->next;
	}

	pParam->SetDeviceDataJson(pJson);

	UpdateReport_Topo(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);

	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_Device_Cmd_Topo_Update(CString& strProcedureID, CEdgeCmd* pCmd)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);
	oCmd.m_nCode = 200;
	oCmd.m_nMid = pCmd->m_nMid;

	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(m_strDeviceID);
	if(!pDevice)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, ("融合终端[%s]未接入,请重新连接!"), m_strDeviceID);
		return FALSE;
	}

	CJSON* pJson = CJSON_CreateArray();
	POS pos = pCmd->GetEdgeParam()->GetHeadPosition();
	while (pos)
	{
		CExBaseList* pChild = (CExBaseList*)pParam->GetNext(pos);
		if(pChild->GetClassID() == EDGECMDCLASSID_CEDGEDEVICESTATUSES)
		{
			CEdgeDeviceStatuses* pStatuses = (CEdgeDeviceStatuses*)pChild;
			CEdgeData* pData = new CEdgeData;
			pData->m_strDeviceId = pStatuses->m_strDeviceId;
			if(pStatuses->m_strDeviceStatus == _T("ONLINE"))
			{
				pData->m_nStatusCode = 200;
				pDevice->m_bIsOnline = TRUE;
			}
			else
			{
				pData->m_nStatusCode = 400;
				pDevice->m_bIsOnline = FALSE;
			}

			char* strJson = NULL;
			pData->GetXml_UTF8(CEdgeCmdMngrXmlRWKeys::g_pXmlKeys, &strJson, 0, _JSON_TYPE_);
			CJSON_AddItemToArray(pJson, CJSON_Parse(strJson));
			delete strJson;
		}
	}

	pParam->SetDeviceDataJson(pJson);

	UpdateReport_Topo(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);
	
	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_Device_Event_HeartBeat(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CString strTime;
	GetCurrSystemtimeString(strTime);
	oCmd.m_strID = m_strDeviceID;//报文主题的ID
	oCmd.m_strType = edge_GetCmdInfoType(strProcedureID);
	oCmd.m_strDeviceId = m_strDeviceID;//报文内部的ID
	oCmd.m_strTimestamp = strTime;
	oCmd.m_nCode = 200;
	oCmd.SetProcedureID(strProcedureID);
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);

	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::OnRunProcedure_Container(CString& strProcedureID)
{
	if(strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_INSTALL)
		RunProcedure_Container_Cmd_Con_Install(strProcedureID);
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_START
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_STOP
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_REMOVE)
		RunProcedure_Container_Cmd_Con_Control(strProcedureID);
	else if (strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_UPGRADE)
		RunProcedure_Container_Cmd_Con_Upgrade(strProcedureID);
	else if (strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_LOG)
		RunProcedure_Container_Cmd_Con_Log(strProcedureID);
	else if (strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_SET_CONFIG)
		RunProcedure_Container_Cmd_Con_Set_Config(strProcedureID);
	SetProcedureState(PrcdrState_Step_1);
	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_Container_Cmd_Con_Install(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);
	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_container, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_port, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_jobId, EDGE_DATATYPE_LONG);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_policy, EDGE_DATATYPE_LONG);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_networkMode, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_env, EDGE_DATATYPE_STRING);

	CDvmData* pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_image);
	pParam->SetEdgeImage(AddEdgeImage(pData));
	pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_withAPP);
	pParam->SetEdgeWithApp(AddEdgeWithApp(pData));
	pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_cfgCpu);
	pParam->SetEdgeCfgCpu(AddEdgeCfgCpu(pData));
	pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_cfgMem);
	pParam->SetEdgeCfgMem(AddEdgeCfgMem(pData));
	pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_cfgDisk);
	pParam->SetEdgeCfgDisk(AddEdgeCfgDisk(pData));

	CJSON* pMountJson = CJSON_CreateArray();
	pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_mount);
	GetEdgeJson(pData, pMountJson);
	pParam->SetMountJson(pMountJson);

	CJSON* pDevJson = CJSON_CreateArray();
	pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_dev);
	GetEdgeJson(pData, pDevJson);
	pParam->SetDevJson(pDevJson);

	//pMountJson和pDevJson指针将在send过程中被加入到json对象中
	//send完毕后由CJSON控制释放
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);

	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_Container_Cmd_Con_Control(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);
	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	CDvmData* pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_container);
	pParam->AddNewData(pData->m_strName, pData->m_strID, EDGE_DATATYPE_STRING, pData->m_strValue);
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);

	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_Container_Cmd_Con_Set_Config(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_container, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_port, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_networkMode, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_env, EDGE_DATATYPE_STRING);

	CDvmData* pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_cfgCpu);
	pParam->SetEdgeCfgCpu(AddEdgeCfgCpu(pData));
	pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_cfgMem);
	pParam->SetEdgeCfgMem(AddEdgeCfgMem(pData));
	pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_cfgDisk);
	pParam->SetEdgeCfgDisk(AddEdgeCfgDisk(pData));

	CJSON* pMountJson = CJSON_CreateArray();
	pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_mount);
	GetEdgeJson(pData, pMountJson);
	pParam->SetMountJson(pMountJson);

	CJSON* pDevJson = CJSON_CreateArray();
	pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_dev);
	GetEdgeJson(pData, pDevJson);
	pParam->SetDevJson(pDevJson);

	//pMountJson和pDevJson指针将在send过程中被加入到json对象中
	//send完毕后由CJSON控制释放
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);

	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_Container_Cmd_Con_Upgrade(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_container, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_version, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_jobId, EDGE_DATATYPE_LONG);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_policy, EDGE_DATATYPE_LONG);
	CDvmData* pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_file);
	pParam->SetEdgeFile(AddEdgeFile(pData));
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);
	
	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_Container_Cmd_Con_Log(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_url, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_container, EDGE_DATATYPE_STRING);
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);
	
	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::OnRunProcedure_App(CString& strProcedureID)
{
	if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_UPGRADE)
	{
		RunProcedure_App_Cmd_App_Upgrade(strProcedureID);
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_START
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_STOP
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_REMOVE
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_ENABLE
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_UNENABLE)
		RunProcedure_App_Cmd_App_X(strProcedureID);
	else if (strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_SET_CONFIG)
		RunProcedure_App_Cmd_App_Set_Config(strProcedureID);
	else if (strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_INSTALL)
		RunProcedure_App_Cmd_App_Install(strProcedureID);
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_LOG)
		RunProcedure_App_Cmd_App_Log(strProcedureID);
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_GET_CONFIG
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_STATUS)
		RunProcedure_App_Query(strProcedureID);
	SetProcedureState(PrcdrState_Step_1);
	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_App_Cmd_App_Upgrade(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_app, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_jobId, EDGE_DATATYPE_LONG);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_policy, EDGE_DATATYPE_LONG);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_container, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_version, EDGE_DATATYPE_STRING);
	CDvmData* pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_file);
	pParam->SetEdgeFile(AddEdgeFile(pData));
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);

	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_App_Cmd_App_Install(CString& strProcedureID)
{	
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_jobId, EDGE_DATATYPE_LONG);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_policy, EDGE_DATATYPE_LONG);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_container, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_version, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_enable, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_app, EDGE_DATATYPE_STRING);
	CDvmData* pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_file);
	pParam->SetEdgeFile(AddEdgeFile(pData));
	//这里的cpu、mem,4号文表达有误,以5号文为准cpu实质是cfgCpu,mem实质是cfgMem
	pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_cfgCpu);
	pParam->SetEdgeCfgCpu(AddEdgeCfgCpu(pData));
	pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_cfgMem);
	pParam->SetEdgeCfgMem(AddEdgeCfgMem(pData));
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);

	return TRUE;
}

//5种应用控制命令结构一致,使用该函数
BOOL CMqttEdgePrcdrWrite::RunProcedure_App_Cmd_App_X(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_container, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_app, EDGE_DATATYPE_STRING);
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);

	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_App_Cmd_App_Set_Config(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_container, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_app, EDGE_DATATYPE_STRING);
	CDvmData* pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_cfgCpu);
	pParam->SetEdgeCfgCpu(AddEdgeCfgCpu(pData));
	pData = (CDvmData*)m_pRefDataset->FindByID(EDGE_PROCEDURE_VAR_cfgMem);
	pParam->SetEdgeCfgMem(AddEdgeCfgMem(pData));
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);

	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_App_Cmd_App_Log(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);

	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_url, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_container, EDGE_DATATYPE_STRING);
	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_app, EDGE_DATATYPE_STRING);
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);

	return TRUE;
}

BOOL CMqttEdgePrcdrWrite::RunProcedure_App_Query(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);


	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);

// 	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(m_strDeviceID);
// 	if(pDevice)
// 	{	
// 		pParam->AddNewData(EDGE_PROCEDURE_VAR_container, EDGE_PROCEDURE_VAR_container, EDGE_DATATYPE_STRING, pDevice->m_strContainerID);
// 	}

	AddEdgeData(pParam, m_pRefDataset, EDGE_PROCEDURE_VAR_container, EDGE_DATATYPE_STRING);
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);

	return TRUE;
}