/*
 *  iso_server.c
 */

#include "libdlt860_platform_includes.h"

#include "stack_config.h"

#ifndef DEBUG_ISO_SERVER
#ifdef DEBUG
#define DEBUG_ISO_SERVER 1
#else
#define DEBUG_ISO_SERVER 0
#endif /*DEBUG */
#endif /* DEBUG_ISO_SERVER */

#include "mms_server_connection.h"

#include "gsp_hal_thread.h"

#include "iso_server.h"

#include "iso_server_private.h"

#ifndef CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS
#define CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS 32
#endif

#define TCP_PORT 102
#define SECURE_TCP_PORT 3782
#define BACKLOG 10

struct sGspIsoServer {
    GspIsoServerState state;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore stateLock;
#endif

    GspConnectionIndicationHandler connectionHandler;
    void* connectionHandlerParameter;

    GspAcseAuthenticator authenticator;
    void* authenticatorParameter;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspThread serverThread;
#endif

    GspHandleSet handleset;

    GspSocket serverSocket;
    int tcpPort;
    const char* localIpAddress;

    GspTLSConfiguration tlsConfiguration;

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)
    int maxConnections;
#endif

#if (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1)
    LinkedList openClientConnections;
#else
    GspIsoConnection openClientConnections[CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS];
#endif /* (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1) */

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    /* used to control access to server data model */
    GspSemaphore userLock;
#endif

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    Semaphore openClientConnectionsMutex; /* mutex for openClientConnections list */
    Semaphore connectionCounterMutex;
#endif

    int connectionCounter;
};

static void
setState(GspIsoServer self, GspIsoServerState newState)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_wait(self->stateLock);
#endif
    self->state = newState;
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_post(self->stateLock);
#endif
}

static GspIsoServerState
getState(GspIsoServer self)
{
    GspIsoServerState state;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_wait(self->stateLock);
#endif
    state = self->state;
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_post(self->stateLock);
#endif

    return state;
}

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
static inline void
lockClientConnections(IsoServer self)
{
    Semaphore_wait(self->openClientConnectionsMutex);
}

static inline void
unlockClientConnections(IsoServer self)
{
    Semaphore_post(self->openClientConnectionsMutex);
}
#endif /* (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1) */

static void
addClientConnection(GspIsoServer self, GspIsoConnection connection)
{

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    Semaphore_wait(self->connectionCounterMutex);
#endif

    self->connectionCounter++;
    if (DEBUG_ISO_SERVER)
        printf("ISO_SERVER: increase connection counter to %i!\n", self->connectionCounter);

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    lockClientConnections(self);
#endif

#if (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1)
    LinkedList_add(self->openClientConnections, connection);
#else
    int i;

    for (i = 0; i < CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS; i++) {
        if (self->openClientConnections[i] == NULL) {
            self->openClientConnections[i] = connection;

            if (DEBUG_ISO_SERVER)
                printf("ISO_SERVER: added connection (%p) index:%i\n", connection, i);

            break;
        }
    }
#endif

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    unlockClientConnections(self);
#endif

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    Semaphore_post(self->connectionCounterMutex);
#endif

}

static void
removeClientConnection(GspIsoServer self, GspIsoConnection connection)
{
#if (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1)

    LinkedList_remove(self->openClientConnections, connection);

#if (CONFIG_MMS_SINGLE_THREADED == 1)
    IsoConnection_removeFromHandleSet(connection, self->handleset);
#endif


#else

    int i;

    for (i = 0; i < CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS; i++) {
        if (self->openClientConnections[i] == connection) {

#if (CONFIG_MMS_SINGLE_THREADED == 1)
            IsoConnection_removeFromHandleSet(connection, self->handleset);
#endif

            if (DEBUG_ISO_SERVER)
                printf("ISO_SERVER: removed connection (%p) index:%i\n", connection, i);

            self->openClientConnections[i] = NULL;
            break;
        }
    }
#endif /* (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1) */
}

static void
removeTerminatedConnections(GspIsoServer self, bool isSingleThread)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    lockClientConnections(self);
#endif

#if (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1)

    LinkedList openConnection = LinkedList_getNext(self->openClientConnections);

    while (openConnection) {
        IsoConnection isoConnection = (IsoConnection) openConnection->data;

        if (isSingleThread) {
            if (IsoConnection_getState(isoConnection) == ISO_CON_STATE_STOPPED) {

                self->connectionHandler(ISO_CONNECTION_CLOSED, self->connectionHandlerParameter,
                        isoConnection);

                IsoConnection_close(isoConnection);
            }
        }

        if (IsoConnection_getState(isoConnection) == ISO_CON_STATE_TERMINATED) {
            removeClientConnection(self, isoConnection);
            IsoConnection_destroy(isoConnection);
            openConnection = LinkedList_getNext(self->openClientConnections);
        }
        else
            openConnection = LinkedList_getNext(openConnection);
    }

#else
    int i;

    for (i = 0; i < CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS; i++) {
        if (self->openClientConnections[i] != NULL) {

            GspIsoConnection isoConnection = self->openClientConnections[i];

            if (isSingleThread) {
                if (IsoConnection_getState(isoConnection) == GSP_ISO_CON_STATE_STOPPED) {

                    self->connectionHandler(GSP_ISO_CONNECTION_CLOSED, self->connectionHandlerParameter,
                            isoConnection);

                    GspIsoConnection_close(isoConnection);

                    IsoConnection_removeFromHandleSet(isoConnection, self->handleset);
                }
            }

            if (IsoConnection_getState(isoConnection) == GSP_ISO_CON_STATE_TERMINATED) {
                removeClientConnection(self, isoConnection);
                IsoConnection_destroy(isoConnection);
            }
        }
    }
#endif /* (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1) */

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    unlockClientConnections(self);
#endif

}

static void
closeAllOpenClientConnections(GspIsoServer self)
{

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    lockClientConnections(self);
#endif

#if (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1)

    LinkedList openConnection = LinkedList_getNext(self->openClientConnections);
    while (openConnection != NULL) {
        IsoConnection isoConnection = (IsoConnection) openConnection->data;

        IsoConnection_close(isoConnection);
        IsoConnection_destroy(isoConnection);

        openConnection = LinkedList_getNext(openConnection);
    }

#if (CONFIG_MMS_SINGLE_THREADED == 1)
    LinkedList_destroyStatic(self->openClientConnections);
    self->openClientConnections = NULL;
#endif

#else
    int i;

    for (i = 0; i < CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS; i++) {
        if (self->openClientConnections[i] != NULL) {
            GspIsoConnection_close(self->openClientConnections[i]);
            IsoConnection_destroy(self->openClientConnections[i]);
        }
    }
#endif /* (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1) */

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    unlockClientConnections(self);
#endif

}

static void
callTickHandlerForClientConnections(GspIsoServer self)
{

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    lockClientConnections(self);
#endif

#if (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1)

    LinkedList openConnection = LinkedList_getNext(self->openClientConnections);

    while (openConnection != NULL) {
        IsoConnection isoConnection = (IsoConnection) openConnection->data;

        IsoConnection_callTickHandler(isoConnection);

        openConnection = LinkedList_getNext(openConnection);
    }

#else
    int i;

    for (i = 0; i < CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS; i++) {
        if (self->openClientConnections[i] != NULL) {
            IsoConnection_callTickHandler(self->openClientConnections[i]);
        }
    }
#endif /* (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1) */

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    unlockClientConnections(self);
#endif

}

static void
handleClientConnections(GspIsoServer self)
{
#if (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1)

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    lockClientConnections(self);
#endif

    LinkedList openConnection = LinkedList_getNext(self->openClientConnections);

    while (openConnection != NULL) {
        IsoConnection isoConnection = (IsoConnection) openConnection->data;

        if (IsoConnection_isRunning(isoConnection))
            IsoConnection_handleTcpConnection(isoConnection, true);

        openConnection = LinkedList_getNext(openConnection);
    }

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    unlockClientConnections(self);
#endif

    removeTerminatedConnections(self, true);

#else

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    lockClientConnections(self);
#endif

    int i;

    for (i = 0; i < CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS; i++) {
        if (self->openClientConnections[i] != NULL) {
            if (IsoConnection_isRunning(self->openClientConnections[i])) {

                //IsoConnection_handleTcpConnection(self->openClientConnections[i], true);
                IsoConnection_handleGspTcpConnection(self->openClientConnections[i], true);
            }
            else {
                IsoConnection_destroy(self->openClientConnections[i]);

                self->openClientConnections[i] = NULL;
            }

        }
    }

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    unlockClientConnections(self);
#endif

    removeTerminatedConnections(self, true);

#endif /* (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1) */
}

static bool
setupIsoServer(GspIsoServer self)
{
    bool success = true;

    self->serverSocket = (GspSocket) GspTcpServerSocket_create(self->localIpAddress, self->tcpPort);

    if (self->serverSocket == NULL) {
        setState(self, GSP_ISO_SVR_STATE_ERROR);
        success = false;

        goto exit_function;
    }

    self->handleset = GspHandleset_new();
    GspHandleset_addSocket(self->handleset, self->serverSocket);

#if (CONFIG_ACTIVATE_TCP_KEEPALIVE == 1)
    GspSocket_activateTcpKeepAlive(self->serverSocket,
            CONFIG_TCP_KEEPALIVE_IDLE,
            CONFIG_TCP_KEEPALIVE_INTERVAL,
            CONFIG_TCP_KEEPALIVE_CNT);
#endif

    GspServerSocket_setBacklog((GspServerSocket) self->serverSocket, BACKLOG);

    GspServerSocket_listen((GspServerSocket) self->serverSocket);

    setState(self, GSP_ISO_SVR_STATE_RUNNING);

exit_function:
    return success;
}


/** used by single and multi-threaded versions
 *
 * \param isSingleThread when true server is running in single thread or non-thread mode
 */
static void
handleIsoConnections(GspIsoServer self, bool isSingleThread)
{
    if (isSingleThread) {
        /*
         * NOTE: when running in multi thread mode the tick handler is called
         * by the connection thread.
         */
        callTickHandlerForClientConnections(self);
    }

    if (GspHandleset_waitReady(self->handleset, 1) < 1)
        return;

    GspSocket connectionSocket;

    if ((connectionSocket = GspServerSocket_accept((GspServerSocket) self->serverSocket)) != NULL) {

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)
        if (self->maxConnections > -1) {
            if (private_IsoServer_getConnectionCounter(self) >= self->maxConnections) {
                if (DEBUG_ISO_SERVER)
                    printf("ISO_SERVER: maximum number of connections reached -> reject connection attempt.\n");

                GspSocket_destroy(connectionSocket);

                return;
            }
        }
#endif /* (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1) */

#if (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS != -1)
        if (private_IsoServer_getConnectionCounter(self) >= CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS) {
            if (DEBUG_ISO_SERVER)
                printf("ISO_SERVER: maximum number of connections reached -> reject connection attempt.\n");

            GspSocket_destroy(connectionSocket);

            if (isSingleThread)
                handleClientConnections(self);

            return;
        }
#endif

        GspIsoConnection isoConnection = IsoConnection_create(connectionSocket, self, isSingleThread);

        if (isoConnection) {
            addClientConnection(self, isoConnection);

            if (isSingleThread)
                IsoConnection_addToHandleSet(isoConnection, self->handleset);

            self->connectionHandler(GSP_ISO_CONNECTION_OPENED, self->connectionHandlerParameter,
                    isoConnection);

            if (isSingleThread == false)
                IsoConnection_start(isoConnection);
        }
        else {
            GspSocket_destroy(connectionSocket);
        }
    }

    if (isSingleThread)
        handleClientConnections(self);
}

#if (CONFIG_MMS_SINGLE_THREADED == 0) && (CONFIG_MMS_THREADLESS_STACK == 0)
/* only required for multi-threaded server! */
static void
isoServerThread(void* isoServerParam)
{
    IsoServer self = (IsoServer) isoServerParam;

    if (!setupIsoServer(self)) {
        if (DEBUG_ISO_SERVER)
            printf("ISO_SERVER: starting server failed!\n");

        self->serverSocket = NULL;

        goto cleanUp;
    }

    if (DEBUG_ISO_SERVER)
        printf("ISO_SERVER: isoServerThread %p started\n", &isoServerParam);

    while (self->state == ISO_SVR_STATE_RUNNING)
    {
        removeTerminatedConnections(self, false);

        handleIsoConnections(self, false);
    }

    self->state = ISO_SVR_STATE_STOPPED;

cleanUp:

    if (DEBUG_ISO_SERVER)
        printf("ISO_SERVER: isoServerThread %p stopped\n", &isoServerParam);
}
#endif

GspIsoServer
GspIsoServer_create(GspTLSConfiguration tlsConfiguration)
{
    GspIsoServer self = (GspIsoServer) GLOBAL_CALLOC(1, sizeof(struct sGspIsoServer));

    self->state = GSP_ISO_SVR_STATE_IDLE;

    if (tlsConfiguration == NULL)
        self->tcpPort = TCP_PORT;
    else
        self->tcpPort = SECURE_TCP_PORT;

    self->tlsConfiguration = tlsConfiguration;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    self->stateLock = GspSemaphore_create(1);
#endif

#if (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1)
    self->openClientConnections = LinkedList_create();
#endif

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)
    self->maxConnections = CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS;
#endif

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    self->connectionCounterMutex = Semaphore_create(1);
    self->openClientConnectionsMutex = Semaphore_create(1);
#endif /* (CONFIG_MMS_THREADLESS_STACK != 1) */

    self->connectionCounter = 0;

    return self;
}

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)
void
GspIsoServer_setMaxConnections(GspIsoServer self, int maxConnections)
{
    self->maxConnections = maxConnections;
}
#endif /* (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1) */

void
GspIsoServer_setTcpPort(GspIsoServer self, int port)
{
    self->tcpPort = port;
}

void
GspIsoServer_setLocalIpAddress(GspIsoServer self, const char* ipAddress)
{
	self->localIpAddress = ipAddress;
}

GspIsoServerState
GspIsoServer_getState(GspIsoServer self)
{
    return getState(self);
}

void
GspIsoServer_setAuthenticator(GspIsoServer self, GspAcseAuthenticator authenticator, void* authenticatorParameter)
{
    self->authenticator = authenticator;
    self->authenticatorParameter = authenticatorParameter;
}

GspAcseAuthenticator
GspIsoServer_getAuthenticator(GspIsoServer self)
{
    return self->authenticator;
}

void*
GspIsoServer_getAuthenticatorParameter(GspIsoServer self)
{
    return self->authenticatorParameter;
}

GspTLSConfiguration
GspIsoServer_getTLSConfiguration(GspIsoServer self)
{
    return self->tlsConfiguration;
}

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED != 1)
void
IsoServer_startListening(IsoServer self)
{
    if (self->state == ISO_SVR_STATE_RUNNING) {
        if (DEBUG_ISO_SERVER)
                printf("ISO_SERVER: server already in RUNNING state!\n");

        goto exit_function;
    }

    self->state = ISO_SVR_STATE_IDLE;

    self->serverThread = Thread_create((ThreadExecutionFunction) isoServerThread, self, false);

    Thread_start(self->serverThread);

    /* wait until server is up */
    while (self->state == ISO_SVR_STATE_IDLE)
        Thread_sleep(1);

    if (DEBUG_ISO_SERVER)
        printf("ISO_SERVER: new iso server thread started\n");

exit_function:
    return;
}
#endif /* (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED != 1) */

void
GspIsoServer_startListeningThreadless(GspIsoServer self)
{
    if (!setupIsoServer(self)) {
        if (DEBUG_ISO_SERVER)
            printf("ISO_SERVER: starting server failed!\n");

        self->serverSocket = NULL;
    }
    else {
        setState(self, GSP_ISO_SVR_STATE_RUNNING);

        if (DEBUG_ISO_SERVER)
            printf("ISO_SERVER: new iso server (threadless) started\n");
    }
}

int
GspIsoServer_waitReady(GspIsoServer self, unsigned int timeoutMs)
{
   int result;

   if (getState(self) == GSP_ISO_SVR_STATE_RUNNING) {

       if (self->handleset) {
           result = GspHandleset_waitReady(self->handleset, 10);
       }
       else {
           if (DEBUG_ISO_SERVER)
               printf("ISO_SERVER: internal error - no handleset!\n");
       }

   } else {
       result = -1;
   }

   return result;
}

void
GspIsoServer_processIncomingMessages(GspIsoServer self)
{
    if (getState(self) == GSP_ISO_SVR_STATE_RUNNING)
        handleIsoConnections(self, true);
}

int
GspIsoServer_getConnectionCounter(GspIsoServer self)
{
    return private_IsoServer_getConnectionCounter(self);
}

static void
stopListening(GspIsoServer self)
{
    setState(self, GSP_ISO_SVR_STATE_STOPPED);

    if (self->serverSocket != NULL) {
        GspServerSocket_destroy((GspServerSocket) self->serverSocket);
        self->serverSocket = NULL;
    }
}

void
GspIsoServer_stopListeningThreadless(GspIsoServer self)
{
    stopListening(self);

    closeAllOpenClientConnections(self);

    if (DEBUG_ISO_SERVER)
        printf("ISO_SERVER: IsoServer_stopListeningThreadless finished!\n");
}

#if (CONFIG_MMS_THREADLESS_STACK != 1)
void
GspIsoServer_stopListening(GspIsoServer self)
{
    setState(self, GSP_ISO_SVR_STATE_STOPPED);

    if (self->serverThread != NULL)
        GspThread_destroy(self->serverThread);

    if (self->serverSocket != NULL) {
        GspServerSocket_destroy((GspServerSocket) self->serverSocket);
        self->serverSocket = NULL;
    }

    closeAllOpenClientConnections(self);

    /* Wait for connection threads to finish */
    while (private_IsoServer_getConnectionCounter(self) > 0)
        GspThread_sleep(10);

    if (DEBUG_ISO_SERVER)
        printf("ISO_SERVER: IsoServer_stopListening finished!\n");
}
#endif

void
GspIsoServer_closeConnection(GspIsoServer self, GspIsoConnection isoConnection)
{
    if (getState(self) != GSP_ISO_SVR_STATE_IDLE) {
        self->connectionHandler(GSP_ISO_CONNECTION_CLOSED, self->connectionHandlerParameter,
                isoConnection);
    }
}

void
GspIsoServer_setConnectionHandler(GspIsoServer self, GspConnectionIndicationHandler handler,
        void* parameter)
{
    self->connectionHandler = handler;
    self->connectionHandlerParameter = parameter;
}

void
GspIsoServer_destroy(GspIsoServer self)
{

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    if (self->state == GSP_ISO_SVR_STATE_RUNNING)
        GspIsoServer_stopListening(self);
#endif

#if (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1)

#if (CONFIG_MMS_SINGLE_THREADED == 1)
    if (self->openClientConnections != NULL)
        LinkedList_destroy(self->openClientConnections);
#else
    if (self->openClientConnections != NULL)
        LinkedList_destroyStatic(self->openClientConnections);
#endif /* (CONFIG_MMS_SINGLE_THREADED == 1) */

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    lockClientConnections(self);
#endif

#endif /* (CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS == -1) */

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    Semaphore_destroy(self->connectionCounterMutex);
    Semaphore_destroy(self->openClientConnectionsMutex);
#endif

    if (self->handleset)
        GspHandleset_destroy(self->handleset);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_destroy(self->stateLock);
#endif

    GLOBAL_FREEMEM(self);
}

void
Private_IsoServer_decreaseConnectionCounter(GspIsoServer self)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    Semaphore_wait(self->connectionCounterMutex);
#endif

    self->connectionCounter--;

    if (DEBUG_ISO_SERVER)
        printf("IsoServer: decrease connection counter to %i!\n", self->connectionCounter);

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    Semaphore_post(self->connectionCounterMutex);
#endif
}

int
private_IsoServer_getConnectionCounter(GspIsoServer self)
{
    int connectionCounter;

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    Semaphore_wait(self->connectionCounterMutex);
#endif

    connectionCounter = self->connectionCounter;

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED == 0)
    Semaphore_post(self->connectionCounterMutex);
#endif

    return connectionCounter;
}

#if (CONFIG_MMS_THREADLESS_STACK != 1)

void
IsoServer_setUserLock(GspIsoServer self, GspSemaphore userLock)
{
    self->userLock = userLock;
}

void
IsoServer_userLock(GspIsoServer self)
{
    if (self->userLock != NULL)
        GspSemaphore_wait(self->userLock);
}

void
IsoServer_userUnlock(GspIsoServer self)
{
    if (self->userLock != NULL)
        GspSemaphore_post(self->userLock);
}

int
GspIsoServer_getConnectionId(GspIsoServer self, GspIsoConnection isoConnection) {
    for(int i = 0; i < CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS; ++i) {
        if(self->openClientConnections[i] == isoConnection) {
            return i;
        }
    }
    return -1;
}

#endif /* (CONFIG_MMS_THREADLESS_STACK != 1) */

