#ifndef MYLOGHANDLE_H
#define MYLOGHANDLE_H

#include "..\..\..\Module\XmlRpc\XmlRpc.h"

class CAtsRpcClientLogHandle : public XmlRpc::XmlRpcLogHandler
{
public:
    CAtsRpcClientLogHandle();

    virtual void log(int level, const char* msg);
};

#endif // MYLOGHANDLE_H
