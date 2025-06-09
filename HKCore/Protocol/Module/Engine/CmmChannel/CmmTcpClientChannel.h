#pragma once
#include "cmmchannel.h"
#include "../DeviceModel/CmmTcpClientConfig.h"

#include "../../../../Module/Socket/WinTcpSocket.h"

class CCmmTcpClientChannel :	public CCmmChannel, public CWinTcpSocket//,public CWnd//CThreadSocket
{
public:
	CCmmTcpClientChannel(void);
	virtual ~CCmmTcpClientChannel(void);

	CCmmTcpClientConfig *m_pConfig;
	char m_pszPpLogProtocol[10240]; 

public:
	virtual UINT GetClassID(){return CMMCLASSID_TCP_CLIENT_CHANNEL;};

public:
	virtual BOOL Create(CExBaseObject *pConfig);
	virtual void Send(CExBaseObject *pPkgSend);
	virtual BOOL Connect();
	virtual BOOL DisConnect();
	virtual long OnReceive();
	virtual BOOL IsConnectSuccessful();
	virtual BOOL IsCmmChannelExit();
	virtual BOOL TerminateChannel();

	int ReceiveOwnSocket(void* lpBuf, int nBufLen, int nFlags = 0);

	BOOL Is_ExitThread()	{	return m_bExitThread;	}
	void SetThread_NULL()	{	m_pThread = NULL;		}
private:
	//UDP¿Í»§¶Ëº¯Êý
#ifdef _PSX_IDE_QT_
    pthread_t m_pThread;
#else
	CWinThread *m_pThread;
#endif

	BOOL m_bExitThread;


protected:
	//{{AFX_MSG(CThreadSocket)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
    //afx_msg LRESULT OnTCPIP(WPARAM wParam, LPARAM lParam);

// 	DECLARE_MESSAGE_MAP()

};

#ifndef _PSX_IDE_QT_
static UINT Cmm_TcpClientThread(LPVOID pParam);
#else
static void* Cmm_TcpClientThread(LPVOID pParam);
#endif
