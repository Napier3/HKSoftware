#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "gsp_hal_thread.h"
#include "gsp_lib_memory.h"
#include "../config/example_config.h"
#include <string>
#include <vector>

/**
 * 获取指定refs串的一个值或者多个值。
 * refs 可以是一个DO也可以是DA
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

    // 参数列表
    std::vector<std::string> refsList = {
        "PL1001PROT/LLN0.FuncEna1",
        "PL1001PROT/LPHD1.PhyNam"
    };

    // 请求参数
    for(int index=0; index < 2; ++index){
        RefsFC dataRefs = (RefsFC)GspMemory_calloc(1, sizeof(sRefsFc));

        // fc
        dataRefs->fc = (char*)GspMemory_calloc(3, sizeof(char));
        memcpy((char*)dataRefs->fc, "XX", 2);

        // refs
        dataRefs->objRefs = (char*)GspMemory_calloc(refsList[index].size()+1, sizeof(char));
        memcpy((char*)dataRefs->objRefs, refsList[index].data(), refsList[index].size());

        GspLinkedList_add(requestList, dataRefs);
    }

    // 获取数据定义
    GspLinkedList dataDefiniaionList = Gsp_IedConnection_GetDataDefinition(con, &error, requestList);
    if(!dataDefiniaionList){

        // 获取数据失败处理
        printf("获取数据失败 \n");

        // 释放内存
        GspLinkedList_destroyStatic(requestList);

        // 释放内存
        GspLinkedList_destroyStatic(dataDefiniaionList);

        return -1;
    }

    // 调试信息
    printf("**************************** 读数据定义应用层打印 ******************************* \n");
    // 解析并打印内容信息
    for(int index=0; index < GspLinkedList_size(dataDefiniaionList); ++index)
    {
        // 获取元素值
        void* item = GspLinkedList_get(dataDefiniaionList, index);
        GetDataDefinitionResponsePDU_t* dataDefinitionInfo = static_cast<GetDataDefinitionResponsePDU_t*>(item);

        // 打印信息
    }

    // 获取数据值
    GspLinkedList dataValueList = Gsp_IedConnection_GetDataValues(con, &error, requestList);
    if(!dataValueList){

        // 获取数据失败处理
        printf("获取数据失败 \n");

        // 释放内存
        GspLinkedList_destroyStatic(requestList);

        // 释放内存
        GspLinkedList_destroyStatic(dataValueList);

        return -1;
    }

    // 调试信息
    printf("**************************** 读值应用层打印 ******************************* \n");

    // 解析并打印内容信息
    for(int index=0; index < GspLinkedList_size(dataValueList); ++index)
    {
        // 获取元素值
        void* item = GspLinkedList_get(dataValueList, index);
        Data* dataInfo = static_cast<Data*>(item);
        if(dataInfo){
            // 打印调试信息
            printf("数据类型%i\n", GspMmsValue_getType(dataInfo));
            GspMmsValue_printToBuffer(dataInfo);

            if(GspMmsValue_getType(dataInfo) == Data_PR_float32){
                printf("数据值: %f \n", GspMmsValue_toFloat(dataInfo));
            }
        } else {
            printf("解析结果为空\n");
        }

        // 释放元素值
        GspMmsValue_delete(dataInfo);
    }

    // 释放数据内存
    GspLinkedList_destroyStatic(dataValueList);

    // 释放参数内存
    for(auto& item : *requestList){
        RefsFC dataRequestItem = (RefsFC)item;
        GspMemory_free((char*)dataRequestItem->fc);
        GspMemory_free((char*)dataRequestItem->objRefs);
        GspMemory_free(dataRequestItem);
    }
    GspLinkedList_destroyStatic(requestList);


    // 终止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 销毁链接
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);

}


