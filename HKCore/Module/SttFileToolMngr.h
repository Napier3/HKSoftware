#ifndef _SttFileToolMngr_h_
#define _SttFileToolMngr_h_

#include "SttSocket\SttCmdOverTimeMngr.h"

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

//文件上传下载工具管理类
class CSttFileToolMngr : public CExBaseList
{
private:
	CSttFileToolMngr();
	virtual ~CSttFileToolMngr();

	static CSttFileToolMngr * g_pSttFileToolMngr;
	static long g_nSttFileToolMngrRef;

public:
	static CSttFileToolMngr *Create();
	static void Release();
	static CSttFileToolMngr *GetSttFileToolMngr();

	static BOOL AddSocketRef(CSttSocketDataBase_File *pSocket);
	static void ReleaseSocketRef(CSttSocketDataBase_File *pSocket);

protected:
	BOOL IsSocketExist(CSttSocketDataBase_File *pSocket);
private:
	//互斥锁
	CAutoCriticSection m_oCriticSection;
};

//文件上传下载工具类
class CSttFileTool: public CExBaseList, public CSttSocketFileTransferProgress, public CSttCmdOverTimeMsgRcv
{
public:
	CSttFileTool();
	virtual ~CSttFileTool();
	virtual void Free();

public:
	virtual void TransferStart(const CString &strFile, long nTotalSize);
	virtual void TransferStep(long nCurrSendSize);
	virtual void TransferFinish(const CString &strFile);
	virtual void TransferError(const CString &strFile,long nErrNo);
	virtual void Init(CStringArray &strArray);
	virtual void OnSendCmdFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID);
	virtual void OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID);

public:
	void AttachSttSocketFileTransferProgress(CSttSocketFileTransferProgress *pProgress);
	void AttachSttCmdOverTimeMsgRcv(CSttCmdOverTimeMsgRcv *pCmdOverTimeMsgRcv);

	BOOL ConnectServer(const CString &strIP,long nPort);
	void InitBefore();

	void AddFile(const CString &strLocalFile, const CString &strRemoteFile); //添加到文件列表
	BOOL SendFiles(BOOL bBlock);
	BOOL DownloadFiles(BOOL bBlock);
	BOOL AttachSttSocket(CSttSocketDataBase_File *pSocket);
	void DettachSttSocket();
	void SetDestID(long nDestID){	m_nDestID = nDestID;	}

protected:
	virtual BOOL SendFiles_Block();
	virtual BOOL SendFiles_NonBlock();
	virtual BOOL SendCurrFile();
	virtual BOOL SendNextFile();

	virtual BOOL DownloadFiles_Block();
	virtual BOOL DownloadFiles_NonBlock();
	virtual BOOL DownloadCurrFile();
	virtual BOOL DownloadNextFile();

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
	CSttSocketDataBase_File *m_pSocket;
	long m_nRetResult;//
	BOOL m_bSendFile;
	long m_nDestID;

	long m_nCurrSendIndex;
	BOOL m_bIsBlock;
	BOOL m_bIsSocketRef;
	CSttSocketFileTransferProgress *m_pProgress;
	CSttCmdOverTimeMsgRcv *m_pCmdOverTimeMsgRcv;
};


#endif