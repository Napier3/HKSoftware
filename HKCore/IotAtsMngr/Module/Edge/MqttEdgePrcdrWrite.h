#pragma once

#include "MqttEdgePrcdrBase.h"

class CMqttEdgePrcdrWrite : public CMqttEdgePrcdrBase
{
public:
	CMqttEdgePrcdrWrite();
	virtual ~CMqttEdgePrcdrWrite();

public:
	//ѭ��ִ�У��жϳ�ʱ���ͱ��ģ����̽�������TRUE
	virtual BOOL Run();

public:
	virtual BOOL RunStepNull();
	virtual BOOL RunStep1();

	virtual BOOL ProcessPackageAck(CPxPkgBase *pPkgDetail){ SetProcedureState(PrcdrState_Step_End); return FALSE;}
	virtual BOOL ProcessPackageDetail(CPxPkgBase *pPkgDetail);
	BOOL ProcessDeviceUpgrade(CEdgeCmd* pEdgeCmd);
	BOOL ProcessContainerUpgrade(CEdgeCmd* pEdgeCmd);
	BOOL ProcessAppUpgrade(CEdgeCmd* pEdgeCmd);
	BOOL ProcessContainerInstall(CEdgeCmd* pEdgeCmd);
	BOOL ProcessAppInstall(CEdgeCmd* pEdgeCmd);

public:
	//����jsonͨ������
	BOOL RunProcedure_Cmd_Status_Query(const CString& strProcedureID);

	//����ҵ��
	BOOL OnRunProcedure_Service(CString& strProcedureID, CExBaseList* pData = NULL, CDvmValue* pValue = NULL);
	BOOL RunProcedure_Svr_Cmd_Service(CString& strProcedureID, CExBaseList* pData = NULL, CDvmValue* pValue = NULL);
	BOOL RunProcedure_Svr_Cmd_Profile(CString& strProcedureID);

	//�����豸
	BOOL OnRunProcedure_Device(CString& strProcedureID, CEdgeCmd* pCmd = NULL);
	////�豸��������
	BOOL RunProcedure_Device_Cmd_Sys_Upgrade(CString& strProcedureID);
	BOOL RunProcedure_Device_Cmd_Sys_Log(CString& strProcedureID);
	////�豸��������޸�����
	BOOL RunProcedure_Device_Cmd_Sys_Set_Config(CString& strProcedureID);
	////�豸ʱ��ͬ������
	BOOL RunProcedure_Device_Cmd_Datetime_Syn(CString& strProcedureID);
	////���豸���
	BOOL RunProcedure_Device_Cmd_Topo_Add(CString& strProcedureID, CEdgeCmd* pCmd);
	BOOL RunProcedure_Device_Cmd_Topo_Delete(CString& strProcedureID, CEdgeCmd* pCmd);
	BOOL RunProcedure_Device_Cmd_Topo_Update(CString& strProcedureID, CEdgeCmd* pCmd);
	BOOL RunProcedure_Device_Event_HeartBeat(CString& strProcedureID);

	//��������
	BOOL OnRunProcedure_Container(CString& strProcedureID);
	BOOL RunProcedure_Container_Cmd_Con_Install(CString& strProcedureID);
	BOOL RunProcedure_Container_Cmd_Con_Control(CString& strProcedureID);
	BOOL RunProcedure_Container_Cmd_Con_Stop(CString& strProcedureID);
	BOOL RunProcedure_Container_Cmd_Con_Remove(CString& strProcedureID);
	BOOL RunProcedure_Container_Cmd_Con_Set_Config(CString& strProcedureID);
	BOOL RunProcedure_Container_Cmd_Con_Upgrade(CString& strProcedureID);
	BOOL RunProcedure_Container_Cmd_Con_Log(CString& strProcedureID);

	//����Ӧ��
	BOOL OnRunProcedure_App(CString& strProcedureID);
	BOOL RunProcedure_App_Cmd_App_Upgrade(CString& strProcedureID);
	BOOL RunProcedure_App_Cmd_App_Install(CString& strProcedureID);
	BOOL RunProcedure_App_Cmd_App_X(CString& strProcedureID);
	BOOL RunProcedure_App_Cmd_App_Set_Config(CString& strProcedureID);
	BOOL RunProcedure_App_Cmd_App_Log(CString& strProcedureID);
	BOOL RunProcedure_App_Query(CString& strProcedureID);
};