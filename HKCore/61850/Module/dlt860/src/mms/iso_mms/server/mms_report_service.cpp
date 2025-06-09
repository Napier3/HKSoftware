#include "mms_server_func.h"
#include "asn_inc.h"
#include <string>
#include "mms_server_internal.h"
#include "mms_mapping.h"
#include "reporting.h"
#include <algorithm>
#include "nlogging.h"

using std::string;

bool fillUrcbResponse(GspMmsServer self,
                      GspMmsDomain *domain,
                      const string &referName,
                      URCB_t *urcb)
{
    GspMmsMapping *mapping = static_cast<GspMmsMapping *>(self->connectionHandlerParameter);
    GspLinkedList nextElement = mapping->reportControls;
    for(auto &item : *nextElement)
    {
        GspReportControl* rc = (GspReportControl*) item;
        if(rc->domain == domain && rc->name == referName)
        {
            auto value = GspReportControl_getRCBValue(rc, (char *)"RptID");
            auto rptId = GspMmsValue_toString(value);
            OCTET_STRING_fromBuf(&urcb->rptID, rptId, strlen(rptId));
            value = GspReportControl_getRCBValue(rc, (char *)"RptEna");
            urcb->rptEna = GspMmsValue_getBoolean(value) ? 1 : 0;
            value = GspReportControl_getRCBValue(rc, (char *)"DatSet");
            string dataSet = GspMmsValue_toString(value);
            toDotReference(dataSet);
            OCTET_STRING_fromBuf(&urcb->datSet, dataSet.c_str(), dataSet.size());
            value = GspReportControl_getRCBValue(rc, (char *)"ConfRev");
            urcb->confRev = GspMmsValue_toUint32(value);
            value = GspReportControl_getRCBValue(rc, (char *)"OptFlds");
            //urcb.optFlds = rc->triggerOps;
            GspFillMmsValueToBitString(urcb->optFlds, value);
            value = GspReportControl_getRCBValue(rc, (char *)"BufTm");
            urcb->bufTm = GspMmsValue_toUint32(value);
            value = GspReportControl_getRCBValue(rc, (char *)"SqNum");
            urcb->sqNum = GspMmsValue_toUint32(value);
            value = GspReportControl_getRCBValue(rc, (char *)"TrgOps");
            GspFillMmsValueToBitString(urcb->trgOps, value);
            value = GspReportControl_getRCBValue(rc, (char *)"IntgPd");
            urcb->intgPd = GspMmsValue_toUint32(value);
            value = GspReportControl_getRCBValue(rc, (char *)"GI");
            urcb->gi = GspMmsValue_getBoolean(value) ? 1 : 0;
            value = GspReportControl_getRCBValue(rc, (char *)"Resv");
            urcb->resv = GspMmsValue_getBoolean(value) ? 1 : 0;
            //optional
            urcb->owner = nullptr;
            return true;

        }
    }
    return false;
}

bool fillBrcbResponse(GspMmsServer self,
                      GspMmsDomain *domain,
                      const string &referName,
                      BRCB_t *brcb)
{

    GspMmsMapping *mapping = static_cast<GspMmsMapping *>(self->connectionHandlerParameter);
    GspLinkedList nextElement = mapping->reportControls;
    for(auto &item : *nextElement)
    {
        GspReportControl* rc = (GspReportControl*) item;
        if(rc->domain == domain && referName == rc->name)
        {
            auto value = GspReportControl_getRCBValue(rc, (char *)"RptID");
            auto rptId = GspMmsValue_toString(value);
            OCTET_STRING_fromBuf(&brcb->rptID, rptId, strlen(rptId));
            value = GspReportControl_getRCBValue(rc, (char *)"RptEna");
            brcb->rptEna = GspMmsValue_getBoolean(value) ? 1 : 0;
            value = GspReportControl_getRCBValue(rc, (char *)"DatSet");
            string dataSet = GspMmsValue_toString(value);
            toDotReference(dataSet);
            OCTET_STRING_fromBuf(&brcb->datSet, dataSet.c_str(), dataSet.size());
            value = GspReportControl_getRCBValue(rc, (char *)"ConfRev");
            brcb->confRev = GspMmsValue_toUint32(value);
            value = GspReportControl_getRCBValue(rc, (char *)"OptFlds");
            GspFillMmsValueToBitString(brcb->optFlds, value);
            value = GspReportControl_getRCBValue(rc, (char *)"BufTm");
            brcb->bufTm = GspMmsValue_toUint32(value);
            value = GspReportControl_getRCBValue(rc, (char *)"SqNum");
            brcb->sqNum = GspMmsValue_toUint32(value);
            value = GspReportControl_getRCBValue(rc, (char *)"TrgOps");
            GspFillMmsValueToBitString(brcb->trgOps, value);
            value = GspReportControl_getRCBValue(rc, (char *)"IntgPd");
            brcb->intgPd = GspMmsValue_toUint32(value);
            value = GspReportControl_getRCBValue(rc, (char *)"GI");
            brcb->gi = GspMmsValue_getBoolean(value) ? 1 : 0;
            value = GspReportControl_getRCBValue(rc, (char *)"PurgeBuf");
            brcb->purgeBuf = GspMmsValue_getBoolean(value) ? 1 : 0;
            value = GspReportControl_getRCBValue(rc, (char *)"EntryID");
            GspFillMmsValueToOctetString(brcb->entryID, value);
            value = GspReportControl_getRCBValue(rc, (char *)"TimeofEntry");
            GspFillMmsValueToBinaryTime(brcb->timeOfEntry, value);
            //optional
            brcb->resvTms = nullptr;
            brcb->owner = nullptr;
            return true;
        }
    }
    return false;
}

void *GspServerReport::handleGetBrcbValues(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetBRCBValuesRequestPDU_t*>(requestData);
    auto response = createAsnResponse<GetBRCBValuesResponsePDU_t>();
    response->moreFollows = (BOOLEAN_t *)calloc(1, sizeof(BOOLEAN_t));
    *response->moreFollows = 0;

    for(int i = 0; i < request->reference.list.count; ++i)
    {
        auto ref = request->reference.list.array[i];
        if(i >= 50)
        {
            *response->moreFollows = 1;
            break;
        }

        GetBRCBValuesResponsePDU__brcb__Member *member = (GetBRCBValuesResponsePDU__brcb__Member*)calloc(1, sizeof(GetBRCBValuesResponsePDU__brcb__Member));
        string reference = (const char *)ref->buf;
        string domainName;
        string itemId;
        splitDomainAndItemId(reference.c_str(), domainName, itemId);

        // convert to rc name
        itemId.insert(itemId.find("."), "$BR");
        std::replace(itemId.begin(), itemId.end(),'.', '$');
        GspMmsDomain *domain = GspMmsDevice_getDomain(self->server->device, domainName.c_str());

        member->present = GetBRCBValuesResponsePDU__brcb__Member_PR_value;
        auto ret = fillBrcbResponse(self->server, domain, itemId, &member->choice.value);

        if(!ret)
        {
            member->present = GetBRCBValuesResponsePDU__brcb__Member_PR_error;
            member->choice.error = ServiceError_failed_due_to_server_constraint;
        }

        asn_sequence_add(&response->brcb, member);
    }
    return response;
}

SetBRCBValuesErrorPDU__result__Member* setBrcbResponse(GspMmsServerConnection self,
                     GspMmsDomain *domain,
                     const string &referName,
                     SetBRCBValuesRequestPDU__brcb__Member &brcb)
{
    bool isOk = false;
    auto respItem = (SetBRCBValuesErrorPDU__result__Member*)calloc(1, sizeof(SetBRCBValuesErrorPDU__result__Member));
    GspMmsMapping *mapping = static_cast<GspMmsMapping *>(self->server->connectionHandlerParameter);
    GspLinkedList nextElement = mapping->reportControls;
    bool findRc = false;
    for(auto &item : *nextElement)
    {
        GspReportControl* rc = (GspReportControl*) item;
        if(rc->domain == domain && referName == rc->name)
        {
            findRc = true;
            isOk = true;
            GspMmsValue *value = nullptr;
            if(brcb.rptEna && !*brcb.rptEna)
            {
                value = GspMmsValue_newBoolean(*brcb.rptEna);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"RptEna", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->rptEna = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->rptEna = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.bufTm)
            {
                value = GspMmsValue_newUnsignedFromUint32(*brcb.bufTm);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"bufTm", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->bufTm = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->bufTm = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.datSet)
            {
                value = GspMmsValue_newMmsString((char *)brcb.datSet->buf);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"datSet", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->datSet = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->datSet = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.entryID)
            {
                value = GspMmsValue_newOctetString(8,8);
                GspMmsValue_setOctetString(value, brcb.entryID->buf, brcb.entryID->size);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"entryID", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->entryID = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->entryID = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.intgPd)
            {
                value = GspMmsValue_newUnsignedFromUint32(*brcb.intgPd);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"intgPd", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->intgPd = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->intgPd = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.optFlds)
            {
                value = GspMmsValue_newBitString(brcb.optFlds->size * 8 - brcb.optFlds->bits_unused);
                GspBIT_STRING_createBitString(&value->choice.bit_string, (const char *)brcb.optFlds->buf, brcb.optFlds->size, brcb.optFlds->bits_unused);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"optFlds", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->optFlds = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->optFlds = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.purgeBuf)
            {
                value = GspMmsValue_newBoolean(*brcb.purgeBuf);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"purgeBuf", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->purgeBuf = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->purgeBuf = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.resvTms)
            {
                value = GspMmsValue_newIntegerFromInt16(*brcb.resvTms);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"resvTms", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->resvTms = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->resvTms = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.rptID)
            {
                value = GspMmsValue_newVisibleString((const char *)brcb.rptID->buf);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"rptID", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->rptID = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->rptID = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.trgOps)
            {
                value = GspMmsValue_newBitString(brcb.trgOps->size * 8 - brcb.trgOps->bits_unused);
                GspBIT_STRING_createBitString(&value->choice.bit_string, (const char *)brcb.trgOps->buf, brcb.trgOps->size, brcb.trgOps->bits_unused);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"trgOps", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->trgOps = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->trgOps = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.rptEna && *brcb.rptEna)
            {
                value = GspMmsValue_newBoolean(*brcb.rptEna);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"RptEna", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->rptEna = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->rptEna = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.gi)
            {
                value = GspMmsValue_newBoolean(*brcb.gi);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"gi", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->gi = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->gi = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            break;
        }
    }

    if(!findRc)
    {
        NLOG_WARN("没有找到[{}/{}]对应的报告控制块", domain->domainName, referName);
    }
    if(isOk)
    {
        free(respItem);
        return nullptr;
    }
    return respItem;
}

void *GspServerReport::handleSetBrcbValues(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<SetBRCBValuesRequestPDU_t*>(requestData);
    auto response = createAsnResponse<SetBRCBValuesErrorPDU_t>();
    bool ok = true;
    for(int i = 0; i < request->brcb.list.count; ++i)
    {
        auto data = request->brcb.list.array[i];
        string reference = (const char *)data->reference.buf;

        string domainName;
        string itemId;
        splitDomainAndItemId(reference.c_str(), domainName, itemId);

        // convert to rc name
        itemId.insert(itemId.find("."), "$BR");
        std::replace(itemId.begin(), itemId.end(),'.', '$');
        GspMmsDomain *domain = GspMmsDevice_getDomain(self->server->device, domainName.c_str());
        auto ret = setBrcbResponse(self, domain, itemId, *data);
        ok = ok && !ret;
        if(ret)
        {
            asn_sequence_add(&response->result, ret);
        }
    }

    if(ok)
    {
        ASN_STRUCT_FREE(asn_DEF_SetBRCBValuesErrorPDU, response);
        return calloc(1, sizeof(NULL_t));
    }
    throw response;
}

void *GspServerReport::handleGetUrcbValues(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetURCBValuesRequestPDU_t*>(requestData);
    auto response = createAsnResponse<GetURCBValuesResponsePDU_t>();
    response->moreFollows = (BOOLEAN_t *)calloc(1, sizeof(BOOLEAN_t));
    *response->moreFollows = 0;
    for(int i = 0; i < request->reference.list.count; ++i)
    {
        auto ref = request->reference.list.array[i];
        if(i >= 50)
        {
            *response->moreFollows = 1;
            break;
        }

        GetURCBValuesResponsePDU__urcb__Member *member = (GetURCBValuesResponsePDU__urcb__Member*)calloc(1, sizeof(GetURCBValuesResponsePDU__urcb__Member));
        string reference = (const char *)ref->buf;
        string domainName;
        string itemId;
        splitDomainAndItemId(reference.c_str(), domainName, itemId);

        // convert to rc name
        itemId.insert(itemId.find("."), "$RP");
        std::replace(itemId.begin(), itemId.end(),'.', '$');
        GspMmsDomain *domain = GspMmsDevice_getDomain(self->server->device, domainName.c_str());

        member->present = GetURCBValuesResponsePDU__urcb__Member_PR_value;
        auto ret = fillUrcbResponse(self->server, domain, itemId, &member->choice.value);

        if(!ret)
        {
            member->present = GetURCBValuesResponsePDU__urcb__Member_PR_error;
            member->choice.error = ServiceError_failed_due_to_server_constraint;
        }

        asn_sequence_add(&response->urcb, member);
    }
    return response;
}

SetURCBValuesErrorPDU__result__Member* setUrcbResponse(GspMmsServerConnection self,
                     GspMmsDomain *domain,
                     const string &referName,
                     SetURCBValuesRequestPDU__urcb__Member &brcb)
{
    bool isOk = false;
    bool findRc = false;
    auto respItem = (SetURCBValuesErrorPDU__result__Member*)calloc(1, sizeof(SetURCBValuesErrorPDU__result__Member));
    GspMmsMapping *mapping = static_cast<GspMmsMapping *>(self->server->connectionHandlerParameter);
    GspLinkedList nextElement = mapping->reportControls;
    for(auto &item : *nextElement)
    {
        GspReportControl* rc = (GspReportControl*) item;
        if(rc->domain == domain && referName == rc->name)
        {
            findRc = true;
            isOk = true;
            GspMmsValue *value = nullptr;
            if(brcb.rptEna && !*brcb.rptEna)
            {
                value = GspMmsValue_newBoolean(*brcb.rptEna);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"RptEna", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->rptEna = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->rptEna = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.bufTm)
            {
                value = GspMmsValue_newUnsignedFromUint32(*brcb.bufTm);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"bufTm", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->bufTm = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->bufTm = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.datSet)
            {
                value = GspMmsValue_newMmsString((char *)brcb.datSet->buf);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"datSet", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->datSet = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->datSet = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.resv)
            {
                value = GspMmsValue_newBoolean(*brcb.resv);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"resv", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->resv = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->resv = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.intgPd)
            {
                value = GspMmsValue_newUnsignedFromUint32(*brcb.intgPd);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"intgPd", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->intgPd = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->intgPd = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.optFlds)
            {
                value = GspMmsValue_newBitString(brcb.optFlds->size * 8 - brcb.optFlds->bits_unused);
                GspBIT_STRING_createBitString(&value->choice.bit_string, (const char *)brcb.optFlds->buf, brcb.optFlds->size, brcb.optFlds->bits_unused);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"optFlds", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->optFlds = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->optFlds = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.rptID)
            {
                value = GspMmsValue_newVisibleString((const char *)brcb.rptID->buf);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"rptID", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->rptID = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->rptID = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.trgOps)
            {
                value = GspMmsValue_newBitString(brcb.trgOps->size * 8 - brcb.trgOps->bits_unused);
                GspBIT_STRING_createBitString(&value->choice.bit_string, (const char *)brcb.trgOps->buf, brcb.trgOps->size, brcb.trgOps->bits_unused);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"trgOps", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->trgOps = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->trgOps = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }

            if(brcb.rptEna && *brcb.rptEna)
            {
                value = GspMmsValue_newBoolean(*brcb.rptEna);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"RptEna", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->rptEna = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->rptEna = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }
            if(brcb.gi)
            {
                value = GspMmsValue_newBoolean(*brcb.gi);
                auto mmsError = GspReporting_RCBWriteAccessHandler(mapping, rc, (char *)"gi", value, self);
                if(mmsError != GSP_DATA_ACCESS_ERROR_SUCCESS)
                {
                    isOk = false;
                    respItem->gi = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
                    *respItem->gi = GspMmsDataAccessErrorToServiceError(mmsError);
                }
                GspMmsValue_delete(value);
            }
            break;
        }
    }
    if(isOk)
    {
        free(respItem);
        return nullptr;
    }

    if(!findRc)
    {
        NLOG_WARN("没有找到[{}/{}]对应的报告控制块", domain->domainName, referName);
    }
    return respItem;
}

void *GspServerReport::handleSetUrcbValues(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<SetURCBValuesRequestPDU_t*>(requestData);
    auto response = createAsnResponse<SetURCBValuesErrorPDU_t>();
    bool ok = true;
    for(int i = 0; i < request->urcb.list.count; ++i)
    {
        auto data = request->urcb.list.array[i];
        string reference = (const char *)data->reference.buf;

        string domainName;
        string itemId;
        splitDomainAndItemId(reference.c_str(), domainName, itemId);

        // convert to rc name
        itemId.insert(itemId.find("."), "$RP");
        std::replace(itemId.begin(), itemId.end(),'.', '$');
        GspMmsDomain *domain = GspMmsDevice_getDomain(self->server->device, domainName.c_str());
        auto ret = setUrcbResponse(self, domain, itemId, *data);
        ok = ok && !ret;
        if(ret)
        {
            asn_sequence_add(&response->result, ret);
        }
    }

    if(ok)
    {
        ASN_STRUCT_FREE(asn_DEF_SetURCBValuesErrorPDU, response);
        return calloc(1, sizeof(NULL_t));
    }

    throw response;
}
