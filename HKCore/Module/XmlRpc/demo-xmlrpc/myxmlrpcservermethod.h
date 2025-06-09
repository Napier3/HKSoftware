#ifndef MYXMLRPCSERVERMETHOD_H
#define MYXMLRPCSERVERMETHOD_H

#include"../xmlrpc/XmlRpcServerMethod.h"
#include"../xmlrpc/XmlRpcValue.h"
#include"../xmlrpc/XmlRpcServer.h"
#include"../xmlrpc/XmlRpcServerConnection.h"

using namespace XmlRpc;

class myXmlRpcServerMethod : public XmlRpcServerMethod
{
public:
  myXmlRpcServerMethod
   (const char *name, XmlRpcServer * server):XmlRpcServerMethod(name, server) {}
   virtual void execute(XmlRpcValue & params, XmlRpcValue& result) {}
};

class Start:public myXmlRpcServerMethod
{
public:
   Start(XmlRpcServer* s);
   virtual void execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context);
};


class TestItem:public myXmlRpcServerMethod
{
public:
    TestItem(XmlRpcServer* s);
     virtual void execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context);//zhangsen20170402
};
// 
// class SetBinaryInSetting:public myXmlRpcServerMethod
// {
// public:
//     SetBinaryInSetting(XmlRpcServer* s);
//      virtual void execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context);
// };
// 
// class SetSetting:public myXmlRpcServerMethod
// {
// public:
//     SetSetting(XmlRpcServer* s);
//      virtual void execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context);
// };
// 
// class LockerDispel:public myXmlRpcServerMethod
// {
// public:
// 
//     LockerDispel(XmlRpcServer* s);
//      virtual void execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context);
// };
// 
class TestParaSet:public myXmlRpcServerMethod
{
public:
    TestParaSet(XmlRpcServer* s);
     virtual void execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context);
};
// 
// class DeviceInnerParaSet:public myXmlRpcServerMethod
// {
// public:
//     DeviceInnerParaSet(XmlRpcServer* s);
//      virtual void execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context);
// };
// 
// class DeviceInnerParaRead:public myXmlRpcServerMethod
// {
// public:
//     DeviceInnerParaRead(XmlRpcServer* s);
//      virtual void execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context);
// };
// 
// class Read:public myXmlRpcServerMethod
// {
// public:
//     Read(XmlRpcServer* s);
//      virtual void execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context);
// };
// 
// class Write:public myXmlRpcServerMethod
// {
// public:
//     Write(XmlRpcServer* s);
//      virtual void execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context);
// };
// 
// 
// class ReadCompensation:public myXmlRpcServerMethod
// {
// public:
//     ReadCompensation(XmlRpcServer* s);
//      virtual void execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context);
// };
// 
// class WriteCompensation:public myXmlRpcServerMethod
// {
// public:
//     WriteCompensation(XmlRpcServer* s);
//      virtual void execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context);
// };
// 
// 
// class TestParaOutput:public myXmlRpcServerMethod
// {
// public:
//     TestParaOutput(XmlRpcServer* s);
//      virtual void execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context);
// };
// 
// class PSUDifferTest:public myXmlRpcServerMethod
// {
// public:
//     PSUDifferTest(XmlRpcServer* s);
//      virtual void execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context);
// };
// 
// class PSUDistanceTest:public myXmlRpcServerMethod
// {
// public:
//     PSUDistanceTest(XmlRpcServer* s);
//      virtual void execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context);
// };
// 
// class PSUSearchZBorderTest:public myXmlRpcServerMethod
// {
// public:
//     PSUSearchZBorderTest(XmlRpcServer* s);
//      virtual void execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context);
// };
// 
#endif // MYXMLRPCSERVERMETHOD_H
