#include "mms_server_func.h"
#include "nlogging.h"

map<string, map<string, RpcInfo *> > GspServerRpc::interfaceMethodMap;

void* GspServerRpc::handleGetRpcInterfaceDirectory(GspMmsServerConnection self, void* request)
{
	auto resp = createAsnResponse<GetRpcInterfaceDirectoryResponsePDU_t>();
	auto requestData = static_cast<GetRpcInterfaceDirectoryRequestPDU_t *>(request);
	string referAfter;
	if(requestData->referenceAfter)
	{
		referAfter = (const char *)requestData->referenceAfter->buf;
	}

	auto it = interfaceMethodMap.begin();
	
	if(!referAfter.empty())
	{
		it = interfaceMethodMap.find(referAfter);
		if(it == interfaceMethodMap.end())
		{
			resp->moreFollows = (BOOLEAN_t*)calloc(1, sizeof(BOOLEAN_t));
			*resp->moreFollows = 0;
			return resp;
		}
		it++;
	}

	int count = 0;
	resp->moreFollows = (BOOLEAN_t *)calloc(sizeof(BOOLEAN_t), 1);

	for(; it != interfaceMethodMap.end(); ++it)
	{
		auto item =	OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, it->first.c_str(), -1);
		ASN_SEQUENCE_ADD(&resp->reference.list, item);
		count += 1;
		if(count == 100)
		{
			*resp->moreFollows = 1;
			break;
		}
	}
	return resp;
}
void* GspServerRpc::handleGetRpcMethodDirectory(GspMmsServerConnection self, void* requestData)
{
	auto request = static_cast<GetRpcMethodDirectoryRequestPDU_t *>(requestData);
	auto resp = createAsnResponse<GetRpcMethodDirectoryResponsePDU_t>();

    string interface = (const char *)request->interface->buf;
	if(!interfaceMethodMap.count(interface))
	{
		throw invalid_argument(fmt::format("rpc interface [{}] 不存在", interface));
	}

	auto methodMap = interfaceMethodMap[interface];
	
	string referAfter;
	if(request->referenceAfter)
	{
		referAfter = (const char *)request->referenceAfter->buf;
	}
	auto it = methodMap.begin();
	if(!referAfter.empty())
	{
		it = methodMap.find(referAfter);
		if(it == methodMap.end())
		{
			resp->moreFollows = (BOOLEAN_t*)calloc(1, sizeof(BOOLEAN_t));
			return resp;
		}
		it++;
	}

	int count = 0;
	resp->moreFollows = (BOOLEAN_t*)calloc(1, sizeof(BOOLEAN_t));

	for(; it != methodMap.end(); ++it)
	{
		auto item =	OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, it->first.c_str(), -1);
		ASN_SEQUENCE_ADD(&resp->reference.list, item);
		count += 1;
		if(count == 100)
		{
			*resp->moreFollows = 1;
			break;
		}
	}

	return resp;
}
void* GspServerRpc::handleGetRpcInterfaceDefinition(GspMmsServerConnection self, void* requestData)
{
	auto request = static_cast<GetRpcInterfaceDefinitionRequestPDU_t *>(requestData);
	auto resp = createAsnResponse<GetRpcInterfaceDefinitionResponsePDU_t>();
	
	string interface = (const char *)request->interface.buf;
	if(!interfaceMethodMap.count(interface))
	{
		throw invalid_argument(fmt::format("rpc interface [{}] 不存在", interface));
	}

	auto methodMap = interfaceMethodMap[(const char *)request->interface.buf];
	
	string referAfter;
	if(request->referenceAfter)
	{
		referAfter = (const char *)request->referenceAfter->buf;
	}
	auto it = methodMap.begin();
	if(!referAfter.empty())
	{
		it = methodMap.find(referAfter);
		if(it == methodMap.end())
		{
			resp->moreFollows = (BOOLEAN_t*)calloc(1, sizeof(BOOLEAN_t));
			return resp;
		}
		it++;
	}

	int count = 0;
	resp->moreFollows = (BOOLEAN_t*)calloc(1, sizeof(BOOLEAN_t));

	for(; it != methodMap.end(); ++it)
	{
		auto &rpcInfo = it->second;
		auto method = (GetRpcInterfaceDefinitionResponsePDU__method__Member *)calloc(1, sizeof(GetRpcInterfaceDefinitionResponsePDU__method__Member));

		OCTET_STRING_fromString(&method->name, rpcInfo->name.c_str());
		memcpy(&method->request, &rpcInfo->requestDefine, sizeof(method->request));
		memcpy(&method->response, &rpcInfo->responseDefine, sizeof(method->response));
		method->timeout = rpcInfo->timeout;
		method->version = rpcInfo->timeout;

		ASN_SEQUENCE_ADD(&resp->method.list, method);
		count += 1;
		if(count == 20)
		{
			*resp->moreFollows = 1;
			break;
		}
	}

	resp->moreFollows = (BOOLEAN_t*)calloc(1, sizeof(BOOLEAN_t));
	*resp->moreFollows = 0;
	return resp;
}
void* GspServerRpc::handleGetRpcMethodDefinition(GspMmsServerConnection self, void* requestData)
{
	auto request = static_cast<GetRpcMethodDefinitionRequestPDU_t *>(requestData);
	auto resp = createAsnResponse<GetRpcMethodDefinitionResponsePDU_t>();
	resp->moreFollows = (BOOLEAN_t*)calloc(1, sizeof(BOOLEAN_t));

	int count = 0;
	for(int i = 0; i < request->reference.list.count; ++i)
	{
		auto refer = request->reference.list.array[i];
		string sRefer = (const char *)refer->buf;
		
		string interface = sRefer.substr(0, sRefer.find("."));
		string methodName = sRefer.substr(sRefer.find(".") + 1);
		auto respItem = (GetRpcMethodDefinitionResponsePDU__reference__Member *)calloc(1, sizeof(GetRpcMethodDefinitionResponsePDU__reference__Member));

		if(!interfaceMethodMap.count(interface) || !interfaceMethodMap[interface].count(methodName))
		{
			respItem->present = GetRpcMethodDefinitionResponsePDU__reference__Member_PR_error;
			respItem->choice.error = ServiceError_instance_not_available;
		}
		else
		{
			auto rpcInfo = interfaceMethodMap[interface][methodName];
			if(rpcInfo)
			{
				auto method = &respItem->choice.method;
				respItem->present = GetRpcMethodDefinitionResponsePDU__reference__Member_PR_method;
				memcpy(&method->request, &rpcInfo->requestDefine, sizeof(method->request));
				memcpy(&method->response, &rpcInfo->responseDefine, sizeof(method->response));
				method->timeout = rpcInfo->timeout;
				method->version = rpcInfo->timeout;
			}
			else
			{
				respItem->present = GetRpcMethodDefinitionResponsePDU__reference__Member_PR_error;
				respItem->choice.error = ServiceError_instance_not_available;
			}
		}

		ASN_SEQUENCE_ADD(&resp->reference.list, respItem);
		count += 1;
		if(count == 20)
		{
			*resp->moreFollows = 1;
			break;
		}
	}

	*resp->moreFollows = 0;
	return resp;
}
void* GspServerRpc::handleRpcCall(GspMmsServerConnection self, void* requestData)
{
	auto resp = createAsnResponse<RpcCallResponsePDU_t>();
	auto request = static_cast<RpcCallRequestPDU_t *>(requestData);
	string sRefer = (const char *)request->method.buf;
	
	string interface = sRefer.substr(0, sRefer.find("."));
	string methodName = sRefer.substr(sRefer.find(".") + 1);

	if(!interfaceMethodMap.count(interface))
	{
		throw invalid_argument(fmt::format("rpc interface [{}] 不存在", interface));
	}

	if(!interfaceMethodMap[interface].count(methodName))
	{
		throw invalid_argument(fmt::format("rpc method [{}.{}] 不存在", interface, methodName));
	}

	auto rpcInfo = interfaceMethodMap[interface][methodName];
	if(rpcInfo)
	{
		string nextCallId;
		
		if(request->req.present == RpcCallRequestPDU__req_PR_reqData)
		{
			auto data = rpcInfo->func(&request->req.choice.reqData, nextCallId);
			if(!nextCallId.empty())
			{
				resp->nextCallID = OCTET_STRING_new_fromBuf(&asn_DEF_OCTET_STRING, nextCallId.c_str(), -1);
			}
			GspMmsValue_update(&resp->rspData, data);
		}
		else
		{
			nextCallId = (const char *)request->req.choice.callID.buf;
			auto data = rpcInfo->func(NULL, nextCallId);
			if(!nextCallId.empty())
			{
				resp->nextCallID = OCTET_STRING_new_fromBuf(&asn_DEF_OCTET_STRING, nextCallId.c_str(), -1);
			}
			GspMmsValue_update(&resp->rspData, data);
		}
	}

	return resp;
}

void GspServerRpc::addRpcCall(const string &interface, const string &method, RpcInfo *rpcInfo)
{
	interfaceMethodMap[interface][method] = rpcInfo;
}

void GspServerRpc::delRpcCall(const string &interface, const string &method)
{
	auto &methodMap = interfaceMethodMap[interface];
	methodMap.erase(method);
}