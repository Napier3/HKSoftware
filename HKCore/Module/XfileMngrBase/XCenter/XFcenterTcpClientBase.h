#pragma once
#include "../../DataMngr/DvmDataset.h"

#include "XFcenterDef.h"


class CXFcenterTcpClientBase : public CSocket
{
public:
	CXFcenterTcpClientBase(void);
	virtual ~CXFcenterTcpClientBase(void);

	BYTE m_byteReceiveBuffer[XFCENTER_RECV_BUF_LEN+100];
	BYTE m_byteSendBuffer[XFCENTER_RECV_BUF_LEN+100];

	virtual void OnReceive(int nErrorCode);
	
	virtual BOOL SendXFcenterCmd(CDvmData *pData);
	virtual BOOL SendXFcenterCmd(const CString &strCmd);
	virtual BOOL IsSendCmdFinished();
	virtual long GetSendCmdResult();

	virtual void SetMsgRcvWnd(CWnd *pMsgRcvWnd);

protected:
	virtual BOOL ProcessXFcenterCmd(CDvmData *pData);
	virtual void InitThreadParam(CDvmData *pData, XFCENTER_THREAD_PARAM *pParam);

	CDvmData m_oSendCmd;
	CWnd *m_pMsgRcvWnd;
	//XFCENTER_THREAD_PARAM m_oParam;

public:
	//用户登录
	virtual BOOL Login(const CString &strFcenterID, const CString &strPsw);
	virtual BOOL Logoff(const CString &strFcenterID);

	//软件授权
	virtual BOOL hasp_has_catalog(UINT nFetureID);
	virtual BOOL hasp_get_infor();
};


UINT xfcenter_send_files(XFCENTER_THREAD_PARAM *pParam, SOCKET &sktSend);
UINT xfcenter_recv_files(XFCENTER_THREAD_PARAM *pParam, SOCKET &sktRecv);
UINT xfcenter_send_query_files(XFCENTER_THREAD_PARAM *pParam, SOCKET &sktSend);
UINT xfcenter_recv_query_files(XFCENTER_THREAD_PARAM *pParam, SOCKET &sktRecv);
// CXFileMngr* xfcenter_find_filemngr(CExBaseList *pList, const CString &strBucket);

BOOL xfcenter_set_send_timeout(SOCKET hSocket, int nSecond);
BOOL xfcenter_set_recv_timeout(SOCKET hSocket, int nSecond);
BOOL xfcenter_set_connect_timeout(SOCKET hSocket, int nSecond);
BOOL xfcenter_set_accept_timeout(SOCKET hSocket, int nSecond);

//2022-2-15  lijunqing
UINT xfcenter_client_thread_use_own(LPVOID pParam);
UINT xfcenter_client_thread(LPVOID pParam);

UINT xfcenter_server_thread_use_own(LPVOID pParam);
UINT xfcenter_server_thread(LPVOID pParam);
