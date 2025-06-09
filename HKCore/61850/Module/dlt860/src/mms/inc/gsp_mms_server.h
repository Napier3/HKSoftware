/*
 *  gsp_mms_server.h
 *
 */

#ifndef GSP_MMS_SERVER_H_
#define GSP_MMS_SERVER_H_


#include "gsp_mms_value.h"
#include "gsp_iso_connection_parameters.h"

typedef enum {
    GSP_MMS_SERVER_NEW_CONNECTION,
    GSP_MMS_SERVER_CONNECTION_CLOSED,
    GSP_MMS_SERVER_CONNECTION_TICK
} GspMmsServerEvent;

typedef struct sGspMmsServer* GspMmsServer;
typedef struct sGspMmsServerConnection* GspMmsServerConnection;

typedef enum {
    GSP_MMS_DOMAIN_SPECIFIC,
    GSP_MMS_ASSOCIATION_SPECIFIC,
    GSP_MMS_VMD_SPECIFIC
} GspMmsVariableListType;

LIB860_INTERNAL void GspMmsServer_setLocalIpAddress(GspMmsServer self, const char* localIpAddress);
LIB860_INTERNAL bool GspMmsServer_checkState(GspMmsServer self, int state);

typedef GspMmsError (*GspMmsNamedVariableListChangedHandler)(void* parameter,
                                                             bool create,
                                                             GspMmsVariableListType listType,
                                                             GspMmsDomain* domain,
                                                             char* listName,
                                                             GspMmsServerConnection connection);

LIB860_INTERNAL void GspMmsServer_installVariableListChangedHandler(GspMmsServer self,
                                                                    GspMmsNamedVariableListChangedHandler handler,
                                                                    void* parameter);

typedef bool (*GspMmsObtainFileHandler)(void* parameter,
                                        GspMmsServerConnection connection,
                                        const char* sourceFilename,
                                        const char* destinationFilename);

LIB860_INTERNAL void GspMmsServer_installObtainFileHandler(GspMmsServer self,
                                                           GspMmsObtainFileHandler handler,
                                                           void* parameter);

typedef void (*GspMmsGetFileCompleteHandler)(void* parameter,
                                             GspMmsServerConnection connection,
                                             const char* destinationFilename);

LIB860_INTERNAL void GspMmsServer_installGetFileCompleteHandler(GspMmsServer self,
                                                                GspMmsGetFileCompleteHandler handler,
                                                                void* parameter);


typedef  enum {
    MMS_FILE_ACCESS_TYPE_READ_DIRECTORY,
    MMS_FILE_ACCESS_TYPE_OPEN,
    MMS_FILE_ACCESS_TYPE_OBTAIN,
    MMS_FILE_ACCESS_TYPE_DELETE,
    MMS_FILE_ACCESS_TYPE_RENAME
} GspMmsFileServiceType;

typedef GspMmsError (*GspMmsFileAccessHandler) (void* parameter,
                                                GspMmsServerConnection connection,
                                                GspMmsFileServiceType service,
                                                const char* localFilename,
                                                const char* otherFilename);

LIB860_API void GspMmsServer_installFileAccessHandler(GspMmsServer self,
                                                      GspMmsFileAccessHandler handler,
                                                      void* parameter);

LIB860_INTERNAL void GspMmsServer_setFilestoreBasepath(GspMmsServer self, const char* basepath);
LIB860_INTERNAL void GspMmsServer_setLogStoragePath(GspMmsServer self, const char* basepath);

LIB860_INTERNAL void GspMmsServer_setMaxConnections(GspMmsServer self, int maxConnections);

LIB860_INTERNAL void GspMmsServer_enableFileService(GspMmsServer self, bool enable);

LIB860_INTERNAL void GspMmsServer_enableDynamicNamedVariableListService(GspMmsServer self, bool enable);

LIB860_INTERNAL void GspMmsServer_setMaxAssociationSpecificDataSets(GspMmsServer self, int maxDataSets);

LIB860_INTERNAL void GspMmsServer_setMaxDomainSpecificDataSets(GspMmsServer self, int maxDataSets);

LIB860_INTERNAL void GspMmsServer_setMaxDataSetEntries(GspMmsServer self, int maxDataSetEntries);

LIB860_INTERNAL void GspMmsServer_enableJournalService(GspMmsServer self, bool enable);

/***************************************************
 * Functions for MMS status service
 ***************************************************/

#define GSP_MMS_LOGICAL_STATE_STATE_CHANGES_ALLOWED 0
#define GSP_MMS_LOGICAL_STATE_NO_STATE_CHANGES_ALLOWED 1
#define GSP_MMS_LOGICAL_STATE_LIMITED_SERVICES_PERMITTED 2
#define GSP_MMS_LOGICAL_STATE_SUPPORT_SERVICES_ALLOWED 3

#define GSP_MMS_PHYSICAL_STATE_OPERATIONAL 0
#define GSP_MMS_PHYSICAL_STATE_PARTIALLY_OPERATIONAL 1
#define GSP_MMS_PHYSICAL_STATE_INOPERATIONAL 2
#define GSP_MMS_PHYSICAL_STATE_NEEDS_COMMISSIONING 3

typedef void (*GSP_MmsStatusRequestListener)(void* parameter,
                                             GspMmsServer mmsServer,
                                             GspMmsServerConnection connection,
                                             bool extendedDerivation);

//LIB860_INTERNAL void GspMmsServer_setVMDStatus(GspMmsServer self, int vmdLogicalStatus, int vmdPhysicalStatus);

//LIB860_INTERNAL int GspMmsServer_getVMDLogicalStatus(GspMmsServer self);

//LIB860_INTERNAL int GspMmsServer_getVMDPhysicalStatus(GspMmsServer self);

//LIB860_INTERNAL void GspMmsServer_setStatusRequestListener(GspMmsServer self, GSP_MmsStatusRequestListener listener, void* parameter);

LIB860_INTERNAL char* GspMmsServerConnection_getClientAddress(GspMmsServerConnection self);

LIB860_INTERNAL char* GspMmsServerConnection_getLocalAddress(GspMmsServerConnection self);

LIB860_INTERNAL void* GspMmsServerConnection_getSecurityToken(GspMmsServerConnection self);


#endif /* GSP_MMS_SERVER_H_ */
