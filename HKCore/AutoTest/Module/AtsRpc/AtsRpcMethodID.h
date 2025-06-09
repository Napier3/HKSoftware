#pragma once

//////////////////////////////////////////////////////////////////////////
//SmartTest RPC方法定义	
//////////////////////////////////////////////////////////////////////////

#define AtsRpc_Method_IsSmartTestExist ("IsSmartTestExist")
#define AtsRpc_Method_ExitSmartTest ("ExitSmartTest")

#define AtsRpc_Method_InitSmartTestClient ("InitSmartTestClient")

#define AtsRpc_Method_CreateTest ("CreateTest")

#define AtsRpc_Method_BeginTest ("BeginTest")

#define AtsRpc_Method_StopTest ("StopTest")

#define AtsRpc_Method_TestAllInlegibleItems ("TestAllInlegibleItems")

#define AtsRpc_Method_TestPoint ("TestPoint")

#define AtsRpc_Method_TestBelow ("TestBelow")
	
#define AtsRpc_Method_CloseTest ("CloseTest")

#define AtsRpc_Method_ExportRpt ("ExportRpt")

#define AtsRpc_Method_ViewItemRpt ("ViewItemRpt")

#define AtsRpc_Method_GetAllTestItems ("GetAllTestItems")

#define AtsRpc_Method_GetTestItemReport ("GetTestItemReport")
		
#define AtsRpc_Method_TestItem ("TestItem")
		
#define AtsRpc_Method_GetDvmDatas ("GetDvmDatas")

#define AtsRpc_Method_GetReportFiles ("GetReportFiles")

#define AtsRpc_Method_ExecCmd ("ExecCmd")

#define AtsRpc_Method_GbDevWzdAuto ("GbDevWzdAuto")

#define AtsRpc_Method_OpenGbrptFile ("OpenGbrptFile")

//////////////////////////////////////////////////////////////////////////
//测试远程控制端方法RPC定义
//////////////////////////////////////////////////////////////////////////

#define AtsRpc_Method_OnItemStateChanged ("OnItemStateChanged")

#define AtsRpc_Method_OnLogPrint ("OnLogPrint")

#define AtsRpc_Method_OnTestFinished ("OnTestFinished")

#define AtsRpc_Method_OnTestStoped ("OnTestStoped")

#define AtsRpc_Method_OnTestAppEvent ("OnTestAppEvent")

#define AtsRpc_Method_OnEngineEvent ("OnEngineEvent")

#define AtsRpc_Method_SmartTestCreated ("SmartTestCreated")

#define AtsRpc_Method_OnExportRptFinished ("OnExportRptFinished")

#define AtsRpc_Method_GbDevCreated ("GbDevCreated")

#define AtsRpc_Method_GbDevFinished ("GbDevFinished")

#define AtsRpc_Method_OnConnectDeviceFailed ("OnConnectDeviceFailed")

#define AtsRpc_Method_OnGbrptOpened ("OnGbrptOpened")

#define AtsRpc_Method_OnGbrptOpenFailed ("OnGbrptOpenFailed")