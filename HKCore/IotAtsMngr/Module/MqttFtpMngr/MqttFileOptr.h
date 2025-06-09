#pragma once
#include "../../../Module/System/StringTokenizer.h"
#include "../../../Module/BaseClass/SttFileTransferProgress.h"
#include "../../../Module/BaseClass/XTimer.h"
#include "../../../SttStudio/Module/SttGlobalDef_File.h"

#define MQTT_FTP_CMDTYPE_UploadCmd			_T("UploadCmd")
#define MQTT_FTP_CMDTYPE_DownloadCmd		_T("DownloadCmd")

#define MQTT_FTP_CMD_DownloadFileName		_T("DownloadFileName")
#define MQTT_FTP_CMD_DownloadFileNameReply	_T("DownloadFileNameReply")
#define MQTT_FTP_CMD_UploadFileName			_T("UploadFileName")
#define MQTT_FTP_CMD_UploadFileNameReply	_T("UploadFileNameReply")
#define MQTT_FTP_CMD_UploadFileData			_T("UploadFileData")
#define MQTT_FTP_CMD_UploadFileDataReply	_T("UploadFileDataReply")

class CMqttCmdOverTimeMsgRcv
{
public:
	virtual void OnSendCmdFailFinish(const char *pszSrcID, const char *pszCmdType, UINT nErrCode){};
	virtual void OnSendCmdFinish(const char *pszSrcID, const char *pszCmdType){};
	virtual void OnSendCmdOverTime(const char *pszSrcID, const char *pszTopic) = 0;
};

extern long g_nFileCmdTimeOut;
extern CString g_strFtpRootFile;
CString Mqtt_GetAbsolutePathFile(const CString &strFile);

class CMqttFileOptr : public CExBaseObject,public CXTimer
{
public:
	CMqttFileOptr();
	virtual ~CMqttFileOptr();

public:
	virtual void OnXTimer(DWORD dwTimerID);

public:
	//m_strID:SrcID
	CString m_strDstID;
	CFile m_oFile;
	unsigned long m_nFileTotalSize;
	unsigned long m_nFileSendSize;
	SYSTEMTIME m_tmFileModify;
	CString m_strCurExceptTopic;//当前期望主题
	CString m_strCurSendTopic;	//当前准备发送主题
	CString m_strLocalFile;
	CString m_strRemoteFile;
	CSttSocketFileTransferProgress *m_pFtpProgress;
	CMqttCmdOverTimeMsgRcv *m_pMqttCmdOverTimeMsgRcv;
	BOOL m_bValid;//是否有效，解决超时不能删除，只能设置标记

	virtual BOOL SendFileCmd(BYTE *pBuf, UINT nFileCmd, UINT nMode, long nLen);
	virtual BOOL SendRetFileCmd(UINT nFileCmd, UINT nMode);
	void SetID(const CString &strSrcID,const CString &strDstID);

private:
	BYTE m_chSendFileCmdBuf[STT_FILECMD_MAX_LEN];//文件命令发送缓存:4K+帧头长

public:
	void CloseFile();
	void AttachFileTransferProgress(CSttSocketFileTransferProgress *pFtpProgress)		{	m_pFtpProgress = pFtpProgress;	}
	void DetachFileTransferProgress()		{	m_pFtpProgress = NULL;	}
	void AttachCmdOverTimeMsgRcv(CMqttCmdOverTimeMsgRcv *pMqttCmdOverTimeMsgRcv){ m_pMqttCmdOverTimeMsgRcv = pMqttCmdOverTimeMsgRcv;}

	int RenameRecvFile(const CString &strBkFileName);

	void SendFile(const CString &strLocalFile, const CString &strReoteFile, BOOL bServer=FALSE);
	void DownloadFile(const CString &strLocalFile, const CString &strReoteFile);

	virtual BOOL Process_UploadFileNameReply(char *pBuf,long nLen,const CString &strCmdType);
	virtual BOOL Process_UploadFileDataReply(char *pBuf,long nLen,const CString &strCmdType);

	//服务端逻辑
	virtual BOOL Process_UploadCmd_UploadFileName(const CString &strSrcID
									,const CString &strDstID,char *pBuf,long nLen);
	virtual BOOL Process_UploadCmd_UploadFileData(char *pBuf,long nLen);
	virtual BOOL Process_DownloadCmd_DownloadFileName(const CString &strSrcID
		,const CString &strDstID,char *pBuf,long nLen);
	virtual BOOL Process_DownloadCmd_UploadFileNameReply(char *pBuf,long nLen);
	virtual BOOL Process_DownloadCmd_UploadFileDataReply(char *pBuf,long nLen);

	//客户端逻辑
	virtual BOOL Process_UploadCmd_UploadFileNameReply(char *pBuf,long nLen);
	virtual BOOL Process_UploadCmd_UploadFileDataReply(char *pBuf,long nLen);
	virtual BOOL Process_DownloadCmd_UploadFileName(char *pBuf,long nLen);
	virtual BOOL Process_DownloadCmd_UploadFileData(char *pBuf,long nLen);
};

BOOL IsUploadCmdTopic(CStringTokenizer &oTopicToken);
BOOL IsDownloadCmdTopic(CStringTokenizer &oTopicToken);