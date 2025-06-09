#include "StdAfx.h"
#include "XFcenterTcpClient.h"
#include "..\..\XLanguage\XLanguageResource.h"
#include "..\..\System\TickCount32.h"
#include "..\..\XfileMngrBase\XCenter\XFcenterConfig.h"

// #define _use_xfcenter_own_thread
// 
// SOCKET xfcenter_accept(XFCENTER_THREAD_PARAM *pThreadParam, long nTimeOut)
// {
// 	int status;
// 	SOCKET destSocket;
// 	SOCKADDR_IN sockAddr;
// 	int len = sizeof (sockAddr);
// 	memset(&sockAddr, 0, sizeof (sockAddr));
// 	sockAddr.sin_port = htons(pThreadParam->nServerPort);
// 	sockAddr.sin_family = AF_INET;
// 	sockAddr.sin_addr.s_addr = inet_addr(pThreadParam->pszServerIP);//htonl(INADDR_ANY);
// 	destSocket = socket(AF_INET, SOCK_STREAM, 0);
// 
// 	if (destSocket == INVALID_SOCKET)
// 	{
// 		return INVALID_SOCKET ;
// 	}
// 
// 	status = bind(destSocket, (LPSOCKADDR)&sockAddr, sizeof (sockAddr));
// 
// 	if (status == SOCKET_ERROR)
// 	{
// 		return INVALID_SOCKET ;
// 	}
// 
// 	status = listen(destSocket, 1);
// 
// 	if (status == SOCKET_ERROR)
// 	{
// 		return INVALID_SOCKET ;
// 	}
// 
// 	SOCKET sktAccept = INVALID_SOCKET ;
// 	struct timeval timeout = {1,0};  
// 
// 	if (setsockopt(destSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval)) != 0)  
// 	{  
// 		return INVALID_SOCKET ;
// 	}  
// 
// 	CTickCount32 oTick;
// 
// 	while (TRUE)
// 	{
// 		sktAccept = accept(destSocket, (LPSOCKADDR)&sockAddr, &len);
// 
// 		if (nTimeOut > 0)
// 		{
// 			if (oTick.GetTickCountLong(FALSE) > nTimeOut)
// 			{
// 				break;
// 			}
// 		}
// 	}
// 
// 	closesocket(destSocket);	//关闭原来的套接字
// 
// 	return sktAccept;
// }

CXFcenterTcpClient::CXFcenterTcpClient(void)
{
	m_dwTcpConnectState = XFCENTER_CLIENT_STATE_NORMAL;
	m_bXFcenterFinish = FALSE;
}

CXFcenterTcpClient::~CXFcenterTcpClient(void)
{

}


BOOL CXFcenterTcpClient::IsTcpConnectSucc()
{
	return (m_dwTcpConnectState == XFCENTER_CLIENT_STATE_CONNECTSUCC);
}

BOOL CXFcenterTcpClient::IsTcpConnectting()
{
	return (m_dwTcpConnectState == XFCENTER_CLIENT_STATE_CONNECTTING);
}

BOOL CXFcenterTcpClient::ConnectServer(const CString &strIP, UINT nPort)
{
	m_dwTcpConnectState = XFCENTER_CLIENT_STATE_CONNECTTING;
	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Connect server [%s] [%d] ......................"), strIP, nPort);

	if (!Create())
	{
		m_dwTcpConnectState = XFCENTER_CLIENT_STATE_NORMAL;
	}

	if (!xfcenter_set_connect_timeout(m_hSocket, 50)) //设置5秒延时
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("set connect timeout failed"));
	}

	if ( Connect(strIP, nPort) )
	{
		m_dwTcpConnectState = XFCENTER_CLIENT_STATE_CONNECTSUCC;
	}
	else
	{
		m_dwTcpConnectState = XFCENTER_CLIENT_STATE_CONNECTFAILED;
	}

	if (IsTcpConnectSucc())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Connect server [%s] [%d] sucessful"), strIP, nPort);

		GetPeerName(m_strRemoteIp, m_nLocalPort);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("PeerName [%s][%d]"), m_strRemoteIp, m_nLocalPort);

		//本地IP作为服务器
		GetSockName(m_strLocalIp, m_nLocalPort);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("SockName [%s][%d]"), m_strLocalIp, m_nLocalPort);
	}
	else
	{
		Close();
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Connect server [%s] [%d] failed"), strIP, nPort);
	}

	return IsTcpConnectSucc();
}

void CXFcenterTcpClient::DisConnectServer()
{
	Close();
	m_dwTcpConnectState = XFCENTER_CLIENT_STATE_NORMAL;
}

BOOL CXFcenterTcpClient::ProcessXFcenterCmd(CDvmData *pData)
{
	ASSERT (m_pMsgRcvWnd != NULL);

	if (m_pMsgRcvWnd != NULL)
	{
	m_pMsgRcvWnd->SendMessage(WM_XFCENTERTCPCLIENT_CMD, (LPARAM)pData, (WPARAM)pData);
	}
// 	if (pData->m_strID == XFCENTER_CMD_LOGIN)
// 	{
// 		return ProcessXFcenterCmd_Login(pData);
// 	}
// 
// 	if (pData->m_strID == XFCENTER_CMD_LOGOUT)
// 	{
// 		return ProcessXFcenterCmd_Logout(pData);
// 	}
// 
// 	if (pData->m_strID == XFCENTER_CMD_GETINFOR)
// 	{
// 		return ProcessXFcenterCmd_GetInfor(pData);
// 	}
// 
// 	if (pData->m_strID == XFCENTER_CMD_HASFETURE)
// 	{
// 		return ProcessXFcenterCmd_HasFetureID(pData);
// 	}

	return FALSE;
}

BOOL CXFcenterTcpClient::ProcessXFcenterCmd_Login(CDvmData *pData)
{
	
	return TRUE;
}

BOOL CXFcenterTcpClient::ProcessXFcenterCmd_Logout(CDvmData *pData)
{
	return FALSE;
}

BOOL CXFcenterTcpClient::ProcessXFcenterCmd_GetInfor(CDvmData *pData)
{
	return TRUE;
}


BOOL CXFcenterTcpClient::ProcessXFcenterCmd_HasFetureID(CDvmData *pData)
{
	return TRUE;
}

void CXFcenterTcpClient::OnClose(int nErrorCode)
{
	m_dwTcpConnectState = FALSE;
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CXFcenterTcpClient::OnClose"));

	CXFcenterTcpClientBase::OnClose(nErrorCode);
}



//////////////////////////////////////////////////////////////////////////
//
long CXFcenterTcpClient::DownLoadFile(const CString &strRootPath, const CString &strFile,CWinThread *pThread, UINT nCmdFinishMsg, CWnd *pMsgRcvWnd, UINT nMsg)
{
	m_oSendCmd.DeleteAll();

	m_oSendCmd.m_strID = XFCENTER_CMD_DOWNLOADFILE;
// 	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_BUCKET, pXFileMngr->m_strYunRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_ROOTPATH, strRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_FILE, strFile);

	XFCENTER_THREAD_PARAM *pParam = new XFCENTER_THREAD_PARAM;
	pParam->nCmdID = XFCENTER_OPTR_SVR_TO_CLIENT;
 	pParam->strRootPath = strRootPath;
	InitThreadParam(&m_oSendCmd, pParam);
	pParam->pWndMsgRcv = pMsgRcvWnd;
	pParam->nMsgRcv = nMsg;
	pParam->pThread = pThread;
	pParam->nCmdFinishMsg = nCmdFinishMsg;

	return ExecXFcenterCmd(pParam);
}

void CXFcenterTcpClient::InitXFcenterFiles(CDvmData *pData, const CStringArray &astrFiles)
{
	CString strFile;
	long nCount = astrFiles.GetCount();
	long nIndex = 0;
	pData->m_strValue.Format(_T("%d"), nCount);

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strFile = astrFiles.GetAt(nIndex);
		pData->AddValue(XFCENTER_CMD_PARA_FILE, strFile);
	}
}

long CXFcenterTcpClient::DownLoadFiles(const CString &strRootPath, const CStringArray &astrFiles,CWinThread *pThread, UINT nCmdFinishMsg, CWnd *pMsgRcvWnd, UINT nMsg)
{
	m_oSendCmd.DeleteAll();

	m_oSendCmd.m_strID = XFCENTER_CMD_DOWNLOADFILE;
// 	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_BUCKET, pXFileMngr->m_strYunRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_ROOTPATH, strRootPath);

	InitXFcenterFiles(&m_oSendCmd, astrFiles);

	XFCENTER_THREAD_PARAM *pParam = new XFCENTER_THREAD_PARAM;
	pParam->nCmdID = XFCENTER_OPTR_SVR_TO_CLIENT;
 	pParam->strRootPath = strRootPath;
	InitThreadParam(&m_oSendCmd, pParam);
	pParam->pWndMsgRcv = pMsgRcvWnd;
	pParam->nMsgRcv = nMsg;
	pParam->pThread = pThread;
	pParam->nCmdFinishMsg = nCmdFinishMsg;
	
	return ExecXFcenterCmd(pParam);
}

long CXFcenterTcpClient::UpLoadFiles(const CString &strRootPath, const CStringArray &astrFiles, CWinThread *pThread, UINT nCmdFinishMsg, CWnd *pMsgRcvWnd, UINT nMsg)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CXFcenterTcpClient::UpLoadFiles   --- 338"));
	m_oSendCmd.DeleteAll();
	XFCENTER_THREAD_PARAM *pParam = new XFCENTER_THREAD_PARAM;
	InitThreadParam(&m_oSendCmd, pParam);

	m_oSendCmd.m_strID = XFCENTER_CMD_UPLOADFILE;
// 	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_BUCKET, pXFileMngr->m_strYunRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_ROOTPATH, strRootPath);
	InitXFcenterFiles(&m_oSendCmd, astrFiles);

	pParam->nCmdID = XFCENTER_OPTR_CLIENT_TO_SVR;
 	pParam->strRootPath = strRootPath;
	pParam->pWndMsgRcv = pMsgRcvWnd;
	pParam->nMsgRcv = nMsg;
	pParam->pThread = pThread;
	pParam->nCmdFinishMsg = nCmdFinishMsg;
	pParam->astrPath.Append(astrFiles);
	
	return ExecXFcenterCmd(pParam);
}

long CXFcenterTcpClient::UpLoadFile(const CString &strRootPath, const CString &strFile,CWinThread *pThread, UINT nCmdFinishMsg, CWnd *pMsgRcvWnd, UINT nMsg)
{
	m_oSendCmd.DeleteAll();

	m_oSendCmd.m_strID = XFCENTER_CMD_UPLOADFILE;
// 	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_BUCKET, pXFileMngr->m_strYunRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_ROOTPATH, strRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_FILE, strFile);

	XFCENTER_THREAD_PARAM *pParam = new XFCENTER_THREAD_PARAM;
	pParam->nCmdID = XFCENTER_OPTR_CLIENT_TO_SVR;
 	pParam->strRootPath = strRootPath;
	InitThreadParam(&m_oSendCmd, pParam);
	pParam->pWndMsgRcv = pMsgRcvWnd;
	pParam->nMsgRcv = nMsg;
	pParam->pThread = pThread;
	pParam->nCmdFinishMsg = nCmdFinishMsg;
	
	return ExecXFcenterCmd(pParam);
}

long CXFcenterTcpClient::DeleteFile(const CString &strRootPath, const CString &strFile)
{
	m_oSendCmd.DeleteAll();

	m_oSendCmd.m_strID = XFCENTER_CMD_DELETEFILE;
// 	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_BUCKET, pXFileMngr->m_strYunRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_ROOTPATH, strRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_FILE, strFile);

	return SendXFcenterCmd(&m_oSendCmd);
}

long CXFcenterTcpClient::RenameFile(const CString &strRootPath, const CString &strFile, const CString &strDesFile)
{
	m_oSendCmd.DeleteAll();

	m_oSendCmd.m_strID = XFCENTER_CMD_RENAMEFILE;
// 	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_BUCKET, pXFileMngr->m_strYunRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_ROOTPATH, strRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_FILE, strFile);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_DESTFILE, strDesFile);

	return SendXFcenterCmd(&m_oSendCmd);
}


long CXFcenterTcpClient::DownLoadFolder(const CString &strRootPath, const CString &strFolder,CWinThread *pThread, UINT nCmdFinishMsg, CWnd *pMsgRcvWnd, UINT nMsg)
{
	m_oSendCmd.DeleteAll();

	m_oSendCmd.m_strID = XFCENTER_CMD_DOWNLOADFOLDER;
// 	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_BUCKET, pXFileMngr->m_strYunRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_ROOTPATH, strRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_FOLDER, strFolder);

	XFCENTER_THREAD_PARAM *pParam = new XFCENTER_THREAD_PARAM;
	InitThreadParam(&m_oSendCmd, pParam);
	pParam->nCmdID = XFCENTER_OPTR_SVR_TO_CLIENT;
 	pParam->strRootPath = strRootPath;
	pParam->pWndMsgRcv = pMsgRcvWnd;
	pParam->nMsgRcv = nMsg;
	pParam->pThread = pThread;
	pParam->nCmdFinishMsg = nCmdFinishMsg;
	
	return ExecXFcenterCmd(pParam);
}

long CXFcenterTcpClient::UpLoadFolder(const CString &strRootPath, const CString &strFolder,CWinThread *pThread, UINT nCmdFinishMsg, CWnd *pMsgRcvWnd, UINT nMsg) 
{
	m_oSendCmd.DeleteAll();

	m_oSendCmd.m_strID = XFCENTER_CMD_UPLOADFOLDER;
// 	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_BUCKET, pXFileMngr->m_strYunRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_ROOTPATH, strRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_FOLDER, strFolder);

	XFCENTER_THREAD_PARAM *pParam = new XFCENTER_THREAD_PARAM;
	pParam->nCmdID = XFCENTER_OPTR_CLIENT_TO_SVR;
	InitThreadParam(&m_oSendCmd, pParam);
 	pParam->strRootPath = strRootPath;
	pParam->pWndMsgRcv = pMsgRcvWnd;
	pParam->nMsgRcv = nMsg;
	pParam->pThread = pThread;
	pParam->nCmdFinishMsg = nCmdFinishMsg;

// 	CXFolder *pFolder = NULL;
// 	pFolder = xfile_SelectFolder_RelPath(strFolder);
// 
// 	if (strFolder.GetLength() == 0 || pFolder == NULL)
// 	{
// 		pFolder = pXFileMngr;
// 	}
// 
// 	xfile_GetAllFiles(pFolder, pParam->astrPath);
// 	xfile_TrimAllFiles(pXFileMngr->m_strRootPath, pParam->astrPath);
	
	return ExecXFcenterCmd(pParam);
}

long CXFcenterTcpClient::DeleteFolder(const CString &strRootPath, const CString &strFolder)
{
	m_oSendCmd.DeleteAll();

	m_oSendCmd.m_strID = XFCENTER_CMD_DELETEFOLDER;
// 	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_BUCKET, pXFileMngr->m_strYunRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_ROOTPATH, strRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_FOLDER, strFolder);

	return SendXFcenterCmd(&m_oSendCmd);
}

long CXFcenterTcpClient::RenameFolder(const CString &strRootPath, const CString &strFolder, const CString &strDesFolder)
{
	m_oSendCmd.DeleteAll();

	m_oSendCmd.m_strID = XFCENTER_CMD_RENAMEFOLDER;
// 	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_BUCKET, pXFileMngr->m_strYunRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_ROOTPATH, strRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_FOLDER, strFolder);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_DESTFOLDER, strDesFolder);

	return SendXFcenterCmd(&m_oSendCmd);
}


long CXFcenterTcpClient::Query(const CString &strRootPath, const CString &strFolder, const CString &strQueryMode, const CString &strKeys,CWinThread *pThread, UINT nCmdFinishMsg, CWnd *pMsgRcvWnd, UINT nMsg)
{
	m_oSendCmd.DeleteAll();

	return 0;

	m_oSendCmd.m_strID = XFCENTER_CMD_QUERY;
// 	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_BUCKET, pXFileMngr->m_strYunRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_ROOTPATH, strRootPath);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_FOLDER, strFolder);
	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_KEYS, strKeys);
	m_oSendCmd.m_strDataType = strQueryMode;

	XFCENTER_THREAD_PARAM *pParam = new XFCENTER_THREAD_PARAM;
	pParam->nCmdID = XFCENTER_OPTR_QUERY;
	InitThreadParam(&m_oSendCmd, pParam);
 	pParam->strRootPath = strRootPath;
	pParam->pWndMsgRcv = pMsgRcvWnd;
	pParam->nMsgRcv = nMsg;
	pParam->pThread = pThread;
	pParam->nCmdFinishMsg = nCmdFinishMsg;

	return ExecXFcenterCmd(pParam);
}

void CXFcenterTcpClient::WaiteXFcenterFinish()
{
// 	while (!m_bXFcenterFinish)
// 	{
// 		Sleep(100);
// 	}

	WaitForSingleObject(m_eventXFcenter, INFINITE);
}

void CXFcenterTcpClient::InitThreadParam(CDvmData *pData, XFCENTER_THREAD_PARAM *pParam)
{
	CXFcenterTcpClientBase::InitThreadParam(pData, pParam);

	//本地创建文件传输服务器
	CString_to_char(m_strLocalIp, pParam->pszServerIP);
	pParam->nServerPort = 8201;
	//pParam->nServerPort = m_nLocalPort;
	pParam->pbXFcenterFinish = &m_bXFcenterFinish;
}

void CXFcenterTcpClient::BeginClientThread(XFCENTER_THREAD_PARAM *pParam)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CXFcenterTcpClient::BeginServerThread   ----  531"));
	pParam->pEvent = &m_eventXFcenter;
	pParam->sktClient = m_hSocket;
	pParam->sktClientRef = this;
	Detach();

	CTickCount32 oTick;
	oTick.DoEvents(500);

	//CWinThread *pThread = AfxBeginThread(xfcenter_server_thread, pParam);
	CWinThread *pThread = AfxBeginThread(xfcenter_client_thread_use_own, pParam);
	pThread->m_bAutoDelete = TRUE;
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CXFcenterTcpClient::BeginServerThread   ----  535"));
}

long CXFcenterTcpClient::ExecXFcenterCmd(XFCENTER_THREAD_PARAM *pParam)
{
#ifdef _use_xfcenter_own_thread
	long nRet = SendXFcenterCmd(&m_oSendCmd);
	xfcenter_server_thread(pParam);
	return nRet;
#else
	long nRet = SendXFcenterCmd(&m_oSendCmd);
	BeginClientThread(pParam);  //lijunqing 2022-2-15 
	return nRet;
#endif
}

//////////////////////////////////////////////////////////////////////////
//

IMPLEMENT_DYNCREATE(CXFcenterTcpClientThread, CWinThread)

CXFcenterTcpClientThread::CXFcenterTcpClientThread()
{
	m_bThreadHasExit = FALSE;
	m_pXFcenterTcpClientCmd = NULL;
	m_pXFcenterTcpClient = new CXFcenterTcpClient();
}

CXFcenterTcpClientThread::~CXFcenterTcpClientThread()
{
	if (m_pXFcenterTcpClient != NULL)
	{
		delete m_pXFcenterTcpClient;
		m_pXFcenterTcpClient = NULL;
	}
}

BOOL CXFcenterTcpClientThread::InitInstance()
{
	AfxOleInit();
	AfxSocketInit(NULL);

	return TRUE;
}

int CXFcenterTcpClientThread::ExitInstance()
{
	int nReturn = CWinThread::ExitInstance();

	m_bThreadHasExit = TRUE;

	return nReturn;
}

void CXFcenterTcpClientThread::XFcenterResetEvent()
{
	m_pXFcenterTcpClient->m_eventXFcenter.ResetEvent();
}

void CXFcenterTcpClientThread::XFcenterSetEvent()
{
	m_pXFcenterTcpClient->m_eventXFcenter.SetEvent();
}

BOOL CXFcenterTcpClientThread::IsTcpConnectSucc()
{
	return m_pXFcenterTcpClient->IsTcpConnectSucc();
}

BOOL CXFcenterTcpClientThread::IsTcpConnectting()
{
	return m_pXFcenterTcpClient->IsTcpConnectting();
}

//2022-2-16  lijunqing
void CXFcenterTcpClientThread::ConnectServer()
{	
	if (m_pXFcenterTcpClient == NULL)
	{
		m_pXFcenterTcpClient = new CXFcenterTcpClient();
	}

	if (m_pXFcenterTcpClient->IsTcpConnectSucc())
	{
		return;
	}

	this->PostThreadMessage(WM_ConnectServer, 1, 1);
	CTickCount32 oTick;
	oTick.DoEvents(100);
	//m_pXFcenterTcpClient->ConnectServer(CXFcenterConfig::GetServerIP(), CXFcenterConfig::GetServerPort());
}

void CXFcenterTcpClientThread::ConnectServer(CWnd *pMsgRcvWnd, UINT nMsg)	
{
	AddCmd(_T(""), _T(""), _T(""), _T(""), pMsgRcvWnd, nMsg, WM_ConnectServer);
}

void CXFcenterTcpClientThread::DisConnectServer(CWnd *pMsgRcvWnd, UINT nMsg)
{
	AddCmd(_T(""), _T(""), _T(""), _T(""), pMsgRcvWnd, nMsg, WM_DisConnectServer);
}

void CXFcenterTcpClientThread::AddCmd(const CString &strRootPath, const CStringArray &astrPaths
									  , CWnd *pMsgRcvWnd, UINT nMsg, UINT nXFcenterMsg)
{
	CAutoSimpleLock oLock(m_oListCmdAutoCriticSection);
	CXFcenterTcpClientCmd *pNew = new CXFcenterTcpClientCmd();
	pNew->m_pMsgRcvWnd = pMsgRcvWnd;
 	pNew->m_strRootPath = strRootPath;
	pNew->m_nXFcenterMsg = nXFcenterMsg;
	pNew->m_nMsgRcv = nMsg;
	pNew->m_astrFiles.Append(astrPaths);
	m_listXFcenterTcpClientCmd.AddTail(pNew);

// 	if (pXFileMngr != NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("######################AddCmd  [%s] [%d]"), pXFileMngr->m_strYunRootPath, nXFcenterMsg);
// 	}
// 	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("######################AddCmd  [%d]"), nXFcenterMsg);
	}

	if (m_pXFcenterTcpClientCmd == NULL)
	{
		m_pXFcenterTcpClientCmd = (CXFcenterTcpClientCmd *)m_listXFcenterTcpClientCmd.GetHead();
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CXFcenterTcpClientThread::AddCmd   [%d] ---- 633"), nXFcenterMsg);
		PostThreadMessage(WM_ExecCmd, 0, 0);
	}
}

void CXFcenterTcpClientThread::AddCmd(const CString &strRootPath, const CString &strPath, const CString &strPathDest
									  , const CString &strKeys, CWnd *pMsgRcvWnd, UINT nMsg, UINT nXFcenterMsg)
{
	CAutoSimpleLock oLock(m_oListCmdAutoCriticSection);
	CXFcenterTcpClientCmd *pNew = new CXFcenterTcpClientCmd();
	pNew->m_pMsgRcvWnd = pMsgRcvWnd;
 	pNew->m_strRootPath = strRootPath;
	pNew->m_strKeys = strKeys;
	pNew->m_strPath = strPath;
	pNew->m_strPathDest = strPathDest;
	pNew->m_strRootPath = _T("");
	pNew->m_nXFcenterMsg = nXFcenterMsg;
	pNew->m_nMsgRcv = nMsg;
	m_listXFcenterTcpClientCmd.AddTail(pNew);

// 	if (pXFileMngr != NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("######################AddCmd  [%s] [%d]"), pXFileMngr->m_strYunRootPath, nXFcenterMsg);
// 	}
// 	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("######################AddCmd  [%d]"), nXFcenterMsg);
	}

	if (m_pXFcenterTcpClientCmd == NULL)
	{
		m_pXFcenterTcpClientCmd = (CXFcenterTcpClientCmd *)m_listXFcenterTcpClientCmd.GetHead();
		PostThreadMessage(WM_ExecCmd, 0, 0);
	}
}

void CXFcenterTcpClientThread::AddCmd_Query(const CString &strRootPath, const CString &strPath, const CString &strQueryMode
									  , const CString &strKeys, CWnd *pMsgRcvWnd, UINT nMsg, UINT nXFcenterMsg)
{
	CAutoSimpleLock oLock(m_oListCmdAutoCriticSection);
	CXFcenterTcpClientCmd *pNew = new CXFcenterTcpClientCmd();
	pNew->m_pMsgRcvWnd = pMsgRcvWnd;
 	pNew->m_strRootPath = strRootPath;
	pNew->m_strKeys = strKeys;
	pNew->m_strPath = strPath;
	pNew->m_strQueryMode = strQueryMode;
	pNew->m_nXFcenterMsg = nXFcenterMsg;
	pNew->m_nMsgRcv = nMsg;
	m_listXFcenterTcpClientCmd.AddTail(pNew);

// 	if (pXFileMngr != NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("######################AddCmd  [%s] [%d]"), pXFileMngr->m_strYunRootPath, nXFcenterMsg);
// 	}
// 	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("######################AddCmd  [%d]"), nXFcenterMsg);
	}

	if (m_pXFcenterTcpClientCmd == NULL)
	{
		m_pXFcenterTcpClientCmd = (CXFcenterTcpClientCmd *)m_listXFcenterTcpClientCmd.GetHead();
		PostThreadMessage(WM_ExecCmd, 0, 0);
	}
}

void CXFcenterTcpClientThread::PostXFcenterFinishMsg()
{
	CAutoSimpleLock oLock(m_oListCmdAutoCriticSection);
	ASSERT (m_pXFcenterTcpClientCmd != NULL);

	if (m_pXFcenterTcpClientCmd == NULL)
	{
		return;
	}

	//发送结束消息给窗口
	CXFcenterTcpClientCmd *pXFcenterTcpClientCmd = m_pXFcenterTcpClientCmd;

	m_listXFcenterTcpClientCmd.Remove(pXFcenterTcpClientCmd);
	m_pXFcenterTcpClientCmd = (CXFcenterTcpClientCmd *)m_listXFcenterTcpClientCmd.GetHead();

	//继续下一个命令的执行
	if (m_pXFcenterTcpClientCmd != NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("********Post Next Cmd Msg [%d]......................"), m_pXFcenterTcpClientCmd->m_nXFcenterMsg);
		PostThreadMessage(m_pXFcenterTcpClientCmd->m_nXFcenterMsg, 0, 0);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("********All Cmd Finished......................"));
	}

	pXFcenterTcpClientCmd->PostWndMsg();
	delete pXFcenterTcpClientCmd;
}

long CXFcenterTcpClientThread::DownLoadFiles(const CString &strRootPath, const CStringArray &astrFiles, CWnd *pMsgRcvWnd, UINT nMsg)
{
	ConnectServer();  //2022-2-16  lijunqing

	if (! IsTcpConnectSucc())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("The connection to the server is not established"));
		return 0;
	}

	AddCmd(strRootPath, astrFiles, pMsgRcvWnd, nMsg, WM_DownLoadFile);

	return 0;
}

long CXFcenterTcpClientThread::DownLoadFile(const CString &strRootPath, const CString &strFile, CWnd *pMsgRcvWnd, UINT nMsg)
{
	ConnectServer();  //2022-2-16  lijunqing

	if (! IsTcpConnectSucc())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("The connection to the server is not established"));
		return 0;
	}

	AddCmd(strRootPath, strFile, _T(""), _T(""), pMsgRcvWnd, nMsg, WM_DownLoadFile);

	return 0;
}

long CXFcenterTcpClientThread::UpLoadFile(const CString &strRootPath, const CString &strFile, CWnd *pMsgRcvWnd, UINT nMsg)
{
	ConnectServer();  //2022-2-16  lijunqing

	if (! IsTcpConnectSucc())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("The connection to the server is not established"));
		return 0;
	}

	AddCmd(strRootPath, strFile, _T(""), _T(""), pMsgRcvWnd, nMsg, WM_UpLoadFile);

	return 0;
}

long CXFcenterTcpClientThread::UpLoadFiles(const CString &strRootPath, const CStringArray &astrFiles, CWnd *pMsgRcvWnd, UINT nMsg)
{
	ConnectServer();  //2022-2-16  lijunqing

	if (! IsTcpConnectSucc())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("The connection to the server is not established"));
		return 0;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CXFcenterTcpClientThread::UpLoadFiles --- [%d]   772"), nMsg);
	AddCmd(strRootPath, astrFiles, pMsgRcvWnd, nMsg, WM_UpLoadFile);

	return 0;
}

long CXFcenterTcpClientThread::DeleteFile(const CString &strRootPath, const CString &strFile, CWnd *pMsgRcvWnd, UINT nMsg)
{	
	if (! IsTcpConnectSucc())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("The connection to the server is not established"));
		return 0;
	}

	AddCmd(strRootPath, strFile, _T(""), _T(""), pMsgRcvWnd, nMsg, WM_DeleteFile);

	return 0;
}

long CXFcenterTcpClientThread::RenameFile(const CString &strRootPath, const CString &strFile, const CString &strDesFile, CWnd *pMsgRcvWnd, UINT nMsg)
{
	if (! IsTcpConnectSucc())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("The connection to the server is not established"));
		return 0;
	}

	AddCmd(strRootPath, strFile, strDesFile, _T(""), pMsgRcvWnd, nMsg, WM_RenameFile);

	return 0;
}


long CXFcenterTcpClientThread::DownLoadFolder(const CString &strRootPath, const CString &strFolder, CWnd *pMsgRcvWnd, UINT nMsg)
{
	if (! IsTcpConnectSucc())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("The connection to the server is not established"));
		return 0;
	}

	AddCmd(strRootPath, strFolder, _T(""), _T(""), pMsgRcvWnd, nMsg, WM_DownLoadFolder);

	return 0;
}

long CXFcenterTcpClientThread::UpLoadFolder(const CString &strRootPath, const CString &strFolder, CWnd *pMsgRcvWnd, UINT nMsg) 
{
	if (! IsTcpConnectSucc())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("The connection to the server is not established"));
		return 0;
	}

	AddCmd(strRootPath, strFolder, _T(""), _T(""), pMsgRcvWnd, nMsg, WM_UpLoadFolder);

	return 0;
}

long CXFcenterTcpClientThread::DeleteFolder(const CString &strRootPath, const CString &strFolder, CWnd *pMsgRcvWnd, UINT nMsg)
{
	if (! IsTcpConnectSucc())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("The connection to the server is not established"));
		return 0;
	}

	AddCmd(strRootPath, strFolder, _T(""), _T(""), pMsgRcvWnd, nMsg, WM_DeleteFolder);

	return 0;
}

long CXFcenterTcpClientThread::RenameFolder(const CString &strRootPath, const CString &strFolder, const CString &strDesFolder, CWnd *pMsgRcvWnd, UINT nMsg)
{
	if (! IsTcpConnectSucc())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("The connection to the server is not established"));
		return 0;
	}

	AddCmd(strRootPath, strFolder,strDesFolder, _T(""), pMsgRcvWnd, nMsg, WM_RenameFolder);

	return 0;
}


long CXFcenterTcpClientThread::Query(const CString &strRootPath, const CString &strFolder, const CString &strQueryMode, const CString &strKeys, CWnd *pMsgRcvWnd, UINT nMsg)
{
	if (! IsTcpConnectSucc())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("The connection to the server is not established"));
		return 0;
	}

	AddCmd_Query(strRootPath, strFolder, strQueryMode, strKeys, pMsgRcvWnd, nMsg, WM_Query);

	return 0;
}

void CXFcenterTcpClientThread::WaiteXFcenterFinish()
{
	m_pXFcenterTcpClient->WaiteXFcenterFinish();
}



BEGIN_MESSAGE_MAP(CXFcenterTcpClientThread, CWinThread)
	//{{AFX_MSG_MAP(CTestWorkThread)
	ON_THREAD_MESSAGE(WM_ConnectServer, OnConnectServer)
	ON_THREAD_MESSAGE(WM_DisConnectServer, OnDisConnectServer)
	ON_THREAD_MESSAGE(WM_DownLoadFile, OnDownLoadFile)
	ON_THREAD_MESSAGE(WM_UpLoadFile, OnUpLoadFile)
	ON_THREAD_MESSAGE(WM_DeleteFile, OnDeleteFile)
	ON_THREAD_MESSAGE(WM_RenameFile, OnRenameFile)
	ON_THREAD_MESSAGE(WM_DownLoadFolder, OnDownLoadFolder)
	ON_THREAD_MESSAGE(WM_UpLoadFolder, OnUpLoadFolder)
	ON_THREAD_MESSAGE(WM_DeleteFolder, OnDeleteFolder)
	ON_THREAD_MESSAGE(WM_RenameFolder, OnRenameFolder)
	ON_THREAD_MESSAGE(WM_Query, OnQuery)
	ON_THREAD_MESSAGE(WM_ExecCmd, OnExecCmd)
	ON_THREAD_MESSAGE(WM_ExecCmdFinish, OnExecCmdFinish)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CXFcenterTcpClientThread::OnConnectServer(WPARAM wParam, LPARAM lParam)
{
	m_pXFcenterTcpClient->DisConnectServer();
	m_pXFcenterTcpClient->ConnectServer(CXFcenterConfig::GetServerIP(), CXFcenterConfig::GetServerPort());

	if (lParam == 0)
	{
	PostXFcenterFinishMsg();
	}
}

void CXFcenterTcpClientThread::OnDisConnectServer(WPARAM wParam, LPARAM lParam)
{
	m_pXFcenterTcpClient->DisConnectServer();
	PostXFcenterFinishMsg();
}

void CXFcenterTcpClientThread::OnDownLoadFile(WPARAM wParam, LPARAM lParam)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("********Thread::DownLoadFile......................"));

	if (m_pXFcenterTcpClientCmd == NULL)
	{
		return;
	}

	ASSERT (m_pXFcenterTcpClientCmd != NULL);

	if (m_pXFcenterTcpClientCmd->m_strPath.GetLength() > 0)
	{
		m_pXFcenterTcpClient->DownLoadFile(m_pXFcenterTcpClientCmd->m_strRootPath, m_pXFcenterTcpClientCmd->m_strPath
			, this, WM_ExecCmdFinish);//
	}
	else
	{
		m_pXFcenterTcpClient->DownLoadFiles(m_pXFcenterTcpClientCmd->m_strRootPath, m_pXFcenterTcpClientCmd->m_astrFiles
			, this, WM_ExecCmdFinish);//
	}
}

void CXFcenterTcpClientThread::OnUpLoadFile(WPARAM wParam, LPARAM lParam)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("********Thread::UpLoadFile......................"));

	if (m_pXFcenterTcpClientCmd == NULL)
	{
		return;
	}

	ASSERT (m_pXFcenterTcpClientCmd != NULL);

	if (m_pXFcenterTcpClientCmd->m_strPath.GetLength() > 0)
	{
		m_pXFcenterTcpClient->UpLoadFile(m_pXFcenterTcpClientCmd->m_strRootPath, m_pXFcenterTcpClientCmd->m_strPath
			, this, WM_ExecCmdFinish);//
	}
	else
	{
		m_pXFcenterTcpClient->UpLoadFiles(m_pXFcenterTcpClientCmd->m_strRootPath, m_pXFcenterTcpClientCmd->m_astrFiles
			, this, WM_ExecCmdFinish);//
	}
}

void CXFcenterTcpClientThread::OnDeleteFile(WPARAM wParam, LPARAM lParam)
{
	ASSERT (m_pXFcenterTcpClientCmd != NULL);
	m_pXFcenterTcpClient->DeleteFile(m_pXFcenterTcpClientCmd->m_strRootPath, m_pXFcenterTcpClientCmd->m_strPath);
	PostXFcenterFinishMsg();
}

void CXFcenterTcpClientThread::OnRenameFile(WPARAM wParam, LPARAM lParam)
{
	ASSERT (m_pXFcenterTcpClientCmd != NULL);
	m_pXFcenterTcpClient->RenameFile(m_pXFcenterTcpClientCmd->m_strRootPath, m_pXFcenterTcpClientCmd->m_strPath, m_pXFcenterTcpClientCmd->m_strPathDest);
	PostXFcenterFinishMsg();
}

void CXFcenterTcpClientThread::OnDownLoadFolder(WPARAM wParam, LPARAM lParam)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("********Thread::DownLoadFolder......................"));

	ASSERT (m_pXFcenterTcpClientCmd != NULL);
	m_pXFcenterTcpClient->DownLoadFolder(m_pXFcenterTcpClientCmd->m_strRootPath, m_pXFcenterTcpClientCmd->m_strPath
		, this, WM_ExecCmdFinish);//
}

void CXFcenterTcpClientThread::OnUpLoadFolder(WPARAM wParam, LPARAM lParam)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("********Thread::UpLoadFolder......................"));

	ASSERT (m_pXFcenterTcpClientCmd != NULL);
	m_pXFcenterTcpClient->UpLoadFolder(m_pXFcenterTcpClientCmd->m_strRootPath, m_pXFcenterTcpClientCmd->m_strPath
		, this, WM_ExecCmdFinish);//
}

void CXFcenterTcpClientThread::OnDeleteFolder(WPARAM wParam, LPARAM lParam)
{
	ASSERT (m_pXFcenterTcpClientCmd != NULL);
	m_pXFcenterTcpClient->DeleteFolder(m_pXFcenterTcpClientCmd->m_strRootPath, m_pXFcenterTcpClientCmd->m_strPath);
	PostXFcenterFinishMsg();
}

void CXFcenterTcpClientThread::OnRenameFolder(WPARAM wParam, LPARAM lParam)
{
	ASSERT (m_pXFcenterTcpClientCmd != NULL);
	m_pXFcenterTcpClient->RenameFolder(m_pXFcenterTcpClientCmd->m_strRootPath, m_pXFcenterTcpClientCmd->m_strPath, m_pXFcenterTcpClientCmd->m_strPathDest);
	PostXFcenterFinishMsg();
}

void CXFcenterTcpClientThread::OnQuery(WPARAM wParam, LPARAM lParam)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("+++++++++++Thread::Query [%s][%s]......................")
		, m_pXFcenterTcpClientCmd->m_strPath
		, m_pXFcenterTcpClientCmd->m_strQueryMode);

	ASSERT (m_pXFcenterTcpClientCmd != NULL);
	m_pXFcenterTcpClient->Query(m_pXFcenterTcpClientCmd->m_strRootPath, m_pXFcenterTcpClientCmd->m_strPath
		, m_pXFcenterTcpClientCmd->m_strQueryMode
		, m_pXFcenterTcpClientCmd->m_strKeys
		, this, WM_ExecCmdFinish);//
}

void CXFcenterTcpClientThread::OnExecCmd(WPARAM wParam, LPARAM lParam)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("********Thread::OnExecCmd [%d]......................"), m_pXFcenterTcpClientCmd->m_nXFcenterMsg);

	ASSERT (m_pXFcenterTcpClientCmd != NULL);
	PostThreadMessage(m_pXFcenterTcpClientCmd->m_nXFcenterMsg, 0, 0);
}


void CXFcenterTcpClientThread::OnExecCmdFinish(WPARAM wParam, LPARAM lParam)
{
	//CAutoSimpleLock oLock(m_oAutoCriticSection);
	//ASSERT (m_pXFcenterTcpClientCmd != NULL);
	//PostThreadMessage(m_pXFcenterTcpClientCmd->m_nXFcenterMsg, 0, 0);
	PostXFcenterFinishMsg();

	CAutoSimpleLock oLock(m_oListCmdAutoCriticSection);
	m_pXFcenterTcpClientCmd = NULL;
	m_listXFcenterTcpClientCmd.DeleteAll();
	m_pXFcenterTcpClient->DisConnectServer();
	delete m_pXFcenterTcpClient;
	m_pXFcenterTcpClient = NULL;
}

