// FTPclient.h: interface for the CFTPclient class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxsock.h>		// MFC socket extensions

#define IDS_FTPMSG3             (_T("不能连接服务器"))
#define IDS_FTPMSG4             (_T("不能打开本地文件"))
#define IDS_FTPMSG5             (_T("文件错误"))
#define IDS_FTPMSG6             (_T("网络错误"))
#define IDS_FTPMSG1             (_T("登录失败"))
#define IDS_FTPMSG2             (_T("不能创建SOCKET"))

#include "XMiniFtpFile.h"
#include "../BaseClass/SttFileTransferProgress.h"

#define  FTP_CLIENT_GET_TIMERID      21
//2分钟查询一次
#define  FTP_CLIENT_GET_TIMER_LONG   2000

extern BOOL g_bXMiniFtpLogInfor;

///#define  FTP_CLIENT_GET_TIMER_LONG   30000

// class CXFtpTransferProgress
// {
// public:
// 	virtual void XFtpTransferFinish(long nResult) = 0;
// 	virtual void XFtpTransferStep() = 0;
// 	virtual void XFtpInit(CStringArray &strArray) = 0;
// };

class CXMiniFtpFileItem : public CExBaseList
{
public:
	CXMiniFtpFileItem();
	virtual ~CXMiniFtpFileItem();

	BOOL IsDirectory()		{	return m_bDirectory;	}
	CString GetDirectory();

	void Compare(CXMiniFtpFileItem *pCurrItem, CExBaseList &oListNewFileItem, const CString &strFileType);
	void GetAllFile(CExBaseList &oListNewFileItem, const CString &strFileType);

	static CString g_strServerRootDir;
protected:
	BOOL IsFileType(const CString &strFileType);

public:
	BOOL ParseLine(const CString &strLine);
	//BOOL ParseLine(const CString &strLine);
	BOOL	m_bDirectory;
	WORD	m_bSec;
	CString m_strSec;
	CString m_strDate;
	int m_index;

	CString m_fileName;// 文件或者文件夹的名称
};


class CXMiniFtpClient : public CXMiniFtpFileMngr
{
public:
	CXMiniFtpClient();
	~CXMiniFtpClient();

	CString m_retmsg;
	CByteArray m_buf;
	CString m_strLine;

	CXMiniFtpFileItem m_oXMiniFtpRoot;


public:
	BOOL MoveFile(const CString &remotefile, const CString &localfile,BOOL pasv,BOOL get);
	void LogOffServer();
	BOOL LogOnToServer(CString hostname,int hostport,const CString &username, const CString &password, const CString &acct
		, const CString &fwhost,const CString &fwusername, const CString &fwpassword,int fwport,int logontype);
	BOOL FTPcommand(const CString &command);
	BOOL ReadStr();
	BOOL WriteStr(const CString &outputstring);
	BOOL List();
	void ProcessList();
	BOOL GetLine(int& ndx);
	BOOL GetLine(int& ndx, CString &strLine);

	void Dir();
	void Dir(CXMiniFtpFileItem *pItem, const CString &subDir);
	//void CD(CXMiniFtpFileItem *pItem);
	void DownFile(CXMiniFtpFileItem *pItem, const CString &strLocalPath);
	void GetAllNewFile(CExBaseList &oListFiles, const CString &strFileType);
	void DownAllNewFile(const CString &strLocalPath, CExBaseList &oListFiles, const CString &strFileType);

private:
	CArchive* m_pCtrlRxarch;
	CArchive* m_pCtrlTxarch;
	CSocketFile* m_pCtrlsokfile;
	CSocket* m_Ctrlsok;
	int m_fc;
	BOOL ReadStr2();
	BOOL OpenControlChannel(const CString &serverhost,int serverport);
	
public:
	void CloseControlChannel();
	BOOL m_isLogOn;

private:
	CSttSocketFileTransferProgress *m_pFtpProgress;

public:
	CString m_strSvrIP;
	CString m_strFtpUser;
	CString m_strFtpPsw;

	BOOL m_bDownload;
	BOOL m_bXFptResult;
	CString m_strLocalFile;
	CString m_strRemoteFile;
	CWinThread* m_pXFtpThread;

	void XFtpInit(CStringArray &strArray);
	void TransferFinish(const CString &strFile);
	void TransferError(const CString &strFile,long nErrNo);
	void AttachSttSocketFileTransferProgress(CSttSocketFileTransferProgress *pProgress){	m_pFtpProgress = pProgress;	}

	void Init(const CString &strSvrIP,const CString &strFtpUser,const CString &strFtpPsw,CWnd *pWnd);

	BOOL InitXMiniFtp(const CString &strSvrIP,const CString &strFtpUser,const CString &strFtpPsw,CWnd *pWnd);
	BOOL InitXMiniFtp();
	void ExitXMiniFtp();

	BOOL UploadFile(const CString &strRemoteFile, const CString &strLocalFile,BOOL bShowProgress=TRUE);
	BOOL DownLoadFile(const CString &strRemoteFile, const CString &strLocalFile,BOOL bShowProgress=TRUE);
	int DownloadSvrFile(HWND hWnd, const CString& strRemoteFile);

	BOOL UploadFileFun();
	BOOL DownLoadFileFun();
	BOOL XFtpProcFun(BOOL bShowProgress);

	static UINT XFtpProc(LPVOID lParam);
	
};
