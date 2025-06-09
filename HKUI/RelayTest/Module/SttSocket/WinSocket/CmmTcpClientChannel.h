#pragma once
#include "cmmchannel.h"
#include "..\DeviceModel\CmmTcpClientConfig.h"
#include "..\..\..\..\Module\Socket\ThreadSocket.h"
#include "..\..\..\..\Module\Socket\WinTcpSocket.h"

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

private:
	//UDP客户端函数
	static UINT TcpClientThread(LPVOID pParam);
	CWinThread *m_pThread;
	BOOL m_bExitThread;


protected:
	//{{AFX_MSG(CThreadSocket)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg LRESULT OnTCPIP(WPARAM wParam, LPARAM lParam);

// 	DECLARE_MESSAGE_MAP()

};
