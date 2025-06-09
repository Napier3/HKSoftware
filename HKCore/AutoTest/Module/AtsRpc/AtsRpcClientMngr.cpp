#include "stdafx.h"

#include "AtsRpcClientMngr.h"

#include "..\..\..\Module\System\TickCount32.h"

// extern "C" {
// 	_CRTIMP void __cdecl _invalid_parameter_noinfo(void) {  }
// }

using namespace XmlRpc;
using namespace std;

CAtsRpcClientMngr *g_theAtsRpcClientMngr = NULL;

#define _CONNECTDEVICE_USE_SINGLE


CAtsRpcClientMngr::CAtsRpcClientMngr()
{
	g_theAtsRpcClientMngr = this;
	m_pAtsRpcServer = NULL;
}

CAtsRpcClientMngr::~CAtsRpcClientMngr()
{
	
}

void CAtsRpcClientMngr::InitAtsRpcClientMngr()
{
	CAtsRpcServerConfig::Create();

	CreateAtsRpcServer();
}

void CAtsRpcClientMngr::ExitAtsRpcClientMngr()
{
	ExitAtsRpcServer();
	
	CAtsRpcServerConfig::Release();
}


void CAtsRpcClientMngr::ExitAtsRpcServer()
{
	TerminateProgram(_T("SmartTest.exe"));

	if (m_pAtsRpcServer != NULL)
	{
		m_pAtsRpcServer->exit();
		CTickCount32 oTick;

		while (m_pAtsRpcServerThread != NULL)
		{
			oTick.DoEvents(50);
		}

		while (TRUE)
		{
// 			if (m_pAtsRpcServer->getConnectSize() == 0)
// 			{
// 				break;
// 			} 

			oTick.DoEvents(50);
		}
		delete m_pAtsRpcServer;
	}
}

void CAtsRpcClientMngr::CreateAtsRpcServer()
{
	m_pAtsRpcServer = new CAtsRpcClientXmlRpcServer();
	m_pAtsRpcServerThread = AfxBeginThread(AtsRpcServer, this);
	m_pAtsRpcServerThread->m_bAutoDelete = TRUE;
}

UINT CAtsRpcClientMngr::AtsRpcServer(LPVOID pPara)
{
	CAtsRpcClientMngr *pMngr = (CAtsRpcClientMngr*)pPara;

	::CoInitialize(NULL);
	pMngr->m_pAtsRpcServer->run();
	pMngr->m_pAtsRpcServerThread = NULL;
	::CoUninitialize();

	return 0;
}


//////////////////////////////////////////////////////////////////////////
//

CAtsRpcClient* CAtsRpcClientMngr::AddNewAtsRpcClient(const CString &strIP, short nPort)
{
	CAtsRpcClient *pAtsRpcClient = new CAtsRpcClient();
	AddNewChild(pAtsRpcClient);

	pAtsRpcClient->InitXmlRpcClient(strIP, nPort);

	return pAtsRpcClient;
}

//////////////////////////////////////////////////////////////////////////
//CAtsRpcClient
CAtsRpcClient::CAtsRpcClient()
{
	m_pXmlRpcClient = NULL;
}

CAtsRpcClient::~CAtsRpcClient()
{

}

void CAtsRpcClient::InitSmartTestClient()
{
	XmlRpcValue args, res, res_true;
	res_true = true;
	
	args[0] = "";
	args[1] = (int)AtsRpcClientXmlRpcServer_Port;

	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("AtsRpcClient::InitSmartTestClient(%d)"), AtsRpcClientXmlRpcServer_Port);

	try
	{
		CTickCount32 oTick32;
		
		while (TRUE)
		{
			m_pXmlRpcClient->execute(AtsRpc_Method_InitSmartTestClient, args, res);
			oTick32.DoEvents(200);

			if (res == res_true)
			{
				break;
			}
		}
	}
	catch(...)
	{
		int i = 0;
	}
}

BOOL CAtsRpcClient::IsSmartTestExist(const CString &strTestID)
{
	XmlRpcValue args, res;
	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("AtsRpcClient::IsSmartTestExist(%s)"), strTestID);

	String_To_XmlRpcValue(strTestID, args[0]);

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_IsSmartTestExist, args, res);
		int nRet = res;
		
		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
}

BOOL CAtsRpcClient::ExitSmartTest()
{
	XmlRpcValue args, res;

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_ExitSmartTest, args, res);
		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
}

void CAtsRpcClient::CreateTest(const CString &strTestID, CAtsRpcTestDefine *pAtsRpcTestDefine)
{
	XmlRpcValue args, res;
	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("AtsRpcClient::CreateTest(TestID = %s)"), strTestID);

	CBinarySerialBuffer oBinaryBuffer;
	dvm_SerializeWrite(pAtsRpcTestDefine, oBinaryBuffer);
	char *pBuffer = NULL;
	long nLen = 0;
	oBinaryBuffer.GetBuffer(&pBuffer, &nLen);

	String_To_XmlRpcValue(strTestID, args[0]);
	Buffer_To_XmlRpcValue(pBuffer, nLen, args[1]);

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_CreateTest, args, res);
	}
	catch (...)
	{
		CString strPath;
		strPath = _P_GetWorkspacePath();
		log_WriteLogFileForDebug(strPath, (BYTE*)pBuffer, nLen);
	}
}

void CAtsRpcClient::BeginTest(const CString &strTestID)
{
	XmlRpcValue args, res;
	CLogPrint::LogString(LOGLEVEL_TRACE, _T("AtsRpcClient::BeginTest"));

	String_To_XmlRpcValue(strTestID, args[0]);

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_BeginTest, args, res);
	}
	catch (...)
	{

	}
}

void CAtsRpcClient::StopTest(const CString &strTestID)
{
	XmlRpcValue args, res;
	CLogPrint::LogString(LOGLEVEL_TRACE, _T("AtsRpcClient::StopTest"));
	String_To_XmlRpcValue(strTestID, args[0]);

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_StopTest, args, res);
	}
	catch (...)
	{

	}
}

void CAtsRpcClient::TestAllInlegibleItems(const CString &strTestID)
{
	XmlRpcValue args, res;
	CLogPrint::LogString(LOGLEVEL_TRACE, _T("AtsRpcClient::TestAllInlegibleItems"));

	String_To_XmlRpcValue(strTestID, args[0]);

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_TestAllInlegibleItems, args, res);
	}
	catch (...)
	{

	}
}

void CAtsRpcClient::TestPoint(const CString &strTestID, long nIndex)
{
	XmlRpcValue args, res;
	CLogPrint::LogString(LOGLEVEL_TRACE, _T("AtsRpcClient::TestPoint"));

	String_To_XmlRpcValue(strTestID, args[0]);
	args[1] = nIndex;

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_TestPoint, args, res);
	}
	catch (...)
	{

	}
}

void CAtsRpcClient::TestBelow(const CString &strTestID, long nIndex)
{
	XmlRpcValue args, res;
	CLogPrint::LogString(LOGLEVEL_TRACE, _T("AtsRpcClient::TestBelow"));

	String_To_XmlRpcValue(strTestID, args[0]);
	args[1] = nIndex;

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_TestBelow, args, res);
	}
	catch (...)
	{

	}
}

void  CAtsRpcClient::OpenGbrptFile(const CString &strGbrptFilePath, long nDeviceIndex)
{
	XmlRpcValue args, res;
	CLogPrint::LogString(LOGLEVEL_TRACE, _T("AtsRpcClient::OpenGbrptFile"));

	String_To_XmlRpcValue(strGbrptFilePath, args[0]);
	args[1] = nDeviceIndex;

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_OpenGbrptFile, args, res);
	}
	catch (...)
	{

	}
}

void CAtsRpcClient::CloseTest(const CString &strTestID)
{
	XmlRpcValue args, res;
	CLogPrint::LogString(LOGLEVEL_TRACE, _T("AtsRpcClient::CloseTest"));
	String_To_XmlRpcValue(strTestID, args[0]);

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_CloseTest, args, res);
	}
	catch (...)
	{

	}
}

void CAtsRpcClient::ExportRpt(const CString &strTestID)
{
	XmlRpcValue args, res;
	CLogPrint::LogString(LOGLEVEL_TRACE, _T("AtsRpcClient::ExportRpt"));
	String_To_XmlRpcValue(strTestID, args[0]);
	CString strRet;

	try
	{
		BOOL bRet = m_pXmlRpcClient->execute(AtsRpc_Method_ExportRpt, args, res, 10);

		if (bRet == TRUE)
		{
// 			nRet = res[0];
// 			if (nRet == 1)
// 			{
// 				strRet = _T("成功");
// 
// 				oDataset.DeleteAll();
// 				XmlRpcValue_To_Dvm(res[1],oDataset);
// 			}
			strRet = _T("命令发送成功");
		}
		else
		{
			strRet = _T("超时");
		}
		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("生成报告：%s"),strRet);
	}
	catch (...)
	{
		
	}
}

void CAtsRpcClient::ViewItemRpt(long nDeviceIndex, long nItemIndex)
{
	XmlRpcValue args, res;
	CLogPrint::LogString(LOGLEVEL_TRACE, _T("AtsRpcClient::ViewItemRpt"));
	args[0] = nDeviceIndex;
	args[1] = nItemIndex;

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_ViewItemRpt, args, res);
	}
	catch (...)
	{

	}
}
// void CAtsRpcClient::GetAllTestItems(CDvmDataset *pDvmDataset)
// {
// 	XmlRpcValue args, res;
// 
// 	try
// 	{
// 		m_pXmlRpcClient->execute(AtsRpc_Method_GetAllTestItems, args, res);
// 		char *pBuffer = NULL;
// 		long nLen = 0;
// 		XmlRpcValue_To_Buffer(res, &pBuffer, nLen);
// 		dvm_SerializeRead(pDvmDataset, (char*)pBuffer, nLen);
// 	}
// 	catch (...)
// 	{
// 	}
// }

void CAtsRpcClient::GetTestItemReport(const CString &strItemPath, CBinarySerialBuffer &oBuffer)
{

}


void CAtsRpcClient::GbDevWzdAuto(CGbWzdAutoConfig *pGbWzdAutoConfig)
{
	XmlRpcValue args, res;
	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("AtsRpcClient::GbDevWzdAuto(%s)"), pGbWzdAutoConfig->m_strGbxmlFile);

	CString strTestID(_T("AtsBentch"));
	CBinarySerialBuffer oBinaryBuffer;
	pGbWzdAutoConfig->SerializeWrite(oBinaryBuffer);
	char *pBuffer = NULL;
	long nLen = 0;
	oBinaryBuffer.GetBuffer(&pBuffer, &nLen);

	String_To_XmlRpcValue(strTestID, args[0]);
	Buffer_To_XmlRpcValue(pBuffer, nLen, args[1]);

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_GbDevWzdAuto, args, res);
	}
	catch (...)
	{
		CString strPath;
		strPath = _P_GetWorkspacePath();
		log_WriteLogFileForDebug(strPath, (BYTE*)pBuffer, nLen);
	}
}

//////////////////////////////////////////////////////////////////////////
//XMLRPC Client
void CAtsRpcClient::InitXmlRpcClient(const CString &strIP, short nPort)
{
	char *server;// = "localhost";
	int port = nPort;
	const char *uri = NULL;

	if (strIP.GetLength() == 0)
	{
		CString_to_char(CAtsRpcServerConfig::GetRemoteIP(), &server);
	}
	else
	{
		CString_to_char(strIP, &server);
	}

	m_strServerIP = server;

	if (nPort > 0)
	{
		port = nPort;
	}
	else
	{
		port = CAtsRpcServerConfig::GetRpcServerPort();
	}

	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("XmlRpcClient==>>%s + %d"), m_strServerIP, port);
	m_pXmlRpcClient = new XmlRpcClient(server, port, uri);

	delete server;
}

void CAtsRpcClient::ExitXmlRpcClient()
{
	delete m_pXmlRpcClient;
}
