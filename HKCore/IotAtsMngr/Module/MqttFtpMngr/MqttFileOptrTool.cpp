#include "stdafx.h"
#include "MqttFileOptrTool.h"
#include "../../../Module/System/TickCount32.h"
#include "../SttMqttClientTool.h"
#include "../SttMqttClientEngineConfig.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CMqttFileOptrTool g_oMqttFileOptrTool;

CMqttFileOptrTool::CMqttFileOptrTool()
{
	m_nRetResult = STT_CMD_RET_RESULT_NULL;
	m_bSendFile = TRUE;
	m_nCurrSendIndex = 0;
	m_nSTT_PKG_SEND_FILEDATA_MAXLEN = STT_PKG_SEND_FILEDATA_MAXLEN;

	m_pProgress = NULL;
	m_pCurMqttFileOptr = NULL;
}

CMqttFileOptrTool::~CMqttFileOptrTool()
{
	Free();
}

void CMqttFileOptrTool::InitProgressDlg()
{
	m_oSttXFtpProgressDlg.SetUseModeless(TRUE);
	m_oSttXFtpProgressDlg.DoModal();
	m_pProgress = &m_oSttXFtpProgressDlg;
	m_oSttXFtpProgressDlg.ShowWindow(FALSE);
}

void CMqttFileOptrTool::SubcribeFtpToic()
{
	CString strSrcID,strDstID;
	strSrcID = CSttMqttClientTool::GetClientID();
	CSttMqttClientEngineConfig::GetMqttFtpServerIP(strDstID);
	SetID(strSrcID,strDstID);

	CString strTopic1,strTopic2,strTopic3,strTopic4;
	strTopic1.Format(_T("%s/%s/UploadCmd/UploadFileName/Reply"),strDstID,strSrcID);
	strTopic2.Format(_T("%s/%s/UploadCmd/UploadFileData/Reply"),strDstID,strSrcID);
	strTopic3.Format(_T("%s/%s/DownloadCmd/UploadFileName"),strDstID,strSrcID);
	strTopic4.Format(_T("%s/%s/DownloadCmd/UploadFileData"),strDstID,strSrcID);

	CSttMqttClientTool::SubscribeTopic(strTopic1,0);
	CSttMqttClientTool::SubscribeTopic(strTopic2,0);
	CSttMqttClientTool::SubscribeTopic(strTopic3,0);
	CSttMqttClientTool::SubscribeTopic(strTopic4,0);
}

void CMqttFileOptrTool::Free()
{
	if (m_pCurMqttFileOptr != NULL)
	{
		delete m_pCurMqttFileOptr;
		m_pCurMqttFileOptr = NULL;
	}
}

void CMqttFileOptrTool::SetID(const CString &strSrcID,const CString &strDstID)
{
	m_strSrcID = strSrcID;
	m_strDstID = strDstID;
}

void CMqttFileOptrTool::TransferStart(const CString &strFile, long nTotalSize)
{
	if (m_pProgress != NULL)
	{
		m_pProgress->TransferStart(strFile, nTotalSize);
	}
}

void CMqttFileOptrTool::TransferStep(long nCurrSendSize)
{
	if (m_pProgress != NULL)
	{
		m_pProgress->TransferStep(nCurrSendSize);
	}
}

void CMqttFileOptrTool::TransferFinish(const CString &strFile)
{
	if (m_pProgress != NULL)
	{
		m_pProgress->TransferFinish(strFile);
	}
}

void CMqttFileOptrTool::TransferError(const CString &strFile,long nErrNo)
{
	if (m_pProgress != NULL)
	{
		m_pProgress->TransferError(strFile,nErrNo);
	}
}

void CMqttFileOptrTool::Init(CStringArray &strArray)
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

void CMqttFileOptrTool::OnSendCmdFinish(const char *pszSrcID, const char *pszCmdType)
{
	Free();
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnSendCmdFinish:[%s][%s]"),pszSrcID,pszCmdType);

	SetRetResult_Finish();
}

void CMqttFileOptrTool::OnSendCmdFailFinish(const char *pszSrcID, const char *pszCmdType,UINT nErrCode)
{
	Free();
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnSendCmdFailFinish:[%s][%s][%d]"),pszSrcID,pszCmdType,nErrCode);

	SetRetResult_Failure();
}

void CMqttFileOptrTool::OnSendCmdOverTime(const char *pszSrcID, const char *pszTopic)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnSendCmdOverTime:[%s][%s]"),pszSrcID,pszTopic);

	if (m_pProgress != NULL)
	{
		m_pProgress->TransferError(_T(""),0);
	}

	SetRetResult_Timeout();
}

void CMqttFileOptrTool::InitBefore()
{
	CStringArray strArray;
	Init(strArray);
}

void CMqttFileOptrTool::AddFile(const CString &strLocalFile, const CString &strRemoteFile)
{
	CSttXftpFile *pNew = new CSttXftpFile;
	pNew->m_strLocalFile = strLocalFile;
	pNew->m_strRemoteFile = strRemoteFile;
	AddTail(pNew);
}

BOOL CMqttFileOptrTool::SendCurrFile()
{
	Free();

	m_pCurMqttFileOptr = new CMqttFileOptr;
	m_pCurMqttFileOptr->AttachFileTransferProgress(this);
	m_pCurMqttFileOptr->AttachCmdOverTimeMsgRcv(this);
	m_pCurMqttFileOptr->SetID(m_strSrcID,m_strDstID);

	CSttXftpFile *pFile = (CSttXftpFile*)GetAtIndex(m_nCurrSendIndex);
	m_pCurMqttFileOptr->SendFile(pFile->m_strLocalFile, pFile->m_strRemoteFile,FALSE);
	SetRetResult_Proccessing();

	return TRUE;
}

BOOL CMqttFileOptrTool::DownloadCurrFile()
{
	Free();

	m_pCurMqttFileOptr = new CMqttFileOptr;
	m_pCurMqttFileOptr->AttachFileTransferProgress(this);
	m_pCurMqttFileOptr->AttachCmdOverTimeMsgRcv(this);
	m_pCurMqttFileOptr->SetID(m_strSrcID,m_strDstID);

	CSttXftpFile *pFile = (CSttXftpFile*)GetAtIndex(m_nCurrSendIndex);
	m_pCurMqttFileOptr->DownloadFile(pFile->m_strLocalFile, pFile->m_strRemoteFile);
	SetRetResult_Proccessing();

	return TRUE;
}

BOOL CMqttFileOptrTool::SendFiles()
{
	InitBefore();
	m_bSendFile = TRUE;

	long nCount = GetCount();
	CTickCount32 oTickCount32;

	m_nCurrSendIndex = 0;
	BOOL bRet = TRUE;

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
			bRet = FALSE;
			break;
		}

		m_nCurrSendIndex++;
	}

	Free();
	return bRet;
}

BOOL CMqttFileOptrTool::DownloadFiles()
{
	InitBefore();
	m_bSendFile = FALSE;

	long nCount = GetCount();
	CTickCount32 oTickCount32;

	m_nCurrSendIndex = 0;
	BOOL bRet = TRUE;

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
			bRet = FALSE;
			break;
		}

		m_nCurrSendIndex++;
	}

	Free();
	return TRUE;
}

void CMqttFileOptrTool::SetRetResult_NULL()
{
	m_nRetResult = STT_CMD_RET_RESULT_NULL;
}

void CMqttFileOptrTool::SetRetResult_Proccessing()
{
	m_nRetResult = STT_CMD_RET_RESULT_PROCESSING;
}

void CMqttFileOptrTool::SetRetResult_Failure()
{
	m_nRetResult = STT_CMD_RET_RESULT_FAILURE;
}

void CMqttFileOptrTool::SetRetResult_Timeout()
{
	m_nRetResult = STT_CMD_RET_RESULT_TIMEOUT;
}

void CMqttFileOptrTool::SetRetResult_Finish()
{
	m_nRetResult = STT_CMD_RET_RESULT_FINISH;
}

BOOL CMqttFileOptrTool::IsRetResult_NULL()
{
	return m_nRetResult==STT_CMD_RET_RESULT_NULL;
}

BOOL CMqttFileOptrTool::IsRetResult_Proccessing()
{
	return m_nRetResult==STT_CMD_RET_RESULT_PROCESSING;
}

BOOL CMqttFileOptrTool::IsRetResult_Finish()
{
	return m_nRetResult==STT_CMD_RET_RESULT_FINISH;
}

BOOL CMqttFileOptrTool::IsRetResult_Failure()
{
	return m_nRetResult==STT_CMD_RET_RESULT_FAILURE;
}

BOOL CMqttFileOptrTool::IsRetResult_Timeout()
{
	return m_nRetResult==STT_CMD_RET_RESULT_TIMEOUT;
}

void CMqttFileOptrTool::CheckMqttFtpMsgRecv(CStringTokenizer &oToken,char *pBuf,long nLen)
{
	if (IsUploadCmdTopic(oToken))
	{
		Process_UploadFileCmd(oToken,pBuf,nLen);
	}
	else if (IsDownloadCmdTopic(oToken))
	{
		Process_DownloadFileCmd(oToken,pBuf,nLen);
	}
}

/*********************************
DstID/SrcID/UploadCmd/UploadFileName/Reply
DstID/SrcID/UploadCmd/UploadFileData/Reply
*********************************/
long CMqttFileOptrTool::Process_UploadFileCmd(CStringTokenizer &oToken,char *pBuf,long nLen)
{
	if (m_pCurMqttFileOptr == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Process_UploadFileCmd:m_pCurMqttFileOptr == NULL"));
		return 2;
	}

	CString strDstID,strSrcID,strCmd,strTopic;
	strDstID = oToken.GetToken(0);
	strSrcID = oToken.GetToken(1);
	strCmd = oToken.GetToken(3);

	if (strDstID != m_strDstID || strSrcID != m_strSrcID)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Process_UploadFileCmd:SrcID,DstID不匹配"));
		return 3;
	}

	if (strCmd == MQTT_FTP_CMD_UploadFileName)
	{
		strTopic.Format(_T("%s/%s/UploadCmd/UploadFileName/Reply"),strDstID,strSrcID);
		if (m_pCurMqttFileOptr->m_strCurExceptTopic != strTopic)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("UploadCmd/UploadFileName/Reply:与期待主题不一致[%s]。"),m_pCurMqttFileOptr->m_strCurExceptTopic);
			return 1;
		}

		m_pCurMqttFileOptr->Process_UploadCmd_UploadFileNameReply(pBuf,nLen);
	}
	else if (strCmd == MQTT_FTP_CMD_UploadFileData)
	{
		strTopic.Format(_T("%s/%s/UploadCmd/UploadFileData/Reply"),strDstID,strSrcID);

		if (m_pCurMqttFileOptr->m_strCurExceptTopic != strTopic)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("UploadCmd/UploadFileData/Reply:与期待主题不一致[%s]。"),m_pCurMqttFileOptr->m_strCurExceptTopic);
			return 1;
		}

		m_pCurMqttFileOptr->Process_UploadCmd_UploadFileDataReply(pBuf,nLen);
	}
	return 0;
}

/***********************************
DstID/SrcID/DownloadCmd/DownloadFileName/Reply
SrcID/DstID/DownloadCmd/UploadFileName	
SrcID/DstID/DownloadCmd/UploadFileData	
************************************/
long CMqttFileOptrTool::Process_DownloadFileCmd(CStringTokenizer &oToken,char *pBuf,long nLen)
{
	if (m_pCurMqttFileOptr == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Process_DownloadFileCmd:m_pCurMqttFileOptr == NULL"));
		return 2;
	}

	CString strDstID,strSrcID,strCmd,strTopic;
	strDstID = oToken.GetToken(0);
	strSrcID = oToken.GetToken(1);
	strCmd = oToken.GetToken(3);

	if (strDstID != m_strDstID || strSrcID != m_strSrcID)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Process_DownloadFileCmd:SrcID,DstID不匹配"));
		return 3;
	}

	if (strCmd == MQTT_FTP_CMD_UploadFileName)
	{
		strTopic.Format(_T("%s/%s/DownloadCmd/UploadFileName"),strDstID,strSrcID);
		if (m_pCurMqttFileOptr->m_strCurExceptTopic != strTopic)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("DownloadCmd/UploadFileName:与期待主题不一致[%s]。"),m_pCurMqttFileOptr->m_strCurExceptTopic);
			return 1;
		}

		m_pCurMqttFileOptr->Process_DownloadCmd_UploadFileName(pBuf,nLen);
	}
	else if (strCmd == MQTT_FTP_CMD_UploadFileData)
	{
		strTopic.Format(_T("%s/%s/DownloadCmd/UploadFileData"),strDstID,strSrcID);
		if (m_pCurMqttFileOptr->m_strCurExceptTopic != strTopic)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("DownloadCmd/UploadFileData:与期待主题不一致[%s]。"),m_pCurMqttFileOptr->m_strCurExceptTopic);
			return 1;
		}

		m_pCurMqttFileOptr->Process_DownloadCmd_UploadFileData(pBuf,nLen);
	}

	return 0;
}