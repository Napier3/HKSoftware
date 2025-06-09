#pragma once

#include "MqttFileOptr.h"
#include "../../../Module/ui/XFtpProgressDynDlg.h"

////////////文件上传下载机制/////////////////
#define STT_CMD_RET_RESULT_NULL 			0
#define STT_CMD_RET_RESULT_PROCESSING	 	1
#define STT_CMD_RET_RESULT_FINISH			2
#define STT_CMD_RET_RESULT_FAILURE 			3
#define STT_CMD_RET_RESULT_TIMEOUT 			4

//文件上传下载命令对象类
class CSttXftpFile : public CExBaseObject
{
public:
	CString m_strLocalFile;
	CString m_strRemoteFile;
};

class CMqttFileOptrTool:public CExBaseList, public CSttSocketFileTransferProgress,public CMqttCmdOverTimeMsgRcv
{
public:
	CMqttFileOptrTool();
	virtual ~CMqttFileOptrTool();
	void Free();

public:
	virtual void TransferStart(const CString &strFile, long nTotalSize);
	virtual void TransferStep(long nCurrSendSize);
	virtual void TransferFinish(const CString &strFile);
	virtual void TransferError(const CString &strFile,long nErrNo);
	virtual void Init(CStringArray &strArray);

	virtual void OnSendCmdFailFinish(const char *pszSrcID, const char *pszCmdType,UINT nErrCode);
	virtual void OnSendCmdFinish(const char *pszSrcID, const char *pszCmdType);
	virtual void OnSendCmdOverTime(const char *pszSrcID, const char *pszTopic);

public:
	CXFtpProgressDynDlg m_oSttXFtpProgressDlg;
	CSttSocketFileTransferProgress *m_pProgress;
	CMqttFileOptr *m_pCurMqttFileOptr;
	long m_nRetResult;
	BOOL m_bSendFile;
	long m_nCurrSendIndex;
	
	CString m_strDstID;
	CString m_strSrcID;

	void SetID(const CString &strSrcID,const CString &strDstID);
	void AttachSttSocketFileTransferProgress(CSttSocketFileTransferProgress *pProgress){m_pProgress=pProgress;}
	void InitProgressDlg();
	void SubcribeFtpToic();

	void InitBefore();
	void AddFile(const CString &strLocalFile, const CString &strRemoteFile); //添加到文件列表
	BOOL SendFiles();
	BOOL DownloadFiles();
	virtual BOOL SendCurrFile();
	virtual BOOL DownloadCurrFile();

	void SetRetResult_NULL();
	void SetRetResult_Proccessing();
	void SetRetResult_Failure();
	void SetRetResult_Timeout();
	void SetRetResult_Finish();
	BOOL IsRetResult_NULL();
	BOOL IsRetResult_Proccessing();
	BOOL IsRetResult_Finish();
	BOOL IsRetResult_Failure();
	BOOL IsRetResult_Timeout();

public:
	void CheckMqttFtpMsgRecv(CStringTokenizer &oToken,char *pBuf,long nLen);
	long Process_UploadFileCmd(CStringTokenizer &oToken,char *pBuf,long nLen);
	long Process_DownloadFileCmd(CStringTokenizer &oToken,char *pBuf,long nLen);
};

extern CMqttFileOptrTool g_oMqttFileOptrTool;