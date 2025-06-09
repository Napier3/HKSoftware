#include "mms_server_internal.h"
#include <stdio.h>
#include "asn_inc.h"
#include "mms_mapping.h"
#include "iso_server_private.h"
#include <vector>
#include <string>
#include <exception>
#include "nlogging.h"
#include "reporting.h"
#include "mms_server_func.h"
#include "logging.h"

using namespace std;

void *GspServerObject::handleGetServerDirectory(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetServerDirectoryRequestPDU_t*>(requestData);
    auto response = createAsnResponse<GetServerDirectoryResponsePDU_t>();

    string lastAfter;
    if(request->referenceAfter)
    {
        lastAfter = reinterpret_cast<const char *>(request->referenceAfter->buf);
    }
    GspMmsDevice *device = self->server->device;
    bool begin = lastAfter.empty();
    for(auto &item : device->domains)
    {
        auto deviceName = item.first.c_str();
        
        if(!begin)
        {
            if(lastAfter == deviceName)
            {
                begin = true;
                continue;
            }
        }
        else
        {
            // 如果ied name在忽略列表中，则不返回
            if(_ignoreIedNames.count(item.second->modelName))
            {
                continue;
            }
            ObjectReference_t *obr = (ObjectReference_t *)GspMemory_calloc(1, sizeof(ObjectReference_t));
            OCTET_STRING_fromString(obr, deviceName);
            ASN_SEQUENCE_ADD(&response->reference, obr);
        }
    }

    // TODO  这里需要分帧逻辑判断
    response->moreFollows = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
    *response->moreFollows = false;
    return response;
}

void *GspServerObject::handleGetLogicalDeviceDirectory(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetLogicalDeviceDirectoryRequestPDU_t*>(requestData);
    auto response = createAsnResponse<GetLogicalDeviceDirectoryResponsePDU_t>();

    string lastAfter;
    if(request->referenceAfter)
    {
        lastAfter = reinterpret_cast<const char *>(request->referenceAfter->buf);
    }

    bool begin = lastAfter.empty();

    if(request->ldName)
    {
        string ldName = (char *)request->ldName->buf;
        GspMmsDomain *domain = GspMmsDevice_getDomain(self->server->device, ldName.c_str());
        for (int i = 0; i < domain->namedVariablesCount; i++) {
            char* lnName = domain->namedVariables[i]->name;
            string refer = lnName;

            if(!begin)
            {
                if(lastAfter == refer)
                {
                    begin = true;
                    continue;
                }
            }
            else
            {
                ObjectReference_t *obj = (ObjectReference_t *)GspMemory_calloc(1, sizeof(ObjectReference_t));
                OCTET_STRING_fromString(obj, refer.c_str());
                ASN_SEQUENCE_ADD(&response->lnReference, obj);
            }
        }
    }
    else
    {
        auto device = self->server->device;
        for(auto &item : device->domains)
        {
            GspMmsDomain *domain = item.second;
            char *ldName = domain->domainName;

            for(int j = 0; j < domain->namedVariablesCount; ++j)
            {
                char *lnName = domain->namedVariables[j]->name;
                string refer = string(ldName) + "/" + lnName;
                if(!begin)
                {
                    if(lastAfter == refer)
                    {
                        begin = true;
                        continue;
                    }
                }
                else
                {
                    ObjectReference_t *obj = (ObjectReference_t *)GspMemory_calloc(1, sizeof(ObjectReference_t));
                    OCTET_STRING_fromString(obj, refer.c_str());
                    ASN_SEQUENCE_ADD(&response->lnReference, obj);
                }
            }
        }
    }

    // TODO  这里需要分帧逻辑判断
    response->moreFollows = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
    *response->moreFollows = false;

    return response;
}

void fillDataObjectResponse(const string &refer, const string &lastAfter, bool &begin, GspModelNode *dataObject, GetLogicalNodeDirectoryResponsePDU_t *respData)
{
    if(dataObject->modelType != GspDataObjectModelType)
    {
        return;
    }
    string currName = refer + "." + dataObject->name;
    
    
    if(begin)
    {
        auto subRefer = createAsnResponse<SubReference_t>();
        OCTET_STRING_fromString(subRefer, currName.c_str());
        ASN_SEQUENCE_ADD(&respData->reference, subRefer);
    } 
    else
    {
        if(lastAfter == currName)
        {
            begin = true;
        }
    }

    auto child = dataObject->firstChild;
    while(child)
    {
        fillDataObjectResponse(refer, lastAfter, begin, child, respData);
        child = child->sibling;
    }
}

void createDataObjectResponse(GspMmsServerConnection self, const string &refer, const string &lastAfter, GetLogicalNodeDirectoryResponsePDU_t *respData)
{
    GspMmsMapping *mapping = static_cast<GspMmsMapping *>(self->server->connectionHandlerParameter);

    string domainName;
    string itemId;
    splitDomainAndItemId(refer, domainName, itemId);
    NLOG_DEBUG("请求domain[{}]数据对象", domainName);

    auto ld = GspMmsMapping_getLdByDomainName(mapping, domainName);
    
    if(!ld)
    {
        throw invalid_argument(fmt::format("没有找到[{}]对应的模型", domainName));
    }
    
    auto ln = ld->firstChild;
    while(ln)
    {
        if(itemId.compare(ln->name) == 0)
        {
            break;
        }
        ln = ln->sibling;
    }

    bool begin = lastAfter.empty();
    if(ln)
    {
        auto dataObject = ln->firstChild;
        while(dataObject)
        {
            fillDataObjectResponse(refer, lastAfter, begin, dataObject, respData);
            dataObject = dataObject->sibling;
        }
    }
}

void createDataSetResponse(GspMmsServerConnection self, const string &refer, const string &lastAfter, GetLogicalNodeDirectoryResponsePDU_t *respData)
{
    string domainName;
    string itemId;
    splitDomainAndItemId(refer, domainName, itemId);
    auto domain = GspMmsDevice_getDomain(self->server->device, domainName.c_str());
    NLOG_DEBUG("请求domain[{}][{}]数据集", domainName, fmt::ptr(domain));

    if(!domain)
    {
        throw invalid_argument(fmt::format("没有找到[{}]对应的模型", domainName));
    }
    GspLinkedList nextElement = domain->namedVariableLists;

    bool begin = lastAfter.empty();
    for(auto &item : *nextElement)
    {
        auto mmsList = (GspMmsNamedVariableList)item;
        if(strncmp(itemId.c_str(), mmsList->name, itemId.size()) != 0)
        {
            continue;
        }
        string entryRefer = mmsList->name;
        if (!itemId.empty())
        {
            entryRefer = entryRefer.substr(itemId.size() + 1);
        }
        toDotReference(entryRefer);

        if(!begin)
        {
            if(entryRefer == lastAfter)
            {
                begin = true;
                continue;
            }
        }
        else
        {
            auto subRefer = createAsnResponse<SubReference_t>();
            OCTET_STRING_fromString(subRefer, entryRefer.c_str());
            ASN_SEQUENCE_ADD(&respData->reference, subRefer);
        }
    }
}

void *GspServerObject::handleGetLogicalNodeDirectory(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetLogicalNodeDirectoryRequestPDU_t*>(requestData);
    auto response = createAsnResponse<GetLogicalNodeDirectoryResponsePDU_t>();
    string refer = reinterpret_cast<const char*>(request->reference.choice.ldName.buf);

    string lastAfter;
    if(request->referenceAfter)
    {
        lastAfter = reinterpret_cast<const char *>(request->referenceAfter->buf);
    }
    switch (request->acsiClass)
    {
    case GSP_ACSIClass_data_set:
        createDataSetResponse(self, refer, lastAfter, response);
        break;
    case GSP_ACSIClass_data_object:
        createDataObjectResponse(self, refer, lastAfter, response);
        break;
    default:
        break;
    }

    // TODO  这里需要分帧逻辑判断
    response->moreFollows = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
    *response->moreFollows = false;

    return response;
}

void fillSGCBResponse(GspMmsServer self,
                      GspMmsDomain *domain,
                      GetAllCBValuesResponsePDU_t &respData,
                      const string &referAfter)
{
    GspMmsMapping *mapping = static_cast<GspMmsMapping *>(self->connectionHandlerParameter);
    GspLinkedList nextElement = mapping->settingGroups;
    for(auto &item : *nextElement)
    {
        GspSettingGroup *sg = (GspSettingGroup *)item;
        SGCB_t sgcb;
        memset(&sgcb, 0, sizeof(sgcb));
        if(domain == sg->mmsDomain)
        {
            auto resp = (GetAllCBValuesResponsePDU__cbValue__Member*)calloc(1, sizeof(GetAllCBValuesResponsePDU__cbValue__Member));
            string refer = "SGCB";
            OCTET_STRING_fromBuf(&resp->reference, refer.c_str(), refer.size());
            resp->value.present = GetAllCBValuesResponsePDU__cbValue__Member__value_PR_sgcb;

            auto values = sg->sgcbMmsValues;
            auto value = GspMmsValue_getElement(values, 0);
            sgcb.numOfSG = GspMmsValue_toInt32(value);
            value = GspMmsValue_getElement(values, 1);
            sgcb.actSG = GspMmsValue_toInt32(value);
            value = GspMmsValue_getElement(values, 2);
            sgcb.editSG = GspMmsValue_toInt32(value);
            value = GspMmsValue_getElement(values, 4);
            GspFillMmsValueToUtcTime(sgcb.lActTm, value);
            // optional
            //MmsValue* resvTms = MmsValue_getElement(values, 5);
            //sgcb.resvTms = MmsValue_toInt32(resvTms);
            resp->value.choice.sgcb = sgcb;

            ASN_SEQUENCE_ADD(&respData.cbValue, resp);
        }
    }
}

void fillLCBResponse(GspMmsServer self,
                      GspMmsDomain *domain,
                      const string &lnName,
                      GetAllCBValuesResponsePDU_t &respData,
                      const string &referAfter)
{
    bool begin = referAfter.empty();
    GspMmsMapping *mapping = static_cast<GspMmsMapping *>(self->connectionHandlerParameter);
    for(auto &&element : *mapping->logControls)
    {
        auto *lc = (GspLogControl*)element;
        if (lc->domain == domain) {
            if (strcmp(lc->logicalNode->name, lnName.c_str()) == 0 && begin) {
                auto resp = (GetAllCBValuesResponsePDU__cbValue__Member*)calloc(1, sizeof(GetAllCBValuesResponsePDU__cbValue__Member));
                string referData = lc->name;
                referData = referData.substr(lnName.size() + 1);
                OCTET_STRING_fromString(&resp->reference, referData.c_str());
                resp->value.present = GetAllCBValuesResponsePDU__cbValue__Member__value_PR_lcb;
                LCB_t &lcb = resp->value.choice.lcb;
                memset(&lcb, 0, sizeof(lcb));
                OCTET_STRING_fromString(&lcb.datSet, lc->logControlBlock->dataSetName);
                lcb.intgPd = lc->logControlBlock->intPeriod;
                lcb.logEna = lc->logControlBlock->logEna;
                GspBIT_STRING_createBitString(&lcb.trgOps, (const char*)&lc->logControlBlock->trgOps, 1, 2);
                OCTET_STRING_fromString(&lcb.logRef, lc->logControlBlock->logRef);
                ASN_SEQUENCE_ADD(&respData.cbValue, resp);
            }
        }
        if(referAfter == lc->name)
        {
            begin = true;
        }
    }
}

void fillURCBResponse(GspMmsServer self,
                      GspMmsDomain *domain,
                      const string &lnName,
                      GetAllCBValuesResponsePDU_t &respData,
                      const string &referAfter)
{
    bool begin = referAfter.empty();
    GspMmsMapping *mapping = static_cast<GspMmsMapping *>(self->connectionHandlerParameter);
    GspLinkedList nextElement = mapping->reportControls;
    for(auto &item : *nextElement)
    {
        GspReportControl* rc = (GspReportControl*) item;
        if(rc->domain == domain)
        {
            if(strncmp(rc->name, lnName.c_str(), lnName.size()) == 0 && begin)
            {
                auto resp = (GetAllCBValuesResponsePDU__cbValue__Member*)calloc(1, sizeof(GetAllCBValuesResponsePDU__cbValue__Member));
                string referData = rc->name;
                referData = referData.substr(lnName.size() + 1);
                OCTET_STRING_fromString(&resp->reference, referData.c_str());
                resp->value.present = GetAllCBValuesResponsePDU__cbValue__Member__value_PR_urcb;
                URCB_t urcb;
                memset(&urcb, 0, sizeof(urcb));
                auto value = GspReportControl_getRCBValue(rc, (char *)"RptID");
                auto rptId = GspMmsValue_toString(value);
                OCTET_STRING_fromBuf(&urcb.rptID, rptId, strlen(rptId));
                value = GspReportControl_getRCBValue(rc, (char *)"RptEna");
                urcb.rptEna = GspMmsValue_getBoolean(value) ? 1 : 0;
                value = GspReportControl_getRCBValue(rc, (char *)"DatSet");
                auto dataSet = GspMmsValue_toString(value);
                OCTET_STRING_fromBuf(&urcb.datSet, dataSet, strlen(dataSet));
                value = GspReportControl_getRCBValue(rc, (char *)"ConfRev");
                urcb.confRev = GspMmsValue_toUint32(value);
                value = GspReportControl_getRCBValue(rc, (char *)"OptFlds");
                //urcb.optFlds = rc->triggerOps;
                GspFillMmsValueToBitString(urcb.optFlds, value);
                value = GspReportControl_getRCBValue(rc, (char *)"BufTm");
                urcb.bufTm = GspMmsValue_toUint32(value);
                value = GspReportControl_getRCBValue(rc, (char *)"SqNum");
                urcb.sqNum = GspMmsValue_toUint32(value);
                value = GspReportControl_getRCBValue(rc, (char *)"TrgOps");
                GspFillMmsValueToBitString(urcb.trgOps, value);
                value = GspReportControl_getRCBValue(rc, (char *)"IntgPd");
                urcb.intgPd = GspMmsValue_toUint32(value);
                value = GspReportControl_getRCBValue(rc, (char *)"GI");
                urcb.gi = GspMmsValue_getBoolean(value) ? 1 : 0;
                value = GspReportControl_getRCBValue(rc, (char *)"Resv");
                urcb.resv = GspMmsValue_getBoolean(value) ? 1 : 0;
                //optional
                urcb.owner = nullptr;

                resp->value.choice.urcb = urcb;

                ASN_SEQUENCE_ADD(&respData.cbValue, resp);
            }
            if(referAfter.compare(rc->name) == 0)
            {
                begin = true;
            }
        }
    }
}

void fillBRCBResponse(GspMmsServer self,
                      GspMmsDomain *domain,
                      const string &lnName,
                      GetAllCBValuesResponsePDU_t &respData,
                      const string &referAfter)
{
    bool begin = referAfter.empty();

    GspMmsMapping *mapping = static_cast<GspMmsMapping *>(self->connectionHandlerParameter);
    GspLinkedList nextElement = mapping->reportControls;
    for(auto &item : *nextElement)
    {
        GspReportControl* rc = (GspReportControl*) item;
        if(rc->domain == domain)
        {
            if(strncmp(rc->name, lnName.c_str(), lnName.size()) == 0 && begin)
            {
                auto resp = (GetAllCBValuesResponsePDU__cbValue__Member*)calloc(1, sizeof(GetAllCBValuesResponsePDU__cbValue__Member));
                string referData = rc->name;
                referData = referData.substr(lnName.size() + 1);
                OCTET_STRING_fromString(&resp->reference, referData.c_str());
                resp->value.present = GetAllCBValuesResponsePDU__cbValue__Member__value_PR_brcb;
                BRCB_t brcb;
                memset(&brcb, 0, sizeof(brcb));
                auto value = GspReportControl_getRCBValue(rc, (char *)"RptID");
                auto rptId = GspMmsValue_toString(value);
                OCTET_STRING_fromBuf(&brcb.rptID, rptId, strlen(rptId));
                value = GspReportControl_getRCBValue(rc, (char *)"RptEna");
                brcb.rptEna = GspMmsValue_getBoolean(value) ? 1 : 0;
                value = GspReportControl_getRCBValue(rc, (char *)"DatSet");
                auto dataSet = GspMmsValue_toString(value);
                OCTET_STRING_fromBuf(&brcb.datSet, dataSet, strlen(dataSet));
                value = GspReportControl_getRCBValue(rc, (char *)"ConfRev");
                brcb.confRev = GspMmsValue_toUint32(value);
                value = GspReportControl_getRCBValue(rc, (char *)"OptFlds");
                //brcb.optFlds = rc->triggerOps;
                GspFillMmsValueToBitString(brcb.optFlds, value);
                value = GspReportControl_getRCBValue(rc, (char *)"BufTm");
                brcb.bufTm = GspMmsValue_toUint32(value);
                value = GspReportControl_getRCBValue(rc, (char *)"SqNum");
                brcb.sqNum = GspMmsValue_toUint32(value);
                value = GspReportControl_getRCBValue(rc, (char *)"TrgOps");
                GspFillMmsValueToBitString(brcb.trgOps, value);
                value = GspReportControl_getRCBValue(rc, (char *)"IntgPd");
                brcb.intgPd = GspMmsValue_toUint32(value);
                value = GspReportControl_getRCBValue(rc, (char *)"GI");
                brcb.gi = GspMmsValue_getBoolean(value) ? 1 : 0;
                value = GspReportControl_getRCBValue(rc, (char *)"PurgeBuf");
                brcb.purgeBuf = GspMmsValue_getBoolean(value) ? 1 : 0;
                value = GspReportControl_getRCBValue(rc, (char *)"EntryID");
                GspFillMmsValueToOctetString(brcb.entryID, value);
                value = GspReportControl_getRCBValue(rc, (char *)"TimeofEntry");
                GspFillMmsValueToBinaryTime(brcb.timeOfEntry, value);
                //optional
                brcb.resvTms = nullptr;
                brcb.owner = nullptr;

                resp->value.choice.brcb = brcb;

                ASN_SEQUENCE_ADD(&respData.cbValue, resp);
            }
            if(referAfter.compare(rc->name) == 0)
            {
                begin = true;
            }
        }

    }
}

void fillCbResponseByLn(sGspMmsServer *self,
                        ACSIClass_t acsi,
                        GspMmsDomain *domain,
                        const string &itemId,
                        GetAllCBValuesResponsePDU_t &respData,
                        const string &referAfter)
{
    string lnName = itemId;

    switch (acsi) {
    case GSP_ACSIClass_brcb:
        lnName = lnName + "$BR";
        fillBRCBResponse(self, domain, lnName, respData, referAfter);
        break;
    case GSP_ACSIClass_urcb:
        lnName = lnName + "$RP";
        fillURCBResponse(self, domain, lnName, respData, referAfter);
        break;
    case GSP_ACSIClass_lcb:
        fillLCBResponse(self, domain, lnName, respData, referAfter);
        break;
    case GSP_ACSIClass_sgcb:
        fillSGCBResponse(self, domain, respData, referAfter);
        break;
    case GSP_ACSIClass_gocb:
        break;
    case GSP_ACSIClass_msvcb:
        break;
    default:
        NLOG_WARN("接收到错误的acsi类型，{}\n", int(acsi));
        throw exception();
        break;
    }

}

void *createCbResponse(GspMmsServer self, ACSIClass_t acsi, const string &refer, const string &referAfter)
{

    string domainName;
    string itemId;

    splitDomainAndItemId(refer, domainName, itemId);

    GspMmsDomain *domain = GspMmsDevice_getDomain(self->device, domainName.c_str());

    if(!domain)
    {
        throw invalid_argument(fmt::format("没有找到[{}]对应的模型", domainName));
    }

    GetAllCBValuesResponsePDU_t *respData = createAsnResponse<GetAllCBValuesResponsePDU_t>();

    uint32_t* moreFollows = (BOOLEAN_t*)calloc(1, sizeof(BOOLEAN_t));
    respData->moreFollows = moreFollows;
    if(!itemId.empty())
    {
        fillCbResponseByLn(self, acsi, domain, itemId, *respData, referAfter);
    }
    else
    {
        for(int i = 0; i < domain->namedVariablesCount; ++i)
        {
            fillCbResponseByLn(self, acsi, domain, domain->namedVariables[i]->name, *respData, referAfter);
        }
    }
    return respData;
}

void *GspServerObject::handleGetAllDataValues(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetAllDataValuesRequestPDU_t*>(requestData);
    string reference = (const char *)request->reference.choice.ldName.buf;
    string lastRefer;
    if(request->referenceAfter)
    {
        lastRefer = (const char *)request->referenceAfter->buf; 
    }
    string fc;
    if(request->fc)
    {
        fc = (const char *)request->fc->buf;
    }
    printf("get all data values, reference is %s, fc %s, after %s\n", reference.c_str(), fc.c_str(), lastRefer.c_str());

    vector<pair<string, Data_t *> > dataVec;
    mmsServer_getAllDataValues(self, reference, fc, lastRefer, dataVec);
    auto response = createAsnResponse<GetAllDataValuesResponsePDU_t>();
    response->moreFollows = (BOOLEAN_t *)calloc(1, sizeof(BOOLEAN_t));
    *response->moreFollows = 0;
    for(auto &data : dataVec)
    {
        auto item = (GetAllDataValuesResponsePDU__data__Member*)CALLOC(1, sizeof(GetAllDataValuesResponsePDU__data__Member));
        OCTET_STRING_fromString(&item->reference, data.first.c_str());
        GspMmsValue_update(&item->value, data.second);
        ASN_SEQUENCE_ADD(&response->data, item);
    }
    return response;
}

void fillSubDataDefine(GspModelNode* modelNode, const string& fc, DataDefinition_t *dataDefine)
{
    if (modelNode->firstChild)
    {
        dataDefine->present = DataDefinition_PR_structure;
        auto child = modelNode->firstChild;
        while (child)
        {
            if (child->modelType == GspDataAttributeModelType)
            {
                auto da = (GspDataAttribute*)child;
                char* fcString = GspFunctionalConstraint_toString(da->fc);
                if (fc == "XX" || fc.empty() || fc == fcString)
                {
                    auto member = (DataDefinition__structure__Member*)calloc(1, sizeof(DataDefinition__structure__Member));
                    member->type = (DataDefinition_t*)calloc(1, sizeof(DataDefinition_t));
                    OCTET_STRING_fromString(&member->name, child->name);
                    fillSubDataDefine(child, fc, member->type);
                    member->fc = (OCTET_STRING_t*)calloc(1, sizeof(OCTET_STRING_t));
                    OCTET_STRING_fromString(member->fc, fcString);
                    ASN_SEQUENCE_ADD(&dataDefine->choice.structure, member);
                }

                if(fcString){
                    delete [] fcString;
                }

            } else {
                auto member = (DataDefinition__structure__Member*)calloc(1, sizeof(DataDefinition__structure__Member));
                member->type = (DataDefinition_t*)calloc(1, sizeof(DataDefinition_t));
                OCTET_STRING_fromString(&member->name, child->name);
                fillSubDataDefine(child, fc, member->type);
                if(member->type->choice.structure.list.count > 0)
                {
                    ASN_SEQUENCE_ADD(&dataDefine->choice.structure, member);
                }
                else
                {
                    free(member);
                }
            }
            child = child->sibling;
        }
    }
    else
    {
        assert(modelNode->modelType == GspDataAttribute);
        
        auto da = (GspDataAttribute*)modelNode;

        switch (da->type) {
        case DLT860_BOOLEAN:
            dataDefine->present = DataDefinition_PR_boolean;
            break;
        case DLT860_INT8:
            dataDefine->present = DataDefinition_PR_int8;
            break;
        case DLT860_INT16:
            dataDefine->present = DataDefinition_PR_int16;
            break;
        case DLT860_INT32:
            dataDefine->present = DataDefinition_PR_int32;
            break;
        case DLT860_INT64:
            dataDefine->present = DataDefinition_PR_int64;
            break;
        case DLT860_INT8U:
            dataDefine->present = DataDefinition_PR_int8u;
            break;
        case DLT860_INT16U:
            dataDefine->present = DataDefinition_PR_int16u;
            break;
        case DLT860_INT32U:
            dataDefine->present = DataDefinition_PR_int32u;
            break;
        case DLT860_FLOAT32:
            dataDefine->present = DataDefinition_PR_float32;
            break;
        case DLT860_FLOAT64:
            dataDefine->present = DataDefinition_PR_float64;
            break;
        case DLT860_ENUMERATED:
            dataDefine->present = DataDefinition_PR_int8;
            break;
        case DLT860_CHECK:
            dataDefine->present = DataDefinition_PR_check;
            break;
        case DLT860_CODEDENUM:
            dataDefine->present = DataDefinition_PR_tcmd;
            break;
        case DLT860_OCTET_STRING_6:
            dataDefine->present = DataDefinition_PR_octet_string;
            dataDefine->choice.octet_string = -6;
            break;
        case DLT860_OCTET_STRING_8:
            dataDefine->present = DataDefinition_PR_octet_string;
            dataDefine->choice.octet_string = -8;
            break;
        case DLT860_OCTET_STRING_64:
            dataDefine->present = DataDefinition_PR_octet_string;
            dataDefine->choice.octet_string = -64;
            break;
        case DLT860_VISIBLE_STRING_32:
            dataDefine->present = DataDefinition_PR_visible_string;
            dataDefine->choice.visible_string = -32;
            break;
        case DLT860_VISIBLE_STRING_64:
            dataDefine->present = DataDefinition_PR_visible_string;
            dataDefine->choice.visible_string = -64;
            break;
        case DLT860_VISIBLE_STRING_65:
            dataDefine->present = DataDefinition_PR_visible_string;
            dataDefine->choice.visible_string = -65;
            break;
        case DLT860_VISIBLE_STRING_129:
            dataDefine->present = DataDefinition_PR_visible_string;
            dataDefine->choice.visible_string = -129;
            break;
        case DLT860_VISIBLE_STRING_255:
            dataDefine->present = DataDefinition_PR_visible_string;
            dataDefine->choice.visible_string = -255;
            break;
        case DLT860_UNICODE_STRING_255:
            dataDefine->present = DataDefinition_PR_unicode_string;
            dataDefine->choice.visible_string = -255;
            break;
        case DLT860_GENERIC_BITSTRING:
            dataDefine->present = DataDefinition_PR_bit_string;
            dataDefine->choice.bit_string = da->mmsValue->choice.bit_string.size * 8 - da->mmsValue->choice.bit_string.bits_unused;
            break;
        case DLT860_TIMESTAMP:
            dataDefine->present = DataDefinition_PR_utc_time;
            break;
        case DLT860_QUALITY:
            dataDefine->present = DataDefinition_PR_quality;
            break;
        case DLT860_ENTRY_TIME:
            dataDefine->present = DataDefinition_PR_binary_time;
            break;
            break;
        case DLT860_OPTFLDS:
            dataDefine->present = DataDefinition_PR_bit_string;
            dataDefine->choice.bit_string = 10;
            break;
        case DLT860_TRGOPS:
            dataDefine->present = DataDefinition_PR_bit_string;
            dataDefine->choice.bit_string = 6;
            break;
        case DLT860_DBPOS:
            dataDefine->present = DataDefinition_PR_dbpos;
            dataDefine->choice.bit_string = 2;
            break;
        case DLT860_TCMD:
            dataDefine->present = DataDefinition_PR_tcmd;
            dataDefine->choice.bit_string = 2;
            break;
        default:
            NLOG_ERROR("MMS-MAPPING: type cannot be mapped %i\n", da->type);
            break;
        }
    }
}

void fillDataDefine(GspModelNode* modelNode, GetAllDataDefinitionResponsePDU_t* resp, const string& parentRef, const string& fc, const string& referAfter)
{
    bool start = referAfter.empty();
    int count = 0;
    auto child = modelNode->firstChild;
    while (child)
    {
        if (count >= 10)
        {
            throw 10;
        }
        string childRef = child->name;
        if (!start)
        {
            if (childRef == referAfter)
            {
                start = true;
            }
        }
        else
        {
            auto member = (GetAllDataDefinitionResponsePDU__data__Member*)calloc(1, sizeof(GetAllDataDefinitionResponsePDU__data__Member));

            if (child->modelType == GspDataObjectModelType)
            {
                member->cdcType = (OCTET_STRING_t*)calloc(1, sizeof(OCTET_STRING_t));
                auto dataObject = (GspDataObject*)child;
                OCTET_STRING_fromString(member->cdcType, dataObject->cdcType);
            }
            OCTET_STRING_fromString(&member->reference, childRef.c_str());
            fillSubDataDefine(child, fc, &member->definition);

            if(member->definition.choice.structure.list.count > 0)
            {
                ASN_SEQUENCE_ADD(&resp->data, member);
                count += 1;
            }
            else 
            {
                free(member);
            }

        }
        child = child->sibling;
    }
}

void* GspServerObject::handleGetAllDataDefinition(GspMmsServerConnection self, void* requestData)
{
    auto sourceData = static_cast<GetAllDataDefinitionRequestPDU_t*>(requestData);
    string fc = sourceData->fc ? (const char*)sourceData->fc->buf : "";
    string refer = (const char*)sourceData->reference.choice.ldName.buf;
    //string refer = "PE1001MEAS/LLN0";
    string referAfter = sourceData->referenceAfter ? (const char*)sourceData->referenceAfter->buf : "";
    NLOG_DEBUG("get all define {} {} {}", refer, fc, referAfter);

    auto resp = createAsnResponse<GetAllDataDefinitionResponsePDU_t>();
    string ldName, itemId;
    splitDomainAndItemId(refer, ldName, itemId);
    
    auto mapping = (GspMmsMapping *)self->server->connectionHandlerParameter;

    auto model = GspMmsMapping_getIedModelByDomainName(mapping, ldName);
    if (!model)
    {
        ASN_STRUCT_FREE(asn_DEF_GetAllDataDefinitionResponsePDU, resp);
        throw invalid_argument(fmt::format("没有找到[{}]对应的模型", ldName));
    }

    auto modelNode = GspIedModel_getModelNodeByReference(model, refer.c_str(), "");
    if (!modelNode)
    {
        ASN_STRUCT_FREE(asn_DEF_GetAllDataDefinitionResponsePDU, resp);
        throw invalid_argument(fmt::format("没有找到[{}]对应的节点", ldName));
    }
    try
    {
        fillDataDefine(modelNode, resp, "", fc, referAfter);
        resp->moreFollows = (BOOLEAN_t*)calloc(1, sizeof(BOOLEAN_t));
    }
    catch (int count)
    {
        
    }
    return resp;
}

void *GspServerObject::handleGetAllCbValues(GspMmsServerConnection self, void *requestData)
{
    auto sourceData = static_cast<GetAllCBValuesRequestPDU_t*>(requestData);
    auto acsi = sourceData->acsiClass;
    string reference((char *)sourceData->reference.choice.ldName.buf,
                     sourceData->reference.choice.ldName.size);

    string referAfter;
    if(sourceData->referenceAfter)
    {
        referAfter.append((char *)sourceData->referenceAfter->buf,
                           sourceData->referenceAfter->size);
    }
    return createCbResponse(self->server, acsi, reference, referAfter);
}

set<string> GspServerObject::_ignoreIedNames;