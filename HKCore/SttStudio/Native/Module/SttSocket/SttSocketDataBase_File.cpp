#include "stdafx.h"
#include "SttSocketDataBase_File.h"
#include "SttServerSocketDataBase.h"
#include "../../Module/API/FileApi.h"
#include "../../Module/API/GlobalConfigApi.h"
#include "SttCmdOverTimeMngr.h"
#include "../../Module/System/TickCount32.h"
#include "../SttFileToolMngr.h"

#ifndef NOT_USE_XLANGUAGE
#include "../../Module/XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef CHECK_HEARTBEAT_TIMEOUT_MODE
long g_nSendHeartbeatTimeGap = 5000;
//long g_nRecvHeartbeatTimeGap = 30000;//2021-8-20  lijunqing  use timer-count
long g_nRecvHeartbeatTimeGap = 30;//2021-8-20  lijunqing  use timer-count
#else
long g_nSendHeartbeatTimeGap = 0;
long g_nRecvHeartbeatTimeGap = 0;
#endif

long g_nFileCmdTimeOut = 10000;
CString g_strFtpRootFile = _T("");

CSttSocketDataBase_File::CSttSocketDataBase_File()
{
	m_nFileTotalSize = 0;
	m_nFileSendSize = 0;
	m_dwSendBeginTime = 0;
	m_pFtpProgress = NULL;
	m_pCmdOverTimeMsgRcv = NULL;

	m_nSendIndex = 0;
	m_nRecvIndex = 0;

	m_nPortLocal = 0;
	m_nPortRemote = 0;

	m_oExpandRecvBuf.AllocBuffer();

	//2021-8-20  lijunqing  use timer-count
	m_nRecvHeartbeatCounter = 0;
}

CSttSocketDataBase_File::~CSttSocketDataBase_File()
{
	CloseFile();
	ResetAfterTransmit();
}

BOOL CSttSocketDataBase_File::ConnectServer()
{
#ifndef _PSX_QT_LINUX_
	InitSocket();
#endif
	SetReceiveBuffLen( STT_FILECMD_MAX_LEN );
	Create(SOCK_STREAM);
	InitSocketClient(20);

	BOOL bRet = Connect(m_strIPRemote.GetString(), m_nPortRemote);
	#ifdef NOT_USE_XLANGUAGE
	if (bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("���ӷ�����[%s][%d]�ɹ�"), m_strIPRemote.GetString(), m_nPortRemote);
	}
	#else
	if (bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ConServerSucc.GetString(), m_strIPRemote.GetString(), m_nPortRemote);
	}
	#endif
	return bRet;
}

BOOL CSttSocketDataBase_File::ConnectServer(const CString &strIPServer,long nPort)
{//���ػ�Զ�̲��Զˣ����ӳɹ�������SttLocalTestEngine��RefSocket

	char pszIPServer[64] = {0};
	CString_to_char(strIPServer,pszIPServer);

	m_strIPRemote = strIPServer;
	m_nPortRemote = nPort;

	return ConnectServer();
}

void CSttSocketDataBase_File::CloseFile()
{
	//lijq 2020-03-22  Close�����У��Ѿ��Ծ䱾����Ч�������ж�
#ifdef _PSX_IDE_QT_
	if (m_oFile.handle() != (int)INVALID_HANDLE_VALUE)
#else
	if (m_oFile.m_hFile != INVALID_HANDLE_VALUE)
#endif
	{
//		CTickCount32 oTick;
		m_oFile.Close();
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("m_oFile.Close[%d]"),oTick.GetTickCountLong());
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("m_oFile.Close"));
	}
}

void CSttSocketDataBase_File::ResetAfterTransmit()
{
	m_strLocalFile.Empty();
	m_strRemoteFile.Empty();
	m_pFtpProgress = NULL;
	m_pCmdOverTimeMsgRcv = NULL;
}

void CSttSocketDataBase_File::ProcessCmd_End()
{
	CloseFile();
	ResetAfterTransmit();
}

DWORD CSttSocketDataBase_File::GetIDTest()
{
	return 0;
}

void CSttSocketDataBase_File::OnSocketClose(int nErrorCode, BOOL bDeleteSocket)
{
	CSttServerSocketDataBase *pServer = (CSttServerSocketDataBase*)GetParent();

	if (pServer == NULL)
	{
		return;
	}

	pServer->OnSttScktClose(this, bDeleteSocket);
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("nErrorCode=%d[CSttSocketDataBase_File::OnSocketClose]"),nErrorCode);
}

void CSttSocketDataBase_File::CloseSocket()
{
	Close();
}

long CSttSocketDataBase_File::SendBuffer(BYTE *pBuf,long nLen)
{
	long nRet = Send((char*)pBuf, nLen);

	if(nRet <= 0)
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG,_T("+++++++++++SendBuffer failed"));
	}

	//�������ݺ����¼�ʱ
	RestartSendHeartbeatTickCount();

	return nRet;
}

long CSttSocketDataBase_File::SendRetFileCmd(UINT nFileCmd, UINT nMode)
{
	return SendFileCmd(m_chSendFileCmdBuf, nFileCmd, nMode, 0);
}

long CSttSocketDataBase_File::OnReceive(BYTE *pRcvBuf, int iLen)
{
	OnReceiveBuffer(pRcvBuf, iLen);
	return 0;
}

void CSttSocketDataBase_File::OnReceiveBuffer(BYTE *pBuf, long nLen)
{
	if (nLen <= 0)
	{
		return;
	}

	//�յ�����ʱ���¼�ʱ
	RestartRecvHeartbeatTickCount();

	CSttProtocolBufBase::OnReceiveBuffer(pBuf, nLen);
}

long CSttSocketDataBase_File::HasComplatePkg()
{
	BYTE *pTemp = (BYTE *)m_oExpandRecvBuf.GetDataBuffer();
	long nDataLen = m_oExpandRecvBuf.GetDataLength();

	if (nDataLen < STT_PKG_HEAD_LEN)
	{
		return STT_PKG_HEAD_LEN - nDataLen;
	}

	if(!stt_pkg_match_head(pTemp))
	{
		//��ʱ������Ƿ�����
	}

	long nPkgDataLen = stt_pkg_get_data_len(pTemp);
	long nPkgNeedLen = nPkgDataLen + STT_PKG_HEAD_LEN;

	if (nPkgNeedLen > nDataLen)
	{//���µı��ĳ��Ȳ���һ�������ı���
		return nPkgNeedLen - nDataLen;
	}
	else
	{
		return 0;
	}
}

BOOL CSttSocketDataBase_File::ProcessRecvPacket(BYTE *pBuf,long nLen)
{
	long nCmdType = 0, nRetCmdType=0;
	nCmdType = stt_pkg_get_cmd_type(pBuf);

	if (stt_is_cmd_a_file_cmd(nCmdType))
	{
		ProcessCmd_File(pBuf, nLen);
		return TRUE;
	}

	return FALSE;
}

long CSttSocketDataBase_File::SendFileCmd(BYTE *pBuf, UINT nFileCmd, UINT nMode, long nLen)
{
	//	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("-----SendFileCmd:nFileCmd[%x],Mode[%x],SendLen[%d]"),nFileCmd,nMode,nLen);
	
	stt_InitPktBuffer_Head_File(pBuf, nFileCmd, nMode, nLen
								, m_nDestID, 0, FALSE);

	return SendBuffer(pBuf, STT_PKG_HEAD_LEN + nLen);
}

long CSttSocketDataBase_File::ProcessCmd_File(BYTE *pBuf,long nLen)
{
	long nDataLen = stt_pkg_get_data_len_cmd_file(pBuf);
	UINT nCmd = stt_pkg_get_cmd_type(pBuf);
	UINT nMode = stt_pkg_get_cmd_file_mode(pBuf);

	//ÿ�յ��ļ��������Ŀ������ID
	m_nDestID = stt_pkg_get_idtester(pBuf);

	CSttCmdOverTimeTool::OnSocketReceive_FileCmd(this, nCmd, nMode, GetTickCount());

	switch (nCmd)
	{
	case STT_CMD_TYPE_FILE_WRITE:
	case STT_CMD_TYPE_FILE_READ:
		ProcessCmd_File_ReadWrite(pBuf, nLen, nCmd, nMode, nDataLen);
		break;
	}
	
	return 1;
}

long CSttSocketDataBase_File::ProcessCmd_File_ReadWrite(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen)
{
	if (nDataLen > 0)
	{//��ʶ�յ��ļ�����
		//��ʾ��֡��������ļ����������ļ�
		if (nMode == STT_FILEMODE_FILENAME)
		{
			return ProcessCmd_File_FileName(pBuf, nLen, nFileCmd, nMode, nDataLen);
		}
		else
		{
			return ProcessCmd_File_Data(pBuf, nLen, nMode, nDataLen);
		}
	}
	else
	{//����0����ʾ�յ��ļ�����Ӧ��
		return ProcessCmd_File_Ret(pBuf, nLen, nFileCmd, nMode);
	}
}

long CSttSocketDataBase_File::ProcessCmd_File_FileName(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen)
{
	//ReadFile��WriteFile��������SendFile��ʵ���ļ��ķ��ͣ����ߵ�����
	//1�������ļ���Write����
	//                                  ����ˣ�m_strLocalFileΪ���͵ı����ļ���m_strRemoteFileΪ���ն��ļ�
	//                                  ���նˣ�m_strLocalFile��m_strRemoteFile��Ϊ�գ�m_strLocalFileΪ�յ��ļ����Ƶ�����ʱ�����õ�ֵ��m_strRemoteFileΪ��
	//2�������ļ���Read����
	//                                  ����ˣ�m_strLocalFileΪ����Ŀ���ļ�����m_strRemoteFileΪ���ն��ļ���
	//                                  ���նˣ�m_strLocalFileΪ�յ��ļ����ƣ�֮�����SendFile�����ļ�
	//                                                 m_strLocalFileΪ�յ��ļ����ƣ�֮�����SendFile�����ļ���LocalFile��RemoteFile��ͬ
	//                                  ����ˣ�m_strLocalFile��m_strRemoteFile�Ѿ�����ֵ����ʱ�����ļ�
	if (nFileCmd == STT_CMD_TYPE_FILE_WRITE)
	{//1�������ļ���Write����
		if (m_strLocalFile.GetLength() <= 3)
		{//ֱ�ӷ����ļ���
			return ProcessCmd_File_FileName_Write(pBuf, nLen, nMode, nDataLen);
		}
		else
		{//����˵���ReadFile������ˣ����նˣ�����SendFile��������յ����ļ�����
			char *pszFileName = NULL;
			stt_pkg_get_cmd_file_name(pBuf, &pszFileName);

			if ((pszFileName == NULL) || (m_strRemoteFile.CompareNoCase(pszFileName) != 0))
			{
				CString strRemoteFile;
				strRemoteFile = pszFileName;
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DownFile[%s] != SendFile[%s]"), m_strRemoteFile.GetString(), strRemoteFile.GetString());
			}

			delete pszFileName;
			return ProcessCmd_File_FileName_Read(pBuf, nLen, nMode, nDataLen);
		}
	}
	else //if (nFileCmd == STT_CMD_TYPE_FILE_READ)
	{//2�������ļ���Read��
		char *pszFileName = NULL;
		stt_pkg_get_cmd_file_name(pBuf, &pszFileName);
		CString strFile,strLocalFile;
		strFile = pszFileName;
		delete pszFileName;

		//��ȡ����·��
		strLocalFile = Stt_GetAbsolutePathFile(strFile);
		SendFile(strLocalFile, strFile, g_nFileCmdTimeOut,TRUE);
		return 0;
	}
}

long CSttSocketDataBase_File::ProcessCmd_File_FileName_Write(BYTE *pBuf,long nLen, long nMode, long nDataLen)
{
	if (nLen == 0)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("�ļ����ƴ���......"));
		return FALSE;
	}

	// 	long nLenFileName = stt_pkg_get_data_len_cmd_file(pBuf);
	// 	pBuf[nLen] = 0;
	char * pszFileName = NULL;
	stt_pkg_get_cmd_file_name(pBuf, &pszFileName);
	long nFileSize = stt_pkg_get_cmd_file_size(pBuf);
	m_tmFileModify = stt_pkg_get_cmd_file_time(pBuf);

	CString strFile = pszFileName;
	CString strLocalFile;
	//��������·�������ȡ����·��
	strLocalFile = Stt_GetAbsolutePathFile(strFile);
	strLocalFile = strLocalFile + _T("bk");

	CString strPath = GetPathFromFilePathName(strLocalFile);
	CreateAllDirectories(strPath);
	
	UINT nOpenMode = CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive;
#ifdef _PSX_IDE_QT_
	nOpenMode |= CFile::modeTruncate;
#endif
	BOOL bRet = m_oFile.Open(strLocalFile, nOpenMode);

	m_nFileTotalSize = 0;
	m_nFileSendSize = 0;
	m_strLocalFile = strLocalFile;

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("[%s]����д�ļ�ʧ��"),pszFileName);

		nMode = STT_FILEMODE_ERRNO_OCCUPIED_OPENFAILED;

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferError(m_strLocalFile,nMode);
		}
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferError��%s��%d��"), m_strLocalFile.GetString(),nMode);

		m_strLocalFile.Empty();
		m_strRemoteFile.Empty();
	}
	else
	{
		//�����ļ�ʱ��
		// #ifdef _PSX_IDE_QT_
		// 		file_set_time(m_strLocalFile,tmFile);
		// #else
		// 		file_set_time(m_oFile.m_hFile,tmFile);
		// #endif

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferStart(pszFileName, stt_pkg_get_cmd_file_size(pBuf));
		}

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Start:%s"), pszFileName);
	}

	delete pszFileName;

	if(!stt_is_ret_file_cmd_fail(nMode))
	{
		//����ѷ����������
		CSttCmdOverTimeTool::AddSttFileCmd(this, STT_CMD_TYPE_FILE_WRITE, GetTickCount(), g_nFileCmdTimeOut, m_pCmdOverTimeMsgRcv);
	}

	return SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, nMode);
}

long CSttSocketDataBase_File::ProcessCmd_File_FileName_Read(BYTE *pBuf,long nLen, long nMode, long nDataLen)
{
	if (nLen == 0)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("�ļ����ƴ���......"));
		return FALSE;
	}

	//��������ʱ���յ�sendFile����ʱ������bk�ļ�
	m_strLocalFile = m_strLocalFile + _T("bk");
	CString strPath = GetPathFromFilePathName(m_strLocalFile);
	CreateAllDirectories(strPath);

	UINT nOpenMode = CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive;
#ifdef _PSX_IDE_QT_
	nOpenMode |= CFile::modeTruncate;
#endif
	BOOL bRet = m_oFile.Open(m_strLocalFile, nOpenMode);

	m_nFileTotalSize = 0;
	m_nFileSendSize = 0;

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("[%s]����д�ļ�ʧ��"),m_strLocalFile.GetString());

		nMode = STT_FILEMODE_ERRNO_OCCUPIED_OPENFAILED;

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferError(m_strLocalFile.GetString(),nMode);
		}
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferError��%s��%d��"), m_strLocalFile.GetString(),nMode);

		m_strLocalFile.Empty();
		m_strRemoteFile.Empty();

		CSttCmdOverTimeTool::OnSocketFailFinish_FileCmd(this, STT_CMD_TYPE_FILE_WRITE
														, nMode, GetTickCount());
	}
	else
	{
		m_tmFileModify = stt_pkg_get_cmd_file_time(pBuf);

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferStart(m_strLocalFile, stt_pkg_get_cmd_file_size(pBuf));
		}

		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("Start:%s[%d]"), m_strLocalFile.GetString(),stt_pkg_get_cmd_file_size(pBuf));
	}

	return SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, nMode);
}

int CSttSocketDataBase_File::RenameRecvFile(const CString &strBkFileName)
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

#ifdef  _STT_NOT_IN_TEST_SERVER_
		//�ײ��轫��ʱ�ļ�����
		X_DeleteFile(strBkFileName);
#endif
	}
	return bRet;

	//	char chOldFileName[255] = {0};
	//	char chNewFileName[255] = {0};
	//	CString_to_char(strBkFileName,chOldFileName);
	//	CString_to_char(strNewFile,chNewFileName);

	//	if (IsFileExist(strNewFile))
	//	{
	//		if (!X_DeleteFile(strNewFile))
	//		{
	//			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("X_DeleteFile fail[%s]"),strNewFile.GetString());
	//		}
	//	}

	//	return rename(chOldFileName,chNewFileName);
}

long CSttSocketDataBase_File::ProcessCmd_File_Data(BYTE *pBuf, long nLen, long nMode, long nDataLen)
{
	CString strLocalFile = m_strLocalFile;

	//��ʾ��������ļ����ݣ�д�ļ�
	if (nDataLen > 0)
	{//�������һ֡û�����ݣ����ļ�������4096��������
		//��ȷ��д��0�����Ƿ��������ԣ�������
#ifdef _PSX_IDE_QT_
		if (m_oFile.handle() != (int)INVALID_HANDLE_VALUE)
#else
		if (m_oFile.m_hFile != INVALID_HANDLE_VALUE)
#endif
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
			//			DeleteFile(m_strLocalFile);
			nMode = STT_FILEMODE_ERRNO_READFILE_FAILED;

			CSttCmdOverTimeTool::OnSocketFailFinish_FileCmd(this, STT_CMD_TYPE_FILE_WRITE, nMode, GetTickCount());
		}
	}

	if (nMode == STT_FILEMODE_LASTFRAME)//��ʾ���һ֡
	{
		m_oFile.Flush();
		CloseFile();
#ifdef _PSX_QT_LINUX_
        system("sync");
#endif
		//�����ļ�ʱ��
		file_set_time(strLocalFile,m_tmFileModify);

		if (RenameRecvFile(strLocalFile) < 0)
		{//������ʧ��
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("X_Copy fail[%s]"),strLocalFile.GetString());
		}

		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("TransferFinish:%s[%d]"), strLocalFile.GetString(),m_nFileSendSize);
#ifdef _PSX_QT_LINUX_
		system("sync");
#endif
		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferFinish(strLocalFile);
		}

		ResetAfterTransmit();
	}

	return SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, nMode);
}

long CSttSocketDataBase_File::ProcessCmd_File_Ret(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode)
{
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
		
		CSttCmdOverTimeTool::OnSocketFailFinish_FileCmd(this, nFileCmd, nMode, GetTickCount());

		ResetAfterTransmit();
		return -1;
	}

	if (nMode == STT_FILEMODE_LASTFRAME)//��ʾ���һ֡
	{//��Ϊ�ļ����ն˵Ĵ���
		CloseFile();

		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("TransferFinish---:%s[%d]"), strLocalFile.GetString(),m_nFileSendSize);

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferFinish(strLocalFile);
		}

		ResetAfterTransmit();
		return 0;
	}

	long nReadLen = 0;
#ifdef _PSX_IDE_QT_
	if (m_oFile.handle() != (int)INVALID_HANDLE_VALUE)
#else
	if (m_oFile.m_hFile != INVALID_HANDLE_VALUE)
#endif
	{
		nReadLen = m_oFile.Read(m_chSendFileCmdBuf+STT_PKG_HEAD_LEN, STT_PKG_SEND_FILEDATA_MAXLEN);
		m_nFileSendSize += nReadLen;

		//���ɱ���ͷ
		//if (nReadLen < STT_PKG_SEND_FILEDATA_MAXLEN)
		if (nReadLen == 0 || m_nFileSendSize >= m_nFileTotalSize)
		{//���һ֡
			nMode = STT_FILEMODE_LASTFRAME;

			if(nReadLen == 0)
			{//DataLenΪ0�����ն���ΪӦ�����������������
				CloseFile();
				
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("TransferFinish===:%s[%d]"), strLocalFile.GetString(),m_nFileSendSize);

				if (m_pFtpProgress != NULL)
				{
					m_pFtpProgress->TransferFinish(strLocalFile);
				}

				ResetAfterTransmit();
			}
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
		CSttCmdOverTimeTool::OnSocketFailFinish_FileCmd(this, nFileCmd, nMode, GetTickCount());
	}

	long nRet = SendFileCmd(m_chSendFileCmdBuf, nFileCmd, nMode, nReadLen);

	if ((m_pFtpProgress != NULL) && (nReadLen > 0))
	{
		m_pFtpProgress->TransferStep(m_nFileSendSize);
	}

	return nRet;
}

//�ļ�Ϊ���·��
void CSttSocketDataBase_File::SendFile(const CString &strLocalFile, const CString &strReoteFile, long nTimeOut,BOOL bServer)
{
	m_strLocalFile = strLocalFile;
	m_strRemoteFile = strReoteFile;
	long nRet = -1;
	long nMode = 1;

	BOOL bRet = m_oFile.Open(strLocalFile, CFile::modeRead | CFile::shareDenyWrite);

	if (bRet)
	{//
		m_nFileTotalSize = m_oFile.GetLength();
		m_nFileSendSize = 0;
		m_dwSendBeginTime = GetTickCount();

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferStart(strLocalFile, m_nFileTotalSize);
		}
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("Start:%s[%d]"), strLocalFile.GetString(),m_nFileTotalSize);

		//���ȷ����ļ����������������ļ������̱���һ��
		//		long nLen = CString_to_char(strReoteFile, (char*)(m_chSendFileCmdBuf+STT_PKG_HEAD_LEN));

		memcpy((char*)(m_chSendFileCmdBuf+STT_PKG_INDEX_FILESIZE),&m_nFileTotalSize,STT_PKG_FILEMODE_FILESIZE_LEN);

#ifdef _PSX_IDE_QT_
		stt_pkg_set_cmd_file_time(m_chSendFileCmdBuf,strLocalFile.toStdString().c_str());
#else
		stt_pkg_set_cmd_file_time(m_chSendFileCmdBuf,strLocalFile);
#endif

		long nLen = CString_to_char(strReoteFile, (char*)(m_chSendFileCmdBuf+STT_PKG_INDEX_FILENAME));
		nLen += STT_PKG_FILEMODE_FILESIZE_LEN + STT_PKG_FILEMODE_FILETIME_LEN;

		nRet = SendFileCmd(m_chSendFileCmdBuf, STT_CMD_TYPE_FILE_WRITE, STT_FILEMODE_FILENAME, nLen);

		//����ѷ����������
		CSttCmdOverTimeTool::AddSttFileCmd(this, STT_CMD_TYPE_FILE_WRITE, GetTickCount(), nTimeOut, m_pCmdOverTimeMsgRcv);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("[%s]�������ļ�ʧ��"),strLocalFile.GetString());
		//�ļ���Ϊ�գ���ʾ�ļ������ڣ������������ļ������̱���һ��
		if (bServer)
		{//����������ļ���ģʽ�����ش�����Ϣ

			SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, STT_FILEMODE_ERRNO_READFILE_FAILED);
		}
		else
		{
			if (m_pFtpProgress != NULL)
			{
				m_pFtpProgress->TransferError(strLocalFile,STT_FILEMODE_ERRNO_READFILE_FAILED);
			}
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferError��%s��%d��"), m_strLocalFile.GetString()
									   ,STT_FILEMODE_ERRNO_READFILE_FAILED);
		}
	}
}

void CSttSocketDataBase_File::DownloadFile(const CString &strLocalFile, const CString &strReoteFile, long nTimeOut)
{
	m_strLocalFile = strLocalFile;
	m_strRemoteFile = strReoteFile;

	//���ȷ����ļ����������������ļ������̱���һ��
	long nLen = CString_to_char(strReoteFile, (char*)(m_chSendFileCmdBuf+STT_PKG_INDEX_FILENAME));
	nLen += STT_PKG_FILEMODE_FILESIZE_LEN + STT_PKG_FILEMODE_FILETIME_LEN;

	SendFileCmd(m_chSendFileCmdBuf, STT_CMD_TYPE_FILE_READ, STT_FILEMODE_FILENAME, nLen);

	//����ѷ����������
	CSttCmdOverTimeTool::AddSttFileCmd(this, STT_CMD_TYPE_FILE_READ, GetTickCount(), nTimeOut, m_pCmdOverTimeMsgRcv);
}


long CSttSocketDataBase_File::ProcessCmd_File_Rename(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen)
{
	return 0;
}

long CSttSocketDataBase_File::ProcessCmd_File_Delete(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen)
{
	return 0;
}

long CSttSocketDataBase_File::ProcessCmd_File_GetDir(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen)
{
	return 0;
}

long CSttSocketDataBase_File::ProcessCmd_File_Move(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen)
{
	return 0;
}

void CSttSocketDataBase_File::RestartSendHeartbeatTickCount()
{
	m_oSendHeartbeatTick.Enter();
}

void CSttSocketDataBase_File::RestartRecvHeartbeatTickCount()
{
	//m_oRecvHeartbeatTick.Enter();
	//2021-8-20  lijunqing  use timer-count
	m_nRecvHeartbeatCounter = 0;
}

BOOL CSttSocketDataBase_File::SttSendFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
	CSttFileTool oFileTool;
	oFileTool.m_pSocket = this;
	oFileTool.AttachSttSocketFileTransferProgress(pProgress);
	SetDestID(nTestID);
	oFileTool.m_bIsSocketRef = TRUE;
	oFileTool.AddFile(strLocalFile,strRemoteFile);
	return oFileTool.SendFiles(TRUE);
}

BOOL CSttSocketDataBase_File::SttSendFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
	CSttFileTool oFileTool;
	oFileTool.m_pSocket = this;
	oFileTool.AttachSttSocketFileTransferProgress(pProgress);
	SetDestID(nTestID);
	oFileTool.m_bIsSocketRef = TRUE;
	oFileTool.Append(oFilesList);
	oFilesList.RemoveAll();
	return oFileTool.SendFiles(TRUE);
}

BOOL CSttSocketDataBase_File::SttDownloadFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
	CSttFileTool oFileTool;
	oFileTool.m_pSocket = this;
	oFileTool.AttachSttSocketFileTransferProgress(pProgress);
	SetDestID(nTestID);
	oFileTool.m_bIsSocketRef = TRUE;
	oFileTool.AddFile(strLocalFile,strRemoteFile);
	return oFileTool.DownloadFiles(TRUE);
}

BOOL CSttSocketDataBase_File::SttDownloadFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
	CSttFileTool oFileTool;
	oFileTool.m_pSocket = this;
	oFileTool.AttachSttSocketFileTransferProgress(pProgress);
	SetDestID(nTestID);
	oFileTool.m_bIsSocketRef = TRUE;
	oFileTool.Append(oFilesList);
	oFilesList.RemoveAll();
	return oFileTool.DownloadFiles(TRUE);
}

//////////////////////////////////////////
//Ǩ����"SttGlobalDef_File.h"��������
//void stt_InitPktBuffer_Head_File(BYTE *pPkgBuffer,long nTypeCmd, long nMode, long nDataLen, DWORD nIDTester, long nSendIndex, BYTE bCompress)
//{
//	stt_pkg_set_head(pPkgBuffer);
//	stt_pkg_set_cmd_type(pPkgBuffer, (BYTE)nTypeCmd);
//	stt_pkg_set_idtester(pPkgBuffer, nIDTester);
//	stt_pkg_set_send_index(pPkgBuffer, nSendIndex);
//	//	stt_pkg_set_compress(pPkgBuffer, bCompress);

//	stt_pkg_set_data_len_cmd_file(pPkgBuffer, nMode, nDataLen);
//}


void stt_pkg_offset(char* &pPos)
{
	while (*pPos == ' ' || *pPos == '\t')
	{
		pPos++;
	}
}

char* stt_pkg_find_attr(char *pPkgBuf, const char *pszKey, long nKeyLen)
{
	char *pPos = pPkgBuf;
	char *pTemp = NULL;

	while (*pPos != '>')
	{
		if (strncmp(pPos, pszKey,nKeyLen) == 0)
		{
			pTemp = pPos;
			pTemp += nKeyLen;
			stt_pkg_offset(pTemp);

			if (*pTemp == '=')
			{
				if((pPos-pPkgBuf) > 0)
				{
					if(*(pPos-1) == ' '||*(pPos-1) == '<'||*(pPos-1) == '\"')
						return pTemp+1;
				}
				else
					return pTemp+1;

				//return pTemp+1;zhoulei 20211014
			}

			pPos++;
		}
		else
		{
			pPos++;
		}
	}

	return NULL;
}

BOOL stt_cmd_get_key_value(char *pCmdBuf,long nCmdLen, const char *pszKey, char *pszValue)
{
	ASSERT(pCmdBuf[0] == '<');

	char *pPos = pCmdBuf;
	long nKeyLen = strlen(pszKey);

	pPos = stt_pkg_find_attr(pPos, pszKey, nKeyLen);

	if (pPos == NULL)
	{
		return FALSE;
	}

	stt_pkg_offset(pPos);
	ASSERT (*pPos == '\"' || *pPos == '\'');
	char *pBegin = ++pPos;
	char *pEnd = pPos;

	while (*pPos != '>')
	{
		if (*pPos == '\"' || *pPos == '\'')
		{
			pEnd = pPos;
			break;
		}

		pPos++;
	}

	if (pEnd == pBegin)
	{
		*pszValue = 0;
	}
	else
	{
		memcpy(pszValue, pBegin, pEnd - pBegin);
	}
	
	return TRUE;
}

BOOL stt_pkg_get_cmddata(char *pPkgBuf,long nPktLen,char *&pCmdData,long &nCmdLen)
{
	ASSERT(pPkgBuf[STT_PKG_HEAD_LEN] == '<');

	pCmdData = pPkgBuf + STT_PKG_INDEX_DATA;
	if (strncmp(pCmdData,"<?xml",5) != 0)
	{
		nCmdLen = nPktLen - STT_PKG_INDEX_DATA;
		return TRUE;
	}

	//ȥ����<?xml ����\>��
	int nCnt = STT_PKG_INDEX_DATA;
	while(*pCmdData != '>' && nCnt < nPktLen)
	{
		pCmdData++;
		nCnt++;
	}

	if (*pCmdData != '>' || nCnt >= nPktLen)
	{
		return FALSE;
	}

	pCmdData++;
	stt_pkg_offset(pCmdData);

	if (*pCmdData != '<')
	{
		return FALSE;
	}

	nCmdLen = nPktLen - (pCmdData - pPkgBuf);
	return TRUE;
}

CString Stt_GetAbsolutePathFile(const CString &strFile)
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
			strPath = _P_GetSystemPath();
			strTemp = strPath + strTemp;
		}
		else
		{
			strTemp = g_strFtpRootFile + strTemp;
		}
	}

	return strTemp;
}


void stt_LogPkgHeadError(BYTE *pBuf, long nLen)
{
	CLogPrint::LogString(XLOGLEVEL_ERROR,_T("������������ͷ����!!!!!"));
	long i = 0;
	CString strMsg;

	long nBeginPos = STT_PKG_HEAD_LEN * 2;
	char *pHexPkg = new char[nLen + STT_PKG_HEAD_LEN * 2 + 2];

	for (i=0; i<STT_PKG_HEAD_LEN; i++)
	{
		ValueToHex(pBuf[i], pHexPkg[i*2], pHexPkg[i*2+1]);
	}

	memcpy(pHexPkg + STT_PKG_HEAD_LEN * 2, pBuf+STT_PKG_HEAD_LEN, nLen - STT_PKG_HEAD_LEN);

	pHexPkg[nLen + STT_PKG_HEAD_LEN ] = 0;
	pHexPkg[nLen + STT_PKG_HEAD_LEN +1] = 0;
	strMsg = pHexPkg;
	CLogPrint::LogString(XLOGLEVEL_ERROR, strMsg);

	delete pHexPkg;
}