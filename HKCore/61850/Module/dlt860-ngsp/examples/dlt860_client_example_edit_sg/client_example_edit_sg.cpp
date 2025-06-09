#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "gsp_hal_thread.h"
#include "gsp_lib_memory.h"
#include "../config/example_config.h"
#include <string>
#include <vector>


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

    // 定值修改业务流 001 -> 选择编辑定值组
    uint8_t testDemoNum = 2;
    const char* testSgcbRefs = "P_L1011XPROT/LLN0.SGCB";
    bool ret = Gsp_IedConnection_SelectEditSG(con, &error, testSgcbRefs, testDemoNum);

    // 调试信息
    if(ret){
        printf("****************** 选择编辑定值区成功，切换到 %d 区。\n", testDemoNum);
    } else {
        printf("****************** 选择编辑定值区失败，切换到 %d 区。失败, 错误代码: %d \n", testDemoNum, error);
    }

    // 读定值控制块的值
    std::vector<std::string> testSGRefList = {
        "P_L1011XPROT/PVOC1.StrValSG.setMag.f",
        "P_L1011XPROT/RecRREC1.SPRecTmms.setVal",
        "P_L1011XPROT/ZerPTOC2.Enable.setVal"
    };

    GspLinkedList demoSgRefList = GspLinkedList_create();

    // 定值01
    RefsFC tmpRefs01 = (RefsFC)GspMemory_calloc(1, sizeof(struct sRefsFc));
    tmpRefs01->fc = "SE";
    tmpRefs01->objRefs = testSGRefList[0].data();
    GspLinkedList_add(demoSgRefList, tmpRefs01);

    // 定值02
    RefsFC tmpRefs02 = (RefsFC)GspMemory_calloc(1, sizeof(struct sRefsFc));
    tmpRefs02->fc = "SE";
    tmpRefs02->objRefs = testSGRefList[1].data();
    GspLinkedList_add(demoSgRefList, tmpRefs02);

    // 定值03
    RefsFC tmpRefs03 = (RefsFC)GspMemory_calloc(1, sizeof(struct sRefsFc));
    tmpRefs03->fc = "SE";
    tmpRefs03->objRefs = testSGRefList[2].data();
    GspLinkedList_add(demoSgRefList, tmpRefs03);

    // 定值修改业务流 002 -> 读定值操作
    GspLinkedList sgvalues = Gsp_IedConnection_GetEditSGValue(con, &error, demoSgRefList);

    // 打印测试
    if(sgvalues){
        for(auto &item : *sgvalues)
        {
            GetEditSGValueResponsePDU_t* tmpSgItem = (GetEditSGValueResponsePDU_t*)item;
            for (int index=0; index<tmpSgItem->value.list.count; ++index) {

                // 获取定值元素
                GspMmsValue* sgValueItem = tmpSgItem->value.list.array[index];
                Data_PR dataType = GspMmsValue_getType(sgValueItem);

                // 打印测试
                switch (dataType) {
                case Data_PR_boolean:{
                    bool tmpValue = GspMmsValue_getBoolean(sgValueItem);
                    printf("读取到了 %s 的 bool 类型的定值: %d", testSGRefList[index].data(), tmpValue);
                }
                    break;
                    // TODO 这里需要按照需求打印一些测试东西
                default:
                    printf("该种数据类型的定值, 在测试例子中没有进行解析 \n");
                }
            }

            // 释放定值元素
            Gsp_FreeEditSGValues(tmpSgItem);
        }
    } else {
        printf("获取编辑区定值失败, 没有获取到数据\n");
    }

    // 释放定值列表
    GspLinkedList_destroyStatic(sgvalues);

    // 写定值控制块的值
    GspLinkedList writeSgValues = GspLinkedList_create();

    // 修改 bool 类型的定值
    RefsData sgvalue = (RefsData)GspMemory_calloc(1, sizeof (sRefsData));
    sgvalue->objRefs = testSGRefList[2].data();
    sgvalue->data = GspMmsValue_newBoolean(true);

    GspLinkedList_add(writeSgValues, sgvalue);

    // 定值修改业务流 003 -> 写定值操作
    if(Gsp_IedConnection_SetEditSGValue(con, &error, writeSgValues)){
        printf("写定值成功!! \n");
    } else {
        printf("写定值失败!! \n");
    }

    // 释放写定值参数内存
    for(auto& item: *writeSgValues){
        RefsData innerItem = (RefsData)item;

        // refs 为引用的常量字符串此处不用释放

        // data
        GspMmsValue_delete(innerItem->data);

        // value 本身
        GspMemory_free(innerItem);
    }
    GspLinkedList_destroyStatic(writeSgValues);

    // 定值修改业务流 004 -> 确认定值修改操作
    if(Gsp_IedConnection_ConfirmEditSGValues(con, &error, testSgcbRefs)){
        printf("确认写定值成功!! \n");
    } else {
        printf("确认写定值失败!! \n");
    }

    // 定制参数内存释放
    for(auto& item: *demoSgRefList){
        RefsFC innerItem = (RefsFC)item;
        GspMemory_free(innerItem);
    }
    GspLinkedList_destroyStatic(demoSgRefList);

    // 中止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 销毁链接
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);
}


