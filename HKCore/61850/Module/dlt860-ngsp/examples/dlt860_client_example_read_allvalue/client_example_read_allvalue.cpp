#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "gsp_hal_thread.h"
#include "../config/example_config.h"


int main(int argc, char** argv) {

    char* hostname;
    int tcpPort = PORT;

    if (argc > 1) {
        hostname = argv[1];
    } else {
        hostname = HOSTNAME;
    }

    if (argc > 2)
        tcpPort = atoi(argv[2]);

    // 创建链接
    GspIedClientError error;
    GspIedConnection con = Gsp_IedConnection_Create();

    // 链接到服务器
    Gsp_IedConnection_Connect(con, &error, hostname, tcpPort);
    if (error == GSP_IED_ERROR_OK) {
        printf("链接到服务端成功\n");
    } else {
        printf("链接到服务端失败\n");
        // 销毁链接
        Gsp_IedConnection_Destroy(con);
        return -1;
    }

    // 发生关联
    const char* associateID = Gsp_IedConnection_Associate(con, &error, "S1");

    // 获取 所有数据的ref 和 值
    GspLinkedList allDataSetValue = Gsp_IedConnection_GetAllDataValues(con, &error, DLT860_FC_ALL, "P_L1011XLD0/LTSM1", LNREFERENCE);

    // 解析并打印
    if(allDataSetValue){
        for(auto &item : *allDataSetValue)
        {
            GspClientDataSet dataItem = (GspClientDataSet)item;

            printf("参引串：%s \n", Gsp_ClientDataSet_GetReference(dataItem));
            GspMmsValue_printToBuffer(Gsp_ClientDataSet_GetValues(dataItem));

            // 使用者一定要自己释放内存
            Gsp_ClientDataSet_Destroy(dataItem);
        }
    }

    // 释放内存
    GspLinkedList_destroyStatic(allDataSetValue);

    // 终止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 销毁链接
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);
}


