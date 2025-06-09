#include "mms_server_internal.h"
#include "iso_server_private.h"
#include <stdio.h>
#include <exception>
#include "asn_inc.h"
#include "mms_server_func.h"
#include "nlogging.h"

void *GspServerAssociate::handleRelease(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<ReleaseRequestPDU_t*>(requestData);
    auto respData = (ReleaseResponsePDU_t*)calloc(1, sizeof(ReleaseResponsePDU_t));
    OCTET_STRING_new_fromBuf(
                &asn_DEF_OCTET_STRING,
                (const char *)request->associationId.buf,
                request->associationId.size
                );
    respData->serviceError = ServiceError_no_error;
    return respData;
}

void *GspServerAssociate::handleAssociateNegotiate(GspMmsServerConnection self,  void *requestData)
{
    auto request = static_cast<AssociateNegotiateRequestPDU_t*>(requestData);
    NLOG_DEBUG("associate decode {}, {}, {}", request->asduSize, request->apduSize, request->protocolVersion);


    GspMmsServerConnection_setApduSize(self, CONFIG_MMS_MAXIMUM_APDU_SIZE);
    GspMmsServerConnection_setAsduSize(self, CONFIG_MMS_MAXIMUM_ASDU_SIZE);

    // 回应
    auto rData = createAsnResponse<AssociateNegotiateResponsePDU_t>();

    rData->apduSize = CONFIG_MMS_MAXIMUM_APDU_SIZE;
    rData->asduSize = CONFIG_MMS_MAXIMUM_ASDU_SIZE;
    rData->protocolVersion = request->protocolVersion;
    OCTET_STRING_fromString(&rData->modelVersion, "V1.0.0");
    return rData;
}

void *GspServerAssociate::handleAssociate(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<AssociateRequestPDU_t*>(requestData);
    VisibleString129_t *apRef = request->serverAccessPointReference;
    if(apRef != NULL) {
        NLOG_DEBUG("关联解码成功，指定AP为 {}", apRef->buf);
    }

    // 获取连接ID
    int connectionId = GspIsoServer_getConnectionId(self->server->isoServer, self->isoConnection);

    // create response
    auto respData = createAsnResponse<AssociateResponsePDU_t>();
    auto id = to_string(connectionId);
    
    OCTET_STRING_fromString(&respData->associationId, id.c_str());
    return respData;
}

void *GspServerAssociate::handleAbort(GspMmsServerConnection self, void *requestData)
{
    //GspIsoServer_closeConnection(self->server->isoServer, self->isoConnection);
    return nullptr;
}
