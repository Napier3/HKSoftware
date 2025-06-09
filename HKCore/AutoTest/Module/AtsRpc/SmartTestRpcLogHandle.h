#ifndef MYLOGHANDLE_H
#define MYLOGHANDLE_H

#include "..\..\..\Module\XmlRpc\XmlRpc.h"

class CSmartTestRpcLogHandle : public XmlRpc::XmlRpcLogHandler
{
public:
    CSmartTestRpcLogHandle();

    virtual void log(int level, const char* msg);
};

#endif // MYLOGHANDLE_H
