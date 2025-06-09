#include "StdAfx.h"
#include "XFcenterTcpClient.h"
#include "..\..\System\TickCount32.h"
#include "..\..\API\FileApi.h"

CXFcenterTcpClientBase::CXFcenterTcpClientBase(void)
{
	ZeroMemory(m_byteReceiveBuffer, XFCENTER_BUF_LEN);
	ZeroMemory(m_byteSendBuffer, XFCENTER_BUF_LEN);
	m_pMsgRcvWnd = NULL;
}

CXFcenterTcpClientBase::~CXFcenterTcpClientBase(void)
{

}

BOOL CXFcenterTcpClientBase::IsSendCmdFinished()
{
	return (m_oSendCmd.m_strValue.GetLength() > 0);
}

long CXFcenterTcpClientBase::GetSendCmdResult()
{
	if (m_oSendCmd.m_strValue.GetLength() > 0)
	{
		return CString_To_long(m_oSendCmd.m_strValue);
	}
	else
	{
		return -1;
	}
}

void CXFcenterTcpClientBase::SetMsgRcvWnd(CWnd *pMsgRcvWnd)
{
	m_pMsgRcvWnd = pMsgRcvWnd;
}
// 
// long CXFcenterTcpClientBase::XEncrypt(const CString &strText, char *pszBuffer)
// {
// 	char *pText = NULL;
// 	long nLen = CString_to_char(strText, &pText);
// 
// 	ValueToHex((const BYTE*)pText, nLen, pszBuffer);
// 
// 	delete pText;
// 
// 	long nRet = strlen(pszBuffer);
// 	return nRet;
// }
// 
// long CXFcenterTcpClientBase::XDecrypt(char *strSrcText, CString &strDest)
// {
// 	static char _xdecrypt_buffer[8192];
// 	ZeroMemory(_xdecrypt_buffer, 8192);
// 
// 	long nLen = HexToValue((const char*)strSrcText, (BYTE*)_xdecrypt_buffer);
// 	_xdecrypt_buffer[nLen] = 0;
// 
// 	strDest = _xdecrypt_buffer;
// 	return nLen;
// }

void CXFcenterTcpClientBase::OnReceive(int nErrorCode)
{
	BYTE *pTemp = m_byteReceiveBuffer;
	long nLen = 0;

	while (TRUE)
	{
		nLen = recv(m_hSocket, (char*)pTemp, XFCENTER_BUF_LEN, 0);
		//nLen = Receive(pTemp, XFCENTER_BUF_LEN); //Get the whole thing
		
		if (nLen <= 0)
		{
			*pTemp = 0;
			break;
		}
		else
		{
			pTemp += nLen;
		}
	}

	nLen = pTemp - m_byteReceiveBuffer;
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CXFcenterTcpClientBase::OnReceive=%d"), nLen);

	if (nLen < 3)
	{
		return;
	}

	_bstr_t strXml;
	strXml = (char*)m_byteReceiveBuffer;

	CDvmData oData;
	oData.SetXml(strXml, CDataMngrXmlRWKeys::g_pXmlKeys);

	CSocket::OnReceive(nErrorCode);

	ProcessXFcenterCmd(&oData);
}


void CXFcenterTcpClientBase::InitThreadParam(CDvmData *pData, XFCENTER_THREAD_PARAM *pParam)
{
	pParam->strBucket = pData->GetAttrValue(XFCENTER_CMD_PARA_BUCKET);
	pParam->strRootPath = pData->GetAttrValue(XFCENTER_CMD_PARA_ROOTPATH);
	pParam->nMsgRcv = 0;
	pParam->pszServerIP[0] = 0;
	pParam->astrKeys.RemoveAll();
	pParam->astrPath.RemoveAll();
	pParam->pWndMsgRcv = m_pMsgRcvWnd;
	pParam->pbXFcenterFinish = NULL;
	pParam->pEvent = NULL;
	pParam->pThread = NULL;
	pParam->nCmdFinishMsg = 0;
}

BOOL CXFcenterTcpClientBase::ProcessXFcenterCmd(CDvmData *pData)
{
	ASSERT (FALSE);
	return TRUE;
}


BOOL CXFcenterTcpClientBase::SendXFcenterCmd(CDvmData *pData)
{
	CLogPrint::LogString(XLOGLEVEL_ERROR, _T("CXFcenterTcpClientBase::SendXFcenterCmd---110"));
	CString strCmd;
	pData->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strCmd);

	return SendXFcenterCmd(strCmd);
}

BOOL CXFcenterTcpClientBase::SendXFcenterCmd(const CString &strCmd)
{
	long nLen = CString_to_char(strCmd, (char*)m_byteSendBuffer);
	
	nLen = Send(m_byteSendBuffer, nLen);

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CXFcenterTcpClientBase::SendXFcenterCmd=%d"), nLen);

	return (nLen > 0);
}

BOOL CXFcenterTcpClientBase::Login(const CString &strFcenterID, const CString &strPsw)
{
	m_oSendCmd.DeleteAll();
// 	m_oSendCmd.m_strID = XFCENTER_CMD_LOGIN;
// 	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_USERID, strFcenterID);
// 	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_USERPSW, strPsw);
	
	return SendXFcenterCmd(&m_oSendCmd);
}

BOOL CXFcenterTcpClientBase::Logoff(const CString &strFcenterID)
{
	m_oSendCmd.DeleteAll();
// 	m_oSendCmd.m_strID = XFCENTER_CMD_LOGOUT;
// 	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_USERID, strFcenterID);

	return SendXFcenterCmd(&m_oSendCmd);
}

//软件授权
BOOL CXFcenterTcpClientBase::hasp_has_catalog(UINT nFetureID)
{
	CString strValue;
	m_oSendCmd.DeleteAll();

	strValue.Format(_T("%d"), nFetureID);
// 	m_oSendCmd.m_strID = XFCENTER_CMD_HASFETURE;
// 	m_oSendCmd.AddValue(XFCENTER_CMD_PARA_FETUREID, strValue);

	return SendXFcenterCmd(&m_oSendCmd);
}

BOOL CXFcenterTcpClientBase::hasp_get_infor()
{
	m_oSendCmd.DeleteAll();
// 	m_oSendCmd.m_strID = XFCENTER_CMD_GETINFOR;

	return SendXFcenterCmd(&m_oSendCmd);
}

//////////////////////////////////////////////////////////////////////////
//
BOOL xfcenter_send_cmd_ret(SOCKET &sktSend, XFCENTER_CMD_RET &cmdRet)
{
	if (SOCKET_ERROR == send(sktSend, (char*)(&cmdRet),  sizeof(cmdRet), 0))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


void xfcenter_log_error()
{
	return ;
	int nErrNo = GetLastError();
	switch(nErrNo)
	{
	case WSANOTINITIALISED:
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("初始化错误") );
		break;
	case WSAENOTCONN:
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("对方没有启动"));
		break;
	case WSAEWOULDBLOCK :
		CLogPrint::LogString(XLOGLEVEL_ERROR,  _T("对方已经关闭"));
		break;
	case WSAECONNREFUSED:
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("连接的尝试被拒绝"));
		break;
	case WSAENOTSOCK:
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("在一个非套接字上尝试了一个操作"));
		break;
	case WSAEADDRINUSE:
		CLogPrint::LogString(XLOGLEVEL_ERROR,  _T("特定的地址已在使用中"));
		break;
	case WSAECONNRESET:
		CLogPrint::LogString(XLOGLEVEL_ERROR,  _T("与主机的连接被关闭"));
		break;
	}
}

//////////////////发送文件///////////////////////////////////////////////////
BOOL xfcenter_send_buf(SOCKET &sktSend, char *pBuffer, long nSendLen, XFCENTER_CMD_RET &cmdRet, char *pRecvBuff, long nTimeOut)
{
	//发送数据
	//???是否需要多次发送
	long nLen = 0;

	nLen = send(sktSend, pBuffer,  nSendLen, 0);

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Send nSendLen=%d  nLen = %d"), nSendLen, nLen);

	if (SOCKET_ERROR == nLen)
	{
		return FALSE;
	}

	//Sleep(100);

	long nLenRcv = 0;
	XFCENTER_CMD_RET *pCmdRet = NULL;
	CTickCount32 oTick;
	ZeroMemory(&cmdRet, sizeof(cmdRet));
	BOOL bLogError = TRUE;

	//接受接收方应答的消息
	while (TRUE)
	{
		//Sleep(5);
		nLenRcv = recv(sktSend, pRecvBuff, XFCENTER_RECV_MAX_LEN, 0);
		
		if (nLenRcv < 0 && bLogError)
		{
			xfcenter_log_error();
			bLogError = FALSE;
		}

		if (nLenRcv > 0)
		{
			pCmdRet = (XFCENTER_CMD_RET *)pBuffer;
			cmdRet = *pCmdRet;
			break;
		}
		else
		{
			Sleep(1);
		}

		if (nTimeOut > 0)
		{
			if (oTick.GetTickCountLong(FALSE) > nTimeOut)
			{
				break;
			}
		}
	}

	return (nLenRcv > 0);
}

BOOL xfcenter_send_file_info(SOCKET &sktSend, const CString &strFileName, XFCENTER_CMD_FILE_INFO &cmdFileInfo, char *pRecvBuffer,XFCENTER_CMD_RET &cmdRet, long nTimeOut)
{
	cmdFileInfo.dwCmdID = XFCENTER_CMDID_FILE_INFO;

	if (strFileName.GetLength() > 0)
	{
		if (!xfile_GetFileInfo(strFileName, cmdFileInfo.dwSize, cmdFileInfo.dtTime))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("File [%s] not exist"), strFileName);
			return FALSE;
		}
	}

	long nLenSend = sizeof(cmdFileInfo);

	if(!xfcenter_send_buf(sktSend, (char*)(&cmdFileInfo), nLenSend, cmdRet, pRecvBuffer, nTimeOut))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Send File [%s] info failed"), strFileName);
		return FALSE;
	}

	return TRUE;
}

UINT xfcenter_send_files(XFCENTER_THREAD_PARAM *pParam, SOCKET &sktSend)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR, _T("xfcenter_send_files---247"));
	long nCount = pParam->astrPath.GetSize();
	CString strRoot = pParam->strRootPath;

	long nFileIndex = 0;
	long nLenSend = 0;
	char pRecvBuffer[XFCENTER_RECV_BUF_LEN];
	XFCENTER_CMD_RET cmdRet;
	XFCENTER_CMD_FILE_BUF cmd_file_buf;
	XFCENTER_CMD_FILE_INFO cmdFileInfo;

	for (nFileIndex=0; nFileIndex<nCount; nFileIndex++)
	{
		//遍历文件列表
		CString strFileName = pParam->astrPath.GetAt(nFileIndex);
		//strFileName = GetFileNameFromFilePath(strFileName);
		ZeroMemory(&cmdFileInfo, sizeof(cmdFileInfo));
		CString_to_char_ex(strFileName, cmdFileInfo.pszPath);
		//strFileName = strRoot + strFileName;
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Send File [%s]"), strFileName);

		//第一步：发送文件信息
		if (!xfcenter_send_file_info(sktSend, strFileName, cmdFileInfo, pRecvBuffer, cmdRet, XFCENTER_TIME_OUT))
		{
			continue;
		}

		CFile file;
		file.Open(strFileName, CFile::modeRead | CFile::typeBinary);
		long nTotolLen = 0;

		cmd_file_buf.dwIndex = 0;
		cmd_file_buf.dwLen = 0;
		cmd_file_buf.dwCmdID = XFCENTER_CMDID_FILE_BUFF;
		
		///第二步：发送文件///////////////////////////////////////////
		while (1)
		{
			cmd_file_buf.dwLen = file.Read(cmd_file_buf.pBuffer, XFCENTER_FILE_BUF_LEN);

			//读文件结束
			if (cmd_file_buf.dwLen == 0)
			{
				if (g_bLogXFcenterTransInfo)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("-----------Read File [%s] Finish"), strFileName);
				}

				break;
			}

			nLenSend = xfcenter_get_file_buf_send_len(cmd_file_buf);//3*sizeof(DWORD) + cmd_file_buf.dwLen;			//DWORD dwCmdID;			DWORD dwIndex; 			DWORD dwLen; 
			if (g_bLogXFcenterTransInfo)CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("-----------Send [%d, %d] begin"), cmd_file_buf.dwIndex, cmd_file_buf.dwLen);
			
			if(!xfcenter_send_buf(sktSend, (char*)(&cmd_file_buf), nLenSend, cmdRet, pRecvBuffer, XFCENTER_TIME_OUT))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("************Send [%d] Error"), cmd_file_buf.dwIndex);
				//AfxMessageBox("发送线程UINT dlgSend(void *d)出错!");
				break;
			}
			else
			{
				if (g_bLogXFcenterTransInfo)CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("-----------Send [%d, %d] success"), cmd_file_buf.dwIndex, cmd_file_buf.dwLen);
			}

			nTotolLen += cmd_file_buf.dwLen;
			cmd_file_buf.dwIndex++;
			//pDlg->m_ctrCent.SetWindowText(cent);
		}

		file.Close();

		//第三步：发送文件传输完成消息
		cmd_file_buf.dwCmdID = XFCENTER_CMDID_FILE_FINISH;
		cmd_file_buf.dwIndex++;
		cmd_file_buf.dwLen = CString_to_char(strFileName, cmd_file_buf.pBuffer);
		nLenSend = xfcenter_get_file_buf_send_len(cmd_file_buf);//3*sizeof(DWORD) + cmd_file_buf.dwLen;
	
		if(!xfcenter_send_buf(sktSend, (char*)(&cmd_file_buf), nLenSend, cmdRet, pRecvBuffer, XFCENTER_TIME_OUT))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Send File [%s] info failed"), strFileName);
			break;
		}

		if (nTotolLen ==  cmdFileInfo.dwSize)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("File [%s] send success"), strFileName);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("File [%s] send failed"), strFileName);
		}
	}

	//最后：所有文件传输完毕，发送空文件信息表示结束
	ZeroMemory(&cmdFileInfo, sizeof(cmdFileInfo));
	xfcenter_send_file_info(sktSend, _T(""), cmdFileInfo, pRecvBuffer, cmdRet, XFCENTER_TIME_OUT);

	return 0;
}


//////////////////////////////////////////////////////////////////////////
//接收文件
BOOL xfcenter_recv_file_info(SOCKET &sktRecv, char *pRecvBuff, XFCENTER_CMD_FILE_INFO &cmdFileInfo, long nTimeOut)
{
	long nLen = 0;
	CTickCount32 oTick;
	XFCENTER_CMD_FILE_INFO *pCmdFileInfo = NULL;
	ZeroMemory(&cmdFileInfo, sizeof(cmdFileInfo));
	XFCENTER_CMD_RET cmdRet;
	BOOL bLogError = TRUE;

	while (TRUE)
	{
		nLen = recv(sktRecv, pRecvBuff, XFCENTER_BUF_LEN, 0);

		if (nLen < 0 && bLogError)
		{
			bLogError = FALSE;
			xfcenter_log_error();
		}

		if (nLen <= 0)
		{
			Sleep(5);
		}
		else
		{
			pCmdFileInfo = (XFCENTER_CMD_FILE_INFO *)pRecvBuff;

			if (pCmdFileInfo->dwCmdID == XFCENTER_CMDID_FILE_INFO)
			{
				cmdFileInfo = *pCmdFileInfo;
				cmdRet.dwCmdID = cmdFileInfo.dwCmdID;
				cmdRet.dwRcvIndex = 0;
				cmdRet.dwRcvLen = nLen;
				xfcenter_send_cmd_ret(sktRecv, cmdRet);
				break;
			}
		}

		if (nTimeOut > 0)
		{
			if (oTick.GetTickCountLong(FALSE) > nTimeOut)
			{
				break;
			}
		}
	}

	return (cmdFileInfo.dwCmdID == XFCENTER_CMDID_FILE_INFO);
}


//接收文件传输
XFCENTER_CMD_FILE_BUF* xfcenter_recv_file_buf(SOCKET &sktRecv, char *pRecvBuff, long nTimeOut)
{
	long nLen = 0;
	CTickCount32 oTick;
	XFCENTER_CMD_RET cmdRet;
	XFCENTER_CMD_FILE_BUF *pCmdFileBuff = NULL;
	long nLenRev = 0;
	long nLenNeedRev = 0;
	char *pRevBufPos = pRecvBuff;
	BOOL bLogError = TRUE;

	while (TRUE)
	{
		nLen = recv(sktRecv, pRevBufPos, XFCENTER_BUF_LEN, 0);
		
		if (nLen < 0 && bLogError)
		{
			bLogError = FALSE;
			xfcenter_log_error();
		}

		if (nLen <= 0)
		{
			Sleep(5);
		}
		else
		{
			pRevBufPos += nLen;
			nLenRev += nLen;

			if (pCmdFileBuff == NULL)
			{
				pCmdFileBuff = (XFCENTER_CMD_FILE_BUF *)pRecvBuff;
			}

			if (nLenRev > 12)
			{
				//全部接受完毕
				if (pCmdFileBuff->dwLen <= nLenRev - 12)
				{
					break;
				}
			}
		}

		if (nTimeOut > 0)
		{
			if (oTick.GetTickCountLong(FALSE) > nTimeOut)
			{
				break;
			}
		}
	}

	if (pCmdFileBuff != NULL)
	{
		cmdRet.dwCmdID = pCmdFileBuff->dwCmdID;
		cmdRet.dwRcvIndex = pCmdFileBuff->dwIndex;
		cmdRet.dwRcvLen = pCmdFileBuff->dwLen;
		xfcenter_send_cmd_ret(sktRecv, cmdRet);
	}

	return pCmdFileBuff;
}

BOOL xfcnter_create_file(const CString &strFilePath, CFile &oFile)
{
	CString strPath = GetPathFromFilePathName(strFilePath);
	CreateAllDirectories(strPath);

	return oFile.Open(strFilePath, CFile::modeCreate | CFile::modeWrite);
}

UINT xfcenter_recv_files(XFCENTER_THREAD_PARAM *pParam, SOCKET &sktRecv)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR, _T("xfcenter_recv_files---464"));
	long nFileIndex = 0;
	long nMaxRecvBuff = 0;
	char pRecvBuffer[XFCENTER_RECV_BUF_LEN];
	XFCENTER_CMD_FILE_INFO cmdFileInfo;
	CFile oFile;
	CString strFilePath;
	XFCENTER_CMD_FILE_BUF *pCmdFileBuf = NULL;

	while (TRUE)
	{
		//第一步：接受文件信息
		if (!xfcenter_recv_file_info(sktRecv, pRecvBuffer, cmdFileInfo, XFCENTER_TIME_OUT))
		{
			break;
		}

		//文件传输完毕
		if (cmdFileInfo.dwSize == 0 && cmdFileInfo.dtTime.wYear == 0 && cmdFileInfo.dtTime.wMonth == 0)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, _T("Receive Files finish"));
			break;
		}

		strFilePath = pParam->strRootPath;
		CString strFileName;
		strFileName = cmdFileInfo.pszPath;
		strFileName = GetFileNameFromFilePath(strFileName);
		strFilePath += strFileName;
		
		if (!xfcnter_create_file(strFilePath, oFile))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Create File[%s] failed!"), strFilePath);
			break;
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Create File [%s]"), strFilePath);
		}

		//第二步：接收文件数据、写文件
		while (TRUE)
		{
			pCmdFileBuf = xfcenter_recv_file_buf(sktRecv, pRecvBuffer, XFCENTER_TIME_OUT);

			if (pCmdFileBuf->dwCmdID == XFCENTER_CMDID_FILE_BUFF)
			{
				if (g_bLogXFcenterTransInfo)CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("-------- Write File [%d]"), pCmdFileBuf->dwIndex);
				oFile.Write(pCmdFileBuf->pBuffer, pCmdFileBuf->dwLen);
			}
			else if (pCmdFileBuf->dwCmdID == XFCENTER_CMDID_FILE_FINISH)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Write File [%s] finished"), strFilePath);
				oFile.Close();
				break;
			}
		}
	}

	return 0;
}

UINT xfcenter_send_query_files(XFCENTER_THREAD_PARAM *pParam, SOCKET &sktSend)
{
/*	CStringArray astrFiles;
	char pRecvBuffer[XFCENTER_RECV_BUF_LEN];
	long nLenSend = 0, nFileCount = 0, nFileIndex = 0, nLen = 0;
	XFCENTER_CMD_RET cmdRet;
	XFCENTER_CMD_FILE_BUF cmd_file_buf;
	char *pBuffer = NULL;
	CString strFile;
	CXFolder *pFolder = NULL;
	CString strPath;
	
	//获取需要检索的路径信息
	if (pParam->astrPath.GetCount() > 0)
	{
		strPath = pParam->astrPath.GetAt(0);
	}

	if (strPath.GetLength() > 0)
	{
		pFolder = xfile_SelectFolder_RelPath(pParam->pXFileMngr, strPath);
	}
	else
	{
		pFolder = pParam->pXFileMngr;
	}

	//获得所有的文件
	if (pParam->astrKeys.GetCount() == 0)
	{
		xfile_QueryAllFiles(pFolder, astrFiles);
	}
	else
	{
		if (pParam->dwKeysMode == XFCENTER_QUERY_MODE_AND)
		{
			xfile_QueryAllFiles_And(pFolder, pParam->astrKeys, astrFiles);
		}
		else
		{
			xfile_QueryAllFiles_Or(pFolder, pParam->astrKeys, astrFiles);
		}
	}

	cmd_file_buf.dwCmdID = XFCENTER_CMDID_QUERY_FILES_BUF;
	cmd_file_buf.dwIndex = 0;
	cmd_file_buf.dwLen = 0;
	nFileCount = astrFiles.GetCount();

	while (TRUE)
	{
		ZeroMemory(cmd_file_buf.pBuffer, XFCENTER_FILE_BUF_LEN);
		cmd_file_buf.dwIndex = 0;
		pBuffer = cmd_file_buf.pBuffer;
		cmd_file_buf.dwLen = 0;

		while (cmd_file_buf.dwLen < XFCENTER_FILE_BUF_LEN - MAX_PATH)
		{
			if (nFileIndex >= nFileCount)
			{
				break;
			}

			//拼接文件名称缓冲区
			strFile = astrFiles.GetAt(nFileIndex);
			nLen = CString_to_char_ex(strFile, pBuffer) + 1;
			pBuffer += nLen;
			cmd_file_buf.dwLen += nLen;
			nFileIndex++;
			cmd_file_buf.dwIndex++; //文件名称的数量
		}

		if (cmd_file_buf.dwLen > 0)
		{
			nLenSend = xfcenter_get_file_buf_send_len(cmd_file_buf);

			if(!xfcenter_send_buf(sktSend, (char*)(&cmd_file_buf), nLenSend, cmdRet, pRecvBuffer, XFCENTER_TIME_OUT))
			{
				break;
			}
		}

		//如果全部传送完毕
		if (nFileIndex >= nFileCount)
		{
			break;
		}
	}

	cmd_file_buf.dwCmdID = XFCENTER_CMDID_QUERY_FILES_FINISH;
	cmd_file_buf.dwIndex = 0;
	cmd_file_buf.dwLen = CString_to_char_ex(pParam->pXFileMngr->m_strYunRootPath, cmd_file_buf.pBuffer) + 1;
	nLenSend = xfcenter_get_file_buf_send_len(cmd_file_buf);
	xfcenter_send_buf(sktSend, (char*)(&cmd_file_buf), nLenSend, cmdRet, pRecvBuffer, XFCENTER_TIME_OUT);

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("send query files finished"));
*/
	return 0;
}

UINT xfcenter_recv_query_files(XFCENTER_THREAD_PARAM *pParam, SOCKET &sktRecv)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR, _T("xfcenter_recv_query_files---628"));
/*	long nFileIndex = 0;
	long nMaxRecvBuff = 0;
	char pRecvBuffer[XFCENTER_RECV_BUF_LEN];
	XFCENTER_CMD_FILE_BUF *pCmdFileBuf = NULL;
	CString strFile;
	CStringArray astrFiles;
	char *pBuffer = NULL;
	char *pBufferEnd = NULL;
	CXFileMngr *pXFileMngr = pParam->pXFileMngr;

	while (TRUE)
	{
		pCmdFileBuf = xfcenter_recv_file_buf(sktRecv, pRecvBuffer, XFCENTER_TIME_OUT);

		if (pCmdFileBuf->dwCmdID == XFCENTER_CMDID_QUERY_FILES_BUF)
		{
			pBuffer = pCmdFileBuf->pBuffer;
			pBufferEnd = pBuffer + pCmdFileBuf->dwLen;
			nFileIndex = 0;

			while (pBuffer < pBufferEnd)
			{
				strFile = pBuffer;
				//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s"), strFile);

				if (strFile.Right(1) == _T("\\"))
				{
					xfcenter_add_folder(pXFileMngr, strFile);
				}
				else
				{
					xfcenter_add_file(pXFileMngr, strFile);
				}

				nFileIndex++;

				while (*pBuffer != 0)
				{
					pBuffer++;
				}

				while ((*pBuffer == 0) && (pBuffer < pBufferEnd))
				{
					pBuffer++;
				}
			}

			if (nFileIndex != pCmdFileBuf->dwIndex)
			{//数量不对应

			}
		}
		else if (pCmdFileBuf->dwCmdID == XFCENTER_CMDID_QUERY_FILES_FINISH)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("query files finished"));
			break;
		}
	}
*/
	return 0;
}

/*
CXFileMngr* xfcenter_find_filemngr(CExBaseList *pList, const CString &strBucket)
{
	POS pos = pList->GetHeadPosition();
	CXFileMngr *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CXFileMngr *)pList->GetNext(pos);

		if (p->m_strYunRootPath == strBucket)
		{
			pFind = p;
			break;
		}
	}

	if (pFind == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Find FileMngr [%s] = NULL"), strBucket);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Find FileMngr [%s] = [%s]"), strBucket, pFind->m_strRootPath);
	}

	return pFind;
}
*/

BOOL xfcenter_set_send_timeout(SOCKET hSocket, int nSecond)
{
	if( nSecond < 0 )
	{
		return FALSE;
	}

// 	struct timeval tmOut;
// 	tmOut.tv_sec = nSecond;
// 	tmOut.tv_usec = 0;
	nSecond *= 1000;

	if( setsockopt( hSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&nSecond, sizeof( nSecond ) ) == SOCKET_ERROR )
	{
		return FALSE;
	}

	return TRUE;
}


BOOL xfcenter_set_recv_timeout(SOCKET hSocket, int nSecond)
{
	if( nSecond < 0 )
	{
		return FALSE;
	}

// 	struct timeval tmOut;
// 	tmOut.tv_sec = nSecond;
// 	tmOut.tv_usec = 0;
	nSecond *= 1000;

	if( setsockopt( hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&nSecond, sizeof( nSecond ) ) == SOCKET_ERROR )
	{
		return FALSE;
	}

	return TRUE;
}

BOOL xfcenter_set_connect_timeout(SOCKET hSocket, int nSecond)
{
	return xfcenter_set_send_timeout(hSocket, nSecond);
}

BOOL xfcenter_set_accept_timeout(SOCKET hSocket, int nSecond)
{
	return xfcenter_set_recv_timeout(hSocket, nSecond);
}


bool ConnectWithTimeout(SOCKET &sktDest, XFCENTER_THREAD_PARAM *pThreadParam, int timeout)
{
	sktDest = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if(sktDest==INVALID_SOCKET)
	{
		return FALSE;
	}

	SOCKADDR_IN addrRecv;
	addrRecv.sin_family = AF_INET;
	addrRecv.sin_addr.S_un.S_addr = inet_addr(pThreadParam->pszServerIP);
	addrRecv.sin_port = htons(pThreadParam->nServerPort);
	int nRet = connect(sktDest,(SOCKADDR*)&addrRecv,sizeof(SOCKADDR));

	return (nRet == 0); 
}
// 
// UINT xfcenter_client_thread(LPVOID pParam)
// {
// 	XFCENTER_THREAD_PARAM *pThreadParam = (XFCENTER_THREAD_PARAM*)pParam;
// 	SOCKET destSocket;
// 	// 	destSocket = socket(AF_INET, SOCK_STREAM, 0);
// 
// 	/////////////////////用套接字连接服务器//////////////////////////////////////////
// 	long nIndex = 0;
// 	BOOL bConnectSucc = FALSE;
// 
// 	while (nIndex <= 10)
// 	{
// 		bConnectSucc = ConnectWithTimeout(destSocket, pThreadParam, 1000);
// 
// 		if (bConnectSucc)
// 		{
// 			break;
// 		}
// 
// 		nIndex++;
// 	}
// 
// 	if ( !bConnectSucc)
// 	{
// 		closesocket(destSocket);
// 		return 0;
// 	}
// 
// 	if (pThreadParam->nCmdID == XFCENTER_OPTR_SVR_TO_CLIENT) //发送文件
// 	{
// 		xfcenter_send_files(pThreadParam, destSocket);
// 	}
// 	else if (pThreadParam->nCmdID == XFCENTER_OPTR_CLIENT_TO_SVR) //接收文件
// 	{
// 		xfcenter_recv_files(pThreadParam, destSocket);
// 	}
// 	else if (pThreadParam->nCmdID == XFCENTER_OPTR_QUERY) //查询文件
// 	{
// 		xfcenter_send_query_files(pThreadParam, destSocket);
// 	}
// 
// 	shutdown(destSocket, 2);
// 	closesocket(destSocket);
// 
// 	delete pThreadParam;
// 
// 	return 0;
// }


UINT xfcenter_server_thread_use_own(LPVOID pParam)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR, _T("xfcenter_server_thread---118"));
	XFCENTER_THREAD_PARAM *pThreadParam = (XFCENTER_THREAD_PARAM*)pParam;
	SOCKET sktClient = pThreadParam->sktClient;

	if (pThreadParam->nCmdID == XFCENTER_OPTR_SVR_TO_CLIENT) //发送文件
	{
		xfcenter_send_files(pThreadParam, sktClient);
	}
	else if (pThreadParam->nCmdID == XFCENTER_OPTR_CLIENT_TO_SVR) //接收文件
	{
		xfcenter_recv_files(pThreadParam, sktClient);
	}
	else if (pThreadParam->nCmdID == XFCENTER_OPTR_QUERY) //查询文件
	{
		xfcenter_send_query_files(pThreadParam, sktClient);
	}

	xfcenter_set_thread_finish(pThreadParam);
	AfxGetMainWnd()->PostMessage(WM_USER+2338, (WPARAM)pThreadParam->sktClientRef, (LPARAM)sktClient);

	delete pThreadParam;

	CLogPrint::LogString(XLOGLEVEL_INFOR, _T("xfcenter_server_thread---145"));
	return 0;
}

UINT xfcenter_client_thread_use_own(LPVOID pParam)
{
	XFCENTER_THREAD_PARAM *pThreadParam = (XFCENTER_THREAD_PARAM*)pParam;
	SOCKET destSocket = pThreadParam->sktClient;

	/////////////////////用套接字连接服务器//////////////////////////////////////////
	long nIndex = 0;
	BOOL bConnectSucc = FALSE;

	if (pThreadParam->nCmdID == XFCENTER_OPTR_SVR_TO_CLIENT) //发送文件
	{
		xfcenter_recv_files(pThreadParam, destSocket);
	}
	else if (pThreadParam->nCmdID == XFCENTER_OPTR_CLIENT_TO_SVR) //接收文件
	{
		xfcenter_send_files(pThreadParam, destSocket);
	}
	else if (pThreadParam->nCmdID == XFCENTER_OPTR_QUERY) //查询文件
	{
		xfcenter_recv_query_files(pThreadParam, destSocket);
	}

	AfxGetMainWnd()->SendMessage(WM_USER+2338, (WPARAM)pThreadParam->sktClientRef, (LPARAM)destSocket);
	xfcenter_set_thread_finish(pThreadParam);

	delete pThreadParam;

	return 0;
}

SOCKET xfcenter_accept(XFCENTER_THREAD_PARAM *pThreadParam, long nTimeOut)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR, _T("xfcenter_accept ---- 70"));
	SOCKET sktListen;
	SOCKADDR_IN addrListen;
	addrListen.sin_family = AF_INET;

	addrListen.sin_port = htons(pThreadParam->nServerPort);
	addrListen.sin_family = AF_INET;
	addrListen.sin_addr.s_addr = inet_addr(pThreadParam->pszServerIP);//htonl(INADDR_ANY);

	if((sktListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET)
		return INVALID_SOCKET;

	if (bind(sktListen,(SOCKADDR *)&addrListen,sizeof(SOCKADDR))==SOCKET_ERROR)
		return INVALID_SOCKET;

	if (listen(sktListen, SOMAXCONN) == SOCKET_ERROR)
		return INVALID_SOCKET;

	SOCKET sktAccept;
	sockaddr_in addr;
	int len = sizeof(addr);

	CLogPrint::LogString(XLOGLEVEL_INFOR, _T("xfcenter_accept ---- 92"));
	while(TRUE)
	{
		sktAccept = accept(sktListen, NULL, NULL );

		if (sktAccept != INVALID_SOCKET)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR, _T("xfcenter_accept ---- 99"));
			break;
		}

		Sleep(50);
	}

	closesocket(sktListen);
	// 	while((AcceptSocket = accept(sktListen, (sockaddr*)&addr, &len)) == INVALID_SOCKET )
	// 	{
	// 		Sleep(50);
	// 	}

	CLogPrint::LogString(XLOGLEVEL_INFOR, _T("xfcenter_accept ---- 112"));
	return sktAccept;
}

// UINT xfcenter_server_thread(LPVOID pParam)
// {
// 	CLogPrint::LogString(XLOGLEVEL_INFOR, _T("xfcenter_server_thread---118"));
// 	XFCENTER_THREAD_PARAM *pThreadParam = (XFCENTER_THREAD_PARAM*)pParam;
// 	SOCKET sendSocket;
// 	sendSocket = xfcenter_accept(pThreadParam, XFCENTER_TIME_OUT);
// 
// 	if (sendSocket == INVALID_SOCKET)
// 	{
// 		xfcenter_set_thread_finish(pThreadParam);
// 		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("xfcenter_server_thread---122"));
// 		return 0;
// 	}
// 
// 	if (pThreadParam->nCmdID == XFCENTER_OPTR_SVR_TO_CLIENT) //发送文件
// 	{
// 		xfcenter_send_files(pThreadParam, sendSocket);
// 	}
// 	else if (pThreadParam->nCmdID == XFCENTER_OPTR_CLIENT_TO_SVR) //接收文件
// 	{
// 		xfcenter_recv_files(pThreadParam, sendSocket);
// 	}
// 	else if (pThreadParam->nCmdID == XFCENTER_OPTR_QUERY) //查询文件
// 	{
// 		xfcenter_recv_query_files(pThreadParam, sendSocket);
// 	}
// 
// 	closesocket(sendSocket);
// 	shutdown(sendSocket, 2);
// 
// 	xfcenter_set_thread_finish(pThreadParam);
// 	delete pThreadParam;
// 
// 	CLogPrint::LogString(XLOGLEVEL_INFOR, _T("xfcenter_server_thread---145"));
// 	return 0;
// }

