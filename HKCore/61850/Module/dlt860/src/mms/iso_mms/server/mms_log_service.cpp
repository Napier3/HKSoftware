#include "mms_server_func.h"
#include "asn_inc.h"
#include <string>
#include "mms_server_internal.h"
#include "mms_mapping.h"
#include "reporting.h"
#include <algorithm>
#include "nlogging.h"
#include "logging.h"
#include "logging_api.h"

void *GspServerLog::handleGetLcbValues(GspMmsServerConnection self, void *requestData)
{
    GspMmsMapping *mapping = static_cast<GspMmsMapping *>(self->server->connectionHandlerParameter);
    
    auto request = static_cast<GetLCBValuesRequestPDU_t *>(requestData);
    GetLCBValuesResponsePDU_t *response = createAsnResponse<GetLCBValuesResponsePDU_t>();

    for(int i = 0; i < request->reference.list.count; ++i)
    {
        auto referAsn = request->reference.list.array[i];
        string refer = (const char *)referAsn->buf;
        string ldName;
        string itemId;
        splitDomainAndItemId(refer, ldName, itemId);
        GspMmsDomain* mmsDomain = GspMmsDevice_getDomain(mapping->mmsDevice, ldName.c_str());
        if(!mmsDomain) 
        {
            NLOG_WARN("没有找到 {} 对应的domain", ldName);
            auto member = (GetLCBValuesResponsePDU__lcb__Member *)calloc(1, sizeof(GetLCBValuesResponsePDU__lcb__Member));
            member->present = GetLCBValuesResponsePDU__lcb__Member_PR_error;
            member->choice.error = ServiceError_instance_not_available;
            ASN_SEQUENCE_ADD(&response->lcb.list.array, member);
            continue;
        }

        size_t uPos = itemId.find('.');

        if(uPos == string::npos)
        {
            NLOG_WARN("reference 错误 {}", refer);
            auto member = (GetLCBValuesResponsePDU__lcb__Member *)calloc(1, sizeof(GetLCBValuesResponsePDU__lcb__Member));
            member->present = GetLCBValuesResponsePDU__lcb__Member_PR_error;
            member->choice.error = ServiceError_instance_not_available;
            ASN_SEQUENCE_ADD(&response->lcb.list.array, member);
            continue;
        }

        string lnName = itemId.substr(0, uPos);
        itemId = itemId.substr(uPos + 1);

        auto lc = lookupGspLogControl(mapping, mmsDomain, (char *)lnName.c_str(), (char *)itemId.c_str());
        if(!lc) 
        {
            NLOG_WARN("没有找到 {}/{}.{} 对应的log control", ldName, lnName, itemId);
            auto member = (GetLCBValuesResponsePDU__lcb__Member *)calloc(1, sizeof(GetLCBValuesResponsePDU__lcb__Member));
            member->present = GetLCBValuesResponsePDU__lcb__Member_PR_error;
            member->choice.error = ServiceError_instance_not_available;
            ASN_SEQUENCE_ADD(&response->lcb.list.array, member);
            continue;
        }
        auto member = (GetLCBValuesResponsePDU__lcb__Member *)calloc(1, sizeof(GetLCBValuesResponsePDU__lcb__Member));
        member->present = GetLCBValuesResponsePDU__lcb__Member_PR_value;
        // member->choice.value.bufTm = (INT32U_t *)calloc(1, sizeof(INT32U_t));
        // *(member->choice.value.bufTm) = lc->logControlBlock.;
        OCTET_STRING_fromString(&member->choice.value.datSet, lc->logControlBlock->dataSetName);
        member->choice.value.intgPd = lc->logControlBlock->intPeriod;
        member->choice.value.logEna = lc->logControlBlock->logEna;
        GspBIT_STRING_createBitString(&member->choice.value.trgOps, (const char*)&lc->logControlBlock->trgOps, 1, 2);
        OCTET_STRING_fromString(&member->choice.value.logRef, lc->logControlBlock->logRef);
        ASN_SEQUENCE_ADD(&response->lcb.list.array, member);
    }

    return response;
}

void *GspServerLog::handleSetLcbValues(GspMmsServerConnection self, void *requestData)
{
    GspMmsMapping *mapping = static_cast<GspMmsMapping *>(self->server->connectionHandlerParameter);
    
    auto request = static_cast<SetLCBValuesRequestPDU_t *>(requestData);
    bool hasError = false;
    auto response = createAsnResponse<SetLCBValuesErrorPDU_t>();
    for(int i = 0; i < request->lcb.list.count; ++i)
    {
        auto member = (SetLCBValuesErrorPDU__result__Member*)calloc(1, sizeof(SetLCBValuesErrorPDU__result__Member));

        auto lcb = request->lcb.list.array[i];

        // 异常兼容
        if(!lcb){
            continue;
        }
        if(!lcb->logRef){
            continue;
        }

        string refer = (const char *)lcb->logRef->buf;
        string ldName;
        string itemId;
        splitDomainAndItemId(refer, ldName, itemId);
        GspMmsDomain* mmsDomain = GspMmsDevice_getDomain(mapping->mmsDevice, ldName.c_str());
        if(!mmsDomain) 
        {
            throw invalid_argument(fmt::format("没有找到 {} 对应的domain", ldName));
        }
        if(lcb->logEna)
        {
            string target = refer + "$LogEna";
            auto value = GspMmsValue_newBoolean(*lcb->logEna);
            auto error = Gsp_LOG_SVC_writeAccessLogControlBlock(mapping, mmsDomain, (char *)target.c_str(), value, self);
            auto serviceError = GspMmsDataAccessErrorToServiceError(error);
            if(serviceError != ServiceError_no_error)
            {
                hasError = true;
                member->logEna = (ServiceError_t*)calloc(1, sizeof(ServiceError_t));
                *member->logEna = ServiceError_instance_not_available;
            }
            GspMmsValue_delete(value);
        }
        if(lcb->datSet)
        {
            string target = refer + "$DatSet";
            auto value = GspMmsValue_newMmsString((const char *)lcb->datSet->buf);
            auto error = Gsp_LOG_SVC_writeAccessLogControlBlock(mapping, mmsDomain, (char *)target.c_str(), value, self);
            auto serviceError = GspMmsDataAccessErrorToServiceError(error);
            if(serviceError != ServiceError_no_error)
            {
                hasError = true;
                member->datSet = (ServiceError_t*)calloc(1, sizeof(ServiceError_t));
                *member->datSet = ServiceError_instance_not_available;
            }
            GspMmsValue_delete(value);
        }
        if(lcb->trgOps)
        {
            string target = refer + "$TrgOps";
            
            auto value = GspMmsValue_newBitString(lcb->trgOps->size * 8 - lcb->trgOps->bits_unused);
            GspBIT_STRING_createBitString(&value->choice.bit_string, (const char *)lcb->trgOps->buf, lcb->trgOps->size, lcb->trgOps->bits_unused);

            auto error = Gsp_LOG_SVC_writeAccessLogControlBlock(mapping, mmsDomain, (char *)target.c_str(), value, self);
            auto serviceError = GspMmsDataAccessErrorToServiceError(error);
            if(serviceError != ServiceError_no_error)
            {
                hasError = true;
                member->trgOps = (ServiceError_t*)calloc(1, sizeof(ServiceError_t));
                *member->trgOps = ServiceError_instance_not_available;
            }
            GspMmsValue_delete(value);
        }

        if(lcb->intgPd)
        {
            string target = refer + "$intgPd";
            auto value = GspMmsValue_newUnsignedFromUint32(*lcb->intgPd);
            auto error = Gsp_LOG_SVC_writeAccessLogControlBlock(mapping, mmsDomain, (char *)target.c_str(), value, self);
            auto serviceError = GspMmsDataAccessErrorToServiceError(error);
            if(serviceError != ServiceError_no_error)
            {
                hasError = true;
                member->intgPd = (ServiceError_t*)calloc(1, sizeof(ServiceError_t));
                *member->intgPd = ServiceError_instance_not_available;
            }
            GspMmsValue_delete(value);
        }

        if(lcb->logRef)
        {
            string target = refer + "$logRef";
            auto value = GspMmsValue_newMmsString((const char *)lcb->logRef->buf);
            auto error = Gsp_LOG_SVC_writeAccessLogControlBlock(mapping, mmsDomain, (char *)target.c_str(), value, self);
            auto serviceError = GspMmsDataAccessErrorToServiceError(error);
            if(serviceError != ServiceError_no_error)
            {
                hasError = true;
                member->logRef = (ServiceError_t*)calloc(1, sizeof(ServiceError_t));
                *member->logRef = ServiceError_instance_not_available;
            }
            GspMmsValue_delete(value);            
        }
        ASN_SEQUENCE_ADD(&response->result.list, member);
    }
    if(hasError)
    {
        return response;
    }
    else
    {
        free(response);
        return nullptr;
    }
}

struct QueryParam {
    uint64_t endTime;
    void *resp;
};

void *GspServerLog::handleQueryLogByTime(GspMmsServerConnection self, void *requestData)
{
    GspMmsMapping *mapping = static_cast<GspMmsMapping *>(self->server->connectionHandlerParameter);
    
    auto request = static_cast<QueryLogByTimeRequestPDU_t *>(requestData);
    auto response = createAsnResponse<QueryLogByTimeResponsePDU_t>();

    response->moreFollows= (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));

    *response->moreFollows = 0;

    auto startTime = BinaryTime_getAsUtcMs(request->startTime);
    auto stopTime =BinaryTime_getAsUtcMs(request->stopTime);
    uint64_t entryId = 0;
    if(request->entryAfter)
    {
        memcpy(&entryId, request->entryAfter->buf, sizeof(entryId));
    }
    string refer = (const char*)request->logReference.buf;
    auto logInst = getGspLogInstanceByLogRef(mapping, refer.c_str());
    if(!logInst) {
        throw invalid_argument(fmt::format("没有找到 {} 对应的loginst", refer));
    }

    QueryParam param{stopTime, response};
    GspLogStorage_getEntriesAfter(logInst->logStorage, startTime, entryId, 
    [](void* parameter, uint64_t timestamp, uint64_t entryID, bool moreFollow){
        if(!moreFollow)
            return false;
        auto *param = static_cast<QueryParam *>(parameter);
        auto resp = static_cast<QueryLogAfterResponsePDU_t *>(param->resp);
        uint64_t endTime = param->endTime;

        if(timestamp > endTime)
        {
            NLOG_ERROR("end: {}  time:{}", endTime, timestamp)
            return false;
        }
        if(resp->logEntry.list.count > 20)
        {
            *resp->moreFollows = 1;
            return false;
        }

        auto entry = (LogEntry *)calloc(1, sizeof(LogEntry));
        OCTET_STRING_fromBuf(&entry->entryID, (const char *)&entryID, sizeof(entryID));
        BinaryTime_newTimeFromTimeStamp(&entry->timeOfEntry, timestamp);

        ASN_SEQUENCE_ADD(&resp->logEntry.list, entry);

        return true;
    } , 
    [](void* parameter, const char* dataRef, uint8_t* data, int dataSize, uint8_t reasonCode, bool moreFollow) {
        if(!moreFollow)
            return false;
        auto resp = static_cast<QueryLogAfterResponsePDU_t *>(((QueryParam*)parameter)->resp);
        auto entry = resp->logEntry.list.array[resp->logEntry.list.count - 1];
        auto entryData = (LogEntry__entryData__Member *)calloc(1, sizeof(LogEntry__entryData__Member));
        GspMmsValue* value = &entryData->value;
        asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                                &asn_DEF_Data,
                                                (void **)(&value),
                                                data,
                                                dataSize);
        GspBIT_STRING_createBitString(&entryData->reason, (const char *)&reasonCode, 1, 1);
        string refer;
        string fc;
        splitFcFromReference(dataRef, fc, refer);
        OCTET_STRING_fromString(&entryData->reference, refer.c_str());
        OCTET_STRING_fromString(&entryData->fc, fc.c_str());
        ASN_SEQUENCE_ADD(&entry->entryData.list, entryData);
        return true;
    }
    , &param);
    
    // GspLogStorage_getEntriesAfter(nullptr, request->startTime)
    return response;
}

void *GspServerLog::handleQueryLogAfter(GspMmsServerConnection self, void *requestData)
{
    GspMmsMapping *mapping = static_cast<GspMmsMapping *>(self->server->connectionHandlerParameter);
    
    auto request = static_cast<QueryLogAfterRequestPDU_t *>(requestData);
    auto response = createAsnResponse<QueryLogAfterResponsePDU_t>();
    response->moreFollows = (BOOLEAN_t*)calloc(1, sizeof(BOOLEAN_t));

    auto startTime = BinaryTime_getAsUtcMs(request->startTime);
    uint64_t entryId = 0;
    memcpy(&entryId, request->entry.buf, sizeof(entryId));

    string refer = (const char*)request->logReference.buf;
    auto logInst = getGspLogInstanceByLogRef(mapping, refer.c_str());
    if(!logInst) {
        throw invalid_argument(fmt::format("没有找到 {} 对应的loginst", refer));
    }
    
    GspLogStorage_getEntriesAfter(logInst->logStorage, startTime, entryId, 
    [](void* parameter, uint64_t timestamp, uint64_t entryID, bool moreFollow){
        if(!moreFollow)
            return false;
        auto resp = static_cast<QueryLogAfterResponsePDU_t *>(parameter);
        if(resp->logEntry.list.count > 20)
        {
            *resp->moreFollows = 1;
            return false;
        }

        auto entry = (LogEntry *)calloc(1, sizeof(LogEntry));
        OCTET_STRING_fromBuf(&entry->entryID, (const char *)&entryID, sizeof(entryID));
        BinaryTime_newTimeFromTimeStamp(&entry->timeOfEntry, timestamp);

        ASN_SEQUENCE_ADD(&resp->logEntry.list, entry);

        return true;
    } , 
    [](void* parameter, const char* dataRef, uint8_t* data, int dataSize, uint8_t reasonCode, bool moreFollow) {
        if(!moreFollow)
            return false;
        auto resp = static_cast<QueryLogAfterResponsePDU_t *>(parameter);
        auto entry = resp->logEntry.list.array[resp->logEntry.list.count - 1];
        auto entryData = (LogEntry__entryData__Member *)calloc(1, sizeof(LogEntry__entryData__Member));
        GspMmsValue* value = &entryData->value;
        asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                                &asn_DEF_Data,
                                                (void **)(&value),
                                                data,
                                                dataSize);
        GspBIT_STRING_createBitString(&entryData->reason, (const char *)&reasonCode, 1, 1);
        string refer;
        string fc;
        splitFcFromReference(dataRef, fc, refer);
        OCTET_STRING_fromString(&entryData->reference, refer.c_str());
        OCTET_STRING_fromString(&entryData->fc, fc.c_str());
        ASN_SEQUENCE_ADD(&entry->entryData.list, entryData);
        return true;
    }
    , response);

    return response;

}

void *GspServerLog::handleGetLogStatusValues(GspMmsServerConnection self, void *requestData)
{
    GspMmsMapping *mapping = static_cast<GspMmsMapping *>(self->server->connectionHandlerParameter);
    
    auto request = static_cast<GetLogStatusValuesRequestPDU_t *>(requestData);
    auto response = createAsnResponse<GetLogStatusValues_ResponsePDU_t>();

    response->moreFollows = (BOOLEAN_t*)calloc(1, sizeof(BOOLEAN_t));
    for(size_t i = 0; i < request->logReference.list.count; ++i)
    {
        string refer = (const char *)request->logReference.list.array[i]->buf;
        auto logInst = getGspLogInstanceByLogRef(mapping, refer.c_str());

        auto member = (GetLogStatusValues_ResponsePDU__log__Member*)calloc(1, sizeof(GetLogStatusValues_ResponsePDU__log__Member));
    
        if(!logInst)
        {
            member->present = GetLogStatusValues_ResponsePDU__log__Member_PR_error;
            member->choice.error = ServiceError_instance_not_available;
            ASN_SEQUENCE_ADD(&response->log.list, member);
            continue;
        }

        member->present = GetLogStatusValues_ResponsePDU__log__Member_PR_value;
        OCTET_STRING_fromBuf(&member->choice.value.newEntr, (const char *)&logInst->newEntryId, sizeof(logInst->newEntryId));
        OCTET_STRING_fromBuf(&member->choice.value.oldEntr, (const char *)&logInst->newEntryId, sizeof(logInst->oldEntryId));
        BinaryTime_newTimeFromTimeStamp(&member->choice.value.newEntrTm, logInst->newEntryTime);
        BinaryTime_newTimeFromTimeStamp(&member->choice.value.oldEntrTm, logInst->oldEntryTime);
        ASN_SEQUENCE_ADD(&response->log.list, member);

        if(i > 100)
        {
            *response->moreFollows = 1;
            break;
        }
    }

    return response;
}
