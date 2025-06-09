/*
 * 在线读模型
 */

#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "gsp_hal_thread.h"
#include "gsp_lib_memory.h"
#include "../config/example_config.h"


int main(int argc, char** argv) {

    char* hostname;
    int tcpPort = PORT;

    if (argc > 1)
        hostname = argv[1];
    else
        hostname = HOSTNAME;

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

    // 获取数据模型
    GspLinkedList serverList = Gsp_IedConnection_GetServerDirectory(con, &error);

    // 打印在线模型
    if(serverList){
        for(auto& serverItem: *serverList){
            std::string serverStr(static_cast<char*>(serverItem));
            printf("server dir: %s \n", serverStr.data());

            // 逻辑设备节点
            GspLinkedList ldList = Gsp_IedConnection_GetLogicDeviceDirectory(con, &error, serverStr.data());
            for(auto& ldItem: *ldList){
                std::string ldItemStr(static_cast<char*>(ldItem));
                printf("ld: %s \n", ldItemStr.data());

                // 获取数据集
                GspLinkedList dsList = Gsp_IedConnection_GetLogicNodeDirectory(con, &error, GSP_ACSIClass_data_set, std::string(serverStr+"/"+ldItemStr).data());
                for(auto &dsItem: *dsList){
                    std::string dsNameStr(static_cast<char*>(dsItem));
                    printf("dsname: %s \n", dsNameStr.data());
                }
            }
        }
    }

    // 中止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 销毁链接
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);
}


