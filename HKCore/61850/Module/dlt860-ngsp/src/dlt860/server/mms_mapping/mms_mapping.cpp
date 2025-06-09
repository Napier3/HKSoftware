/*
 *  mms_mapping.c
 */

#include "libdlt860_platform_includes.h"
#include "mms_mapping.h"
#include "mms_mapping_internal.h"
#include "mms_server_internal.h"
#include "sgstorage.h"
#include "stack_config.h"
#include "mms_goose.h"
#include "mms_sv.h"
#include "reporting.h"
#include "logging.h"
#include "control.h"
#include "ied_server_private.h"
#include "nlogging.h"
#include "mms_server_func.h"
#include "mms_server_libinternal.h"
#include "dlt860_common.h"
#include "dlt860_server_interface.h"

#include <filesystem>

#ifndef CONFIG_IEC61850_SG_RESVTMS
#define CONFIG_IEC61850_SG_RESVTMS 100
#endif

#ifndef DEBUG_IED_SERVER
#define DEBUG_IED_SERVER 0
#endif

namespace fs = std::filesystem;

typedef struct
{
    GspDataAttribute* attribute;
    GspWriteAccessHandler handler;
    void* parameter;
} AttributeAccessHandler;

#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
GspMmsValue*
Control_readAccessControlObject(GspMmsMapping* self, GspMmsDomain* domain, char* variableIdOrig, GspMmsServerConnection connection);
#endif

void /* Create PHYCOMADDR ACSI type instance */
GspMmsMapping_createPhyComAddrStructure(GspMmsVariableSpecification* namedVariable)
{
    namedVariable->type = GSP_MMS_STRUCTURE;
    namedVariable->typeSpec.structure.elementCount = 4;
    namedVariable->typeSpec.structure.elements = (GspMmsVariableSpecification**) GLOBAL_CALLOC(4, sizeof(GspMmsVariableSpecification*));

    GspMmsVariableSpecification* element;

    element = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    element->name = StringUtils_copyString("Addr");
    element->type = GSP_MMS_OCTET_STRING;
    element->typeSpec.octetString = 6;
    namedVariable->typeSpec.structure.elements[0] = element;

    element = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    element->name = StringUtils_copyString("PRIORITY");
    element->type = GSP_MMS_UINT8;
    element->typeSpec.uint8 = 8;
    namedVariable->typeSpec.structure.elements[1] = element;

    element = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    element->name = StringUtils_copyString("VID");
    element->type = GSP_MMS_UINT16;
    element->typeSpec.uint16 = 16;
    namedVariable->typeSpec.structure.elements[2] = element;

    element = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    element->name = StringUtils_copyString("APPID");
    element->type = GSP_MMS_UINT16;
    element->typeSpec.uint16 = 16;
    namedVariable->typeSpec.structure.elements[3] = element;
}

static GspMmsVariableSpecification* createNamedVariableFromDataAttribute(GspDataAttribute* attribute)
{
    GspMmsVariableSpecification* origNamedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    origNamedVariable->name = StringUtils_copyString(attribute->name);

    GspMmsVariableSpecification* namedVariable = origNamedVariable;

    if (attribute->elementCount > 0) {
        namedVariable->type = GSP_MMS_ARRAY;
        namedVariable->typeSpec.array.elementCount = attribute->elementCount;
        namedVariable->typeSpec.array.elementTypeSpec = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
        namedVariable = namedVariable->typeSpec.array.elementTypeSpec;
    }

    if (attribute->firstChild != nullptr) {
        namedVariable->type = GSP_MMS_STRUCTURE;

        int componentCount = GspModelNode_getChildCount((GspModelNode*) attribute);

        namedVariable->typeSpec.structure.elements = (GspMmsVariableSpecification**) GLOBAL_CALLOC(componentCount, sizeof(GspMmsVariableSpecification*));

        GspDataAttribute* subDataAttribute = (GspDataAttribute*) attribute->firstChild;

        int i = 0;
        while (subDataAttribute != nullptr) {
            namedVariable->typeSpec.structure.elements[i] =
                    createNamedVariableFromDataAttribute(subDataAttribute);

            subDataAttribute = (GspDataAttribute*) subDataAttribute->sibling;
            i++;
        }

        namedVariable->typeSpec.structure.elementCount = i;
    }
    else {
        switch (attribute->type) {
        case DLT860_BOOLEAN:
            namedVariable->type = GSP_MMS_BOOLEAN;
            break;
        case DLT860_INT8:
            namedVariable->type = GSP_MMS_INT8;
            break;
        case DLT860_INT16:
            namedVariable->type = GSP_MMS_INT16;
            break;
        case DLT860_INT32:
            namedVariable->type = GSP_MMS_INT32;
            break;
        case DLT860_INT64:
            namedVariable->type = GSP_MMS_INT64;
            break;
            //        case IEC61850_INT128:
            //            namedVariable->type = MMS_INT128;
            //            break;
        case DLT860_INT8U:
            namedVariable->type = GSP_MMS_UINT8;
            break;
        case DLT860_INT16U:
            namedVariable->type = GSP_MMS_UINT16;
            break;
            //        case IEC61850_INT24U:
            //            namedVariable->type = MMS_UNSIGNED;
            //            break;
        case DLT860_INT32U:
            namedVariable->type = GSP_MMS_UINT32;
            break;
        case DLT860_FLOAT32:
            namedVariable->typeSpec.floatingpoint.formatWidth = 32;
            namedVariable->typeSpec.floatingpoint.exponentWidth = 8;
            namedVariable->type = GSP_MMS_FLOAT32;
            break;
        case DLT860_FLOAT64:
            namedVariable->typeSpec.floatingpoint.formatWidth = 64;
            namedVariable->typeSpec.floatingpoint.exponentWidth = 11;
            namedVariable->type = GSP_MMS_FLOAT64;
            break;
        case DLT860_ENUMERATED:
            namedVariable->type = GSP_MMS_ENUM;
            break;
        case DLT860_CHECK:
            namedVariable->typeSpec.bitString = -2;
            namedVariable->type = GSP_MMS_CHECK;
            break;
        case DLT860_CODEDENUM:
            namedVariable->typeSpec.bitString = 2;
            namedVariable->type = GSP_MMS_BIT_STRING;
            break;
        case DLT860_OCTET_STRING_6:
            namedVariable->typeSpec.octetString = -6;
            namedVariable->type = GSP_MMS_OCTET_STRING;
            break;
        case DLT860_OCTET_STRING_8:
            namedVariable->typeSpec.octetString = 8;
            namedVariable->type = GSP_MMS_OCTET_STRING;
            break;
        case DLT860_OCTET_STRING_64:
            namedVariable->typeSpec.octetString = -64;
            namedVariable->type = GSP_MMS_OCTET_STRING;
            break;
        case DLT860_CURRENCY:  /* mapping of Currency BasicType (see tissue 1047) */
            namedVariable->typeSpec.visibleString = -3;
            namedVariable->type = GSP_MMS_VISIBLE_STRING;
            break;
        case DLT860_VISIBLE_STRING_32:
            namedVariable->typeSpec.visibleString = -32;
            namedVariable->type = GSP_MMS_VISIBLE_STRING;
            break;
        case DLT860_VISIBLE_STRING_64:
            namedVariable->typeSpec.visibleString = -64;
            namedVariable->type = GSP_MMS_VISIBLE_STRING;
            break;
        case DLT860_VISIBLE_STRING_65:
            namedVariable->typeSpec.visibleString = -65;
            namedVariable->type = GSP_MMS_VISIBLE_STRING;
            break;
        case DLT860_VISIBLE_STRING_129:
            namedVariable->typeSpec.visibleString = -129;
            namedVariable->type = GSP_MMS_VISIBLE_STRING;
            break;
        case DLT860_VISIBLE_STRING_255:
            namedVariable->typeSpec.visibleString = -255;
            namedVariable->type = GSP_MMS_VISIBLE_STRING;
            break;
        case DLT860_UNICODE_STRING_255:
            namedVariable->typeSpec.visibleString = -255;
            namedVariable->type = GSP_MMS_UNICODE_STRING;
            break;
        case DLT860_GENERIC_BITSTRING:
            namedVariable->type = GSP_MMS_BIT_STRING;
            break;
        case DLT860_TIMESTAMP:
            namedVariable->type = GSP_MMS_UTC_TIME;
            break;
        case DLT860_QUALITY:
            namedVariable->typeSpec.bitString = -13; /* -13 = up to 13 bits */
            namedVariable->type = GSP_MMS_QUALITY;
            break;
        case DLT860_ENTRY_TIME:
            namedVariable->type = GSP_MMS_BINARY_TIME;
            namedVariable->typeSpec.binaryTime = 6;
            break;
        case DLT860_PHYCOMADDR:
            GspMmsMapping_createPhyComAddrStructure(namedVariable);
            break;
        case DLT860_OPTFLDS:
            namedVariable->typeSpec.bitString = 10;
            namedVariable->type = GSP_MMS_BIT_STRING;
            break;
        case DLT860_TRGOPS:
            namedVariable->typeSpec.bitString = 6;
            namedVariable->type = GSP_MMS_BIT_STRING;
            break;
        case DLT860_DBPOS:
            namedVariable->typeSpec.bitString = 2;
            namedVariable->type = GSP_MMS_DBPOS;
            break;
        case DLT860_TCMD:
            namedVariable->typeSpec.bitString = 2;
            namedVariable->type = GSP_MMS_TCMD;
            break;
        default:
            if (DEBUG_IED_SERVER)
                printf("MMS-MAPPING: type cannot be mapped %i\n", attribute->type);
            break;
        }
    }

    return origNamedVariable;
}

static int
countChildrenWithFc(GspDataObject* dataObject, GspFunctionalConstraint fc)
{
    int elementCount = 0;

    GspModelNode* child = dataObject->firstChild;

    while (child != nullptr) {
        if (child->modelType == GspDataAttributeModelType) {
            GspDataAttribute* dataAttribute = (GspDataAttribute*) child;

            if (dataAttribute->fc == fc)
                elementCount++;
        }
        else if (child->modelType == GspDataObjectModelType) {
            GspDataObject* subDataObject = (GspDataObject*) child;

            if (GspDataObject_hasFCData(subDataObject, fc))
                elementCount++;
        }

        child = child->sibling;
    }

    return elementCount;
}

static GspMmsVariableSpecification*
createFCNamedVariableFromDataObject(GspDataObject* dataObject,
                                    GspFunctionalConstraint fc)
{
    GspMmsVariableSpecification* namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));

    GspMmsVariableSpecification* completeNamedVariable = namedVariable;

    namedVariable->name = StringUtils_copyString(dataObject->name);

    if (dataObject->elementCount > 0) {
        namedVariable->type = GSP_MMS_ARRAY;
        namedVariable->typeSpec.array.elementCount = dataObject->elementCount;
        namedVariable->typeSpec.array.elementTypeSpec = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
        namedVariable = namedVariable->typeSpec.array.elementTypeSpec;
    }

    namedVariable->type = GSP_MMS_STRUCTURE;

    int elementCount = countChildrenWithFc(dataObject, fc);

    /* Allocate memory for components */
    namedVariable->typeSpec.structure.elements = (GspMmsVariableSpecification**) GLOBAL_CALLOC(elementCount, sizeof(GspMmsVariableSpecification*));

    int i = 0;
    GspModelNode* component = dataObject->firstChild;

    while (component != nullptr) {
        if (component->modelType == GspDataAttributeModelType) {
            GspDataAttribute* dataAttribute = (GspDataAttribute*) component;

            if (dataAttribute->fc == fc) {
                namedVariable->typeSpec.structure.elements[i] =
                        createNamedVariableFromDataAttribute(dataAttribute);
                i++;
            }
        }
        else if (component->modelType == GspDataObjectModelType) {
            GspDataObject* subDataObject = (GspDataObject*) component;

            if (GspDataObject_hasFCData(subDataObject, fc)) {
                namedVariable->typeSpec.structure.elements[i] =
                        createFCNamedVariableFromDataObject(subDataObject, fc);
                i++;
            }

        }

        component = component->sibling;
    }

    namedVariable->typeSpec.structure.elementCount = elementCount;

    return completeNamedVariable;
}

static GspMmsVariableSpecification* createFCNamedVariable(GspLogicalNode* logicalNode, GspFunctionalConstraint fc)
{
    GspMmsVariableSpecification* namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    char* fcString = GspFunctionalConstraint_toString(fc);
    if(fcString == nullptr){
        return nullptr;
    }
    namedVariable->name = StringUtils_copyString(fcString);
    namedVariable->type = GSP_MMS_STRUCTURE;
    delete [] fcString;

    int dataObjectCount = 0;
    GspDataObject* dataObject = (GspDataObject*) logicalNode->firstChild;
    while (dataObject != nullptr) {
        if (GspDataObject_hasFCData(dataObject, fc))
            dataObjectCount++;
        dataObject = (GspDataObject*) dataObject->sibling;
    }

    namedVariable->typeSpec.structure.elementCount = dataObjectCount;
    namedVariable->typeSpec.structure.elements = (GspMmsVariableSpecification**) GLOBAL_CALLOC(dataObjectCount, sizeof(GspMmsVariableSpecification*));

    dataObjectCount = 0;
    dataObject = (GspDataObject*) logicalNode->firstChild;

    while (dataObject != nullptr) {
        if (GspDataObject_hasFCData(dataObject, fc)) {
            namedVariable->typeSpec.structure.elements[dataObjectCount] = createFCNamedVariableFromDataObject(dataObject, fc);
            dataObjectCount++;
        }

        dataObject = (GspDataObject*) dataObject->sibling;
    }

    return namedVariable;
}

#if (CONFIG_DLT860_SETTING_GROUPS == 1)

static GspMmsVariableSpecification* createSGCB(void)
{
    GspMmsVariableSpecification* namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("SGCB");
    namedVariable->type = GSP_MMS_STRUCTURE;

    namedVariable->typeSpec.structure.elementCount = 6;
    namedVariable->typeSpec.structure.elements = (GspMmsVariableSpecification**) GLOBAL_CALLOC(6, sizeof(GspMmsVariableSpecification*));

    GspMmsVariableSpecification* element;

    element = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    element->name = StringUtils_copyString("NumOfSG");
    element->type = GSP_MMS_UINT16;
    element->typeSpec.uint16 = 8;
    namedVariable->typeSpec.structure.elements[0] = element;

    element = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    element->name = StringUtils_copyString("ActSG");
    element->type = GSP_MMS_UINT16;
    element->typeSpec.uint16 = 8;
    namedVariable->typeSpec.structure.elements[1] = element;

    element = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    element->name = StringUtils_copyString("EditSG");
    element->type = GSP_MMS_UINT16;
    element->typeSpec.uint16 = 8;
    namedVariable->typeSpec.structure.elements[2] = element;

    element = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    element->name = StringUtils_copyString("CnfEdit");
    element->type = GSP_MMS_BOOLEAN;
    namedVariable->typeSpec.structure.elements[3] = element;

    element = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    element->name = StringUtils_copyString("LActTm");
    element->type = GSP_MMS_UTC_TIME;
    namedVariable->typeSpec.structure.elements[4] = element;

    element = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    element->name = StringUtils_copyString("ResvTms");
    element->type = GSP_MMS_UINT16;
    element->typeSpec.uint16 = 16;
    namedVariable->typeSpec.structure.elements[5] = element;

    return namedVariable;
}


static GspMmsVariableSpecification* createFCNamedVariableSPWithSGCB(GspLogicalNode* logicalNode)
{
    GspMmsVariableSpecification* namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("SP");
    namedVariable->type = GSP_MMS_STRUCTURE;

    int dataObjectCount = 1;

    GspDataObject* dataObject = (GspDataObject*) logicalNode->firstChild;

    while (dataObject != nullptr) {
        if (GspDataObject_hasFCData(dataObject, DLT860_FC_SP))
            dataObjectCount++;

        dataObject = (GspDataObject*) dataObject->sibling;
    }

    namedVariable->typeSpec.structure.elementCount = dataObjectCount;
    namedVariable->typeSpec.structure.elements = (GspMmsVariableSpecification**) GLOBAL_CALLOC(dataObjectCount, sizeof(GspMmsVariableSpecification*));

    dataObjectCount = 1;

    namedVariable->typeSpec.structure.elements[0] = createSGCB();

    dataObject = (GspDataObject*) logicalNode->firstChild;

    while (dataObject != nullptr) {
        if (GspDataObject_hasFCData(dataObject, DLT860_FC_SP)) {

            namedVariable->typeSpec.structure.elements[dataObjectCount] =
                    createFCNamedVariableFromDataObject(dataObject, DLT860_FC_SP);

            dataObjectCount++;
        }

        dataObject = (GspDataObject*) dataObject->sibling;
    }

    return namedVariable;
}

static bool
isSettingGroupControlBlock(char* separator)
{
    if (strncmp(separator + 1, "SP$SGCB", 7) == 0)
        return true;

    return false;
}

GspSettingGroup*
GspgetSettingGroupByMmsDomain(GspMmsMapping* self, GspMmsDomain* domain)
{
    for(auto &item : *(self->settingGroups))
    {
        GspSettingGroup* settingGroup = (GspSettingGroup*) item;

        if (settingGroup->mmsDomain == domain)
            return settingGroup;
    }

    return nullptr;
}

static GspSettingGroup*
getSettingGroupBySGCB(GspMmsMapping* self, GspSettingGroupControlBlock* sgcb)
{
    for(auto &item : *(self->settingGroups))
    {
        GspSettingGroup* settingGroup = (GspSettingGroup*) item;

        if (settingGroup->sgcb == sgcb)
            return settingGroup;

    }

    return nullptr;
}

static void
unselectEditSettingGroup(GspSettingGroup* settingGroup)
{
    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: Unselect setting group\n");

    settingGroup->sgcb->editSG = 0;
    settingGroup->editingClient = nullptr;
    GspMmsValue* editSg = GspMmsValue_getElement(settingGroup->sgcbMmsValues, 2);
    GspMmsValue_setUint8(editSg, 0U);
    GspMmsValue* resvTms = GspMmsValue_getElement(settingGroup->sgcbMmsValues, 5);
    GspMmsValue_setUint16(resvTms, 0U);
}

static void
unselectAllSettingGroups(GspMmsMapping* self, GspMmsServerConnection serverCon)
{
    for(auto &item : *(self->settingGroups))
    {
        GspSettingGroup* settingGroup = (GspSettingGroup*) item;

        if (settingGroup->editingClient == (GspClientConnection) serverCon)
            unselectEditSettingGroup(settingGroup);
    }
}

void
GspMmsMapping_checkForSettingGroupReservationTimeouts(GspMmsMapping* self, uint64_t currentTime)
{
    for(auto &item : *(self->settingGroups))
    {
        GspSettingGroup* settingGroup = (GspSettingGroup*) item;

        if (settingGroup->sgcb->editSG != 0)
            if (currentTime >= settingGroup->reservationTimeout)
                unselectEditSettingGroup(settingGroup);

    }
}
#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
void
GspMmsMapping_initializeControlObjects(GspMmsMapping* self)
{
    for(auto &item : *(self->controlObjects))
    {
        GspControlObject* controlObject = (GspControlObject*) item;

        GspControlObject_initialize(controlObject);
    }
}
#endif

void
GspMmsMapping_configureSettingGroups(GspMmsMapping* self)
{

    for(auto &item : *(self->settingGroups))
    {
        GspSettingGroup* settingGroup = (GspSettingGroup*) item;

        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: Configure setting group\n");

        GspMmsValue* values = MmsServer_getValueFromCache(self->mmsServer, settingGroup->mmsDomain, "LLN0$SP$SGCB");

        if (values != nullptr) {
            settingGroup->sgcb->resvTms = CONFIG_IEC61850_SG_RESVTMS;

            GspMmsValue* numOfSg = GspMmsValue_getElement(values, 0);
            GspMmsValue* actSg = GspMmsValue_getElement(values, 1);
            GspMmsValue* resvTms = GspMmsValue_getElement(values, 5);

            GspMmsValue_setUint8(numOfSg, settingGroup->sgcb->numOfSGs);
            GspMmsValue_setUint8(actSg, settingGroup->sgcb->actSG);

            GspMmsValue_setUint16(resvTms, 0U);

            settingGroup->sgcbMmsValues = values;
        } else {
            if (DEBUG_IED_SERVER)
                printf("IED_SERVER: Values for SGCB do not exist\n");
        }
    }
}

void
GspMmsMapping_setSgChangedHandler(GspMmsMapping* self, GspSettingGroupControlBlock* sgcb,
                                  GspActiveSettingGroupChangedHandler handler, void* parameter)
{
    GspSettingGroup* sg = getSettingGroupBySGCB(self, sgcb);

    if (sg != nullptr) {
        sg->actSgChangedHandler = handler;
        sg->actSgChangedHandlerParameter = parameter;
    } else {
        for(auto &item : *(self->settingGroups))
        {
            GspSettingGroup* settingGroup = (GspSettingGroup*) item;

            settingGroup->actSgChangedHandler = handler;
            settingGroup->actSgChangedHandlerParameter = parameter;
        }
    }
}

void
GspMmsMapping_setEditSgChangedHandler(GspMmsMapping* self, GspSettingGroupControlBlock* sgcb,
                                      GspEditSettingGroupChangedHandler handler, void* parameter)
{
    GspSettingGroup* sg = getSettingGroupBySGCB(self, sgcb);

    if (sg != nullptr) {
        sg->editSgChangedHandler = handler;
        sg->editSgChangedHandlerParameter = parameter;
    } else {
        for(auto &item : *(self->settingGroups))
        {
            GspSettingGroup* settingGroup = (GspSettingGroup*) item;

            settingGroup->editSgChangedHandler = handler;
            settingGroup->editSgChangedHandlerParameter = parameter;
        }
    }
}

void
GspMmsMapping_setConfirmEditSgHandler(GspMmsMapping* self, GspSettingGroupControlBlock* sgcb,
                                      GspEditSettingGroupConfirmationHandler handler, void* parameter)
{
    GspSettingGroup* sg = getSettingGroupBySGCB(self, sgcb);

    if (sg != nullptr) {
        sg->editSgConfirmedHandler = handler;
        sg->editSgConfirmedHandlerParameter = parameter;
    } else {
        for(auto &item : *(self->settingGroups))
        {
            GspSettingGroup* settingGroup = (GspSettingGroup*) item;

            settingGroup->editSgConfirmedHandler = handler;
            settingGroup->editSgConfirmedHandlerParameter = parameter;
        }
    }
}

int
GspchangeActiveSettingGroup(GspMmsMapping* self, GspSettingGroup* sg, uint8_t newActiveSg, GspClientConnection clientConn)
{
    if (sg != nullptr) {

        auto value = GspMmsValue_getElement(sg->sgcbMmsValues, 0);
        int numOfSG = GspMmsValue_toInt32(value);
        if (newActiveSg > 0 && newActiveSg <= numOfSG) {

            uint8_t orgSeGroup = sg->sgcb->editSG;
            uint8_t orgSgGroup = sg->sgcb->actSG;

            // 判断当前编辑定值组号是否为零,如果为零,则表明有用户在进行编辑定值区,则不能切换.
            if(orgSeGroup != 0)
            {
                return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
            }

            // 判断待切换定值区为当前定值区,如果相同,不能切换.
            if(orgSgGroup == newActiveSg)
            {
           //     return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
            }

            // 用户回调
            if(sg->actSgChangedHandler)
            {
                auto ret = sg->actSgChangedHandler(sg->actSgChangedHandlerParameter, sg->sgcb, newActiveSg, clientConn);
                if(!ret)
                {
                    return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
                }
            }

            // 修改模型至
            GspMmsValue* actSg = GspMmsValue_getElement(sg->sgcbMmsValues, 1);
            GspMmsValue* lActTm = GspMmsValue_getElement(sg->sgcbMmsValues, 4);
            sg->sgcb->actSG = newActiveSg;
            sg->sgcb->timestamp = GSP_Hal_getTimeInMs();
            GspMmsValue_setUint8(actSg, sg->sgcb->actSG);
            GspMmsValue_setUtcTimeMs(lActTm, sg->sgcb->timestamp);

            // 更换定值区激活定值
            self->sgStorage->selectActiveSg(sg->mmsDomain->domainName, sg->sgcb->actSG, sg->sgcb->timestamp);

            // 先把SE切换到要激活的定值组
/*
            if(clientConn != nullptr)
            {
                GspSelectEditSg(self, clientConn, sg, newActiveSg);


            }

            GspMmsValue* actSg = GspMmsValue_getElement(sg->sgcbMmsValues, 1);
            GspMmsValue* lActTm = GspMmsValue_getElement(sg->sgcbMmsValues, 4);
            sg->sgcb->actSG = newActiveSg;
            sg->sgcb->timestamp = GSP_Hal_getTimeInMs();
            GspMmsValue_setUint8(actSg, sg->sgcb->actSG);
            GspMmsValue_setUtcTimeMs(lActTm, sg->sgcb->timestamp);

            self->sgStorage->selectActiveSg(sg->mmsDomain->domainName, sg->sgcb->actSG, sg->sgcb->timestamp);

            // 将对应SE组定值设置到SG组
            // 从存储内取出编辑区定值，设置到对应的se节点上
            SgValueVec valueVec;
            self->sgStorage->getSgValues(sg->mmsDomain->domainName, newActiveSg, valueVec);
            for(auto &item : valueVec)
            {
                void *conn = Gsp_private_ClientConnection_getServerConnectionHandle(clientConn);
                setDataByReference((GspMmsServerConnection)conn, item.reference, "SG", item.value);
            }

            // 激活后，切换回原来的编辑定值组
            GspSelectEditSg(self, clientConn, sg, orgSeGroup);
*/
            return GSP_DATA_ACCESS_ERROR_SUCCESS;
        }
        return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
    }
    else
    {
        return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
    }
}

#endif /* (CONFIG_DLT860_SETTING_GROUPS == 1) */

static int
determineLogicalNodeComponentCount(GspLogicalNode* logicalNode)
{
    int componentCount = 0;

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_ST))
        componentCount++;

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_MX))
        componentCount++;

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_SP))
        componentCount++;

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_SV))
        componentCount++;

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_CF))
        componentCount++;

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_DC))
        componentCount++;

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_SG))
        componentCount++;

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_SE))
        componentCount++;

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_SR))
        componentCount++;

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_OR))
        componentCount++;

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_BL))
        componentCount++;

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_EX))
        componentCount++;

    //if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_CO))
    //    componentCount++;

    return componentCount;
}


#if (CONFIG_DLT860_REPORT_SERVICE == 1)
static int
countReportControlBlocksForLogicalNode(GspMmsMapping* self, GspLogicalNode* logicalNode, bool buffered)
{
    int rcbCount = 0;

    GspReportControlBlock* rcb = self->model->rcbs;

    /* Iterate list of RCBs */
    while (rcb != nullptr) {
        if (rcb->parent == logicalNode) {
            if (rcb->buffered == buffered)
                rcbCount++;
        }

        rcb = rcb->sibling;
    }

    return rcbCount;
}
#endif /* (CONFIG_DLT860_CONTROL_SERVICE == 1) */

#if (CONFIG_DLT860_LOG_SERVICE == 1)
static int
countLogControlBlocksForLogicalNode (GspMmsMapping* self, GspLogicalNode* logicalNode)
{
    int lcbCount = 0;

    GspLogControlBlock* lcb = self->model->lcbs;

    while (lcb != nullptr) {
        if (lcb->parent == logicalNode)
            lcbCount++;

        lcb = lcb->sibling;
    }

    return lcbCount;
}
#endif /* (CONFIG_DLT860_LOG_SERVICE == 1) */


#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)

static int
countGSEControlBlocksForLogicalNode(MmsMapping* self, LogicalNode* logicalNode)
{
    int gseCount = 0;

    GSEControlBlock* gcb = self->model->gseCBs;

    while (gcb != nullptr) {
        if (gcb->parent == logicalNode)
            gseCount++;

        gcb = gcb->sibling;
    }

    return gseCount;
}

#endif /* (CONFIG_INCLUDE_GOOSE_SUPPORT == 1) */

#if (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1)

static int
countSVControlBlocksForLogicalNode(MmsMapping* self, LogicalNode* logicalNode, bool unicast)
{
    int svCount = 0;

    SVControlBlock* svCb = self->model->svCBs;

    while (svCb != nullptr) {
        if ((svCb->parent == logicalNode) && (svCb->isUnicast == unicast))
            svCount++;

        svCb = svCb->sibling;
    }

    return svCount;
}

#endif /* (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1) */

#if (CONFIG_DLT860_SETTING_GROUPS == 1)

static GspSettingGroupControlBlock*
checkForSgcb(GspMmsMapping* self, GspLogicalNode* logicalNode)
{
    GspSettingGroupControlBlock* sgcb = self->model->sgcbs;

    while (sgcb != nullptr) {
        if (sgcb->parent == logicalNode)
            return sgcb;

        sgcb = sgcb->sibling;
    }

    return nullptr;
}

#endif /* (CONFIG_DLT860_SETTING_GROUPS == 1) */


static GspMmsVariableSpecification*
createNamedVariableFromLogicalNode(GspMmsMapping* self, GspMmsDomain* domain,
                                   GspLogicalNode* logicalNode)
{
    GspMmsVariableSpecification* namedVariable = (GspMmsVariableSpecification*)
            GLOBAL_MALLOC(sizeof(GspMmsVariableSpecification));

    namedVariable->name = StringUtils_copyString(logicalNode->name);

    namedVariable->type = GSP_MMS_STRUCTURE;

    int componentCount = determineLogicalNodeComponentCount(logicalNode);

#if (CONFIG_DLT860_SETTING_GROUPS == 1)
    GspSettingGroupControlBlock* sgControlBlock = nullptr;

    sgControlBlock = checkForSgcb(self, logicalNode);

    if (sgControlBlock != nullptr) {
        if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_SP) == false)
            componentCount++;

        GspSettingGroup* settingGroup = (GspSettingGroup*) GLOBAL_CALLOC(1, sizeof(GspSettingGroup));

        settingGroup->sgcb = sgControlBlock;
        settingGroup->mmsDomain = domain;

        GspLinkedList_add(self->settingGroups, (void*) settingGroup);
    }
#endif /* (CONFIG_DLT860_SETTING_GROUPS == 1) */

    if (DEBUG_IED_SERVER)
        printf("LogicalNode %s has %i fc components\n", logicalNode->name,
               componentCount);

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
    int brcbCount = countReportControlBlocksForLogicalNode(self, logicalNode,
                                                           true);

    if (brcbCount > 0) {
        if (DEBUG_IED_SERVER)
            printf("  and %i buffered RCBs\n", brcbCount);
        componentCount++;
    }

    int urcbCount = countReportControlBlocksForLogicalNode(self, logicalNode,
                                                           false);

    if (urcbCount > 0) {
        if (DEBUG_IED_SERVER)
            printf("  and %i unbuffered RCBs\n", urcbCount);
        componentCount++;
    }
#endif /* (CONFIG_DLT860_REPORT_SERVICE == 1) */

#if (CONFIG_DLT860_LOG_SERVICE == 1)

    int lcbCount = countLogControlBlocksForLogicalNode(self, logicalNode);

    if (lcbCount > 0) {
        if (DEBUG_IED_SERVER)
            printf("   and %i LOG control blocks\n", lcbCount);

        componentCount++;
    }

#endif /* (CONFIG_DLT860_LOG_SERVICE == 1) */

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)

    int gseCount = countGSEControlBlocksForLogicalNode(self, logicalNode);

    if (gseCount > 0) {
        if (DEBUG_IED_SERVER)
            printf("   and %i GSE control blocks\n", gseCount);
        componentCount++;
    }

#endif /* (CONFIG_INCLUDE_GOOSE_SUPPORT == 1) */

#if (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1)

    int msvcbCount = countSVControlBlocksForLogicalNode(self, logicalNode, false);

    if (msvcbCount > 0) {
        if (DEBUG_IED_SERVER)
            printf("   and %i MSV control blocks\n", msvcbCount);

        componentCount++;
    }

    int usvcbCount = countSVControlBlocksForLogicalNode(self, logicalNode, true);

    if (usvcbCount > 0) {
        if (DEBUG_IED_SERVER)
            printf("   and %i USV control blocks\n", usvcbCount);

        componentCount++;
    }

#endif /* (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1) */

    namedVariable->typeSpec.structure.elements = (GspMmsVariableSpecification**) GLOBAL_CALLOC(componentCount,
                                                                                               sizeof(GspMmsVariableSpecification*));

    /* Create a named variable of type structure for each functional constrained */
    int currentComponent = 0;

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_MX)) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                createFCNamedVariable(logicalNode, DLT860_FC_MX);
        currentComponent++;
    }

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_ST)) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                createFCNamedVariable(logicalNode, DLT860_FC_ST);
        currentComponent++;
    }

    //if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_CO)) {
    //    namedVariable->typeSpec.structure.elements[currentComponent] =
    //            createFCNamedVariable(logicalNode, DLT860_FC_CO);
    //    currentComponent++;
    //}

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_CF)) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                createFCNamedVariable(logicalNode, DLT860_FC_CF);
        currentComponent++;
    }

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_DC)) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                createFCNamedVariable(logicalNode, DLT860_FC_DC);
        currentComponent++;
    }

#if (CONFIG_DLT860_SETTING_GROUPS == 1)
    if (sgControlBlock != nullptr) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                createFCNamedVariableSPWithSGCB(logicalNode);
        currentComponent++;
    }
    else
#endif /* (CONFIG_DLT860_SETTING_GROUPS == 1) */
        if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_SP)) {
            namedVariable->typeSpec.structure.elements[currentComponent] =
                    createFCNamedVariable(logicalNode, DLT860_FC_SP);
            currentComponent++;
        }

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_SG)) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                createFCNamedVariable(logicalNode, DLT860_FC_SG);
        currentComponent++;
    }

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
    if (urcbCount > 0) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                GspReporting_createMmsUnbufferedRCBs(self, domain, logicalNode,
                                                     urcbCount);
        currentComponent++;
    }
#endif /* (CONFIG_DLT860_REPORT_SERVICE == 1) */

#if (CONFIG_DLT860_LOG_SERVICE == 1)

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)
    if (self->iedServer->logServiceEnabled) {
#endif

        if (lcbCount > 0) {
            namedVariable->typeSpec.structure.elements[currentComponent] =
                    GspLogging_createLCBs(self, domain, logicalNode, lcbCount);

            currentComponent++;
        }

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)
    }
#endif

#endif /* (CONFIG_DLT860_LOG_SERVICE == 1) */


#if (CONFIG_DLT860_REPORT_SERVICE == 1)
    if (brcbCount > 0) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                GspReporting_createMmsBufferedRCBs(self, domain, logicalNode,
                                                   brcbCount);
        currentComponent++;
    }
#endif /* (CONFIG_DLT860_REPORT_SERVICE == 1) */

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
    if (gseCount > 0) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                GOOSE_createGOOSEControlBlocks(self, domain, logicalNode, gseCount);

        currentComponent++;
    }
#endif /* (CONFIG_INCLUDE_GOOSE_SUPPORT == 1) */



    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_SV)) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                createFCNamedVariable(logicalNode, DLT860_FC_SV);
        currentComponent++;
    }

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_SE)) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                createFCNamedVariable(logicalNode, DLT860_FC_SE);
        currentComponent++;
    }

#if (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1)

    /* Add MS and US named variables */
    if (msvcbCount > 0) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                LIBIEC61850_SV_createSVControlBlocks(self, domain, logicalNode, msvcbCount, false);

        currentComponent++;
    }

    if (usvcbCount > 0) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                LIBIEC61850_SV_createSVControlBlocks(self, domain, logicalNode, usvcbCount, true);

        currentComponent++;
    }
#endif

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_EX)) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                createFCNamedVariable(logicalNode, DLT860_FC_EX);
        currentComponent++;
    }

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_SR)) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                createFCNamedVariable(logicalNode, DLT860_FC_SR);
        currentComponent++;
    }

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_OR)) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                createFCNamedVariable(logicalNode, DLT860_FC_OR);
        currentComponent++;
    }

    if (GspLogicalNode_hasFCData(logicalNode, DLT860_FC_BL)) {
        namedVariable->typeSpec.structure.elements[currentComponent] =
                createFCNamedVariable(logicalNode, DLT860_FC_BL);
        currentComponent++;
    }

    namedVariable->typeSpec.structure.elementCount = currentComponent;

    return namedVariable;
}

static GspMmsDomain*
createMmsDomainFromIedDevice(GspMmsMapping* self, GspLogicalDevice* logicalDevice)
{
    GspMmsDomain* domain = nullptr;
    char domainName[65];
    std::string str_domainName;

    int modelNameLength = strlen(self->model->name);

    if (modelNameLength > 64)
        return domain;

    strncpy(domainName, self->model->name, 64);
    strncat(domainName, logicalDevice->name, 64 - modelNameLength);

    str_domainName = std::string(domainName);

    domain = GspMmsDomain_create(domainName);
    domain->modelName = logicalDevice->iedName;
    if (domain == nullptr)
        return domain;
    
#if (CONFIG_DLT860_LOG_SERVICE == 1)

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)
    if (self->iedServer->logServiceEnabled) {
#endif
        /* add logs (journals) */
        GspLog* log = self->model->logs;

        if(strcmp(self->model->name, "P_L2212B") == 0){
            auto a = 0;
        }

        while (log != nullptr) {

            char journalName[65];

            if(str_domainName.find(logicalDevice->iedName) == str_domainName.npos ||
                    str_domainName.find(log->parent->parent->name) == str_domainName.npos){
                log = log->sibling;
                continue;
            }

            int nameLength = strlen(log->parent->name) + strlen(log->name);

            if (nameLength > 63) {
                if (DEBUG_IED_SERVER)
                    printf("IED_SERVER: Log name %s invalid! Resulting journal name too long! Skip log\n", log->name);
            }
            else {
                strcpy(journalName, log->parent->name);
                strcat(journalName, "$");
                strcat(journalName, log->name);

                GspMmsDomain_addJournal(domain, journalName);

                GspLogInstance* logInstance = GspLogInstance_create(log->parent, log->name);

                string logStoragePath = string(self->iedServer->serverConfig->logStoragePath) + "/history";
                if(!fs::exists(fs::status(logStoragePath))){
                    fs::create_directories(logStoragePath);
                }
                logStoragePath += string("/") + string(logicalDevice->iedName);
                if(!fs::exists(fs::status(logStoragePath))){
                    fs::create_directories(logStoragePath);
                }

                logStoragePath += string("/") + domain->domainName + "." + journalName;
                //string logStoragePath = string(self->iedServer->serverConfig->logStoragePath) + "." + domain->domainName + "." + journalName;
                auto sqliteStorage = SqliteLogStorage_createInstance(logStoragePath.c_str());
                logInstance->logStorage = sqliteStorage;

                GspLinkedList_add(self->logInstances, (void*) logInstance);
            }

            log = log->sibling;
        }

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)
    }
#endif

#endif /* (CONFIG_DLT860_LOG_SERVICE == 1) */

    int nodesCount = GspLogicalDevice_getLogicalNodeCount(logicalDevice);

    /* Logical nodes are first level named variables */
    domain->namedVariablesCount = nodesCount;
    domain->namedVariables = (GspMmsVariableSpecification**) GLOBAL_MALLOC(nodesCount * sizeof(GspMmsVariableSpecification*));

    GspLogicalNode* logicalNode = (GspLogicalNode*) logicalDevice->firstChild;

    int i = 0;
    while (logicalNode != nullptr) {
        domain->namedVariables[i] = createNamedVariableFromLogicalNode(self,
                                                                       domain, logicalNode);

        logicalNode = (GspLogicalNode*) logicalNode->sibling;
        i++;
    }
    return domain;
}

static void
createMmsDataModelMulti(GspMmsMapping* self, int iedDeviceCount,
                        GspMmsDevice *mmsDevice, GspIedModel **iedModel) {

    mmsDevice->domainCount = iedDeviceCount;
    GspIedModel *model = *iedModel;
    int i = 0;

    self->iedMap[model->name] = model;
    while(model) {
        self->model = model;
        GspLogicalDevice* logicalDevice = model->firstChild;
        while (logicalDevice != nullptr) {
            auto device = createMmsDomainFromIedDevice(self, logicalDevice);
            mmsDevice->domains.insert({device->domainName, device});
            self->domainIedMap[device->domainName] = model;
            self->ldMap[device->domainName] = logicalDevice;
            i++;
            logicalDevice = (GspLogicalDevice*) logicalDevice->sibling;
        }

        iedModel += 1;
        model = *iedModel;
    }
    self->model = nullptr;
}

static void
createMmsDataModel(GspMmsMapping* self, int iedDeviceCount,
                   GspMmsDevice* mmsDevice, GspIedModel* iedModel)
{
    mmsDevice->domainCount = iedDeviceCount;

    GspLogicalDevice* logicalDevice = iedModel->firstChild;

    int i = 0;
    while (logicalDevice != nullptr) {
        auto device = createMmsDomainFromIedDevice(self, logicalDevice);
        mmsDevice->domains.insert({device->domainName, device});
        i++;
        logicalDevice = (GspLogicalDevice*) logicalDevice->sibling;
    }
}

static void
createDataSetsMulti(GspMmsDevice *mmsDevice, GspIedModel **iedModel) {
    GspIedModel *model = *iedModel;
    while(model) {
        GspDataSet* dataset = model->dataSets;

        char domainName[65];

        int iedModelNameLength = strlen(model->name);

        if (iedModelNameLength > 64) {

            if (DEBUG_IED_SERVER)
                printf("IED_SERVER: IED model name too long!\n");

            goto exit_function;
        }

        while (dataset != nullptr) {
            strncpy(domainName, model->name, 64);
            strncat(domainName, dataset->logicalDeviceName, 64 - iedModelNameLength);

            GspMmsDomain* dataSetDomain = GspMmsDevice_getDomain(mmsDevice, domainName);

            if (dataSetDomain == nullptr) {

                if (DEBUG_IED_SERVER)
                    printf("IED_SERVER: LD for dataset does not exist!\n");

                goto exit_function;
            }

            GspMmsNamedVariableList varList = MmsNamedVariableList_create(dataSetDomain, dataset->name, false);

            GspDataSetEntry* dataSetEntry = dataset->fcdas;

            while (dataSetEntry != nullptr) {

                GspMmsAccessSpecifier accessSpecifier;

                strncpy(domainName, model->name, 64);
                strncat(domainName, dataSetEntry->logicalDeviceName, 64 - iedModelNameLength);

                accessSpecifier.domain = GspMmsDevice_getDomain(mmsDevice, domainName);

                accessSpecifier.variableName = dataSetEntry->variableName;
                accessSpecifier.arrayIndex = dataSetEntry->index;
                accessSpecifier.componentName = dataSetEntry->componentName;

                GspMmsNamedVariableListEntry variableListEntry =
                        MmsNamedVariableListEntry_create(accessSpecifier);

                MmsNamedVariableList_addVariable(varList, variableListEntry);

                dataSetEntry = dataSetEntry->sibling;
            }

            GspMmsDomain_addNamedVariableList(dataSetDomain, varList);

            dataset = dataset->sibling;
        }
        iedModel += 1;
        model = *iedModel;
    }
exit_function:
    return;
}

static void
createDataSets(GspMmsDevice* mmsDevice, GspIedModel* iedModel)
{
    GspDataSet* dataset = iedModel->dataSets;

    char domainName[65];

    int iedModelNameLength = strlen(iedModel->name);

    if (iedModelNameLength > 64) {

        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: IED model name too long!\n");

        goto exit_function;
    }

    while (dataset != nullptr) {
        strncpy(domainName, iedModel->name, 64);
        strncat(domainName, dataset->logicalDeviceName, 64 - iedModelNameLength);

        GspMmsDomain* dataSetDomain = GspMmsDevice_getDomain(mmsDevice, domainName);

        if (dataSetDomain == nullptr) {

            if (DEBUG_IED_SERVER)
                printf("IED_SERVER: LD for dataset does not exist!\n");

            goto exit_function;
        }

        GspMmsNamedVariableList varList = MmsNamedVariableList_create(dataSetDomain, dataset->name, false);

        GspDataSetEntry* dataSetEntry = dataset->fcdas;

        while (dataSetEntry != nullptr) {

            GspMmsAccessSpecifier accessSpecifier;

            strncpy(domainName, iedModel->name, 64);
            strncat(domainName, dataSetEntry->logicalDeviceName, 64 - iedModelNameLength);

            accessSpecifier.domain = GspMmsDevice_getDomain(mmsDevice, domainName);

            accessSpecifier.variableName = dataSetEntry->variableName;
            accessSpecifier.arrayIndex = dataSetEntry->index;
            accessSpecifier.componentName = dataSetEntry->componentName;

            GspMmsNamedVariableListEntry variableListEntry =
                    MmsNamedVariableListEntry_create(accessSpecifier);

            MmsNamedVariableList_addVariable(varList, variableListEntry);

            dataSetEntry = dataSetEntry->sibling;
        }

        GspMmsDomain_addNamedVariableList(dataSetDomain, varList);

        dataset = dataset->sibling;
    }

exit_function:
    return;
}

static GspMmsDevice*
createMmsModelFromIedModelMulti(GspMmsMapping* self, GspIedModel** iedModel) {
    GspMmsDevice* mmsDevice = nullptr;
    mmsDevice = GspMmsDevice_create(iedModel[0]->name);


    int iedDeviceCount = 0;
    GspIedModel **tmpModel = iedModel;
    GspIedModel *currentIed = *tmpModel;

    while(currentIed) {
        if(currentIed->firstChild != nullptr) {
            iedDeviceCount += GspIedModel_getLogicalDeviceCount(currentIed);
        }
        tmpModel += 1;
        currentIed = *tmpModel;
    }
    createMmsDataModelMulti(self, iedDeviceCount, mmsDevice, iedModel);
    createDataSetsMulti(mmsDevice, iedModel);

    return mmsDevice;
}

static GspMmsDevice*
createMmsModelFromIedModel(GspMmsMapping* self, GspIedModel* iedModel)
{
    GspMmsDevice* mmsDevice = nullptr;

    mmsDevice = GspMmsDevice_create(iedModel->name);

    if (iedModel->firstChild != nullptr) {

        int iedDeviceCount = GspIedModel_getLogicalDeviceCount(iedModel);

        createMmsDataModel(self, iedDeviceCount, mmsDevice, iedModel);

        createDataSets(mmsDevice, iedModel);
    }

    return mmsDevice;
}

GspMmsMapping*
GspMmsMapping_createMulti(GspIedModel** model, GspIedServer iedServer) {
    GspMmsMapping* self = new sGspMmsMapping();
    self->modelss = model;
    self->iedServer = iedServer;
#if (CONFIG_DLT860_REPORT_SERVICE == 1)
    self->reportControls = GspLinkedList_create();
#endif

#if (CONFIG_DLT860_LOG_SERVICE == 1)
    self->logControls = GspLinkedList_create();
    self->logInstances = GspLinkedList_create();
#endif

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
    self->gseControls = LinkedList_create();
    self->gooseInterfaceId = nullptr;
#endif

#if (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1)
    self->svControls = LinkedList_create();
    self->svInterfaceId = nullptr;
#endif

#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
    self->controlObjects = GspLinkedList_create();
#endif

#if (CONFIG_DLT860_SETTING_GROUPS == 1)
    self->settingGroups = GspLinkedList_create();
#endif

    self->attributeAccessHandlers = GspLinkedList_create();
    /* create data model specification */
    self->mmsDevice = createMmsModelFromIedModelMulti(self, model);

    return self;
}

GspMmsMapping*
GspMmsMapping_create(GspIedModel* model, GspIedServer iedServer)
{
    GspMmsMapping* self = (GspMmsMapping*) GLOBAL_CALLOC(1, sizeof(struct sGspMmsMapping));

    self->model = model;
    self->iedServer = iedServer;

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
    self->reportControls = GspLinkedList_create();
#endif

#if (CONFIG_DLT860_LOG_SERVICE == 1)
    self->logControls = GspLinkedList_create();
    self->logInstances = GspLinkedList_create();
#endif

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
    self->gseControls = LinkedList_create();
    self->gooseInterfaceId = nullptr;
#endif

#if (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1)
    self->svControls = LinkedList_create();
    self->svInterfaceId = nullptr;
#endif

#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
    self->controlObjects = GspLinkedList_create();
#endif

#if (CONFIG_DLT860_SETTING_GROUPS == 1)
    self->settingGroups = GspLinkedList_create();
#endif

    self->attributeAccessHandlers = GspLinkedList_create();

    /* create data model specification */
    self->mmsDevice = createMmsModelFromIedModel(self, model);
    self->model = nullptr;
    return self;
}

void
GspMmsMapping_destroy(GspMmsMapping* self)
{
    if(!self)
    {
        return;
    }
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    if (self->reportWorkerThread) {
        self->reportThreadRunning = false;
        GspThread_destroy(self->reportWorkerThread);
    }
#endif

    if (self->mmsDevice != nullptr)
        GspMmsDevice_destroy(self->mmsDevice);

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
    GspLinkedList_destroyDeep(self->reportControls, (GspLinkedListValueDeleteFunction) GspReportControl_destroy);
#endif

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
    LinkedList_destroyDeep(self->gseControls, (LinkedListValueDeleteFunction) MmsGooseControlBlock_destroy);
#endif

#if (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1)
    LinkedList_destroyDeep(self->svControls, (LinkedListValueDeleteFunction) MmsSampledValueControlBlock_destroy);
#endif

#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
    GspLinkedList_destroyDeep(self->controlObjects, (GspLinkedListValueDeleteFunction) GspControlObject_destroy);
#endif

#if (CONFIG_DLT860_SETTING_GROUPS == 1)
    GspLinkedList_destroy(self->settingGroups);
#endif

#if (CONFIG_DLT860_LOG_SERVICE == 1)
    GspLinkedList_destroyDeep(self->logControls, (GspLinkedListValueDeleteFunction) GspLogControl_destroy);
    GspLinkedList_destroyDeep(self->logInstances, (GspLinkedListValueDeleteFunction) GspLogInstance_destroy);
#endif

    GspLinkedList_destroy(self->attributeAccessHandlers);

   auto pModel = self->modelss;
   auto model = *pModel;
   while(model)
   {
       GspIedModel_setAttributeValuesToNull(model);
       pModel += 1;
       model = *pModel;
   }

    delete self;
}

GspMmsDevice*
GspMmsMapping_getMmsDeviceModel(GspMmsMapping* mapping)
{
    return mapping->mmsDevice;
}

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
static bool
isReportControlBlock(char* separator)
{
    if (strncmp(separator + 1, "RP", 2) == 0)
        return true;

    if (strncmp(separator + 1, "BR", 2) == 0)
        return true;

    return false;
}
#endif /* (CONFIG_DLT860_REPORT_SERVICE == 1) */

static bool
isFunctionalConstraintCF(char* separator)
{
    if (strncmp(separator + 1, "CF", 2) == 0)
        return true;
    else
        return false;
}

static bool
isFunctionalConstraintDC(char* separator)
{
    if (strncmp(separator + 1, "DC", 2) == 0)
        return true;
    else
        return false;
}

static bool
isFunctionalConstraintSP(char* separator)
{
    if (strncmp(separator + 1, "SP", 2) == 0)
        return true;
    else
        return false;
}

static bool
isFunctionalConstraintSV(char* separator)
{
    if (strncmp(separator + 1, "SV", 2) == 0)
        return true;
    else
        return false;
}

static bool
isFunctionalConstraintSE(char* separator)
{
    if (strncmp(separator + 1, "SE", 2) == 0)
        return true;
    else
        return false;
}


#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
static bool
isControllable(char* separator)
{
    if (strncmp(separator + 1, "CO", 2) == 0)
        return true;
    else
        return false;
}
#endif /* (CONFIG_DLT860_CONTROL_SERVICE == 1) */

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)

static bool
isGooseControlBlock(char* separator)
{
    if (strncmp(separator + 1, "GO", 2) == 0)
        return true;
    else
        return false;
}

#endif /* (CONFIG_INCLUDE_GOOSE_SUPPORT == 1) */


#if (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1)

static bool
isSampledValueControlBlock(char* separator)
{
    if (strncmp(separator + 1, "MS", 2) == 0)
        return true;

    if (strncmp(separator + 1, "US", 2) == 0)
        return true;

    return false;
}

#endif /* (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1) */

#if (CONFIG_DLT860_LOG_SERVICE == 1)

static bool
isLogControlBlock(char* separator)
{
    if (strncmp(separator + 1, "LG", 2) == 0)
        return true;

    return false;
}

#endif /* (CONFIG_DLT860_LOG_SERVICE == 1) */

char*
GspMmsMapping_getNextNameElement(char* name)
{
    char* separator = strchr(name, '$');

    if (separator == nullptr)
        return nullptr;

    separator++;

    if (*separator == 0)
        return nullptr;

    return separator;
}

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)

static MmsGooseControlBlock
lookupGCB(MmsMapping* self, MmsDomain* domain, char* lnName, char* objectName)
{
    LinkedList element = LinkedList_getNext(self->gseControls);

    while (element != nullptr) {
        MmsGooseControlBlock mmsGCB = (MmsGooseControlBlock) element->data;

        if (MmsGooseControlBlock_getDomain(mmsGCB) == domain) {
            if (strcmp(MmsGooseControlBlock_getLogicalNodeName(mmsGCB), lnName) == 0) {
                if (strcmp(MmsGooseControlBlock_getName(mmsGCB), objectName) == 0) {
                    return mmsGCB;
                }
            }
        }

        element = LinkedList_getNext(element);
    }

    return nullptr;
}

#ifndef CONFIG_GOOSE_GOID_WRITABLE
#define CONFIG_GOOSE_GOID_WRITABLE 0
#endif

#ifndef CONFIG_GOOSE_DATSET_WRITABLE
#define CONFIG_GOOSE_DATSET_WRITABLE 0
#endif

#ifndef CONFIG_GOOSE_CONFREV_WRITABLE
#define CONFIG_GOOSE_CONFREV_WRITABLE 0
#endif

#ifndef CONFIG_GOOSE_NDSCOM_WRITABLE
#define CONFIG_GOOSE_NDSCOM_WRITABLE 0
#endif

#ifndef CONFIG_GOOSE_DSTADDRESS_WRITABLE
#define CONFIG_GOOSE_DSTADDRESS_WRITABLE 0
#endif

#ifndef CONFIG_GOOSE_MINTIME_WRITABLE
#define CONFIG_GOOSE_MINTIME_WRITABLE 0
#endif

#ifndef CONFIG_GOOSE_MAXTIME_WRITABLE
#define CONFIG_GOOSE_MAXTIME_WRITABLE 0
#endif

#ifndef CONFIG_GOOSE_FIXEDOFFS_WRITABLE
#define CONFIG_GOOSE_FIXEDOFFS_WRITABLE 0
#endif

static MmsDataAccessError
writeAccessGooseControlBlock(MmsMapping* self, MmsDomain* domain, char* variableIdOrig,
                             MmsValue* value)
{
    char variableId[130];

    strncpy(variableId, variableIdOrig, 129);

    char* separator = strchr(variableId, '$');

    *separator = 0;

    char* lnName = variableId;

    if (lnName == nullptr)
        return DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;

    char* objectName = MmsMapping_getNextNameElement(separator + 1);

    if (objectName == nullptr)
        return DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;

    char* varName = MmsMapping_getNextNameElement(objectName);

    if (varName != nullptr)
        *(varName - 1) = 0;
    else
        return DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;

    MmsGooseControlBlock mmsGCB = lookupGCB(self, domain, lnName, objectName);

    if (mmsGCB == nullptr)
        return DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;

    if (strcmp(varName, "GoEna") == 0) {
        if (MmsValue_getType(value) != MMS_BOOLEAN)
            return DATA_ACCESS_ERROR_TYPE_INCONSISTENT;

        if (MmsValue_getBoolean(value))
            MmsGooseControlBlock_enable(mmsGCB);
        else
            MmsGooseControlBlock_disable(mmsGCB);

        return DATA_ACCESS_ERROR_SUCCESS;
    }
    else {
        if (MmsGooseControlBlock_isEnabled(mmsGCB))
            return DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
        else {
            bool allowAccess = false;

#if (CONFIG_GOOSE_GOID_WRITABLE == 1)
            if (strcmp(varName, "GoID") == 0) {
                MmsValue_update(MmsValue_getElement(MmsGooseControlBlock_getMmsValues(mmsGCB), 1), value);
                allowAccess = true;
            }
#endif

#if (CONFIG_GOOSE_DATSET_WRITABLE == 1)
            if (strcmp(varName, "DatSet") == 0) {
                /* allow to set non-existing data set? */

                MmsValue_update(MmsValue_getElement(MmsGooseControlBlock_getMmsValues(mmsGCB), 2), value);
                allowAccess = true;
            }
#endif

#if (CONFIG_GOOSE_CONFREV_WRITABLE == 1)
            if (strcmp(varName, "ConfRev") == 0) {
                MmsValue_update(MmsValue_getElement(MmsGooseControlBlock_getMmsValues(mmsGCB), 3), value);
                allowAccess = true;
            }
#endif

#if (CONFIG_GOOSE_NDSCOM_WRITABLE == 1)
            if (strcmp(varName, "NdsCom") == 0) {
                MmsValue_update(MmsValue_getElement(MmsGooseControlBlock_getMmsValues(mmsGCB), 4), value);
                allowAccess = true;
            }
#endif

#if (CONFIG_GOOSE_DSTADDRESS_WRITABLE == 1)
            if (memcmp(varName, "DstAddress", 9) == 0) {
                MmsValue* subValue = MmsValue_getSubElement(MmsGooseControlBlock_getMmsValues(mmsGCB),
                                                            MmsGooseControlBlock_getVariableSpecification(mmsGCB), varName);

                if (subValue == nullptr)
                    return DATA_ACCESS_ERROR_INVALID_ADDRESS;

                if (MmsValue_update(subValue, value))
                    return DATA_ACCESS_ERROR_SUCCESS;
                else
                    return DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
            }
#endif

#if (CONFIG_GOOSE_MINTIME_WRITABLE == 1)
            if (strcmp(varName, "MinTime") == 0) {
                MmsValue_update(MmsValue_getElement(MmsGooseControlBlock_getMmsValues(mmsGCB), 6), value);
                allowAccess = true;
            }
#endif

#if (CONFIG_GOOSE_MAXTIME_WRITABLE == 1)
            if (strcmp(varName, "MaxTime") == 0) {
                MmsValue_update(MmsValue_getElement(MmsGooseControlBlock_getMmsValues(mmsGCB), 7), value);
                allowAccess = true;
            }
#endif

#if (CONFIG_GOOSE_FIXEDOFFS_WRITABLE == 1)
            if (strcmp(varName, "FixedOffs") == 0) {
                MmsValue_update(MmsValue_getElement(MmsGooseControlBlock_getMmsValues(mmsGCB), 8), value);
                allowAccess = true;
            }
#endif

            if (allowAccess)
                return DATA_ACCESS_ERROR_SUCCESS;
            else
                return DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;

        }
    }
}

#endif /* (CONFIG_INCLUDE_GOOSE_SUPPORT == 1) */

static GspMmsValue*
checkIfValueBelongsToModelNode(GspDataAttribute* dataAttribute, GspMmsValue* value, GspMmsValue* newValue)
{
    if (dataAttribute->mmsValue == value)
        return newValue;

    GspDataAttribute* child = (GspDataAttribute*) dataAttribute->firstChild;

    while (child != nullptr) {
        GspMmsValue* tmpValue = checkIfValueBelongsToModelNode(child, value, newValue);

        if (tmpValue != nullptr)
            return tmpValue;
        else
            child = (GspDataAttribute*) child->sibling;
    }

    if (GspMmsValue_getType(value) == Data_PR_structure) {
        int elementCount = GspMmsValue_getArraySize(value);

        int i;
        for (i = 0; i < elementCount; i++) {
            GspMmsValue* childValue = GspMmsValue_getElement(value, i);
            GspMmsValue* childNewValue = GspMmsValue_getElement(newValue, i);

            GspMmsValue* tmpValue = checkIfValueBelongsToModelNode(dataAttribute, childValue, childNewValue);

            if (tmpValue != nullptr)
                return tmpValue;
        }
    }

    return nullptr;
}

static GspFunctionalConstraint
getFunctionalConstraintForWritableNode(GspMmsMapping* self, char* separator)
{
    if (isFunctionalConstraintCF(separator))
        return DLT860_FC_CF;
    if (isFunctionalConstraintDC(separator))
        return DLT860_FC_DC;
    if (isFunctionalConstraintSP(separator))
        return DLT860_FC_SP;
    if (isFunctionalConstraintSV(separator))
        return DLT860_FC_SV;
    if (isFunctionalConstraintSE(separator))
        return DLT860_FC_SE;

    return DLT860_FC_NONE;
}

static GspAccessPolicy
getAccessPolicyForFC(GspMmsMapping* self, GspFunctionalConstraint fc)
{
    if (fc == DLT860_FC_CF) {
        if (self->iedServer->writeAccessPolicies & ALLOW_WRITE_ACCESS_CF)
            return ACCESS_POLICY_ALLOW;
        else
            return ACCESS_POLICY_DENY;
    }

    if (fc == DLT860_FC_DC) {
        if (self->iedServer->writeAccessPolicies & ALLOW_WRITE_ACCESS_DC)
            return ACCESS_POLICY_ALLOW;
        else
            return ACCESS_POLICY_DENY;
    }

    if (fc == DLT860_FC_SP) {
        if (self->iedServer->writeAccessPolicies & ALLOW_WRITE_ACCESS_SP)
            return ACCESS_POLICY_ALLOW;
        else
            return ACCESS_POLICY_DENY;
    }

    if (fc == DLT860_FC_SV) {
        if (self->iedServer->writeAccessPolicies & ALLOW_WRITE_ACCESS_SV)
            return ACCESS_POLICY_ALLOW;
        else
            return ACCESS_POLICY_DENY;
    }

    if (fc == DLT860_FC_SE) {
        if (self->iedServer->writeAccessPolicies & ALLOW_WRITE_ACCESS_SE)
            return ACCESS_POLICY_ALLOW;
        else
            return ACCESS_POLICY_DENY;
    }

    return ACCESS_POLICY_DENY;
}

static GspMmsDataAccessError
mmsWriteHandler(void* parameter, GspMmsDomain* domain,
                char* variableId, GspMmsValue* value, GspMmsServerConnection connection)
{
    GspMmsMapping* self = (GspMmsMapping*) parameter;

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: Write requested %s\n", variableId);

    /* Access control based on functional constraint */

    char* separator = strchr(variableId, '$');

    if (separator == nullptr)
        return GSP_DATA_ACCESS_ERROR_INVALID_ADDRESS;

    int lnNameLength = separator - variableId;

#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
    /* Controllable objects - CO */
    if (isControllable(separator)) {
        return GspControl_writeAccessControlObject(self, domain, variableId, value,
                                                   connection);
    }
#endif /* (CONFIG_DLT860_CONTROL_SERVICE == 1) */

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)

    /* Goose control block - GO */
    if (isGooseControlBlock(separator))
        return writeAccessGooseControlBlock(self, domain, variableId, value);

#endif /* (CONFIG_INCLUDE_GOOSE_SUPPORT == 1) */

#if (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1)

    /* Sampled Value control block - MS/US */
    if (isSampledValueControlBlock(separator))
        return LIBIEC61850_SV_writeAccessSVControlBlock(self, domain, variableId, value, connection);

#endif /* (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1) */

#if (CONFIG_DLT860_LOG_SERVICE == 1)

    /* Log control block - LG */
    if (isLogControlBlock(separator))
        return Gsp_LOG_SVC_writeAccessLogControlBlock(self, domain, variableId, value, connection);

#endif /* (CONFIG_DLT860_LOG_SERVICE == 1) */

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
    /* Report control blocks - BR, RP */
    if (isReportControlBlock(separator)) {

        char* reportName = GspMmsMapping_getNextNameElement(separator + 1);

        if (reportName == nullptr)
            return GSP_DATA_ACCESS_ERROR_OBJECT_NONE_EXISTENT;

        separator = strchr(reportName, '$');

        int variableIdLen;

        if (separator != nullptr)
            variableIdLen = separator - variableId;
        else
            variableIdLen = strlen(variableId);

        GspLinkedList nextElement = self->reportControls;

        for(auto &item : *nextElement)
        {
            GspReportControl* rc = (GspReportControl*) item;

            if (rc->domain == domain) {

                int parentLNNameStrLen = strlen(rc->parentLN->name);

                if (parentLNNameStrLen != lnNameLength)
                    continue;

                if (memcmp(rc->parentLN->name, variableId, parentLNNameStrLen) != 0)
                    continue;

                int rcNameLen = strlen(rc->name);

                if (rcNameLen == variableIdLen) {

                    if (strncmp(variableId, rc->name, variableIdLen) == 0) {
                        char* elementName = variableId + rcNameLen + 1;

                        return GspReporting_RCBWriteAccessHandler(self, rc, elementName, value, connection);
                    }
                }
            }
        }

        return GSP_DATA_ACCESS_ERROR_OBJECT_NONE_EXISTENT;
    }
#endif /* (CONFIG_DLT860_REPORT_SERVICE == 1) */

#if (CONFIG_DLT860_SETTING_GROUPS == 1)
    if (isSettingGroupControlBlock(separator)) {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: Access to SGCB\n");

        char* nextSep = strchr(separator + 1, '$');

        if (nextSep != nullptr) {
            nextSep = strchr(nextSep + 1, '$');

            char* nameId = nextSep + 1;

            if (strcmp(nameId, "ActSG") == 0) {
                GspSettingGroup* sg = GspgetSettingGroupByMmsDomain(self, domain);

                if (sg != nullptr) {
                    uint32_t val = GspMmsValue_toUint32(value);

                    if ((val > 0) && (val <= sg->sgcb->numOfSGs)) {
                        if (val != sg->sgcb->actSG) {

                            if (sg->actSgChangedHandler != nullptr) {
                                if (sg->actSgChangedHandler(sg->actSgChangedHandlerParameter, sg->sgcb,
                                                            (uint8_t) val, (GspClientConnection) connection))
                                {
                                    sg->sgcb->actSG = val;

                                    GspMmsValue* actSg = GspMmsValue_getElement(sg->sgcbMmsValues, 1);
                                    GspMmsValue* lActTm = GspMmsValue_getElement(sg->sgcbMmsValues, 4);

                                    GspMmsValue_setUint8(actSg, sg->sgcb->actSG);
                                    GspMmsValue_setUtcTimeMs(lActTm, GSP_Hal_getTimeInMs());
                                }

                                else
                                    return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
                            }
                            else
                                return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;

                        }

                        return GSP_DATA_ACCESS_ERROR_SUCCESS;
                    }
                    else
                        return GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
                }
            }
            else if (strcmp(nameId, "EditSG") == 0) {
                GspSettingGroup* sg = GspgetSettingGroupByMmsDomain(self, domain);

                if (sg != nullptr) {
                    uint32_t val = GspMmsValue_toUint32(value);

                    if ((sg->editingClient != nullptr) && ( sg->editingClient != (GspClientConnection) connection))
                        /* Edit SG was set by other client */
                        return GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;

                    if (val == 0) {
                        unselectEditSettingGroup(sg);
                        return GSP_DATA_ACCESS_ERROR_SUCCESS;
                    }

                    if ((val > 0) && (val <= sg->sgcb->numOfSGs)) {

                        if (sg->editSgChangedHandler != nullptr) {

                            if (sg->editSgChangedHandler(sg->editSgChangedHandlerParameter, sg->sgcb,
                                                         (uint8_t) val, (GspClientConnection) connection))
                            {
                                sg->sgcb->editSG = val;
                                sg->editingClient = (GspClientConnection) connection;

                                sg->reservationTimeout = GSP_Hal_getTimeInMs() + (sg->sgcb->resvTms * 1000);

                                GspMmsValue* editSg = GspMmsValue_getElement(sg->sgcbMmsValues, 2);
                                GspMmsValue* resvTms = GspMmsValue_getElement(sg->sgcbMmsValues, 5);

                                GspMmsValue_setUint16(resvTms, sg->sgcb->resvTms);
                                GspMmsValue_setUint8(editSg, sg->sgcb->editSG);

                                return GSP_DATA_ACCESS_ERROR_SUCCESS;
                            }
                            else
                                return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
                        }
                        else
                            return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;

                    }
                    else
                        return GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;

                }
            }
            else if (strcmp(nameId, "CnfEdit") == 0) {
                GspSettingGroup* sg = GspgetSettingGroupByMmsDomain(self, domain);

                if (sg != nullptr) {
                    bool val = GspMmsValue_getBoolean(value);

                    if (val == true) {
                        if (sg->sgcb->editSG != 0) {
                            if (sg->editingClient == (GspClientConnection) connection) {
                                if (sg->editSgConfirmedHandler != nullptr) {
                                    sg->editSgConfirmedHandler(sg->editSgConfirmedHandlerParameter, sg->sgcb,
                                                               sg->sgcb->editSG);

                                    unselectEditSettingGroup(sg);

                                    return GSP_DATA_ACCESS_ERROR_SUCCESS;
                                }
                                else
                                    return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
                            }
                            else
                                return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
                        }
                        else
                            return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
                    }
                    else
                        return GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
                }
            }
        }

        return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
    }
#endif /* (CONFIG_DLT860_SETTING_GROUPS == 1) */

    GspFunctionalConstraint fc = getFunctionalConstraintForWritableNode(self, separator);

#if (CONFIG_DLT860_SETTING_GROUPS == 1)
    if (fc == DLT860_FC_SE) {
        GspSettingGroup* sg = GspgetSettingGroupByMmsDomain(self, domain);

        if (sg != nullptr) {
            if (sg->editingClient != (GspClientConnection) connection)
                return GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
        }
        else
            return GSP_DATA_ACCESS_ERROR_OBJECT_NONE_EXISTENT;
    }
#endif /* (CONFIG_DLT860_SETTING_GROUPS == 1) */

    /* writable data model elements - SP, SV, CF, DC */
    if (fc != DLT860_FC_NONE) {
        GspMmsValue* cachedValue;

        cachedValue = MmsServer_getValueFromCache(self->mmsServer, domain, variableId);

        if (cachedValue != nullptr) {

            if (!GspMmsValue_equalTypes(cachedValue, value))
                return GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;

            bool handlerFound = false;

            GspAccessPolicy nodeAccessPolicy = getAccessPolicyForFC(self, fc);

            if (DEBUG_IED_SERVER)
                printf("IED_SERVER: write to %s policy:%i\n", variableId, nodeAccessPolicy);

#if (CONFIG_DLT860_SETTING_GROUPS == 1)
            if (isFunctionalConstraintSE(separator)) {
                GspSettingGroup* sg = GspgetSettingGroupByMmsDomain(self, domain);

                if (sg != nullptr) {
                    if (sg->sgcb->editSG == 0)
                        return GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
                }
                else
                    return GSP_DATA_ACCESS_ERROR_OBJECT_NONE_EXISTENT;
            }
#endif

            /* Call write access handlers */
            for(auto &item : *(self->attributeAccessHandlers))
            {
                AttributeAccessHandler* accessHandler = (AttributeAccessHandler*) item;
                GspDataAttribute* dataAttribute = accessHandler->attribute;

                if (nodeAccessPolicy == ACCESS_POLICY_ALLOW) {

                    GspMmsValue* matchingValue = checkIfValueBelongsToModelNode(dataAttribute, cachedValue, value);

                    if (matchingValue != nullptr) {

                        GspClientConnection clientConnection = Gsp_private_IedServer_getClientConnectionByHandle(self->iedServer,
                                                                                                                 connection);

                        GspMmsDataAccessError handlerResult =
                                accessHandler->handler(dataAttribute, matchingValue, clientConnection,
                                                       accessHandler->parameter);

                        if (handlerResult == GSP_DATA_ACCESS_ERROR_SUCCESS)
                            handlerFound = true;
                        else
                            return handlerResult;
                    }

                }
                else { /* if ACCESS_POLICY_DENY only allow direct access to handled data attribute */
                    if (dataAttribute->mmsValue == cachedValue) {

                        GspClientConnection clientConnection = Gsp_private_IedServer_getClientConnectionByHandle(self->iedServer,
                                                                                                                 connection);

                        GspMmsDataAccessError handlerResult =
                                accessHandler->handler(dataAttribute, value, clientConnection,
                                                       accessHandler->parameter);

                        if (handlerResult == GSP_DATA_ACCESS_ERROR_SUCCESS) {
                            handlerFound = true;
                            break;
                        }
                        else
                            return handlerResult;
                    }

                }

            }

            /* DENY access if no handler is found and default policy is DENY */
            if (!handlerFound) {

                if (nodeAccessPolicy == ACCESS_POLICY_DENY)
                    return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;

            }
            auto model = self->domainIedMap[domain->domainName];

            if(!model)
            {
                return GSP_DATA_ACCESS_ERROR_OBJECT_NONE_EXISTENT;
            }
            GspDataAttribute* da = GspIedModel_lookupDataAttributeByMmsValue(model, cachedValue);

            if (da != nullptr)
                GspIedServer_updateAttributeValue(self->iedServer, da, value);
            else
                return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;

            return GSP_DATA_ACCESS_ERROR_SUCCESS;
        }
        else
            return GSP_DATA_ACCESS_ERROR_OBJECT_NONE_EXISTENT;
    }

    return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
}

static AttributeAccessHandler*
getAccessHandlerForAttribute(GspMmsMapping* self, GspDataAttribute* dataAttribute)
{
    for(auto &item : *(self->attributeAccessHandlers))
    {
        AttributeAccessHandler* accessHandler = (AttributeAccessHandler*) item;

        if (accessHandler->attribute == dataAttribute)
            return accessHandler;
    }

    return nullptr;
}

void
GspMmsMapping_installWriteAccessHandler(GspMmsMapping* self, GspDataAttribute* dataAttribute, GspWriteAccessHandler handler, void* parameter)
{
    AttributeAccessHandler* accessHandler = getAccessHandlerForAttribute(self, dataAttribute);

    if (accessHandler == nullptr) {
        accessHandler = (AttributeAccessHandler*) GLOBAL_MALLOC(sizeof(AttributeAccessHandler));

        accessHandler->attribute = dataAttribute;
        accessHandler->parameter = parameter;
        GspLinkedList_add(self->attributeAccessHandlers, (void*) accessHandler);
    }

    accessHandler->handler = handler;
}

void
GspMmsMapping_installReadAccessHandler(GspMmsMapping* self, GspReadAccessHandler handler, void* parameter)
{
#if (CONFIG_IEC61850_SUPPORT_USER_READ_ACCESS_CONTROL == 1)
    self->readAccessHandler = handler;
    self->readAccessHandlerParameter = parameter;
#endif
}

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)

static MmsValue*
readAccessGooseControlBlock(MmsMapping* self, MmsDomain* domain, char* variableIdOrig)
{
    MmsValue* value = nullptr;

    char variableId[130];

    strncpy(variableId, variableIdOrig, 129);

    char* separator = strchr(variableId, '$');

    *separator = 0;

    char* lnName = variableId;

    if (lnName == nullptr)
        return nullptr;

    char* objectName = MmsMapping_getNextNameElement(separator + 1);

    if (objectName == nullptr)
        return nullptr;

    char* varName = MmsMapping_getNextNameElement(objectName);

    if (varName != nullptr)
        *(varName - 1) = 0;

    MmsGooseControlBlock mmsGCB = lookupGCB(self, domain, lnName, objectName);

    if (mmsGCB != nullptr) {
        if (varName != nullptr) {
            value = MmsValue_getSubElement(MmsGooseControlBlock_getMmsValues(mmsGCB),
                                           MmsGooseControlBlock_getVariableSpecification(mmsGCB), varName);
        }
        else {
            value = MmsGooseControlBlock_getMmsValues(mmsGCB);
        }
    }

    return value;
}

#endif /* (CONFIG_INCLUDE_GOOSE_SUPPORT == 1) */


static GspMmsValue*
mmsReadHandler(void* parameter, GspMmsDomain* domain, char* variableId, GspMmsServerConnection connection)
{
    GspMmsMapping* self = (GspMmsMapping*) parameter;

    GspMmsValue* retValue = nullptr;

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: mmsReadHandler: Requested %s\n", variableId);

    char* separator = strchr(variableId, '$');

    if (separator == nullptr)
        return retValue;

    int lnNameLength = separator - variableId;

#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
    /* Controllable objects - CO */
    if (isControllable(separator)) {
        retValue = Control_readAccessControlObject(self, domain, variableId, connection);
        return retValue;
    }
#endif


#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
    /* GOOSE control blocks - GO */
    if (isGooseControlBlock(separator)) {
        retValue = readAccessGooseControlBlock(self, domain, variableId);
        goto exit_function;
    }
#endif

#if (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1)
    /* Sampled Value control blocks - MS/US */
    if (isSampledValueControlBlock(separator)) {
        retValue = LIBIEC61850_SV_readAccessSampledValueControlBlock(self, domain, variableId);
        goto exit_function;
    }
#endif

#if (CONFIG_DLT860_LOG_SERVICE == 1)
    /* LOG control block - LG */
    if (isLogControlBlock(separator)) {
        retValue = Gsp_LOG_SVC_readAccessControlBlock(self, domain, variableId);
        return retValue;
    }
#endif

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
    /* Report control blocks - BR, RP */
    if (isReportControlBlock(separator)) {

        GspLinkedList reportControls = self->reportControls;

        GspLinkedList nextElement = reportControls;

        char* reportName = GspMmsMapping_getNextNameElement(separator + 1);

        if (reportName == nullptr) {
            retValue = nullptr;
            return nullptr;
        }

        separator = strchr(reportName, '$');

        size_t variableIdLen;

        if (separator != nullptr)
            variableIdLen = separator - variableId;
        else
            variableIdLen = strlen(variableId);
        for(auto &item : *nextElement)
        {
            GspReportControl* rc = (GspReportControl*) item;

            if (rc->domain == domain) {

                int parentLNNameStrLen = strlen(rc->parentLN->name);

                if (parentLNNameStrLen != lnNameLength)
                    continue;

                if (memcmp(rc->parentLN->name, variableId, parentLNNameStrLen) != 0)
                    continue;

                if (strlen(rc->name) == variableIdLen) {
                    if (strncmp(variableId, rc->name, variableIdLen) == 0) {

                        char* elementName = GspMmsMapping_getNextNameElement(reportName);

                        GspReportControl_readAccess(rc, elementName);

                        GspMmsValue* value = nullptr;

                        if (elementName != nullptr)
                            value = GspReportControl_getRCBValue(rc, elementName);
                        else
                            value = rc->rcbValues;

                        retValue = value;

                        return retValue;
                    }
                }

            }

        }
    }
#endif /* (CONFIG_DLT860_REPORT_SERVICE == 1) */

    /* handle read access to other objects */

    return retValue;
}

void
GspMmsMapping_setMmsServer(GspMmsMapping* self, GspMmsServer server)
{
    self->mmsServer = server;
}

#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
static void
unselectControlsForConnection(GspMmsMapping* self, GspMmsServerConnection connection)
{
    for(auto &item : *(self->controlObjects))
    {
        GspControlObject* controlObject = (GspControlObject*) item;

        if (GspControlObject_unselect(controlObject, connection))
            break;

    }
}
#endif /* (CONFIG_DLT860_CONTROL_SERVICE == 1) */

static void /* is called by MMS server layer and runs in the connection handling thread */
mmsConnectionHandler(void* parameter, GspMmsServerConnection connection, GspMmsServerEvent event)
{
    GspMmsMapping* self = (GspMmsMapping*) parameter;

    if (event == GSP_MMS_SERVER_CONNECTION_TICK) {
        GspReporting_sendReports(self, connection);
    }
    else if (event == GSP_MMS_SERVER_CONNECTION_CLOSED) {
        GspClientConnection clientConnection = Gsp_private_IedServer_getClientConnectionByHandle(self->iedServer, connection);

        /* call user provided handler function */
        if (self->connectionIndicationHandler != nullptr)
            self->connectionIndicationHandler(self->iedServer, clientConnection, false,
                                              self->connectionIndicationHandlerParameter);

        Gsp_private_IedServer_removeClientConnection(self->iedServer, clientConnection);

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
        GspReporting_deactivateReportsForConnection(self, connection);
#endif

#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
        unselectControlsForConnection(self, connection);
#endif

#if (CONFIG_DLT860_SETTING_GROUPS == 1)
        unselectAllSettingGroups(self, connection);
#endif

        Gsp_private_ClientConnection_destroy(clientConnection);
    }
    else if (event == GSP_MMS_SERVER_NEW_CONNECTION) {
        /* call user provided handler function */
        GspClientConnection newClientConnection = Gsp_private_ClientConnection_create(connection);

        Gsp_private_IedServer_addNewClientConnection(self->iedServer, newClientConnection);

        /* call user provided handler function */
        if (self->connectionIndicationHandler != nullptr)
            self->connectionIndicationHandler(self->iedServer, newClientConnection, true,
                                              self->connectionIndicationHandlerParameter);
    }
}

static GspMmsDataAccessError
mmsReadAccessHandler (void* parameter, GspMmsDomain* domain, char* variableId, GspMmsServerConnection connection)
{
    GspMmsMapping* self = (GspMmsMapping*) parameter;

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: mmsReadAccessHandler: Requested %s\n", variableId);

    char* separator = strchr(variableId, '$');

#if (CONFIG_DLT860_SETTING_GROUPS == 1)

    if (separator) {
        if (isFunctionalConstraintSE(separator)) {
            GspSettingGroup* sg = GspgetSettingGroupByMmsDomain(self, domain);

            if (sg != nullptr) {
                if (sg->sgcb->editSG == 0)
                    return GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
            }
            else
                return GSP_DATA_ACCESS_ERROR_OBJECT_NONE_EXISTENT;
        }
    }

#endif /* (CONFIG_DLT860_SETTING_GROUPS == 1) */

#if (CONFIG_IEC61850_SUPPORT_USER_READ_ACCESS_CONTROL == 1)
    if (self->readAccessHandler != nullptr)
    {
        char* ldName = MmsDomain_getName(domain);

        LogicalDevice* ld = IedModel_getDevice(self->model, ldName);

        if (ld != nullptr) {

            char str[65];

            FunctionalConstraint fc;

            if (separator != nullptr) {
                fc = FunctionalConstraint_fromString(separator + 1);

                if (fc == DLT860_FC_BR || fc == DLT860_FC_US ||
                        fc == DLT860_FC_MS || fc == DLT860_FC_RP ||
                        fc == DLT860_FC_LG || fc == DLT860_FC_GO)
                {
                    return DATA_ACCESS_ERROR_SUCCESS;
                }
                else {

                    StringUtils_createStringFromBufferInBuffer(str, (uint8_t*) variableId, separator - variableId);

                    LogicalNode* ln = LogicalDevice_getLogicalNode(ld, str);

                    if (ln != nullptr) {


                        char* doStart = strchr(separator + 1, '$');


                        if (doStart != nullptr) {

                            char* doEnd = strchr(doStart + 1, '$');

                            if (doEnd == nullptr) {
                                StringUtils_copyStringToBuffer(doStart + 1, str);
                            }
                            else {
                                doEnd--;

                                StringUtils_createStringFromBufferInBuffer(str, (uint8_t*) (doStart + 1), doEnd - doStart);
                            }

                            ModelNode* dobj = ModelNode_getChild((ModelNode*) ln, str);

                            if (dobj != nullptr) {

                                if (dobj->modelType == DataObjectModelType) {

                                    ClientConnection clientConnection = private_IedServer_getClientConnectionByHandle(self->iedServer,
                                                                                                                      connection);

                                    return self->readAccessHandler(ld, ln, (DataObject*) dobj, fc, clientConnection,
                                                                   self->readAccessHandlerParameter);
                                }
                            }
                        }
                    }
                }
            }
        }

        return DATA_ACCESS_ERROR_OBJECT_ACCESS_UNSUPPORTED;
    }
#endif /* CONFIG_IEC61850_SUPPORT_USER_READ_ACCESS_CONTROL */

    return GSP_DATA_ACCESS_ERROR_SUCCESS;
}

static GspMmsError
variableListChangedHandler (void* parameter, bool create, GspMmsVariableListType listType, GspMmsDomain* domain,
                            char* listName, GspMmsServerConnection connection)
{
    GspMmsError allow = GSP_MMS_ERROR_NONE;

    //#if (DEBUG_IED_SERVER == 1)
    //    if (create)
    //        printf("IED_SERVER: create data set ");
    //    else
    //        printf("IED_SERVER: delete data set ");

    //    switch (listType) {
    //    case MMS_VMD_SPECIFIC:
    //        printf("VMD ");
    //        break;
    //    case MMS_ASSOCIATION_SPECIFIC:
    //        printf("association ");
    //        break;
    //    case MMS_DOMAIN_SPECIFIC:
    //        printf("domain ");
    //        break;
    //    }

    //    printf("specific (name=%s)\n", listName);
    //#endif /* (DEBUG_IED_SERVER == 1) */

    //    MmsMapping* self = (MmsMapping*) parameter;

    //    if (create) {
    //        if (listType == MMS_DOMAIN_SPECIFIC) {
    //            /* check if LN exists - otherwise reject request (to fulfill test case sDsN1c) */

    //            allow = MMS_ERROR_ACCESS_OBJECT_NON_EXISTENT;

    //            IedModel* model = self->model;

    //            LogicalDevice* ld = IedModel_getDevice(model, domain->domainName);

    //            if (ld != nullptr) {

    //                char lnName[129];

    //                char* separator = strchr(listName, '$');

    //                if (separator != nullptr) {
    //                    int lnNameLen = separator - listName;

    //                    memcpy(lnName, listName, lnNameLen);
    //                    lnName[lnNameLen] = 0;

    //                    if (LogicalDevice_getLogicalNode(ld, lnName) != nullptr)
    //                        allow = MMS_ERROR_NONE;
    //                }

    //            }

    //        }
    //    }
    //    else {
    //        /* Check if data set is referenced in a report */

    //        LinkedList rcElement = self->reportControls;

    //        while ((rcElement = LinkedList_getNext(rcElement)) != nullptr) {
    //            ReportControl* rc = (ReportControl*) rcElement->data;

    //            if (rc->isDynamicDataSet) {
    //                if (rc->dataSet != nullptr) {

    //                    if (listType == MMS_DOMAIN_SPECIFIC) {
    //                        if (rc->dataSet->logicalDeviceName != nullptr) {
    //                            if (strcmp(rc->dataSet->name, listName) == 0) {
    //                                if (strcmp(rc->dataSet->logicalDeviceName, MmsDomain_getName(domain) + strlen(self->model->name)) == 0) {
    //                                    allow = MMS_ERROR_SERVICE_OBJECT_CONSTRAINT_CONFLICT;
    //                                    break;
    //                                }
    //                            }
    //                        }
    //                    }
    //                    else if (listType == MMS_VMD_SPECIFIC) {
    //                        if (rc->dataSet->logicalDeviceName == nullptr) {
    //                            if (strcmp(rc->dataSet->name, listName) == 0) {
    //                                allow = MMS_ERROR_SERVICE_OBJECT_CONSTRAINT_CONFLICT;
    //                               break;
    //                            }
    //                        }
    //                    }
    //                    else if (listType == MMS_ASSOCIATION_SPECIFIC) {
    //                        if (rc->dataSet->logicalDeviceName == nullptr) {
    //                            if (strcmp(rc->dataSet->name, listName) == 0) {
    //                                allow = MMS_ERROR_SERVICE_OBJECT_CONSTRAINT_CONFLICT;
    //                                break;
    //                            }
    //                        }
    //                    }

    //                }
    //            }
    //        }


    //#if (CONFIG_DLT860_LOG_SERVICE == 1)
    //        /* check if data set is referenced in a log control block*/
    //        LinkedList logElement = self->logControls;

    //        while ((logElement = LinkedList_getNext(logElement)) != nullptr) {
    //            LogControl* lc = (LogControl*) logElement->data;

    //            if (lc->isDynamicDataSet) {
    //                if (lc->dataSet != nullptr) {

    //                    if (listType == MMS_DOMAIN_SPECIFIC) {
    //                        if (lc->dataSet->logicalDeviceName != nullptr) {
    //                            if (strcmp(lc->dataSet->name, listName) == 0) {
    //                                if (strcmp(lc->dataSet->logicalDeviceName, MmsDomain_getName(domain) + strlen(self->model->name)) == 0) {
    //                                    allow = MMS_ERROR_SERVICE_OBJECT_CONSTRAINT_CONFLICT;
    //                                    break;
    //                                }
    //                            }
    //                        }
    //                    }
    //                    else if (listType == MMS_VMD_SPECIFIC) {
    //                        if (lc->dataSet->logicalDeviceName == nullptr) {
    //                            if (strcmp(lc->dataSet->name, listName) == 0) {
    //                                allow = MMS_ERROR_SERVICE_OBJECT_CONSTRAINT_CONFLICT;
    //                               break;
    //                            }
    //                        }
    //                    }

    //                }
    //            }
    //        }

    //#endif /* (CONFIG_DLT860_LOG_SERVICE == 1) */
    //    }

    return allow;
}

void
GspMmsMapping_installHandlers(GspMmsMapping* self)
{
    MmsServer_installReadHandler(self->mmsServer, mmsReadHandler, (void*) self);
    MmsServer_installWriteHandler(self->mmsServer, mmsWriteHandler, (void*) self);
    MmsServer_installReadAccessHandler(self->mmsServer, mmsReadAccessHandler, (void*) self);
    MmsServer_installConnectionHandler(self->mmsServer, mmsConnectionHandler, (void*) self);
    GspMmsServer_installVariableListChangedHandler(self->mmsServer, variableListChangedHandler, (void*) self);
}

void
GspMmsMapping_setConnectionIndicationHandler(GspMmsMapping* self, GspIedConnectionIndicationHandler handler, void* parameter)
{
    self->connectionIndicationHandler = handler;
    self->connectionIndicationHandlerParameter = parameter;
}

static bool
isMemberValueRecursive(GspMmsValue* container, GspMmsValue* value)
{
    bool isMemberValue = false;

    if (container == value)
        isMemberValue = true;
    else {
        if ((GspMmsValue_getType(container) == Data_PR_structure) ||
                (GspMmsValue_getType(container) == Data_PR_array))
        {

            int compCount = GspMmsValue_getArraySize(container);
            int i;
            for (i = 0; i < compCount; i++) {
                if (isMemberValueRecursive(GspMmsValue_getElement(container, i), value)) {
                    isMemberValue = true;
                    break;
                }
            }
        }
    }

    return isMemberValue;
}

#if ((CONFIG_DLT860_REPORT_SERVICE == 1) || (CONFIG_INCLUDE_GOOSE_SUPPORT == 1))

static bool
DataSet_isMemberValue(GspDataSet* dataSet, GspMmsValue* value, int* index)
{
    int i = 0;

    GspDataSetEntry* dataSetEntry = dataSet->fcdas;

    while (dataSetEntry != nullptr) {

        GspMmsValue* dataSetValue = dataSetEntry->value;

        if (dataSetValue != nullptr) { /* prevent invalid data set members */
            if (isMemberValueRecursive(dataSetValue, value)) {
                if (index != nullptr)
                    *index = i;

                return true;
            }
        }

        i++;

        dataSetEntry = dataSetEntry->sibling;
    }

    return false;
}
#endif /* ((CONFIG_DLT860_REPORT_SERVICE == 1) || (CONFIG_INCLUDE_GOOSE_SUPPORT)) */

#if (CONFIG_DLT860_LOG_SERVICE == 1)

static bool
GspDataSet_isMemberValueWithRef(GspDataSet* dataSet, GspMmsValue* value, char* dataRef, const char* iedName, int* index)
{
    int i = 0;

    GspDataSetEntry* dataSetEntry = dataSet->fcdas;

    while (dataSetEntry != nullptr) {

        GspMmsValue *dataSetValue = dataSetEntry->value;

        if (dataSetValue != nullptr) { /* prevent invalid data set members */
            if (isMemberValueRecursive(dataSetValue, value)) {
                if (dataRef != nullptr)
                    sprintf(dataRef, "%s%s/%s", iedName, dataSetEntry->logicalDeviceName, dataSetEntry->variableName);

                if (index)
                    *index = i;

                return true;
            }
        }

        i++;

        dataSetEntry = dataSetEntry->sibling;
    }

    return false;
}

#endif /* (CONFIG_DLT860_LOG_SERVICE == 1) */

#if (CONFIG_DLT860_REPORT_SERVICE == 1)

void GspReportControl_triggerReportObservers(GspReportControl* rc, int flag, bool modelLocked, int index)
{
    if (rc->enabled || (rc->buffered && rc->dataSet != nullptr)) {

        switch (flag) {
        case GSP_REPORT_CONTROL_VALUE_UPDATE:
            if ((rc->triggerOps & GSP_TRG_OPT_DATA_UPDATE) == 0)
                return;
            break;
        case GSP_REPORT_CONTROL_VALUE_CHANGED:
            if (((rc->triggerOps & GSP_TRG_OPT_DATA_CHANGED) == 0) &&
                    ((rc->triggerOps & GSP_TRG_OPT_DATA_UPDATE) == 0))
                return;
            break;
        case GSP_REPORT_CONTROL_QUALITY_CHANGED:
            if ((rc->triggerOps & GSP_TRG_OPT_QUALITY_CHANGED) == 0)
                return;
            break;
        default:
            return;
        }

        GspReportControl_valueUpdated(rc, index, flag, modelLocked);
    }
}

void
GspMmsMapping_triggerReportObservers(GspMmsMapping* self, GspMmsValue* value, int flag)
{
    GspLinkedList element = self->reportControls;

    bool modelLocked = self->isModelLocked;
    for(auto &item : *element)
    {
        GspReportControl* rc = (GspReportControl*) item;

        if (rc->enabled || (rc->buffered && rc->dataSet != nullptr)) {
            int index;

            switch (flag) {
            case GSP_REPORT_CONTROL_VALUE_UPDATE:
                if ((rc->triggerOps & GSP_TRG_OPT_DATA_UPDATE) == 0)
                    continue;
                break;
            case GSP_REPORT_CONTROL_VALUE_CHANGED:
                if (((rc->triggerOps & GSP_TRG_OPT_DATA_CHANGED) == 0) &&
                        ((rc->triggerOps & GSP_TRG_OPT_DATA_UPDATE) == 0))
                    continue;
                break;
            case GSP_REPORT_CONTROL_QUALITY_CHANGED:
                if ((rc->triggerOps & GSP_TRG_OPT_QUALITY_CHANGED) == 0)
                    continue;
                break;
            default:
                continue;
            }

            if (DataSet_isMemberValue(rc->dataSet, value, &index)) {

                GspReportControl_valueUpdated(rc, index, flag, modelLocked);
            }
        }
    }

    if (modelLocked == false) {
        GspReporting_processReportEventsAfterUnlock(self);
    }
}

#endif /* (CONFIG_DLT860_REPORT_SERVICE == 1) */

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)

void
MmsMapping_triggerGooseObservers(MmsMapping* self, MmsValue* value)
{
    LinkedList element = self->gseControls;

    while ((element = LinkedList_getNext(element)) != nullptr) {
        MmsGooseControlBlock gcb = (MmsGooseControlBlock) element->data;

        if (MmsGooseControlBlock_isEnabled(gcb)) {
            DataSet* dataSet = MmsGooseControlBlock_getDataSet(gcb);

            if (DataSet_isMemberValue(dataSet, value, nullptr)) {
                MmsGooseControlBlock_observedObjectChanged(gcb);
            }
        }
    }
}

void
MmsMapping_enableGoosePublishing(MmsMapping* self)
{

    LinkedList element = self->gseControls;

    while ((element = LinkedList_getNext(element)) != nullptr) {
        MmsGooseControlBlock gcb = (MmsGooseControlBlock) element->data;

        MmsGooseControlBlock_enable(gcb);
    }

}

void
MmsMapping_useGooseVlanTag(MmsMapping* self, LogicalNode* ln, const char* gcbName, bool useVlanTag)
{
    LinkedList element = self->gseControls;

    while ((element = LinkedList_getNext(element)) != nullptr) {
        MmsGooseControlBlock gcb = (MmsGooseControlBlock) element->data;

        if (ln == nullptr) {
            MmsGooseControlBlock_useGooseVlanTag(gcb, useVlanTag);
        }
        else {
            if ((MmsGooseControlBlock_getLogicalNode(gcb) == ln) && !strcmp(MmsGooseControlBlock_getName(gcb), gcbName)) {
                MmsGooseControlBlock_useGooseVlanTag(gcb, useVlanTag);
            }
        }
    }
}

void
MmsMapping_setGooseInterfaceId(MmsMapping* self,  LogicalNode* ln, const char* gcbName, const char* interfaceId)
{
    LinkedList element = self->gseControls;

    while ((element = LinkedList_getNext(element)) != nullptr) {
        MmsGooseControlBlock gcb = (MmsGooseControlBlock) element->data;

        if (ln == nullptr) {
            MmsGooseControlBlock_setGooseInterfaceId(gcb, interfaceId);
        }
        else {
            if ((MmsGooseControlBlock_getLogicalNode(gcb) == ln) && !strcmp(MmsGooseControlBlock_getName(gcb), gcbName)) {
                MmsGooseControlBlock_setGooseInterfaceId(gcb, interfaceId);
            }
        }
    }
}

void
MmsMapping_disableGoosePublishing(MmsMapping* self)
{
    LinkedList element = self->gseControls;

    while ((element = LinkedList_getNext(element)) != nullptr) {
        MmsGooseControlBlock gcb = (MmsGooseControlBlock) element->data;

        MmsGooseControlBlock_disable(gcb);
    }
}

#endif /* (CONFIG_INCLUDE_GOOSE_SUPPORT == 1) */

#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
void
GspMmsMapping_addControlObject(GspMmsMapping* self, GspControlObject* controlObject)
{
    GspLinkedList_add(self->controlObjects, controlObject);
}

GspControlObject*
GspMmsMapping_getControlObject(GspMmsMapping* self, GspMmsDomain* domain, char* lnName, char* coName)
{
    return GspControl_lookupControlObject(self, domain, lnName, coName);
}
#endif /* (CONFIG_DLT860_CONTROL_SERVICE == 1) */

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)

static void
GOOSE_processGooseEvents(MmsMapping* self, uint64_t currentTimeInMs)
{
    LinkedList element = LinkedList_getNext(self->gseControls);

    while (element != nullptr) {
        MmsGooseControlBlock mmsGCB = (MmsGooseControlBlock) element->data;

        if (MmsGooseControlBlock_isEnabled(mmsGCB)) {
            MmsGooseControlBlock_checkAndPublish(mmsGCB, currentTimeInMs);
        }

        element = LinkedList_getNext(element);
    }
}

#endif /* (CONFIG_INCLUDE_GOOSE_SUPPORT == 1) */

static void
processPeriodicTasks(GspMmsMapping* self)
{
    uint64_t currentTimeInMs = GSP_Hal_getTimeInMs();

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
    GOOSE_processGooseEvents(self, currentTimeInMs);
#endif

#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
    GspControl_processControlActions(self, currentTimeInMs);
#endif

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
    GspReporting_processReportEvents(self, currentTimeInMs);
#endif

#if (CONFIG_DLT860_SETTING_GROUPS == 1)
    GspMmsMapping_checkForSettingGroupReservationTimeouts(self, currentTimeInMs);
#endif

#if (CONFIG_DLT860_LOG_SERVICE == 1)
    GspLogging_processIntegrityLogs(self, currentTimeInMs);
#endif
}

void
GspIedServer_performPeriodicTasks(GspIedServer self)
{
    processPeriodicTasks(self->mmsMapping);
}

#if (CONFIG_MMS_THREADLESS_STACK != 1)
/* single worker thread for all enabled GOOSE and report control blocks */
static void
eventWorkerThread(GspMmsMapping* self)
{
    bool running = true;

    while (running) {

        processPeriodicTasks(self);

        GspThread_sleep(1); /* hand-over control to other threads */

        running = self->reportThreadRunning;
    }

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: event worker thread finished!\n");
}

void
GspMmsMapping_startEventWorkerThread(GspMmsMapping* self)
{
    self->reportThreadRunning = true;

    GspThread thread = GspThread_create((GspThreadExecutionFunction) eventWorkerThread, self, false);
    self->reportWorkerThread = thread;
    GspThread_start(thread);
}

void
GspMmsMapping_stopEventWorkerThread(GspMmsMapping* self)
{
    if (self->reportThreadRunning) {

        self->reportThreadRunning = false;

        if (self->reportWorkerThread) {
            GspThread_destroy(self->reportWorkerThread);
            self->reportWorkerThread = nullptr;
        }
    }
}
#endif /* (CONFIG_MMS_THREADLESS_STACK != 1) */

GspDataSet*
GspMmsMapping_createDataSetByNamedVariableList(GspMmsMapping* self, GspMmsNamedVariableList variableList)
{
    GspDataSet* dataSet = new GspDataSet();
    if (variableList->domain != nullptr)
        dataSet->logicalDeviceName = GspMmsDomain_getName(variableList->domain) + strlen(variableList->domain->modelName);
    else
        dataSet->logicalDeviceName = nullptr; /* name is not relevant for association specific data sets */
    dataSet->iedName = (char *)variableList->domain->modelName;
    dataSet->name = variableList->name;
    dataSet->elementCount = GspLinkedList_size(variableList->listOfVariables);


    GspDataSetEntry* lastDataSetEntry = nullptr;
    for(auto &item : *(variableList->listOfVariables))
    {
        GspMmsAccessSpecifier* listEntry = (GspMmsAccessSpecifier*) item;

        GspDataSetEntry* dataSetEntry = (GspDataSetEntry*) GLOBAL_MALLOC(sizeof(GspDataSetEntry));

        /* use variable name part of domain name as logicalDeviceName */
        dataSetEntry->logicalDeviceName = GspMmsDomain_getName(listEntry->domain) + strlen(variableList->domain->modelName);

        dataSetEntry->variableName = listEntry->variableName;
        dataSetEntry->index = listEntry->arrayIndex;
        dataSetEntry->componentName = listEntry->componentName;
        dataSetEntry->sibling = nullptr;

        if (lastDataSetEntry == nullptr)
            dataSet->fcdas =dataSetEntry;
        else
            lastDataSetEntry->sibling = dataSetEntry;

        dataSetEntry->value =
                MmsServer_getValueFromCache(self->mmsServer, listEntry->domain, listEntry->variableName);
        if(!dataSetEntry->value)
        {
            NLOG_ERROR("!!!!\n");
        }
        lastDataSetEntry = dataSetEntry;
        dataSet->fcdaArray.push_back(dataSetEntry);
    }

    return dataSet;
}

GspMmsNamedVariableList
GspMmsMapping_getDomainSpecificVariableList(GspMmsMapping* self, const char* variableListReference)
{
    char variableListReferenceCopy[193];

    strncpy(variableListReferenceCopy, variableListReference, 192);
    variableListReferenceCopy[192] = 0;

    char* separator = strchr(variableListReferenceCopy, '/');

    if (separator == nullptr)
        return nullptr;

    char* domainName = variableListReferenceCopy;

    char* variableListName = separator + 1;

    *separator = 0;

    GspMmsDomain* domain = GspMmsDevice_getDomain(self->mmsDevice, domainName);

    if (domain == nullptr)
        return nullptr;

    GspMmsNamedVariableList variableList = GspMmsDomain_getNamedVariableList(domain, variableListName);

    return variableList;
}

GspDataSet*
GspMmsMapping_getDomainSpecificDataSet(GspMmsMapping* self, const char* dataSetName)
{
    GspMmsNamedVariableList variableList = GspMmsMapping_getDomainSpecificVariableList(self, dataSetName);

    if (variableList == nullptr)
        return nullptr;

    return GspMmsMapping_createDataSetByNamedVariableList(self, variableList);
}

void
GspMmsMapping_freeDynamicallyCreatedDataSet(GspDataSet* dataSet)
{
    GspDataSetEntry* dataSetEntry = dataSet->fcdas;

    while (dataSetEntry != nullptr) {
        GspDataSetEntry* nextEntry = dataSetEntry->sibling;

        GLOBAL_FREEMEM (dataSetEntry);

        dataSetEntry = nextEntry;
    }
    delete dataSet;
}

GspIedModel *GspMmsMapping_getIedModelByDomainName(GspMmsMapping *self, const string &domainName)
{
    return self->domainIedMap[domainName];
}

GspLogicalDevice *GspMmsMapping_getLdByDomainName(GspMmsMapping *self, const string &domainName)
{
    return self->ldMap[domainName];
}

void GspMmsMapping_setSgStorageFile(GspMmsMapping *self, const string &filePath)
{
    self->sgStorage = SgStorage::create(filePath);

    // 打开定值存储后，直接插入各domain定值参数数据，如果已存在则忽略
    for(auto &ld : self->ldMap)
    {
        auto domain = GspMmsDevice_getDomain(self->mmsDevice, ld.first.c_str());
        auto sgcb = GspgetSettingGroupByMmsDomain(self, domain);
        if(sgcb)
        {
            const string &ldName = ld.first;
            NLOG_DEBUG("初始化{}相关定值", ldName);
            auto ret = self->sgStorage->insertSgcb(ld.first, sgcb->sgcb->actSG, sgcb->sgcb->editSG, sgcb->sgcb->numOfSGs, sgcb->sgcb->timestamp);
        }
    }

    // 从定值数据表中获取所有domain的存储参数，设置到模型上
    vector<Sgcb> sgcbVec;
    self->sgStorage->getAllSgcbValues(sgcbVec);

    for(auto &sgcb : sgcbVec)
    {
        auto domain = GspMmsDevice_getDomain(self->mmsServer->device, sgcb.ldName.c_str());
        auto sg = GspgetSettingGroupByMmsDomain(self, domain);

        if(sg)
        {
            GspchangeActiveSettingGroup(self, sg, sgcb.actSg, nullptr);

            sg->sgcb->editSG = sgcb.editSg;
            GspMmsValue* editSg = GspMmsValue_getElement(sg->sgcbMmsValues, 2);
            GspMmsValue_setUint8(editSg, 0U);

            sg->sgcb->numOfSGs = sgcb.sgNumber;
            sg->sgcb->editSgs.resize(sgcb.sgNumber);

            GspMmsValue* numOfSg = GspMmsValue_getElement(sg->sgcbMmsValues, 0);
            GspMmsValue_setUint8(numOfSg, sg->sgcb->numOfSGs);
        }
    }
}

int GspSelectEditSg(GspMmsMapping *self, GspClientConnection connection, GspSettingGroup *sg, uint8_t val)
{
    if ((sg->editingClient != nullptr) && ( sg->editingClient != connection))
        /* Edit SG was set by other client */
        return GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;

    if ((val >= 0) && (val <= sg->sgcb->numOfSGs)) {

        sg->sgcb->editSG = val;
        sg->editingClient = connection;

        sg->reservationTimeout = GSP_Hal_getTimeInMs() + (sg->sgcb->resvTms * 1000);

        GspMmsValue* editSg = GspMmsValue_getElement(sg->sgcbMmsValues, 2);
        GspMmsValue* resvTms = GspMmsValue_getElement(sg->sgcbMmsValues, 5);

        GspMmsValue_setUint16(resvTms, sg->sgcb->resvTms);
        GspMmsValue_setUint8(editSg, sg->sgcb->editSG);

        // 更新数据库内的编辑定值区
        self->sgStorage->selectEditSg(sg->mmsDomain->domainName, val);

        // 从存储内取出编辑区定值，设置到对应的se节点上
        SgValueVec valueVec;
        self->sgStorage->getSgValues(sg->mmsDomain->domainName, val, valueVec);
        for(auto &item : valueVec)
        {
            setDataByReference((GspMmsServerConnection)connection, item.reference, "SE", item.value);
        }

        if (sg->editSgChangedHandler != nullptr) {

            if (sg->editSgChangedHandler(sg->editSgChangedHandlerParameter, sg->sgcb,
                                         (uint8_t) val, (GspClientConnection) connection))
            {
                return GSP_DATA_ACCESS_ERROR_SUCCESS;
            }
            else
                return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
        }
        else
            return GSP_DATA_ACCESS_ERROR_SUCCESS;

    }
    return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
}


Data_t *mmsMapping_getModelNodeValue(GspModelNode *node, deque<string> &itemQueue, const string &fc)
{
    Data_t *ret = nullptr;
    switch (node->modelType) {
    case GspLogicalNodeModelType:
    case GspDataObjectModelType:
    {
        auto child = node->firstChild;
        while(child)
        {
            if(!itemQueue.empty())
            {
                auto &itemName = itemQueue.front();

                if(itemName.compare(child->name))
                {
                    child = child->sibling;
                    continue;
                }
                itemQueue.pop_front();
                auto childRet = mmsMapping_getModelNodeValue(child, itemQueue, fc);
                if(childRet)
                {
                    return childRet;
                }
                break;
            }
            else
            {
                auto childRet = mmsMapping_getModelNodeValue(child, itemQueue, fc);
                if(childRet)
                {
                    if(!ret)
                    {
                        ret = (Data_t*)calloc(1, sizeof(Data_t));
                        ret->present =  Data_PR_structure;
                    }
                    asn_sequence_add(&ret->choice, childRet);
                }
            }

            child = child->sibling;
        }
        return ret;
    }
    case GspDataAttributeModelType:
    {
        auto da = (GspDataAttribute *)node;
        while(da)
        {
            char* fcStr = GspFunctionalConstraint_toString(da->fc);
            if(fc.compare(fcStr) == 0 || fc.empty() || fc.compare("XX") == 0 || da->fc == DLT860_FC_NONE)
            {
                if(fcStr){
                    delete [] fcStr;
                }

                if(itemQueue.empty())
                {
                    return GspMmsValue_clone(da->mmsValue);
                }
                else
                {
                    auto child = da->firstChild;
                    while(child)
                    {
                        auto &daRefer = itemQueue.front();
                        auto bda = (GspDataAttribute *)child;
                        auto fcVal = GspFunctionalConstraint_fromString(fc.c_str());
                        if(daRefer.compare(child->name) == 0 && bda->fc == fcVal)
                        {
                            itemQueue.pop_front();
                            auto childRet = mmsMapping_getModelNodeValue(child, itemQueue, fc);
                            return childRet;
                        }
                        child = child->sibling;
                    }
                }
            }
            else
            {
                if(fcStr){
                    delete [] fcStr;
                }
            }
            da = (GspDataAttribute *)da->sibling;
        }

    }
        break;
    default:
        break;
    }

    return ret;
}


Data_t *mmsMapping_getDataByReference(GspMmsMapping *mapping, const string &reference, const string &fc)
{
    string ld;
    string itemId;
    splitDomainAndItemId(reference, ld, itemId);
    deque<string> itemQueue;
    splitStr(itemQueue, itemId, '.');

    string lnName;
    if(itemQueue.size() >= 1)
    {
        lnName = itemQueue.front();
        itemQueue.pop_front();
    }

    auto logiceDevice = mapping->ldMap[ld];
    if(!logiceDevice)
    {
        return nullptr;
    }
    Data_t *ret = nullptr;

    auto ln = logiceDevice->firstChild;
    while(ln)
    {
        if(lnName.empty())
        {
            if(!ret)
            {
                ret = (Data_t *)calloc(1, sizeof(Data_t));
                ret->present = Data_PR_structure;
            }
            auto item = mmsMapping_getModelNodeValue(ln, itemQueue, fc);
            asn_sequence_add(&ret->choice.structure, item);
        }
        else
        {
            if(lnName.compare(ln->name) == 0)
            {
                free(ret);
                return mmsMapping_getModelNodeValue(ln, itemQueue, fc);
            }
        }
        ln = ln->sibling;
    }
    return ret;
}

int GspConfirmEditSgs(GspMmsMapping *self, const string &refer, int editSg, const vector<string> &refers, const vector<string> &values)
{
    string domain;
    string itemId;
    splitDomainAndItemId(refer, domain, itemId);
    SgValueVec vec;
    for(size_t i = 0; i < refers.size(); ++i)
    {
        auto value = GspIedServer_getValueByStr(self->iedServer, refers[i].c_str(), "SG", values[i].c_str());
        if(!value)
        {
            continue;
        }
        vec.push_back({refers[i], value});
        GspIedServer_updateReferValue(self->iedServer, refers[i].c_str(), "SE", value);
    }
    self->sgStorage->setEditSgValues(domain, editSg, vec);
    return 0;
}

int GspSetEditSgs(GspMmsMapping *self, GspClientConnection connection, GspSettingGroup *sg)
{
    if(sg->editSgConfirmedHandler)
    {
        if(!sg->editSgConfirmedHandler(sg->editSgConfirmedHandlerParameter, sg->sgcb, sg->sgcb->editSG))
        {
            return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
        }
    }

    SgValueVec vec;
    auto &sgMap = sg->sgcb->editSgs[sg->sgcb->editSG-1];

    for(auto &item : sgMap) {
        vec.push_back({item.first, item.second});
    }

    sgMap.clear();

    self->sgStorage->setEditSgValues(sg->mmsDomain->domainName, sg->sgcb->editSG, vec);
    return GSP_DATA_ACCESS_ERROR_SUCCESS;
}


void GspMmsMapping_triggerLogging(GspMmsMapping* self, GspMmsValue* value, GspLogInclusionFlag flag)
{
    GspLinkedList element = self->logControls;
    for(auto &&element : *self->logControls)
    {
        GspLogControl* lc = (GspLogControl*) element;

        if ((lc->enabled) && (lc->dataSet != NULL)) {

            uint8_t reasonCode;

            switch (flag) {

            case LOG_CONTROL_VALUE_UPDATE:
                if ((lc->triggerOps & GSP_TRG_OPT_DATA_UPDATE) == 0)
                    continue;

                reasonCode = GSP_TRG_OPT_DATA_UPDATE * 2;

                break;

            case LOG_CONTROL_VALUE_CHANGED:
                if (((lc->triggerOps & GSP_TRG_OPT_DATA_CHANGED) == 0) &&
                        ((lc->triggerOps & GSP_TRG_OPT_DATA_UPDATE) == 0))
                    continue;

                reasonCode = GSP_TRG_OPT_DATA_CHANGED * 2;

                break;

            case LOG_CONTROL_QUALITY_CHANGED:
                if ((lc->triggerOps & GSP_TRG_OPT_QUALITY_CHANGED) == 0)
                    continue;

                reasonCode = GSP_TRG_OPT_QUALITY_CHANGED * 2;

                break;

            default:
                continue;
            }

            char dataRef[130];

            int dsEntryIdx = 0;

            if (GspDataSet_isMemberValueWithRef(lc->dataSet, value, dataRef, lc->domain->modelName, &dsEntryIdx)) {

                if (lc->logInstance != NULL) {

                    if (lc->dataSet) {

                        GspDataSetEntry* dsEntry = lc->dataSet->fcdas;

                        while (dsEntry && (dsEntryIdx > 0)) {
                            dsEntry = dsEntry->sibling;

                            if (dsEntry == NULL)
                                break;

                            dsEntryIdx--;
                        }

                        if (dsEntry) {
                            GspMmsValue* dsValue = dsEntry->value;

                            GspLogInstance_logSingleData(lc->logInstance, dataRef, dsValue, reasonCode);
                        }

                    }

                }
                else {
                    if (DEBUG_IED_SERVER)
                        printf("IED_SERVER: No log instance available!\n");
                }
            }

        }
    }
}
