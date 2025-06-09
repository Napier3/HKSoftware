#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "gsp_hal_thread.h"
#include "conversions.h"
#include "gsp_lib_memory.h"
#include "../config/example_config.h"

/************************************************
 * 链接测试用例
 * v1.0
 ************************************************/

int main(int argc, char** argv) {

    // 目标设备
    char* hostname;

    // 目标IP
    int tcpPort = PORT;

    // 配置的IP
    if (argc > 1) {
        hostname = argv[1];
    } else {
        hostname = HOSTNAME;
    }

    // 配置的端口
    if (argc > 2) {
        tcpPort = atoi(argv[2]);
    }

    // 创建链接
    GspIedClientError error;
    GspIedConnection con = Gsp_IedConnection_Create();

    // 链接到服务器
    Gsp_IedConnection_Connect(con, &error, hostname, tcpPort);
    if (error == GSP_IED_ERROR_OK) {
        printf("链接到服务端成功:%s\n", hostname);
    } else {
        printf("链接到服务端失败:%s\n", hostname);

        // 销毁链接
        Gsp_IedConnection_Destroy(con);
        return -1;
    }

    // 发生关联
    const char* associateID = Gsp_IedConnection_Associate(con, &error, "S1");

    // 安装关闭回调
    Gsp_IedConnection_InstallConnectionClosedHandler(con, [](void* parameter, GspIedConnection connection){
        printf("链接关闭了\n");
    },
    nullptr);

    // 维护链接20秒
    printf("链接已经建立, 现在维持链接一段时间\n");
    int count = 0;
    while (1) {
        GspThread_sleep(10);
        if(count++ > 2000){
            break;
        }
    }

    // 释放链接
    Gsp_IedConnection_Release(con, &error, associateID);

    // 中止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 销毁链接
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);
}

