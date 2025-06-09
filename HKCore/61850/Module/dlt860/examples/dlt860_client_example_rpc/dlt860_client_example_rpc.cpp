#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "gsp_hal_thread.h"
#include "conversions.h"
#include "gsp_lib_memory.h"
#include "../config/example_config.h"

/************************************************
 * RPC测试帧用例
 * v 1.0
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

    // 获取 rpc 接口名字信息
    GspLinkedList interfaceList = Gsp_IedConnection_GetRpcInterfaceDirectory(con, &error);

    // 获取 rpc 方法信息
    for (auto &interfaceItem : *interfaceList) {
        // 打印接口名字信息
        printf("interface: %s \n", interfaceItem);

        // 获取 rpc 接口定义信息
        GspLinkedList interfaceDefinitionList = Gsp_IedConnection_GetRpcInterfaceDefinition(con, &error, (char*)interfaceItem);
        for(auto &interfaceDefinationItem: *interfaceDefinitionList){
            // 获取接口定义信息
            GetRpcInterfaceDefinitionResponsePDU_t* rpcdItem = (GetRpcInterfaceDefinitionResponsePDU_t*)interfaceDefinationItem;

            // 打印接口定义信息
            for(int index=0; index < rpcdItem->method.list.count; ++index){
                GetRpcInterfaceDefinitionResponsePDU__method__Member* rpcdInnerItem = (GetRpcInterfaceDefinitionResponsePDU__method__Member*)rpcdItem->method.list.array[index];
                // name
                printf("\tname: %s \n", rpcdInnerItem->name.buf);
                // version
                printf("\tversion: %lu \n", rpcdInnerItem->version);
                // timeout
                printf("\ttimeout: %lu \n", rpcdInnerItem->timeout);
                // request（剩余内部信息不在打印，类推即可）
                printf("\trequest->type: %u \n", rpcdInnerItem->request.present);
                // response（剩余内部信息不在打印，类推即可）
                printf("\tresponse->type: %u \n", rpcdInnerItem->response.present);
            }
        }

        // 释放接口定义
        Gsp_IedConnection_FreeRpcInterfaceDefinition(interfaceDefinitionList);

        // 获取方法列表
        GspLinkedList methodList = Gsp_IedConnection_GetRpcMethodDirectory(con, &error, (char*)interfaceItem);

        for (auto &methodItem : *methodList) {
            // 打印方法名字信息
            printf("interface: %s \n", methodItem);

            // 获取 rpc 接口定义信息
            GspLinkedList medthodDefinitionList = Gsp_IedConnection_GetRpcInterfaceDefinition(con, &error, (char*)interfaceItem);
            for(auto &interfaceDefinationItem: *medthodDefinitionList){
                // 获取接口定义信息
                GetRpcInterfaceDefinitionResponsePDU_t* rpcdItem = (GetRpcInterfaceDefinitionResponsePDU_t*)interfaceDefinationItem;

                // 打印接口定义信息
                for(int index=0; index < rpcdItem->method.list.count; ++index){
                    GetRpcInterfaceDefinitionResponsePDU__method__Member* rpcdInnerItem = (GetRpcInterfaceDefinitionResponsePDU__method__Member*)rpcdItem->method.list.array[index];
                    // name
                    printf("\tname: %s \n", rpcdInnerItem->name.buf);
                    // version
                    printf("\tversion: %lu \n", rpcdInnerItem->version);
                    // timeout
                    printf("\ttimeout: %lu \n", rpcdInnerItem->timeout);
                    // request（剩余内部信息不在打印，类推即可）
                    printf("\trequest->type: %u \n", rpcdInnerItem->request.present);
                    // response（剩余内部信息不在打印，类推即可）
                    printf("\tresponse->type: %u \n", rpcdInnerItem->response.present);
                }
            }

            // 释放方法定义
            Gsp_IedConnection_FreeRpcMethodDefinition(medthodDefinitionList);
        }

        // 释放方法信息
        Gsp_IedConnection_FreeRpcMethodDirectory(methodList);
    }

    // RPC调用（在上述定义中随便找一个接口进行调用）
    GspMmsValue* reqParam = GspMmsValue_newVisibleString("test_rpc");
    void* response = Gsp_IedConnection_RPCCall(con, &error, "hello.world", reqParam);

    // 调用结果判断
    if(error == GSP_IED_ERROR_OK){
        // 获取结果
        GspMmsValue* responsePDU = Gsp_RPCCallResPonse_getData(response);

        // 依照数据类型进行获取内部的值，和渎值接口获取出来的值一致(TODO)

        // 释放内存
        Gsp_IedConnection_FreeRPCCallPDU(response);
    } else {
        printf("RPCCall 失败\n");
    }

    // 释放接口信息
    Gsp_IedConnection_FreeRpcInterfaceDirectory(interfaceList);

    // 释放链接
    Gsp_IedConnection_Release(con, &error, associateID);

    // 中止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 销毁链接
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);
}

