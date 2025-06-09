/*
 *  iso_server.h
 */

#ifndef GSP_ISO_SERVER_H_
#define GSP_ISO_SERVER_H_

#include "byte_buffer.h"
#include "gsp_iso_connection_parameters.h"

typedef enum {
    GSP_SC_Associate = 1,
    GSP_SC_Abort = 2,
    GSP_SC_Release = 3,
    GSP_SC_GetServerDirectory = 80,
    GSP_SC_GetLogicDeviceDirectory = 81,
    GSP_SC_GetLogicNodeDirectory = 82,
    GSP_SC_GetAllDataValues = 83,
    GSP_SC_GetAllDataDefinition = 155,
    GSP_SC_GetAllCBValues = 156,
    GSP_SC_GetDataValues = 48,
    GSP_SC_SetDataValues = 49,
    GSP_SC_GetDataDirectory = 50,
    GSP_SC_GetDataDefinition = 51,
    GSP_SC_CreateDataSet = 54,
    GSP_SC_DeleteDataSet = 55,
    GSP_SC_GetDataSetDirectory = 57,
    GSP_SC_GetDataSetValues = 58,
    GSP_SC_SetDataSetValues = 59,
    GSP_SC_Select = 68,
    GSP_SC_SelectWithValue = 69,
    GSP_SC_Cancel = 70,
    GSP_SC_Operate = 71,
    GSP_SC_CommandTermination = 72,
    GSP_SC_TimeActivatedOperate = 73,
    GSP_SC_TimeActivatedOperateTermination = 74,
    GSP_SC_SelectActiveSG = 84,
    GSP_SC_SelectEditSG = 85,
    GSP_SC_SetEditSGValue = 86,
    GSP_SC_ConfirmEditSGValues = 87,
    GSP_SC_GetEditSGValue = 88,
    GSP_SC_GetSGCBValues = 89,
    GSP_SC_Report = 90,
    GSP_SC_GetBRCBValues = 91,
    GSP_SC_SetBRCBValues = 92,
    GSP_SC_GetURCBValues = 93,
    GSP_SC_SetURCBValues = 94,
    GSP_SC_GetLCBValues = 95,
    GSP_SC_SetLCBValues = 96,
    GSP_SC_QueryLogByTime = 97,
    GSP_SC_QueryLogAfter = 98,
    GSP_SC_GetLogStatusValues = 99,
    GSP_SC_GetGoCBValues = 102,
    GSP_SC_SetGoCBValues = 103,
    GSP_SC_GetMSVCBValues = 105,
    GSP_SC_SetMSVCBValues = 106,
    GSP_SC_GetFile = 128,
    GSP_SC_SetFile = 129,
    GSP_SC_DeleteFile = 130,
    GSP_SC_GetFileAttributeValues = 131,
    GSP_SC_GetFileDirectory = 132,
    GSP_SC_GetRpcInterfaceDirectory = 110,
    GSP_SC_GetRpcMethodDirectory = 111,
    GSP_SC_GetRpcInterfaceDefinition = 112,
    GSP_SC_GetRpcMethodDefinition = 113,
    GSP_SC_RpcCall = 114,
    GSP_SC_Test = 153,
    GSP_SC_AssociateNegotiate = 154
} GSP_SC;

typedef enum
{
    GSP_ISO_SVR_STATE_IDLE,
    GSP_ISO_SVR_STATE_RUNNING,
    GSP_ISO_SVR_STATE_STOPPED,
    GSP_ISO_SVR_STATE_ERROR
} GspIsoServerState;

typedef struct sGspIsoServer* GspIsoServer;

typedef enum
{
    GSP_ISO_CONNECTION_OPENED,
    GSP_ISO_CONNECTION_CLOSED
} GspIsoConnectionIndication;

typedef struct sGspIsoConnection* GspIsoConnection;

typedef struct sGspIsoServerCallbacks
{
    void (*clientConnected)(GspIsoConnection connection);
} GspIsoServerCallbacks;

typedef void (*GspConnectionIndicationHandler)(GspIsoConnectionIndication indication, void* parameter, GspIsoConnection connection);

typedef void (*GspMessageReceivedHandler)(void* parameter, GspByteBuffer* message, GspByteBuffer* response);

typedef void (*GspUserLayerTickHandler)(void* parameter);

LIB860_INTERNAL char* GspIsoConnection_getPeerAddress(GspIsoConnection self);

LIB860_INTERNAL char* GspIsoConnection_getLocalAddress(GspIsoConnection self);

LIB860_INTERNAL void GspIsoConnection_close(GspIsoConnection self);

LIB860_INTERNAL uint64_t GspIsoConnection_getConnectID(GspIsoConnection self);

LIB860_INTERNAL void GspIsoConnection_lock(GspIsoConnection self);

LIB860_INTERNAL void GspIsoConnection_unlock(GspIsoConnection self);

LIB860_INTERNAL void GspIsoConnection_installListener(GspIsoConnection self, GspMessageReceivedHandler rcvdHandler,
                                                      GspUserLayerTickHandler tickHandler,
                                                      void* parameter);

LIB860_INTERNAL void GspIsoConnection_installGspListener(GspIsoConnection self,
                                                         GspMessageReceivedHandler rcvdMmsHandler,
                                                         GspMessageReceivedHandler rcvdGspHandler,
                                                         GspUserLayerTickHandler tickHandler,
                                                         void* parameter);

LIB860_INTERNAL uint8_t GspIsoConnection_getGspSc(GspIsoConnection self);

LIB860_INTERNAL int GspIsoConnection_getGspNext(GspIsoConnection self);

LIB860_INTERNAL int GspIsoConnection_getGspResp(GspIsoConnection self);

LIB860_INTERNAL int GspIsoConnection_getGspError(GspIsoConnection self);

LIB860_INTERNAL void GspIsoConnection_setCc(GspIsoConnection self, uint8_t next, uint8_t resp, uint8_t error);

LIB860_INTERNAL void* GspIsoConnection_getSecurityToken(GspIsoConnection self);

LIB860_INTERNAL GspIsoServer GspIsoServer_create(GspTLSConfiguration tlsConfiguration);

LIB860_INTERNAL void GspIsoServer_setTcpPort(GspIsoServer self, int port);

LIB860_INTERNAL void GspIsoServer_setMaxConnections(GspIsoServer self, int maxConnections);

LIB860_INTERNAL void GspIsoServer_setLocalIpAddress(GspIsoServer self, const char* ipAddress);

LIB860_INTERNAL GspIsoServerState GspIsoServer_getState(GspIsoServer self);

LIB860_INTERNAL void GspIsoServer_setConnectionHandler(GspIsoServer self, GspConnectionIndicationHandler handler, void* parameter);

LIB860_INTERNAL void GspIsoServer_setAuthenticator(GspIsoServer self, GspAcseAuthenticator authenticator, void* authenticatorParameter);

LIB860_INTERNAL GspAcseAuthenticator GspIsoServer_getAuthenticator(GspIsoServer self);

LIB860_INTERNAL void* GspIsoServer_getAuthenticatorParameter(GspIsoServer self);

LIB860_INTERNAL GspTLSConfiguration GspIsoServer_getTLSConfiguration(GspIsoServer self);

LIB860_INTERNAL void GspIsoServer_startListening(GspIsoServer self);

LIB860_INTERNAL void GspIsoServer_stopListening(GspIsoServer self);

LIB860_INTERNAL void GspIsoServer_startListeningThreadless(GspIsoServer self);

LIB860_INTERNAL void GspIsoServer_processIncomingMessages(GspIsoServer self);

LIB860_INTERNAL int GspIsoServer_getConnectionCounter(GspIsoServer self);

LIB860_INTERNAL int GspIsoServer_waitReady(GspIsoServer self, unsigned int timeoutMs);

LIB860_INTERNAL void GspIsoServer_stopListeningThreadless(GspIsoServer self);

LIB860_INTERNAL void GspIsoServer_closeConnection(GspIsoServer self, GspIsoConnection isoConnection);

LIB860_INTERNAL void GspIsoServer_destroy(GspIsoServer self);

LIB860_INTERNAL int GspIsoServer_getConnectionId(GspIsoServer self, GspIsoConnection isoConnection);

#endif /* ISO_SERVER_H_ */
