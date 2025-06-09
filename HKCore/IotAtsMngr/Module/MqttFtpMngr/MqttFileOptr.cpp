#include "stdafx.h"
#include "MqttFileOptr.h"
#include "../SttMqttClientTool.h"
#include "../SttMqttClientEngineConfig.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CMqttFileOptr::CMqttFileOptr()
{
	m_nFileTotalSize = 0;
	m_nFileSendSize = 0;
	m_pFtpProgress = NULL;
	m_pMqttCmdOverTimeMsgRcv = NULL;
	GetLocalTime(&m_tmFileModify);

	m_bValid = TRUE;
}

CMqttFileOptr::~CMqttFileOptr()
{
	KillXTimer(1);
	CloseFile();
}

void CMqttFileOptr::SetID(const CString &strSrcID,const CString &strDstID)
{
	m_strID = strSrcID;
	m_strDstID = strDstID;
}

void CMqttFileOptr::CloseFile()
{
	if (m_oFile.m_hFile != INVALID_HANDLE_VALUE)
	{
		m_oFile.Close();
	}
}

void CMqttFileOptr::OnXTimer(DWORD dwTimerID)
{
	KillXTimer(dwTimerID);

	if (m_pFtpProgress != NULL)
	{
		m_pFtpProgress->TransferError(m_strLocalFile,0);
	}
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferError��%s����ʱ��"), m_strLocalFile);

	m_pMqttCmdOverTimeMsgRcv->OnSendCmdOverTime(m_strID,m_strCurExceptTopic);
}

BOOL CMqttFileOptr::SendFileCmd(BYTE *pBuf, UINT nFileCmd, UINT nMode, long nLen)
{
	stt_InitPktBuffer_Head_File(pBuf, nFileCmd, nMode, nLen, 0, 0, FALSE);

	return CSttMqttClientTool::PublicTopic(m_strCurSendTopic,(char *)pBuf, STT_PKG_HEAD_LEN + nLen);
}

BOOL CMqttFileOptr::SendRetFileCmd(UINT nFileCmd, UINT nMode)
{
	return SendFileCmd(m_chSendFileCmdBuf, nFileCmd, nMode, 0);
}

void CMqttFileOptr::SendFile(const CString &strLocalFile, const CString &strReoteFile, BOOL bServer)
{
	KillXTimer(1);

	m_strLocalFile = strLocalFile;
	m_strRemoteFile = strReoteFile;
	long nRet = -1;
	long nMode = 1;
	CString strCmdType;

	if (bServer)
	{
		strCmdType = MQTT_FTP_CMDTYPE_DownloadCmd;
		m_strCurSendTopic.Format(_T("%s/%s/%s/%s"),m_strDstID,m_strID,MQTT_FTP_CMDTYPE_DownloadCmd,MQTT_FTP_CMD_UploadFileName);
		m_strCurExceptTopic.Format(_T("%s/%s/%s/%s/Reply"),m_strDstID,m_strID,MQTT_FTP_CMDTYPE_DownloadCmd,MQTT_FTP_CMD_UploadFileName);
	}
	else
	{
		strCmdType = MQTT_FTP_CMDTYPE_UploadCmd;
		m_strCurSendTopic.Format(_T("%s/%s/%s/%s"),m_strDstID,m_strID,MQTT_FTP_CMDTYPE_UploadCmd,MQTT_FTP_CMD_UploadFileName);
		m_strCurExceptTopic.Format(_T("%s/%s/%s/%s/Reply"),m_strDstID,m_strID,MQTT_FTP_CMDTYPE_UploadCmd,MQTT_FTP_CMD_UploadFileName);
	}

	BOOL bRet = m_oFile.Open(strLocalFile, CFile::modeRead | CFile::shareDenyWrite);

	if (bRet)
	{//
		m_nFileTotalSize = m_oFile.GetLength();
		m_nFileSendSize = 0;

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferStart(strLocalFile, m_nFileTotalSize);
		}
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("Start:%s[%d]"), strLocalFile.GetString(),m_nFileTotalSize);

		memcpy((char*)(m_chSendFileCmdBuf+STT_PKG_INDEX_FILESIZE),&m_nFileTotalSize,STT_PKG_FILEMODE_FILESIZE_LEN);
		stt_pkg_set_cmd_file_time(m_chSendFileCmdBuf,strLocalFile);
		long nLen = CString_to_char(strReoteFile, (char*)(m_chSendFileCmdBuf+STT_PKG_INDEX_FILENAME));
		nLen += STT_PKG_FILEMODE_FILESIZE_LEN + STT_PKG_FILEMODE_FILETIME_LEN;

		SendFileCmd(m_chSendFileCmdBuf, STT_CMD_TYPE_FILE_WRITE, STT_FILEMODE_FILENAME, nLen);
		SetXTimer(1,g_nFileCmdTimeOut);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("[%s]�������ļ�ʧ��"),strLocalFile.GetString());
		//�ļ���Ϊ�գ���ʾ�ļ������ڣ������������ļ������̱���һ��
		if (bServer)
		{//����������ļ���ģʽ�����ش�����Ϣ
			SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, STT_FILEMODE_ERRNO_READFILE_FAILED);
			m_pMqttCmdOverTimeMsgRcv->OnSendCmdFailFinish(m_strID,strCmdType,STT_FILEMODE_ERRNO_READFILE_FAILED);
		}
		else
		{
			if (m_pFtpProgress != NULL)
			{
				m_pFtpProgress->TransferError(strLocalFile,STT_FILEMODE_ERRNO_READFILE_FAILED);
			}
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferError��%s��%d��"), m_strLocalFile.GetString()
				,STT_FILEMODE_ERRNO_READFILE_FAILED);
			m_pMqttCmdOverTimeMsgRcv->OnSendCmdFailFinish(m_strID,strCmdType,STT_FILEMODE_ERRNO_READFILE_FAILED);
		}
	}
}

void CMqttFileOptr::DownloadFile(const CString &strLocalFile, const CString &strReoteFile)
{
	m_strLocalFile = strLocalFile;
	m_strRemoteFile = strReoteFile;

	//���ȷ����ļ����������������ļ������̱���һ��
	long nLen = CString_to_char(strReoteFile, (char*)(m_chSendFileCmdBuf+STT_PKG_INDEX_FILENAME));
	nLen += STT_PKG_FILEMODE_FILESIZE_LEN + STT_PKG_FILEMODE_FILETIME_LEN;

	m_strCurExceptTopic.Format(_T("%s/%s/%s/%s"),m_strDstID,m_strID,MQTT_FTP_CMDTYPE_DownloadCmd,MQTT_FTP_CMD_UploadFileName);
	m_strCurSendTopic.Format(_T("%s/%s/%s/%s"),m_strDstID,m_strID,MQTT_FTP_CMDTYPE_DownloadCmd,MQTT_FTP_CMD_DownloadFileName);
	SendFileCmd(m_chSendFileCmdBuf, STT_CMD_TYPE_FILE_READ, STT_FILEMODE_FILENAME, nLen);
	SetXTimer(1,g_nFileCmdTimeOut);
}

BOOL CMqttFileOptr::Process_UploadCmd_UploadFileName(const CString &strSrcID
								,const CString &strDstID,char *pBuf,long nLen)
{
	KillXTimer(1);

	if (nLen == 0)
	{
		m_pMqttCmdOverTimeMsgRcv->OnSendCmdFailFinish(m_strID,MQTT_FTP_CMDTYPE_UploadCmd,STT_FILEMODE_ERRNO_TRANSMITERROR);
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("�ļ����ƴ���......"));
		return FALSE;
	}

	SetID(strSrcID,strDstID);

	BYTE *pTemp = (BYTE *)pBuf;
	char * pszFileName = NULL;
	stt_pkg_get_cmd_file_name(pTemp, &pszFileName);
	m_nFileTotalSize = stt_pkg_get_cmd_file_size(pTemp);
	m_tmFileModify = stt_pkg_get_cmd_file_time(pTemp);

	m_strCurSendTopic.Format(_T("%s/%s/%s/%s/Reply"),m_strDstID,m_strID,MQTT_FTP_CMDTYPE_UploadCmd,MQTT_FTP_CMD_UploadFileName);
	m_strCurExceptTopic.Format(_T("%s/%s/%s/%s"),m_strDstID,m_strID,MQTT_FTP_CMDTYPE_UploadCmd,MQTT_FTP_CMD_UploadFileData);

	CString strFile = pszFileName;
	CString strLocalFile;
	//��������·�������ȡ����·��
	strLocalFile = Mqtt_GetAbsolutePathFile(strFile);
	strLocalFile = strLocalFile + _T("bk");

	CString strPath = GetPathFromFilePathName(strLocalFile);
	CreateAllDirectories(strPath);
	delete pszFileName;

	m_nFileSendSize = 0;
	m_strLocalFile = strLocalFile;
	m_strRemoteFile.Empty();
	UINT nMode = STT_FILEMODE_FILENAME;

	BOOL bRet = m_oFile.Open(strLocalFile, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("[%s]����д�ļ�ʧ��"),strFile.GetString());

		nMode = STT_FILEMODE_ERRNO_OCCUPIED_OPENFAILED;
		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferError(m_strLocalFile,nMode);
		}
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferError��%s��%d��"), m_strLocalFile.GetString(),nMode);

		SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, nMode);
		m_pMqttCmdOverTimeMsgRcv->OnSendCmdFailFinish(m_strID,MQTT_FTP_CMDTYPE_UploadCmd,nMode);
		return FALSE;
	}
	else
	{
		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferStart(strFile, m_nFileTotalSize);
		}

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Start:%s"), strFile);
	}
	
	SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, nMode);
	SetXTimer(1,g_nFileCmdTimeOut);

	return TRUE;
}

BOOL CMqttFileOptr::Process_UploadCmd_UploadFileData(char *pBuf,long nLen)
{
	KillXTimer(1);

	BYTE *pTemp = (BYTE *)pBuf;
	long nDataLen = stt_pkg_get_data_len_cmd_file(pTemp);
	UINT nCmd = stt_pkg_get_cmd_type(pTemp);
	UINT nMode = stt_pkg_get_cmd_file_mode(pTemp);

	m_strCurSendTopic.Format(_T("%s/%s/%s/%s/Reply"),m_strDstID,m_strID,MQTT_FTP_CMDTYPE_UploadCmd,MQTT_FTP_CMD_UploadFileData);

	CString strLocalFile = m_strLocalFile;

	//��ʾ��������ļ����ݣ�д�ļ�
	if (nDataLen > 0)
	{
		if (m_oFile.m_hFile != INVALID_HANDLE_VALUE)
		{
			m_oFile.Write(pBuf + STT_PKG_INDEX_DATA, nDataLen);
			m_nFileSendSize += nDataLen;

			if (m_pFtpProgress != NULL)
			{
				m_pFtpProgress->TransferStep(m_nFileSendSize);
			}
		}
		else
		{//�ļ��ѹر�
			SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, STT_FILEMODE_ERRNO_READFILE_FAILED);
			m_pMqttCmdOverTimeMsgRcv->OnSendCmdFailFinish(m_strID,MQTT_FTP_CMDTYPE_UploadCmd,STT_FILEMODE_ERRNO_READFILE_FAILED);
			return FALSE;
		}
	}

	if (nMode == STT_FILEMODE_LASTFRAME)//��ʾ���һ֡
	{
		m_oFile.Flush();
		CloseFile();

		//�����ļ�ʱ��
		file_set_time(strLocalFile,m_tmFileModify);

		if (RenameRecvFile(strLocalFile) < 0)
		{//������ʧ��
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("X_Copy fail[%s]"),strLocalFile.GetString());
		}

		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("TransferFinish:%s[%d]"), strLocalFile.GetString(),m_nFileSendSize);

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferFinish(strLocalFile);
		}

		SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, nMode);
		m_pMqttCmdOverTimeMsgRcv->OnSendCmdFinish(m_strID,MQTT_FTP_CMDTYPE_UploadCmd);
		return TRUE;
	}

	SetXTimer(1,g_nFileCmdTimeOut);	
	return SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, nMode);
}

BOOL CMqttFileOptr::Process_DownloadCmd_DownloadFileName(const CString &strSrcID
									 ,const CString &strDstID,char *pBuf,long nLen)
{
	KillXTimer(1);

	SetID(strSrcID,strDstID);

	char *pszFileName = NULL;
	stt_pkg_get_cmd_file_name((BYTE *)pBuf, &pszFileName);
	CString strFile,strLocalFile;
	strFile = pszFileName;
	delete pszFileName;

	//��ȡ����·��
	strLocalFile = Mqtt_GetAbsolutePathFile(strFile);
	SendFile(strLocalFile, strFile,TRUE);
	return TRUE;
}

BOOL CMqttFileOptr::Process_DownloadCmd_UploadFileNameReply(char *pBuf,long nLen)
{
	return Process_UploadFileNameReply(pBuf,nLen,MQTT_FTP_CMDTYPE_DownloadCmd);
}

BOOL CMqttFileOptr::Process_DownloadCmd_UploadFileDataReply(char *pBuf,long nLen)
{
	return Process_UploadFileDataReply(pBuf,nLen,MQTT_FTP_CMDTYPE_DownloadCmd);
}

BOOL CMqttFileOptr::Process_UploadCmd_UploadFileNameReply(char *pBuf,long nLen)
{
	return Process_UploadFileNameReply(pBuf,nLen,MQTT_FTP_CMDTYPE_UploadCmd);
}

BOOL CMqttFileOptr::Process_UploadCmd_UploadFileDataReply(char *pBuf,long nLen)
{
	return Process_UploadFileDataReply(pBuf,nLen,MQTT_FTP_CMDTYPE_UploadCmd);
}

BOOL CMqttFileOptr::Process_DownloadCmd_UploadFileName(char *pBuf,long nLen)
{
	KillXTimer(1);

	BYTE *pTemp = (BYTE *)pBuf;
	UINT nMode = stt_pkg_get_cmd_file_mode(pTemp);
	CString strLocalFile = m_strLocalFile + _T("bk");

	if (stt_is_ret_file_cmd_fail(nMode))
	{//�ļ�������󣬹ر��ļ�
		CloseFile();

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferError(strLocalFile,nMode);
		}
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferError��%s��%d��"), strLocalFile,nMode);

		m_pMqttCmdOverTimeMsgRcv->OnSendCmdFailFinish(m_strID,MQTT_FTP_CMDTYPE_DownloadCmd,nMode);
		return FALSE;
	}

	char * pszFileName = NULL;
	stt_pkg_get_cmd_file_name(pTemp, &pszFileName);
	m_nFileTotalSize = stt_pkg_get_cmd_file_size(pTemp);
	m_tmFileModify = stt_pkg_get_cmd_file_time(pTemp);

	CString strPath = GetPathFromFilePathName(strLocalFile);
	CreateAllDirectories(strPath);
	m_nFileSendSize = 0;
	m_strRemoteFile = pszFileName;
	delete pszFileName;

	m_strCurSendTopic.Format(_T("%s/%s/%s/%s/Reply"),m_strDstID,m_strID,MQTT_FTP_CMDTYPE_DownloadCmd,MQTT_FTP_CMD_UploadFileName);
	m_strCurExceptTopic.Format(_T("%s/%s/%s/%s"),m_strDstID,m_strID,MQTT_FTP_CMDTYPE_DownloadCmd,MQTT_FTP_CMD_UploadFileData);

	BOOL bRet = m_oFile.Open(strLocalFile, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("[%s]����д�ļ�ʧ��"),strLocalFile);

		nMode = STT_FILEMODE_ERRNO_OCCUPIED_OPENFAILED;
		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferError(strLocalFile,nMode);
		}
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferError��%s��%d��"), strLocalFile,nMode);

		SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, nMode);
		m_pMqttCmdOverTimeMsgRcv->OnSendCmdFailFinish(m_strID,MQTT_FTP_CMDTYPE_DownloadCmd,nMode);
		return FALSE;
	}
	else
	{
		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferStart(strLocalFile, m_nFileTotalSize);
		}

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Start:%s"), strLocalFile);
	}

	SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, nMode);
	SetXTimer(1,g_nFileCmdTimeOut);

	return TRUE;
}

BOOL CMqttFileOptr::Process_DownloadCmd_UploadFileData(char *pBuf,long nLen)
{
	KillXTimer(1);

	BYTE *pTemp = (BYTE *)pBuf;
	long nDataLen = stt_pkg_get_data_len_cmd_file(pTemp);
	UINT nCmd = stt_pkg_get_cmd_type(pTemp);
	UINT nMode = stt_pkg_get_cmd_file_mode(pTemp);

	m_strCurSendTopic.Format(_T("%s/%s/%s/%s/Reply"),m_strDstID,m_strID,MQTT_FTP_CMDTYPE_DownloadCmd,MQTT_FTP_CMD_UploadFileData);

	CString strLocalFile = m_strLocalFile + _T("bk");

	//��ʾ��������ļ����ݣ�д�ļ�
	if (nDataLen > 0)
	{
		if (m_oFile.m_hFile != INVALID_HANDLE_VALUE)
		{
			m_oFile.Write(pBuf + STT_PKG_INDEX_DATA, nDataLen);
			m_nFileSendSize += nDataLen;

			if (m_pFtpProgress != NULL)
			{
				m_pFtpProgress->TransferStep(m_nFileSendSize);
			}
		}
		else
		{//�ļ��ѹر�
			SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, STT_FILEMODE_ERRNO_READFILE_FAILED);
			m_pMqttCmdOverTimeMsgRcv->OnSendCmdFailFinish(m_strID,MQTT_FTP_CMDTYPE_DownloadCmd,STT_FILEMODE_ERRNO_READFILE_FAILED);
			return FALSE;
		}
	}

	if (nMode == STT_FILEMODE_LASTFRAME)//��ʾ���һ֡
	{
		m_oFile.Flush();
		CloseFile();

		//�����ļ�ʱ��
		file_set_time(strLocalFile,m_tmFileModify);

		if (RenameRecvFile(strLocalFile) < 0)
		{//������ʧ��
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("X_Copy fail[%s]"),strLocalFile.GetString());
		}

		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("TransferFinish:%s[%d]"), strLocalFile.GetString(),m_nFileSendSize);

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferFinish(strLocalFile);
		}

		SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, nMode);
		m_pMqttCmdOverTimeMsgRcv->OnSendCmdFinish(m_strID,MQTT_FTP_CMDTYPE_DownloadCmd);
		return TRUE;
	}

	SetXTimer(1,g_nFileCmdTimeOut);	
	return SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, nMode);
}

BOOL CMqttFileOptr::Process_UploadFileNameReply(char *pBuf,long nLen,const CString &strCmdType)
{
	KillXTimer(1);

	UINT nMode = stt_pkg_get_cmd_file_mode((BYTE *)pBuf);
	if (strCmdType == MQTT_FTP_CMDTYPE_UploadCmd)
	{
		m_strCurSendTopic.Format(_T("%s/%s/%s/%s"),m_strDstID,m_strID,strCmdType,MQTT_FTP_CMD_UploadFileData);
		m_strCurExceptTopic.Format(_T("%s/%s/%s/%s/Reply"),m_strDstID,m_strID,strCmdType,MQTT_FTP_CMD_UploadFileData);
	}
	else
	{
		m_strCurSendTopic.Format(_T("%s/%s/%s/%s"),m_strDstID,m_strID,strCmdType,MQTT_FTP_CMD_UploadFileData);
		m_strCurExceptTopic.Format(_T("%s/%s/%s/%s/Reply"),m_strDstID,m_strID,strCmdType,MQTT_FTP_CMD_UploadFileData);
	}
	

	//�ļ�����ʧ�ܻ������һ��Ҫ�ȹر��ļ�������ú����ӿڣ���ֹ���߳�ʱ����
	CString strLocalFile = m_strLocalFile;

	if (stt_is_ret_file_cmd_fail(nMode))
	{//�ļ�������󣬹ر��ļ�
		CloseFile();

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferError(strLocalFile,nMode);
		}
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferError��%s��%d��"), strLocalFile.GetString(),nMode);

		m_pMqttCmdOverTimeMsgRcv->OnSendCmdFailFinish(m_strID,strCmdType,nMode);
		return FALSE;
	}

// 	if (nMode == STT_FILEMODE_LASTFRAME)//��ʾ���һ֡
// 	{//��Ϊ�ļ����ն˵Ĵ���
// 		CloseFile();
// 
// 		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("TransferFinish---:%s[%d]"), strLocalFile.GetString(),m_nFileSendSize);
// 
// 		if (m_pFtpProgress != NULL)
// 		{
// 			m_pFtpProgress->TransferFinish(strLocalFile);
// 		}
// 
// 		m_pMqttCmdOverTimeMsgRcv->OnSendCmdFinish(m_strID,strCmdType);
// 		return 0;
// 	}

	long nReadLen = 0;
	if (m_oFile.m_hFile != INVALID_HANDLE_VALUE)
	{
		nReadLen = m_oFile.Read(m_chSendFileCmdBuf+STT_PKG_HEAD_LEN, STT_PKG_SEND_FILEDATA_MAXLEN);
		m_nFileSendSize += nReadLen;

		//���ɱ���ͷ
		if (nReadLen == 0 || m_nFileSendSize >= m_nFileTotalSize)
		{//���һ֡
			nMode = STT_FILEMODE_LASTFRAME;
		}
		else
		{
			//���һ֡û�����ݣ��˴������ǣ��ļ�������4096��������������ǣ����һ֤Ϊ�գ��෢һ֡����
			nMode++ ;

			if (nMode >= STT_FILEMODE_ERRNO_TRANSMITERROR )
			{
				nMode = 0x01;
			}
		}
	}
	else
	{
		nMode = STT_FILEMODE_ERRNO_READFILE_FAILED;
		m_pMqttCmdOverTimeMsgRcv->OnSendCmdFailFinish(m_strID,strCmdType,nMode);
	}

	SetXTimer(1,g_nFileCmdTimeOut);
	long nRet = SendFileCmd(m_chSendFileCmdBuf, STT_CMD_TYPE_FILE_WRITE, nMode, nReadLen);

	if ((m_pFtpProgress != NULL) && (nReadLen > 0))
	{
		m_pFtpProgress->TransferStep(m_nFileSendSize);
	}

	return nRet;
}

BOOL CMqttFileOptr::Process_UploadFileDataReply(char *pBuf,long nLen,const CString &strCmdType)
{
	KillXTimer(1);

	UINT nMode = stt_pkg_get_cmd_file_mode((BYTE *)pBuf);

	//�ļ�����ʧ�ܻ������һ��Ҫ�ȹر��ļ�������ú����ӿڣ���ֹ���߳�ʱ����
	CString strLocalFile = m_strLocalFile;

	if (stt_is_ret_file_cmd_fail(nMode))
	{//�ļ�������󣬹ر��ļ�
		CloseFile();

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferError(strLocalFile,nMode);
		}
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferError��%s��%d��"), strLocalFile.GetString(),nMode);

		m_pMqttCmdOverTimeMsgRcv->OnSendCmdFailFinish(m_strID,strCmdType,nMode);
		return FALSE;
	}

	if (nMode == STT_FILEMODE_LASTFRAME)//��ʾ���һ֡
	{//��Ϊ�ļ����ն˵Ĵ���
		CloseFile();

		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("TransferFinish---:%s[%d]"), strLocalFile.GetString(),m_nFileSendSize);

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferFinish(strLocalFile);
		}

		m_pMqttCmdOverTimeMsgRcv->OnSendCmdFinish(m_strID,strCmdType);
		return 0;
	}

	long nReadLen = 0;
	if (m_oFile.m_hFile != INVALID_HANDLE_VALUE)
	{
		nReadLen = m_oFile.Read(m_chSendFileCmdBuf+STT_PKG_HEAD_LEN, STT_PKG_SEND_FILEDATA_MAXLEN);
		m_nFileSendSize += nReadLen;

		//���ɱ���ͷ
		if (nReadLen == 0 || m_nFileSendSize >= m_nFileTotalSize)
		{//���һ֡
			nMode = STT_FILEMODE_LASTFRAME;
		}
		else
		{
			//���һ֡û�����ݣ��˴������ǣ��ļ�������4096��������������ǣ����һ֤Ϊ�գ��෢һ֡����
			nMode++ ;

			if (nMode >= STT_FILEMODE_ERRNO_TRANSMITERROR )
			{
				nMode = 0x01;
			}
		}
	}
	else
	{
		nMode = STT_FILEMODE_ERRNO_READFILE_FAILED;
		m_pMqttCmdOverTimeMsgRcv->OnSendCmdFailFinish(m_strID,strCmdType,nMode);
	}

	SetXTimer(1,g_nFileCmdTimeOut);
	long nRet = SendFileCmd(m_chSendFileCmdBuf, STT_CMD_TYPE_FILE_WRITE, nMode, nReadLen);

	if ((m_pFtpProgress != NULL) && (nReadLen > 0))
	{
		m_pFtpProgress->TransferStep(m_nFileSendSize);
	}

	return nRet;
}

int CMqttFileOptr::RenameRecvFile(const CString &strBkFileName)
{//������ʱ�����ļ���d:/abk��d:/a.txtbk,Ŀ���ļ���d:/a��d:/a.txt
	//ȥ����ʱ�ļ�������bk,�õ�������Ҫ���ļ���
	CString strNewFile = strBkFileName.Left(strBkFileName.GetLength()-2);

	if (IsFileExist(strNewFile))
	{
		if (!X_DeleteFile(strNewFile))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("X_DeleteFile fail[%s]"),strNewFile.GetString());
		}
	}
	BOOL bRet = X_CopyFile(strBkFileName,strNewFile);
	if(bRet)
	{
		file_set_time(strNewFile,m_tmFileModify);

		//�ײ��轫��ʱ�ļ�����
		X_DeleteFile(strBkFileName);
	}
	return bRet;
}


///////////////////////////////////////

long g_nFileCmdTimeOut = 5000;
CString g_strFtpRootFile = _T("");

CString Mqtt_GetAbsolutePathFile(const CString &strFile)
{
	CString strTemp = strFile;

#ifdef _PSX_QT_LINUX_
	if (strFile.GetAt(0) != '/')
#else
	if (strFile.Find(_T(":")) < 0)
#endif
	{//���·��
		if (g_strFtpRootFile.GetLength() == 0)
		{
			CString strPath;
			CSttMqttClientEngineConfig::GetMqttFtpRoot(strPath);
	//		strPath = _P_GetSystemPath();
			strTemp = strPath + strTemp;
		}
		else
		{
			strTemp = g_strFtpRootFile + strTemp;
		}
	}

	return strTemp;
}

BOOL IsUploadCmdTopic(CStringTokenizer &oTopicToken)
{
	CString strCmdType;

	if (oTopicToken.GetStringsCount() >= 4)
	{
		strCmdType = oTopicToken.GetToken(2);
		return (strCmdType == MQTT_FTP_CMDTYPE_UploadCmd);
	}

	return FALSE;
}

BOOL IsDownloadCmdTopic(CStringTokenizer &oTopicToken)
{
	CString strCmdType;

	if (oTopicToken.GetStringsCount() >= 4)
	{
		strCmdType = oTopicToken.GetToken(2);
		return (strCmdType == MQTT_FTP_CMDTYPE_DownloadCmd);
	}

	return FALSE;
}