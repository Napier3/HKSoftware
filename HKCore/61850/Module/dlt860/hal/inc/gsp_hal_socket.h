/*
 *  socket_hal.h
 */

#ifndef GSP_SOCKET_HAL_H_
#define GSP_SOCKET_HAL_H_

#include "gsp_hal_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Opaque reference for a server socket instance */
typedef struct sGspServerSocket* GspServerSocket;

/** Opaque reference for a client or connection socket instance */
typedef struct sSocket* GspSocket;

/** Opaque reference for a set of server and socket handles */
typedef struct sHandleSet* GspHandleSet;

/** State of an asynchronous connect */
typedef enum
{
    GSP_SOCKET_STATE_CONNECTING = 0,
    GSP_SOCKET_STATE_FAILED = 1,
    GSP_SOCKET_STATE_CONNECTED = 2
} GspSocketState;

PAL_API GspHandleSet GspHandleset_new(void);

PAL_API void GspHandleset_reset(GspHandleSet self);

PAL_API void GspHandleset_addSocket(GspHandleSet self, const GspSocket sock);

void GspHandleset_removeSocket(GspHandleSet self, const GspSocket sock);

PAL_API int GspHandleset_waitReady(GspHandleSet self, unsigned int timeoutMs);

PAL_API void GspHandleset_destroy(GspHandleSet self);

PAL_API GspServerSocket GspTcpServerSocket_create(const char* address, int port);

PAL_API void GspServerSocket_listen(GspServerSocket self);

PAL_API GspSocket GspServerSocket_accept(GspServerSocket self);

PAL_API void GspSocket_activateTcpKeepAlive(GspSocket self, int idleTime, int interval, int count);

PAL_API void GspServerSocket_setBacklog(GspServerSocket self, int backlog);

PAL_API void GspServerSocket_destroy(GspServerSocket self);

PAL_API GspSocket GspTcpSocket_create(void);

PAL_API void GspSocket_setConnectTimeout(GspSocket self, uint32_t timeoutInMs);

PAL_API bool GspSocket_connect(GspSocket self, const char* address, int port);

PAL_API bool GspSocket_connectAsync(GspSocket self, const char* address, int port ,const char* local_address = NULL);//zhouhj 20210929 增加客户端本地IP地址的绑定

PAL_API GspSocketState GspSocket_checkAsyncConnectState(GspSocket self);

PAL_API int GspSocket_getId(GspSocket self);

PAL_API int GspSocket_read(GspSocket self, uint8_t* buf, int size);

PAL_API int GspSocket_write(GspSocket self, uint8_t* buf, int size);

PAL_API char* GspSocket_getLocalAddress(GspSocket self);

PAL_API char* GspSocket_getPeerAddress(GspSocket self);

PAL_API char* GspSocket_getPeerAddressStatic(GspSocket self, char* peerAddressString);

PAL_API void GspSocket_destroy(GspSocket self);

#ifdef __cplusplus
}
#endif

#endif /* GSP_SOCKET_HAL_H_ */
