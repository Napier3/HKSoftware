#include "asn_inc.h"
#include "mms_server_func.h"


void *GspServerControl::handleSelect(GspMmsServerConnection self, void *request)
{
    return request;
}
void *GspServerControl::handleSelectWithValue(GspMmsServerConnection self, void *request)
{
    return request;
}

void *GspServerControl::handleCancel(GspMmsServerConnection self, void *request)
{
    return request;
}

void *GspServerControl::handleOperate(GspMmsServerConnection self, void *request)
{
    return request;
}

void *GspServerControl::handleCommandTermination(GspMmsServerConnection self, void *request)
{
    return nullptr;
}

void *GspServerControl::handleTimeActivatedOperate(GspMmsServerConnection self, void *request)
{
    return request;
}

void *GspServerControl::handleTimeActivatedOperateTermination(GspMmsServerConnection self, void *request)
{
    return nullptr;
}
