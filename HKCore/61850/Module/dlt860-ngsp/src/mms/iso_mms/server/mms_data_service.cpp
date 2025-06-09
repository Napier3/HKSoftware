#include "mms_server_internal.h"
#include "nlogging.h"
#include "iso_server_private.h"
#include "mms_server_func.h"
#include "logicaldevice.h"
#include "mms_mapping.h"
#include "ied_server_private.h"

void *GspServerData::handleGetDataValues(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetDataValuesRequestPDU_t*>(requestData);
    auto response = createAsnResponse<GetDataValuesResponsePDU_t>();
    for(int i = 0; i < request->data.list.count; ++i)
    {
        auto item = request->data.list.array[i];
        string refer((char *)item->reference.buf,
                        item->reference.size);
        string fc;
        if(item->fc)
        {
            fc = string((char *)item->fc->buf,
                        item->fc->size);

            if(fc == "XX")
            {
                fc.clear();
            }
        }
        auto data = mmsServer_getDataByReference(self, refer, fc);
        ASN_SEQUENCE_ADD(&response->value, data);
    }
    response->moreFollows = createAsnResponse<BOOLEAN_t>();
    *response->moreFollows = 0;
    
    return response;
}

extern void fillSubDataDefine(GspModelNode* modelNode, const string& fc, DataDefinition_t *dataDefine);

void GspServerData::fillDataDefine(GspModelNode* modelNode, GetDataDefinitionResponsePDU_t* resp, const string& parentRef, const string& fc, const string& referAfter)
{
    auto member = (GetDataDefinitionResponsePDU__data__Member *)calloc(1, sizeof(GetDataDefinitionResponsePDU__data__Member));

    try {
        if(modelNode->modelType == GspDataObjectModelType)
        {
            member->cdcType = (OCTET_STRING*)calloc(1, sizeof(OCTET_STRING_t));
            auto dataObject = (GspDataObject *)modelNode;
            OCTET_STRING_fromString(member->cdcType, dataObject->cdcType);
        }

        fillSubDataDefine(modelNode, fc, &member->definition);

        ASN_SEQUENCE_ADD(&resp->data, member);

    } catch(const std::exception &e) {
        ASN_STRUCT_FREE(asn_DEF_DataDefinition, &member->definition);
        if(member->cdcType)
        {
            ASN_STRUCT_FREE(asn_DEF_OCTET_STRING, member->cdcType);
        }
        free(member);
        auto member = (GetDataDefinitionResponsePDU__data__Member *)calloc(1, sizeof(GetDataDefinitionResponsePDU__data__Member));

        member->definition.present = DataDefinition_PR_error;
        member->definition.choice.error = ServiceError_instance_not_available;
        ASN_SEQUENCE_ADD(&resp->data, member);
        NLOG_WARN(e.what());
    }
}


void *GspServerData::handleSetDataValues(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<SetDataValuesRequestPDU_t*>(requestData);

    auto response = createAsnResponse<SetDataValuesResponsePDU_t>();

    for(int i = 0; i < request->data.list.count; ++i)
    {
        auto item = request->data.list.array[i];
        string refer((char *)item->reference.buf,
                     item->reference.size);
        string fc;
        if(item->fc)
        {
            fc = string((char *)item->fc->buf,
                        item->fc->size);
        }
        auto ret = setDataByReference(self, refer, fc, &item->value);
        auto error = new ServiceError_t();
        *error = GspMmsDataAccessErrorToServiceError(ret);
        ASN_SEQUENCE_ADD(&response->result, error);
    }
    return response;
}

void fillModelNode(GspModelNode *modelNode, bool &begin, const string &lastAfter, const string &ldName, const string &prefix, GetDataDirectoryResponsePDU_t *response)
{
    while(modelNode)
    {
        if(!modelNode->firstChild)
        {
            switch (modelNode->modelType)
            {
            case GspDataAttributeModelType:
            {
                auto dataAttr = reinterpret_cast<GspDataAttribute*>(modelNode);
                string refer = ldName + "/" + prefix + "." + modelNode->name;
                if(refer == lastAfter)
                {
                    begin = true;
                }
                else
                {
                    auto item = new GetDataDirectoryResponsePDU__dataAttribute__Member();
                    memset(item, 0, sizeof(GetDataDirectoryResponsePDU__dataAttribute__Member));
                    OCTET_STRING_fromString(&item->reference, refer.c_str());
                    char *fc = GspFunctionalConstraint_toString(dataAttr->fc);
                    if(fc)
                    {
                        item->fc = new FunctionalConstraint_t();
                        OCTET_STRING_fromString(item->fc, fc);
                        delete [] fc;
                    }

                    ASN_SEQUENCE_ADD(&response->dataAttribute, item);

                    if(response->dataAttribute.list.count > 50)
                    {
                        throw runtime_error("");
                    }
                }
            }
                break;
            default:
                break;
            }
        }
        else
        {
            fillModelNode(modelNode->firstChild, begin, lastAfter, ldName, prefix + "." + modelNode->name, response);
            string refer = ldName + "/" + prefix + "." + modelNode->name;
            if(refer == lastAfter)
            {
                begin = true;
            }
            else
            {
                auto item = new GetDataDirectoryResponsePDU__dataAttribute__Member();
                memset(item, 0, sizeof(GetDataDirectoryResponsePDU__dataAttribute__Member));
                OCTET_STRING_fromString(&item->reference, refer.c_str());
                ASN_SEQUENCE_ADD(&response->dataAttribute, item);
                if(response->dataAttribute.list.count > 50)
                {
                    throw runtime_error("");
                }
            }
        }
        modelNode = modelNode->sibling;
    }
}

void findModelNode(GspModelNode *modelNode, int depth, const vector<string> &dataVec, const string &lastAfter, const string &ldName, const string &prefix, GetDataDirectoryResponsePDU_t *response)
{
    if(depth == dataVec.size())
    {
        // 开始处理
        bool begin = lastAfter.empty();
        fillModelNode(modelNode, begin, lastAfter, ldName, prefix, response);        
        return;
    }

    while(modelNode)
    {
        if(dataVec[depth].compare(modelNode->name) == 0)
        {
            depth++;
            findModelNode(modelNode->firstChild, depth, dataVec, lastAfter, ldName, prefix + "." + modelNode->name, response);
            break;
        }
        modelNode = modelNode->sibling;
    }
}

void *GspServerData::handleGetDataDirectory(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetDataDirectoryRequestPDU_t*>(requestData);
    auto response = createAsnResponse<GetDataDirectoryResponsePDU_t>();

    uint32_t more = 0;
    response->moreFollows = &more;
    auto *mapping = static_cast<GspMmsMapping*>(self->server->connectionHandlerParameter);

    string domainName;
    string itemId;
    splitDomainAndItemId((char *)request->dataReference.buf, domainName, itemId);
    auto ld = GspMmsMapping_getLdByDomainName(mapping, domainName);
    
    string lastAfter;
    if(request->referenceAfter)
    {
        lastAfter = (const char*)request->referenceAfter->buf;
    }
    if(!ld)
    {
        throw exception();
    }

    string fc;
    vector<string> nameList;
    splitStr(nameList, itemId, '.');
    
    if(nameList.size() > 1)
    {
        if(nameList[1].size() == 2)
        {
            auto iFc = GspFunctionalConstraint_fromString(fc.c_str());
            fc = (iFc != DLT860_FC_NONE ? fc : "");
        }
    }

    auto ln = ld->firstChild;
    int depth = 0;

    try
    {
        while(ln)
        {
            if(nameList[0].compare(ln->name) == 0)
            {
                depth++;
                if(!fc.empty())
                {
                    depth++;
                }
                
                auto node = ln->firstChild;
                findModelNode(node, depth, nameList, lastAfter, domainName, ln->name, response);
                break;    
            }
            
            ln = ln->sibling;
        }
    }
    catch(const std::runtime_error &ex)
    {
        response->moreFollows = nullptr;
    }

    return response;
}

DataDefinition_t *fillModelNodeDefine(GspModelNode *node, const string &fc, 
                        const string &ldName, const string &prefix)
{
    switch (node->modelType)
    {
    case GspLogicalDeviceModelType:
        break;
    case GspLogicalNodeModelType:
        break;
    case GspDataObjectModelType:
    {
        if(node->firstChild)
        {
            auto childData = new DataDefinition_t();
            memset(childData, 0, sizeof(DataDefinition_t));

            childData->present = DataDefinition_PR_structure;
            
            auto child = node->firstChild;
            while(child)
            {

                auto childItem = fillModelNodeDefine(child, fc, ldName, prefix);

                if(childItem)
                {
                    auto *member = new DataDefinition__structure__Member();
                    memset(member, 0, sizeof(DataDefinition__structure__Member));
                    OCTET_STRING_fromString(&member->name, child->name);
                    member->type = childItem;
                    if(fc.empty())
                    {

                    }
                    ASN_SEQUENCE_ADD(&childData->choice.structure, member);
                }
                child = child->sibling;
            }
            return childData;
        }   
        return nullptr;
    }
        break;
    case GspDataAttributeModelType:
    {
        GspDataAttribute *dataAttr = reinterpret_cast<GspDataAttribute*>(node);
        if(!fc.empty() && fc != GspFunctionalConstraint_toString(dataAttr->fc))
        {
            return nullptr;
        }
        auto childData = new DataDefinition_t();
        memset(childData, 0, sizeof(DataDefinition_t));

        auto type = dataAttr->type;

        switch (type) {
        case DLT860_CONSTRUCTED:
        {
            childData->present = DataDefinition_PR_structure;
            
            auto child = node->firstChild;
            while(child)
            {
                auto childItem = fillModelNodeDefine(child, fc, ldName, prefix);
                if(childItem)
                {
                    auto *member = new DataDefinition__structure__Member();
                    memset(member, 0, sizeof(DataDefinition__structure__Member));
                    OCTET_STRING_fromString(&member->name, child->name);
                    member->type = childItem;
                    if(fc.empty())
                    {

                    }
                    ASN_SEQUENCE_ADD(&childData->choice.structure, member);
                }

                child = child->sibling;
            }
        }
            break;
        case DLT860_BOOLEAN:
            childData->present = DataDefinition_PR(GSP_MMS_BOOLEAN + 1);
            break;
        case DLT860_INT8:
            childData->present = DataDefinition_PR(GSP_MMS_INT8 + 1);
            break;
        case DLT860_INT16:
            childData->present = DataDefinition_PR(GSP_MMS_INT16 + 1);
            break;
        case DLT860_INT32:
            childData->present = DataDefinition_PR(GSP_MMS_INT32 + 1);
            break;
        case DLT860_INT64:
            childData->present = DataDefinition_PR(GSP_MMS_INT64 + 1);
            break;
//        case IEC61850_INT128:
//            namedVariable->type = MMS_INT128;
//            break;
        case DLT860_INT8U:
            childData->present = DataDefinition_PR(GSP_MMS_UINT8 + 1);
            break;
        case DLT860_INT16U:
            childData->present = DataDefinition_PR(GSP_MMS_UINT16 + 1);
            break;
//        case IEC61850_INT24U:
//            namedVariable->type = MMS_UNSIGNED;
//            break;
        case DLT860_INT32U:
            childData->present = DataDefinition_PR(GSP_MMS_UINT32 + 1);
            break;
        case DLT860_FLOAT32:
            childData->present = DataDefinition_PR(GSP_MMS_FLOAT32 + 1);
            break;
        case DLT860_FLOAT64:
            childData->present = DataDefinition_PR(GSP_MMS_FLOAT64 + 1);
            break;
        case DLT860_ENUMERATED:
            childData->present = DataDefinition_PR(GSP_MMS_INT8 + 1);
            break;
        case DLT860_CHECK:
            childData->present = DataDefinition_PR(GSP_MMS_BIT_STRING + 1);
            childData->choice.bit_string = -2;
            break;
        case DLT860_CODEDENUM:
            childData->present = DataDefinition_PR(GSP_MMS_BIT_STRING + 1);
            childData->choice.bit_string = 2;
            break;
        case DLT860_OCTET_STRING_6:
            childData->present = DataDefinition_PR(GSP_MMS_OCTET_STRING + 1);
            childData->choice.octet_string = -6;
            break;
        case DLT860_OCTET_STRING_8:
            childData->present = DataDefinition_PR(GSP_MMS_OCTET_STRING + 1);
            childData->choice.octet_string = 8;
            break;
        case DLT860_OCTET_STRING_64:
            childData->present = DataDefinition_PR(GSP_MMS_OCTET_STRING + 1);
            childData->choice.octet_string = -64;
            break;
        case DLT860_CURRENCY:  /* mapping of Currency BasicType (see tissue 1047) */
            childData->present = DataDefinition_PR(GSP_MMS_VISIBLE_STRING + 1);
            childData->choice.visible_string = -3;
            break;
        case DLT860_VISIBLE_STRING_32:
            childData->present = DataDefinition_PR(GSP_MMS_VISIBLE_STRING + 1);
            childData->choice.visible_string = -32;
            break;
        case DLT860_VISIBLE_STRING_64:
            childData->present = DataDefinition_PR(GSP_MMS_VISIBLE_STRING + 1);
            childData->choice.visible_string = -64;
            break;
        case DLT860_VISIBLE_STRING_65:
            childData->present = DataDefinition_PR(GSP_MMS_VISIBLE_STRING + 1);
            childData->choice.visible_string = -65;
            break;
        case DLT860_VISIBLE_STRING_129:
            childData->present = DataDefinition_PR(GSP_MMS_VISIBLE_STRING + 1);
            childData->choice.visible_string = -129;
            break;
        case DLT860_VISIBLE_STRING_255:
            childData->present = DataDefinition_PR(GSP_MMS_VISIBLE_STRING + 1);
            childData->choice.visible_string = -255;
            break;
        case DLT860_UNICODE_STRING_255:
            childData->present = DataDefinition_PR(GSP_MMS_UNICODE_STRING + 1);
            childData->choice.unicode_string = -255;
            break;
        case DLT860_GENERIC_BITSTRING:
            childData->present = DataDefinition_PR(GSP_MMS_BIT_STRING + 1);
            break;
        case DLT860_TIMESTAMP:
            childData->present = DataDefinition_PR(GSP_MMS_UTC_TIME + 1);
            break;
        case DLT860_QUALITY:
            childData->present = DataDefinition_PR(GSP_MMS_QUALITY + 1);
            break;
        case DLT860_ENTRY_TIME:
            childData->present = DataDefinition_PR(GSP_MMS_BINARY_TIME + 1);
            break;
        // case IEC61850_PHYCOMADDR:
        //     MmsMapping_createPhyComAddrStructure(namedVariable);
        //     break;
        case DLT860_OPTFLDS:
            childData->present = DataDefinition_PR(GSP_MMS_BIT_STRING + 1);
            childData->choice.bit_string = 10;
            break;
        case DLT860_TRGOPS:
            childData->present = DataDefinition_PR(GSP_MMS_BIT_STRING + 1);
            childData->choice.bit_string = 6;
            break;
        case DLT860_DBPOS:
            childData->present = DataDefinition_PR_dbpos;
            childData->choice.bit_string = 2;
            break;
        case DLT860_TCMD:
            childData->present = DataDefinition_PR_tcmd;
            childData->choice.bit_string = 2;
            break;
        default:
            break;
        }
        return childData;
    }
        break;
    default:
        break;
    }

    return nullptr;
}

DataDefinition_t *findModelNodeDefine(GspModelNode *node, int depth, const string &fc, const vector<string> &dataVec, 
                        const string &ldName, const string &prefix)
{
    if(depth == dataVec.size())
    {
        auto data = new DataDefinition_t();
        memset(data, 0, sizeof(*data));
        data->present = DataDefinition_PR_structure;
        while(node)
        {
            auto item = fillModelNodeDefine(node, fc, ldName, prefix);
            if(item)
            {
                //                ASN_SEQUENCE_ADD(data->choice.structure, )
                auto *member = new DataDefinition__structure__Member();
                memset(member, 0, sizeof(DataDefinition__structure__Member));
                OCTET_STRING_fromString(&member->name, node->name);
                member->type = item;
                if(fc.empty())
                {

                }
                ASN_SEQUENCE_ADD(&data->choice.structure, member);
            }
            node = node->sibling;
        }
        
        return data;
    }

    while(node)
    {
        if(dataVec[depth].compare(node->name) == 0)
        {
            depth++;
            return findModelNodeDefine(node->firstChild, depth, fc, dataVec, ldName, prefix);
        }
        node = node->sibling;
    }
    return nullptr;
}

void *GspServerData::handleGetDataDefinition(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetDataDefinitionRequestPDU_t*>(requestData);
    auto response = createAsnResponse<GetDataDefinitionResponsePDU_t>();
    response->moreFollows = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
    *response->moreFollows = false;
    auto mapping = static_cast<GspMmsMapping*>(self->server->connectionHandlerParameter);

    for(int i = 0; i < request->data.list.count; ++i)
    {
        auto item = request->data.list.array[i];
        string refer = (const char *)item->reference.buf;
        string fc;
        if(item->fc)
        {
            fc = (const char *)item->fc->buf;
            if(fc == "XX")
            {
                fc = "";
            }
        }
        
        string ldName;
        string itemId;
        splitDomainAndItemId(refer, ldName, itemId);

        auto model = GspMmsMapping_getIedModelByDomainName(mapping, ldName);
        if (!model)
        {
            ASN_STRUCT_FREE(asn_DEF_GetDataDefinitionResponsePDU, response);
            throw invalid_argument(fmt::format("没有找到[{}]对应的模型", ldName));
        }

        auto modelNode = GspIedModel_getModelNodeByReference(model, refer.c_str(), fc.data());
        if (!modelNode)
        {
            ASN_STRUCT_FREE(asn_DEF_GetDataDefinitionResponsePDU, response);
            throw invalid_argument(fmt::format("没有找到[{}]对应的节点", ldName));
        }

        fillDataDefine(modelNode, response, "", fc, "");

    }
    return response;
}

int
GspServer_handleSetDataValues(GspMmsServerConnection self,
                              GspByteBuffer *request,
                              GspByteBuffer *response)
{
    SetDataValuesRequestPDU_t *sourceData = nullptr;
    SetDataValuesErrorPDU_t error = ServiceError_no_error;

    try {
        auto destVal = aper_decode_complete(NULL,
                                            &asn_DEF_SetDataValuesRequestPDU,
                                            (void **)&sourceData,
                                            request->buffer,
                                            request->size);

        if(destVal.code != RC_OK)
        {
            NLOG_ERROR("解码set data values 失败!\n");
            error = ServiceError_failed_due_to_communications_constraint;
            throw exception();
        }

        SetDataValuesResponsePDU_t respData;
        memset(&respData, 0, sizeof (respData));
        for(int i = 0; i < sourceData->data.list.count; ++i)
        {
            //mmsServer_setValue()
            ServiceError_t *data = nullptr;// setDataByReference();
            ASN_SEQUENCE_ADD(&respData.result, data);
        }
        IsoConnection_sendGspResp(self->isoConnection, response);
        ASN_STRUCT_FREE(asn_DEF_SetDataValuesResponsePDU, sourceData);
        return 0;
    }  catch (const exception &ex) {
        ASN_STRUCT_FREE(asn_DEF_SetDataValuesRequestPDU, sourceData);
        GspServer_encodeStructToBuffer(&asn_DEF_SetDataValuesErrorPDU, &error, response);
        IsoConnection_sendGspError(self->isoConnection, response);
        return -1;
    }
}
