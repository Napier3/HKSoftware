#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "gsp_hal_thread.h"
#include "gsp_lib_memory.h"
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

    // 参数信息
    const char* testLn = "PL1001LD0/LLN0.dsWarning";

    // 调试信息
    printf("**************************** 读数据集目录协议层打印 ******************************* \n");

    GspLinkedList datasetDirectoryList = Gsp_IedConnection_GetDataSetDirectory(con, &error, testLn);
    if(!datasetDirectoryList){

        // 获取数据失败处理
        printf("获取数据集目录失败 \n");

        // 释放链接
        Gsp_IedConnection_Release(con, &error, associateID);

        // 释放内存
        GspLinkedList_destroyStatic(datasetDirectoryList);


        // 销毁链接
        Gsp_IedConnection_Destroy(con);
        Gsp_IedConnection_FreeAssociateID(associateID);
        return -1;
    }

    // 调试信息
    printf("**************************** 读数据集目录应用层打印 ******************************* \n");

    // 解析并打印内容信息
    for(int index=0; index < GspLinkedList_size(datasetDirectoryList); ++index)
    {
        // 获取元素值
        void* item = GspLinkedList_get(datasetDirectoryList, index);
        RefsFC dataInfo = static_cast<RefsFC>(item);
        if(dataInfo){
            // 打印调试信息
            printf("REFS: %s \n", dataInfo->objRefs);
            printf("FC: %s \n", dataInfo->fc);
        } else {
            printf("解析结果为空\n");
        }
    }

    // 释放数据内存
    Gsp_GetDataSetDirectory_Destory(datasetDirectoryList);

    // 调试信息
    printf("**************************** 读数据集值协议层打印 ******************************* \n");

    GspLinkedList dataValueList = Gsp_IedConnection_GetDataSetValues(con, &error, testLn);
    if(!dataValueList){

        // 获取数据失败处理
        printf("获取数据集值失败 \n");

        // 释放链接
        Gsp_IedConnection_Release(con, &error, associateID);

        // 释放内存
        Gsp_GetDataSetValues_Destory(dataValueList);

        // 销毁链接
        Gsp_IedConnection_Destroy(con);
        Gsp_IedConnection_FreeAssociateID(associateID);
        return -1;
    }

    // 调试信息
    printf("**************************** 读数据集值应用层打印 ******************************* \n");

    // 解析并打印内容信息
    for(int index=0; index < GspLinkedList_size(dataValueList); ++index)
    {
        // 获取元素值
        void* item = GspLinkedList_get(dataValueList, index);
        GspMmsValue* dataInfo = static_cast<GspMmsValue*>(item);
        if(dataInfo){
            // 打印调试信息
            GspMmsValue_printToBuffer(dataInfo);

        } else {
            printf("解析结果为空\n");
        }
    }

    // 释放内存
    Gsp_GetDataSetValues_Destory(dataValueList);

    // 终止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 释放链接
    Gsp_IedConnection_Release(con, &error, associateID);

    // 销毁链接
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);
}


