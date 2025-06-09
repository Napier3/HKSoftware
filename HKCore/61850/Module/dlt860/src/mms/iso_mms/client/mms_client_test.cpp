#include "cotp.h"
#include <stdio.h>
#include "mms_client_internal.h"

void mmsClient_createTestRequest(GspMmsConnection self){

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_Test);

    // 没有asdu
}

void mmsClient_createTestResponse(GspMmsConnection self){
    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 1, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_Test);

    // 没有asdu
}
