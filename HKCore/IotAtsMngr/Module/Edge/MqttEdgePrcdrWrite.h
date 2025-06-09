#pragma once

#include "MqttEdgePrcdrBase.h"

class CMqttEdgePrcdrWrite : public CMqttEdgePrcdrBase
{
public:
	CMqttEdgePrcdrWrite();
	virtual ~CMqttEdgePrcdrWrite();

public:
	//循环执行，判断超时或发送报文，过程结束返回TRUE
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
	//以下json通用生成
	BOOL RunProcedure_Cmd_Status_Query(const CString& strProcedureID);

	//以下业务
	BOOL OnRunProcedure_Service(CString& strProcedureID, CExBaseList* pData = NULL, CDvmValue* pValue = NULL);
	BOOL RunProcedure_Svr_Cmd_Service(CString& strProcedureID, CExBaseList* pData = NULL, CDvmValue* pValue = NULL);
	BOOL RunProcedure_Svr_Cmd_Profile(CString& strProcedureID);

	//以下设备
	BOOL OnRunProcedure_Device(CString& strProcedureID, CEdgeCmd* pCmd = NULL);
	////设备升级流程
	BOOL RunProcedure_Device_Cmd_Sys_Upgrade(CString& strProcedureID);
	BOOL RunProcedure_Device_Cmd_Sys_Log(CString& strProcedureID);
	////设备管理参数修改流程
	BOOL RunProcedure_Device_Cmd_Sys_Set_Config(CString& strProcedureID);
	////设备时间同步流程
	BOOL RunProcedure_Device_Cmd_Datetime_Syn(CString& strProcedureID);
	////端设备相关
	BOOL RunProcedure_Device_Cmd_Topo_Add(CString& strProcedureID, CEdgeCmd* pCmd);
	BOOL RunProcedure_Device_Cmd_Topo_Delete(CString& strProcedureID, CEdgeCmd* pCmd);
	BOOL RunProcedure_Device_Cmd_Topo_Update(CString& strProcedureID, CEdgeCmd* pCmd);
	BOOL RunProcedure_Device_Event_HeartBeat(CString& strProcedureID);

	//以下容器
	BOOL OnRunProcedure_Container(CString& strProcedureID);
	BOOL RunProcedure_Container_Cmd_Con_Install(CString& strProcedureID);
	BOOL RunProcedure_Container_Cmd_Con_Control(CString& strProcedureID);
	BOOL RunProcedure_Container_Cmd_Con_Stop(CString& strProcedureID);
	BOOL RunProcedure_Container_Cmd_Con_Remove(CString& strProcedureID);
	BOOL RunProcedure_Container_Cmd_Con_Set_Config(CString& strProcedureID);
	BOOL RunProcedure_Container_Cmd_Con_Upgrade(CString& strProcedureID);
	BOOL RunProcedure_Container_Cmd_Con_Log(CString& strProcedureID);

	//以下应用
	BOOL OnRunProcedure_App(CString& strProcedureID);
	BOOL RunProcedure_App_Cmd_App_Upgrade(CString& strProcedureID);
	BOOL RunProcedure_App_Cmd_App_Install(CString& strProcedureID);
	BOOL RunProcedure_App_Cmd_App_X(CString& strProcedureID);
	BOOL RunProcedure_App_Cmd_App_Set_Config(CString& strProcedureID);
	BOOL RunProcedure_App_Cmd_App_Log(CString& strProcedureID);
	BOOL RunProcedure_App_Query(CString& strProcedureID);
};