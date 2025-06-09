/*
 *  ied_server.c
 */

#include "dlt860_server.h"
#include "gsp_mms_value.h"
#include "mms_mapping.h"
#include "mms_mapping_internal.h"
#include "mms_server_libinternal.h"
#include "mms_server_internal.h"
#include "control.h"
#include "stack_config.h"
#include "ied_server_private.h"
#include "gsp_hal_thread.h"
#include "reporting.h"
#include "libdlt860_platform_includes.h"
#include "mms_sv.h"
#include "sgstorage.h"
#include <json.hpp>
#include <fstream>
#include <exception>
#include "modelgenerator.h"
#include "dlt860_common.h"
#include "nlogging.h"
#include "Data.h"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <deque>
#include "mms_server_func.h"

using namespace std;
using json = nlohmann::json;
using namespace GSP;

#ifndef DEBUG_IED_SERVER
#define DEBUG_IED_SERVER 0
#endif

#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
static bool createControlObjects(GspIedServer self, GspMmsDomain *domain, char *lnName, GspMmsVariableSpecification *typeSpec, char *namePrefix)
{
    GspMmsMapping *mapping = self->mmsMapping;

    bool success = false;

    if (typeSpec->type == GSP_MMS_STRUCTURE)
    {
        int coCount = typeSpec->typeSpec.structure.elementCount;
        int i;
        for (i = 0; i < coCount; i++)
        {

            char objectName[65];
            objectName[0] = 0;

            if (namePrefix != nullptr)
            {
                strcat(objectName, namePrefix);
                strcat(objectName, "$");
            }

            bool hasCancel = false;
            int cancelIndex = 0;
            bool hasSBOw = false;
            bool hasSBO = false;
            int sBOwIndex = 0;
            int operIndex = 0;
            int sBOIndex = 0;

            GspMmsVariableSpecification *coSpec = typeSpec->typeSpec.structure.elements[i];

            if (coSpec->type == GSP_MMS_STRUCTURE)
            {

                int coElementCount = coSpec->typeSpec.structure.elementCount;

                GspMmsVariableSpecification *operSpec = nullptr;

                int j;
                for (j = 0; j < coElementCount; j++)
                {
                    GspMmsVariableSpecification *coElementSpec = coSpec->typeSpec.structure.elements[j];

                    if (strcmp(coElementSpec->name, "Oper") == 0)
                    {
                        operSpec = coElementSpec;
                        operIndex = j;
                    }
                    else if (strcmp(coElementSpec->name, "Cancel") == 0)
                    {
                        hasCancel = true;
                        cancelIndex = j;
                    }
                    else if (strcmp(coElementSpec->name, "SBOw") == 0)
                    {
                        hasSBOw = true;
                        sBOwIndex = j;
                    }
                    else if ((strcmp(coElementSpec->name, "SBO") == 0))
                    {
                        hasSBO = true;
                        sBOIndex = j;
                    }
                    else
                    {
                        if (DEBUG_IED_SERVER)
                            printf("IED_SERVER: createControlObjects: Unknown element in CO: %s\n", coElementSpec->name);

                        break;
                    }
                }

                if (operSpec)
                {

                    strcat(objectName, coSpec->name);

                    if (DEBUG_IED_SERVER)
                        printf("IED_SERVER: create control object LN:%s DO:%s\n", lnName, objectName);

                    GspControlObject *controlObject = GspControlObject_create(self, domain, lnName, objectName, operSpec);

                    if (controlObject == nullptr)
                        goto exit_function;

                    GspMmsValue *structure = GspMmsValue_newDefaultValue(coSpec);

                    if (structure == nullptr)
                    {
                        GspControlObject_destroy(controlObject);
                        goto exit_function;
                    }

                    GspControlObject_setMmsValue(controlObject, structure);

                    GspControlObject_setTypeSpec(controlObject, coSpec);

                    controlObject->oper = GspMmsValue_getElement(structure, operIndex);

                    if (hasCancel)
                        controlObject->cancel = GspMmsValue_getElement(structure, cancelIndex);

                    if (hasSBOw)
                        controlObject->sbow = GspMmsValue_getElement(structure, sBOwIndex);

                    if (hasSBO)
                        controlObject->sbo = GspMmsValue_getElement(structure, sBOIndex);

                    GspMmsMapping_addControlObject(mapping, controlObject);
                }
                else
                {
                    strcat(objectName, coSpec->name);

                    if (createControlObjects(self, domain, lnName, coSpec, objectName) == false)
                        goto exit_function;
                }
            }
        }
    }

    success = true;

exit_function:
    return success;
}
#endif /* (CONFIG_DLT860_CONTROL_SERVICE == 1) */

static GspModelNode *getDaNodeByReference(void *server, const char *daRefer, const char *fc)
{
    auto self = (GspIedServer)server;
    auto it = self->referNodeCache.find(fmt::format("{}.{}", daRefer, fc));
    if (it != self->referNodeCache.end())
    {
        return it->second;
    }

    string domainName;
    string itemId;
    splitDomainAndItemId(daRefer, domainName, itemId);
    auto model = GspMmsMapping_getIedModelByDomainName(self->mmsMapping, domainName);
    if (!model)
    {
        return nullptr;
    }
    auto ret = GspIedModel_getModelNodeByReference(model, daRefer, fc);
    self->referNodeCache.insert({fmt::format("{}.{}", daRefer, fc), ret});
    return ret;
}

static bool createMmsServerCache(GspIedServer self)
{
    self->cacheValueList = GspLinkedList_create();
    assert(self != NULL);

    bool success = false;

    int domain = 0;
    for (auto &item : self->mmsDevice->domains)
    {
        /* Install all top level MMS named variables (=Logical nodes) in the MMS server cache */
        GspMmsDomain *logicalDevice = item.second;

        int i;

        for (i = 0; i < logicalDevice->namedVariablesCount; i++)
        {
            char *lnName = logicalDevice->namedVariables[i]->name;

            if (DEBUG_IED_SERVER)
                printf("IED_SERVER: Insert into cache %s - %s\n", logicalDevice->domainName, lnName);

            int fcCount = logicalDevice->namedVariables[i]->typeSpec.structure.elementCount;
            int j;

            for (j = 0; j < fcCount; j++)
            {
                GspMmsVariableSpecification *fcSpec = logicalDevice->namedVariables[i]->typeSpec.structure.elements[j];

                char *fcName = fcSpec->name;

#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
                if (strcmp(fcName, "CO") == 0)
                {
                    continue;
                    //createControlObjects(self, logicalDevice, lnName, fcSpec, NULL);
                }
                else
#endif /* (CONFIG_DLT860_CONTROL_SERVICE == 1) */

                    if ((strcmp(fcName, "BR") != 0) && (strcmp(fcName, "RP") != 0)

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
                        && (strcmp(fcName, "GO") != 0)
#endif

#if (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1)
                        && (strcmp(fcName, "MS") != 0) && (strcmp(fcName, "US") != 0)
#endif

#if (CONFIG_DLT860_LOG_SERVICE == 1)
                        && (strcmp(fcName, "LG") != 0)
#endif

                    )
                {
                    char variableName[65];

                    StringUtils_createStringInBuffer(variableName, 3, lnName, "$", fcName);

                    GspMmsValue *defaultValue = GspMmsValue_newDefaultValue(fcSpec);

                    if (defaultValue == nullptr)
                        goto exit_function;

                    if (DEBUG_IED_SERVER)
                        printf("ied_server.c: Insert into cache %s - %s\n", logicalDevice->domainName, variableName);

                    self->cacheValueList->push_back(defaultValue);
                    MmsServer_insertIntoCache(self->mmsServer, logicalDevice, variableName, defaultValue);
                }
            }
        }
    }

    success = true;

exit_function:
    return success;
}

static void installDefaultValuesForDataAttribute(GspIedServer self, GspDataAttribute *dataAttribute, char *objectReference, int position, GspIedModel *model)
{
    sprintf(objectReference + position, ".%s", dataAttribute->name);

    char mmsVariableName[65]; /* maximum size is 64 according to 61850-8-1 */

    GspMmsValue *value = dataAttribute->mmsValue;

    GspMmsMapping_createMmsVariableNameFromObjectReference(objectReference, dataAttribute->fc, mmsVariableName);

    char domainName[65];

    strncpy(domainName, model->name, 64);

    GspMmsMapping_getMmsDomainFromObjectReference(objectReference, domainName + strlen(domainName));

    GspMmsDomain *domain = GspMmsDevice_getDomain(self->mmsDevice, domainName);

    if (domain == nullptr)
    {
        if (DEBUG_IED_SERVER)
            printf("Error domain (%s) not found for %s!\n", domainName, objectReference);
        return;
    }

    GspMmsValue *cacheValue = MmsServer_getValueFromCache(self->mmsServer, domain, mmsVariableName);
    dataAttribute->mmsValue = cacheValue;

    if (value != nullptr)
    {

        if (cacheValue != nullptr)
            GspMmsValue_update(cacheValue, value);

#if (DEBUG_IED_SERVER == 1)
        if (cacheValue == NULL)
        {
            printf("IED_SERVER: exception: invalid initializer for %s\n", mmsVariableName);
        }
#endif

        GspMmsValue_delete(value);
    }

    int childPosition = strlen(objectReference);
    GspDataAttribute *subDataAttribute = (GspDataAttribute *)dataAttribute->firstChild;
    while (subDataAttribute != nullptr)
    {
        installDefaultValuesForDataAttribute(self, subDataAttribute, objectReference, childPosition, model);

        subDataAttribute = (GspDataAttribute *)subDataAttribute->sibling;
    }
}

static void installDefaultValuesForDataObject(GspIedServer self, GspDataObject *dataObject,
                                              char *objectReference, int position, GspIedModel *model)
{
    if (dataObject->elementCount > 0)
    {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: DataObject is an array. Skip installing default values in cache\n");

        return;
    }

    sprintf(objectReference + position, ".%s", dataObject->name);

    GspModelNode *childNode = dataObject->firstChild;

    int childPosition = strlen(objectReference);

    while (childNode != nullptr)
    {
        if (childNode->modelType == GspDataObjectModelType)
        {
            installDefaultValuesForDataObject(self, (GspDataObject *)childNode, objectReference, childPosition, model);
        }
        else if (childNode->modelType == GspDataAttributeModelType)
        {
            installDefaultValuesForDataAttribute(self, (GspDataAttribute *)childNode, objectReference, childPosition, model);
        }

        childNode = childNode->sibling;
    }
}

static void installDefaultValuesInCache(GspIedServer self)
{
    GspIedModel **pModel = self->modelss;
    GspIedModel *model = pModel[0];
    deque<GspIedModel *> modelQueue;

    while (model)
    {
        modelQueue.push_back(model);
        pModel += 1;
        model = *pModel;
    }

    std::mutex queueLock;

    vector<thread> threadVec;
    auto func = [&]()
    {
        while (true)
        {
            queueLock.lock();
            if (modelQueue.empty())
            {
                queueLock.unlock();
                break;
            }
            auto model = modelQueue.front();
            modelQueue.pop_front();
            queueLock.unlock();

            char objectReference[130];

            GspLogicalDevice *logicalDevice = model->firstChild;

            while (logicalDevice != nullptr)
            {
                sprintf(objectReference, "%s", logicalDevice->name);

                GspLogicalNode *logicalNode = (GspLogicalNode *)logicalDevice->firstChild;

                char *nodeReference = objectReference + strlen(objectReference);

                while (logicalNode != nullptr)
                {
                    sprintf(nodeReference, "/%s", logicalNode->name);

                    GspDataObject *dataObject = (GspDataObject *)logicalNode->firstChild;

                    int refPosition = strlen(objectReference);

                    while (dataObject != nullptr)
                    {
                        installDefaultValuesForDataObject(self, dataObject, objectReference, refPosition, model);

                        dataObject = (GspDataObject *)dataObject->sibling;
                    }

                    logicalNode = (GspLogicalNode *)logicalNode->sibling;
                }

                logicalDevice = (GspLogicalDevice *)logicalDevice->sibling;
            }
        }
    };
    for (auto i = 0; i < 7; ++i)
    {
        threadVec.push_back(thread(func));
    }

    func();

    for (auto &t : threadVec)
    {
        t.join();
    }
}

static void createDataSetCache(GspIedServer self)
{
    GspIedModel **pModel = self->modelss;
    GspIedModel *model = *pModel;
    while (model)
    {
        GspDataSet *dataSet = model->dataSets;
        while (dataSet != nullptr)
        {
            self->dataSetCache[dataSet->refer] = dataSet;
            dataSet = dataSet->sibling;
        }
        pModel += 1;
        model = *pModel;
    }
}

static void updateDataSetsWithCachedValues(GspIedServer self)
{
    GspIedModel **pModel = self->modelss;
    GspIedModel *model = *pModel;
    while (model)
    {

        GspDataSet *dataSet = model->dataSets;

        int iedNameLength = strlen(model->name);

        if (iedNameLength <= 64)
        {

            while (dataSet != nullptr)
            {

                GspDataSetEntry *dataSetEntry = dataSet->fcdas;

                while (dataSetEntry != nullptr)
                {

                    char domainName[65];

                    strncpy(domainName, model->name, 64);
                    strncat(domainName, dataSetEntry->logicalDeviceName, 64 - iedNameLength);

                    GspMmsDomain *domain = GspMmsDevice_getDomain(self->mmsDevice, domainName);

                    GspMmsValue *value = MmsServer_getValueFromCache(self->mmsServer, domain, dataSetEntry->variableName);

                    if (value == nullptr)
                    {

                        NLOG_WARN("LD: {} dataset: {} : error cannot get value from cache for {} -> {}!\n",
                                  dataSet->logicalDeviceName, dataSet->name,
                                  dataSetEntry->logicalDeviceName,
                                  dataSetEntry->variableName);
                    }
                    else
                    {
                        dataSetEntry->value = value;
                    }

                    dataSetEntry = dataSetEntry->sibling;
                }

                dataSet = dataSet->sibling;
            }
        }
        pModel += 1;
        model = *pModel;
    }
}

GspIedServer GspIedServer_createWithConfigMulti(GspIedModel **dataModel, GspTLSConfiguration tlsConfiguration, GspIedServerConfig serverConfiguration)
{
    GspIedServer self = new sGspIedServer();

    if (self)
    {
        self->modelss = dataModel;
        self->running = false;
        self->localIpAddress = nullptr;
        self->serverConfig = serverConfiguration;
#if (CONFIG_IEC61850_EDITION_1 == 1)
        self->edition = DLT_860_EDITION_1;
#else
        self->edition = DLT_860_EDITION_2;
#endif

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)
        self->logServiceEnabled = true;

        if (serverConfiguration)
        {
            self->logServiceEnabled = serverConfiguration->enableLogService;
            self->edition = serverConfiguration->edition;
        }

#endif /* (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1) */

#if (CONFIG_MMS_THREADLESS_STACK != 1)
        self->dataModelLock = GspSemaphore_create(1);
        self->clientConnectionsLock = GspSemaphore_create(1);
#endif /* (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1) */
#if (CONFIG_DLT860_REPORT_SERVICE == 1)
        if (serverConfiguration)
        {
            self->reportBufferSizeBRCBs = serverConfiguration->reportBufferSize;
            self->reportBufferSizeURCBs = serverConfiguration->reportBufferSizeURCBs;
        }
        else
        {
            self->reportBufferSizeBRCBs = CONFIG_REPORTING_DEFAULT_REPORT_BUFFER_SIZE;
            self->reportBufferSizeURCBs = CONFIG_REPORTING_DEFAULT_REPORT_BUFFER_SIZE;
        }
#endif

        //self->mmsMapping = MmsMapping_create(dataModel, self);
        self->mmsMapping = GspMmsMapping_createMulti(dataModel, self);

        self->mmsDevice = GspMmsMapping_getMmsDeviceModel(self->mmsMapping);

        self->mmsServer = MmsServer_create(self->mmsDevice, tlsConfiguration);

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)
        //        if (serverConfiguration) {
        //            GspMmsServer_enableFileService(self->mmsServer, serverConfiguration->enableFileService);
        //            GspMmsServer_enableDynamicNamedVariableListService(self->mmsServer, serverConfiguration->enableDynamicDataSetService);
        //            GspMmsServer_setMaxAssociationSpecificDataSets(self->mmsServer, serverConfiguration->maxAssociationSpecificDataSets);
        //            GspMmsServer_setMaxDomainSpecificDataSets(self->mmsServer, serverConfiguration->maxDomainSpecificDataSets);
        //            GspMmsServer_setMaxDataSetEntries(self->mmsServer, serverConfiguration->maxDataSetEntries);
        //            GspMmsServer_enableJournalService(self->mmsServer, serverConfiguration->enableLogService);
        //            GspMmsServer_setFilestoreBasepath(self->mmsServer, serverConfiguration->fileServiceBasepath);
        //            GspMmsServer_setMaxConnections(self->mmsServer, serverConfiguration->maxMmsConnections);
        //        }
#endif

        GspMmsMapping_setMmsServer(self->mmsMapping, self->mmsServer);

        GspMmsMapping_installHandlers(self->mmsMapping);
        createMmsServerCache(self);

        // init all models
        GspIedModel **tmpModel = dataModel;
        GspIedModel *currentModel = *tmpModel;
        while (currentModel)
        {
            currentModel->initializer();
            currentModel->installCacheValue = true;
            tmpModel += 1;
            currentModel = *tmpModel;
        }

        installDefaultValuesInCache(self); /* This will also connect cached MmsValues to DataAttributes */
        updateDataSetsWithCachedValues(self);
        createDataSetCache(self);
        self->clientConnections = GspLinkedList_create();

        /* default write access policy allows access to SP, SE and SV FCDAs but denies access to DC and CF FCDAs */
        self->writeAccessPolicies = ALLOW_WRITE_ACCESS_SP | ALLOW_WRITE_ACCESS_SV | ALLOW_WRITE_ACCESS_SE;
#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
        GspMmsMapping_initializeControlObjects(self->mmsMapping);
#endif

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
        GspReporting_activateBufferedReports(self->mmsMapping);
#endif

#if (CONFIG_DLT860_SETTING_GROUPS == 1)
        GspMmsMapping_configureSettingGroups(self->mmsMapping);
#endif
    }
    return self;
}

GspIedServer GspIedServer_createWithConfig(GspIedModel *dataModel, GspTLSConfiguration tlsConfiguration, GspIedServerConfig serverConfiguration)
{
    GspIedServer self = (GspIedServer)GLOBAL_CALLOC(1, sizeof(struct sGspIedServer));

    if (self)
    {

        //self->models = dataModel;

        self->running = false;
        self->localIpAddress = nullptr;

#if (CONFIG_IEC61850_EDITION_1 == 1)
        self->edition = DLT_860_EDITION_1;
#else
        self->edition = DLT_860_EDITION_2;
#endif

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)
        self->logServiceEnabled = true;

        if (serverConfiguration)
        {
            self->logServiceEnabled = serverConfiguration->enableLogService;
            self->edition = serverConfiguration->edition;
        }

#endif /* (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1) */

#if (CONFIG_MMS_THREADLESS_STACK != 1)
        self->dataModelLock = GspSemaphore_create(1);
        self->clientConnectionsLock = GspSemaphore_create(1);
#endif /* (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1) */

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
        if (serverConfiguration)
        {
            self->reportBufferSizeBRCBs = serverConfiguration->reportBufferSize;
            self->reportBufferSizeURCBs = serverConfiguration->reportBufferSizeURCBs;
        }
        else
        {
            self->reportBufferSizeBRCBs = CONFIG_REPORTING_DEFAULT_REPORT_BUFFER_SIZE;
            self->reportBufferSizeURCBs = CONFIG_REPORTING_DEFAULT_REPORT_BUFFER_SIZE;
        }
#endif

        self->mmsMapping = GspMmsMapping_create(dataModel, self);

        self->mmsDevice = GspMmsMapping_getMmsDeviceModel(self->mmsMapping);

        self->mmsServer = MmsServer_create(self->mmsDevice, tlsConfiguration);

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)
        if (serverConfiguration)
        {
            GspMmsServer_enableFileService(self->mmsServer, serverConfiguration->enableFileService);
            GspMmsServer_enableDynamicNamedVariableListService(self->mmsServer, serverConfiguration->enableDynamicDataSetService);
            GspMmsServer_setMaxAssociationSpecificDataSets(self->mmsServer, serverConfiguration->maxAssociationSpecificDataSets);
            GspMmsServer_setMaxDomainSpecificDataSets(self->mmsServer, serverConfiguration->maxDomainSpecificDataSets);
            GspMmsServer_setMaxDataSetEntries(self->mmsServer, serverConfiguration->maxDataSetEntries);
            GspMmsServer_enableJournalService(self->mmsServer, serverConfiguration->enableLogService);
            GspMmsServer_setFilestoreBasepath(self->mmsServer, (char *)serverConfiguration->fileServiceBasepath.c_str());
            GspMmsServer_setMaxConnections(self->mmsServer, serverConfiguration->maxMmsConnections);
        }
#endif

        GspMmsMapping_setMmsServer(self->mmsMapping, self->mmsServer);

        GspMmsMapping_installHandlers(self->mmsMapping);

        createMmsServerCache(self);

        dataModel->initializer();

        installDefaultValuesInCache(self); /* This will also connect cached MmsValues to DataAttributes */
        dataModel->installCacheValue = true;

        updateDataSetsWithCachedValues(self);

        self->clientConnections = GspLinkedList_create();

        /* default write access policy allows access to SP, SE and SV FCDAs but denies access to DC and CF FCDAs */
        self->writeAccessPolicies = ALLOW_WRITE_ACCESS_SP | ALLOW_WRITE_ACCESS_SV | ALLOW_WRITE_ACCESS_SE;
#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
        GspMmsMapping_initializeControlObjects(self->mmsMapping);
#endif

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
        GspReporting_activateBufferedReports(self->mmsMapping);
#endif

#if (CONFIG_DLT860_SETTING_GROUPS == 1)
        GspMmsMapping_configureSettingGroups(self->mmsMapping);
#endif
    }

    return self;
}

GspIedServer GspIedServer_create(GspIedModel *dataModel)
{
    return GspIedServer_createWithConfig(dataModel, nullptr, nullptr);
}

struct Dlt860NetworkConfig
{
    string bind;
    int port;
};

struct Dlt860Config
{
    string model;
    string file_root;
    string sg_storage;
    Dlt860NetworkConfig network;
};

GspIedServer GspIedServer_startWithJson(const char *configContent)
{
    json j = json::parse(configContent);

    string model = j.value("model", "");
    if (model.empty())
    {
        throw std::runtime_error("配置文件model字段不能为空");
    }
    bool is_debug = j.value("debug", false);

    bool needStart = j.value("start", true);

    if (needStart)
    {
        set_is_debug(is_debug);

        string fileRoot = j.value("file_root", "");

        if (fileRoot.empty())
        {
            throw std::runtime_error("配置文件file_root项不能为空");
        }
        string sgStorage = j.value("sg_storage", "");

        if (sgStorage.empty())
        {
            throw std::runtime_error("配置文件sg_storage项不能为空");
        }
        string logStorage = j.value("log_storage", "");
        if (logStorage.empty())
        {
            throw std::runtime_error("配置文件log_storage项不能为空");
        }

        auto network = j.value("network", nlohmann::json());

        string bind = network.value("bind", "0.0.0.0");
        int port = network.value("port", 8102);

        auto ignoreObj = j.value("ignore_ied", nlohmann::json());
        scd::ScdConfig scdConfig;

        for (auto &item : ignoreObj)
        {
            scdConfig.ignoreIeds.insert(string(item));
        }

        auto models = ModelGenerator::inst()->generateWithConfig(model, scdConfig);
        auto serverConfig = GspIedServerConfig_create();
        serverConfig->reportBufferSize = j.value("report_buf_size", 100);
        serverConfig->reportBufferSizeURCBs = j.value("report_buf_size", 100);
        serverConfig->logStoragePath = logStorage;

        auto server = GspIedServer_createMulti(models->data(), serverConfig);

        GspIedServerConfig_destroy(serverConfig);
        GspIedServer_setFilestoreBasepath(server, fileRoot.c_str());
        GspIedServer_setSgStorageFile(server, sgStorage.c_str());
        if (!bind.empty())
        {
            GspIedServer_setLocalIpAddress(server, bind.c_str());
        }
        GspIedServer_start(server, port);
        return server;
    } else {
        auto models = ModelGenerator::inst()->generate(model);
        auto server = new sGspIedServer();
        server->modelss = models->data();
        return server;
    }
}

GspIedServer GspIedServer_startWithJsonAndModels(const char *configContent, GspIedModel **model, GspIedServer origServer)
{
    json j = json::parse(configContent);
    bool is_debug = j.value("debug", false);

    bool needStart = j.value("start", true);

    set_is_debug(is_debug);

    string fileRoot = j.value("file_root", "");

    if (fileRoot.empty())
    {
        throw std::runtime_error("配置文件file_root项不能为空");
    }
    string sgStorage = j.value("sg_storage", "");

    if (sgStorage.empty())
    {
        throw std::runtime_error("配置文件sg_storage项不能为空");
    }
    string logStorage = j.value("log_storage", "");
    if (logStorage.empty())
    {
        throw std::runtime_error("配置文件log_storage项不能为空");
    }

    auto network = j.value("network", nlohmann::json());

    string bind = network.value("bind", "0.0.0.0");
    int port = network.value("port", 8102);

    auto ignoreObj = j.value("ignore_ied", nlohmann::json());
    scd::ScdConfig scdConfig;

    for (auto &item : ignoreObj)
    {
        scdConfig.ignoreIeds.insert(string(item));
    }

    auto serverConfig = GspIedServerConfig_create();
    serverConfig->reportBufferSize = j.value("report_buf_size", 100);
    serverConfig->reportBufferSizeURCBs = j.value("report_buf_size", 100);
    serverConfig->logStoragePath = logStorage;

    auto server = origServer ? origServer : GspIedServer_createMulti(model, serverConfig);

    GspIedServerConfig_destroy(serverConfig);
    GspIedServer_setFilestoreBasepath(server, fileRoot.c_str());
    GspIedServer_setSgStorageFile(server, sgStorage.c_str());
    if (!bind.empty())
    {
        GspIedServer_setLocalIpAddress(server, bind.c_str());
    }
    GspIedServer_start(server, port);
    return server;
}


GspIedServer GspIedServer_startWithJsonFile(const char *jsonFile)
{
    std::ifstream i(jsonFile);
    std::string str((std::istreambuf_iterator<char>(i)),
                    std::istreambuf_iterator<char>());
    return GspIedServer_startWithJson(str.c_str());
}

GspIedServer GspIedServer_createMulti(GspIedModel **dataModel, GspIedServerConfig config)
{
    return GspIedServer_createWithConfigMulti(dataModel, nullptr, config);
}

GspIedServer GspIedServer_createWithTlsSupport(GspIedModel *dataModel, GspTLSConfiguration tlsConfiguration)
{
    return GspIedServer_createWithConfig(dataModel, tlsConfiguration, nullptr);
}

void GspIedServer_destroy(GspIedServer server)
{
    auto self = (GspIedServer)server;
    /* Stop server if running */
    if (self->running)
    {
#if (CONFIG_MMS_THREADLESS_STACK == 1)
        IedServer_stopThreadless(self);
#else
        GspIedServer_stop(self);
#endif
    }

#if ((CONFIG_MMS_SINGLE_THREADED == 1) && (CONFIG_MMS_THREADLESS_STACK == 0))

    if (self->serverThread)
        GspThread_destroy(self->serverThread);

#endif

    MmsServer_destroy(self->mmsServer);

    if (self->localIpAddress != nullptr)
        GLOBAL_FREEMEM(self->localIpAddress);

    GspMmsMapping_destroy(self->mmsMapping);

    GspLinkedList_destroyDeep(self->clientConnections, (GspLinkedListValueDeleteFunction)Gsp_private_ClientConnection_destroy);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_destroy(self->dataModelLock);
    GspSemaphore_destroy(self->clientConnectionsLock);
#endif

#if (CONFIG_IEC61850_SUPPORT_SERVER_IDENTITY == 1)

    if (self->vendorName)
        GLOBAL_FREEMEM(self->vendorName);

    if (self->modelName)
        GLOBAL_FREEMEM(self->modelName);

    if (self->revision)
        GLOBAL_FREEMEM(self->revision);
#endif /* (CONFIG_IEC61850_SUPPORT_SERVER_IDENTITY == 1) */

    for(auto &&item : *self->cacheValueList)
    {
        GspMmsValue_delete((GspMmsValue *)item);
    }
    delete self;
    //GLOBAL_FREEMEM(self);
}

void GspIedServer_setAuthenticator(GspIedServer self, GspAcseAuthenticator authenticator, void *authenticatorParameter)
{
    MmsServer_setClientAuthenticator(self->mmsServer, authenticator, authenticatorParameter);
}

GspMmsServer
GspIedServer_getMmsServer(GspIedServer self)
{
    return self->mmsServer;
}

#if (CONFIG_MMS_THREADLESS_STACK != 1)
#if (CONFIG_MMS_SINGLE_THREADED == 1)
static void singleThreadedServerThread(void *parameter)
{
    GspIedServer self = (GspIedServer)parameter;

    GspMmsMapping *mmsMapping = self->mmsMapping;

    bool running = true;

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: server thread started!\n");

    while (running)
    {
        MmsServer_handleIncomingMessages(self->mmsServer);

        GspIedServer_performPeriodicTasks(self);

        running = mmsMapping->reportThreadRunning;
    }

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: server thread finished!\n");
}
#endif /* (CONFIG_MMS_SINGLE_THREADED == 1) */
#endif /* (CONFIG_MMS_THREADLESS_STACK != 1) */

#if (CONFIG_MMS_THREADLESS_STACK != 1)
void GspIedServer_start(GspIedServer self, int tcpPort)
{
    if (self->running == false)
    {

#if (CONFIG_MMS_SINGLE_THREADED == 1)
        MmsServer_startListeningThreadless(self->mmsServer, tcpPort);

        self->mmsMapping->reportThreadRunning = true;

        self->serverThread = GspThread_create((GspThreadExecutionFunction)singleThreadedServerThread, (void *)self, false);

        GspThread_start(self->serverThread);
#else
        MmsServer_startListening(self->mmsServer, tcpPort);
        MmsMapping_startEventWorkerThread(self->mmsMapping);
#endif

        self->running = true;
    }
}
#endif

bool GspIedServer_isRunning(GspIedServer self)
{
    if (self)
    {
        return GspMmsServer_checkState(((GspIedServer)self)->mmsServer, GSP_ISO_SVR_STATE_RUNNING);
    }
    return false;
}

bool GspIedServer_isError(GspIedServer self)
{
    if (self)
    {
        return GspMmsServer_checkState(((GspIedServer)self)->mmsServer, GSP_ISO_SVR_STATE_ERROR);
    }
    return false;
}

void GspIedServer_setIgnoreIeds(const set<string> &iedNames)
{
    GspServerObject::setIgnoreIedNames(iedNames);
}

GspIedModel **GspIedServer_getDataModels(GspIedServer self)
{
    return self->modelss;
}

#if (CONFIG_MMS_THREADLESS_STACK != 1)
void GspIedServer_stop(GspIedServer server)
{
    auto self = (GspIedServer)server;
    if (self->running)
    {
        self->running = false;

        GspMmsMapping_stopEventWorkerThread(self->mmsMapping);

#if (CONFIG_MMS_SINGLE_THREADED == 1)
        GspThread_destroy(self->serverThread);
        self->serverThread = nullptr;

        MmsServer_stopListeningThreadless(self->mmsServer);
#else
        MmsServer_stopListening(self->mmsServer);
#endif
    }
}
#endif /* (CONFIG_MMS_THREADLESS_STACK != 1) */

void GspIedServer_setFilestoreBasepath(GspIedServer self, const char *basepath)
{
    /* simply pass to MMS server API */
    GspMmsServer_setFilestoreBasepath(self->mmsServer, basepath);
}

void GspIedServer_setLocalIpAddress(GspIedServer self, const char *localIpAddress)
{
    if (self->localIpAddress != nullptr)
        GLOBAL_FREEMEM(self->localIpAddress);

    self->localIpAddress = StringUtils_copyString(localIpAddress);

    GspMmsServer_setLocalIpAddress(self->mmsServer, self->localIpAddress);
}

void GspIedServer_startThreadless(GspIedServer self, int tcpPort)
{
    if (self->running == false)
    {
        MmsServer_startListeningThreadless(self->mmsServer, tcpPort);
        self->running = true;
    }
}

int GspIedServer_getNumberOfOpenConnections(GspIedServer self)
{
    return MmsServer_getConnectionCounter(self->mmsServer);
}

int GspIedServer_waitReady(GspIedServer self, unsigned int timeoutMs)
{
    return MmsServer_waitReady(self->mmsServer, timeoutMs);
}

void GspIedServer_processIncomingData(GspIedServer self)
{
    MmsServer_handleIncomingMessages(self->mmsServer);
}

void GspIedServer_stopThreadless(GspIedServer self)
{
    if (self->running)
    {
        self->running = false;

        MmsServer_stopListeningThreadless(self->mmsServer);
    }
}

void GspIedServer_lockDataModel(GspIedServer self)
{
    MmsServer_lockModel(self->mmsServer);

    self->mmsMapping->isModelLocked = true;
}

void GspIedServer_unlockDataModel(GspIedServer self)
{
    /* check if reports have to be sent! */
    GspReporting_processReportEventsAfterUnlock(self->mmsMapping);

    self->mmsMapping->isModelLocked = false;

    MmsServer_unlockModel(self->mmsServer);
}

#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
static GspControlObject *lookupControlObject(GspIedServer self, GspDataObject *node)
{
    char objectReference[130];

    GspModelNode_getObjectReference((GspModelNode *)node, objectReference);

    char *separator = strchr(objectReference, '/');

    *separator = 0;

    GspMmsDomain *domain = GspMmsDevice_getDomain(self->mmsDevice, objectReference);

    char *lnName = separator + 1;

    separator = strchr(lnName, '.');

    assert(separator != NULL);

    *separator = 0;

    char *objectName = separator + 1;

    StringUtils_replace(objectName, '.', '$');

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: looking for control object: %s\n", objectName);

    GspControlObject *controlObject = GspMmsMapping_getControlObject(self->mmsMapping, domain,
                                                                     lnName, objectName);

    if (controlObject)
        controlObject->dataObject = node;

    return controlObject;
}

void GspIedServer_setControlHandler(
    GspIedServer self,
    GspDataObject *node,
    GspControlHandler listener,
    void *parameter)
{
    GspControlObject *controlObject = lookupControlObject(self, node);

    if (controlObject != nullptr)
    {
        GspControlObject_installListener(controlObject, listener, parameter);
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: Installed control handler for %s!\n", node->name);
    }
    else
    {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: Failed to install control handler!\n");
    }
}

void GspIedServer_setPerformCheckHandler(GspIedServer self, GspDataObject *node, GspControlPerformCheckHandler handler, void *parameter)
{
    GspControlObject *controlObject = lookupControlObject(self, node);

    if (controlObject != nullptr)
        GspControlObject_installCheckHandler(controlObject, handler, parameter);
}

void GspIedServer_setWaitForExecutionHandler(GspIedServer self, GspDataObject *node, GspControlWaitForExecutionHandler handler, void *parameter)
{
    GspControlObject *controlObject = lookupControlObject(self, node);

    if (controlObject != nullptr)
        GspControlObject_installWaitForExecutionHandler(controlObject, handler, parameter);
}

void GspIedServer_updateCtlModel(GspIedServer self, GspDataObject *ctlObject, GspControlModel value)
{
    GspControlObject *controlObject = lookupControlObject(self, ctlObject);

    if (controlObject != nullptr)
        GspControlObject_updateControlModel(controlObject, value, ctlObject);
}

#endif /* (CONFIG_DLT860_CONTROL_SERVICE == 1) */

#if (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1)

void IedServer_setSVCBHandler(IedServer self, SVControlBlock *svcb, SVCBEventHandler handler, void *parameter)
{
    LIBIEC61850_SV_setSVCBHandler(self->mmsMapping, svcb, handler, parameter);
}

#endif /* (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1) */

GspMmsValue *GspIedServer_getAttributeValue(GspIedServer self, GspDataAttribute *dataAttribute)
{
    return dataAttribute->mmsValue;
}

bool GspIedServer_getBooleanAttributeValue(GspIedServer self, const GspDataAttribute *dataAttribute)
{
    assert(self != NULL);
    assert(dataAttribute != NULL);
    assert(dataAttribute->mmsValue != NULL);

    return GspMmsValue_getBoolean(dataAttribute->mmsValue);
}

int32_t GspIedServer_getInt32AttributeValue(GspIedServer self, const GspDataAttribute *dataAttribute)
{
    assert(self != NULL);
    assert(dataAttribute != NULL);
    assert(dataAttribute->mmsValue != NULL);

    return GspMmsValue_toInt32(dataAttribute->mmsValue);
}

int64_t GspIedServer_getInt64AttributeValue(GspIedServer self, const GspDataAttribute *dataAttribute)
{
    assert(self != NULL);
    assert(dataAttribute != NULL);
    assert(dataAttribute->mmsValue != NULL);

    return GspMmsValue_toInt64(dataAttribute->mmsValue);
}

uint32_t GspIedServer_getUInt32AttributeValue(GspIedServer self, const GspDataAttribute *dataAttribute)
{
    assert(self != NULL);
    assert(dataAttribute != NULL);
    assert(dataAttribute->mmsValue != NULL);
    return GspMmsValue_toUint32(dataAttribute->mmsValue);
}

float GspIedServer_getFloatAttributeValue(GspIedServer self, const GspDataAttribute *dataAttribute)
{
    assert(self != NULL);
    assert(dataAttribute != NULL);
    assert(dataAttribute->mmsValue != NULL);

    return GspMmsValue_toFloat(dataAttribute->mmsValue);
}

uint64_t GspIedServer_getUTCTimeAttributeValue(GspIedServer self, const GspDataAttribute *dataAttribute)
{
    assert(self != NULL);
    assert(dataAttribute != NULL);
    assert(dataAttribute->mmsValue != NULL);

    return GspMmsValue_getUtcTimeInMs(dataAttribute->mmsValue);
}

uint32_t GspIedServer_getBitStringAttributeValue(GspIedServer self, const GspDataAttribute *dataAttribute)
{
    assert(self != NULL);
    assert(dataAttribute != NULL);
    assert(dataAttribute->mmsValue != NULL);
    assert(GspMmsValue_getBitStringSize(dataAttribute->mmsValue) < 33);

    return GspMmsValue_getBitStringAsInteger(dataAttribute->mmsValue);
}

const char *GspIedServer_getStringAttributeValue(GspIedServer self, const GspDataAttribute *dataAttribute)
{
    assert(self != NULL);
    assert(dataAttribute != NULL);
    assert(dataAttribute->mmsValue != NULL);
    return GspMmsValue_toString(dataAttribute->mmsValue);
}

static inline void checkForUpdateTrigger(GspIedServer self, GspDataAttribute *dataAttribute)
{
#if ((CONFIG_DLT860_REPORT_SERVICE == 1) || (CONFIG_DLT860_LOG_SERVICE == 1))
    if (dataAttribute->triggerOptions & GSP_TRG_OPT_DATA_UPDATE)
    {

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
        GspMmsMapping_triggerReportObservers(self->mmsMapping, dataAttribute->mmsValue,
                                             GSP_REPORT_CONTROL_VALUE_UPDATE);
#endif

#if (CONFIG_DLT860_LOG_SERVICE == 1)
        GspMmsMapping_triggerLogging(self->mmsMapping, dataAttribute->mmsValue,
                                     LOG_CONTROL_VALUE_UPDATE);
#endif
    }
#endif /* ((CONFIG_DLT860_REPORT_SERVICE == 1) || (CONFIG_DLT860_LOG_SERVICE == 1)) */
}

static inline void checkForChangedTriggers(GspIedServer self, GspDataAttribute *dataAttribute)
{
#if (CONFIG_DLT860_REPORT_SERVICE == 1) || (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
    if (dataAttribute->triggerOptions & GSP_TRG_OPT_DATA_CHANGED)
    {

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
        MmsMapping_triggerGooseObservers(self->mmsMapping, dataAttribute->mmsValue);
#endif

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
        GspMmsMapping_triggerReportObservers(self->mmsMapping, dataAttribute->mmsValue,
                                             GSP_REPORT_CONTROL_VALUE_CHANGED);
#endif

#if (CONFIG_DLT860_LOG_SERVICE == 1)
        GspMmsMapping_triggerLogging(self->mmsMapping, dataAttribute->mmsValue,
                                     LOG_CONTROL_VALUE_CHANGED);
#endif
    }
    else if (dataAttribute->triggerOptions & GSP_TRG_OPT_QUALITY_CHANGED)
    {

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
        MmsMapping_triggerGooseObservers(self->mmsMapping, dataAttribute->mmsValue);
#endif

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
        GspMmsMapping_triggerReportObservers(self->mmsMapping, dataAttribute->mmsValue,
                                             GSP_REPORT_CONTROL_QUALITY_CHANGED);
#endif

#if (CONFIG_DLT860_LOG_SERVICE == 1)
        GspMmsMapping_triggerLogging(self->mmsMapping, dataAttribute->mmsValue,
                                     LOG_CONTROL_QUALITY_CHANGED);
#endif
    }
#endif /* (CONFIG_DLT860_REPORT_SERVICE== 1) || (CONFIG_INCLUDE_GOOSE_SUPPORT == 1) */
}

void GspIedServer_updateAttributeValue(GspIedServer self, GspDataAttribute *dataAttribute, GspMmsValue *value)
{
    if (!dataAttribute)
    {
        throw invalid_argument(fmt::format("gsp server, 更新DA[{}]失败", fmt::ptr(dataAttribute)));
    }
    if (!value)
    {
        throw invalid_argument(fmt::format("gsp server, 更新DA[{}]失败, 更新值为空",
                                           GspModelNode_getObjectReference((GspModelNode *)dataAttribute)));
    }

    if (GspMmsValue_getType(dataAttribute->mmsValue) != GspMmsValue_getType(value))
    {
        throw invalid_argument(
            fmt::format("gsp server, 更新DA[{}]失败，更新值类型[{}]与DA值类型[{}]不匹配",
                        GspModelNode_getObjectReference((GspModelNode *)dataAttribute),
                        GspMmsValue_getType(value),
                        GspMmsValue_getType(dataAttribute->mmsValue)));
    }

    if (GspMmsValue_equals(dataAttribute->mmsValue, value))
    {
        checkForUpdateTrigger(self, dataAttribute);
    }
    else
    {

        if (dataAttribute->type == DLT860_BOOLEAN)
        {
            /* Special treatment because of transient option */
            GspIedServer_updateBooleanAttributeValue(self, dataAttribute, GspMmsValue_getBoolean(value));
        }
        else
        {
#if (CONFIG_MMS_THREADLESS_STACK != 1)
            GspSemaphore_wait(self->dataModelLock);
#endif

            GspMmsValue_update(dataAttribute->mmsValue, value);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
            GspSemaphore_post(self->dataModelLock);
#endif

            checkForChangedTriggers(self, dataAttribute);
        }
    }
}

void GspIedServer_updateFloatAttributeValue(GspIedServer self, GspDataAttribute *dataAttribute, float value)
{
    assert(dataAttribute != NULL);
    assert(self != NULL);

    float currentValue = GspMmsValue_toFloat(dataAttribute->mmsValue);

    if (currentValue == value)
    {
        checkForUpdateTrigger(self, dataAttribute);
    }
    else
    {
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->dataModelLock);
#endif
        GspMmsValue_setFloat(dataAttribute->mmsValue, value);
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->dataModelLock);
#endif
        checkForChangedTriggers(self, dataAttribute);
    }
}

void GspIedServer_updateInt32AttributeValue(GspIedServer self, GspDataAttribute *dataAttribute, int32_t value)
{
    assert(dataAttribute != NULL);
    assert(self != NULL);

    int32_t currentValue = GspMmsValue_toInt32(dataAttribute->mmsValue);

    if (currentValue == value)
    {
        checkForUpdateTrigger(self, dataAttribute);
    }
    else
    {
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->dataModelLock);
#endif
        GspMmsValue_setInt32(dataAttribute->mmsValue, value);
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->dataModelLock);
#endif

        checkForChangedTriggers(self, dataAttribute);
    }
}

void GspIedServer_updateDbposValue(GspIedServer self, GspDataAttribute *dataAttribute, GspDbpos value)
{
    GspDbpos currentValue = GspDbpos_fromMmsValue(dataAttribute->mmsValue);

    if (currentValue == value)
    {
        checkForUpdateTrigger(self, dataAttribute);
    }
    else
    {
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->dataModelLock);
#endif
        GspDbpos_toMmsValue(dataAttribute->mmsValue, value);
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->dataModelLock);
#endif

        checkForChangedTriggers(self, dataAttribute);
    }
}

void GspIedServer_updateInt64AttributeValue(GspIedServer self, GspDataAttribute *dataAttribute, int64_t value)
{
    assert(dataAttribute != NULL);
    assert(self != NULL);

    int64_t currentValue = GspMmsValue_toInt64(dataAttribute->mmsValue);

    if (currentValue == value)
    {
        checkForUpdateTrigger(self, dataAttribute);
    }
    else
    {
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->dataModelLock);
#endif
        GspMmsValue_setInt64(dataAttribute->mmsValue, value);
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->dataModelLock);
#endif

        checkForChangedTriggers(self, dataAttribute);
    }
}

void GspIedServer_updateUnsignedAttributeValue(GspIedServer self, GspDataAttribute *dataAttribute, uint32_t value)
{
    assert(dataAttribute != NULL);
    assert(self != NULL);

    uint32_t currentValue = GspMmsValue_toUint32(dataAttribute->mmsValue);

    if (currentValue == value)
    {
        checkForUpdateTrigger(self, dataAttribute);
    }
    else
    {
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->dataModelLock);
#endif
        GspMmsValue_setUint32(dataAttribute->mmsValue, value);
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->dataModelLock);
#endif

        checkForChangedTriggers(self, dataAttribute);
    }
}

void GspIedServer_updateBitStringAttributeValue(GspIedServer self, GspDataAttribute *dataAttribute, uint32_t value)
{
    assert(dataAttribute != NULL);
    assert(self != NULL);

    uint32_t currentValue = GspMmsValue_getBitStringAsInteger(dataAttribute->mmsValue);

    if (currentValue == value)
    {
        checkForUpdateTrigger(self, dataAttribute);
    }
    else
    {
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->dataModelLock);
#endif
        GspMmsValue_setBitStringFromInteger(dataAttribute->mmsValue, value);
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->dataModelLock);
#endif

        checkForChangedTriggers(self, dataAttribute);
    }
}

void GspIedServer_updateBoolValue(GspIedServer self, const char *daRefer, bool value)
{
    string domainName;
    string itemId;
    splitDomainAndItemId(daRefer, domainName, itemId);
    auto model = GspMmsMapping_getIedModelByDomainName(self->mmsMapping, domainName);
    GspModelNode *daNode = GspIedModel_getModelNodeByObjectReference(model, daRefer);
    if (daNode)
    {
        auto dataAttribute = (GspDataAttribute *)daNode;
        GspIedServer_updateBooleanAttributeValue(self, dataAttribute, value);
    }
}

void GspIedServer_updateBooleanAttributeValue(GspIedServer self, GspDataAttribute *dataAttribute, bool value)
{
    assert(self != NULL);
    assert(dataAttribute != NULL);

    bool currentValue = GspMmsValue_getBoolean(dataAttribute->mmsValue);

    if (currentValue == value)
    {
        checkForUpdateTrigger(self, dataAttribute);
    }
    else
    {

        bool callCheckTriggers = true;

        if (dataAttribute->triggerOptions & TRG_OPT_TRANSIENT)
        {
            if (currentValue == true)
                callCheckTriggers = false;
        }

#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->dataModelLock);
#endif
        GspMmsValue_setBoolean(dataAttribute->mmsValue, value);
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->dataModelLock);
#endif

        if (callCheckTriggers)
            checkForChangedTriggers(self, dataAttribute);
    }
}

void GspIedServer_updateVisibleStringAttributeValue(GspIedServer self, GspDataAttribute *dataAttribute, char *value)
{
    assert(dataAttribute != NULL);
    assert(self != NULL);

    const char *currentValue = GspMmsValue_toString(dataAttribute->mmsValue);

    if (!strcmp(currentValue, value))
    {
        checkForUpdateTrigger(self, dataAttribute);
    }
    else
    {
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->dataModelLock);
#endif
        GspMmsValue_setVisibleString(dataAttribute->mmsValue, value);
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->dataModelLock);
#endif

        checkForChangedTriggers(self, dataAttribute);
    }
}

void GspIedServer_updateUTCTimeAttributeValue(GspIedServer self, GspDataAttribute *dataAttribute, uint64_t value)
{
    assert(dataAttribute != NULL);
    assert(self != NULL);

    uint64_t currentValue = GspMmsValue_getUtcTimeInMs(dataAttribute->mmsValue);

    if (currentValue == value)
    {
        checkForUpdateTrigger(self, dataAttribute);
    }
    else
    {
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->dataModelLock);
#endif
        GspMmsValue_setUtcTimeMs(dataAttribute->mmsValue, value);
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->dataModelLock);
#endif

        checkForChangedTriggers(self, dataAttribute);
    }
}

void GspIedServer_updateTimestampAttributeValue(GspIedServer self, GspDataAttribute *dataAttribute, GspTimestamp *timestamp)
{
    assert(dataAttribute != NULL);
    assert(self != NULL);

    if (memcmp(dataAttribute->mmsValue->choice.utc_time.buf, timestamp->val, 8) == 0)
    {
        checkForUpdateTrigger(self, dataAttribute);
    }
    else
    {
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->dataModelLock);
#endif
        GspMmsValue_setUtcTimeByBuffer(dataAttribute->mmsValue, timestamp->val);
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->dataModelLock);
#endif

        checkForChangedTriggers(self, dataAttribute);
    }
}

void GspIedServer_updateQuality(GspIedServer self, GspDataAttribute *dataAttribute, GspQuality quality)
{
    assert(strcmp(dataAttribute->name, "q") == 0);
    assert(GspMmsValue_getBitStringSize(dataAttribute->mmsValue) >= 12);
    assert(GspMmsValue_getBitStringSize(dataAttribute->mmsValue) <= 15);

    uint32_t oldQuality = GspMmsValue_getBitStringAsInteger(dataAttribute->mmsValue);

    if (oldQuality != (uint32_t)quality)
    {
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->dataModelLock);
#endif
        GspMmsValue_setBitStringFromInteger(dataAttribute->mmsValue, (uint32_t)quality);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->dataModelLock);
#endif

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
        MmsMapping_triggerGooseObservers(self->mmsMapping, dataAttribute->mmsValue);
#endif

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
        if (dataAttribute->triggerOptions & GSP_TRG_OPT_QUALITY_CHANGED)
            GspMmsMapping_triggerReportObservers(self->mmsMapping, dataAttribute->mmsValue,
                                                 GSP_REPORT_CONTROL_QUALITY_CHANGED);
#endif

#if (CONFIG_DLT860_LOG_SERVICE == 1)
        if (dataAttribute->triggerOptions & GSP_TRG_OPT_QUALITY_CHANGED)
            GspMmsMapping_triggerLogging(self->mmsMapping, dataAttribute->mmsValue,
                                         LOG_CONTROL_QUALITY_CHANGED);
#endif
    }
}

void GspIedServer_useGooseVlanTag(GspIedServer self, GspLogicalNode *ln, const char *gcbName, bool useVlanTag)
{
#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
    MmsMapping_useGooseVlanTag(self->mmsMapping, ln, gcbName, useVlanTag);
#endif /* (CONFIG_INCLUDE_GOOSE_SUPPORT == 1) */
}

void GspIedServer_setGooseInterfaceIdEx(GspIedServer self, GspLogicalNode *ln, const char *gcbName, const char *interfaceId)
{
#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
    MmsMapping_setGooseInterfaceId(self->mmsMapping, ln, gcbName, interfaceId);
#endif /* (CONFIG_INCLUDE_GOOSE_SUPPORT == 1) */
}

void GspIedServer_enableGoosePublishing(GspIedServer self)
{
#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
    MmsMapping_enableGoosePublishing(self->mmsMapping);
#endif /* (CONFIG_INCLUDE_GOOSE_SUPPORT == 1) */
}

void GspIedServer_disableGoosePublishing(GspIedServer self)
{
#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
    MmsMapping_disableGoosePublishing(self->mmsMapping);
#endif /* (CONFIG_INCLUDE_GOOSE_SUPPORT == 1) */
}

void GspIedServer_setWriteAccessPolicy(GspIedServer self, GspFunctionalConstraint fc, GspAccessPolicy policy)
{
    if (policy == ACCESS_POLICY_ALLOW)
    {
        switch (fc)
        {
        case DLT860_FC_DC:
            self->writeAccessPolicies |= ALLOW_WRITE_ACCESS_DC;
            break;
        case DLT860_FC_CF:
            self->writeAccessPolicies |= ALLOW_WRITE_ACCESS_CF;
            break;
        case DLT860_FC_SP:
            self->writeAccessPolicies |= ALLOW_WRITE_ACCESS_SP;
            break;
        case DLT860_FC_SV:
            self->writeAccessPolicies |= ALLOW_WRITE_ACCESS_SV;
            break;
        case DLT860_FC_SE:
            self->writeAccessPolicies |= ALLOW_WRITE_ACCESS_SE;
            break;
        default: /* ignore - request is invalid */
            break;
        }
    }
    else
    {
        switch (fc)
        {
        case DLT860_FC_DC:
            self->writeAccessPolicies &= ~ALLOW_WRITE_ACCESS_DC;
            break;
        case DLT860_FC_CF:
            self->writeAccessPolicies &= ~ALLOW_WRITE_ACCESS_CF;
            break;
        case DLT860_FC_SP:
            self->writeAccessPolicies &= ~ALLOW_WRITE_ACCESS_SP;
            break;
        case DLT860_FC_SV:
            self->writeAccessPolicies &= ~ALLOW_WRITE_ACCESS_SV;
            break;
        case DLT860_FC_SE:
            self->writeAccessPolicies &= ~ALLOW_WRITE_ACCESS_SE;
            break;
        default: /* ignore - request is invalid */
            break;
        }
    }
}

void GspIedServer_handleWriteAccess(GspIedServer self, GspDataAttribute *dataAttribute, GspWriteAccessHandler handler, void *parameter)
{
    if (dataAttribute == nullptr)
    {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: IedServer_handleWriteAccess - dataAttribute == NULL!\n");
    }
    else
    {
        GspMmsMapping_installWriteAccessHandler(self->mmsMapping, dataAttribute, handler, parameter);
    }
}

void GspIedServer_setReadAccessHandler(GspIedServer self, GspReadAccessHandler handler, void *parameter)
{
    GspMmsMapping_installReadAccessHandler(self->mmsMapping, handler, parameter);
}

void GspIedServer_setConnectionIndicationHandler(GspIedServer self, GspIedConnectionIndicationHandler handler, void *parameter)
{
    GspMmsMapping_setConnectionIndicationHandler(self->mmsMapping, handler, parameter);
}

GspMmsValue *GspIedServer_getFunctionalConstrainedData(GspIedServer self, GspDataObject *dataObject, GspFunctionalConstraint fc)
{
    char buffer[128]; /* buffer for variable name string */
    char *currentStart = buffer + 127;
    currentStart[0] = 0;
    GspMmsValue *value = nullptr;

    int nameLen;

    while (dataObject->modelType == GspDataObjectModelType)
    {
        nameLen = strlen(dataObject->name);
        currentStart -= nameLen;
        memcpy(currentStart, dataObject->name, nameLen);
        currentStart--;
        *currentStart = '$';

        if (dataObject->parent->modelType == GspDataObjectModelType)
        {
            dataObject = (GspDataObject *)dataObject->parent;
        }
        else
        {
            break;
        }
    }

    char *fcString = GspFunctionalConstraint_toString(fc);
    if (fcString == nullptr)
    {
        return nullptr;
    }

    currentStart--;
    *currentStart = fcString[1];
    currentStart--;
    *currentStart = fcString[0];
    currentStart--;
    *currentStart = '$';

    GspLogicalNode *ln = (GspLogicalNode *)dataObject->parent;

    nameLen = strlen(ln->name);

    currentStart -= nameLen;
    memcpy(currentStart, ln->name, nameLen);

    GspLogicalDevice *ld = (GspLogicalDevice *)ln->parent;

    char domainName[65];

    if ((strlen(ld->iedName) + strlen(ld->name)) > 64)
    {

        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: LD name too long!\n");

        delete[] fcString;
        return value;
    }

    strncpy(domainName, ld->iedName, 64);
    strncat(domainName, ld->name, 64);

    GspMmsDomain *domain = GspMmsDevice_getDomain(self->mmsDevice, domainName);

    if (domain == nullptr)
    {

        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: internal error - domain does not exist!\n");
        delete[] fcString;
        return value;
    }

    value = MmsServer_getValueFromCache(self->mmsServer, domain, currentStart);
    delete[] fcString;
    return value;
}

void GspIedServer_changeActiveSettingGroup(GspIedServer self, GspSettingGroupControlBlock *sgcb, uint8_t newActiveSg)
{
#if (CONFIG_DLT860_SETTING_GROUPS == 1)
    //MmsMapping_changeActiveSettingGroup(self->mmsMapping, sgcb, newActiveSg);
#endif
}

uint8_t GspIedServer_getActiveSettingGroup(GspIedServer self, GspSettingGroupControlBlock *sgcb)
{
    return sgcb->actSG;
}

void GspIedServer_setActiveSettingGroupChangedHandler(GspIedServer self, GspSettingGroupControlBlock *sgcb,
                                                      GspActiveSettingGroupChangedHandler handler, void *parameter)
{
#if (CONFIG_DLT860_SETTING_GROUPS == 1)
    GspMmsMapping_setSgChangedHandler(self->mmsMapping, sgcb, handler, parameter);
#endif
}

void GspIedServer_setEditSettingGroupChangedHandler(GspIedServer self, GspSettingGroupControlBlock *sgcb,
                                                    GspEditSettingGroupChangedHandler handler, void *parameter)
{
#if (CONFIG_DLT860_SETTING_GROUPS == 1)
    GspMmsMapping_setEditSgChangedHandler(self->mmsMapping, sgcb, handler, parameter);
#endif
}

void GspIedServer_setEditSettingGroupConfirmationHandler(GspIedServer self, GspSettingGroupControlBlock *sgcb,
                                                         GspEditSettingGroupConfirmationHandler handler, void *parameter)
{
#if (CONFIG_DLT860_SETTING_GROUPS == 1)
    GspMmsMapping_setConfirmEditSgHandler(self->mmsMapping, sgcb, handler, parameter);
#endif
}

void GspIedServer_setLogStorage(GspIedServer self, const char *logRef, GspLogStorage logStorage)
{
#if (CONFIG_DLT860_LOG_SERVICE == 1)
    GspMmsMapping_setGspLogStorage(self->mmsMapping, logRef, logStorage);
#endif
}

void GspIedServer_setServerIdentity(GspIedServer self, const char *vendor, const char *model, const char *revision)
{
#if (CONFIG_IEC61850_SUPPORT_SERVER_IDENTITY == 1)

    if (self->vendorName)
        GLOBAL_FREEMEM(self->vendorName);

    if (self->modelName)
        GLOBAL_FREEMEM(self->modelName);

    if (self->revision)
        GLOBAL_FREEMEM(self->revision);

    self->vendorName = StringUtils_copyString(vendor);
    self->modelName = StringUtils_copyString(model);
    self->revision = StringUtils_copyString(revision);

    MmsServer_setServerIdentity(self->mmsServer, self->vendorName, self->modelName, self->revision);
#endif
}

GspClientConnection Gsp_private_IedServer_getClientConnectionByHandle(GspIedServer self, void *serverConnectionHandle)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_wait(self->clientConnectionsLock);
#endif
    GspClientConnection matchingConnection = nullptr;
    for (auto &item : *(self->clientConnections))
    {
        GspClientConnection connection = (GspClientConnection)item;

        if (Gsp_private_ClientConnection_getServerConnectionHandle(connection) == serverConnectionHandle)
        {
            matchingConnection = connection;
            break;
        }
    }

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_post(self->clientConnectionsLock);
#endif

    return matchingConnection;
}

void Gsp_private_IedServer_addNewClientConnection(GspIedServer self, GspClientConnection newClientConnection)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_wait(self->clientConnectionsLock);
#endif

    GspLinkedList_add(self->clientConnections, (void *)newClientConnection);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_post(self->clientConnectionsLock);
#endif
}

void Gsp_private_IedServer_removeClientConnection(GspIedServer self, GspClientConnection clientConnection)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_wait(self->clientConnectionsLock);
#endif

    GspLinkedList_remove(self->clientConnections, clientConnection);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_post(self->clientConnectionsLock);
#endif
}

void GspIedServer_setGooseInterfaceId(GspIedServer self, const char *interfaceId)
{
#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
    self->mmsMapping->gooseInterfaceId = interfaceId;
#endif
}

void GspIedServer_setSgStorageFile(GspIedServer self, const char *file)
{
    GspMmsMapping_setSgStorageFile(self->mmsMapping, file);
}

void flattenDataObject(void *server, GspModelNode *dataObject, const char *fc, vector<GspDataAttribute *> &das)
{
    auto child = dataObject->firstChild;
    while (child)
    {
        if (child->modelType == GspDataObjectModelType)
        {
            flattenDataObject(server, child, fc, das);
        }
        else if (child->modelType == GspDataAttributeModelType)
        {
            auto da = (GspDataAttribute *)child;
            if (da->fc == GspFunctionalConstraint_fromString(fc))
            {
                if (child->firstChild)
                {
                    flattenDataObject(server, child, fc, das);
                }
                else
                {
                    das.push_back(da);
                }
            }
        }
        else
        {
            assert(0);
        }

        child = child->sibling;
    }
}

void flattenValue(void *server, GspMmsValue *value, vector<GspMmsValue *> &values)
{
    if (value->present == Data_PR_structure)
    {
        for (int i = 0; i < value->choice.structure.list.count; ++i)
        {
            flattenValue(server, value->choice.structure.list.array[i], values);
        }
    }
    else if (value->present == Data_PR_array)
    {
        for (int i = 0; i < value->choice.array.list.count; ++i)
        {
            flattenValue(server, value->choice.array.list.array[i], values);
        }
    }
    else
    {
        values.push_back(value);
    }
}

void updateDoValuFlatten(void *server, GspModelNode *dataObject, GspMmsValue *value, const char *refer, const char *fc)
{
    vector<GspDataAttribute *> das;
    vector<GspMmsValue *> values;

    flattenDataObject(server, dataObject, fc, das);
    flattenValue(server, value, values);

    if (das.size() != values.size())
    {
        string sError = fmt::format("设置DO值，refer: {}[{}]失败，对象数量{}与值数量{}不符\n", refer, fc, das.size(), values.size());
        throw invalid_argument(sError);
    }

    for (size_t i = 0; i < das.size(); ++i)
    {
        GspIedServer_updateAttributeValue((GspIedServer)server, (GspDataAttribute *)das[i], values[i]);
    }
}

void updateDoValue(void *server, GspModelNode *dataObject, GspMmsValue *value)
{
    auto child = dataObject->firstChild;
    int i = 0;
    while (child)
    {
        if (value->present == Data_PR_array)
        {
            if (child->modelType == GspDataObjectModelType)
            {
                updateDoValue(server, child, value->choice.array.list.array[i]);
            }
            else if (child->modelType == GspDataAttributeModelType)
            {
                GspIedServer_updateAttributeValue((GspIedServer)server, (GspDataAttribute *)child, value->choice.array.list.array[i]);
            }
            else
            {
                assert(0);
            }
        }
        else if (value->present == Data_PR_structure)
        {
            if (child->modelType == GspDataObjectModelType)
            {
                updateDoValue(server, child, value->choice.structure.list.array[i]);
            }
            else if (child->modelType == GspDataAttributeModelType)
            {
                GspIedServer_updateAttributeValue((GspIedServer)server, (GspDataAttribute *)child, value->choice.structure.list.array[i]);
            }
            else
            {
                assert(0);
            }
        }
        else
        {
            assert(0);
        }
        i++;
        child = child->sibling;
    }
}

GspModelNode *GspServer_getModelNodeByReferAndFc(GspIedServer server, const char *refer, const char *fc)
{
    return getDaNodeByReference(server, refer, fc);
}

GspMmsValue *GspIedServer_getReferValue(GspIedServer server, const char *refer, const char *fc)
{
    auto node = getDaNodeByReference(server, refer, fc);
    if (node)
    {
        if (node->modelType == GspDataAttributeModelType)
        {
            return GspIedServer_getAttributeValue(server, (GspDataAttribute *)node);
        }
        else
        {
            return nullptr;
        }
    }
    return nullptr;
}

GspMmsValue *GspIedServer_getValueByStr(GspIedServer server, const char *refer, const char *fc, const char *value)
{
    auto node = getDaNodeByReference(server, refer, fc);
    auto self = (GspIedServer)server;
    GspMmsValue *pValue = nullptr;
    if(node && node->modelType == GspDataAttributeModelType)
    {
        auto da = (GspDataAttribute *)node;
        pValue = GspMmsValue_clone(da->mmsValue);
        try {
        switch(da->type)
        {
        case DLT860_BOOLEAN:
        {
            if(strcasecmp(value, "true") == 0 || strcmp(value, "1") == 0)
            {
                GspMmsValue_setBoolean(pValue, true);
            }
            else if(strcasecmp(value, "false") == 0 || strcmp(value, "0") == 0)
            {
                GspMmsValue_setBoolean(pValue, false);
            }
            else
            {
                throw invalid_argument(fmt::format("设置 {} 值 {} 失败", refer, value));
            }
        }
        break;
        case DLT860_INT8:
        {
            int8_t number = (int8_t)stoi(value);
            GspMmsValue_setInt8(pValue, number);
        }
        break;
        case DLT860_INT16:
        {
            int16_t number = (int16_t)stol(value);
            GspMmsValue_setInt16
            (pValue, number);
        }
        break;
        case DLT860_INT32:
        {
            int32_t number = (int32_t)stol(value);
            GspMmsValue_setInt32(pValue, number);
        }
        break;
        case DLT860_INT64:
        {
            int64_t number = (int64_t)stoll(value);
            GspMmsValue_setInt64(pValue, number);
        }
        break;
        case DLT860_INT128:
        break;
        case DLT860_INT8U:
        {
            uint8_t number = (uint8_t)stol(value);
            GspMmsValue_setUint8(pValue, number);
        }
        break;
        case DLT860_INT16U:
        {
            uint16_t number = (uint16_t)stol(value);
            GspMmsValue_setUint16(pValue, number);
        }
        break;
        case DLT860_INT24U:
        {
            uint32_t number = (uint32_t)stoll(value);
            GspMmsValue_setUint32(pValue, number);
        }
        break;
        case DLT860_INT32U:
        {
            uint32_t number = (uint32_t)stoll(value);
            GspMmsValue_setUint32(pValue, number);
        }
        break;
        case DLT860_FLOAT32:
        {
            float number = stof(value);
            GspMmsValue_setFloat(pValue, number);
        }
        break;
        case DLT860_FLOAT64:
        {
            double number = stod(value);
            GspMmsValue_setDouble(pValue, number);
        }
        break;
        case DLT860_ENUMERATED:
        {
            int8_t number = (int8_t)stoi(value);
            GspMmsValue_setInt8(pValue, number);
        }
        break;
        case DLT860_OCTET_STRING_64:
        case DLT860_OCTET_STRING_6:
        case DLT860_OCTET_STRING_8:
        case DLT860_VISIBLE_STRING_32:
        case DLT860_VISIBLE_STRING_64:
        case DLT860_VISIBLE_STRING_65:
        case DLT860_VISIBLE_STRING_129:
        case DLT860_VISIBLE_STRING_255:
        case DLT860_UNICODE_STRING_255:
        {
            GspMmsValue_setOctetString(pValue, (uint8_t *)value, strlen(value));
        }
        break;
        case DLT860_ENTRY_TIME:
        {
            uint64_t ms = (uint64_t)stoull(value);
            GspMmsValue_setBinaryTime(pValue, ms);
            break;
        }
        case DLT860_TIMESTAMP:
        {
            uint64_t ms = (uint64_t)stoull(value);
            GspMmsValue_setUtcTimeMs(pValue, ms);
            break;
        }
        case DLT860_QUALITY:
        case DLT860_CHECK:
        case DLT860_CODEDENUM:
        case DLT860_GENERIC_BITSTRING:
        case DLT860_OPTFLDS:
        case DLT860_TRGOPS:
        case DLT860_DBPOS:
        case DLT860_TCMD:
        {
            GspMmsValue_setBitStringFromString(pValue, value);
        }
        break;
        default:
            break;
        }
        } catch(const std::exception &e)
        {
            GspMmsValue_delete(pValue);
            return NULL;
        }
    }
    return pValue;
}

bool GspIedServer_updateReferValueByStr(GspIedServer self, const char *refer, const char *fc, const char *value)
{
    auto pValue = GspIedServer_getValueByStr(self, refer, fc, value);
    auto node = getDaNodeByReference(self, refer, fc);
    if(pValue)
    {
        GspIedServer_updateAttributeValue(self, (GspDataAttribute *)node, pValue);
        GspMmsValue_delete(pValue);
        return true;
    }
    else
    {
        return false;
        //throw invalid_argument(fmt::format("没有找到 {} 对应的节点，设置值失败", refer));
    }
}

void GspIedServer_updateReferValue(GspIedServer server, const char *refer, const char *fc, GspMmsValue *value)
{
    auto node = getDaNodeByReference(server, refer, fc);
    auto self = (GspIedServer)server;

    if (node)
    {
        std::lock_guard<mutex> lock(server->getlock());
        if (node->modelType == GspDataObjectModelType)
        {
            updateDoValuFlatten(server, node, value, refer, fc);
        }
        else if (node->modelType == GspDataAttributeModelType)
        {
            GspIedServer_updateAttributeValue(self, (GspDataAttribute *)node, value);
        }
        else
        {
            assert(0);
        }
    }
    else
    {
        throw invalid_argument(fmt::format("没有找到 {} 对应的节点，设置值失败", refer));
    }
}

void GspServer_setFunctionHookFunc(GspIedServer server, ServerFunctionHook func, void *param)
{
    server->functionHook = func;
    server->functionHookParam = param;
}

GspDataSet *Gsp_private_IedServer_getDataSet(GspIedServer self, const char *dataSetRefer)
{
    auto it = self->dataSetCache.find(dataSetRefer);
    if (it == self->dataSetCache.end())
    {
        return nullptr;
    }
    return it->second;
}

void GspServer_updateDataSetValue(GspIedServer server, const ReportPDU_t &report, bool paramMode)
{
    // 容错处理
    if (!report.datSet)
    {
        return;
    }

    GspDataSetEntry *item = nullptr;
    string str_tmp;
    char tmp_ref[256]{};
    unsigned long index = 1;

    // 获取模型中的数据集信息
    string dotDataSet = (const char *)report.datSet->buf;
    toDotReference(dotDataSet);
    auto dataSet = Gsp_private_IedServer_getDataSet(server, dotDataSet.c_str());
    if (!dataSet)
    {
        throw invalid_argument(fmt::format("没有找到[{}]对应的数据集", (const char *)report.datSet->buf));
    }

    // 逐个数据条目更新模型
    auto entryCount = report.entry.entryData.list.count;
    for (auto i = 0; i < entryCount; ++i)
    {
        // 取出数据条目
        auto entry = report.entry.entryData.list.array[i];

        // 容错兼容
        if (!entry->reference)
        {
            printf("报告数据不完整, reference 为空\n");
            continue;
        }

        if (!paramMode)
        {

            // 取出数据ID
            index = entry->id;

            // 数据点数量兼容
            if (dataSet->fcdaArray.size() < index)
            {
                printf("%s 模型点数量不匹配, 设备数据集点数量:%lu, 模型数据集点数量:%zu \n", dataSet->name, index, dataSet->fcdaArray.size());
                break;
            }

            // 取出数据集中的fcda列表定义
            item = (dataSet->fcdaArray)[index - 1];
        }
        else
        {

            //如果数据引用长度大于缓冲区长度，则失败返回
            if (entry->reference->size > sizeof tmp_ref)
            {
                return;
            }

            //根据数据引用查找代理中要更新的数据集条目
            std::memcpy(tmp_ref, entry->reference->buf, entry->reference->size);
            str_tmp = string(tmp_ref);
            for (string::size_type k = 0; k < dataSet->fcdaArray.size(); k++)
            {
                string varRefer = (dataSet->fcdaArray)[k]->variableName;
                toDotReference(varRefer);
                string fc;
                string varReferWithoutFc;
                splitFcFromReferenceDot(varRefer, fc, varReferWithoutFc);
                if (str_tmp.find(varReferWithoutFc) != string::npos)
                {
                    index = k + 1;
                    item = (dataSet->fcdaArray)[k];
                    break;
                }
            }

            // 容错处理
            if (!item)
            {
                NLOG_DEBUG("在数据集{}中，找不到对应的条目{}\n", dotDataSet, str_tmp);
                continue;
            }
        }

        // 错误兼容
        printf("更新设备:%s,更新数据集:%s ,entryid: %lu \n", dataSet->iedName, dataSet->name, index);
        if (!item->logicalDeviceName || !item->variableName)
        {
            throw invalid_argument(fmt::format("更新设备[{}]数据集[{}]失败", dataSet->iedName, dataSet->name));
        }

        // 拼接全路径refs
        string refer = string(dataSet->iedName) + item->logicalDeviceName + "/" + (const char *)item->variableName;

        // 容错处理
        if (!item->value)
        {
            continue;
        }

        // 报告值与内存模型一致不在更新
        if (GspMmsValue_equals(item->value, &entry->value))
        {
            // NLOG_DEBUG("[{}]当前值与更新值相同，不更新这个entry", refer);
            continue;
        }

        // 更新内存模型值
        bool ret = GspMmsValue_update(item->value, &entry->value);
        string fc;
        splitFcFromReference(refer, fc, refer);
        toDotReference(refer);
        if (!ret)
        {
            throw invalid_argument(fmt::format("更新数据集[{}]第[{}]个值[{}]失败", dotDataSet, index, refer));
        }

        // 获取DA的信息
        vector<GspDataAttribute *> daVec;
        auto node = getDaNodeByReference(server, refer.c_str(), fc.c_str());
        if (!node)
        {
            throw invalid_argument(fmt::format("没有找到[{}]对应的DA", (const char *)item->variableName));
        }
        if (node->modelType == GspDataObjectModelType)
        {
            GspDataObject_getFCDA((GspDataObject *)node, GspFunctionalConstraint_fromString(fc.c_str()), daVec);
        }
        else if (node->modelType == GspDataAttributeModelType)
        {
            daVec.push_back((GspDataAttribute *)node);
        }
        else
        {
            throw invalid_argument(fmt::format("获取到[{}]对应的node类型错误，[{}]", refer, node->modelType));
        }

        for (auto &rc : dataSet->rcSet)
        {
            // 使能判断
            if (!rc->enabled)
            {
                continue;
            }

            // 变动判断
            for (auto &da : daVec)
            {
                if (da->triggerOptions & GSP_TRG_OPT_DATA_CHANGED)
                {

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
                    GspReportControl_triggerReportObservers(rc, GSP_REPORT_CONTROL_VALUE_CHANGED, server->mmsMapping->isModelLocked, index - 1);
#endif
                    // NLOG_DEBUG("entry [{}][{}] 数据变位，触发报告", rc->name, refer);
                    break;
                }

                else if (da->triggerOptions & GSP_TRG_OPT_QUALITY_CHANGED)
                {

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
                    GspReportControl_triggerReportObservers(rc, GSP_REPORT_CONTROL_QUALITY_CHANGED, server->mmsMapping->isModelLocked, index - 1);
                    // NLOG_DEBUG("entry [{}][{}] 品质变位，触发报告", rc->name, refer);
#endif
                    break;
                }
            }
        }
    }
}

void GspIedServer_addRpcFunc(const string &interface, const string &method, RpcInfo *rpcInfo)
{
    GspServerRpc::addRpcCall(interface, method, rpcInfo);
}
void GspIedServer_delMockRpcFunc(const string &interface, const string &method)
{
    GspServerRpc::delRpcCall(interface, method);
}
void GspIedServer_addMockRpcFunc(const string &interface, const string &method, const string &resp, bool hasNextCallId)
{
    RpcInfo *info = new RpcInfo();
    memset(info, 0, sizeof(RpcInfo));
    info->func = [resp, hasNextCallId](GspMmsValue *req, string &nextCallId) {
        if(req)
        {
            if(hasNextCallId)
            {
                string callId = std::to_string(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
                
                return GspMmsValue_newMmsString(callId.c_str());
            }
            else
            {
                return GspMmsValue_newMmsString(resp.c_str());
            }
        }
        else
        {
            static set<string> callMap;

            if(callMap.count(nextCallId))
            {
                callMap.erase(nextCallId);
            }
            return GspMmsValue_newMmsString(resp.c_str());
        }
    };
    
    GspServerRpc::addRpcCall(interface, method, info);
}
