#ifndef MYLOGHANDLE_H
#define MYLOGHANDLE_H

#include"../xmlrpc/XmlRpc.h"

class MyLogHandle : public XmlRpc::XmlRpcLogHandler
{
public:
    MyLogHandle();

    virtual void log(int level, const char* msg);
};

#endif // MYLOGHANDLE_H
