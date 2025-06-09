#ifndef MYXMLRPCSERVER_H
#define MYXMLRPCSERVER_H
#include "myxmlrpcservermethod.h"
#include "../xmlrpc/XmlRpc.h"
#include"myloghandle.h"

class myXmlRpcServer 
{
public:
        myXmlRpcServer();
		virtual ~myXmlRpcServer();

        void run();
		void exit();

private:
        void pm_registerMethods();
        
        XmlRpc::XmlRpcServer pm_xmlRpcServer;
        std::list< myXmlRpcServerMethod* > pm_serverMethods;
        MyLogHandle* m_pLog;
};



#endif // MYXMLRPCSERVER_H
