#include "mms_server_internal.h"
#include "nlogging.h"
#include "iso_server_private.h"
#include "mms_server_func.h"
#include "logicaldevice.h"
#include "mms_mapping.h"
#include "sqlite3.h"
#include "sqlite_orm/sqlite_orm.h"
#include "mms_named_variable_list.h"
#include "ied_server_private.h"
#include <tuple>

void *GspServerSettingGroup::handleSelectActiveSg(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<SelectActiveSGRequestPDU_t*>(requestData);
    int sgNumber = request->settingGroupNumber;
    string reference = (const char *)request->sgcbReference.buf;
    return handleSelectActiveSgImp(self, reference, sgNumber);
}

void *GspServerSettingGroup::handleSelectActiveSgImp(GspMmsServerConnection self, const string &reference, int sgNumber)
{
    auto response = createAsnResponse<SelectActiveSGResponsePDU_t>();
    string ldName;
    string itemId;
    splitDomainAndItemId(reference, ldName, itemId);
    vector<string> strList;
    splitStr(strList, itemId, '.');

    auto mapping = static_cast<GspMmsMapping*>(self->server->connectionHandlerParameter);
    GspMmsDomain *domain = GspMmsDevice_getDomain(self->server->device, ldName.c_str());
    if(!domain)
    {
        ASN_STRUCT_FREE(asn_DEF_SelectActiveSGResponsePDU, response);
        throw invalid_argument(fmt::format("没有找到[{}]对应的模型", ldName));
    }
    auto sg = GspgetSettingGroupByMmsDomain(mapping, domain);

    GspClientConnection clientConnection = Gsp_private_IedServer_getClientConnectionByHandle(mapping->iedServer, self);

    if(sg)
    {
        int ret = GspchangeActiveSettingGroup(mapping, sg, sgNumber, clientConnection);
        if(ret != GSP_DATA_ACCESS_ERROR_SUCCESS)
        {
            ASN_STRUCT_FREE(asn_DEF_SelectActiveSGResponsePDU, response);
            throw GspMmsDataAccessErrorToServiceError((GspMmsDataAccessError)ret);
        }
    }
    else
    {
        ASN_STRUCT_FREE(asn_DEF_SelectActiveSGResponsePDU, response);
        throw invalid_argument(fmt::format("没有找到[{}]对应的定值", domain->domainName));
    }
    return response;
}

void *GspServerSettingGroup::handleSelectEditSg(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<SelectEditSGRequestPDU_t*>(requestData);
    auto response = createAsnResponse<SelectEditSGResponsePDU_t>();
    int sgNumber = request->settingGroupNumber;
    string reference = (const char *)request->sgcbReference.buf;
    string ldName;
    string itemId;
    splitDomainAndItemId(reference, ldName, itemId);
    vector<string> strList;
    splitStr(strList, itemId, '.');

    auto mapping = static_cast<GspMmsMapping*>(self->server->connectionHandlerParameter);

    GspMmsDomain *domain = GspMmsDevice_getDomain(self->server->device, ldName.c_str());
    if(!domain)
    {
        ASN_STRUCT_FREE(asn_DEF_SelectEditSGResponsePDU, response);
        throw invalid_argument(fmt::format("没有找到[{}]对应的模型", ldName));
    }
    auto sg = GspgetSettingGroupByMmsDomain(mapping, domain);

    if(sg)
    {
        int error = GspSelectEditSg(mapping, (GspClientConnection)self, sg, sgNumber);
        if(error != GSP_DATA_ACCESS_ERROR_SUCCESS)
        {
            ASN_STRUCT_FREE(asn_DEF_SelectEditSGResponsePDU, response);
            throw GspMmsDataAccessErrorToServiceError((GspMmsDataAccessError)error);
        }
    }
    else
    {
        ASN_STRUCT_FREE(asn_DEF_SelectEditSGResponsePDU, response);
        throw invalid_argument(fmt::format("没有找到[{}]对应的定值", domain->domainName));
    }
    return response;
}

void *GspServerSettingGroup::handleSetEditSgValue(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<SetEditSGValueRequestPDU_t*>(requestData);
    auto response = createAsnResponse<SetEditSGValueResponsePDU_t>();
    auto mapping = static_cast<GspMmsMapping*>(self->server->connectionHandlerParameter);
    int editSg = -1;
    for(int i = 0; i < request->data.list.count; ++i)
    {
        auto data = request->data.list.array[i];
        string reference = (const char *)data->reference.buf;
        string ldName;
        string itemId;
        splitDomainAndItemId(reference, ldName, itemId);
        vector<string> strList;
        splitStr(strList, itemId, '.');
        GspMmsDomain *domain = GspMmsDevice_getDomain(self->server->device, ldName.c_str());
        if(!domain)
        {
            ASN_STRUCT_FREE(asn_DEF_SetEditSGValueResponsePDU, response);
            throw invalid_argument(fmt::format("没有找到[{}]对应的模型", ldName));
        }
        auto sg = GspgetSettingGroupByMmsDomain(mapping, domain);
        if(!sg)
        {
            ASN_STRUCT_FREE(asn_DEF_SetEditSGValueResponsePDU, response);
            throw invalid_argument(fmt::format("没有找到[{}]对应的定值", domain->domainName));
        }

        auto ret = setDataByReference(self, reference, "SE", &data->value);
        auto error = new ServiceError_t();
        *error = GspMmsDataAccessErrorToServiceError(ret);

        if (sg->sgcb->editSG>0 && sg->sgcb->editSG<=sg->sgcb->numOfSGs)
        {
            auto &editMap = sg->sgcb->editSgs[sg->sgcb->editSG-1];
            auto seData = mmsServer_getDataByReference(self, reference, "SE");

            editMap.insert({reference, seData});
        }

        ASN_SEQUENCE_ADD(&response->result, error);
    }
    return response;
}

void *GspServerSettingGroup::handleConfirmEditSgValues(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<ConfirmEditSGValuesRequestPDU_t*>(requestData);
    auto response = createAsnResponse<ConfirmEditSGValuesResponsePDU_t>();
    string reference = (const char *)request->sgcbReference.buf;
    string ldName;
    string itemId;
    splitDomainAndItemId(reference, ldName, itemId);
    GspMmsDomain *domain = GspMmsDevice_getDomain(self->server->device, ldName.c_str());
    auto mapping = static_cast<GspMmsMapping*>(self->server->connectionHandlerParameter);

    if(!domain)
    {
        ASN_STRUCT_FREE(asn_DEF_SetEditSGValueResponsePDU, response);
        throw invalid_argument(fmt::format("没有找到[{}]对应的模型", ldName));
    }
    auto sg = GspgetSettingGroupByMmsDomain(mapping, domain);
    if(!sg)
    {
        ASN_STRUCT_FREE(asn_DEF_SetEditSGValueResponsePDU, response);
        throw invalid_argument(fmt::format("没有找到[{}]对应的定值组", domain->domainName));
    }

    // 确认编辑定值, 数据写入数据库
    int error = GspSetEditSgs(mapping, (GspClientConnection)self, sg);
    if(error != GSP_DATA_ACCESS_ERROR_SUCCESS)
    {
        ASN_STRUCT_FREE(asn_DEF_ConfirmEditSGValuesResponsePDU, response);
        throw GspMmsDataAccessErrorToServiceError((GspMmsDataAccessError)error);
    }

    return calloc(sizeof(NULL_t), 1);
}

void *GspServerSettingGroup::handleGetEditSgValue(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetEditSGValueRequestPDU_t*>(requestData);
    auto response = createAsnResponse<GetEditSGValueResponsePDU_t>();
    for(int i = 0; i < request->data.list.count; ++i)
    {
        auto item = request->data.list.array[i];
        string fc = (const char *)item->fc.buf;
        string reference = (const char *)item->reference.buf;

        // 读取定值只需要从SE节点读取即可
        auto data = mmsServer_getDataByReference(self, reference, fc);
        if(!data)
        {
            throw invalid_argument(fmt::format("没有找到[{}]对应的定值!!", reference));
        }
        ASN_SEQUENCE_ADD(&response->value, data);
    }
    response->moreFollows = (BOOLEAN_t *)calloc(1, sizeof(BOOLEAN_t));
    return response;
}

void *GspServerSettingGroup::handleGetSgcbValues(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetSGCBValuesRequestPDU_t*>(requestData);
    auto response = createAsnResponse<GetSGCBValuesResponsePDU_t>();
    for(int i = 0; i < request->sgcbReference.list.count; ++i)
    {
        auto data = request->sgcbReference.list.array[i];
        string reference = (const char *)data->buf;
        string ldName;
        string itemId;
        splitDomainAndItemId(reference, ldName, itemId);
        vector<string> strList;
        splitStr(strList, itemId, '.');

        auto mapping = static_cast<GspMmsMapping*>(self->server->connectionHandlerParameter);
        GspMmsDomain *domain = GspMmsDevice_getDomain(self->server->device, ldName.c_str());
        if(!domain)
        {
            ASN_STRUCT_FREE(asn_DEF_GetSGCBValuesResponsePDU, response);
            throw invalid_argument(fmt::format("没有找到[{}]对应的模型", ldName));
        }
        auto sg = GspgetSettingGroupByMmsDomain(mapping, domain);
        if(!sg)
        {
            ASN_STRUCT_FREE(asn_DEF_GetSGCBValuesResponsePDU, response);
            throw invalid_argument(fmt::format("没有找到[{}]对应的定值", domain->domainName));
        }
        auto item = (GetSGCBValuesResponsePDU__sgcb__Member*)calloc(1, sizeof(GetSGCBValuesResponsePDU__sgcb__Member));

        if(sg)
        {
            item->present = GetSGCBValuesResponsePDU__sgcb__Member_PR_value;
            auto values = sg->sgcbMmsValues;
            auto value = GspMmsValue_getElement(values, 0);
            item->choice.value.numOfSG = GspMmsValue_toInt32(value);
            value = GspMmsValue_getElement(values, 1);
            item->choice.value.actSG = GspMmsValue_toInt32(value);
            value = GspMmsValue_getElement(values, 2);
            item->choice.value.editSG = GspMmsValue_toInt32(value);
            value = GspMmsValue_getElement(values, 4);
            GspFillMmsValueToUtcTime(item->choice.value.lActTm, value);
        }
        else
        {
            item->present = GetSGCBValuesResponsePDU__sgcb__Member_PR_error;
            item->choice.error = ServiceError_instance_not_available;
        }

        ASN_SEQUENCE_ADD(&response->sgcb.list.array, item);
    }
    return response;
}
