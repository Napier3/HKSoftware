/*
 *  mms_server.c
 */

#include "libdlt860_platform_includes.h"
#include "gsp_mms_server.h"
#include "mms_server_connection.h"
#include "mms_value_cache.h"
#include "mms_server_internal.h"
#include "iso_server_private.h"
#include "AssociateNegotiateErrorPDU.h"
#include <vector>
#include "nlogging.h"
#include "mms_mapping.h"

using std::vector;

static CacheMap * createValueCaches(GspMmsDevice* device)
{
    auto valueCaches = new CacheMap();

    if(!device){
        return valueCaches;
    }

    for(auto &item : device->domains)
    {
        valueCaches->insert(std::make_pair(item.second, new ValueHashMap()));
    }

#if (CONFIG_MMS_SUPPORT_VMD_SCOPE_NAMED_VARIABLES == 1)
    MmsValueCache valueCache = MmsValueCache_create((MmsDomain*) device);
    Map_addEntry(valueCaches, (MmsDomain*) device, valueCache);
#endif

    return valueCaches;
}

GspMmsServer MmsServer_create(GspMmsDevice* device, GspTLSConfiguration tlsConfiguration)
{
    GspMmsServer self = (GspMmsServer) GLOBAL_CALLOC(1, sizeof(struct sGspMmsServer));

    self->isoServer = GspIsoServer_create(tlsConfiguration);
    self->device = device;
    self->openConnections = Map_create();
    self->valueCaches = createValueCaches(device);
    self->isLocked = false;
    self->transmitBuffer = GspByteBuffer_create(nullptr, CONFIG_MMS_MAXIMUM_APDU_SIZE);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    self->openConnectionsLock = GspSemaphore_create(1);
    self->modelMutex = GspSemaphore_create(1);
    self->transmitBufferMutex = GspSemaphore_create(1);
    IsoServer_setUserLock(self->isoServer, self->modelMutex);
#endif

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)
    self->fileServiceEnabled = true;
    self->dynamicVariableListServiceEnabled = true;
    self->journalServiceEnabled = true;
    self->maxDataSetEntries = CONFIG_MMS_MAX_NUMBER_OF_DATA_SET_MEMBERS;
    self->maxAssociationSpecificDataSets = CONFIG_MMS_MAX_NUMBER_OF_ASSOCIATION_SPECIFIC_DATA_SETS;
    self->maxDomainSpecificDataSets = CONFIG_MMS_MAX_NUMBER_OF_DOMAIN_SPECIFIC_DATA_SETS;
#endif

    return self;
}

void GspMmsServer_setLocalIpAddress(GspMmsServer self, const char* localIpAddress)
{
    GspIsoServer_setLocalIpAddress(self->isoServer, localIpAddress);
}

bool GspMmsServer_checkState(GspMmsServer self, int state)
{
    return GspIsoServer_getState(self->isoServer) == state;
}

void GspMmsServer_setFilestoreBasepath(GspMmsServer self, const char* basepath)
{
#if (CONFIG_SET_FILESTORE_BASEPATH_AT_RUNTIME == 1)
    if (self->filestoreBasepath != nullptr) {
        GLOBAL_FREEMEM(self->filestoreBasepath);
        self->filestoreBasepath = nullptr;
    }

    if (basepath != nullptr){
        self->filestoreBasepath = StringUtils_copyString(basepath);
    }
#endif
}

void GspMmsServer_setLogStoragePath(GspMmsServer self, const char* basepath)
{
    if (self->logStoragePath != nullptr) {
        GLOBAL_FREEMEM(self->logStoragePath);
        self->logStoragePath = nullptr;
    }

    if (basepath != nullptr){
        self->logStoragePath = StringUtils_copyString(basepath);
    }
}

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)

void GspMmsServer_setMaxConnections(GspMmsServer self, int maxConnections)
{
    GspIsoServer_setMaxConnections(self->isoServer, maxConnections);
}

void GspMmsServer_enableFileService(GspMmsServer self, bool enable)
{
    self->fileServiceEnabled = enable;
}

void GspMmsServer_enableDynamicNamedVariableListService(GspMmsServer self, bool enable)
{
    self->dynamicVariableListServiceEnabled = enable;
}

void GspMmsServer_setMaxDataSetEntries(GspMmsServer self, int maxDataSetEntries)
{
    self->maxDataSetEntries = maxDataSetEntries;
}

void GspMmsServer_enableJournalService(GspMmsServer self, bool enable)
{
    self->journalServiceEnabled = enable;
}

void GspMmsServer_setMaxAssociationSpecificDataSets(GspMmsServer self, int maxDataSets)
{
    self->maxAssociationSpecificDataSets = maxDataSets;
}

void GspMmsServer_setMaxDomainSpecificDataSets(GspMmsServer self, int maxDataSets)
{
    self->maxDomainSpecificDataSets = maxDataSets;
}

#endif

void MmsServer_lockModel(GspMmsServer self)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_wait(self->modelMutex);
#endif
}

void MmsServer_unlockModel(GspMmsServer self)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_post(self->modelMutex);
#endif
}

GspByteBuffer* MmsServer_reserveTransmitBuffer(GspMmsServer self)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_wait(self->transmitBufferMutex);
#endif

    return self->transmitBuffer;
}

void MmsServer_releaseTransmitBuffer(GspMmsServer self)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_post(self->transmitBufferMutex);
#endif
    self->transmitBuffer->size = 0;
}


void MmsServer_installReadHandler(GspMmsServer self, MmsReadVariableHandler readHandler, void* parameter)
{
    self->readHandler = readHandler;
    self->readHandlerParameter = parameter;
}

void MmsServer_installReadAccessHandler(GspMmsServer self, MmsReadAccessHandler readAccessHandler, void* parameter)
{
    self->readAccessHandler = readAccessHandler;
    self->readAccessHandlerParameter = parameter;
}

void MmsServer_installWriteHandler(GspMmsServer self, MmsWriteVariableHandler writeHandler, void* parameter)
{
    self->writeHandler = writeHandler;
    self->writeHandlerParameter = parameter;
}

void MmsServer_installConnectionHandler(GspMmsServer self, MmsConnectionHandler connectionHandler, void* parameter)
{
    self->connectionHandler = connectionHandler;
    self->connectionHandlerParameter = parameter;
}

void GspMmsServer_installVariableListChangedHandler(GspMmsServer self, GspMmsNamedVariableListChangedHandler handler, void* parameter)
{
    self->variableListChangedHandler = handler;
    self->variableListChangedHandlerParameter = parameter;
}

void MmsServer_setClientAuthenticator(GspMmsServer self, GspAcseAuthenticator authenticator, void* authenticatorParameter)
{
    GspIsoServer_setAuthenticator(self->isoServer, authenticator, authenticatorParameter);
}

#if (MMS_FILE_SERVICE == 1)
void GspMmsServer_installFileAccessHandler(GspMmsServer self, GspMmsFileAccessHandler handler, void* parameter)
{
    self->fileAccessHandler = handler;
    self->fileAccessHandlerParameter = parameter;
}
#endif

#if (MMS_OBTAIN_FILE_SERVICE == 1)
void GspMmsServer_installObtainFileHandler(GspMmsServer self, GspMmsObtainFileHandler handler, void* parameter)
{
    self->obtainFileHandler = handler;
    self->obtainFileHandlerParameter = parameter;
}

void GspMmsServer_installGetFileCompleteHandler(GspMmsServer self, GspMmsGetFileCompleteHandler handler, void* parameter)
{
    self->getFileCompleteHandler = handler;
    self->getFileCompleteHandlerParameter = parameter;
}
#endif

static void closeConnection(void* con)
{
    GspMmsServerConnection connection = (GspMmsServerConnection) con;
    GspMmsServerConnection_destroy(connection);
}

void MmsServer_destroy(GspMmsServer self)
{
    if(!self)
    {
        return;
    }
    GspIsoServer_destroy(self->isoServer);
    // for(auto &item : *(self->valueCaches))
    // {
    //     for(auto &m : *(item.second))
    //     {
    //         if(m.second)
    //         {
    //             GspMmsValue_delete(m.second->value);
    //             delete m.second;
    //         }
    //     }
    //     delete item.second;
    // }

    delete self->valueCaches;
    Map_deleteDeep(self->openConnections, false, closeConnection);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_destroy(self->openConnectionsLock);

    GspSemaphore_destroy(self->modelMutex);
    GspSemaphore_destroy(self->transmitBufferMutex);
#endif

    GspByteBuffer_destroy(self->transmitBuffer);

#if (CONFIG_SET_FILESTORE_BASEPATH_AT_RUNTIME == 1)
    if (self->filestoreBasepath != nullptr)
        GLOBAL_FREEMEM(self->filestoreBasepath);
#endif
    if (self->logStoragePath != nullptr)
        GLOBAL_FREEMEM(self->logStoragePath);
    GLOBAL_FREEMEM(self);
}

GspMmsValue* MmsServer_getValueFromCache(GspMmsServer self, GspMmsDomain* domain, const char* itemId)
{
    if(!self || !domain || !itemId){
        return nullptr;
    }

    if(!self->valueCaches){
        return nullptr;
    }

    auto iter = self->valueCaches->find(domain);
    if(iter != self->valueCaches->end()) {
        auto cache = iter->second;
        if(cache){
            return Gsp_MmsValueCache_lookupValue(cache, domain, itemId);
        }
    }
    return nullptr ;
}

void MmsServer_insertIntoCache(GspMmsServer self, GspMmsDomain* domain, char* itemId, GspMmsValue* value)
{
    if(!self || !domain || !itemId || !value){
        return;
    }

    if(!self->valueCaches){
        return;
    }

    auto iter = self->valueCaches->find(domain);
    if(iter != self->valueCaches->end()) {
        auto cache = iter->second;
        if (cache != nullptr) {
            Gsp_MmsValueCache_insertValue(cache, domain, itemId, value);
        }
    }

}

GspMmsDataAccessError mmsServer_setValue(GspMmsServer self,
                                         GspMmsDomain* domain,
                                         char* itemId,
                                         GspMmsValue* value,
                                         GspMmsServerConnection connection)
{
    GspMmsDataAccessError indication;

    if (self->writeHandler != nullptr) {
        indication = self->writeHandler(self->writeHandlerParameter, domain, itemId, value, connection);
    } else {
        GspMmsValue* cachedValue;

        if (domain == nullptr)
            domain = (GspMmsDomain*) self->device;

        cachedValue = MmsServer_getValueFromCache(self, domain, itemId);

        if (cachedValue != nullptr) {
            GspMmsValue_update(cachedValue, value);
            indication = GSP_DATA_ACCESS_ERROR_SUCCESS;
        } else {
            indication = GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
        }
    }

    return indication;
}


GspMmsValue* mmsServer_getValuemmsServer_getValue(GspMmsServer self, GspMmsDomain* domain, char* itemId, GspMmsServerConnection connection)
{
    GspMmsValue* value = nullptr;

    if (self->readAccessHandler != nullptr) {
        GspMmsDataAccessError accessError = self->readAccessHandler(self->readAccessHandlerParameter, (domain == (GspMmsDomain*) self->device) ? nullptr : domain, itemId, connection);

        if (accessError != GSP_DATA_ACCESS_ERROR_SUCCESS) {
            value = GspMmsValue_newDataAccessError(accessError);
            GspMmsValue_setDeletable(value);
            goto exit_function;
        }
    }

    value = MmsServer_getValueFromCache(self, domain, itemId);

    if (value == nullptr)
        if (self->readHandler != nullptr)
            value = self->readHandler(self->readHandlerParameter, (domain == (GspMmsDomain*) self->device) ? nullptr : domain, itemId, connection);

exit_function:
    return value;
}


GspMmsDevice* MmsServer_getDevice(GspMmsServer self)
{
    return self->device;
}

static void isoConnectionIndicationHandler(GspIsoConnectionIndication indication,
                                           void* parameter, GspIsoConnection connection)
{
    GspMmsServer self = (GspMmsServer) parameter;

    if (indication == GSP_ISO_CONNECTION_OPENED) {
        GspMmsServerConnection mmsCon = GspMmsServerConnection_init(nullptr, self, connection);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->openConnectionsLock);
#endif

        Map_addEntry(self->openConnections, connection, mmsCon);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->openConnectionsLock);
#endif

        if (self->connectionHandler != nullptr)
            self->connectionHandler(self->connectionHandlerParameter, mmsCon, GSP_MMS_SERVER_NEW_CONNECTION);
    } else if (indication == GSP_ISO_CONNECTION_CLOSED) {

#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->openConnectionsLock);
#endif

        GspMmsServerConnection mmsCon = (GspMmsServerConnection) Map_removeEntry(self->openConnections, connection, false);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->openConnectionsLock);
#endif

        if (self->connectionHandler != nullptr)
            self->connectionHandler(self->connectionHandlerParameter, mmsCon, GSP_MMS_SERVER_CONNECTION_CLOSED);

        if (mmsCon != nullptr)
            GspMmsServerConnection_destroy(mmsCon);
    }
}

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED != 1)
void MmsServer_startListening(MmsServer server, int tcpPort)
{
    IsoServer_setConnectionHandler(server->isoServer, isoConnectionIndicationHandler, (void*) server);

    if (tcpPort != -1)
        IsoServer_setTcpPort(server->isoServer, tcpPort);

    IsoServer_startListening(server->isoServer);
}

void MmsServer_stopListening(MmsServer server)
{
    IsoServer_stopListening(server->isoServer);
}
#endif

void MmsServer_startListeningThreadless(GspMmsServer self, int tcpPort)
{
    GspIsoServer_setConnectionHandler(self->isoServer, isoConnectionIndicationHandler, (void*) self);

    if (tcpPort != -1)
        GspIsoServer_setTcpPort(self->isoServer, tcpPort);

    GspIsoServer_startListeningThreadless(self->isoServer);
}

int MmsServer_waitReady(GspMmsServer self, unsigned int timeoutMs)
{
    return GspIsoServer_waitReady(self->isoServer, timeoutMs);
}

void MmsServer_handleIncomingMessages(GspMmsServer self)
{
    GspIsoServer_processIncomingMessages(self->isoServer);
}

int MmsServer_getConnectionCounter(GspMmsServer self)
{
    return GspIsoServer_getConnectionCounter(self->isoServer);
}

void MmsServer_callConnectionHandler(GspMmsServer self, GspMmsServerConnection connection)
{
    if (self->connectionHandler) {
        self->connectionHandler(self->connectionHandlerParameter, connection, GSP_MMS_SERVER_CONNECTION_TICK);
    }
}

void MmsServer_stopListeningThreadless(GspMmsServer self)
{
    GspIsoServer_stopListeningThreadless(self->isoServer);
}

int GspServer_encodeStructToBuffer(void *str, void *data, GspByteBuffer *response) {
    response->size += 6;
    asn_enc_rval_t dVal = aper_encode_to_buffer((const struct asn_TYPE_descriptor_s *)str, nullptr, data, response->buffer + 6, response->maxSize - 6);
    if(dVal.encoded > 0) {
        response->size += (dVal.encoded / 8);
        if(dVal.encoded % 8 > 0) {
            response->size += 1;
        }
    } else {
        return dVal.encoded;
    }

    return response->size;
}

GspMmsDataAccessError setDataByReference(GspMmsServerConnection self, const string &reference, const string &fc, Data_t *value)
{
    auto server = self->server;
    string domainName;
    string itemId;
    splitDomainAndItemId(reference, domainName, itemId);
    GspMmsDomain *domain = GspMmsDevice_getDomain(server->device, domainName.c_str());
    // splitLnNameAndResetReference(itemId, lnName, itemId);
    toDollarReference(itemId);
    addFcToReference(itemId, fc, '$');
    return mmsServer_setValue(server, domain, (char *)itemId.c_str(), value, self);
}

void mmsServer_dfsAllValues(GspModelNode *modelNode, const string &fc, const string &lastRefer, vector<string> &subReferVec, bool &beginRecord, vector<pair<string, Data_t *>> &dataVec)
{
    switch (modelNode->modelType) {
    case GspLogicalNodeModelType:
    case GspDataObjectModelType:
    {
        auto child = modelNode->firstChild;
        while(child)
        {
            subReferVec.push_back(child->name);
            mmsServer_dfsAllValues(child, fc, lastRefer, subReferVec, beginRecord, dataVec);
            subReferVec.pop_back();
            child = child->sibling;
        }
    }
        break;
    case GspDataAttributeModelType:
    {
        GspDataAttribute *da = (GspDataAttribute *)modelNode;
        if(!da->firstChild)
        {
            string refer;
            for(const auto &piece : subReferVec) refer += (piece + ".");
            refer.pop_back();
            if(beginRecord)
            {
                char* fcStr = GspFunctionalConstraint_toString(da->fc);
                if(fc.empty() || fc == "XX" || fc == fcStr || da->fc == DLT860_FC_NONE)
                {
                    dataVec.push_back({refer, GspMmsValue_clone(da->mmsValue)});
                }
                if(fcStr){
                    delete [] fcStr;
                }
            }
            else
            {
                if(lastRefer == refer)
                {
                    beginRecord = true;
                }
            }
        }
        else
        {
            auto child = da->firstChild;
            while(child)
            {
                subReferVec.push_back(child->name);
                mmsServer_dfsAllValues(child, fc, lastRefer, subReferVec, beginRecord, dataVec);
                subReferVec.pop_back();
                child = child->sibling;
            }
        }
    }
        break;
    default:
        break;
    }
}

void mmsServer_getAllDataValues(GspMmsServerConnection self, const string &reference, const string &fc, const string &lastRefer, vector<pair<string, Data_t*> > &dataVec)
{
    auto mapping = (GspMmsMapping*) self->server->connectionHandlerParameter;
    string ld;
    string lnName;
    splitDomainAndItemId(reference, ld, lnName);

    auto logiceDevice = mapping->ldMap[ld];
    if(!logiceDevice)
    {
        throw std::runtime_error(fmt::format("没有找到 {} 对应的domain", ld));
    }

    auto ln = logiceDevice->firstChild;
    vector<string> subReferVec;
    bool beginRecord = lastRefer.empty();
    while(ln)
    {
        if(lnName.empty())
        {
            subReferVec.push_back(ln->name);
            mmsServer_dfsAllValues(ln, fc, lastRefer, subReferVec, beginRecord, dataVec);
            subReferVec.pop_back();
        }
        else if(lnName.compare(ln->name) == 0)
        {
            mmsServer_dfsAllValues(ln, fc, lastRefer, subReferVec, beginRecord, dataVec);
            break;
        }
        ln = ln->sibling;
    }
}

Data_t *mmsServer_getDataByReference(GspMmsServerConnection self, const string &reference, const string &fc)
{
    auto mapping = (GspMmsMapping*) self->server->connectionHandlerParameter;
    return mmsMapping_getDataByReference(mapping, reference, fc);
}

void splitLnNameAndResetReference(const string &itemId, string &lnName, string &resetReference)
{
    auto pos = itemId.find(".");
    if(pos == string::npos)
    {
        lnName = itemId;
        resetReference = "";
    }
    else
    {
        lnName = itemId.substr(0, pos);
        resetReference = itemId.substr(pos + 1, itemId.size() - pos - 1);
    }
}

GspMmsDomain *getMmsDomainByRefer(GspMmsServer self, const char *refer)
{
    string domain;
    string itemId;
    splitDomainAndItemId(refer, domain, itemId);
    return GspMmsDevice_getDomain(self->device, domain.c_str());
}


void splitDomainAndItemId(const string &refer, string &domainName, string &itemId)
{
    auto pos = refer.find("/");
    if(pos == string::npos)
    {
        domainName = refer;
    }
    else
    {
        domainName.append(refer.c_str(), 0, pos);
        itemId.append(refer.c_str(), pos + 1, refer.size() - pos - 1);
    }
}

void toDotReference(string &reference)
{
    for(auto &c : reference)
    {
        if(c == '$')
        {
            c = '.';
        }
    }
}

void addFcToReference(string &reference, const string &fc, char delim)
{
    auto pos = reference.find(delim);
    if(pos != string::npos)
    {
        reference.insert(pos + 1, fc + delim);
    }
}

void splitFcFromReference(const string &reference, string &fc, string &referWithoutFc)
{
    auto pos = reference.find_first_of('$');
    fc = reference.substr(pos + 1, 2);
    referWithoutFc = reference;
    referWithoutFc.erase(pos, 3);
}

void splitFcFromReferenceDot(const string &reference, string &fc, string &referWithoutFc)
{
    auto pos = reference.find_first_of('.');
    fc = reference.substr(pos + 1, 2);
    referWithoutFc = reference;
    referWithoutFc.erase(pos, 3);
}

void splitStr(deque<string> &output, const string &input, char delim)
{
    string source = input;
    string tmp;
    size_t pos = 0;
    while((pos = source.find_first_of(delim)) != string::npos)
    {
        tmp = source.substr(0, pos);
        output.push_back(tmp);
        source = source.substr(pos + 1);
    }
    output.push_back(source);
}

void splitStr(vector<string> &output, const string &input, char delim)
{
    string source = input;
    string tmp;
    size_t pos = 0;
    while((pos = source.find_first_of(delim)) != string::npos)
    {
        tmp = source.substr(0, pos);
        output.push_back(tmp);
        source = source.substr(pos + 1);
    }
    output.push_back(source);
}

void toDollarReference(string &reference)
{
    for(auto &c : reference)
    {
        if(c == '.')
        {
            c = '$';
        }
    }
}

GspMmsNamedVariableList mmsServer_getNamedVariableListWithName(GspLinkedList namedVariableLists, const char* variableListName)
{
    for (auto& item : *namedVariableLists)
    {
        auto varList = (GspMmsNamedVariableList)item;
        if (strcmp(MmsNamedVariableList_getName(varList), variableListName) == 0) {
            return varList;
        }
    }
    return nullptr;
}
