/*
 *  client_connection.c
 */

#include "dlt860_server.h"
#include "iso_server.h"
#include "mms_mapping.h"
#include "control.h"
#include "stack_config.h"
#include "gsp_hal_thread.h"

#include "ied_server_private.h"

#include "libdlt860_platform_includes.h"

struct sGspClientConnection {

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore tasksCountMutex;
#endif

    int tasksCount;
    void* serverConnectionHandle;
};

GspClientConnection
Gsp_private_ClientConnection_create(void* serverConnectionHandle)
{
    GspClientConnection self = (GspClientConnection) GLOBAL_MALLOC(sizeof(struct sGspClientConnection));

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    self->tasksCountMutex = GspSemaphore_create(1);
#endif

    self->tasksCount = 0;
    self->serverConnectionHandle = serverConnectionHandle;

    return self;
}

void
Gsp_private_ClientConnection_destroy(GspClientConnection self)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_destroy(self->tasksCountMutex);
#endif

    GLOBAL_FREEMEM(self);
}

int
Gsp_private_ClientConnection_getTasksCount(GspClientConnection self)
{
    int tasksCount;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_wait(self->tasksCountMutex);
#endif

    tasksCount = self->tasksCount;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_post(self->tasksCountMutex);
#endif

    return tasksCount;
}

void
Gsp_private_ClientConnection_increaseTasksCount(GspClientConnection self)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_wait(self->tasksCountMutex);
#endif

    self->tasksCount++;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_post(self->tasksCountMutex);
#endif
}

void
Gsp_private_ClientConnection_decreaseTasksCount(GspClientConnection self)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_wait(self->tasksCountMutex);
#endif

    self->tasksCount--;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_post(self->tasksCountMutex);
#endif
}

void*
Gsp_private_ClientConnection_getServerConnectionHandle(GspClientConnection self)
{
    return self->serverConnectionHandle;
}


const char*
GspClientConnection_getPeerAddress(GspClientConnection self)
{
    GspMmsServerConnection mmsConnection = (GspMmsServerConnection) self->serverConnectionHandle;

    return GspMmsServerConnection_getClientAddress(mmsConnection);
}

const char*
GspClientConnection_getLocalAddress(GspClientConnection self)
{
    GspMmsServerConnection mmsConnection = (GspMmsServerConnection) self->serverConnectionHandle;

    return GspMmsServerConnection_getLocalAddress(mmsConnection);
}


void*
GspClientConnection_getSecurityToken(GspClientConnection self)
{
    GspMmsServerConnection mmsConnection = (GspMmsServerConnection) self->serverConnectionHandle;

    return GspMmsServerConnection_getSecurityToken(mmsConnection);
}


uint64_t GspClientConnection_getConnectID(GspClientConnection self)
{
    GspMmsServerConnection mmsConnection = (GspMmsServerConnection) self->serverConnectionHandle;
    return GspMmsServerConnection_getConnectID(mmsConnection);
}