#include "stdafx.h"
#include "SttFileToolMngr.h"
#include "../../Module/System/TickCount32.h"
#include "SttSocket/SttCmdOverTimeMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttFileToolMngr* CSttFileToolMngr::g_pSttFileToolMngr = NULL;
long CSttFileToolMngr::g_nSttFileToolMngrRef = 0;

CSttFileToolMngr::CSttFileToolMngr()
{

}

CSttFileToolMngr::~CSttFileToolMngr()
{

}

CSttFileToolMngr *CSttFileToolMngr::Create()
{
	g_nSttFileToolMngrRef++;

	if (g_nSttFileToolMngrRef == 1)
	{
		g_pSttFileToolMngr = new CSttFileToolMngr();
	}

	return g_pSttFileToolMngr;
}

void CSttFileToolMngr::Release()
{
	g_nSttFileToolMngrRef--;

	if (g_nSttFileToolMngrRef == 0)
	{
		delete g_pSttFileToolMngr;
		g_pSttFileToolMngr = NULL;
	}
}

CSttFileToolMngr *CSttFileToolMngr::GetSttFileToolMngr()
{
	return g_pSttFileToolMngr;
}

BOOL CSttFileToolMngr::IsSocketExist(CSttSocketDataBase_File *pSocket)
{
	POS pos = GetHeadPosition();
	CSttSocketDataBase_File *p = NULL;

	while(pos != NULL)
	{
		p = (CSttSocketDataBase_File *)GetNext(pos);

		if (p == pSocket)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CSttFileToolMngr::AddSocketRef(CSttSocketDataBase_File *pSocket)
{
	CAutoSimpleLock oLock(g_pSttFileToolMngr->m_oCriticSection);

	if (g_pSttFileToolMngr->IsSocketExist(pSocket))
	{
		return FALSE;
	}

	g_pSttFileToolMngr->AddTail(pSocket);
	return TRUE;

}

void CSttFileToolMngr::ReleaseSocketRef(CSttSocketDataBase_File *pSocket)
{
	CAutoSimpleLock oLock(g_pSttFileToolMngr->m_oCriticSection);

	g_pSttFileToolMngr->Remove(pSocket);
}


///////////////////文件上传下载工具类///////////////////////

CSttFileTool::CSttFileTool()
{
	m_pSocket = NULL;
	m_nRetResult = STT_CMD_RET_RESULT_NULL;
	m_bSendFile = TRUE;

	m_nCurrSendIndex = 0;
	m_bIsBlock = FALSE;
	m_bIsSocketRef = FALSE;;
	m_pProgress = NULL;
	m_pCmdOverTimeMsgRcv = NULL;
	m_nSTT_PKG_SEND_FILEDATA_MAXLEN = STT_PKG_SEND_FILEDATA_MAXLEN;

}

CSttFileTool::~CSttFileTool()
{
	Free();
}

void CSttFileTool::Free()
{
	if (m_bIsSocketRef)
	{
		DettachSttSocket();
	}
	else
	{
		if (m_pSocket)
		{
			m_pSocket->CloseSocket();
            m_pSocket->WaitForThreadExit();
			delete m_pSocket;
			m_pSocket = NULL;
		}
	}

	DeleteAll();
}

void CSttFileTool::TransferStart(const CString &strFile, long nTotalSize)
{
	if (m_pProgress != NULL)
	{
		m_pProgress->TransferStart(strFile, nTotalSize);
	}
}

void CSttFileTool::TransferStep(long nCurrSendSize)
{
	if (m_pProgress != NULL)
	{
		m_pProgress->TransferStep(nCurrSendSize);
	}
}

void CSttFileTool::TransferFinish(const CString &strFile)
{
	if (m_pProgress != NULL)
	{
		m_pProgress->TransferFinish(strFile);
	}

	if (m_bIsBlock)
	{
		SetRetResult_Finish();
	}
	else
	{
		if(m_bSendFile)
		{
			SendNextFile();
		}
		else
		{
			DownloadNextFile();
		}
	}
}

void CSttFileTool::TransferError(const CString &strFile,long nErrNo)
{
	if (m_pProgress != NULL)
	{
		m_pProgress->TransferError(strFile,nErrNo);
	}
}

void CSttFileTool::Init(CStringArray &strArray)
{
	strArray.RemoveAll();

	POS pos = GetHeadPosition();
	CSttXftpFile *p = NULL;

	while(pos != NULL)
	{
		p = (CSttXftpFile *)GetNext(pos);

		strArray.Add(p->m_strLocalFile);
	}

	if (m_pProgress != NULL)
	{
		m_pProgress->Init(strArray);
	}
}

void CSttFileTool::OnSendCmdFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
{
	if (m_pCmdOverTimeMsgRcv != NULL)
	{	
		m_pCmdOverTimeMsgRcv->OnSendCmdFinish(pSocketRef,nCmdType,pszCmdID);		
	}
}

void CSttFileTool::OnSendCmdFailFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
{
	if (m_pCmdOverTimeMsgRcv != NULL)
	{	
		m_pCmdOverTimeMsgRcv->OnSendCmdFailFinish(pSocketRef,nCmdType,pszCmdID);		
	}

	if (!m_bIsBlock)
	{
		Free();
	}

	SetRetResult_Failure();
}

void CSttFileTool::OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
{
	if (m_pCmdOverTimeMsgRcv != NULL)
	{	
		m_pCmdOverTimeMsgRcv->OnSendCmdOverTime(pSocketRef,nCmdType,pszCmdID);		
	}

	if (m_pProgress != NULL)
	{
        m_pProgress->TransferError(_T(""),0);
	}

	((CSttSocketDataBase_File *)pSocketRef)->ProcessCmd_End();

	if (!m_bIsBlock)
	{
		Free();
	}

	SetRetResult_Timeout();
}

void CSttFileTool::AttachSttSocketFileTransferProgress(CSttSocketFileTransferProgress *pProgress)
{
	m_pProgress = pProgress;
}

void CSttFileTool::AttachSttCmdOverTimeMsgRcv(CSttCmdOverTimeMsgRcv *pCmdOverTimeMsgRcv)
{
	m_pCmdOverTimeMsgRcv = pCmdOverTimeMsgRcv;
}

BOOL CSttFileTool::ConnectServer(const CString &strIP,long nPort)
{
	m_pSocket = new CSttSocketDataBase_File;
	m_bIsSocketRef = FALSE;
	
	return m_pSocket->ConnectServer(strIP,nPort);
}

void CSttFileTool::AddFile(const CString &strLocalFile, const CString &strRemoteFile)
{
	CSttXftpFile *pNew = new CSttXftpFile;
	pNew->m_strLocalFile = strLocalFile;
	pNew->m_strRemoteFile = strRemoteFile;
	AddTail(pNew);
}

void CSttFileTool::InitBefore()
{
// 	m_pSocket->AttachFileTransferProgress(this);
// 	m_pSocket->AttachCmdOverTimeMsgRcv(this);

	CStringArray strArray;
	Init(strArray);
}

BOOL CSttFileTool::SendFiles(BOOL bBlock)
{
	InitBefore();

	//目前只支持阻塞模式
	bBlock = TRUE;
	m_bIsBlock = bBlock;
	m_bSendFile = TRUE;
	
// 	__try
// 	{
		if (bBlock)
		{
			return SendFiles_Block();
		}
		else
		{
			return SendFiles_NonBlock();
		}
//	}
// 	__finally
// 	{
// 		//命令结束结束后必须清除绑定
// 		m_pSocket->DetachFileTransferProgress();
// 		m_pSocket->DetachCmdOverTimeMsgRcv();
// 	}
}

BOOL CSttFileTool::DownloadFiles(BOOL bBlock)
{
	InitBefore();

	//目前只支持阻塞模式
	bBlock = TRUE;
	m_bIsBlock = bBlock;
	m_bSendFile = FALSE;
	
//	__try{
		if (bBlock)
		{
			return DownloadFiles_Block();
		}
		else
		{
			return DownloadFiles_NonBlock();
		}
// 	}
// 	__finally
// 	{
// 		m_pSocket->DetachFileTransferProgress();
// 		m_pSocket->DetachCmdOverTimeMsgRcv();
// 	}
}

BOOL CSttFileTool::AttachSttSocket(CSttSocketDataBase_File *pSocket)
{
	if (!CSttFileToolMngr::AddSocketRef(pSocket))
	{
		return FALSE;
	}

	m_pSocket = pSocket;
	m_bIsSocketRef = TRUE;

	return TRUE;
}

void CSttFileTool::DettachSttSocket()
{
	if (!m_bIsSocketRef)
	{
		return;
	}

	CSttFileToolMngr::ReleaseSocketRef(m_pSocket);
	m_pSocket = NULL;
	m_bIsSocketRef = FALSE;
}

BOOL CSttFileTool::SendFiles_Block()
{
	long nCount = GetCount();
	CTickCount32 oTickCount32(FALSE);

	m_nCurrSendIndex = 0;

	while (m_nCurrSendIndex < nCount)
	{
		SendCurrFile();

		while(TRUE)
		{
			oTickCount32.DoEvents(10);
			if (IsRetResult_Finish() 
				|| IsRetResult_Failure() 
				|| IsRetResult_Timeout())
			{
				break;
			}		
		}

		if (IsRetResult_Failure() || IsRetResult_Timeout())
		{
			return FALSE;   //超时了，就不继续发送文件了
		}
			
		m_nCurrSendIndex++;
	}

	return TRUE;
}

BOOL CSttFileTool::SendFiles_NonBlock()
{
	m_nCurrSendIndex = 0;
	return SendCurrFile();
}

BOOL CSttFileTool::SendCurrFile()
{
	m_pSocket->AttachFileTransferProgress(this);
	m_pSocket->AttachCmdOverTimeMsgRcv(this);

	CSttXftpFile *pFile = (CSttXftpFile*)GetAtIndex(m_nCurrSendIndex);
	m_pSocket->SendFile(pFile->m_strLocalFile, pFile->m_strRemoteFile,g_nFileCmdTimeOut,FALSE);
	SetRetResult_Proccessing();

	return TRUE;
}

BOOL CSttFileTool::SendNextFile()
{
	m_nCurrSendIndex++;

	OnSendCmdFinish(m_pSocket,STT_CMD_TYPE_FILE_WRITE,NULL);

	if (m_nCurrSendIndex >= GetCount())
	{
		if (!m_bIsBlock)
		{
			Free();
		}
	}
	else
	{
		return SendCurrFile();
	}

	return TRUE;
}


BOOL CSttFileTool::DownloadFiles_Block()
{
	long nCount = GetCount();
	CTickCount32 oTickCount32(FALSE);

	m_nCurrSendIndex = 0;

	while (m_nCurrSendIndex < nCount)
	{
		DownloadCurrFile();

		while(TRUE)
		{
			oTickCount32.DoEvents(10);
			if (IsRetResult_Finish() 
				|| IsRetResult_Failure() 
				|| IsRetResult_Timeout())
			{
				break;
			}		
		}

		if (IsRetResult_Failure() || IsRetResult_Timeout())
		{
			return FALSE;   //超时了，就不继续发送文件了
		}
			
		m_nCurrSendIndex++;
	}

	return TRUE;
}

BOOL CSttFileTool::DownloadFiles_NonBlock()
{
	m_nCurrSendIndex = 0;
	return DownloadCurrFile();
}

BOOL CSttFileTool::DownloadCurrFile()
{
	m_pSocket->AttachFileTransferProgress(this);
	m_pSocket->AttachCmdOverTimeMsgRcv(this);

	CSttXftpFile *pFile = (CSttXftpFile*)GetAtIndex(m_nCurrSendIndex);
	m_pSocket->DownloadFile(pFile->m_strLocalFile, pFile->m_strRemoteFile, g_nFileCmdTimeOut);
	SetRetResult_Proccessing();

	return TRUE;
}

BOOL CSttFileTool::DownloadNextFile()
{
	m_nCurrSendIndex++;

	OnSendCmdFinish(m_pSocket,STT_CMD_TYPE_FILE_READ,NULL);

	if (m_nCurrSendIndex >= GetCount())
	{
		if (!m_bIsBlock)
		{
			Free();
		}
	}
	else
	{
		return DownloadCurrFile();
	}

	return TRUE;
}


void CSttFileTool::SetRetResult_NULL()
{
	m_nRetResult = STT_CMD_RET_RESULT_NULL;
}

void CSttFileTool::SetRetResult_Proccessing()
{
	m_nRetResult = STT_CMD_RET_RESULT_PROCESSING;
}

void CSttFileTool::SetRetResult_Failure()
{
	m_nRetResult = STT_CMD_RET_RESULT_FAILURE;
}

void CSttFileTool::SetRetResult_Timeout()
{
	m_nRetResult = STT_CMD_RET_RESULT_TIMEOUT;
}

void CSttFileTool::SetRetResult_Finish()
{
	m_nRetResult = STT_CMD_RET_RESULT_FINISH;
}

BOOL CSttFileTool::IsRetResult_NULL()
{
	return m_nRetResult==STT_CMD_RET_RESULT_NULL;
}

BOOL CSttFileTool::IsRetResult_Proccessing()
{
	return m_nRetResult==STT_CMD_RET_RESULT_PROCESSING;
}

BOOL CSttFileTool::IsRetResult_Finish()
{
	return m_nRetResult==STT_CMD_RET_RESULT_FINISH;
}

BOOL CSttFileTool::IsRetResult_Failure()
{
	return m_nRetResult==STT_CMD_RET_RESULT_FAILURE;
}

BOOL CSttFileTool::IsRetResult_Timeout()
{
	return m_nRetResult==STT_CMD_RET_RESULT_TIMEOUT;
}
