#include "stdafx.h"

#include "AtsRpcClientSvr.h"

using namespace XmlRpc;
using namespace std;

CAtsRpcClientXmlRpcServer::CAtsRpcClientXmlRpcServer()
{
    //call register methods
    RegisterMethods();

    //set port bind and listen
    int port = AtsRpcClientXmlRpcServer_Port;
    bool ret = false;
	char pszIP[32];
	pszIP[0] = 0;
	CString_to_char(CAtsRpcServerConfig::GetLocalIP(), pszIP);
	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("AtsRpcClientXmlRpcServer:%s + %d"), pszIP, port);
    ret = m_oXmlRpcServer.bindAndListen(pszIP, port);

    m_pLog  = new CAtsRpcClientLogHandle;
    XmlRpcLogHandler::setLogHandler(m_pLog);
}

CAtsRpcClientXmlRpcServer::~CAtsRpcClientXmlRpcServer()
{
	delete m_pLog;
	m_pLog = NULL;

	long nCount = m_listServerMethods.size();
	long nIndex = 0;
	XmlRpcServerMethod *p = NULL;
	std::list< XmlRpcServerMethod* >::iterator it ;

	for(it=m_listServerMethods.begin();it!=m_listServerMethods.end();it++)
	{
		p = *it;
		delete p;
	}
}

void CAtsRpcClientXmlRpcServer::RegisterMethods()
{
	m_listServerMethods.push_back(new CAtsRpcClient_OnItemStateChanged(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpcClient_OnTestFinished(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpcClient_OnTestAppError(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpcClient_OnEngineError(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpcClient_SmartTestCreated(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpcClient_OnExportRptFinished(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpcClient_OnConnectDeviceFailed(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpcClient_OnOpenGbrptFailed(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpcClient_GbrptOpened(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpcClient_OnTestStoped(&m_oXmlRpcServer));
}

void CAtsRpcClientXmlRpcServer::run()
{
        XmlRpcUtil::log(1,"start run");
        m_oXmlRpcServer.work(-1.0);

		int i = 0;
}

void CAtsRpcClientXmlRpcServer::exit()
{
	m_oXmlRpcServer.shutdown();
	m_oXmlRpcServer.close();
	m_oXmlRpcServer.exit();
}

