#pragma once

#include "XFcenterTcpClientBase.h"
#include "..\..\..\Module\CriticalSection\SynCriticalSection.h"

#define WM_XFCENTER_FINISH   (WM_USER+2703)

#define  XFCENTER_CLIENT_STATE_NORMAL              0
#define  XFCENTER_CLIENT_STATE_CONNECTTING     1
#define  XFCENTER_CLIENT_STATE_CONNECTSUCC     2
#define  XFCENTER_CLIENT_STATE_CONNECTFAILED   3

#define WM_ConnectServer       (WM_USER + 1100)
#define WM_DisConnectServer   (WM_USER + 1101)
#define WM_DownLoadFile        (WM_USER + 1102)
#define WM_UpLoadFile            (WM_USER + 1103)
#define WM_DeleteFile             (WM_USER + 1104)
#define WM_RenameFile           (WM_USER + 1105)
#define WM_DownLoadFolder     (WM_USER + 1106)
#define WM_UpLoadFolder        (WM_USER + 1107)
#define WM_DeleteFolder          (WM_USER + 1108)
#define WM_RenameFolder       (WM_USER + 1109)
#define WM_Query                  (WM_USER + 1110)
#define WM_ExecCmd              (WM_USER + 1111)
#define WM_ExecCmdFinish       (WM_USER + 1112)


class CXFcenterTcpClient : public CXFcenterTcpClientBase
{
public:
	CXFcenterTcpClient(void);
	virtual ~CXFcenterTcpClient(void);

	CString m_strRemoteIp;
	UINT m_nReotePort;
	CString m_strLocalIp;
	UINT m_nLocalPort;

	BOOL m_bXFcenterFinish;
	CEvent m_eventXFcenter;
	DWORD m_dwTcpConnectState;

public:
	BOOL ConnectServer(const CString &strIP, UINT nPort);
	void DisConnectServer();
	virtual BOOL IsTcpConnectSucc();
	virtual BOOL IsTcpConnectting();

protected:
	virtual BOOL ProcessXFcenterCmd(CDvmData *pData);

	BOOL ProcessXFcenterCmd_Login(CDvmData *pData);
	BOOL ProcessXFcenterCmd_Logout(CDvmData *pData);
	BOOL ProcessXFcenterCmd_GetInfor(CDvmData *pData);
	BOOL ProcessXFcenterCmd_HasFetureID(CDvmData *pData);


public:
	virtual void OnClose(int nErrorCode);

public:
	virtual long DownLoadFiles(const CString &strRootPath,  const CStringArray &astrFiles,CWinThread *pThread, UINT nCmdFinishMsg, CWnd *pMsgRcvWnd=NULL, UINT nMsg=WM_XFCENTER_FINISH);
	virtual long DownLoadFile(const CString &strRootPath,  const CString &strFile,CWinThread *pThread, UINT nCmdFinishMsg, CWnd *pMsgRcvWnd=NULL, UINT nMsg=WM_XFCENTER_FINISH);
	virtual long UpLoadFiles(const CString &strRootPath,  const CStringArray &astrFiles,CWinThread *pThread, UINT nCmdFinishMsg, CWnd *pMsgRcvWnd=NULL, UINT nMsg=WM_XFCENTER_FINISH);
	virtual long UpLoadFile(const CString &strRootPath,  const CString &strFile,CWinThread *pThread, UINT nCmdFinishMsg, CWnd *pMsgRcvWnd=NULL, UINT nMsg=WM_XFCENTER_FINISH);
	virtual long DeleteFile(const CString &strRootPath,  const CString &strFile);
	virtual long RenameFile(const CString &strRootPath,  const CString &strFile, const CString &strDesFile);

	virtual long DownLoadFolder(const CString &strRootPath,  const CString &strFolder,CWinThread *pThread, UINT nCmdFinishMsg, CWnd *pMsgRcvWnd=NULL, UINT nMsg=WM_XFCENTER_FINISH);
	virtual long UpLoadFolder(const CString &strRootPath,  const CString &strFolder,CWinThread *pThread, UINT nCmdFinishMsg, CWnd *pMsgRcvWnd=NULL, UINT nMsg=WM_XFCENTER_FINISH) ;
	virtual long DeleteFolder(const CString &strRootPath,  const CString &strFolder);
	virtual long RenameFolder(const CString &strRootPath,  const CString &strFolder, const CString &strDesFolder);

	virtual long Query(const CString &strRootPath,  const CString &strFolder, const CString &strQueryMode, const CString &strKeys,CWinThread *pThread, UINT nCmdFinishMsg, CWnd *pMsgRcvWnd=NULL, UINT nMsg=WM_XFCENTER_FINISH);

	void WaiteXFcenterFinish();

protected:
	void BeginClientThread(XFCENTER_THREAD_PARAM *pParam);
	virtual void InitThreadParam(CDvmData *pData, XFCENTER_THREAD_PARAM *pParam);
	virtual void InitXFcenterFiles(CDvmData *pData, const CStringArray &astrFiles);
	long ExecXFcenterCmd(XFCENTER_THREAD_PARAM *pParam);
};

//////////////////////////////////////////////////////////////////////////
//
class CXFcenterTcpClientCmd : public CExBaseList
{
public:
	CXFcenterTcpClientCmd()
	{
		m_pMsgRcvWnd = NULL;
		m_nMsgRcv = 0;
		m_nXFcenterMsg = 0;
	};
	virtual ~CXFcenterTcpClientCmd()
	{
	};

public:
	CString m_strRootPath;
	CString m_strPath, m_strPathDest, m_strKeys, m_strQueryMode;
	CWnd *m_pMsgRcvWnd;
	UINT m_nMsgRcv;
	UINT m_nXFcenterMsg;
	CStringArray m_astrFiles;

	void PostWndMsg()
	{
		if (m_pMsgRcvWnd != NULL && m_nMsgRcv > 0)
		{
			if (::IsWindow(m_pMsgRcvWnd->m_hWnd))
			{
				m_pMsgRcvWnd->PostMessage(m_nMsgRcv, (WPARAM)this, m_nXFcenterMsg);
			}
		}
	}
};

class CXFcenterTcpClientThread : public CWinThread
{
	DECLARE_DYNCREATE(CXFcenterTcpClientThread)
protected:
	CXFcenterTcpClientThread();           // protected constructor used by dynamic creation

	// Attributes
private:
	CXFcenterTcpClient *m_pXFcenterTcpClient;
	BOOL m_bThreadHasExit;

// 	CXFileMngr *m_pXFileMngr;
// 	CString m_strPath, m_strPathDest, m_strKeys;
// 	CWnd *m_pMsgRcvWnd;
// 	UINT m_nMsg;

	CXFcenterTcpClientCmd *m_pXFcenterTcpClientCmd;
	CExBaseList m_listXFcenterTcpClientCmd;
	CAutoCriticSection m_oListCmdAutoCriticSection;

	void AddCmd(const CString &strRootPath,  const CStringArray &astrPaths, CWnd *pMsgRcvWnd, UINT nMsg, UINT nXFcenterMsg);
	void AddCmd(const CString &strRootPath,  const CString &strPath, const CString &strPathDest, const CString &strKeys, CWnd *pMsgRcvWnd, UINT nMsg, UINT nXFcenterMsg);
	void AddCmd_Query(const CString &strRootPath,  const CString &strPath, const CString &strQueryMode, const CString &strKeys, CWnd *pMsgRcvWnd, UINT nMsg, UINT nXFcenterMsg);

	void PostXFcenterFinishMsg();
public:
	void XFcenterResetEvent();
	void XFcenterSetEvent();
	BOOL IsTcpConnectSucc();
	BOOL IsTcpConnectting();

	//2022-2-16  lijunqing
	void ConnectServer();

	void ConnectServer(CWnd *pMsgRcvWnd, UINT nMsg=WM_XFCENTER_FINISH)	;
	void DisConnectServer(CWnd *pMsgRcvWnd, UINT nMsg=WM_XFCENTER_FINISH);

	virtual long DownLoadFiles(const CString &strRootPath,  const CStringArray &astrFiles, CWnd *pMsgRcvWnd, UINT nMsg=WM_XFCENTER_FINISH);
	virtual long DownLoadFile(const CString &strRootPath,  const CString &strFile, CWnd *pMsgRcvWnd, UINT nMsg=WM_XFCENTER_FINISH);
	virtual long UpLoadFiles(const CString &strRootPath,  const CStringArray &astrFiles, CWnd *pMsgRcvWnd, UINT nMsg=WM_XFCENTER_FINISH);
	virtual long UpLoadFile(const CString &strRootPath,  const CString &strFile, CWnd *pMsgRcvWnd, UINT nMsg=WM_XFCENTER_FINISH);
	virtual long DeleteFile(const CString &strRootPath,  const CString &strFile, CWnd *pMsgRcvWnd, UINT nMsg=WM_XFCENTER_FINISH);
	virtual long RenameFile(const CString &strRootPath,  const CString &strFile, const CString &strDesFile, CWnd *pMsgRcvWnd, UINT nMsg=WM_XFCENTER_FINISH);

	virtual long DownLoadFolder(const CString &strRootPath,  const CString &strFolder, CWnd *pMsgRcvWnd, UINT nMsg=WM_XFCENTER_FINISH);
	virtual long UpLoadFolder(const CString &strRootPath,  const CString &strFolder, CWnd *pMsgRcvWnd, UINT nMsg=WM_XFCENTER_FINISH) ;
	virtual long DeleteFolder(const CString &strRootPath,  const CString &strFolder, CWnd *pMsgRcvWnd, UINT nMsg=WM_XFCENTER_FINISH);
	virtual long RenameFolder(const CString &strRootPath,  const CString &strFolder, const CString &strDesFolder, CWnd *pMsgRcvWnd, UINT nMsg=WM_XFCENTER_FINISH);

	virtual long Query(const CString &strRootPath,  const CString &strFolder, const CString &strQueryMode, const CString &strKeys, CWnd *pMsgRcvWnd, UINT nMsg=WM_XFCENTER_FINISH);
	void WaiteXFcenterFinish();

	// Operations
public:
	static CXFcenterTcpClientThread* CreateXFcenterTcpClientThread()
	{
		CXFcenterTcpClientThread* pThread = (CXFcenterTcpClientThread*)AfxBeginThread(RUNTIME_CLASS(CXFcenterTcpClientThread));
		pThread->m_bAutoDelete = TRUE;
		pThread->ResumeThread();
		return pThread;
	}

	void ExitTestThread();
	BOOL IsThreadExit()		{		return m_bThreadHasExit;		}

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestWorkThread)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	virtual ~CXFcenterTcpClientThread();

	// Generated message map functions
	//{{AFX_MSG(CTestWorkThread)
	afx_msg void OnConnectServer(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDisConnectServer(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDownLoadFile(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpLoadFile(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDeleteFile(WPARAM wParam, LPARAM lParam);
	afx_msg void OnRenameFile(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDownLoadFolder(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpLoadFolder(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDeleteFolder(WPARAM wParam, LPARAM lParam);
	afx_msg void OnRenameFolder(WPARAM wParam, LPARAM lParam);
	afx_msg void OnQuery(WPARAM wParam, LPARAM lParam);
	afx_msg void OnExecCmd(WPARAM wParam, LPARAM lParam);
	afx_msg void OnExecCmdFinish(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

