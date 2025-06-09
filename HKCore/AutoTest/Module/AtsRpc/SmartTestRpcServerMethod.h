#ifndef MYXMLRPCSERVERMETHOD_H
#define MYXMLRPCSERVERMETHOD_H

#include"..\..\..\Module\XmlRpc\XmlRpcServerMethod.h"
#include"..\..\..\Module\XmlRpc\XmlRpcValue.h"
#include"..\..\..\Module\XmlRpc\XmlRpcServer.h"
#include"..\..\..\Module\XmlRpc\XmlRpcServerConnection.h"
#include "..\..\..\Module\DataMngr\DvmDataset.h"

#include "..\..\Module\XmlRpc\XmlRpcApi_MFC.h"

class CAtsRpc_InitSmartTestClient : public XmlRpcServerMethod
{
public:
   CAtsRpc_InitSmartTestClient(XmlRpcServer* s);
   virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_CreateTest : public XmlRpcServerMethod
{
public:
	CAtsRpc_CreateTest(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_BeginTest : public XmlRpcServerMethod
{
public:
	CAtsRpc_BeginTest(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_StopTest : public XmlRpcServerMethod
{
public:
	CAtsRpc_StopTest(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_TestAllInlegibleItems : public XmlRpcServerMethod
{
public:
	CAtsRpc_TestAllInlegibleItems(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_TestPoint : public XmlRpcServerMethod
{
public:
	CAtsRpc_TestPoint(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_TestBelow : public XmlRpcServerMethod
{
public:
	CAtsRpc_TestBelow(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_OpenGbrptFile : public XmlRpcServerMethod
{
public:
	CAtsRpc_OpenGbrptFile(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_IsSmartTestExist : public XmlRpcServerMethod
{
public:
	CAtsRpc_IsSmartTestExist(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_ExitSmartTest : public XmlRpcServerMethod
{
public:
	CAtsRpc_ExitSmartTest(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_CloseTest : public XmlRpcServerMethod
{
public:
	CAtsRpc_CloseTest(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_ExportRpt : public XmlRpcServerMethod
{
public:
	CAtsRpc_ExportRpt(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_ViewItemRpt : public XmlRpcServerMethod
{
public:
	CAtsRpc_ViewItemRpt(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_GetAllTestItems : public XmlRpcServerMethod
{
public:
	CAtsRpc_GetAllTestItems(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_GetTestItemReport : public XmlRpcServerMethod
{
public:
	CAtsRpc_GetTestItemReport(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_TestItem : public XmlRpcServerMethod
{
public:
	CAtsRpc_TestItem(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_GetDvmDatas : public XmlRpcServerMethod
{
public:
	CAtsRpc_GetDvmDatas(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_GetReportFiles : public XmlRpcServerMethod
{
public:
	CAtsRpc_GetReportFiles(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_ExecCmd : public XmlRpcServerMethod
{
public:
	CAtsRpc_ExecCmd(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

class CAtsRpc_GbDevWzdAuto : public XmlRpcServerMethod
{
public:
	CAtsRpc_GbDevWzdAuto(XmlRpcServer* s);
	virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};

#endif // MYXMLRPCSERVERMETHOD_H
