#include "mms_server_internal.h"
#include "asn_inc.h"
#include "mms_mapping.h"
#include "iso_server_private.h"
#include "mms_server_func.h"
#include <stdexcept>
#include "nlogging.h"

void *GspServerDataSet::handleGetDataSetDirectory(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetDataSetDirectoryRequestPDU_t*>(requestData);
    auto response = createAsnResponse<GetDataSetDirectoryResponsePDU_t>();
    string refer = (const char *)request->datasetReference.buf;
    toDollarReference(refer);
    string lastRefer;
    if(request->referenceAfter)
    {
        lastRefer = (const char *)request->referenceAfter->buf;
        toDollarReference(lastRefer);
    }
    auto dataSet = GspMmsMapping_getDomainSpecificDataSet((GspMmsMapping*)self->server->connectionHandlerParameter, refer.c_str());
    if(!dataSet)
    {
        throw runtime_error(fmt::format("数据集[{}]不存在", refer));
    }
    auto entry = dataSet->fcdas;
    bool begin = lastRefer.empty();

    while(entry)
    {
        if(!begin)
        {
            string varName = entry->variableName;
            string fc;
            string refer;
            splitFcFromReference(varName, fc, refer);

            if(strcmp(refer.c_str(), lastRefer.c_str()) == 0)
            {
                begin = true;
            }
            entry = entry->sibling;
            continue;
        }
        else
        {
            string refer;
            string fc;
            string dsName = string(dataSet->iedName) + entry->logicalDeviceName + "/" + entry->variableName;
            splitFcFromReference(dsName, fc, refer);
            toDotReference(refer);
            auto member = new GetDataSetDirectoryResponsePDU__memberData__Member();
            memset(member, 0, sizeof(GetDataSetDirectoryResponsePDU__memberData__Member));
            OCTET_STRING_fromString(&member->fc, fc.c_str());
            OCTET_STRING_fromString(&member->reference, refer.c_str());
            ASN_SEQUENCE_ADD(&response->memberData, member);
            entry = entry->sibling;
        }
    }
    response->moreFollows = (BOOLEAN_t*)calloc(1, sizeof(BOOLEAN_t));
    *response->moreFollows = 0;
    return response;
}

void *GspServerDataSet::handleCreateDataSet(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<CreateDataSetRequestPDU_t*>(requestData);
    auto response = createAsnResponse<CreateDataSetResponsePDU_t>();
    auto mapping = (GspMmsMapping *)self->server->connectionHandlerParameter;

    string refer = (const char *)request->datasetReference.buf;
    toDollarReference(refer);
    printf("%s\n", refer.c_str());
    string domain;
    string itemId;
    splitDomainAndItemId(refer, domain, itemId);
    auto dataSetDomain = GspMmsDevice_getDomain(mapping->mmsDevice, domain.c_str());

    auto varList = MmsNamedVariableList_create(dataSetDomain, (char *)itemId.c_str(), false);

    for(int i = 0; i < request->memberData.list.count; ++i)
    {
        auto item = request->memberData.list.array[i];
        GspMmsAccessSpecifier accessSpecifier;
        accessSpecifier.domain = dataSetDomain;
        string refer = (const char *)item->reference.buf;
        toDollarReference(refer);
        addFcToReference(refer, (const char *)item->fc.buf, '$');
        accessSpecifier.variableName = (char *)refer.c_str();
        accessSpecifier.arrayIndex = -1;
        accessSpecifier.componentName = nullptr;

        GspMmsNamedVariableListEntry variableListEntry =
                MmsNamedVariableListEntry_create(accessSpecifier);
        MmsNamedVariableList_addVariable(varList, variableListEntry);
    }

    GspMmsDomain_addNamedVariableList(dataSetDomain, varList);
    auto ds = GspMmsMapping_getDomainSpecificDataSet(mapping, refer.c_str());
    if(ds)
    {
        mapping->dataSetMap[refer] = ds;
        return response;
    }
    else
    {
        throw runtime_error(fmt::format("数据集 {} 创建失败!", refer));
    }
}

void *GspServerDataSet::handleDeleteDataSet(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<DeleteDataSetRequestPDU_t*>(requestData);
    auto response = createAsnResponse<DeleteDataSetResponsePDU_t>();

    string refer = (const char *)request->datasetReference.buf;
    toDollarReference(refer);
    printf("%s\n", refer.c_str());
    auto mapping = (GspMmsMapping*)self->server->connectionHandlerParameter;
    auto dataSet = mapping->dataSetMap[refer];
    if(dataSet)
    {
        GspMmsMapping_freeDynamicallyCreatedDataSet(dataSet);
        mapping->dataSetMap.erase(refer);
    }
    else
    {
        throw runtime_error(fmt::format("数据集[{}]不存在", refer));
    }
    return response;
}

void *GspServerDataSet::handleSetDataSetValues(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<SetDataSetValuesRequestPDU_t*>(requestData);
    auto response = createAsnResponse<SetDataSetValuesResponsePDU_t>();
    string refer = (const char *)request->datasetReference.buf;
    toDollarReference(refer);
    printf("%s\n", refer.c_str());
    string lastRefer;
    if(request->referenceAfter)
    {
        lastRefer = (const char *)request->referenceAfter->buf;
        toDollarReference(lastRefer);
    }
    auto dataSet = GspMmsMapping_getDomainSpecificDataSet((GspMmsMapping*)self->server->connectionHandlerParameter, refer.c_str());
    if(!dataSet)
    {
        throw runtime_error(fmt::format("数据集[{}]不存在", refer));
    }

    auto entry = dataSet->fcdas;
    bool begin = lastRefer.empty();
    int i = 0;
    while(entry)
    {
        if(!begin)
        {
            if(strcmp(entry->variableName, lastRefer.c_str()) == 0)
            {
                begin = true;
            }
            entry = entry->sibling;
            continue;
        }
        else
        {
            auto ret = GspMmsValue_update(entry->value, request->value.list.array[i]);
            auto error = (ServiceError_t *)calloc(1, sizeof(ServiceError_t));
            if(ret)
            {
                *error = ServiceError_no_error;
            }
            else
            {
                *error = ServiceError_failed_due_to_server_constraint;
            }
            ASN_SEQUENCE_ADD(&response->result, error);
            i++;
            entry = entry->sibling;
        }
    }
    return response;
}

void *GspServerDataSet::handleGetDataSetValues(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetDataSetValuesRequestPDU_t*>(requestData);
    auto response = createAsnResponse<GetDataSetValuesResponsePDU_t>();
    string refer = (const char *)request->datasetReference.buf;
    toDollarReference(refer);
    string lastRefer;
    if(request->referenceAfter)
    {
        lastRefer = (const char *)request->referenceAfter->buf;
        toDollarReference(lastRefer);
    }

    bool begin = lastRefer.empty();
    printf("%s\n", refer.c_str());
    auto dataSet = GspMmsMapping_getDomainSpecificDataSet((GspMmsMapping*)self->server->connectionHandlerParameter, refer.c_str());
    if(!dataSet)
    {
        throw runtime_error(fmt::format("数据集[{}]不存在", refer));
    }
    auto entry = dataSet->fcdas;
    while(entry)
    {
        if(!begin)
        {
            if(strcmp(entry->variableName, lastRefer.c_str()) == 0)
            {
                begin = true;
            }
            entry = entry->sibling;
            continue;
        }
        else
        {
            Data_t *data = new Data_t();
            memset(data, 0, sizeof(Data_t));
            GspMmsValue_update(data, entry->value);
            ASN_SEQUENCE_ADD(&response->value, data);
            entry = entry->sibling;
        }
    }
   
    response->moreFollows = (BOOLEAN_t*)calloc(1, sizeof(BOOLEAN_t));
    *response->moreFollows = 0;
    return response;
}
