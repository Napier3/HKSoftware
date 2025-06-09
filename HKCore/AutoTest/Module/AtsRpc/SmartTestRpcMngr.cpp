#include "stdafx.h"

#include "SmartTestRpcMngr.h"

#include "..\..\..\Module\System\TickCount32.h"
#include "..\TestControl/TestControlMdvMgrp.h"
#include "AtsRpcMethodID.h"
#include "..\..\..\Module\MemBuffer\EquationBuffer.h"
#include "..\TestControl/TCtrlCntrBaseApp.h"

#include "..\SmartTestRpcApi.h"
// extern "C" {
// 	_CRTIMP void __cdecl _invalid_parameter_noinfo(void) {  }
// }

using namespace XmlRpc;
using namespace std;

CSmartTestRpcMngr *g_theSmartTestRpcMngr = NULL;

#define _CONNECTDEVICE_USE_SINGLE

long CSmartTestRpcMngr::g_nSmartTestRpcMngrRef;
CSmartTestRpcMngr *CSmartTestRpcMngr::g_pSmartTestRpcMngr;

void CSmartTestRpcMngr::Create(const CString &strServerIP, long nServerLocalPort, const CString &strTestID)
{
	g_nSmartTestRpcMngrRef++;

	if (g_nSmartTestRpcMngrRef == 1)
	{
		g_pSmartTestRpcMngr = new CSmartTestRpcMngr;
		g_pSmartTestRpcMngr->m_strServerIP = strServerIP;
		g_pSmartTestRpcMngr->m_nServerLocalPort = nServerLocalPort;
		g_pSmartTestRpcMngr->m_strTestID = strTestID;
	}
}

void CSmartTestRpcMngr::Release()
{
	g_nSmartTestRpcMngrRef--;

	if (g_nSmartTestRpcMngrRef == 0)
	{
		g_pSmartTestRpcMngr->ExitSmartTestRpcMngr();
		delete g_pSmartTestRpcMngr;
		g_pSmartTestRpcMngr = NULL;
	}
}

CSmartTestRpcMngr::CSmartTestRpcMngr()
{
	g_theSmartTestRpcMngr = this;
	m_pAtsRpcServer = NULL;
	m_pXmlRpcClient = NULL;
	m_pMainTestControl = NULL;
}

CSmartTestRpcMngr::~CSmartTestRpcMngr()
{
	g_theSmartTestRpcMngr = NULL;
}

void CSmartTestRpcMngr::InitSmartTestRpcMngr()
{
	CAtsRpcServerConfig::Create();

	CreateAtsRpcServer();
	//InitXMiniFtp();
}

void CSmartTestRpcMngr::ExitSmartTestRpcMngr()
{
	ExitXmlRpcClient();
	ExitAtsRpcServer();
	//ExitXMiniFtp();
	
	CAtsRpcServerConfig::Release();
}


void CSmartTestRpcMngr::ExitAtsRpcServer()
{
	m_pAtsRpcServer->exit();
	CTickCount32 oTick;

	while (m_pAtsRpcServerThread != NULL)
	{
		oTick.DoEvents(50);
	}
	
	delete m_pAtsRpcServer;
}

void CSmartTestRpcMngr::CreateAtsRpcServer()
{
	m_pAtsRpcServer = new CSmartTestRpcXmlRpcServer(m_strServerIP, m_nServerLocalPort);
	m_pAtsRpcServerThread = AfxBeginThread(AtsRpcServer, this);
	m_pAtsRpcServerThread->m_bAutoDelete = TRUE;
}

UINT CSmartTestRpcMngr::AtsRpcServer(LPVOID pPara)
{
	CSmartTestRpcMngr *pMngr = (CSmartTestRpcMngr*)pPara;

	::CoInitialize(NULL);
	pMngr->m_pAtsRpcServer->run();
	pMngr->m_pAtsRpcServerThread = NULL;
	::CoUninitialize();

	return 0;
}

BOOL CSmartTestRpcMngr::IsSmartTestExist(const CString &strTestID)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("IsSmartTestExist(%s - %s)"), m_strTestID, strTestID);
	return TRUE;
}

BOOL CSmartTestRpcMngr::ExitSmartTest()
{
	g_theTCtrlCntrApp->m_pMainWnd->PostMessage(WM_CLOSE);
	return TRUE;
}

void CSmartTestRpcMngr::InitSmartTestClient(const CString &strServerIP, long nPort)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("InitSmartTestClient(%s, %d)"), strServerIP, nPort);
	InitXmlRpcClient(strServerIP, nPort);
}

void CSmartTestRpcMngr::CreateTest(const CString &strTestID, BYTE *pBuffer, long nLen)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CreateTest(%s, %d)"), strTestID, nLen);

	try
	{
		CXObjectRefDriver oDriver(CAtsRpcTestDefine::New);
		CAtsRpcTestDefine *pAtsRpcTestDef = (CAtsRpcTestDefine*)oDriver.New();
		oDriver.AddRef();

		dvm_SerializeRead(pAtsRpcTestDef, (char*)pBuffer, nLen);

		g_theTCtrlCntrApp->m_pMainWnd->PostMessage(WM_ATS_CREATETEST, (WPARAM)pAtsRpcTestDef, DVMCLASSID_CDVMLOGICDEVICE);
	}
	catch (...)
	{
		CString strPath;
		strPath = _P_GetWorkspacePath();
		log_WriteLogFileForDebug(strPath, pBuffer, nLen);
	}
}

void CSmartTestRpcMngr::BeginTest()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::BeginTest"));
	g_theTCtrlCntrApp->m_pMainWnd->PostMessage(WM_ATS_TEST, WM_ATS_TEST_PARA_BEGINTEST, WM_ATS_TEST_PARA_BEGINTEST);
}

void CSmartTestRpcMngr::StopTest()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::StopTest"));
	g_theTCtrlCntrApp->m_pMainWnd->PostMessage(WM_ATS_TEST, WM_ATS_TEST_PARA_STOPTEST, WM_ATS_TEST_PARA_STOPTEST);
}

void CSmartTestRpcMngr::TestAllInlegibleItems()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::TestAllInlegibleItems"));
	g_theTCtrlCntrApp->m_pMainWnd->PostMessage(WM_ATS_TEST, WM_ATS_TEST_PARA_TESTALLINLEGIBLEITEMS, WM_ATS_TEST_PARA_TESTALLINLEGIBLEITEMS);
}

void CSmartTestRpcMngr::TestPoint(const CString &strTestID, long nIndex)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TestPoint(%s, %d)"), strTestID, nIndex);

	g_theTCtrlCntrApp->m_pMainWnd ->PostMessage(WM_ATS_TEST, WM_ATS_TEST_PARA_TESTPOINT, nIndex);
}

void CSmartTestRpcMngr::TestBelow(const CString &strTestID, long nIndex)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TestBelow(%s, %d)"), strTestID, nIndex);

	g_theTCtrlCntrApp->m_pMainWnd->PostMessage(WM_ATS_TEST, WM_ATS_TEST_PARA_TESTBELOW, nIndex);
}

void CSmartTestRpcMngr::OpenGbrptFile(CString &strGbrptFile, long nDeviceIndex)
{
	m_strGbrptFile = strGbrptFile;
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::OpenGbrptFile"));
	g_theTCtrlCntrApp->m_pMainWnd->PostMessage(WM_ATS_TEST_PARA_OPENGBRPTFILE, nDeviceIndex, (LPARAM)&m_strGbrptFile);
}

void CSmartTestRpcMngr::CloseTest()
{
	//CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::CloseTest"));
	g_theTCtrlCntrApp->m_pMainWnd->PostMessage(WM_ATS_TEST, WM_ATS_TEST_PARA_CLOSETEST, WM_ATS_TEST_PARA_CLOSETEST);
}

void CSmartTestRpcMngr::ExportRpt()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::ExportRpt"));
	g_theTCtrlCntrApp->m_pMainWnd->PostMessage(WM_ATS_TEST, WM_ATS_TEST_PARA_EXPORTRPTS, WM_ATS_TEST_PARA_EXPORTRPTS);
}

void CSmartTestRpcMngr::ViewItemRpt(long nDeviceIndex, long nItemIndex)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::ViewItemRpt"));
	LPARAM lParam = nItemIndex;
	lParam |= (nDeviceIndex << 24);

	g_theTCtrlCntrApp->m_pMainWnd->PostMessage(WM_ATS_TEST, WM_ATS_TEST_PARA_VIEWITEMRPT, lParam);
}

void CSmartTestRpcMngr::GetAllTestItems(CDvmDataset &oDvmDataset)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::GetAllTestItems"));
	RPC_API_GetAllTestItems(m_pMainTestControl, oDvmDataset);
// 	m_pMainTestControl->QueryFrom(-1);
// 	CExBaseList *pListItems = m_pMainTestControl->m_pItemContainer->GetGuideBookAllItems();
// 
// 	POS pos = pListItems->GetHeadPosition();
// 	CGbItemBase *pItem = NULL;
// 	CDvmData *pData = NULL;
// 	UINT nClassID = 0;
// 
// 	while (pos != NULL)
// 	{
// 		pItem = (CGbItemBase *)pListItems->GetNext(pos);
// 		nClassID = pItem->GetClassID();
// 
// 		if (nClassID == GBCLASSID_DEVICE || nClassID == GBCLASSID_JOBGUIDE
// 			|| nClassID == GBCLASSID_ITEMS)
// 		{
// 			continue;
// 		}
// 
// 		if (pItem->m_nSelect == 0 || pItem->m_nShow == 0 || pItem->m_nEnable == 0)
// 		{
// 			continue;
// 		}
// 
// 		pData = new CDvmData();
// 		pData->m_strName = pItem->GetNamePathEx(GBCLASSID_DEVICE, FALSE);
// 		pData->m_nIndex = pItem->m_nIndex;
// 		pData->m_strID = pItem->GetIDPathEx(GBCLASSID_DEVICE, FALSE);
// 		pData->m_strDataType = pItem->GetXmlElementKey();
// 		oDvmDataset.AddNewChild(pData);
// 	}
}

void CSmartTestRpcMngr::GetTestItemReport(const CString &strItemPath, CBinarySerialBuffer &oBuffer)
{
	
}

void CSmartTestRpcMngr::GbDevWzdAuto(const CString &strTestID, char *pBuffer, long nLen)
{
#ifdef GUIDEBOOK_DEV_MODE
	m_oGbWzdAutoConfig.SerializeRead(pBuffer, nLen);
#endif
}

// 
// void CSmartTestRpcMngr::ExecCmd(const CString &strDvCnlnID, CDvmDataset &oDataset)
// {
// 
// }

//////////////////////////////////////////////////////////////////////////
//XMLRPC Client
void CSmartTestRpcMngr::InitXmlRpcClient(const CString &strServerIP, long nPort)
{
	char *server;// = "localhost";
	int port = 9998;
	const char *uri = NULL;
	CString strIP ;

	if (strServerIP.GetLength() > 0)
	{
		CString_to_char(strServerIP, &server);
	}
	else
	{
		CString_to_char(CAtsRpcServerConfig::GetRemoteIP(), &server);
	}

	if (nPort > 0)
	{
		port = nPort;
	}
	else
	{
		port = CAtsRpcServerConfig::GetRpcServerPort();
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("XmlRpcClient:%s + %d"), server, port);

	m_pXmlRpcClient = new XmlRpcClient(server, port, uri);
	delete server;
}

void CSmartTestRpcMngr::ExitXmlRpcClient()
{
	delete m_pXmlRpcClient;
}

void CSmartTestRpcMngr::ExitXMiniFtp()
{
	if (!m_oXMiniFtpClient.m_isLogOn)
	{
		return;
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("FTP退出登录") );
	m_oXMiniFtpClient.LogOffServer();
}

BOOL CSmartTestRpcMngr::InitXMiniFtp()
{
	if (m_oXMiniFtpClient.m_isLogOn)
	{
		return TRUE;
	}

	m_strRcdFileRootPath = _P_GetWorkspacePath();
	m_oXMiniFtpClient.CloseControlChannel();

	CXMiniFtpFileItem::g_strServerRootDir = _P_GetWorkspacePath();

	BOOL bRet = m_oXMiniFtpClient.LogOnToServer(CAtsRpcServerConfig::GetRemoteIP()
		,21,CAtsRpcServerConfig::GeFtpUser(), CAtsRpcServerConfig::GeFtpPSW()
		,_T(""),_T(""),_T(""),_T(""),1080,0) ;

	if(!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s FTP登录失败"), CAtsRpcServerConfig::GetRemoteIP());
		m_oXMiniFtpClient.CloseControlChannel();
		m_oXMiniFtpClient.m_isLogOn = FALSE;
		return FALSE;
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s FTP登陆成功"), CAtsRpcServerConfig::GetRemoteIP());
	}

	m_oXMiniFtpClient.AttachMainWnd(AfxGetMainWnd());

	return TRUE;
}

void CSmartTestRpcMngr::OnGbrptOpened()
{
	if (m_pXmlRpcClient == NULL)
	{
		return;
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::OnGbrptOpened"));
	XmlRpcValue args, res;
	CDvmDataset oDvmDataset;
	CBinarySerialBuffer oBinaryBuffer;
	char *pBuffer = NULL;
	long nLen = 0;

	GetAllTestItems(oDvmDataset);
	dvm_SerializeWrite(&oDvmDataset, oBinaryBuffer);
	oBinaryBuffer.GetBuffer(&pBuffer, &nLen);
	Buffer_To_XmlRpcValue(pBuffer, nLen, args[0]);

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_OnGbrptOpened, args, res);
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::OnGbrptOpened Error...................."));
	}
}

void CSmartTestRpcMngr::OnOpenGbrptFailed()
{
	if (m_pXmlRpcClient == NULL)
	{
		return;
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::OnOpenGbrptFailed"));
	XmlRpcValue args, res;

	String_To_XmlRpcValue(m_strTestID, args[0]);

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_OnGbrptOpenFailed, args, res);
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::OnOpenGbrptFailed Error...................."));
	}
}

void CSmartTestRpcMngr::OnSmartTestCreated(CDvmDataset *pDvmTasks)
{
	if (m_pXmlRpcClient == NULL)
	{
		return;
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::OnSmartTestCreated"));
	XmlRpcValue args, res;
	CDvmDataset oDvmDataset;
	CBinarySerialBuffer oBinaryBuffer;
	char *pBuffer = NULL;
	long nLen = 0;

	String_To_XmlRpcValue(m_strTestID, args[0]);
	GetAllTestItems(oDvmDataset);
	dvm_SerializeWrite(&oDvmDataset, oBinaryBuffer);
	oBinaryBuffer.GetBuffer(&pBuffer, &nLen);
	Buffer_To_XmlRpcValue(pBuffer, nLen, args[1]);

	dvm_SerializeWrite(pDvmTasks, oBinaryBuffer);
	oBinaryBuffer.GetBuffer(&pBuffer, &nLen);
	Buffer_To_XmlRpcValue(pBuffer, nLen, args[2]);

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_SmartTestCreated, args, res);
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::OnSmartTestCreated Error...................."));
	}
}


void CSmartTestRpcMngr::OnTestItemStateChanged(CGbItemBase *pTestItem)
{
	if (m_pXmlRpcClient == NULL)
	{
		return;
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::OnTestItemStateChanged"));
	XmlRpcValue args, res;
	CString strName, strID, strState;
	int nDeviceIndex = RPC_API_GetTestControlIndex(pTestItem);

	pTestItem->GetIDPathEx(GBCLASSID_DEVICE, FALSE);
	strState = Gb_GetTestStateByID(pTestItem->GetState());

	String_To_XmlRpcValue(m_strTestID, args[0]);
	args[1] = nDeviceIndex;
	args[2] = (int)pTestItem->m_nIndex;
	String_To_XmlRpcValue(strID, args[3]);
	String_To_XmlRpcValue(strState, args[4]);

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_OnItemStateChanged, args, res);
	}
	catch (...)
	{
	}
}

void CSmartTestRpcMngr::OnTestFinished(CTestControlBase *pTestControl, long nType)
{
	if (m_pXmlRpcClient == NULL)
	{
		return;
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::OnTestFinished"));
	XmlRpcValue args, res;
	int nDeviceIndex = RPC_API_GetTestControlIndex(pTestControl);

	String_To_XmlRpcValue(m_strTestID, args[0]);
	args[1] = nDeviceIndex;
	args[2] = (int)nType;

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_OnTestFinished, args, res);
	}
	catch (...)
	{
	}
}

void CSmartTestRpcMngr::OnTestError(CTestControlBase *pTestControl)
{
	
}

void CSmartTestRpcMngr::OnTestStoped(CTestControlBase *pTestControl, const CString &strMsg)
{
	if (m_pXmlRpcClient == NULL)
	{
		return;
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::OnTestStoped"));
	XmlRpcValue args, res;
	int nDeviceIndex = RPC_API_GetTestControlIndex(pTestControl);

	String_To_XmlRpcValue(m_strTestID, args[0]);
	args[1] = nDeviceIndex;
	String_To_XmlRpcValue(strMsg, args[2]);

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_OnTestStoped, args, res);
	}
	catch (...)
	{
	}
}

void CSmartTestRpcMngr::OnExportRptFinished()
{
	if (m_pXmlRpcClient == NULL)
	{
		return;
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::OnExportRptFinished"));
	XmlRpcValue args, res;
	CString strRet;

	String_To_XmlRpcValue(m_strTestID, args[0]);

	try
	{
		BOOL bRet = m_pXmlRpcClient->execute(AtsRpc_Method_OnExportRptFinished, args, res, 20);
		if (bRet == TRUE)
		{
			strRet = _T("命令发送成功");
		}
		else
		{
			strRet = _T("超时");
		}
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("导出报告完成：%s"),strRet);
	}
	catch (...)
	{
	}
}

//Add BY ShaoL  2019.04.26
void CSmartTestRpcMngr::OnConnectDeviceFailed()
{
	if (m_pXmlRpcClient == NULL)
	{
		return;
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSmartTestRpcMngr::OnConnectDeviceFailed"));
	XmlRpcValue args, res;

	String_To_XmlRpcValue(m_strTestID, args[0]);

	try
	{
		m_pXmlRpcClient->execute(AtsRpc_Method_OnConnectDeviceFailed, args, res);
	}
	catch (...)
	{
	}
}

/*
使用与本地远程调用的方式，传入端口来创建远程调用Server，命令行参数格式如下：
	RPC:IP=localhost;Port=$;TestID=;
	Port：测试管理控制台会一次性启动多个测试端，同时执行好多个测试，因此TestID标识了当前创建的测试。作为测试管理控制台的接口，每个SmartTest对象都是一个Server端
*/
BOOL atsrpc_OpenCmdFile_RPC(const CString &strCmdFile, CWnd *pMainWnd)
{
	CString strCmd = strCmdFile.Left(4);
	strCmd.MakeLower();

	if (strCmd != _T("rpc:"))
	{
		return FALSE;
	}

	strCmd = strCmdFile.Mid(4);
	strCmd.MakeLower();

	CLogPrint::LogString(XLOGLEVEL_TRACE, strCmd);
	CEquationBuffer oBuffer;
	oBuffer.InitBuffer(strCmd);
	CString strIP, strTestID;
	long nPort = 0;
	oBuffer.ParseString(_T("ip"), strIP);
	oBuffer.ParseString(_T("testid"), strTestID);
	oBuffer.ParseLong(_T("port"), &nPort);
	CSmartTestRpcMngr::Create(strIP, nPort, strTestID);

	g_theSmartTestRpcMngr->InitSmartTestRpcMngr();

	return TRUE;
}
