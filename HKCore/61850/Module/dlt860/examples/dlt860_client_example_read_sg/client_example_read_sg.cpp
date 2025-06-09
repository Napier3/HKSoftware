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

    // 选择激活定制组
    uint8_t testDemoNum = 1;
    const char* sgcbRefs = "P_L1111A6PROT/LLN0.SGCB";
    bool ret = Gsp_IedConnection_SelectActiveSG(con, &error, sgcbRefs, testDemoNum);

    // 调试信息
    if(ret){
        printf("****************** 选择激活定值区成功，切换到 %d 区。\n", testDemoNum);
    } else {
        printf("****************** 选择激活定值区失败，切换到 %d 区。失败, 错误代码: %d \n", testDemoNum, error);
    }

    // 读定值控制块的值
    GspLinkedList retList = Gsp_IedConnection_GetSGCBValues(con, &error, sgcbRefs);

    // 打印调试
    if(retList){
        GetSGCBValuesResponsePDU_t* sgcbValue = static_cast<GetSGCBValuesResponsePDU_t*>(retList->front());
        for(int index=0; index < sgcbValue->sgcb.list.count; ++index){
            // 读取成员信息
            GetSGCBValuesResponsePDU__sgcb__Member* sgcbItem = sgcbValue->sgcb.list.array[index];

            // 打印测试
            if(sgcbItem->present != GetSGCBValuesResponsePDU__sgcb__Member_PR_value){
                printf("该定制控制块的值有错误, 错误信息: %ld \n", sgcbItem->choice.error);
            } else {
                printf(" ****************** 定值控制块信息调试: %s ****************** \n", sgcbRefs);
                printf("激活定值组: %ld \n", sgcbItem->choice.value.actSG);
                printf("编辑定制组: %ld \n", sgcbItem->choice.value.editSG);
                printf("定制组数量: %ld \n", sgcbItem->choice.value.numOfSG);
                if(sgcbItem->choice.value.resvTms){
                    printf("resvTms: %ld \n", *sgcbItem->choice.value.resvTms);
                }
            }
        }

        // 内存释放
        Gsp_FreeSGCBValues(sgcbValue);

    } else {
        printf("没有读取到定制控制块的值，错误代码: %d \n", error);
    }

    // 释放内存
    GspLinkedList_destroyStatic(retList);

    // 终止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 销毁链接
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);
}


