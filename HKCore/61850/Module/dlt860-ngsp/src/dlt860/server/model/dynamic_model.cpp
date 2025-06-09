/*
 *  dynamic_model.c
 */

#include "dlt860_server.h"
#include "libdlt860_platform_includes.h"
#include "stack_config.h"
using namespace GSP;

static void iedModel_emptyVariableInitializer(void)
{
    return;
}

void
GspIedModel_setIedNameForDynamicModel(GspIedModel* self, const char* name)
{
    if (self->name != NULL)
        GLOBAL_FREEMEM(self->name);

    self->name = StringUtils_copyString(name);
}

GspIedModel*
GspIedModel_create(const char* name/*, MemoryAllocator allocator*/)
{
    GspIedModel* self = (GspIedModel*) GLOBAL_CALLOC(1, sizeof(GspIedModel));

    if (name)
        self->name = StringUtils_copyString(name);
    else
        self->name = NULL;

    self->rcbs = NULL;

    self->dataSets = NULL;

    self->gseCBs = NULL;

    self->sgcbs = NULL;

    self->lcbs = NULL;

    self->logs = NULL;

    self->initializer = iedModel_emptyVariableInitializer;
    self->installCacheValue = false;

    return self;
}

static void
IedModel_addDataSet(GspIedModel* self, GspDataSet* dataSet)
{
    if (self->dataSets == NULL)
        self->dataSets = dataSet;
    else {
        GspDataSet* lastDataSet = self->dataSets;

        while (lastDataSet != NULL) {
            if (lastDataSet->sibling == NULL) {
                lastDataSet->sibling = dataSet;
                break;
            }

            lastDataSet = lastDataSet->sibling;
        }
    }
}

static void
IedModel_addLogicalDevice(GspIedModel* self, GspLogicalDevice* lDevice)
{
    if (self->firstChild == NULL)
        self->firstChild = lDevice;
    else {
        GspLogicalDevice* sibling = self->firstChild;

        while (sibling->sibling != NULL)
            sibling = (GspLogicalDevice*) sibling->sibling;

        sibling->sibling = (GspModelNode*) lDevice;
    }
}

static void
IedModel_addLog(GspIedModel* self, GspLog* log)
{
    if (self->logs == NULL)
        self->logs = log;
    else {
        GspLog* lastLog = self->logs;

        while (lastLog->sibling != NULL)
            lastLog = lastLog->sibling;

        lastLog->sibling = log;
    }
}

static void
IedModel_addLogControlBlock(GspIedModel* self, GspLogControlBlock* lcb)
{
    if (self->lcbs == NULL)
        self->lcbs = lcb;
    else {
        GspLogControlBlock* lastLcb = self->lcbs;

        while (lastLcb->sibling != NULL)
            lastLcb = lastLcb->sibling;

        lastLcb->sibling = lcb;
    }
}

static void
IedModel_addReportControlBlock(GspIedModel* self, GspReportControlBlock* rcb)
{
    if (self->rcbs == NULL)
        self->rcbs = rcb;
    else {
        GspReportControlBlock* lastRcb = self->rcbs;

        while (lastRcb->sibling != NULL)
            lastRcb = lastRcb->sibling;

        lastRcb->sibling = rcb;
    }
}

#if (CONFIG_DLT860_SETTING_GROUPS == 1)
static void
IedModel_addSettingGroupControlBlock(GspIedModel* self, GspSettingGroupControlBlock* sgcb)
{
    if (self->sgcbs == NULL)
        self->sgcbs = sgcb;
    else {
        GspSettingGroupControlBlock* lastSgcb = self->sgcbs;

        while (lastSgcb->sibling != NULL)
            lastSgcb = lastSgcb->sibling;

        lastSgcb->sibling = sgcb;
    }
}
#endif /* (CONFIG_DLT860_SETTING_GROUPS == 1) */


static void
IedModel_addGSEControlBlock(GspIedModel* self, GspGSEControlBlock* gcb)
{
    if (self->gseCBs == NULL)
        self->gseCBs = gcb;
    else {
        GspGSEControlBlock* lastGcb = self->gseCBs;

        while (lastGcb->sibling != NULL)
            lastGcb = lastGcb->sibling;

        lastGcb->sibling = gcb;
    }
}

GspLogicalDevice*
GspLogicalDevice_create(const char* name, GspIedModel* parent)
{
    GspLogicalDevice* self = (GspLogicalDevice*) GLOBAL_CALLOC(1, sizeof(GspLogicalDevice));

    self->name = StringUtils_copyString(name);
    self->modelType = GspLogicalDeviceModelType;
    self->parent = (GspModelNode*) parent;
    self->sibling = NULL;
    self->iedName = parent->name;
    IedModel_addLogicalDevice(parent, self);

    return self;
}

static GspLogicalNode*
LogicalDevice_getLastLogicalNode(GspLogicalDevice* self)
{
    GspLogicalNode* lastNode = (GspLogicalNode*) self->firstChild;

    GspLogicalNode* nextNode = lastNode;

    while (nextNode != NULL) {
        lastNode = nextNode;
        nextNode = (GspLogicalNode*) nextNode->sibling;
    }

    return lastNode;
}

static void
LogicalDevice_addLogicalNode(GspLogicalDevice* self, GspLogicalNode* lNode)
{
    if (self->firstChild == NULL)
        self->firstChild = (GspModelNode*) lNode;
    else {
        GspLogicalNode* lastNode = LogicalDevice_getLastLogicalNode(self);

        lastNode->sibling = (GspModelNode*) lNode;
    }
}

GspLogicalNode*
GspLogicalNode_create(const char* name, GspLogicalDevice* parent)
{
    GspLogicalNode* self = (GspLogicalNode*) GLOBAL_MALLOC(sizeof(GspLogicalNode));

    self->name = StringUtils_copyString(name);
    self->parent = (GspModelNode*) parent;
    self->modelType = GspLogicalNodeModelType;
    self->firstChild = NULL;
    self->sibling = NULL;

    LogicalDevice_addLogicalNode(parent, self);

    return self;
}

static GspDataObject*
LogicalNode_getLastDataObject(GspLogicalNode* self)
{
    GspDataObject* lastNode = (GspDataObject*) self->firstChild;

    GspDataObject* nextNode = lastNode;

    while (nextNode != NULL) {
        lastNode = nextNode;
        nextNode = (GspDataObject*) nextNode->sibling;
    }

    return lastNode;

}

static void
LogicalNode_addDataObject(GspLogicalNode* self, GspDataObject* dataObject)
{
    if (self->firstChild == NULL)
        self->firstChild = (GspModelNode*) dataObject;
    else {
        GspDataObject* lastDataObject = LogicalNode_getLastDataObject(self);

        lastDataObject->sibling = (GspModelNode*) dataObject;
    }
}

static void
LogicalNode_addLog(GspLogicalNode* self, GspLog* log)
{
    GspIedModel* model = (GspIedModel*) self->parent->parent;

    IedModel_addLog(model, log);
}

GspLog*
Log_create(const char* name, GspLogicalNode* parent)
{
    GspLog* self = (GspLog*) GLOBAL_MALLOC(sizeof(GspLog));

    self->name = StringUtils_copyString(name);
    self->parent = parent;
    self->sibling = NULL;

    LogicalNode_addLog(parent, self);

    return self;
}

static void
LogicalNode_addLogControlBlock(GspLogicalNode* self, GspLogControlBlock* lcb)
{
    GspIedModel* model = (GspIedModel*) self->parent->parent;

    IedModel_addLogControlBlock(model, lcb);
}

GspLogControlBlock*
GspLogControlBlock_create(const char* name, GspLogicalNode* parent, char* dataSetName, char* logRef, uint8_t trgOps,
        uint32_t intPeriod, bool logEna, bool reasonCode)
{
    GspLogControlBlock* self = (GspLogControlBlock*) GLOBAL_MALLOC(sizeof(GspLogControlBlock));

    self->name = StringUtils_copyString(name);
    self->parent = parent;
    self->sibling = NULL;

    if (dataSetName)
        self->dataSetName = StringUtils_copyString(dataSetName);
    else
        self->dataSetName = NULL;

    if (logRef)
        self->logRef = StringUtils_copyString(logRef);
    else
        self->logRef = NULL;

    self->trgOps = trgOps;
    self->intPeriod = intPeriod;
    self->logEna = logEna;
    self->reasonCode = reasonCode;

    LogicalNode_addLogControlBlock(parent, self);

    return self;
}

static void
LogicalNode_addReportControlBlock(GspLogicalNode* self, GspReportControlBlock* rcb)
{
    GspIedModel* model = (GspIedModel*) self->parent->parent;

    IedModel_addReportControlBlock(model, rcb);
}

GspReportControlBlock*
GspReportControlBlock_create(const char* name, GspLogicalNode* parent, char* rptId, bool isBuffered, char*
        dataSetName, uint32_t confRef, uint8_t trgOps, uint8_t options, uint32_t bufTm, uint32_t intgPd)
{
    GspReportControlBlock* self = (GspReportControlBlock*) GLOBAL_MALLOC(sizeof(GspReportControlBlock));

    self->name = StringUtils_copyString(name);
    self->parent = parent;

    if (rptId)
        self->rptId = StringUtils_copyString(rptId);
    else
        self->rptId = NULL;

    self->buffered = isBuffered;

    if (dataSetName)
        self->dataSetName = StringUtils_copyString(dataSetName);
    else
        self->dataSetName = NULL;

    self->confRef = confRef;
    self->trgOps = trgOps;
    self->options = options;
    self->bufferTime = bufTm;
    self->intPeriod = intgPd;
    self->sibling = NULL;
    self->clientReservation[0] = 0; /* no pre-configured client */

    LogicalNode_addReportControlBlock(parent, self);

    return self;
}

void
GspReportControlBlock_setPreconfiguredClient(GspReportControlBlock* self, uint8_t clientType, uint8_t* clientAddress)
{
    if (clientType == 4) { /* IPv4 address */
        self->clientReservation[0] = 4;
        memcpy(self->clientReservation + 1, clientAddress, 4);
    }
    else if (clientType == 6) { /* IPv6 address */
        self->clientReservation[0] = 6;
        memcpy(self->clientReservation + 1, clientAddress, 6);
    }
    else { /* no reservation or unknown type */
        self->clientReservation[0] = 0;
    }
}

#if (CONFIG_DLT860_SETTING_GROUPS == 1)
static void
LogicalNode_addSettingGroupControlBlock(GspLogicalNode* self, GspSettingGroupControlBlock* sgcb)
{
    GspIedModel* model = (GspIedModel*) self->parent->parent;

    IedModel_addSettingGroupControlBlock(model, sgcb);
}

GspSettingGroupControlBlock*
GspSettingGroupControlBlock_create(GspLogicalNode* parent, uint8_t actSG, uint8_t numOfSGs)
{
    assert(actSG <= numOfSGs); /* actSG starting with 1 */
    assert(strcmp(parent->name, "LLN0") == 0);

    GspSettingGroupControlBlock* self = new GspSettingGroupControlBlock();

    self->parent = parent;
    self->actSG = actSG;
    self->numOfSGs = numOfSGs;
    self->editSgs.resize(numOfSGs);
    self->sibling = NULL;
    self->editSG = 0;

    LogicalNode_addSettingGroupControlBlock(parent, self);

    return self;
}
#endif /* (CONFIG_DLT860_SETTING_GROUPS == 1) */

static void
LogicalNode_addGSEControlBlock(GspLogicalNode* self, GspGSEControlBlock* gcb)
{
    GspIedModel* model = (GspIedModel*) self->parent->parent;

    IedModel_addGSEControlBlock(model, gcb);
}

GspGSEControlBlock*
GspGSEControlBlock_create(const char* name, GspLogicalNode* parent, char* appId, char* dataSet, uint32_t confRef, bool fixedOffs,
        int minTime, int maxTime)
{
    GspGSEControlBlock* self = (GspGSEControlBlock*) GLOBAL_MALLOC(sizeof(GspGSEControlBlock));

    self->name = StringUtils_copyString(name);
    self->parent = parent;

    if (appId)
        self->appId = StringUtils_copyString(appId);
    else
        self->appId = NULL;

    if (dataSet)
        self->dataSetName = StringUtils_copyString(dataSet);
    else
        self->dataSetName = NULL;

    self->confRev = confRef;
    self->fixedOffs = fixedOffs;
    self->minTime = minTime;
    self->maxTime = maxTime;

    self->address = NULL;

    self->sibling = NULL;

    if (parent != NULL)
        LogicalNode_addGSEControlBlock(parent, self);

    return self;
}

GspSVControlBlock*
GspSVControlBlock_create(const char* name, GspLogicalNode* parent, char* svID, char* dataSet, uint32_t confRev, uint8_t smpMod,
        uint16_t smpRate, uint8_t optFlds, bool isUnicast)
{
    GspSVControlBlock* self = (GspSVControlBlock*) GLOBAL_MALLOC(sizeof(GspSVControlBlock));

    self->name = StringUtils_copyString(name);
    self->parent = parent;

    self->svId = StringUtils_copyString(svID); /* Is there a default value? */

    if (dataSet)
        self->dataSetName = StringUtils_copyString(dataSet);
    else
        self->dataSetName = NULL;

    self->confRev = confRev;

    self->smpMod = smpMod;
    self->smpRate = smpRate;

    self->optFlds = optFlds;
    self->isUnicast = isUnicast;

    return self;
}

void
GspSVControlBlock_addPhyComAddress(GspSVControlBlock* self, GspPhyComAddress* phyComAddress)
{
    self->dstAddress = phyComAddress;
}

void
GspGSEControlBlock_addPhyComAddress(GspGSEControlBlock* self, GspPhyComAddress* phyComAddress)
{
    self->address = phyComAddress;
}

GspPhyComAddress*
GspPhyComAddress_create(uint8_t vlanPriority, uint16_t vlanId, uint16_t appId, uint8_t dstAddress[])
{
    GspPhyComAddress* self = (GspPhyComAddress*) GLOBAL_MALLOC(sizeof(GspPhyComAddress));

    self->vlanPriority = vlanPriority;
    self->vlanId = vlanId;
    self->appId = appId;

    memcpy(self->dstAddress, dstAddress, 6);

    return self;
}

static GspModelNode*
DataObject_getLastChild(GspDataObject* self)
{
    GspModelNode* lastNode = self->firstChild;

    GspModelNode* nextNode = lastNode;

    while (nextNode != NULL) {
        lastNode = nextNode;
        nextNode = (GspModelNode*) nextNode->sibling;
    }

    return lastNode;
}

static void
DataObject_addChild(GspDataObject* self, GspModelNode* child)
{
    if (self->firstChild == NULL)
        self->firstChild = child;
    else {
        GspModelNode* lastChild = DataObject_getLastChild(self);

        lastChild->sibling = child;
    }
}

GspDataObject*
GspDataObject_create(const char* name, GspModelNode* parent, int arrayElements, const char *cdcType)
{
    GspDataObject* self = (GspDataObject*) GLOBAL_MALLOC(sizeof(GspDataObject));

    self->name = StringUtils_copyString(name);
    self->modelType = GspDataObjectModelType;
    self->elementCount = arrayElements;
    self->firstChild = NULL;
    self->parent = parent;
    self->sibling = NULL;
    self->cdcType = StringUtils_copyString(cdcType);

    if (parent->modelType == GspLogicalNodeModelType)
        LogicalNode_addDataObject((GspLogicalNode*) parent, self);
    else if (parent->modelType == GspDataObjectModelType)
        DataObject_addChild((GspDataObject*) parent, (GspModelNode*) self);
    return self;
}

static GspModelNode*
DataAttribute_getLastChild(GspDataAttribute* self)
{
    GspModelNode* lastNode = self->firstChild;

    GspModelNode* nextNode = lastNode;

    while (nextNode != NULL) {
        lastNode = nextNode;
        nextNode = (GspModelNode*) nextNode->sibling;
    }

    return lastNode;
}

static void
DataAttribute_addChild(GspDataAttribute* self, GspModelNode* child)
{
    if (self->firstChild == NULL)
        self->firstChild = child;
    else {
        GspModelNode* lastChild = DataAttribute_getLastChild(self);

        lastChild->sibling = child;
    }
}

GspDataAttribute*
GspDataAttribute_create(const char* name, GspModelNode* parent, GspDataAttributeType type, GspFunctionalConstraint fc,
        uint8_t triggerOptions, int arrayElements, uint32_t sAddr)
{
 //   if (fc == DLT860_FC_CO)
 //   {
 //      return nullptr;
 //   }
    GspDataAttribute* self = (GspDataAttribute*) GLOBAL_MALLOC(sizeof(GspDataAttribute));

    self->name = StringUtils_copyString(name);
    self->elementCount = arrayElements;
    self->modelType = GspDataAttributeModelType;
    self->type = type;
    self->fc = fc;
    self->firstChild = NULL;
    self->mmsValue = NULL;
    self->parent = parent;
    self->sibling = NULL;
    self->triggerOptions = triggerOptions;
    self->sAddr = sAddr;

    if (parent->modelType == GspDataObjectModelType)
        DataObject_addChild((GspDataObject*) parent, (GspModelNode*) self);
    else if (parent->modelType == GspDataAttributeModelType)
        DataAttribute_addChild((GspDataAttribute*) parent, (GspModelNode*) self);

    return self;
}

GspDataSet*
GspDataSet_create(const char* name, GspLogicalNode* parent)
{
    //GspDataSet* self = (GspDataSet*) GLOBAL_MALLOC(sizeof(GspDataSet));
    auto self = new GspDataSet();

    GspLogicalDevice* ld = (GspLogicalDevice*) parent->parent;

    self->name = StringUtils_createString(3, parent->name, "$", name);
    self->elementCount = 0;
    self->sibling = NULL;
    self->logicalDeviceName = ld->name;
    self->fcdas = NULL;
    self->refer = string(ld->iedName) + ld->name + "/" + string(self->name);
    self->iedName = ld->iedName;
    for(auto &c : self->refer)
    {
        if(c == '$')
        {
            c = '.';
        }
    }

    IedModel_addDataSet((GspIedModel*) ld->parent, self);

    return self;
}

int
GspDataSet_getSize(GspDataSet* self)
{
    return self->elementCount;
}

GspDataSetEntry*
GspDataSet_getFirstEntry(GspDataSet* self)
{
    return self->fcdas;
}

GspDataSetEntry*
GspDataSetEntry_getNext(GspDataSetEntry* self)
{
    return self->sibling;
}

static void
DataSet_addEntry(GspDataSet* self, GspDataSetEntry* newEntry)
{
    self->fcdaArray.push_back(newEntry);
    self->elementCount++;

    if (self->fcdas == NULL)
        self->fcdas = newEntry;
    else {
        GspDataSetEntry* lastEntry = self->fcdas;

        while (lastEntry != NULL) {

            if (lastEntry->sibling == NULL) {
                lastEntry->sibling = newEntry;
                break;
            }

            lastEntry = lastEntry->sibling;
        }
    }
}

GspDataSetEntry*
GspDataSetEntry_create(GspDataSet* dataSet, const char* variable, int index, const char* component)
{
    GspDataSetEntry* self = (GspDataSetEntry*) GLOBAL_MALLOC(sizeof(GspDataSetEntry));

    char variableName[130];

    strncpy(variableName, variable, 129);

    char* separator = strchr(variableName, '/');

    if (separator != NULL) {
        *separator = 0;

        self->variableName = StringUtils_copyString(separator + 1);
        self->logicalDeviceName = StringUtils_copyString(variableName);
        self->isLDNameDynamicallyAllocated = true;
    }
    else {
        self->variableName = StringUtils_copyString(variable);
        self->logicalDeviceName = dataSet->logicalDeviceName;
        self->isLDNameDynamicallyAllocated = false;
    }

    if (component != NULL)
        self->componentName = StringUtils_copyString(component);
    else
        self->componentName = NULL;

    self->index = index;

    self->sibling = NULL;

    self->value = NULL;

    DataSet_addEntry(dataSet, self);

    return self;
}

static void
ModelNode_destroy(GspModelNode* modelNode, bool installCache)
{
    GspModelNode* currentChild = modelNode->firstChild;

    while (currentChild != NULL) {
        GspModelNode* nextChild = currentChild->sibling;

        ModelNode_destroy(currentChild, installCache);

        currentChild = nextChild;
    }

    if (modelNode->modelType == GspDataAttributeModelType) {
        GspDataAttribute* dataAttribute = (GspDataAttribute*) modelNode;

        if (dataAttribute->mmsValue != NULL && !installCache) {
            GspMmsValue_delete(dataAttribute->mmsValue);
            dataAttribute->mmsValue = NULL;
        }
    }
    else if(modelNode->modelType == GspDataObjectModelType)
    {
        auto dataObject = (GspDataObject*)modelNode;
        free(dataObject->cdcType);
    }
    GLOBAL_FREEMEM(modelNode->name);
    GLOBAL_FREEMEM(modelNode);
}

void
GspIedModel_destroy(GspIedModel* model)
{
    /* delete all model nodes and dynamically created strings */

    /* delete all logical devices */

    GspLogicalDevice* ld = model->firstChild;

    while (ld != NULL) {
        GLOBAL_FREEMEM (ld->name);

        GspLogicalNode* ln = (GspLogicalNode*) ld->firstChild;

        while (ln != NULL) {
            GLOBAL_FREEMEM(ln->name);

            /* delete all data objects */

            GspDataObject* currentDataObject = (GspDataObject*) ln->firstChild;

            while (currentDataObject != NULL) {
                GspDataObject* nextDataObject = (GspDataObject*) currentDataObject->sibling;

                ModelNode_destroy((GspModelNode*) currentDataObject, model->installCacheValue);

                currentDataObject = nextDataObject;
            }

            GspLogicalNode* currentLn = ln;
            ln = (GspLogicalNode*) ln->sibling;

            GLOBAL_FREEMEM(currentLn);
        }


        GspLogicalDevice* currentLd = ld;
        ld = (GspLogicalDevice*) ld->sibling;

        GLOBAL_FREEMEM(currentLd);
    }

    /*  delete all data sets */

    GspDataSet* dataSet = model->dataSets;

    while (dataSet != NULL) {
        GspDataSet* nextDataSet = dataSet->sibling;

        GLOBAL_FREEMEM(dataSet->name);

        GspDataSetEntry* dse = dataSet->fcdas;

        while (dse != NULL) {
            GspDataSetEntry* nextDse = dse->sibling;

            if (dse->componentName != NULL)
                GLOBAL_FREEMEM(dse->componentName);

            GLOBAL_FREEMEM(dse->variableName);

            if (dse->isLDNameDynamicallyAllocated)
                GLOBAL_FREEMEM(dse->logicalDeviceName);

            GLOBAL_FREEMEM(dse);

            dse = nextDse;
        }
        delete dataSet;
        //GLOBAL_FREEMEM(dataSet);

        dataSet = nextDataSet;
    }

    /* delete all RCBs */

    GspReportControlBlock* rcb = model->rcbs;

    while (rcb != NULL) {
        GspReportControlBlock* nextRcb = rcb->sibling;

        GLOBAL_FREEMEM(rcb->name);

        if (rcb->rptId)
            GLOBAL_FREEMEM(rcb->rptId);

        if (rcb->dataSetName)
            GLOBAL_FREEMEM(rcb->dataSetName);

        GLOBAL_FREEMEM(rcb);

        rcb = nextRcb;
    }

    /* delete all GoCBs */

    GspGSEControlBlock* gcb = model->gseCBs;

    while (gcb != NULL) {
        GspGSEControlBlock* nextGcb = gcb->sibling;

        GLOBAL_FREEMEM(gcb->name);
        GLOBAL_FREEMEM(gcb->appId);
        GLOBAL_FREEMEM(gcb->dataSetName);

        if (gcb->address)
            GLOBAL_FREEMEM(gcb->address);

        GLOBAL_FREEMEM(gcb);

        gcb = nextGcb;
    }

    /* delete setting controls */

    GspSettingGroupControlBlock* sgcb = model->sgcbs;

    while (sgcb != NULL) {
        GspSettingGroupControlBlock* nextSgcb = sgcb->sibling;

        delete sgcb;

        sgcb = nextSgcb;
    }

    /* delete all LCBs */
    GspLogControlBlock* lcb = model->lcbs;

    while (lcb != NULL) {
        GspLogControlBlock* nextLcb = lcb->sibling;

        if (lcb->name)
            GLOBAL_FREEMEM(lcb->name);

        if (lcb->dataSetName)
            GLOBAL_FREEMEM(lcb->dataSetName);

        if (lcb->logRef)
            GLOBAL_FREEMEM(lcb->logRef);

        GLOBAL_FREEMEM(lcb);

        lcb = nextLcb;
    }

    /* delete all LOGs */
    GspLog* log = model->logs;

    while (log != NULL) {
        GspLog* nextLog = log->sibling;

        if (log->name)
            GLOBAL_FREEMEM(log->name);

        GLOBAL_FREEMEM(log);

        log = nextLog;
    }


    /* delete generic model parts */

    if (model->name)
        GLOBAL_FREEMEM(model->name);

    GLOBAL_FREEMEM(model);

}

