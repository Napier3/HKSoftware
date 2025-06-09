#include "mms_server_internal.h"
#include "iso_server_private.h"
#include "mms_server_func.h"

int GspServer_handleTest(GspMmsServerConnection self, GspByteBuffer *message, GspByteBuffer *response) {
    IsoConnection_sendGspResp(self->isoConnection, response);
    return 0;
}

void *GspServerTest::handleTest(GspMmsServerConnection self, void *request)
{
    return nullptr;
}