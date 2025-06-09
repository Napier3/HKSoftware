#include "stdafx.h"
#include "MqttEdgePrcdrRead.h"
#include "EdgeCmd/EdgeGlobalDef.h"
#include "../IotEngineGlobalDef.h"
#include "EdgeEngineProtoSvrBaseApp.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

CMqttEdgePrcdrRead::CMqttEdgePrcdrRead()
{
	
}

CMqttEdgePrcdrRead::~CMqttEdgePrcdrRead()
{

}

/******************
������ȡ����״̬����
�������̣���ʼ��״̬Ϊ��PrcdrState_Step_NULL��
���Ͷ������������ʱ����״̬ΪPrcdrState_Step_1
�ȴ���ʱ���յ�Ӧ�������رն�ʱ����״̬ΪPrcdrState_Step_End
******************/
//ѭ��ִ�У��жϳ�ʱ���ͱ��ģ����̽�������TRUE
BOOL CMqttEdgePrcdrRead::Run()
{
	BOOL bRet = FALSE;

	switch(m_nProcedureState)
	{
	case PrcdrState_Step_NULL:
		//���Ͷ�������ó�ʱ��״̬��ΪPrcdrState_Step_1
		RunStepNull();
		break;
	case PrcdrState_Step_1:
		//����Ƿ�ʱ������ʱ���رն�ʱ����״̬��ΪPrcdrState_Step_End,EventID
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

BOOL CMqttEdgePrcdrRead::RunStepNull()
{
	if (edge_GetCmdTypeID(m_strID) == EDGE_CMD_STR_TYPE_ID_device
		|| edge_GetCmdTypeID(m_strID) == EDGE_CMD_STR_TYPE_ID_topo)
		OnRunProcedure_Device(m_strID);
	else if(edge_GetCmdTypeID(m_strID) ==  EDGE_CMD_STR_TYPE_ID_service)
		OnRunProcedure_Service(m_strID);
	else if (edge_GetCmdTypeID(m_strID) ==  EDGE_CMD_STR_TYPE_ID_container)
		OnRunProcedure_Container(m_strID);
	else if (edge_GetCmdTypeID(m_strID) ==  EDGE_CMD_STR_TYPE_ID_app)
		OnRunProcedure_App(m_strID);

	//�������ó�ʱ
	ResetTimer();
	SetProcedureState(PrcdrState_Step_1);

	return FALSE;
}

BOOL CMqttEdgePrcdrRead::RunStep1()
{
	//����Ƿ�ʱ
	if (IsTimerOut(GetTickCount()))
	{
		SetResultEvent(RUNPROCEDURE_EVENT_CommOverTime);
		SetProcedureState(PrcdrState_Step_End);
		return TRUE;
	}

	//�������б�,����ǰӦ���ģ�����TRUE,���򷵻�FALSE
	return ProcessRecvPkgs();
}

//����Ӧ�����߼�
BOOL CMqttEdgePrcdrRead::ProcessPackageDetail(CPxPkgBase *pPkgDetail)
{
	CEdgeCmd* pEdgeCmd = (CEdgeCmd*)pPkgDetail;

	if(!pEdgeCmd->GetEdgeParam())
	{
		return FALSE;
	}

	if(pEdgeCmd->m_strDeviceId == m_strDeviceID
		|| pEdgeCmd->m_strDeviceId == m_pPxProtocolRef->m_strDeviceID)
	{
		CString strCmdParasID;
		CEdgeParaData* pParasType = (CEdgeParaData*)pEdgeCmd->GetEdgeParam()->FindByID(EDGE_PROCEDURE_VAR_cmd);
		if(pParasType)
		{
			strCmdParasID = pParasType->m_strValue;
		}

		CString strProcedureID = edge_GetProcedureID(edge_CmdTypeID_Idx_To_Str(pEdgeCmd->m_nCmdType) ,pEdgeCmd->m_strType, strCmdParasID);
		if(m_strID == strProcedureID)
		{
			return ProcessPackageFinished(pEdgeCmd);
		}
	}
	return FALSE;
}

BOOL CMqttEdgePrcdrRead::OnRunProcedure_Service(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);
	//yzj 2021-9-28
	//ѡ��Ҫ��ȡ�Ķ��豸
	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(m_strDeviceID);
	if(pDevice)
	{	
		//�Զ�����ת��Ϊ������,��Ҫת��
		oCmd.m_strDeviceId = pDevice->m_strTopoID;
		m_strDeviceID = pDevice->m_strTopoID;
	}

	CEdgeParam* pParam = new CEdgeParam;
	pParam->AddNewData(EDGE_PROCEDURE_VAR_cmd, EDGE_PROCEDURE_VAR_cmd,
		EDGE_DATATYPE_STRING, strProcedureID);
	oCmd.SetEdgeParam(pParam);

	CEdgeParas* pParas = InitProcedure_Server(FALSE);

	pParam->SetEdgeParas(pParas);
	//UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);
	SetProcedureState(PrcdrState_Step_1);
	return TRUE;
}

BOOL CMqttEdgePrcdrRead::OnRunProcedure_Device(CString& strProcedureID)
{	
	if (strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_INFO_QUERY)
		RunProcedure_Query(strProcedureID);
	SetProcedureState(PrcdrState_Step_1);
	return TRUE;
}

BOOL CMqttEdgePrcdrRead::OnRunProcedure_Container(CString& strProcedureID)
{
	if (strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_GET_CONFIG
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_STATUS)
		RunProcedure_Query(strProcedureID);
	SetProcedureState(PrcdrState_Step_1);
	return TRUE;
}

BOOL CMqttEdgePrcdrRead::RunProcedure_Query(CString& strProcedureID)
{
	CEdgeCmd oCmd;
	CreateRunProcedureObject(strProcedureID, &oCmd);
	CEdgeParam* pParam = new CEdgeParam;
	oCmd.SetEdgeParam(pParam);
	UpdateReport(&oCmd);
	m_pPxCmmInterface->Send(&oCmd);
	return TRUE;
}

BOOL CMqttEdgePrcdrRead::OnRunProcedure_App(CString& strProcedureID)
{
	SetProcedureState(PrcdrState_Step_1);
	return TRUE;
}
