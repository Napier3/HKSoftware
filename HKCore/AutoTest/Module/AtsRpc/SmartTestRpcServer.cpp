#include "stdafx.h"

#include "SmartTestRpcServer.h"

using namespace XmlRpc;
using namespace std;

CSmartTestRpcXmlRpcServer::CSmartTestRpcXmlRpcServer(const CString &strServer, long nPort)
{
    //call register methods
    RegisterMethods();

    //set port bind and listen
    int port = nPort;
    bool ret = false;
	char pszIP[32];
	pszIP[0] = 0;

	if (strServer.GetLength() > 0)
	{
		CString_to_char(strServer, pszIP);
	}
	else
	{
		CString_to_char(CAtsRpcServerConfig::GetLocalIP(), pszIP);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("SmartTestRpcXmlRpcServer:%s + %d"), pszIP, port);
   
	if (pszIP[0] == 0)
	{
		ret = m_oXmlRpcServer.bindAndListen(NULL, port);
	}
	else
	{
		ret = m_oXmlRpcServer.bindAndListen(NULL, port);
	}

    m_pLog  = new CSmartTestRpcLogHandle;
    XmlRpcLogHandler::setLogHandler(m_pLog);
}

CSmartTestRpcXmlRpcServer::~CSmartTestRpcXmlRpcServer()
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

void CSmartTestRpcXmlRpcServer::RegisterMethods()
{
	m_listServerMethods.push_back(new CAtsRpc_InitSmartTestClient(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_CreateTest(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_BeginTest(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_StopTest(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_TestAllInlegibleItems(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_GetAllTestItems(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_GetTestItemReport(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_TestItem(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_GetDvmDatas(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_GetReportFiles(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_ExecCmd(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_CloseTest(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_ExportRpt(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_ViewItemRpt(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_IsSmartTestExist(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_ExitSmartTest(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_OpenGbrptFile(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_TestBelow(&m_oXmlRpcServer));
	m_listServerMethods.push_back(new CAtsRpc_TestPoint(&m_oXmlRpcServer));
}

void CSmartTestRpcXmlRpcServer::run()
{
        XmlRpcUtil::log(1,"start run");
        m_oXmlRpcServer.work(-1.0);

		int i = 0;
}

void CSmartTestRpcXmlRpcServer::exit()
{
	m_oXmlRpcServer.close();
	m_oXmlRpcServer.exit();
}

