#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "gsp_hal_thread.h"
#include "gsp_lib_memory.h"
#include "../config/example_config.h"
#include <string>
#include <vector>

/**
 * 写值操作
 */
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

    // 获取单点或者多点数据
    GspLinkedList requestList = GspLinkedList_create();

    // 待写的参数列表
    std::vector<std::string> refsList = {"PL1001PROT/LLN0.DevName.setVal"};

    // 请求参数
    for(int index=0; index < refsList.size(); ++index){
        RefsFcData dataRefs = (RefsFcData)GspMemory_calloc(1, sizeof(sRefsFcData));

        // fc
        dataRefs->fc = (char*)GspMemory_calloc(3, sizeof(char));
        memcpy((char*)dataRefs->fc, "SP", 2);

        // refs
        dataRefs->objRefs = (char*)GspMemory_calloc(refsList[index].size() + 1, sizeof(char));
        memcpy((char*)dataRefs->objRefs, refsList[index].data(), refsList[index].size());

        // data
        dataRefs->data = GspMmsValue_newBoolean(true);

        // 添加到列表
        GspLinkedList_add(requestList, dataRefs);
    }

    // 请求数据
    GspLinkedList resultList = Gsp_IedConnection_SetDataValues(con, &error, requestList);
    if(!resultList){

        // 设置数据失败处理
        printf("设置数据失败 \n");

        // 释放内存
        GspLinkedList_destroyStatic(requestList);

        // 释放内存
        GspLinkedList_destroyStatic(resultList);

        return -1;
    }

    // 调试信息
    printf("**************************** 写值应用层打印 ******************************* \n");

    // 解析并打印内容信息
    for(int index=0; index < GspLinkedList_size(resultList); ++index)
    {
        // 获取元素值
        void* item = GspLinkedList_get(resultList, index);
        ServiceError_t* retCode = static_cast<ServiceError_t*>(item);
        if(retCode){
            // 打印调试信息
            printf("操作结果%li\n", *retCode);
        } else {
            printf("解析结果为空\n");
        }
    }

    // 释放数据内存
    GspLinkedList_destroyStatic(resultList);

    // 释放参数内存
    for(auto& item : *requestList){
        RefsFcData dataRequestItem = (RefsFcData)item;
        GspMemory_free((char*)dataRequestItem->fc);
        GspMemory_free((char*)dataRequestItem->objRefs);
        GspMemory_free(dataRequestItem);
        GspMmsValue_delete(dataRequestItem->data);
    }
    GspLinkedList_destroyStatic(requestList);


    // 终止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 销毁链接
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);

}


