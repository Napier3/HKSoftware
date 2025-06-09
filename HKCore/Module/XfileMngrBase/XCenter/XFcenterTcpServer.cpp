#include "StdAfx.h"
#include "XFcenterTcpServer.h"


/////////////////////////////////////////////////////////////////////////////
//////////////////接收线程///////////////////////////////////////////////////
// bool ConnectWithTimeout(SOCKET &socket, XFCENTER_THREAD_PARAM *pThreadParam, int timeout)
// {
// 	TIMEVAL timeval = {0};
// 	timeval.tv_sec = timeout;
// 	timeval.tv_usec = 0;
// 	struct sockaddr_in address;  
// 
// 	address.sin_family = AF_INET;
// 	address.sin_port = htons(pThreadParam->nServerPort);
// 	address.sin_addr.s_addr = inet_addr(pThreadParam->pszServerIP);
// 
// 	if(address.sin_addr.s_addr == INADDR_NONE)
// 	{
// 		return false;
// 	}
// 
// 	// set the socket in non-blocking
// 	unsigned long mode = 1;
// 	int result = ioctlsocket(socket, FIONBIO, &mode);
// 
// 	if (result != NO_ERROR) 
// 	{
// 		//printf("ioctlsocket failed with error: %ld\n", result);
// 		return FALSE;
// 	}
// 
// 	connect(socket, (struct sockaddr *)&address, sizeof(address));
// 
// 	// restart the socket mode
// 	mode = 0;
// 	result = ioctlsocket(socket, FIONBIO, &mode);
// 	
// 	if (result != NO_ERROR)
// 	{
// 		return false;
// 	}
// 
// 	fd_set Write, Err;
// 	FD_ZERO(&Write);
// 	FD_ZERO(&Err);
// 	FD_SET(socket, &Write);
// 	FD_SET(socket, &Err);
// 
// 	// check if the socket is ready
// 	select(0, NULL, &Write, &Err, &timeval);
// 
// 	if(FD_ISSET(socket, &Write))
// 	{
// 		return true;
// 	}
// 
// 	return false;
// }

// CServerCientSocket

CXFcenterTcpServerClient::CXFcenterTcpServerClient()
{
	m_pServerRef = NULL;
	m_pObjectRef = NULL;
	m_pListXFileMngr = NULL;
}

CXFcenterTcpServerClient::~CXFcenterTcpServerClient()
{
	
}


void CXFcenterTcpServerClient::OnClose(int nErrorCode)
{

	// TODO: 在此添加专用代码和/或调用基类
	if (m_pServerRef != NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Close: Remote[%s][%d]    Local: Remote[%s][%d]")
			, m_pObjectRef->m_strRemoteIp, m_pObjectRef->m_nReotePort
			, m_pObjectRef->m_strLocalIp, m_pObjectRef->m_nLocalPort);
		m_pServerRef->CloseTcpClient(this);
	}

	CSocket::OnClose(nErrorCode);
}

void CXFcenterTcpServerClient::InitObjectRef()
{
	GetPeerName(m_pObjectRef->m_strRemoteIp, m_pObjectRef->m_nReotePort);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("PeerName:  [%s][%d]")
		, m_pObjectRef->m_strRemoteIp, m_pObjectRef->m_nReotePort);

	GetSockName(m_pObjectRef->m_strLocalIp, m_pObjectRef->m_nLocalPort);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("SockName:  [%s][%d]")
		, m_pObjectRef->m_strLocalIp, m_pObjectRef->m_nLocalPort);

}

void CXFcenterTcpServerClient::InitThreadParam(CDvmData *pData, XFCENTER_THREAD_PARAM *pParam)
{
	CXFcenterTcpClientBase::InitThreadParam(pData, pParam);

	//远端服务
	CString_to_char_ex(m_pObjectRef->m_strRemoteIp, pParam->pszServerIP);
	pParam->nServerPort = 8201;

	//pParam->pXFileMngr = xfcenter_find_filemngr(m_pListXFileMngr, pParam->strBucket);
}

void CXFcenterTcpServerClient::BeginServerThread(XFCENTER_THREAD_PARAM *pParam)
{
	xfcenter_log_thread_param(pParam);
	pParam->sktClient = m_hSocket;
	Detach();
	pParam->sktClientRef = this;
	//CWinThread *pThread = AfxBeginThread(xfcenter_client_thread, pParam);  //2022-2-15
	CWinThread *pThread = AfxBeginThread(xfcenter_server_thread_use_own, pParam);
	pThread->m_bAutoDelete = TRUE;
}

BOOL CXFcenterTcpServerClient::ProcessXFcenterCmd(CDvmData *pData)
{
	if (pData->m_strID == XFCENTER_CMD_DOWNLOADFILE)
	{
		return ProcessXFcenterCmd_DownLoadFile(pData);
	}

	if (pData->m_strID == XFCENTER_CMD_UPLOADFILE)
	{
		return ProcessXFcenterCmd_UpLoadFile(pData);
	}

	if (pData->m_strID == XFCENTER_CMD_DELETEFOLDER)
	{
		return ProcessXFcenterCmd_DeleteFile(pData);
	}

	if (pData->m_strID == XFCENTER_CMD_RENAMEFILE)
	{
		return ProcessXFcenterCmd_RenameFile(pData);
	}

	if (pData->m_strID == XFCENTER_CMD_DOWNLOADFOLDER)
	{
		return ProcessXFcenterCmd_DownLoadFolder(pData);
	}

	if (pData->m_strID == XFCENTER_CMD_UPLOADFOLDER)
	{
		return ProcessXFcenterCmd_UpLoadFolder(pData);
	}

	if (pData->m_strID == XFCENTER_CMD_DELETEFOLDER)
	{
		return ProcessXFcenterCmd_DeleteFolder(pData);
	}

	if (pData->m_strID == XFCENTER_CMD_RENAMEFOLDER)
	{
		return ProcessXFcenterCmd_RenameFolder(pData);
	}

	if (pData->m_strID == XFCENTER_CMD_QUERY)
	{
		return ProcessXFcenterCmd_Query(pData);
	}

	return FALSE;
}

//服务器端，收到DownLoadFile，传输文件给客户端
BOOL CXFcenterTcpServerClient::ProcessXFcenterCmd_DownLoadFile(CDvmData *pData)
{
	XFCENTER_THREAD_PARAM *pParam = new XFCENTER_THREAD_PARAM();
	InitThreadParam(pData, pParam);
	CString strFile      = pData->GetAttrValue(XFCENTER_CMD_PARA_FILE);
	pParam->nCmdID = XFCENTER_OPTR_SVR_TO_CLIENT;

	long nCount = CString_To_long(pData->m_strValue);
	long nIndex = 0;

	if (nCount <= 1)
	{
		pParam->astrPath.Add(strFile);
	}
	else
	{
		POS pos = pData->GetHeadPosition();
		CDvmValue *pValue = NULL;

		while (pos != NULL)
		{
			pValue = (CDvmValue *)pData->GetNext(pos);

			if (pValue->m_strID == XFCENTER_CMD_PARA_FILE)
			{
				pParam->astrPath.Add(pValue->m_strValue);
			}
		}
	}

	BeginServerThread(pParam);

	return FALSE;
}

//服务器端，收到UpLoadFile，接收客户端传输的文件
BOOL CXFcenterTcpServerClient::ProcessXFcenterCmd_UpLoadFile(CDvmData *pData)
{
	XFCENTER_THREAD_PARAM *pParam = new XFCENTER_THREAD_PARAM();
	InitThreadParam(pData, pParam);
	
// 	CString strBucket = pData->GetAttrValue(XFCENTER_CMD_PARA_BUCKET);
// 	CString strFile      = pData->GetAttrValue(XFCENTER_CMD_PARA_FILE);

	pParam->nCmdID = XFCENTER_OPTR_CLIENT_TO_SVR;
// 	pParam->astrPath.Add(strFile);

	BeginServerThread(pParam);

	return FALSE;
}

BOOL CXFcenterTcpServerClient::ProcessXFcenterCmd_DeleteFile(CDvmData *pData)
{
	CString strBucket = pData->GetAttrValue(XFCENTER_CMD_PARA_BUCKET);
	CString strFile      = pData->GetAttrValue(XFCENTER_CMD_PARA_FILE);

// 	CXFileMngr *pXFileMngr = xfcenter_find_filemngr(m_pListXFileMngr, strBucket);
// 
// 	if (pXFileMngr != NULL)
// 	{
// 		CXFile *pXFile = xfile_SelectFile_RelPath(pXFileMngr, strFile);
// 
// 		if (pXFile != NULL)
// 		{
// 			CXFolder *pFolder = (CXFolder*)pXFile->GetParent();
// 			pFolder->DeleteFile(pXFile);
// 		}
// 	}

	return FALSE;
}

BOOL CXFcenterTcpServerClient::ProcessXFcenterCmd_RenameFile(CDvmData *pData)
{
	CString strBucket  = pData->GetAttrValue(XFCENTER_CMD_PARA_BUCKET);
	CString strFile       = pData->GetAttrValue(XFCENTER_CMD_PARA_FILE);
	CString strDestFile = pData->GetAttrValue(XFCENTER_CMD_PARA_DESTFILE);

	return FALSE;
}

//服务器端，收到DownLoadFolder，传输文件给客户端
BOOL CXFcenterTcpServerClient::ProcessXFcenterCmd_DownLoadFolder(CDvmData *pData)
{
/*
	XFCENTER_THREAD_PARAM *pParam = new XFCENTER_THREAD_PARAM();
	InitThreadParam(pData, pParam);
	ASSERT (pParam->pXFileMngr != NULL);
	pParam->nCmdID = XFCENTER_OPTR_SVR_TO_CLIENT;

// 	CString strBucket = pData->GetAttrValue(XFCENTER_CMD_PARA_BUCKET);
 	CString strFolder  = pData->GetAttrValue(XFCENTER_CMD_PARA_FOLDER);
	CXFolder *pFind = NULL;
	strFolder.MakeLower();

	if (strFolder.GetLength() == 0)
	{
		pFind = pParam->pXFileMngr;
	}
	else
	{
		pFind = xfile_SelectFolder_RelPath(pParam->pXFileMngr, strFolder);
	}

	CStringArray astrFiles;

	if (pFind != NULL)
	{
		xfile_GetAllFiles(pFind, astrFiles);
	}

	xfile_TrimAllFiles(pParam->pXFileMngr->m_strRootPath, astrFiles);

	BeginClientThread(pParam);
*/

	return TRUE;
}

BOOL CXFcenterTcpServerClient::ProcessXFcenterCmd_UpLoadFolder(CDvmData *pData)
{
/*
	XFCENTER_THREAD_PARAM *pParam = new XFCENTER_THREAD_PARAM();
	InitThreadParam(pData, pParam);
	CString strBucket = pData->GetAttrValue(XFCENTER_CMD_PARA_BUCKET);
	CString strFolder  = pData->GetAttrValue(XFCENTER_CMD_PARA_FOLDER);

	ASSERT (pParam->pXFileMngr != NULL);
	pParam->nCmdID = XFCENTER_OPTR_CLIENT_TO_SVR;

	CXFolder *pFind = NULL;

	if (strFolder.GetLength() == 0)
	{
		pFind = pParam->pXFileMngr;
	}
	else
	{
		pFind = xfile_SelectFolder_RelPath(pParam->pXFileMngr, strFolder);
	}

	BeginClientThread(pParam);
*/

	return TRUE;
}

BOOL CXFcenterTcpServerClient::ProcessXFcenterCmd_DeleteFolder(CDvmData *pData)
{
	XFCENTER_THREAD_PARAM *pParam = new XFCENTER_THREAD_PARAM();
	InitThreadParam(pData, pParam);
	CString strBucket = pData->GetAttrValue(XFCENTER_CMD_PARA_BUCKET);
	CString strFolder  = pData->GetAttrValue(XFCENTER_CMD_PARA_FOLDER);

	return FALSE;
}

BOOL CXFcenterTcpServerClient::ProcessXFcenterCmd_RenameFolder(CDvmData *pData)
{
	XFCENTER_THREAD_PARAM *pParam = new XFCENTER_THREAD_PARAM();
	InitThreadParam(pData, pParam);
	CString strBucket   = pData->GetAttrValue(XFCENTER_CMD_PARA_BUCKET);
	CString strFolder    = pData->GetAttrValue(XFCENTER_CMD_PARA_FOLDER);
	CString strDestFile  = pData->GetAttrValue(XFCENTER_CMD_PARA_DESTFOLDER);

	return FALSE;
}


BOOL CXFcenterTcpServerClient::ProcessXFcenterCmd_Query(CDvmData *pData)
{
/*
	XFCENTER_THREAD_PARAM *pParam = new XFCENTER_THREAD_PARAM();
	InitThreadParam(pData, pParam);

	CString strFolder  = pData->GetAttrValue(XFCENTER_CMD_PARA_FOLDER);
	CString strKeys   = pData->GetAttrValue(XFCENTER_CMD_PARA_KEYS);
	
	ASSERT (pParam->pXFileMngr != NULL);
	pParam->nCmdID = XFCENTER_OPTR_QUERY;
	pParam->astrPath.Add(strFolder);

	if (pData->m_strDataType == XFCENTER_QUERY_MODEKEY_AND)//检索模式
	{
		pParam->dwKeysMode = XFCENTER_QUERY_MODE_AND;
	}
	else
	{
		pParam->dwKeysMode = XFCENTER_QUERY_MODE_OR;
	}
	
	if (strKeys.GetLength() > 0)
	{
		long nPos = strKeys.Find('?');
		long nPosPrev = 0;

		if (nPos > 0)
		{
			while (nPos > 0)
			{
				pParam->astrKeys.Add(strKeys.Mid(nPosPrev, nPos - nPosPrev));
				nPos++;
				nPosPrev = nPos;

				nPos = strKeys.Find('?', nPos);
			}

			if (nPosPrev < strKeys.GetLength())
			{
				pParam->astrKeys.Add(strKeys.Mid(nPosPrev));
			}
		}
		else
		{
			pParam->astrKeys.Add(strKeys);
		}
	}

	BeginClientThread(pParam);
*/

	return TRUE;
}


// 
// BOOL CXFcenterTcpServerClient::ProcessXFcenterCmd_Login(CDvmData *pData)
// {
// 	CString strFcenterName, strPsw;
// // 	strFcenterName = pData->GetAttrValue(XFCENTER_CMD_PARA_USERID);
// // 	strPsw = pData->GetAttrValue(XFCENTER_CMD_PARA_USERPSW);
// // 	CXFcenter *pCurrFcenter = CFcenterDBConstGlobal::Login(strFcenterName, strPsw);;
// // 	ASSERT (m_pObjectRef != NULL);
// // 
// // 	if (m_pObjectRef != NULL)
// // 	{
// // 		m_pServerRef->UpdateTcpClient(this);
// // 	}
// 
// 
// 	//如果用户不存在，则返回没有参数的通讯命令
// // 	if (pCurrFcenter == NULL)
// // 	{
// // 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("login:id=%s   psw=%s error"), strFcenterName, strPsw);
// // 		pData->m_strValue = _T("0");
// // 	}
// // 	else
// // 	{
// // 		pData->m_strValue = _T("1");
// // 		pData->AddValue(XFCENTER_CMD_PARA_user_name, pCurrFcenter->m_strName);
// // 	}
// 
// 	SendXFcenterCmd(pData);
// 
// 	return TRUE;
// }
// 
// BOOL CXFcenterTcpServerClient::ProcessXFcenterCmd_Logout(CDvmData *pData)
// {
// 	return FALSE;
// }
// 
// BOOL CXFcenterTcpServerClient::ProcessXFcenterCmd_GetInfor(CDvmData *pData)
// {
// // 	pData->AddValue(XFCENTER_CMD_PARA_develop, CSafenet_hasp::hasp_get_develop());
// // 	pData->AddValue(XFCENTER_CMD_PARA_ownership, CSafenet_hasp::hasp_get_ownership());
// // 	pData->AddValue(XFCENTER_CMD_PARA_user_cop, CSafenet_hasp::hasp_get_user_cop());
// // 	pData->AddValue(XFCENTER_CMD_PARA_user_name, CSafenet_hasp::hasp_get_user_name());
// // 	pData->AddValue(XFCENTER_CMD_PARA_sys_name, CSafenet_hasp::hasp_get_sys_name());
// 
// 	SendXFcenterCmd(pData);
// 
// 	return TRUE;
// }
// 
// 
// BOOL CXFcenterTcpServerClient::ProcessXFcenterCmd_HasFetureID(CDvmData *pData)
// {
// 	ASSERT (m_pObjectRef != NULL);
// 
// // 	if (m_pObjectRef != NULL)
// // 	{
// // 		GetPeerName(m_pObjectRef->m_strRemoteIp, m_pObjectRef->m_nReotePort);
// // 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("HasFetureID: from 【%s】【%d】"), m_pObjectRef->m_strRemoteIp, m_pObjectRef->m_nReotePort);
// // 		GetSockName(m_pObjectRef->m_strRemoteIp, m_pObjectRef->m_nLocalPort);
// // 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("HasFetureID: from 【%s】【%d】"), m_pObjectRef->m_strRemoteIp, m_pObjectRef->m_nLocalPort);
// // 		m_pServerRef->UpdateTcpClient(this);
// // 	}
// // 
// // 	CString strValue;
// // 	strValue = pData->GetAttrValue(XFCENTER_CMD_PARA_FETUREID);
// // 	UINT nFetureID = CString_To_long(strValue);
// // 
// // 	if (m_pObjectRef != NULL)
// // 	{
// // 		m_pObjectRef->SetModuleID(nFetureID);
// // 		m_pServerRef->UpdateTcpClient(this);
// // 	}
// // 
// // 	BOOL bHas = CSafenet_hasp::hasp_has_catalog(nFetureID, TRUE);
// // 
// // 	pData->m_strValue.Format(_T("%d"), bHas);
// 	SendXFcenterCmd(pData);
// 
// 	return TRUE;
// }

//////////////////////////////////////////////////////////////////////////
//

CXFcenterTcpServer::CXFcenterTcpServer(void)
{
	//m_pListCtrlRef = NULL;
}

CXFcenterTcpServer::~CXFcenterTcpServer(void)
{
	POS pos = m_listTcpClient.GetHeadPosition();
	CXFcenterTcpServerClient *p = NULL;

	while (pos != NULL)
	{
		p = (CXFcenterTcpServerClient *)m_listTcpClient.GetNext(pos);
		p->Close();
	}

	m_listTcpClient.DeleteAll();
	m_listXFileMngr.RemoveAll();
}

BOOL CXFcenterTcpServer::CreateServer(const CString &strIP, UINT nPort)
{
	if (!Create(nPort, SOCK_STREAM, strIP))
	{
		return FALSE;
	}

	if (!Listen())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXFcenterTcpServer::CloseServer()
{
	Close();

	return TRUE;
}

BOOL CXFcenterTcpServer::IsServerClosed()
{
	return TRUE;
}


void CXFcenterTcpServer::OnAccept(int nErrorCode)
{
	CXFcenterTcpServerClientObject *pClientObj = new CXFcenterTcpServerClientObject();
	m_listClientObject.AddTail(pClientObj);
	
	CXFcenterTcpServerClient *pClientSocket = new CXFcenterTcpServerClient();
	pClientSocket->m_pObjectRef = pClientObj;
	pClientSocket->m_pServerRef = this;
	m_listTcpClient.AddTail(pClientSocket);
	pClientSocket->m_pListXFileMngr = &m_listXFileMngr;

	Accept(*pClientSocket); 
	pClientSocket->InitObjectRef();

	CSocket::OnAccept(nErrorCode);
}

void CXFcenterTcpServer::CloseTcpClient(CXFcenterTcpServerClient *pSockt)
{
	//m_pListCtrlRef->DeleteObject(pSockt->m_pObjectRef);
	m_listClientObject.Delete(pSockt->m_pObjectRef);
	pSockt->Close();
	m_listTcpClient.Delete(pSockt);
}

void CXFcenterTcpServer::UpdateTcpClient(CXFcenterTcpServerClient *pSockt)
{
	//m_pListCtrlRef->UpdateListCtrl(pSockt->m_pObjectRef);
}

void CXFcenterTcpServer::AddXFileMngr(CXFileMngr *pXFileMngr)
{
	m_listXFileMngr.AddTail(pXFileMngr);
}

