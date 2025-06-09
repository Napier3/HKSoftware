/*
 *  mms_server_libinternal.h
 */

#ifndef GSP_MMS_SERVER_LIBINTERNAL_H_
#define GSP_MMS_SERVER_LIBINTERNAL_H_

#include "gsp_mms_server.h"
#include "mms_device_model.h"
#include <string>
#include <vector>

using namespace std;

typedef GspMmsValue* (*MmsReadVariableHandler)(void* parameter,
                                               GspMmsDomain* domain,
                                               char* variableId,
                                               GspMmsServerConnection connection);

typedef GspMmsDataAccessError (*MmsReadAccessHandler) (void* parameter,
                                                       GspMmsDomain* domain,
                                                       char* variableId,
                                                       GspMmsServerConnection connection);

typedef GspMmsDataAccessError (*MmsWriteVariableHandler)(void* parameter,
                                                         GspMmsDomain* domain,
                                                         char* variableId,
                                                         GspMmsValue* value,
                                                         GspMmsServerConnection connection);

typedef void (*MmsConnectionHandler)(void* parameter,
                                     GspMmsServerConnection connection,
                                     GspMmsServerEvent event);

LIB860_INTERNAL GspMmsServer MmsServer_create(GspMmsDevice* device, GspTLSConfiguration tlsConfiguration);

LIB860_INTERNAL void MmsServer_destroy(GspMmsServer self);

LIB860_INTERNAL void MmsServer_installReadHandler(GspMmsServer self, MmsReadVariableHandler, void* parameter);

LIB860_INTERNAL void MmsServer_installReadAccessHandler(GspMmsServer self, MmsReadAccessHandler, void* parameter);

LIB860_INTERNAL void MmsServer_installWriteHandler(GspMmsServer self, MmsWriteVariableHandler, void* parameter);

LIB860_INTERNAL void MmsServer_installConnectionHandler(GspMmsServer self, MmsConnectionHandler, void* parameter);

LIB860_INTERNAL void MmsServer_setClientAuthenticator(GspMmsServer self, GspAcseAuthenticator authenticator, void* authenticatorParameter);

LIB860_INTERNAL GspMmsDevice* MmsServer_getDevice(GspMmsServer self);

LIB860_INTERNAL GspMmsValue* MmsServer_getValueFromCache(GspMmsServer self, GspMmsDomain* domain, const char* itemId);

// LIB860_INTERNAL bool MmsServer_isLocked(GspMmsServer self);

LIB860_INTERNAL void MmsServer_lockModel(GspMmsServer self);

LIB860_INTERNAL void MmsServer_unlockModel(GspMmsServer self);

LIB860_INTERNAL void MmsServer_insertIntoCache(GspMmsServer self, GspMmsDomain* domain, char* itemId, GspMmsValue* value);

// LIB860_INTERNAL void MmsServer_startListening(GspMmsServer self, int tcpPort);

// LIB860_INTERNAL void MmsServer_stopListening(GspMmsServer self);

LIB860_INTERNAL void MmsServer_startListeningThreadless(GspMmsServer self, int tcpPort);

LIB860_INTERNAL int MmsServer_waitReady(GspMmsServer self, unsigned int timeoutMs);

LIB860_INTERNAL void MmsServer_handleIncomingMessages(GspMmsServer self);

LIB860_INTERNAL int MmsServer_getConnectionCounter(GspMmsServer self);

LIB860_INTERNAL void MmsServer_stopListeningThreadless(GspMmsServer self);

LIB860_INTERNAL void splitDomainAndItemId(const string &refer, string &domainName, string &itemId);

LIB860_INTERNAL GspMmsDomain *getMmsDomainByRefer(GspMmsServer self, const char *refer);

LIB860_INTERNAL void splitLnNameAndResetReference(const string &itemId, string &lnName, string &resetReference);

LIB860_INTERNAL Data_t *mmsServer_getDataByReference(GspMmsServerConnection self, const string &reference, const string &fc);

LIB860_INTERNAL void mmsServer_getAllDataValues(GspMmsServerConnection self, const string &reference, const string &fc, const string &lastRefer, vector<pair<string, Data_t*> > &dataVec);

LIB860_INTERNAL GspMmsDataAccessError setDataByReference(GspMmsServerConnection self, const string &reference, const string &fc, Data_t *value);

LIB860_INTERNAL GspMmsDataAccessError mmsServer_setValue(GspMmsServer self, GspMmsDomain* domain, char* itemId, GspMmsValue* value, GspMmsServerConnection connection);

#endif /* MMS_SERVER_LIBINTERNAL_H_ */
