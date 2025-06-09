#include "stdafx.h"

#include "SmartTestRpcServerMethod.h"
#include "SmartTestRpcMngr.h"

#include "AtsRpcMethodID.h"
#include "..\..\Module\zlib-1.2.8\zlib.h"


using namespace std;

CAtsRpc_IsSmartTestExist::CAtsRpc_IsSmartTestExist(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_IsSmartTestExist, s)
{

}

void CAtsRpc_IsSmartTestExist::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_IsSmartTestExist::execute"));
	CString strTestID;

	XmlRpcValue_To_String(params[0], strTestID);
	g_theSmartTestRpcMngr->IsSmartTestExist(strTestID);

	result = true;
}

CAtsRpc_ExitSmartTest::CAtsRpc_ExitSmartTest(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_ExitSmartTest, s)
{

}

void CAtsRpc_ExitSmartTest::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_ExitSmartTest::execute"));
	CString strTestID;

	g_theSmartTestRpcMngr->ExitSmartTest();

	result = true;
}

CAtsRpc_InitSmartTestClient::CAtsRpc_InitSmartTestClient(XmlRpcServer* s)
	:XmlRpcServerMethod(AtsRpc_Method_InitSmartTestClient, s)
{
	
}

void CAtsRpc_InitSmartTestClient::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_InitSmartTestClient::execute"));
	CString strIP;
	int nPort = 0;

	XmlRpcValue_To_String(params[0], strIP);
	nPort = params[1];

	g_theSmartTestRpcMngr->InitSmartTestClient(strIP, nPort);

    result = (int)1;
}

CAtsRpc_CreateTest::CAtsRpc_CreateTest(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_CreateTest, s)
{

}

/*
CBinarySerialBuffer oBinaryBuffer;
dvm_SerializeWrite(pAtsRpcTestDefine, oBinaryBuffer);
char *pBuffer = NULL;
long nLen = 0;
oBinaryBuffer.GetBuffer(&pBuffer, &nLen);

String_To_XmlRpcValue(strTestID, args[0]);
Buffer_To_XmlRpcValue(pBuffer, nLen, args[10]);
*/
void CAtsRpc_CreateTest::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_CreateTest::execute"));
	char *pBuffer = NULL;
	long nLen = 0;
	CString strTestID;

	XmlRpcValue_To_String(params[0], strTestID);
	XmlRpcValue_To_Buffer(params[1], &pBuffer, nLen);
	g_theSmartTestRpcMngr->CreateTest(strTestID, (BYTE*)pBuffer, nLen);

	result = true;
}

CAtsRpc_OpenGbrptFile::CAtsRpc_OpenGbrptFile(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_OpenGbrptFile, s)
{

}

void CAtsRpc_OpenGbrptFile::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_OpenGbrptFile::execute"));
	CString strGbrptFilePath;

	XmlRpcValue_To_String(params[0], strGbrptFilePath);
	int nDeviceIndex = params[1];

	g_theSmartTestRpcMngr->OpenGbrptFile(strGbrptFilePath, nDeviceIndex);

	result = true;
}

CAtsRpc_BeginTest::CAtsRpc_BeginTest(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_BeginTest, s)
{
	
}

void CAtsRpc_BeginTest::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_BeginTest::execute"));
	g_theSmartTestRpcMngr->BeginTest();

	result = true;
}

CAtsRpc_StopTest::CAtsRpc_StopTest(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_StopTest, s)
{
	
}

void CAtsRpc_StopTest::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_StopTest::execute"));
	g_theSmartTestRpcMngr->StopTest();

	result = true;
}

CAtsRpc_TestAllInlegibleItems::CAtsRpc_TestAllInlegibleItems(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_TestAllInlegibleItems, s)
{

}

void CAtsRpc_TestAllInlegibleItems::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_TestAllInlegibleItems::execute"));
	g_theSmartTestRpcMngr->TestAllInlegibleItems();

	result = true;
}

CAtsRpc_TestPoint::CAtsRpc_TestPoint(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_TestPoint, s)
{

}

void CAtsRpc_TestPoint::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_TestPoint::execute"));

	CString strTestID;

	XmlRpcValue_To_String(params[0], strTestID);
	int nIndex = params[1];

	g_theSmartTestRpcMngr->TestPoint(strTestID, nIndex);

	result = true;
}

CAtsRpc_TestBelow::CAtsRpc_TestBelow(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_TestBelow, s)
{

}

void CAtsRpc_TestBelow::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_TestBelow::execute"));

	CString strTestID;

	XmlRpcValue_To_String(params[0], strTestID);
	int nIndex = params[1];

	g_theSmartTestRpcMngr->TestBelow(strTestID, nIndex);

	result = true;
}

CAtsRpc_CloseTest::CAtsRpc_CloseTest(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_CloseTest, s)
{

}

void CAtsRpc_CloseTest::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	//CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_CloseTest::execute"));
	g_theSmartTestRpcMngr->CloseTest();

	result = true;
}

CAtsRpc_ExportRpt::CAtsRpc_ExportRpt(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_ExportRpt, s)
{

}

void CAtsRpc_ExportRpt::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_ExportRpt::execute"));
	g_theSmartTestRpcMngr->ExportRpt();

	result = true;
}

CAtsRpc_ViewItemRpt::CAtsRpc_ViewItemRpt(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_ViewItemRpt, s)
{

}

void CAtsRpc_ViewItemRpt::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_ViewItemRpt::execute"));

	int nDeviceIndex = params[0];
	int nItemIndex = params[1];

	g_theSmartTestRpcMngr->ViewItemRpt(nDeviceIndex, nItemIndex);

	result = true;
}


CAtsRpc_GetAllTestItems::CAtsRpc_GetAllTestItems(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_GetAllTestItems, s)
{

}

void CAtsRpc_GetAllTestItems::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_GetAllTestItems::execute"));

	CDvmDataset oDvmDataset;
	g_theSmartTestRpcMngr->GetAllTestItems(oDvmDataset);

	CBinarySerialBuffer oBinaryBuffer;
	dvm_SerializeWrite(&oDvmDataset, oBinaryBuffer);
	char *pBuffer = NULL;
	long nLen = 0;
	oBinaryBuffer.GetBuffer(&pBuffer, &nLen);
	Buffer_To_XmlRpcValue(pBuffer, nLen, result);
}

CAtsRpc_GetTestItemReport::CAtsRpc_GetTestItemReport(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_GetTestItemReport, s)
{
	
}

void CAtsRpc_GetTestItemReport::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_GetTestItemReport::execute"));

	//void GetTestItemReport(const CString &strItemPath, BYTE *pBuffer, long &nLen)
	//g_theSmartTestRpcMngr->GetTestItemReport();

	CString strItemPath;
	CBinarySerialBuffer oBuffer;

	XmlRpcValue_To_String(params[0], strItemPath);
	g_theSmartTestRpcMngr->GetTestItemReport(strItemPath, oBuffer);

	result = true;
}


CAtsRpc_TestItem::CAtsRpc_TestItem(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_TestItem, s)
{
	
}

void CAtsRpc_TestItem::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
// 	CString strAllDvState;
// 
// 	XmlRpcValue_To_String(params[0], strAllDvState);


	result = true;
}


CAtsRpc_GetDvmDatas::CAtsRpc_GetDvmDatas(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_GetDvmDatas, s)
{
	
}

void CAtsRpc_GetDvmDatas::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
// 	CString strAllDvState;
// 
// 	XmlRpcValue_To_String(params[0], strAllDvState);


	result = true;
}


CAtsRpc_GetReportFiles::CAtsRpc_GetReportFiles(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_GetReportFiles, s)
{
	
}

void CAtsRpc_GetReportFiles::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	result = true;
}


CAtsRpc_ExecCmd::CAtsRpc_ExecCmd(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_ExecCmd, s)
{
	
}

void CAtsRpc_ExecCmd::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{

	result = true;
}

CAtsRpc_GbDevWzdAuto::CAtsRpc_GbDevWzdAuto(XmlRpcServer* s)
:XmlRpcServerMethod(AtsRpc_Method_GbDevWzdAuto, s)
{

}

/*
String_To_XmlRpcValue(strTestID, args[0]);
Buffer_To_XmlRpcValue(pBuffer, nLen, args[1]);
*/
void CAtsRpc_GbDevWzdAuto::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CAtsRpc_GetTestItemReport::execute"));

	CString strTestID;
	char *pBuffer = NULL;
	long nLen = 0;

	XmlRpcValue_To_String(params[0], strTestID);
	XmlRpcValue_To_Buffer(params[1], &pBuffer, nLen);

	g_theSmartTestRpcMngr->GbDevWzdAuto(strTestID, pBuffer, nLen);

	result = true;
}
