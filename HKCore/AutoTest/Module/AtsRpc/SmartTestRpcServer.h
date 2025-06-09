#ifndef MYXMLRPCSERVER_H
#define MYXMLRPCSERVER_H
#include "..\..\..\Module\XmlRpc\XmlRpc.h"

#include "SmartTestRpcServerMethod.h"
#include"SmartTestRpcloghandle.h"
#include "AtsRpcServerConfig.h"

class CSmartTestRpcXmlRpcServer 
{
public:
	CSmartTestRpcXmlRpcServer(const CString &strServer, long nPort);
	virtual ~CSmartTestRpcXmlRpcServer();

	void run();
	void exit();

private:
	CSmartTestRpcXmlRpcServer()	{}

private:
	void RegisterMethods();

	XmlRpc::XmlRpcServer m_oXmlRpcServer;
	std::list< XmlRpcServerMethod* > m_listServerMethods;
	CSmartTestRpcLogHandle* m_pLog;
};



#endif // MYXMLRPCSERVER_H
