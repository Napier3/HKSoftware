#include "stdafx.h"

#include "AtsRpcClientMethod.h"
#include "AtsRpcClientMngr.h"

#include "AtsRpcMethodID.h"
#include "..\..\Module\zlib-1.2.8\zlib.h"


using namespace std;

CAtsRpcClient_OnItemStateChanged::CAtsRpcClient_OnItemStateChanged(XmlRpcServer* s)
	:XmlRpcServerMethod(AtsRpc_Method_OnItemStateChanged, s)
{
	
}

void CAtsRpcClient_OnItemStateChanged::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CString strTestID, strState, strID;
	int nDeviceIndex = 0, nItemIndex = 0;

	XmlRpcValue_To_String(params[0], strTestID);
	nDeviceIndex = params[1];
	nItemIndex = params[2];
	XmlRpcValue_To_String(params[3], strID);
	XmlRpcValue_To_String(params[4], strState);

	g_theAtsRpcClientMngr->OnItemStateChanged(strTestID, nDeviceIndex, nItemIndex, strID, strState);


    result = true;
}

CAtsRpcClient_OnTestFinished::CAtsRpcClient_OnTestFinished(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_OnTestFinished, s)
{
	
}

void CAtsRpcClient_OnTestFinished::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	//g_theAtsRpcClientMngr->BeginTest();
	CString strTestID;
	int nDeviceIndex, nType;
	
	XmlRpcValue_To_String(params[0], strTestID);
	nDeviceIndex = params[1];
	nType = params[2];

	g_theAtsRpcClientMngr->OnTestFinished(strTestID, nDeviceIndex, nType);


	result = true;
}

CAtsRpcClient_OnTestStoped::CAtsRpcClient_OnTestStoped(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_OnTestStoped, s)
{

}

void CAtsRpcClient_OnTestStoped::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	//g_theAtsRpcClientMngr->BeginTest();
	CString strTestID, strMsg;
	int nDeviceIndex;

	XmlRpcValue_To_String(params[0], strTestID);
	nDeviceIndex = params[1];
	XmlRpcValue_To_String(params[2], strMsg);

	g_theAtsRpcClientMngr->OnTestStoped(strTestID, nDeviceIndex, strMsg);


	result = true;
}

CAtsRpcClient_OnExportRptFinished::CAtsRpcClient_OnExportRptFinished(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_OnExportRptFinished, s)
{
	
}

void CAtsRpcClient_OnExportRptFinished::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CString strTestID;
	XmlRpcValue_To_String(params[0], strTestID);
	g_theAtsRpcClientMngr->OnExportRptFinished(strTestID);
	result = true;
}

CAtsRpcClient_OnTestAppError::CAtsRpcClient_OnTestAppError(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_OnTestAppEvent, s)
{
	
}

void CAtsRpcClient_OnTestAppError::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	//g_theAtsRpcClientMngr->StopTest();

	result = true;
}


CAtsRpcClient_OnEngineError::CAtsRpcClient_OnEngineError(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_OnEngineEvent, s)
{

}

void CAtsRpcClient_OnEngineError::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{

	result = true;
}


CAtsRpcClient_SmartTestCreated::CAtsRpcClient_SmartTestCreated(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_SmartTestCreated, s)
{

}

void CAtsRpcClient_SmartTestCreated::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	char *pBuffer = NULL, *pBufferRpt=NULL;
	long nLen = 0, nLenRpt = 0;
	CString strTestID;

	XmlRpcValue_To_String(params[0], strTestID);
	XmlRpcValue_To_Buffer(params[1], &pBuffer, nLen);
	XmlRpcValue_To_Buffer(params[2], &pBufferRpt, nLenRpt);
	g_theAtsRpcClientMngr->SmartTestCreated(strTestID, pBuffer, nLen, pBufferRpt, nLenRpt);

	result = true;
}

CAtsRpcClient_GbrptOpened::CAtsRpcClient_GbrptOpened(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_OnGbrptOpened, s)
{

}

//该函数暂时没有实现   打开测试记录文件后，调用的是SmartTestCreated
void CAtsRpcClient_GbrptOpened::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	char *pBuffer = NULL, *pBufferRpt=NULL;
	long nLen = 0, nLenRpt = 0;

	XmlRpcValue_To_Buffer(params[0], &pBuffer, nLen);
	//g_theAtsRpcClientMngr->OnGbrptOpened(pBuffer, nLen);

	result = true;
}

CAtsRpcClient_GbDevCreated::CAtsRpcClient_GbDevCreated(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_GbDevCreated, s)
{

}

void CAtsRpcClient_GbDevCreated::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
// 	char *pBuffer = NULL, *pBufferRpt=NULL;
// 	long nLen = 0, nLenRpt = 0;
// 	CString strTestID;
// 
// 	XmlRpcValue_To_String(params[0], strTestID);
// 	XmlRpcValue_To_Buffer(params[1], &pBuffer, nLen);
// 	XmlRpcValue_To_Buffer(params[2], &pBufferRpt, nLenRpt);
// 	g_theAtsRpcClientMngr->SmartTestCreated(strTestID, pBuffer, nLen, pBufferRpt, nLenRpt);

	result = true;
}

CAtsRpcClient_GbDevFinished::CAtsRpcClient_GbDevFinished(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_GbDevFinished, s)
{

}

void CAtsRpcClient_GbDevFinished::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
// 	char *pBuffer = NULL, *pBufferRpt=NULL;
// 	long nLen = 0, nLenRpt = 0;
// 	CString strTestID;
// 
// 	XmlRpcValue_To_String(params[0], strTestID);
// 	XmlRpcValue_To_Buffer(params[1], &pBuffer, nLen);
// 	XmlRpcValue_To_Buffer(params[2], &pBufferRpt, nLenRpt);
// 	g_theAtsRpcClientMngr->SmartTestCreated(strTestID, pBuffer, nLen, pBufferRpt, nLenRpt);

	result = true;
}


CAtsRpcClient_OnConnectDeviceFailed::CAtsRpcClient_OnConnectDeviceFailed(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_OnConnectDeviceFailed, s)
{

}

void CAtsRpcClient_OnConnectDeviceFailed::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CString strTestID;
	XmlRpcValue_To_String(params[0], strTestID);
	g_theAtsRpcClientMngr->OnConnectDeviceFailed(strTestID);
	result = true;
}

CAtsRpcClient_OnOpenGbrptFailed::CAtsRpcClient_OnOpenGbrptFailed(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_OnGbrptOpenFailed, s)
{

}

void CAtsRpcClient_OnOpenGbrptFailed::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CString strTestID;
	XmlRpcValue_To_String(params[0], strTestID);
	g_theAtsRpcClientMngr->OnGbrptOpenFailed(strTestID);
	result = true;
}