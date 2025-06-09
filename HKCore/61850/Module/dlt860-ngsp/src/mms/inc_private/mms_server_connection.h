/*
 *  mms_server_connection.h
 */

#ifndef GSP_MMS_SERVER_CONNECTION_H_
#define GSP_MMS_SERVER_CONNECTION_H_

#include "libdlt860_platform_includes.h"
#include "gsp_mms_common.h"
#include "mms_device_model.h"
#include "gsp_mms_value.h"
#include "gsp_mms_server.h"
#include "iso_server.h"
#include "gsp_linked_list.h"
#include "byte_buffer.h"

LIB860_INTERNAL GspMmsServerConnection GspMmsServerConnection_init(GspMmsServerConnection connection, GspMmsServer server, GspIsoConnection isoCon);

LIB860_INTERNAL void GspMmsServerConnection_destroy(GspMmsServerConnection connection);

LIB860_INTERNAL int GspMmsServerConnection_getMaxMmsPduSize(GspMmsServerConnection self);

LIB860_INTERNAL bool GspMmsServerConnection_addNamedVariableList(GspMmsServerConnection self, GspMmsNamedVariableList variableList);

LIB860_INTERNAL GspMmsNamedVariableList GspMmsServerConnection_getNamedVariableList(GspMmsServerConnection self, const char* variableListName);

LIB860_INTERNAL GspLinkedList GspMmsServerConnection_getNamedVariableLists(GspMmsServerConnection self);

LIB860_INTERNAL void GspMmsServerConnection_deleteNamedVariableList(GspMmsServerConnection self, char* listName);

LIB860_INTERNAL void GspMmsServerConnection_sendInformationReportSingleVariableVMDSpecific(GspMmsServerConnection self,
                                                                                           char* itemId,
                                                                                           GspMmsValue* value,
                                                                                           bool handlerMode);

LIB860_INTERNAL void GspMmsServerConnection_sendInformationReportVMDSpecific(GspMmsServerConnection self,
                                                                             char* itemId,
                                                                             GspLinkedList values,
                                                                             bool handlerMode);


LIB860_INTERNAL void GspMmsServerConnection_sendInformationReportListOfVariables(
        GspMmsServerConnection self,
        GspLinkedList variableAccessDeclarations,
        GspLinkedList values,
        bool handlerMode
        );

LIB860_INTERNAL void GspMmsServerConnection_sendWriteResponse(GspMmsServerConnection self,
                                                              uint32_t invokeId,
                                                              GspMmsDataAccessError indication,
                                                              bool handlerMode);

LIB860_INTERNAL uint32_t GspMmsServerConnection_getLastInvokeId(GspMmsServerConnection self);

LIB860_INTERNAL uint32_t GspMmsServerConnection_getNextRequestInvokeId(GspMmsServerConnection self);

LIB860_INTERNAL const char* GspMmsServerConnection_getFilesystemBasepath(GspMmsServerConnection self);

LIB860_INTERNAL uint16_t GspMmsServerConnection_getApduSize(GspMmsServerConnection self);

LIB860_INTERNAL void GspMmsServerConnection_setApduSize(GspMmsServerConnection self, uint16_t apduSize);

LIB860_INTERNAL uint32_t GspMmsServerConnection_getAsduSize(GspMmsServerConnection self);

LIB860_INTERNAL void GspMmsServerConnection_setAsduSize(GspMmsServerConnection self, uint32_t asduSize);
LIB860_INTERNAL uint64_t GspMmsServerConnection_getConnectID(GspMmsServerConnection self);

#endif /* MMS_SERVER_CONNECTION_H_ */


