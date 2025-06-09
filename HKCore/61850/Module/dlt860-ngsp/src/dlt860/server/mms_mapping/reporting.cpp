/*
 *  reporting.c
 */

#include "gsp_mms_value.h"
#include "libdlt860_platform_includes.h"
#include "mms_mapping.h"
#include "gsp_linked_list.h"
#include "stack_config.h"
#include "gsp_hal_thread.h"
#include "simple_allocator.h"
#include "mms_mapping_internal.h"
#include "mms_server_internal.h"
#include "conversions.h"
#include "reporting.h"
#include "ied_server_private.h"
#include "iso_server_private.h"
#include <string.h>
#include "nlogging.h"
#include "ReportPDU.h"
#include "dlt860_server_interface.h"
#include "xer_encoder.h"
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "mms_service_table.h"
#include "iso_server.h"


/* if not explicitly set by client "ResvTms" will be set to this value */
#define RESV_TMS_IMPLICIT_VALUE 30

#ifndef DEBUG_IED_SERVER
#define DEBUG_IED_SERVER 0
#endif

#if (CONFIG_DLT860_REPORT_SERVICE == 1)

#ifndef CONFIG_IEC61850_BRCB_WITH_RESVTMS
#define CONFIG_IEC61850_BRCB_WITH_RESVTMS 0
#endif

static GspReportBuffer*
ReportBuffer_create(int bufferSize)
{
    GspReportBuffer* self = new GspReportBuffer(bufferSize);
    return self;
}

static void
ReportBuffer_destroy(GspReportBuffer* self)
{
    delete self;
}

GspReportControl*
GspReportControl_create(bool buffered, GspLogicalNode* parentLN, int reportBufferSize, GspIedServer iedServer)
{
    GspReportControl* self = (GspReportControl*) GLOBAL_MALLOC(sizeof(GspReportControl));
    self->name = NULL;
    self->domain = NULL;
    self->parentLN = parentLN;
    self->rcbValues = NULL;
    self->confRev = NULL;
    self->subSeqVal = GspMmsValue_newUnsigned(16);
    self->segmented = false;
    self->startIndexForNextSegment = 0;
    self->enabled = false;
    self->reserved = false;
    self->buffered = buffered;
    self->isBuffering = false;
    self->isResync = false;
    self->gi = false;
    self->inclusionField = NULL;
    self->dataSet = NULL;
    self->isDynamicDataSet = false;
    self->clientConnection = NULL;
    self->intgPd = 0;
    self->sqNum = 0;
    self->nextIntgReportTime = 0;
    self->inclusionFlags = NULL;
    self->triggered = false;
    self->timeOfEntry = NULL;
    self->reservationTimeout = 0;
    self->triggerOps = 0;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    self->createNotificationsMutex = GspSemaphore_create(1);
#endif

    self->bufferedDataSetValues = NULL;
    self->valueReferences = NULL;
    self->lastEntryId = 0;
    self->resvTms = 0;

    self->server = iedServer;

    self->reportBuffer = ReportBuffer_create(reportBufferSize);

    return self;
}

static void
ReportControl_lockNotify(GspReportControl* self)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_wait(self->createNotificationsMutex);
#endif
}

static void
ReportControl_unlockNotify(GspReportControl* self)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_post(self->createNotificationsMutex);
#endif
}


static void
purgeBuf(GspReportControl* rc)
{
    if (DEBUG_IED_SERVER) printf("IED_SERVER: reporting.c: run purgeBuf\n");

    /* reset trigger */
    rc->triggered = false;

    GspReportBuffer* reportBuffer = rc->reportBuffer;
    reportBuffer->clear();
}


static void
deleteDataSetValuesShadowBuffer(GspReportControl* self)
{
    if (self->bufferedDataSetValues != NULL) {
        assert(self->dataSet != NULL);

        int dataSetSize = GspDataSet_getSize(self->dataSet);

        int i;

        for (i = 0; i < dataSetSize; i++) {
            if (self->bufferedDataSetValues[i] != NULL)
                GspMmsValue_delete(self->bufferedDataSetValues[i]);
        }

        GLOBAL_FREEMEM(self->bufferedDataSetValues);

        if (self->valueReferences != NULL)
            GLOBAL_FREEMEM(self->valueReferences);

        self->bufferedDataSetValues = NULL;
    }
}

void
GspReportControl_destroy(GspReportControl* self)
{
    if (self->rcbValues != NULL )
        GspMmsValue_delete(self->rcbValues);

    if (self->inclusionFlags != NULL)
        GLOBAL_FREEMEM(self->inclusionFlags);

    if (self->inclusionField != NULL)
        GspMmsValue_delete(self->inclusionField);

    if (self->buffered == false)
        GspMmsValue_delete(self->timeOfEntry);

    GspMmsValue_delete(self->subSeqVal);

    deleteDataSetValuesShadowBuffer(self);

    if (self->isDynamicDataSet) {
        if (self->dataSet != NULL) {
            GspMmsMapping_freeDynamicallyCreatedDataSet(self->dataSet);
            self->isDynamicDataSet = false;
            self->dataSet = NULL;
        }
    }

    ReportBuffer_destroy(self->reportBuffer);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_destroy(self->createNotificationsMutex);
#endif

    GLOBAL_FREEMEM(self->name);

    GLOBAL_FREEMEM(self);
}

GspMmsValue*
GspReportControl_getRCBValue(GspReportControl* rc, const char* elementName)
{
    if (rc->buffered) {
        if (strcasecmp(elementName, "RptID") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 0);
        else if (strcasecmp(elementName, "RptEna") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 1);
        else if (strcasecmp(elementName, "DatSet") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 2);
        else if (strcasecmp(elementName, "ConfRev") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 3);
        else if (strcasecmp(elementName, "OptFlds") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 4);
        else if (strcasecmp(elementName, "BufTm") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 5);
        else if (strcasecmp(elementName, "SqNum") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 6);
        else if (strcasecmp(elementName, "TrgOps") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 7);
        else if (strcasecmp(elementName, "IntgPd") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 8);
        else if (strcasecmp(elementName, "GI") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 9);
        else if (strcasecmp(elementName, "PurgeBuf") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 10);
        else if (strcasecmp(elementName, "EntryID") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 11);
        else if (strcasecmp(elementName, "TimeofEntry") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 12);

        if (rc->server->edition >= DLT_860_EDITION_2) {
#if (CONFIG_IEC61850_BRCB_WITH_RESVTMS == 1)
            if (strcmp(elementName, "ResvTms") == 0)
                return MmsValue_getElement(rc->rcbValues, 13);
            if (strcmp(elementName, "Owner") == 0)
                return MmsValue_getElement(rc->rcbValues, 14);
#else
            if (strcasecmp(elementName, "Owner") == 0)
                return GspMmsValue_getElement(rc->rcbValues, 13);
#endif
        }

    } else {
        if (strcasecmp(elementName, "RptID") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 0);
        else if (strcasecmp(elementName, "RptEna") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 1);
        else if (strcasecmp(elementName, "Resv") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 2);
        else if (strcasecmp(elementName, "DatSet") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 3);
        else if (strcasecmp(elementName, "ConfRev") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 4);
        else if (strcasecmp(elementName, "OptFlds") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 5);
        else if (strcasecmp(elementName, "BufTm") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 6);
        else if (strcasecmp(elementName, "SqNum") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 7);
        else if (strcasecmp(elementName, "TrgOps") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 8);
        else if (strcasecmp(elementName, "IntgPd") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 9);
        else if (strcasecmp(elementName, "GI") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 10);
        else if (strcasecmp(elementName, "Owner") == 0)
            return GspMmsValue_getElement(rc->rcbValues, 11);
    }

    return NULL ;
}

static inline void
clearInclusionFlags(GspReportControl* reportControl)
{
    int i;
    for (i = 0; i < reportControl->dataSet->elementCount; i++)
        reportControl->inclusionFlags[i] = GSP_REPORT_CONTROL_NONE;
}

static void
updateTimeOfEntry(GspReportControl* self, uint64_t currentTime)
{
    GspMmsValue* timeOfEntry = self->timeOfEntry;
    GspMmsValue_setBinaryTime(timeOfEntry, currentTime);
}

static GspDataSetEntry*
getDataSetEntryWithIndex(GspDataSetEntry* dataSet, int index)
{
    int i = 0;

    while (dataSet) {
        if (i == index)
            return dataSet;

        i++;

        dataSet = dataSet->sibling;
    }
    NLOG_ERROR("没有获取到[{}]对应的数据集ENTRY!!!!", index);
    return NULL;
}

static void
createDataSetValuesShadowBuffer(GspReportControl* rc)
{
    int dataSetSize = GspDataSet_getSize(rc->dataSet);

    GspMmsValue** dataSetValues = (GspMmsValue**) GLOBAL_CALLOC(dataSetSize, sizeof(GspMmsValue*));

    rc->bufferedDataSetValues = dataSetValues;

    rc->valueReferences = (GspMmsValue**) GLOBAL_MALLOC(dataSetSize * sizeof(GspMmsValue*));

    GspDataSetEntry* dataSetEntry = rc->dataSet->fcdas;

    int i;
    for (i = 0; i < dataSetSize; i++) {
        assert(dataSetEntry != NULL);

        rc->valueReferences[i] = dataSetEntry->value;

        dataSetEntry = dataSetEntry->sibling;
    }
}

static bool
updateReportDataset(GspMmsMapping* mapping, GspReportControl* rc, GspMmsValue* newDatSet, GspMmsServerConnection connection)
{
    bool success = false;

    GspMmsValue* dataSetValue;

    if (newDatSet != NULL) {
        if (strcmp(GspMmsValue_toString(newDatSet), "") == 0) {
            success = true;
            dataSetValue = NULL;

            if (rc->buffered) {
                rc->isBuffering = false;
                purgeBuf(rc);
            }
        }
        else
            dataSetValue = newDatSet;
    }
    else
        dataSetValue = GspReportControl_getRCBValue(rc, "DatSet");


    bool dataSetChanged = true;

    /* check if old and new data sets are the same */
    if (rc->dataSet && dataSetValue) {

        const char* dataSetLdName = rc->dataSet->logicalDeviceName;
        const char* dataSetName = rc->dataSet->name;
        const char* newDataSetName = GspMmsValue_toString(dataSetValue);

        if (newDataSetName[0] == '@') {
            if ((dataSetLdName == NULL) && (!strcmp(dataSetName, newDataSetName + 1))) {
                dataSetChanged = false;
            }
        }
        else if (newDataSetName[0] == '/') {
            if ((dataSetLdName == NULL) && (!strcmp(dataSetName, newDataSetName + 1))) {
                dataSetChanged = false;
            }
        }
        else {
            if (dataSetLdName && dataSetName) {

                char externalVisibleName[256];

                /* Construct external visible name */
                strcpy(externalVisibleName, rc->domain->modelName);
                strcat(externalVisibleName, dataSetLdName);
                strcat(externalVisibleName, "/");
                strcat(externalVisibleName, dataSetName);

                if (!(strcmp(externalVisibleName, newDataSetName))) {
                    dataSetChanged = false;
                }
            }
        }

        if (rc->buffered) {
            if (dataSetChanged)
                purgeBuf(rc);
        }
    }


    if (rc->isDynamicDataSet) {
        if (rc->dataSet && dataSetChanged) {
            deleteDataSetValuesShadowBuffer(rc);
            GspMmsMapping_freeDynamicallyCreatedDataSet(rc->dataSet);
            rc->isDynamicDataSet = false;
            rc->dataSet = NULL;
        }
    }

    if (dataSetValue && dataSetChanged) {
        const char* dataSetName = GspMmsValue_toString(dataSetValue);

        GspDataSet* dataSet = GspIedModel_lookupDataSetFromModels(mapping->modelss, dataSetName);

#if (MMS_DYNAMIC_DATA_SETS == 1)
        if (dataSet == NULL) {
            dataSet = GspMmsMapping_getDomainSpecificDataSet(mapping, dataSetName);

            if (dataSet == NULL) {

                /* check if association specific data set is requested */
                if (dataSetName[0] == '@') {

                    if (rc->buffered == false) { /* for buffered report non-permanent datasets are not allowed */
                        if (connection != NULL) {
                            GspMmsNamedVariableList mmsVariableList
                                = GspMmsServerConnection_getNamedVariableList(connection, dataSetName + 1);

                            if (mmsVariableList != NULL)
                                dataSet = GspMmsMapping_createDataSetByNamedVariableList(mapping, mmsVariableList);
                        }
                    }

                }

                /* check for VMD specific data set */
                else if (dataSetName[0] == '/') {
                    GspMmsNamedVariableList mmsVariableList = GspMmsDevice_getNamedVariableListWithName(mapping->mmsDevice, dataSetName + 1);

                    if (mmsVariableList != NULL)
                        dataSet = GspMmsMapping_createDataSetByNamedVariableList(mapping, mmsVariableList);
                }
            }

            if (dataSet == NULL)
                goto exit_function;

            rc->isDynamicDataSet = true;

        }
        else
            rc->isDynamicDataSet = false;
#else

        if (dataSet == NULL)
            goto exit_function;

#endif /* (MMS_DYNAMIC_DATA_SETS == 1) */

        if ((dataSet == NULL) || (dataSetChanged == true)) {

            /* delete pending event and create buffer for new data set */
            deleteDataSetValuesShadowBuffer(rc);

            rc->dataSet = dataSet;
            dataSet->rcSet.insert(rc);

            createDataSetValuesShadowBuffer(rc);

            if (rc->inclusionField != NULL)
                GspMmsValue_delete(rc->inclusionField);

            rc->inclusionField = GspMmsValue_newBitString(dataSet->elementCount);

            rc->triggered = false;

            if (rc->inclusionFlags != NULL)
                GLOBAL_FREEMEM(rc->inclusionFlags);

            rc->inclusionFlags = (uint8_t*) GLOBAL_CALLOC(dataSet->elementCount, sizeof(uint8_t));

        }

        success = true;

        if (rc->buffered)
            rc->isBuffering = true;

        goto exit_function;
    }
    else {
        success = true;
    }

exit_function:
    return success;
}

static char*
createDataSetReferenceForDefaultDataSet(GspReportControlBlock* rcb, GspReportControl* reportControl)
{
    char* dataSetReference;

    char* domainName = GspMmsDomain_getName(reportControl->domain);
    char* lnName = rcb->parent->name;

    dataSetReference = StringUtils_createString(5, domainName, "/", lnName, "$", rcb->dataSetName);

    return dataSetReference;
}


static GspMmsValue*
createOptFlds(GspReportControlBlock* reportControlBlock)
{
    GspMmsValue* optFlds = GspMmsValue_newBitString(10);
    uint8_t options = reportControlBlock->options;

    if (options & GSP_RPT_OPT_SEQ_NUM)
        GspMmsValue_setBitStringBit(optFlds, 1, true);
    if (options & GSP_RPT_OPT_TIME_STAMP)
        GspMmsValue_setBitStringBit(optFlds, 2, true);
    if (options & GSP_RPT_OPT_REASON_FOR_INCLUSION)
        GspMmsValue_setBitStringBit(optFlds, 3, true);
    if (options & GSP_RPT_OPT_DATA_SET)
        GspMmsValue_setBitStringBit(optFlds, 4, true);
    if (options & GSP_RPT_OPT_DATA_REFERENCE)
        GspMmsValue_setBitStringBit(optFlds, 5, true);
    if (options & GSP_RPT_OPT_BUFFER_OVERFLOW)
        GspMmsValue_setBitStringBit(optFlds, 6, true);
    if (options & GSP_RPT_OPT_ENTRY_ID)
        GspMmsValue_setBitStringBit(optFlds, 7, true);
    if (options & GSP_RPT_OPT_CONF_REV)
        GspMmsValue_setBitStringBit(optFlds, 8, true);

    return optFlds;
}

static GspMmsValue*
createTrgOps(GspReportControlBlock* reportControlBlock) {
    GspMmsValue* trgOps = GspMmsValue_newBitString(6);

    uint8_t triggerOps = reportControlBlock->trgOps;

    if (triggerOps & GSP_TRG_OPT_DATA_CHANGED)
        GspMmsValue_setBitStringBit(trgOps, 1, true);
    if (triggerOps & GSP_TRG_OPT_QUALITY_CHANGED)
        GspMmsValue_setBitStringBit(trgOps, 2, true);
    if (triggerOps & GSP_TRG_OPT_DATA_UPDATE)
        GspMmsValue_setBitStringBit(trgOps, 3, true);
    if (triggerOps & GSP_TRG_OPT_INTEGRITY)
        GspMmsValue_setBitStringBit(trgOps, 4, true);
    if (triggerOps & GSP_TRG_OPT_GI)
        GspMmsValue_setBitStringBit(trgOps, 5, true);

    return trgOps;
}

static void
refreshTriggerOptions(GspReportControl* rc)
{
    rc->triggerOps = 0;
    GspMmsValue* trgOps = GspReportControl_getRCBValue(rc, "TrgOps");
    if (GspMmsValue_getBitStringBit(trgOps, 1))
        rc->triggerOps += GSP_TRG_OPT_DATA_CHANGED;

    if (GspMmsValue_getBitStringBit(trgOps, 2))
        rc->triggerOps += GSP_TRG_OPT_QUALITY_CHANGED;

    if (GspMmsValue_getBitStringBit(trgOps, 3))
        rc->triggerOps += GSP_TRG_OPT_DATA_UPDATE;

    if (GspMmsValue_getBitStringBit(trgOps, 4))
        rc->triggerOps += GSP_TRG_OPT_INTEGRITY;

    if (GspMmsValue_getBitStringBit(trgOps, 5))
        rc->triggerOps += GSP_TRG_OPT_GI;
}

static void
refreshIntegrityPeriod(GspReportControl* rc)
{
    GspMmsValue* intgPd = GspReportControl_getRCBValue(rc, "IntgPd");
    rc->intgPd = GspMmsValue_toUint32(intgPd);

    if (rc->buffered == false)
        rc->nextIntgReportTime = GSP_Hal_getTimeInMs() + rc->intgPd;
}

static void
refreshBufferTime(GspReportControl* rc)
{
    GspMmsValue* bufTm = GspReportControl_getRCBValue(rc, "BufTm");
    rc->bufTm = GspMmsValue_toUint32(bufTm);
}

static void
composeDefaultRptIdString(char* rptIdString, GspReportControl* reportControl)
{
    int bufPos = 0;
    while (reportControl->domain->domainName[bufPos] != 0) {
        rptIdString[bufPos] = reportControl->domain->domainName[bufPos];
        bufPos++;
    }
    rptIdString[bufPos++] = '/';
    int i = 0;
    while (reportControl->name[i] != 0) {
        rptIdString[bufPos] = reportControl->name[i];
        bufPos++;
        i++;
    }
    rptIdString[bufPos] = 0;
}

static GspMmsValue*
createDefaultRptId(GspReportControl* reportControl)
{
    char rptIdString[130]; /* maximum length 129 chars */

    composeDefaultRptIdString(rptIdString, reportControl);

    return GspMmsValue_newVisibleString(rptIdString);
}

static void
updateWithDefaultRptId(GspReportControl* reportControl, GspMmsValue* rptId)
{
    char rptIdString[130]; /* maximum length 129 chars */

    composeDefaultRptIdString(rptIdString, reportControl);

    GspMmsValue_setVisibleString(rptId, rptIdString);
}

static GspMmsVariableSpecification*
createUnbufferedReportControlBlock(GspReportControlBlock* reportControlBlock,
        GspReportControl* reportControl)
{
    GspMmsVariableSpecification* rcb = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    rcb->name = StringUtils_copyString(reportControlBlock->name);
    rcb->type = GSP_MMS_STRUCTURE;

    GspMmsValue* mmsValue = (GspMmsValue*) GLOBAL_CALLOC(1, sizeof(GspMmsValue));
    mmsValue->present = Data_PR_structure;

    int structSize;

    if (reportControl->server->edition >= DLT_860_EDITION_2)
        structSize = 12;
    else
        structSize = 11;

//    mmsValue->value.structure.size = structSize;
//    mmsValue->value.structure.components = (MmsValue**) GLOBAL_CALLOC(structSize, sizeof(MmsValue*));

    rcb->typeSpec.structure.elementCount = structSize;

    rcb->typeSpec.structure.elements = (GspMmsVariableSpecification**) GLOBAL_CALLOC(structSize,
            sizeof(GspMmsVariableSpecification*));

    GspMmsVariableSpecification* namedVariable = 
			(GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("RptID");
    namedVariable->typeSpec.visibleString = -129;
    namedVariable->type = GSP_MMS_VISIBLE_STRING;
    rcb->typeSpec.structure.elements[0] = namedVariable;
    if ((reportControlBlock->rptId != NULL) && (strlen(reportControlBlock->rptId) > 0))
        ASN_SEQUENCE_ADD(&mmsValue->choice.structure, GspMmsValue_newVisibleString(
                             reportControlBlock->rptId));
    else
        ASN_SEQUENCE_ADD(&mmsValue->choice.structure, createDefaultRptId(reportControl));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("RptEna");
    namedVariable->type = GSP_MMS_BOOLEAN;
    rcb->typeSpec.structure.elements[1] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure, GspMmsValue_newBoolean(false));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("Resv");
    namedVariable->type = GSP_MMS_BOOLEAN;
    rcb->typeSpec.structure.elements[2] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure, GspMmsValue_newBoolean(false));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("DatSet");
    namedVariable->typeSpec.visibleString = -129;
    namedVariable->type = GSP_MMS_VISIBLE_STRING;
    rcb->typeSpec.structure.elements[3] = namedVariable;

    if (reportControlBlock->dataSetName != NULL) {
    	char* dataSetReference = createDataSetReferenceForDefaultDataSet(reportControlBlock,
    	            reportControl);
        ASN_SEQUENCE_ADD(&mmsValue->choice.structure, GspMmsValue_newVisibleString(dataSetReference));
    	GLOBAL_FREEMEM(dataSetReference);
    }
    else
        ASN_SEQUENCE_ADD(&mmsValue->choice.structure, GspMmsValue_newVisibleString(""));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("ConfRev");
    namedVariable->type = GSP_MMS_UINT32;
    namedVariable->typeSpec.uint32 = 32;
    rcb->typeSpec.structure.elements[4] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure, GspMmsValue_newUnsignedFromUint32(reportControlBlock->confRef));
    reportControl->confRev = mmsValue->choice.structure.list.array[4];

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("OptFlds");
    namedVariable->type = GSP_MMS_BIT_STRING;
    namedVariable->typeSpec.bitString = -10;
    rcb->typeSpec.structure.elements[5] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure, createOptFlds(reportControlBlock));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("BufTm");
    namedVariable->type = GSP_MMS_UINT32;
    namedVariable->typeSpec.uint32 = 32;
    rcb->typeSpec.structure.elements[6] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure, GspMmsValue_newUnsignedFromUint32(reportControlBlock->bufferTime));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("SqNum");
    namedVariable->type = GSP_MMS_UINT32;
    namedVariable->typeSpec.uint32 = 8;
    rcb->typeSpec.structure.elements[7] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure, GspMmsValue_newUnsigned(8));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("TrgOps");
    namedVariable->type = GSP_MMS_BIT_STRING;
    namedVariable->typeSpec.bitString = -6;
    rcb->typeSpec.structure.elements[8] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure, createTrgOps(reportControlBlock));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("IntgPd");
    namedVariable->type = GSP_MMS_UINT32;
    namedVariable->typeSpec.uint32 = 32;
    rcb->typeSpec.structure.elements[9] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure, GspMmsValue_newUnsignedFromUint32(reportControlBlock->intPeriod));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("GI");
    namedVariable->type = GSP_MMS_BOOLEAN;
    rcb->typeSpec.structure.elements[10] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure, GspMmsValue_newBoolean(false));

    if (reportControl->server->edition >= DLT_860_EDITION_2) {
        namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
        namedVariable->name = StringUtils_copyString("Owner");
        namedVariable->type = GSP_MMS_OCTET_STRING;
        namedVariable->typeSpec.octetString = -64;
        rcb->typeSpec.structure.elements[11] = namedVariable;
        ASN_SEQUENCE_ADD(&mmsValue->choice.structure, GspMmsValue_newOctetString(0, 16));

        /* initialize pre configured owner */
        if (reportControlBlock->clientReservation[0] == 4) {
            reportControl->resvTms = -1;
            GspMmsValue_setOctetString(mmsValue->choice.structure.list.array[11], reportControlBlock->clientReservation + 1, 4);
        }
        else if (reportControlBlock->clientReservation[0] == 6) {
            reportControl->resvTms = -1;
            GspMmsValue_setOctetString(mmsValue->choice.structure.list.array[11], reportControlBlock->clientReservation + 1, 16);
        }
    }

    reportControl->rcbValues = mmsValue;

    reportControl->timeOfEntry = GspMmsValue_newBinaryTime(false);

    refreshBufferTime(reportControl);
    refreshIntegrityPeriod(reportControl);
    refreshTriggerOptions(reportControl);

    return rcb;
}

static GspMmsVariableSpecification*
createBufferedReportControlBlock(GspReportControlBlock* reportControlBlock,
        GspReportControl* reportControl, GspMmsMapping* mmsMapping)
{
    GspMmsVariableSpecification* rcb = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    rcb->name = StringUtils_copyString(reportControlBlock->name);
    rcb->type = GSP_MMS_STRUCTURE;

    int brcbElementCount = 13;

    if (reportControl->server->edition >= DLT_860_EDITION_2) {

#if (CONFIG_IEC61850_BRCB_WITH_RESVTMS == 1)
        brcbElementCount++;
#endif

        brcbElementCount++;
    }

    GspMmsValue* mmsValue = (GspMmsValue*) GLOBAL_CALLOC(1, sizeof(GspMmsValue));
    mmsValue->present = Data_PR_structure;

    rcb->typeSpec.structure.elementCount = brcbElementCount;
    rcb->typeSpec.structure.elements = (GspMmsVariableSpecification**) GLOBAL_CALLOC(brcbElementCount,
            sizeof(GspMmsVariableSpecification*));

    GspMmsVariableSpecification* namedVariable = 
			(GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("RptID");
    namedVariable->typeSpec.visibleString = -129;
    namedVariable->type = GSP_MMS_VISIBLE_STRING;
    rcb->typeSpec.structure.elements[0] = namedVariable;

    if ((reportControlBlock->rptId != NULL) && (strlen(reportControlBlock->rptId) > 0))
        ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, GspMmsValue_newVisibleString(
                             reportControlBlock->rptId));
    else
        ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, createDefaultRptId(reportControl));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("RptEna");
    namedVariable->type = GSP_MMS_BOOLEAN;
    rcb->typeSpec.structure.elements[1] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, GspMmsValue_newBoolean(false));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("DatSet");
    namedVariable->typeSpec.visibleString = -129;
    namedVariable->type = GSP_MMS_VISIBLE_STRING;
    rcb->typeSpec.structure.elements[2] = namedVariable;

    if (reportControlBlock->dataSetName != NULL) {
    	char* dataSetReference = createDataSetReferenceForDefaultDataSet(reportControlBlock,
    	            reportControl);
        ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, GspMmsValue_newVisibleString(dataSetReference));
    	GLOBAL_FREEMEM(dataSetReference);
    }
    else
        ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, GspMmsValue_newVisibleString(""));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("ConfRev");
    namedVariable->type = GSP_MMS_UINT32;
    namedVariable->typeSpec.uint32 = 32;
    rcb->typeSpec.structure.elements[3] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, GspMmsValue_newUnsignedFromUint32(reportControlBlock->confRef));

    reportControl->confRev = mmsValue->choice.structure.list.array[3];

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("OptFlds");
    namedVariable->type = GSP_MMS_BIT_STRING;
    namedVariable->typeSpec.bitString = -10;
    rcb->typeSpec.structure.elements[4] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, createOptFlds(reportControlBlock));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("BufTm");
    namedVariable->type = GSP_MMS_UINT32;
    namedVariable->typeSpec.uint32 = 32;
    rcb->typeSpec.structure.elements[5] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, GspMmsValue_newUnsignedFromUint32(reportControlBlock->bufferTime));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("SqNum");
    namedVariable->type = GSP_MMS_UINT32;
    namedVariable->typeSpec.uint32 = 16;
    rcb->typeSpec.structure.elements[6] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, GspMmsValue_newUnsigned(16));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("TrgOps");
    namedVariable->type = GSP_MMS_BIT_STRING;
    namedVariable->typeSpec.bitString = -6;
    rcb->typeSpec.structure.elements[7] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, createTrgOps(reportControlBlock));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("IntgPd");
    namedVariable->type = GSP_MMS_UINT32;
    namedVariable->typeSpec.uint32 = 32;
    rcb->typeSpec.structure.elements[8] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, GspMmsValue_newUnsignedFromUint32(reportControlBlock->intPeriod));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("GI");
    namedVariable->type = GSP_MMS_BOOLEAN;
    rcb->typeSpec.structure.elements[9] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, GspMmsValue_newBoolean(false));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("PurgeBuf");
    namedVariable->type = GSP_MMS_BOOLEAN;
    rcb->typeSpec.structure.elements[10] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, GspMmsValue_newBoolean(false));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("EntryID");
    namedVariable->type = GSP_MMS_OCTET_STRING;
    namedVariable->typeSpec.octetString = 8;
    rcb->typeSpec.structure.elements[11] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, GspMmsValue_newOctetString(8, 8));

    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("TimeofEntry");
    namedVariable->type = GSP_MMS_BINARY_TIME;
    namedVariable->typeSpec.binaryTime = 6;
    rcb->typeSpec.structure.elements[12] = namedVariable;
    ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, GspMmsValue_newBinaryTime(false));

    reportControl->timeOfEntry = mmsValue->choice.structure.list.array[12];

    if (reportControl->server->edition >= DLT_860_EDITION_2) {
        int currentIndex = 13;

#if (CONFIG_IEC61850_BRCB_WITH_RESVTMS == 1)
        namedVariable = (MmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(MmsVariableSpecification));
        namedVariable->name = StringUtils_copyString("ResvTms");
        namedVariable->type = MMS_INTEGER;
        namedVariable->typeSpec.integer = 16;
        rcb->typeSpec.structure.elements[currentIndex] = namedVariable;
        mmsValue->value.structure.components[currentIndex] = MmsValue_newInteger(16);
        currentIndex++;
#endif /* (CONFIG_IEC61850_BRCB_WITH_RESVTMS == 1) */

        namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
        namedVariable->name = StringUtils_copyString("Owner");
        namedVariable->type = GSP_MMS_OCTET_STRING;
        namedVariable->typeSpec.octetString = -64;
        rcb->typeSpec.structure.elements[currentIndex] = namedVariable;
        ASN_SEQUENCE_ADD(&mmsValue->choice.structure.list, GspMmsValue_newOctetString(0, 16));

        /* initialize pre configured owner */
        if (reportControlBlock->clientReservation[0] == 4) {
            reportControl->resvTms = -1;
            GspMmsValue_setOctetString(mmsValue->choice.structure.list.array[currentIndex], reportControlBlock->clientReservation + 1, 4);
        }
        else if (reportControlBlock->clientReservation[0] == 6) {
            reportControl->resvTms = -1;
            GspMmsValue_setOctetString(mmsValue->choice.structure.list.array[currentIndex], reportControlBlock->clientReservation + 1, 16);
        }

#if (CONFIG_IEC61850_BRCB_WITH_RESVTMS == 1)
        MmsValue_setInt16(mmsValue->value.structure.components[13], reportControl->resvTms);
#endif
    }

    reportControl->rcbValues = mmsValue;

    /* get initial values from BRCB */
    refreshBufferTime(reportControl);
    refreshIntegrityPeriod(reportControl);
    refreshTriggerOptions(reportControl);

    return rcb;
} /* createBufferedReportControlBlock() */

static GspReportControlBlock*
getRCBForLogicalNodeWithIndex(GspMmsMapping* self, GspLogicalNode* logicalNode,
        int index, bool buffered)
{
    int rcbCount = 0;

    GspReportControlBlock* nextRcb = self->model->rcbs;

    while (nextRcb != NULL ) {
        if (nextRcb->parent == logicalNode) {

            if (nextRcb->buffered == buffered) {
                if (rcbCount == index)
                    return nextRcb;

                rcbCount++;
            }

        }

        nextRcb = nextRcb->sibling;
    }

    return NULL ;
}

GspMmsVariableSpecification*
GspReporting_createMmsBufferedRCBs(GspMmsMapping* self, GspMmsDomain* domain,
        GspLogicalNode* logicalNode, int reportsCount)
{
    GspMmsVariableSpecification* namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1,
            sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("BR");
    namedVariable->type = GSP_MMS_STRUCTURE;

    namedVariable->typeSpec.structure.elementCount = reportsCount;
    namedVariable->typeSpec.structure.elements = (GspMmsVariableSpecification**) GLOBAL_CALLOC(reportsCount,
            sizeof(GspMmsVariableSpecification*));

    int currentReport = 0;

    while (currentReport < reportsCount) {
        GspReportControl* rc = GspReportControl_create(true, logicalNode, self->iedServer->reportBufferSizeBRCBs, self->iedServer);

        rc->domain = domain;

        GspReportControlBlock* reportControlBlock = getRCBForLogicalNodeWithIndex(
                self, logicalNode, currentReport, true);

        rc->name = StringUtils_createString(3, logicalNode->name, "$BR$",
                reportControlBlock->name);

        namedVariable->typeSpec.structure.elements[currentReport] =
                createBufferedReportControlBlock(reportControlBlock, rc, self);

        GspLinkedList_add(self->reportControls, rc);

        currentReport++;
    }

    return namedVariable;
}

GspMmsVariableSpecification*
GspReporting_createMmsUnbufferedRCBs(GspMmsMapping* self, GspMmsDomain* domain,
        GspLogicalNode* logicalNode, int reportsCount)
{
    GspMmsVariableSpecification* namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1,
            sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("RP");
    namedVariable->type = GSP_MMS_STRUCTURE;

    namedVariable->typeSpec.structure.elementCount = reportsCount;
    namedVariable->typeSpec.structure.elements = (GspMmsVariableSpecification**) GLOBAL_CALLOC(reportsCount,
            sizeof(GspMmsVariableSpecification*));

    int currentReport = 0;

    while (currentReport < reportsCount) {
        GspReportControl* rc = GspReportControl_create(false, logicalNode, self->iedServer->reportBufferSizeURCBs, self->iedServer);

        rc->domain = domain;

        GspReportControlBlock* reportControlBlock = getRCBForLogicalNodeWithIndex(
                self, logicalNode, currentReport, false);

        rc->name = StringUtils_createString(3, logicalNode->name, "$RP$",
                reportControlBlock->name);

        namedVariable->typeSpec.structure.elements[currentReport] =
                createUnbufferedReportControlBlock(reportControlBlock, rc);

        GspLinkedList_add(self->reportControls, rc);

        currentReport++;
    }

    return namedVariable;
}

static bool
convertIPv4AddressStringToByteArray(const char* clientAddressString, uint8_t ipV4Addr[])
{
    int addrElementCount = 0;

    char* separator = (char*) clientAddressString;

    while (separator != NULL && addrElementCount < 4) {
        int intVal = atoi(separator);

        ipV4Addr[addrElementCount] = intVal;

        separator = strchr(separator, '.');

        if (separator != NULL)
            separator++; /* skip '.' character */

        addrElementCount ++;
    }

    if (addrElementCount == 4)
        return true;
    else
        return false;
}

static void
updateOwner(GspReportControl* rc, GspMmsServerConnection connection)
{
    rc->clientConnection = connection;

    if (rc->server->edition >= DLT_860_EDITION_2) {

        GspMmsValue* owner = GspReportControl_getRCBValue(rc, "Owner");

        if (owner != NULL) {

            if (connection != NULL) {
                char* clientAddressString = GspMmsServerConnection_getClientAddress(connection);

                if (DEBUG_IED_SERVER) printf("IED_SERVER: reporting.c: set owner to %s\n", clientAddressString);

                if (strchr(clientAddressString, '.') != NULL) {
                    if (DEBUG_IED_SERVER)
                        printf("IED_SERVER: reporting.c: client address is IPv4 address\n");

                    uint8_t ipV4Addr[4];

                    bool valid = convertIPv4AddressStringToByteArray(clientAddressString, ipV4Addr);

                    if (valid)
                        GspMmsValue_setOctetString(owner, ipV4Addr, 4);
                    else
                        GspMmsValue_setOctetString(owner, ipV4Addr, 0);

                }
                else {
                    uint8_t ipV6Addr[16];

                    bool valid = StringUtils_convertIPv6AdddressStringToByteArray(clientAddressString, ipV6Addr);

                    if (valid) {
                        if (DEBUG_IED_SERVER)
                            printf("IED_SERVER: reporting.c: client address is IPv6 address\n");

                        GspMmsValue_setOctetString(owner, ipV6Addr, 16);
                    }
                    else {
                        if (DEBUG_IED_SERVER)
                            printf("IED_SERVER: reporting.c: not a valid IPv6 address\n");

                        GspMmsValue_setOctetString(owner, ipV6Addr, 0);
                    }
                }
            }
            else {
                uint8_t emptyAddr[1];
                GspMmsValue_setOctetString(owner, emptyAddr, 0);
            }
        }
    }
}

static bool
checkForZeroEntryID(GspMmsValue* value)
{
    uint8_t* buffer = GspMmsValue_getOctetStringBuffer(value);

    int i = 0;

    while (i < 8) {
        if (buffer[i] != 0)
            return false;

        i++;
    }

    return true;
}

static bool
checkReportBufferForEntryID(GspReportControl* rc, GspMmsValue* value)
{
    bool retVal = false;

    for(size_t i = 0; i < rc->reportBuffer->reportQueue.size(); ++i)
    {
        auto entry = rc->reportBuffer->reportQueue[i];
        if (memcmp(entry->entryId, value->choice.octet_string.buf, 8) == 0) {

            //TODO: rc->reportBuffer->nextToTransmit = (i+1);
            rc->isResync = true;

            retVal = true;
            break;
        }
    }

    return retVal;
}

static void
increaseConfRev(GspReportControl* self)
{
    uint32_t confRev = GspMmsValue_toUint32(self->confRev);

    confRev++;

    if (confRev == 0)
        confRev = 1;

    GspMmsValue_setUint32(self->confRev, confRev);
}

static void
checkReservationTimeout(GspReportControl* rc)
{
    if (rc->enabled == false) {
        if (rc->resvTms > 0) {
            if (GSP_Hal_getTimeInMs() > rc->reservationTimeout) {
                rc->resvTms = 0;

#if (CONFIG_IEC61850_BRCB_WITH_RESVTMS == 1)
                MmsValue* resvTmsVal = ReportControl_getRCBValue(rc, "ResvTms");
                if (resvTmsVal)
                    MmsValue_setInt16(resvTmsVal, rc->resvTms);
#endif

                rc->reservationTimeout = 0;
                updateOwner(rc, NULL);
                rc->reserved = false;
            }
        }
    }
}

void
GspReportControl_readAccess(GspReportControl* rc, char* elementName)
{
    /* check reservation timeout */
    if (rc->buffered) {
        checkReservationTimeout(rc);
    }
}

static bool
isIpAddressMatchingWithOwner(GspReportControl* rc, const char* ipAddress)
{
    GspMmsValue* owner = GspReportControl_getRCBValue(rc, "Owner");

    if (owner != NULL) {

        if (strchr(ipAddress, '.') != NULL) {
            uint8_t ipV4Addr[4];

            if (convertIPv4AddressStringToByteArray(ipAddress, ipV4Addr)) {
                if (memcmp(ipV4Addr, GspMmsValue_getOctetStringBuffer(owner), 4) == 0)
                    return true;
            }
        }
        else {
            uint8_t ipV6Addr[16];

            if (StringUtils_convertIPv6AdddressStringToByteArray(ipAddress, ipV6Addr)) {
                if (memcmp(ipV6Addr, GspMmsValue_getOctetStringBuffer(owner), 16) == 0)
                    return true;
            }
            else
                return false;
        }
    }

    return false;
}

static void
reserveRcb(GspReportControl* rc,  GspMmsServerConnection connection)
{
    rc->reserved = true;
    rc->clientConnection = connection;

#if (CONFIG_IEC61850_BRCB_WITH_RESVTMS == 1)
    MmsValue* resvTmsVal = ReportControl_getRCBValue(rc, "ResvTms");
    if (resvTmsVal)
        MmsValue_setInt16(resvTmsVal, rc->resvTms);
#endif

    rc->reservationTimeout = GSP_Hal_getTimeInMs() + (RESV_TMS_IMPLICIT_VALUE * 1000);
    updateOwner(rc, connection);
}

GspMmsDataAccessError
GspReporting_RCBWriteAccessHandler(GspMmsMapping* self, GspReportControl* rc, char* elementName, GspMmsValue* value,
        GspMmsServerConnection connection)
{
    GspMmsDataAccessError retVal = GSP_DATA_ACCESS_ERROR_SUCCESS;

    ReportControl_lockNotify(rc);

    bool resvTmsAccess = false;

    /* check reservation timeout for buffered RCBs */
    if (rc->buffered) {

        checkReservationTimeout(rc);

        if (rc->resvTms == 0) {
            /* nothing to to */
        }
        else if (rc->resvTms == -1) {

            if (rc->reserved == false) {

#if (CONFIG_IEC61850_RCB_ALLOW_ONLY_PRECONFIGURED_CLIENT == 1)
                if (isIpAddressMatchingWithOwner(rc, MmsServerConnection_getClientAddress(connection))) {
                    rc->reserved = true;
                    rc->clientConnection = connection;
                }
#else
                rc->reserved = true;
                rc->clientConnection = connection;
#endif
            }
        }
        else if (rc->resvTms > 0) {
            if (rc->reserved == false) {

                if (isIpAddressMatchingWithOwner(rc, GspMmsServerConnection_getClientAddress(connection))) {
                    rc->reserved = true;
                    rc->clientConnection = connection;
                    rc->reservationTimeout = GSP_Hal_getTimeInMs() + (rc->resvTms * 1000);
                }
                else {
                    if (DEBUG_IED_SERVER)
                        printf("IED_SERVER: client IP not matching with owner\n");
                }

            }
            else {
                if (rc->clientConnection == connection) {
                    rc->reservationTimeout = GSP_Hal_getTimeInMs() + (rc->resvTms * 1000);
                }
            }
        }
    }

    if ((rc->reserved) && (rc->clientConnection != connection)) {
        retVal = GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
        goto exit_function;
    }

    if (strcasecmp(elementName, "RptEna") == 0) {

        if (value->choice.boolean == true) {

            if (rc->enabled == true) {
                retVal = GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
                goto exit_function;
            }

            if (DEBUG_IED_SERVER)
                printf("IED_SERVER: Activate report for client %s\n",
                        GspMmsServerConnection_getClientAddress(connection));

            if (updateReportDataset(self, rc, NULL, connection)) {

                if (rc->resvTms != -1)
                    updateOwner(rc, connection);

                GspMmsValue* rptEna = GspReportControl_getRCBValue(rc, "RptEna");

                GspMmsValue_update(rptEna, value);

                if (rc->buffered) {

                    if (rc->isResync == false) {
                        //TODO: rc->reportBuffer->nextToTransmit = 0;
                        rc->reportBuffer->isOverflow = true;
                    }

                    rc->isResync = false;
                }

                rc->enabled = true;
                rc->gi = false;

                refreshBufferTime(rc);
                refreshTriggerOptions(rc);
                refreshIntegrityPeriod(rc);

                rc->sqNum = 0;

                GspMmsValue* sqNum = GspReportControl_getRCBValue(rc, "SqNum");

                GspMmsValue_setUint32(sqNum, 0U);

                retVal = GSP_DATA_ACCESS_ERROR_SUCCESS;
                goto exit_function;
            }
            else {
                retVal = GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
                goto exit_function;
            }
        }
        else {
            if (rc->enabled == false)
                goto exit_function;

            if (((rc->enabled) || (rc->reserved)) && (rc->clientConnection != connection)) {
                retVal = GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
                goto exit_function;
            }

            if (DEBUG_IED_SERVER)
                printf("IED_SERVER: Deactivate report for client %s\n",
                        GspMmsServerConnection_getClientAddress(connection));

            if (rc->buffered) {
                rc->reportBuffer->isOverflow = true;
                rc->isResync = false;
            }
            else {
                if (rc->dataSet)
                    clearInclusionFlags(rc);

                /* clear report buffer */
                purgeBuf(rc);
            }

            rc->enabled = false;
        }

    }

    if (strcasecmp(elementName, "GI") == 0) {

        if(rc->clientConnection == connection)
        {
            auto ret = GspMmsValue_getBoolean(value);
            if(ret == rc->gi)
            {
                retVal = GSP_DATA_ACCESS_ERROR_SUCCESS;
                goto exit_function;
            }
        }

        if ((rc->enabled) && (rc->clientConnection == connection)) {

            if (GspMmsValue_getBoolean(value)) {
                if (rc->triggerOps & GSP_TRG_OPT_GI)
                    rc->gi = true;
            }

            retVal = GSP_DATA_ACCESS_ERROR_SUCCESS;
            goto exit_function;
        }
        else {
            retVal = GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
            goto exit_function;
        }
    }

    if (rc->enabled == false) {

        if ((rc->reserved) && (rc->clientConnection != connection)) {
            retVal = GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
            goto exit_function;
        }

        if (strcasecmp(elementName, "Resv") == 0) {
            rc->reserved = value->choice.boolean;

            if (rc->reserved == true) {
                updateOwner(rc, connection);
                rc->clientConnection = connection;
            }
            else {
                updateOwner(rc, NULL);
                rc->clientConnection = NULL;
            }

        }
        else if (strcasecmp(elementName, "PurgeBuf") == 0) {
            if (GspMmsValue_getType(value) == Data_PR_boolean) {

                if (GspMmsValue_getBoolean(value) == true) {
                    purgeBuf(rc);
                    retVal = GSP_DATA_ACCESS_ERROR_SUCCESS;
                    goto exit_function;
                }
            }

        }
        else if (strcasecmp(elementName, "DatSet") == 0) {
            GspMmsValue* datSet = GspReportControl_getRCBValue(rc, "DatSet");

            if (!GspMmsValue_equals(datSet, value)) {

                if (updateReportDataset(self, rc, value, connection)) {

                    if (rc->buffered)
                        purgeBuf(rc);

                    GspMmsValue_update(datSet, value);

                    increaseConfRev(rc);
                }
                else {
                    retVal = GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
                    goto exit_function;
                }
            }

            retVal = GSP_DATA_ACCESS_ERROR_SUCCESS;
            goto exit_function;
        }
        else if (strcasecmp(elementName, "IntgPd") == 0) {
            GspMmsValue* intgPd = GspReportControl_getRCBValue(rc, elementName);

            if (!GspMmsValue_equals(intgPd, value)) {
                GspMmsValue_update(intgPd, value);

                refreshIntegrityPeriod(rc);

                if (rc->buffered) {
                    rc->nextIntgReportTime = 0;
                    purgeBuf(rc);
                }
            }

            goto exit_function;
        }
        else if (strcasecmp(elementName, "TrgOps") == 0) {
            GspMmsValue* trgOps = GspReportControl_getRCBValue(rc, elementName);

            if (!GspMmsValue_equals(trgOps, value)) {
                GspMmsValue_update(trgOps, value);

                if (rc->buffered)
                    purgeBuf(rc);

                refreshTriggerOptions(rc);
            }

            goto exit_function;
        }
        else if (strcasecmp(elementName, "EntryID") == 0) {

            if (GspMmsValue_getOctetStringSize(value) != 8) {
                retVal = GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
                goto exit_function;
            }

            if (checkForZeroEntryID(value) == false) {

                if (!checkReportBufferForEntryID(rc, value)) {
                    rc->reportBuffer->isOverflow = true;
                    retVal = GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
                    goto exit_function;
                }

                rc->reportBuffer->isOverflow = false;
            }
            else {
                //TODO: rc->reportBuffer->nextToTransmit = 0;
                rc->reportBuffer->isOverflow = true;
                rc->isResync = false;
            }

            GspMmsValue* entryID = GspReportControl_getRCBValue(rc, elementName);
            GspMmsValue_update(entryID, value);

            goto exit_function;
        }

        else if (strcasecmp(elementName, "BufTm") == 0) {
            GspMmsValue* bufTm = GspReportControl_getRCBValue(rc, elementName);

            if (!GspMmsValue_equals(bufTm, value)) {
                GspMmsValue_update(bufTm, value);

                if (rc->buffered)
                    purgeBuf(rc);

                refreshBufferTime(rc);
            }

            goto exit_function;
        }
        else if (strcasecmp(elementName, "RptID") == 0) {
            GspMmsValue* rptId = GspReportControl_getRCBValue(rc, elementName);

            if (rc->buffered)
                purgeBuf(rc);

            if (strlen(GspMmsValue_toString(value)) == 0)
                updateWithDefaultRptId(rc, rptId);
            else
                GspMmsValue_update(rptId, value);

            goto exit_function;
        }
        else if (strcasecmp(elementName, "ResvTms") == 0) {
            if (rc->buffered) {

                resvTmsAccess = true;

                if (rc->resvTms != -1) {

                    int resvTms = GspMmsValue_toInt32(value);

                    if (resvTms >= 0) {
                        rc->resvTms = resvTms;

                        if (rc->resvTms == 0) {
                            rc->reservationTimeout = 0;
                            rc->reserved = false;
                            updateOwner(rc, NULL);
                        }
                        else {
                            rc->reservationTimeout = GSP_Hal_getTimeInMs() + (rc->resvTms * 1000);

                            reserveRcb(rc, connection);
                        }

                        GspMmsValue* resvTmsVal = GspReportControl_getRCBValue(rc, "ResvTms");

                        if (resvTmsVal != NULL)
                            GspMmsValue_update(resvTmsVal, value);
                    }
                    else
                        retVal = GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
                }
                else {
                    retVal = GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
                }

                goto exit_function;
            }
        }
        else if (strcasecmp(elementName, "ConfRev") == 0) {
            retVal = GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
            goto exit_function;
        }
        else if (strcasecmp(elementName, "SqNum") == 0) {
            retVal = GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
            goto exit_function;
        }
        else if (strcasecmp(elementName, "Owner") == 0) {
            retVal = GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
            goto exit_function;
        }
        else if (strcasecmp(elementName, "TimeofEntry") == 0) {
            retVal = GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
            goto exit_function;
        }

        GspMmsValue* rcbValue = GspReportControl_getRCBValue(rc, elementName);

        if (rcbValue != NULL)
            GspMmsValue_update(rcbValue, value);
        else {
            retVal = GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
            goto exit_function;
        }

    }
    else {
        retVal = GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
    }

exit_function:

    /* every successful write access reserves the RCB */
    if ((rc->buffered) && (retVal == GSP_DATA_ACCESS_ERROR_SUCCESS) && (resvTmsAccess == false)) {
        if (rc->resvTms == 0) {
            rc->resvTms = RESV_TMS_IMPLICIT_VALUE;

            reserveRcb(rc, connection);
        }
    }

    ReportControl_unlockNotify(rc);

    return retVal;
}

void
GspReporting_deactivateReportsForConnection(GspMmsMapping* self, GspMmsServerConnection connection)
{
    GspLinkedList reportControl = self->reportControls;
    for(auto &item : *reportControl)
    {
        GspReportControl* rc = (GspReportControl*) item;

        if (rc->clientConnection == connection) {

            rc->enabled = false;
            rc->clientConnection = NULL;

            GspMmsValue* rptEna = GspReportControl_getRCBValue(rc, "RptEna");
            GspMmsValue_setBoolean(rptEna, false);

            rc->reserved = false;

            if (rc->buffered == false) {

                GspMmsValue* resv = GspReportControl_getRCBValue(rc, "Resv");
                GspMmsValue_setBoolean(resv, false);

                if (rc->resvTms != -1)
                    updateOwner(rc, NULL);

                /* delete buffer content */
                purgeBuf(rc);
            }
            else {
                if (rc->resvTms == 0)
                    updateOwner(rc, NULL);
                else if (rc->resvTms > 0) {
                     rc->reservationTimeout = GSP_Hal_getTimeInMs() + (rc->resvTms * 1000);
                }
            }
        }
    }
}

#if (DEBUG_IED_SERVER == 1)
static void
printEnqueuedReports(ReportControl* reportControl)
{
    ReportBuffer* rb = reportControl->reportBuffer;

#if 0
    printf("IED_SERVER: --- Enqueued reports ---\n");

    if (rb->oldestReport == NULL) {
        printf("IED_SERVER:   -- no reports --\n");
    }
    else {
        ReportBufferEntry* entry = rb->oldestReport;

        while (entry != NULL) {
            printf("IED_SERVER: ");

            int i = 0;
            printf("  ");
            for (i = 0; i < 8; i++) {
                printf("%02x ", entry->entryId[i]);
            }
            printf(" at [%p] next [%p] (len=%i pos=%i)", entry, entry->next,
                    entry->entryLength, (int) ((uint8_t*) entry - rb->memoryBlock));

            if (entry == rb->lastEnqueuedReport)
                printf("   <-- lastEnqueued");

            if (entry == rb->nextToTransmit)
                printf("   <-- nexttoTransmit");

            printf("\n");

            entry = entry->next;
        }
    }
#endif
    printf("IED_SERVER:   BRCB %s reports: %zu\n", reportControl->name, rb->reportQueue.size());
    printf("IED_SERVER: -------------------------\n");
}

static void
printReportId(ReportBufferEntry* report)
{
    int i = 0;
    for (i = 0; i < 8; i++) {
        printf("%02x ", report->entryId[i]);
    }
}
#endif


static void
removeAllGIReportsFromReportBuffer(GspReportBuffer* reportBuffer)
{
    GspReportBufferEntry* currentReport = nullptr;
    for(size_t i = 0; i < reportBuffer->reportQueue.size(); ++i)
    {
        if(reportBuffer->reportQueue[i])
        {
            currentReport = reportBuffer->reportQueue[i];
            if(currentReport->flags & 2)
            {
#if (DEBUG_IED_SERVER == 1)
                printf("IED_SERVER:   REMOVE old GI report with ID ");
                printReportId(currentReport);
                printf("\n");
#endif
                delete currentReport;
                reportBuffer->reportQueue[i] = nullptr;
            }
        }
    }
}

static void
enqueueReport(GspReportControl* reportControl, bool isIntegrity, bool isGI, uint64_t timeOfEntry)
{
//    if (is_debug())
//        printf("IED_SERVER: enqueueReport: RCB name: %s (SQN:%u) enabled:%i buffered:%i buffering:%i intg:%i GI:%i\n",
//            reportControl->name, (unsigned) reportControl->sqNum, reportControl->enabled,
//            reportControl->isBuffering, reportControl->buffered, isIntegrity, isGI);

    bool isBuffered = reportControl->buffered;
    bool overflow = false;

    updateTimeOfEntry(reportControl, GSP_Hal_getTimeInMs());

    int inclusionBitStringSize = GspMmsValue_getBitStringSize(reportControl->inclusionField);

    GspReportBuffer* buffer = reportControl->reportBuffer;

    GspSemaphore_wait(buffer->lock);

    if (isBuffered) {
        /* remove old buffered GI reports */
        if (isGI) removeAllGIReportsFromReportBuffer(buffer);
    }

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: number of reports in report buffer: %zu\n", buffer->reportQueue.size());

    // 如果队列满了，则移除队首的报告
    if(size_t(buffer->maxReportSize - 1) == buffer->reportQueue.size())
    {
        auto entry = buffer->reportQueue.front();

#if (DEBUG_IED_SERVER == 1)
        printf("IED_SERVER: REMOVE report with ID ");
        printReportId(entry);
        printf("\n");
#endif
        delete entry;
        buffer->reportQueue.pop_front();
        buffer->isOverflow = true;

    }
    auto entry = new GspReportBufferEntry();
    buffer->reportQueue.push_back(entry);

    entry->timeOfEntry = timeOfEntry;

    if (isBuffered) {
        /* ENTRY_ID is set to system time in ms! */
        uint64_t entryId = timeOfEntry;

        if (entryId <= reportControl->lastEntryId)
            entryId = reportControl->lastEntryId + 1;

    #if (ORDER_LITTLE_ENDIAN == 1)
        memcpyReverseByteOrder(entry->entryId, (uint8_t*) &entryId, 8);
    #else
        memcpy (entry->entryId, (uint8_t*) &entryId, 8);
    #endif
        if (reportControl->enabled == false) {
            GspMmsValue* entryIdValue = GspMmsValue_getElement(reportControl->rcbValues, 11);
            GspMmsValue_setOctetString(entryIdValue, (uint8_t*) entry->entryId, 8);
        }

        reportControl->lastEntryId = entryId;
    }

    if (isIntegrity)
        entry->flags = 1;
    else if (isGI)
        entry->flags = 2;
    else
        entry->flags = 0;

    GspDataSetEntry* dataSetEntry = reportControl->dataSet->fcdas;
    if (isIntegrity || isGI) {

        /* encode DATA */
        int i;

        for (i = 0; i < inclusionBitStringSize; i++) {

            auto member = (ReportPDU__entry__entryData__Member*)calloc(1, sizeof(ReportPDU__entry__entryData__Member));

            if (dataSetEntry->value) {
                member->id = i + 1;
                auto entryInfo = getDataSetEntryWithIndex(dataSetEntry, i);
                GspMmsValue_update(&member->value, entryInfo->value);

                string fc;
                string refer;
                splitFcFromReference(entryInfo->variableName, fc, refer);
                refer = fmt::format("{}/{}", reportControl->domain->domainName, refer);
                toDotReference(refer);
                member->reference = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, refer.c_str(), -1);
                member->fc = OCTET_STRING_new_fromBuf(&asn_DEF_FunctionalConstraint, fc.c_str(), -1);

                member->reason = (ReasonCode_t*)calloc(1, sizeof(ReasonCode_t));
                GspBIT_STRING_createBitString(member->reason, nullptr, 1, 1);
                GspBIT_STRING_setBit(member->reason, isGI ? ReasonCode_general_interrogation : ReasonCode_integrity, true);

                entry->data.push_back(member);
            }
            else {
                member->id = i + 1;

                GspMmsValue _errVal;
                _errVal.present = Data_PR_array;
                _errVal.choice.error = GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
                GspMmsValue_update(&member->value, dataSetEntry->value);

                auto entryInfo = getDataSetEntryWithIndex(dataSetEntry, i);
                string fc;
                string refer;
                splitFcFromReference(entryInfo->variableName, fc, refer);
                refer = fmt::format("{}/{}", reportControl->domain->domainName, refer);
                toDotReference(refer);
                NLOG_ERROR("没有获取到报告ENTRY数据，refer为[{}]", refer);
                member->reference = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, refer.c_str(), -1);
                member->fc = OCTET_STRING_new_fromBuf(&asn_DEF_FunctionalConstraint, fc.c_str(), -1);

                member->reason = (ReasonCode_t*)calloc(1, sizeof(ReasonCode_t));
                GspBIT_STRING_createBitString(member->reason, nullptr, 1, 1);
                GspBIT_STRING_setBit(member->reason, isGI ? ReasonCode_general_interrogation : ReasonCode_integrity, true);

                entry->data.push_back(member);
            }

        }

    } else {

        /* encode DATA */
        int i;

        for (i = 0; i < inclusionBitStringSize; i++) {

            if (reportControl->inclusionFlags[i] != GSP_REPORT_CONTROL_NONE) {
                auto member = (ReportPDU__entry__entryData__Member*)calloc(1, sizeof(ReportPDU__entry__entryData__Member));
                member->id = i + 1;
                GspMmsValue_update(&member->value, reportControl->bufferedDataSetValues[i]);
                auto entryInfo = getDataSetEntryWithIndex(dataSetEntry, i);
                string fc;
                string refer;
                splitFcFromReference(entryInfo->variableName, fc, refer);
                refer = fmt::format("{}/{}", reportControl->domain->domainName, refer);
                toDotReference(refer);
                member->reference = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, refer.c_str(), -1);
                member->fc = OCTET_STRING_new_fromBuf(&asn_DEF_FunctionalConstraint, fc.c_str(), -1);
                member->reason = (ReasonCode_t*)calloc(1, sizeof(ReasonCode_t));
                GspBIT_STRING_createBitString(member->reason, nullptr, 1, 1);

                int reasonCode = 0;
                int flag = reportControl->inclusionFlags[i];
                while(flag)
                {
                    flag = flag >> 1;
                    reasonCode += 1;
                }
                GspBIT_STRING_setBit(member->reason, reasonCode, true);
                entry->data.push_back(member);
            }

        }
    }

    clearInclusionFlags(reportControl);

#if (DEBUG_IED_SERVER == 1)
    printEnqueuedReports(reportControl);
#endif

    if (overflow) {
        /* TODO call user callback handler */
    }

    if(is_debug() && isGI)
    {

        FILE *file = fopen("gireport_record.log", "a+");
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S--------------------------------------------------------");
        auto str = oss.str();
        auto clientConn = Gsp_private_IedServer_getClientConnectionByHandle(reportControl->server, reportControl->clientConnection);

        fprintf(file, "%s %s\n", GspClientConnection_getPeerAddress(clientConn), str.c_str());
        for(auto &&entryItem : entry->data)
        {
            fprintf(file, "id:    %d\n", entryItem->id);
            fprintf(file, "refer: %s\n", entryItem->reference->buf);
            fprintf(file, "fc:    %s\n", entryItem->fc->buf);
            fprintf(file, "data:  \n");
            xer_fprint(file, &asn_DEF_Data, &entryItem->value);

            fprintf(file, "\n--\n");
        }
        fprintf(file, "----------------------------------------------------------------------------------\n\n");
        fclose(file);
    }
    GspSemaphore_post(buffer->lock);

    return;
} /* enqueuReport() */

static bool
sendNextReportEntrySegment(GspReportControl* self)
{
    if (self->clientConnection == NULL)
        return false;

    bool isBuffered = self->buffered;

    if (self->reportBuffer->first() == NULL) {
        return false;
    }
    auto pduData = (ReportPDU_t *)calloc(1, sizeof(ReportPDU_t));
    ReportPDU_t &pdu = *pduData;
    int estimatedSegmentSize = 19; /* maximum size of header information (header can have 13-19 byte) */
    estimatedSegmentSize += 8; /* reserve space for more-segments-follow (3 byte) and sub-seq-num (3-5 byte) */

    bool segmented = self->segmented;
    bool moreFollows = false;

    bool hasSeqNum = false;
    bool hasDataSetReference = false;
    bool hasBufOvfl = false;
    bool hasEntryId = false;
    bool hasConfRev = false;

    auto report = self->reportBuffer->first();

    if (isBuffered) {
        GspMmsValue* entryIdValue = GspMmsValue_getElement(self->rcbValues, 11);
        GspMmsValue_setOctetString(entryIdValue, (uint8_t*) report->entryId, 8);
    }

    GspMmsValue* rptId = GspReportControl_getRCBValue(self, "RptID");
    OCTET_STRING_fromString(&pdu.rptID, (const char *)rptId->choice.visible_string.buf);

    GspMmsValue* optFlds = GspReportControl_getRCBValue(self, "OptFlds");

    if (isBuffered == false) {
        /* delete option fields for unrelated options (not present in unbuffered report) */
        GspMmsValue_setBitStringBit(optFlds, 6, false); /* bufOvfl */
        GspMmsValue_setBitStringBit(optFlds, 7, false); /* entryID */
    }

    GspMmsValue_setBitStringBit(optFlds, 9, false); /* segmentation */

    GspMmsValue* sqNum = GspReportControl_getRCBValue(self, "SqNum");
    pdu.sqNum = (INT16U_t *)calloc(1, sizeof(INT16U_t));
    *pdu.sqNum = sqNum->choice.int16u;

    if (GspMmsValue_getBitStringBit(optFlds, 1)) { /* sequence number */
        hasSeqNum = true;
    }


    if (GspMmsValue_getBitStringBit(optFlds, 2)) { /* report time stamp */
        pdu.entry.timeOfEntry = (EntryTime_t *)calloc(1, sizeof(EntryTime_t));
        BinaryTime_newTimeFromTimeStamp(pdu.entry.timeOfEntry, report->timeOfEntry);
    }

    GspMmsValue* datSet = GspReportControl_getRCBValue(self, "DatSet");

    if (GspMmsValue_getBitStringBit(optFlds, 4)) {/* data set reference */
        hasDataSetReference = true;
        string dotDataSet = (const char *)datSet->choice.visible_string.buf;
        toDotReference(dotDataSet);
        pdu.datSet = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, dotDataSet.c_str(), -1);
    }

    if (isBuffered) {
        if (GspMmsValue_getBitStringBit(optFlds, 6)) { /* bufOvfl */
            hasBufOvfl = true;
            pdu.bufOvfl = (BOOLEAN_t *)calloc(1, sizeof(BOOLEAN_t));
            *pdu.bufOvfl = self->reportBuffer->isOverflow;
        }
    }

    if (isBuffered) {
        if (GspMmsValue_getBitStringBit(optFlds, 7)) { /* entryID */
            hasEntryId = true;
            pdu.entry.entryID = OCTET_STRING_new_fromBuf(&asn_DEF_EntryID, (const char *)report->entryId, 8);
        }
    }

    if (GspMmsValue_getBitStringBit(optFlds, 8)) {
        hasConfRev = true;
        pdu.confRev = (INT32U_t*)calloc(1, sizeof(INT32U_t));
        *pdu.confRev = self->confRev->choice.int32u;
    }

    GspMmsValue _moreFollows;
    _moreFollows.present = Data_PR_boolean;
    _moreFollows.choice.boolean = false;

    GspMmsValue* subSeqNum = self->subSeqVal;

    for(size_t i = 0; i < report->data.size(); ++i)
    {
        if(i >= 100)
        {
            segmented = true;
            moreFollows = true;
            _moreFollows.choice.boolean = true;
            GspMmsValue_setUint32(subSeqNum, 0);
            GspMmsValue_setBitStringBit(optFlds, 9, segmented); /* set segmentation flag */
            self->segmented = segmented;
            report->data.erase(report->data.begin(), report->data.begin() + 100);
            break;
        }
        else
        {
            ASN_SEQUENCE_ADD(&pdu.entry.entryData, report->data[i]);            
        }
    }

    if(!moreFollows)
    {
        report->data.clear();
    }

    GspFillMmsValueToBitString(pdu.optFlds, optFlds);
    /* encode the report message */

    ReportControl_unlockNotify(self);

    GspIsoConnection_lock(self->clientConnection->isoConnection);

    GspByteBuffer* reportBuffer = MmsServer_reserveTransmitBuffer(self->server->mmsServer);
    reportBuffer->size = 6;

    if(g_dataDumpCb)
    {
        NLOG_DEBUG("开始数据回调...\n");
        uint64_t connId = GspIsoConnection_getConnectID(self->clientConnection->isoConnection);
        string sId = fmt::format("{}", connId);
        string data;
        xer_encode(&asn_DEF_ReportPDU, &pdu, XER_F_BASIC, xer_dump_to_string, &data);
        g_dataDumpCb(sId.c_str(), data.c_str(), GSP_SC_Report);
    }

    asn_enc_rval_t dVal = aper_encode_to_buffer((const asn_TYPE_descriptor_t *)&asn_DEF_ReportPDU, NULL, &pdu, reportBuffer->buffer + 6, reportBuffer->maxSize - 6);
    ASN_STRUCT_FREE(asn_DEF_ReportPDU, pduData);
    if(dVal.encoded <= 0)
    {
        NLOG_WARN("编码报告{}错误，错误返回{}", self->name, dVal.encoded);
    }
    else
    {
        reportBuffer->size += (dVal.encoded / 8);
        if(dVal.encoded % 8 > 0) {
            reportBuffer->size += 1;
        }
        IsoConnection_sendGspReport(self->clientConnection->isoConnection, reportBuffer);
    }

    MmsServer_releaseTransmitBuffer(self->server->mmsServer);

    GspIsoConnection_unlock(self->clientConnection->isoConnection);

    if(dVal.encoded <= 0)
    {
    delete report;
        self->reportBuffer->reportQueue.pop_front();
        return false;
    }
    if (moreFollows == false) {
        /* reset sub sequence number */
        segmented = false;
        self->startIndexForNextSegment = 0;
    }
    else {
        /* increase sub sequence number */
        uint32_t subSeqNumVal = GspMmsValue_toUint32(subSeqNum);
        subSeqNumVal++;
        GspMmsValue_setUint32(subSeqNum, subSeqNumVal);
    }

    if (segmented == false) {
        delete report;
        self->reportBuffer->reportQueue.pop_front();

    #if (DEBUG_IED_SERVER == 1)
        printf("IED_SERVER: reporting.c nextToTransmit: %p\n", self->reportBuffer->first());
        printEnqueuedReports(self);
    #endif

        /* Increase sequence number */
        self->sqNum++;

        if (isBuffered == false) {
            /* Unbuffered reporting --> sqNum is 8 bit only!!! */
            if (self->sqNum == 256)
                self->sqNum = 0;
        }

        GspMmsValue_setUint16(sqNum, self->sqNum);

        if (self->reportBuffer->isOverflow)
            self->reportBuffer->isOverflow = false;
    }

    self->segmented = segmented;
    return moreFollows;
}

static void
sendNextReportEntry(GspReportControl* self)
{
    GspSemaphore_wait(self->reportBuffer->lock);

    int messageCount = 0;

    while (self->reportBuffer->first()) {
        messageCount++;
        while (sendNextReportEntrySegment(self)) {
            messageCount++;
        }

        if (messageCount > 100)
            break;
    }

    GspSemaphore_post(self->reportBuffer->lock);
}

void
GspReporting_activateBufferedReports(GspMmsMapping* self)
{
    GspLinkedList element = self->reportControls;
    for(auto &item : *element)
    {
        GspReportControl* rc = (GspReportControl*) item;

        if (rc->buffered) {
            if (updateReportDataset(self, rc, NULL, NULL))
                rc->isBuffering = true;
            else
                rc->isBuffering = false;
        }
    }
}

static void
processEventsForReport(GspReportControl* rc, uint64_t currentTimeInMs)
{
    if ((rc->enabled) || (rc->isBuffering)) {

        if (rc->triggerOps & GSP_TRG_OPT_GI) {
            if (rc->gi) {

                /* send current events in event buffer before GI report */
                if (rc->triggered) {
                    rc->triggered = false;
                    enqueueReport(rc, false, false, currentTimeInMs);
                }

                enqueueReport(rc, false, true, currentTimeInMs);

                rc->gi = false;

                rc->triggered = false;
            }
        }

        if (rc->triggerOps & GSP_TRG_OPT_INTEGRITY) {

            if (rc->intgPd > 0) {
                if (currentTimeInMs >= rc->nextIntgReportTime) {

                    /* send current events in event buffer before integrity report */
                    if (rc->triggered) {
                        enqueueReport(rc, false, false, currentTimeInMs);
                        rc->triggered = false;
                    }

                    rc->nextIntgReportTime = currentTimeInMs + rc->intgPd;

                    enqueueReport(rc, true, false, currentTimeInMs);

                    rc->triggered = false;
                }
            }
        }

        if (rc->triggered) {
            if (currentTimeInMs >= rc->reportTime) {

                enqueueReport(rc, false, false, currentTimeInMs);

                rc->triggered = false;
            }
        }
    }
}

void
GspReporting_processReportEvents(GspMmsMapping* self, uint64_t currentTimeInMs)
{
    if (self->isModelLocked == false) {

        GspLinkedList element = self->reportControls;
        for(auto &item : *element)
        {
            GspReportControl* rc = (GspReportControl*) item;

            ReportControl_lockNotify(rc);

            processEventsForReport(rc, currentTimeInMs);

            ReportControl_unlockNotify(rc);
        }
    }
}

/*
 * To be called only by connection thread!
 */
void
GspReporting_sendReports(GspMmsMapping* self, GspMmsServerConnection connection)
{
    for(auto &item : *(self->reportControls))
    {
        GspReportControl* rc = (GspReportControl*) item;
        if (rc->clientConnection == connection) {

            ReportControl_lockNotify(rc);

            if (rc->enabled) {
                sendNextReportEntry(rc);
            }

            ReportControl_unlockNotify(rc);
        }

    }
}

static inline void
copySingleValueToReportBuffer(GspReportControl* self, int dataSetEntryIndex)
{
    if (self->bufferedDataSetValues[dataSetEntryIndex] == NULL)
        self->bufferedDataSetValues[dataSetEntryIndex] = GspMmsValue_clone(self->valueReferences[dataSetEntryIndex]);
    else
        GspMmsValue_update(self->bufferedDataSetValues[dataSetEntryIndex], self->valueReferences[dataSetEntryIndex]);
}

static void
copyValuesToReportBuffer(GspReportControl* self)
{
    int i;
    for (i = 0; i < self->dataSet->elementCount; i++) {
        if (self->inclusionFlags[i] & GSP_REPORT_CONTROL_NOT_UPDATED) {
            copySingleValueToReportBuffer(self, i);

            /* clear not-updated flag */
            self->inclusionFlags[i] &= (~GSP_REPORT_CONTROL_NOT_UPDATED);
        }
    }
}

/* check if report have to be sent after data model update */
void
GspReporting_processReportEventsAfterUnlock(GspMmsMapping* self)
{
    GspLinkedList element = self->reportControls;

    uint64_t currentTime = GSP_Hal_getTimeInMs();
    for(auto &item : *element)
    {
        GspReportControl* rc = (GspReportControl*) item;

        ReportControl_lockNotify(rc);

        if ((rc->enabled) || (rc->isBuffering)) {

            if (rc->triggered) {
                copyValuesToReportBuffer(rc);

                processEventsForReport(rc, currentTime);
            }

        }

        ReportControl_unlockNotify(rc);
    }
}

void
GspReportControl_valueUpdated(GspReportControl* self, int dataSetEntryIndex, int flag, bool modelLocked)
{
    ReportControl_lockNotify(self);

    if (self->inclusionFlags[dataSetEntryIndex] & flag) { /* report for this data set entry is already pending (bypass BufTm) */
        self->reportTime = GSP_Hal_getTimeInMs();

        if (modelLocked) {
            /* buffer all relevant values */
            copyValuesToReportBuffer(self);
        }

        processEventsForReport(self, self->reportTime);
    }

    if (modelLocked) {
        /* set flag to update values when report is to be sent or data model unlocked */
        self->inclusionFlags[dataSetEntryIndex] = self->inclusionFlags[dataSetEntryIndex] | flag | GSP_REPORT_CONTROL_NOT_UPDATED;

    }
    else {
        self->inclusionFlags[dataSetEntryIndex] = flag;

        /* buffer value for report */
        copySingleValueToReportBuffer(self, dataSetEntryIndex);
    }

    if (self->triggered == false) {
        uint64_t currentTime = GSP_Hal_getTimeInMs();

        GspMmsValue_setBinaryTime(self->timeOfEntry, currentTime);

        self->reportTime = currentTime + self->bufTm;
    }

    self->triggered = true;

    ReportControl_unlockNotify(self);
}

#endif /* (CONFIG_DLT860_REPORT_SERVICE == 1) */

void GspReportBuffer::clear()
{
    for(auto &item : reportQueue)
    {
        delete item;
    }
    reportQueue.clear();
}

GspReportBuffer::GspReportBuffer(int maxSize) : isOverflow(false)
  , maxReportSize(maxSize)
  , lock(GspSemaphore_create(1))
{

}

GspReportBuffer::~GspReportBuffer()
{
    GspSemaphore_destroy(lock);
    clear();
}
