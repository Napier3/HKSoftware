#ifndef MYXMLRPCSERVERMETHOD_H
#define MYXMLRPCSERVERMETHOD_H

#include"..\..\..\Module\XmlRpc\XmlRpcServerMethod.h"
#include"..\..\..\Module\XmlRpc\XmlRpcValue.h"
#include"..\..\..\Module\XmlRpc\XmlRpcServer.h"
#include"..\..\..\Module\XmlRpc\XmlRpcServerConnection.h"
#include "..\..\..\Module\DataMngr\DvmDataset.h"

#include "..\..\Module\XmlRpc\XmlRpcApi_MFC.h"
#include "AtsRpcMethodID.h"

class CAtsRpcClient_OnItemStateChanged : public XmlRpcServerMethod
{
public:
   CAtsRpcClient_OnItemStateChanged(XmlRpcServer* s);
   virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpcClient_OnTestFinished : public XmlRpcServerMethod
{
public:
	CAtsRpcClient_OnTestFinished(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpcClient_OnTestStoped : public XmlRpcServerMethod
{
public:
	CAtsRpcClient_OnTestStoped(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpcClient_OnExportRptFinished : public XmlRpcServerMethod
{
public:
	CAtsRpcClient_OnExportRptFinished(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpcClient_OnTestAppError : public XmlRpcServerMethod
{
public:
	CAtsRpcClient_OnTestAppError(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpcClient_OnEngineError : public XmlRpcServerMethod
{
public:
	CAtsRpcClient_OnEngineError(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpcClient_SmartTestCreated : public XmlRpcServerMethod
{
public:
	CAtsRpcClient_SmartTestCreated(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpcClient_GbrptOpened : public XmlRpcServerMethod
{
public:
	CAtsRpcClient_GbrptOpened(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpcClient_GbDevCreated : public XmlRpcServerMethod
{
public:
	CAtsRpcClient_GbDevCreated(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpcClient_GbDevFinished : public XmlRpcServerMethod
{
public:
	CAtsRpcClient_GbDevFinished(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpcClient_OnConnectDeviceFailed : public XmlRpcServerMethod
{
public:
	CAtsRpcClient_OnConnectDeviceFailed(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpcClient_OnOpenGbrptFailed : public XmlRpcServerMethod
{
public:
	CAtsRpcClient_OnOpenGbrptFailed(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

#endif // MYXMLRPCSERVERMETHOD_H
