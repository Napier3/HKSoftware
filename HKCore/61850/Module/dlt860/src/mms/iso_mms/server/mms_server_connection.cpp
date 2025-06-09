/*
 *  mms_server_connection.c
 */

#include "libdlt860_platform_includes.h"
#include "mms_server_internal.h"
#include "iso_server.h"
#include "mms_service_table.h"
/**********************************************************************************************
 * MMS Common support functions
 *********************************************************************************************/

#define MMS_REJECT_CONFIRMED_REQUEST 1
#define MMS_REJECT_CONFIRMED_RESPONSE 2
#define MMS_REJECT_CONFIRMED_ERROR 3
#define MMS_REJECT_UNCONFIRMED 4
#define MMS_REJECT_PDU_ERROR 5
#define MMS_REJECT_CANCEL_REQUEST 6
#define MMS_REJECT_CANCEL_RESPONSE 7
#define MMS_REJECT_CANCEL_ERROR 8
#define MMS_REJECT_CONCLUDE_REQUEST 9
#define MMS_REJECT_CONCLUDE_RESPONSE 10
#define MMS_REJECT_CONCLUDE_ERROR 11

#define MMS_REJECT_CONFIRMED_REQUEST_OTHER 0
#define MMS_REJECT_CONFIRMED_REQUEST_UNRECOGNIZED_SERVICE 1
#define MMS_REJECT_CONFIRMED_REQUEST_UNRECOGNIZED_MODIFIER 2
#define MMS_REJECT_CONFIRMED_REQUEST_INVALID_INVOKE_ID 3
#define MMS_REJECT_CONFIRMED_REQUEST_INVALID_ARGUMENT 4
#define MMS_REJECT_CONFIRMED_REQUEST_INVALID_MODIFIER 5
#define MMS_REJECT_CONFIRMED_REQUEST_MAX_SERV_OUTSTANDING_EXCEEDED 6
#define MMS_REJECT_CONFIRMED_REQUEST_MAX_RECURSION_EXCEEDED 8
#define MMS_REJECT_CONFIRMED_REQUEST_VALUE_OUT_OF_RANGE 9

#define MMS_REJECT_PDU_ERROR_UNKNOWN_PDU_TYPE 0
#define MMS_REJECT_PDU_ERROR_INVALID_PDU 1
#define MMS_REJECT_PDU_ERROR_ILLEGAL_ACSI_MAPPING 2






static inline int handleGspMmsError(GspMmsServerConnection self, GspByteBuffer* message, GspByteBuffer* response) {
    return -1;
}

static inline int handleGspMmsResponse(GspMmsServerConnection self, GspByteBuffer* message, GspByteBuffer* response) {
    return -1;
}

static inline int
handleGspMmsRequest(GspMmsServerConnection self, GspByteBuffer* message, GspByteBuffer* response) {
    uint8_t sc = GspIsoConnection_getGspSc(self->isoConnection);
    callServiceFunc(sc, self, message, response);
    return 0;
}

static inline void MmsServerConnection_parse860Message(GspMmsServerConnection self, GspByteBuffer* message, GspByteBuffer* response)
{
    // for request
    int error = GspIsoConnection_getGspError(self->isoConnection);
    int resp = GspIsoConnection_getGspResp(self->isoConnection);

    if(error == 1) {
        // for error
        handleGspMmsError(self, message, response);
    } else if(resp == 1) {
        // for response
        handleGspMmsResponse(self, message, response);
    } else {
        // for request
        handleGspMmsRequest(self, message, response);
    }


}

/**
 * @brief gspMmsMessageReceived
 * for gsp mms(pi = 1)
 * @param parameter
 * @param message
 * @param response
 */
static void gspMmsMessageReceived(void* parameter, GspByteBuffer* message, GspByteBuffer* response)
{
    GspMmsServerConnection self = (GspMmsServerConnection) parameter;
    MmsServerConnection_parse860Message(self, message, response);
}

/**
 * @brief gspMessageReceived
 * for gsp mms(pi = 0)
 * @param parameter
 * @param message
 * @param response
 */
static void gspMessageReceived(void* parameter, GspByteBuffer* message, GspByteBuffer* response)
{
    // TODO kevin
    // 此处用于处理gsp协议，暂时不进行实现。
    GspMmsServerConnection self = (GspMmsServerConnection) parameter;
    uint8_t sc = GspIsoConnection_getGspSc(self->isoConnection);
    switch (sc) {
    case GSP_SC_Associate:
        break;
    default:
        break;
    }
}

static void connectionTickHandler(void* parameter)
{
    GspMmsServerConnection self = (GspMmsServerConnection) parameter;
    MmsServer_callConnectionHandler(self->server, self);
}

/**********************************************************************************************
 * MMS server connection public API functions
 *********************************************************************************************/

GspMmsServerConnection GspMmsServerConnection_init(GspMmsServerConnection connection, GspMmsServer server, GspIsoConnection isoCon)
{
    GspMmsServerConnection self;

    if (connection == nullptr){
        self = (GspMmsServerConnection) GLOBAL_CALLOC(1, sizeof(struct sGspMmsServerConnection));
    } else {
        self = connection;
    }
    self->maxServOutstandingCalled = 0;
    self->maxServOutstandingCalling = 0;
    self->maxPduSize = CONFIG_MMS_MAXIMUM_APDU_SIZE;
    self->dataStructureNestingLevel = 0;
    self->server = server;
    self->isoConnection = isoCon;

#if (MMS_DYNAMIC_DATA_SETS == 1)
    self->namedVariableLists = GspLinkedList_create();
#endif

#if (MMS_OBTAIN_FILE_SERVICE == 1)
    self->lastRequestInvokeId = 0;
#endif

    // TODO add gsp and mms handler
    GspIsoConnection_installGspListener(isoCon,
                                     gspMmsMessageReceived,
                                     gspMessageReceived,
            (GspUserLayerTickHandler) connectionTickHandler,
            (void*) self);

    return self;
}

void
GspMmsServerConnection_destroy(GspMmsServerConnection self)
{



#if (MMS_DYNAMIC_DATA_SETS == 1)
    GspLinkedList_destroyDeep(self->namedVariableLists, (GspLinkedListValueDeleteFunction) MmsNamedVariableList_destroy);
#endif

    GLOBAL_FREEMEM(self);
}

int
GspMmsServerConnection_getMaxMmsPduSize(GspMmsServerConnection self)
{
    return self->maxPduSize;
}

#if (MMS_DYNAMIC_DATA_SETS == 1)
bool
GspMmsServerConnection_addNamedVariableList(GspMmsServerConnection self, GspMmsNamedVariableList variableList)
{
    /* TODO check if operation is allowed! */

    GspLinkedList_add(self->namedVariableLists, variableList);

    return true;
}

void
GspMmsServerConnection_deleteNamedVariableList(GspMmsServerConnection self, char* listName)
{
//    gspmmsServer_deleteVariableList(self->namedVariableLists, listName);
}

GspMmsNamedVariableList
GspMmsServerConnection_getNamedVariableList(GspMmsServerConnection self, const char* variableListName)
{
    return mmsServer_getNamedVariableListWithName(self->namedVariableLists, variableListName);
}
#endif /* (MMS_DYNAMIC_DATA_SETS == 1) */

char*
GspMmsServerConnection_getClientAddress(GspMmsServerConnection self)
{
    return GspIsoConnection_getPeerAddress(self->isoConnection);
}

char*
GspMmsServerConnection_getLocalAddress(GspMmsServerConnection self)
{
    return GspIsoConnection_getLocalAddress(self->isoConnection);
}

void*
GspMmsServerConnection_getSecurityToken(GspMmsServerConnection self)
{
    return GspIsoConnection_getSecurityToken(self->isoConnection);
}

#if (MMS_DYNAMIC_DATA_SETS == 1)
GspLinkedList
GspMmsServerConnection_getNamedVariableLists(GspMmsServerConnection self)
{
    return self->namedVariableLists;
}
#endif /* (MMS_DYNAMIC_DATA_SETS == 1) */

uint32_t
GspMmsServerConnection_getLastInvokeId(GspMmsServerConnection self)
{
    //return self->isoConnectiolastInvokeId;
    //TODO
    return 0;
}

#if (MMS_OBTAIN_FILE_SERVICE == 1)
uint32_t
GspMmsServerConnection_getNextRequestInvokeId(GspMmsServerConnection self)
{
    self->lastRequestInvokeId++;
    return self->lastRequestInvokeId;
}
#endif /* (MMS_OBTAIN_FILE_SERVICE == 1) */

const char*
GspMmsServerConnection_getFilesystemBasepath(GspMmsServerConnection self)
{
#if (CONFIG_SET_FILESTORE_BASEPATH_AT_RUNTIME == 1)
    if (self->server->filestoreBasepath != NULL)
        return self->server->filestoreBasepath;
    else
        return CONFIG_VIRTUAL_FILESTORE_BASEPATH;
#else
    return CONFIG_VIRTUAL_FILESTORE_BASEPATH;
#endif
}

uint16_t
GspMmsServerConnection_getApduSize(GspMmsServerConnection self) {
    return self->apduSize;
}

void
GspMmsServerConnection_setApduSize(GspMmsServerConnection self, uint16_t apduSize) {
    self->apduSize = apduSize;
}

uint32_t
GspMmsServerConnection_getAsduSize(GspMmsServerConnection self) {
    return self->asduSize;
}

void
GspMmsServerConnection_setAsduSize(GspMmsServerConnection self, uint32_t asduSize) {
    self->asduSize = asduSize;
}

uint64_t
GspMmsServerConnection_getConnectID(GspMmsServerConnection self)
{
    return GspIsoConnection_getConnectID(self->isoConnection);
}


