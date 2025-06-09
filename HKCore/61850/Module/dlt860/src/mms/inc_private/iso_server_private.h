/*
 *  iso_server_private.h
 */

#ifndef GSP_ISO_SERVER_PRIVATE_H_
#define GSP_ISO_SERVER_PRIVATE_H_

#include "gsp_tls_config.h"
#include "gsp_hal_socket.h"
#include "gsp_hal_thread.h"
#include "libdlt860_common_api.h"
#include "iso_server.h"

LIB860_INTERNAL GspIsoConnection IsoConnection_create(GspSocket socket, GspIsoServer isoServer, bool isSingleThread);

LIB860_INTERNAL void IsoConnection_start(GspIsoConnection self);

LIB860_INTERNAL void IsoConnection_destroy(GspIsoConnection self);

LIB860_INTERNAL void IsoConnection_callTickHandler(GspIsoConnection self);

LIB860_INTERNAL void IsoConnection_handleGspTcpConnection(GspIsoConnection self, bool isSingleThread);

LIB860_INTERNAL int IsoConnection_sendGspData(GspIsoConnection self, uint8_t error, uint8_t respFlag, GspByteBuffer *response);

LIB860_INTERNAL int IsoConnection_sendGspResp(GspIsoConnection self, GspByteBuffer *response);

LIB860_INTERNAL int IsoConnection_sendGspReport(GspIsoConnection self, GspByteBuffer *response);

LIB860_INTERNAL int IsoConnection_sendGspError(GspIsoConnection self, GspByteBuffer *response);

#define GSP_ISO_CON_STATE_TERMINATED 2 /* connection has terminated and is ready to be destroyed */
#define GSP_ISO_CON_STATE_RUNNING 1 /* connection is newly started */
#define GSP_ISO_CON_STATE_STOPPED 0 /* connection is being stopped */

LIB860_INTERNAL int IsoConnection_getState(GspIsoConnection self);

/**
 * \brief Add the connection socket to the given HandleSet instance
 */
LIB860_INTERNAL void IsoConnection_addToHandleSet(const GspIsoConnection self, GspHandleSet handles);

/**
 * \brief Remove the connection socket from the given HandleSet instance
 */
LIB860_INTERNAL void IsoConnection_removeFromHandleSet(const GspIsoConnection self, GspHandleSet handles);

LIB860_INTERNAL void Private_IsoServer_increaseConnectionCounter(GspIsoServer self);

LIB860_INTERNAL void Private_IsoServer_decreaseConnectionCounter(GspIsoServer self);

LIB860_INTERNAL int private_IsoServer_getConnectionCounter(GspIsoServer self);

/**
 * \brief User provided lock that will be called when higher layer (MMS) is called
 */
LIB860_INTERNAL void IsoServer_setUserLock(GspIsoServer self, GspSemaphore userLock);

LIB860_INTERNAL void IsoServer_userLock(GspIsoServer self);

LIB860_INTERNAL void IsoServer_userUnlock(GspIsoServer self);

LIB860_INTERNAL bool IsoConnection_isRunning(GspIsoConnection self);

#endif /* ISO_SERVER_PRIVATE_H_ */
