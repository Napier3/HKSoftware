#ifndef _XmlRpcServerThreadBase_H_
#define _XmlRpcServerThreadBase_H_

#include "XmlRpc.h"

#include "XmlRpcServerMethod.h"

class CXmlRpcServerThreadBase 
{
public:
    CXmlRpcServerThreadBase();
	virtual ~CXmlRpcServerThreadBase();

	//创建服务端，注册方法，启动线程
	void InitXmlRpcServerThread(const CString &strServerIP, UINT nServerPort);
	virtual void RegisterMethods()=0;
//	virtual void setLogHandler(XmlRpc::XmlRpcLogHandler* pLog);

    void run();
	void exit();

public:
    XmlRpc::XmlRpcServer m_oXmlRpcServer;

	//xxy20190521
	void SetMsgWnd(CWnd *pWnd)	{m_oXmlRpcServer.SetMsgWnd(pWnd);}
	void CloseServerClient(int nSocket){	m_oXmlRpcServer.CloseServerClient(nSocket);	}

protected:
	static UINT XmlRpcServerThread(LPVOID pPara);
	CWinThread *m_pXmlRpcServerThread;

};



#endif // _XmlRpcServerThreadBase_H_