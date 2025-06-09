#include "stdafx.h"

#include "myxmlrpcserver.h"
using namespace XmlRpc;
using namespace std;

myXmlRpcServer::myXmlRpcServer()
{
    //call register methods
    pm_registerMethods();

    //set port bind and listen
    int port = 8085;
//	char psz_ip[32];
//	strcpy(psz_ip, "192.168.0.112");
    bool ret = false;
    ret = pm_xmlRpcServer.bindAndListen(NULL, port);
    //"bind result is:"<<ret;

    m_pLog  = new MyLogHandle;
 	m_pLog->setVerbosity(1);
    XmlRpcLogHandler::setLogHandler(m_pLog);
   // XmlRpcLogHandler::setVerbosity(2);

}

myXmlRpcServer::~myXmlRpcServer()
{
	delete m_pLog;
	m_pLog = NULL;

	long nCount = pm_serverMethods.size();
	long nIndex = 0;
	myXmlRpcServerMethod *p = NULL;
	std::list< myXmlRpcServerMethod* >::iterator it ;

	for(it=pm_serverMethods.begin();it!=pm_serverMethods.end();it++)
	{
		p = *it;
		delete p;
	}
}

void myXmlRpcServer::pm_registerMethods()
{
        Start* a=new Start(&pm_xmlRpcServer);
        myXmlRpcServerMethod *p=a;
        pm_serverMethods.push_back(p);
        pm_serverMethods.push_back(new TestItem(&pm_xmlRpcServer));
//         pm_serverMethods.push_back(new SetSetting(&pm_xmlRpcServer));
//         pm_serverMethods.push_back(new LockerDispel(&pm_xmlRpcServer));
        pm_serverMethods.push_back(new TestParaSet(&pm_xmlRpcServer));
//         pm_serverMethods.push_back(new Read(&pm_xmlRpcServer));
//         pm_serverMethods.push_back(new Write(&pm_xmlRpcServer));
//         pm_serverMethods.push_back((new DeviceInnerParaSet(&pm_xmlRpcServer)));
//         pm_serverMethods.push_back((new TestParaOutput(&pm_xmlRpcServer)));
//         pm_serverMethods.push_back((new PSUDifferTest(&pm_xmlRpcServer)));
//         pm_serverMethods.push_back((new PSUDistanceTest(&pm_xmlRpcServer)));
//         pm_serverMethods.push_back((new PSUSearchZBorderTest(&pm_xmlRpcServer)));
}

void myXmlRpcServer::run()
{
#ifdef _DEBUG
       XmlRpcUtil::log(1,"start run");
#endif
        pm_xmlRpcServer.work(-1);

		int i = 0;
}

void myXmlRpcServer::exit()
{
	pm_xmlRpcServer.close();
	pm_xmlRpcServer.exit();
}

