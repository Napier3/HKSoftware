#ifndef MYXMLRPCSERVER_H
#define MYXMLRPCSERVER_H
#include "..\..\..\Module\XmlRpc\XmlRpc.h"

#include "AtsRpcClientMethod.h"
#include"AtsRpcClientloghandle.h"
#include "AtsRpcServerConfig.h"

#define AtsRpcClientXmlRpcServer_Port   13240

class CAtsRpcClientXmlRpcServer 
{
public:
	CAtsRpcClientXmlRpcServer();
	virtual ~CAtsRpcClientXmlRpcServer();

	void run();
	void exit();
	//long getConnectSize()  {	return m_oXmlRpcServer.getSize();	}

private:
	void RegisterMethods();

	XmlRpc::XmlRpcServer m_oXmlRpcServer;
	std::list< XmlRpcServerMethod* > m_listServerMethods;
	CAtsRpcClientLogHandle* m_pLog;
};



#endif // MYXMLRPCSERVER_H
