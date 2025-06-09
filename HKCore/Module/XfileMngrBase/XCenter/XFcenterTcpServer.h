#pragma once

#include "XFcenterTcpClientBase.h"
#include "..\XFileMngr.h"
//#include "ServerFcenterListCtrl.h"

class CXFcenterTcpServer;

class CXFcenterTcpServerClientObject : public CExBaseObject
{
public:
	CXFcenterTcpServerClientObject()
	{
		m_nReotePort = 0;
		m_nLocalPort = 0;
	};
	virtual ~CXFcenterTcpServerClientObject(){};

	CString m_strRemoteIp;
	UINT m_nReotePort;
	CString m_strLocalIp;
	UINT m_nLocalPort;
};

class CXFcenterTcpServerClient : public CXFcenterTcpClientBase
{
public:
	CXFcenterTcpServerClient(void);
	virtual ~CXFcenterTcpServerClient(void);
	
	CXFcenterTcpServer *m_pServerRef;
	CXFcenterTcpServerClientObject *m_pObjectRef;
	CExBaseList *m_pListXFileMngr;

public:
	virtual void OnClose(int nErrorCode);
	virtual void InitObjectRef();

protected:
	virtual BOOL ProcessXFcenterCmd(CDvmData *pData);
	virtual void InitThreadParam(CDvmData *pData, XFCENTER_THREAD_PARAM *pParam);

	virtual BOOL ProcessXFcenterCmd_DownLoadFile(CDvmData *pData);
	virtual BOOL ProcessXFcenterCmd_UpLoadFile(CDvmData *pData);
	virtual BOOL ProcessXFcenterCmd_DeleteFile(CDvmData *pData);
	virtual BOOL ProcessXFcenterCmd_RenameFile(CDvmData *pData);

	virtual BOOL ProcessXFcenterCmd_DownLoadFolder(CDvmData *pData);
	virtual BOOL ProcessXFcenterCmd_UpLoadFolder(CDvmData *pData); 
	virtual BOOL ProcessXFcenterCmd_DeleteFolder(CDvmData *pData);
	virtual BOOL ProcessXFcenterCmd_RenameFolder(CDvmData *pData);

	virtual BOOL ProcessXFcenterCmd_Query(CDvmData *pData);

	void BeginServerThread(XFCENTER_THREAD_PARAM *pParam);
};

typedef CTLinkListEx<CXFcenterTcpServerClient>  CXFcenterTcpServerClientList;

class CXFcenterTcpServer : public CSocket
{
public:
	CXFcenterTcpServer(void);
	virtual ~CXFcenterTcpServer(void);

	CXFcenterTcpServerClientList m_listTcpClient;
	CExBaseList m_listClientObject;
// 	CServerFcenterListCtrl *m_pListCtrlRef;

public:
	virtual BOOL CreateServer(const CString &strIP, UINT nPort);
	virtual BOOL CloseServer();
	virtual BOOL IsServerClosed();

	virtual void OnAccept(int nErrorCode);
	void CloseTcpClient(CXFcenterTcpServerClient *pSockt);
	void UpdateTcpClient(CXFcenterTcpServerClient *pSockt);

public:
	CExBaseList m_listXFileMngr;

	void AddXFileMngr(CXFileMngr *pXFileMngr);

};
