#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "gsp_hal_thread.h"
#include "conversions.h"
#include "gsp_lib_memory.h"
#include <string>
#include "string_utilities.h"
#include "../config/example_config.h"

using namespace std;

void reportHandler(void* parameter, void* reportPDU){
    printf("用户层面报告回调! 接受到底层报告: %s\n", static_cast<char*>(parameter));
    if(reportPDU){
        // dataset
        const char* dataSet = Gsp_ClientReport_getDataSetName(reportPDU);
        if(dataSet){
            printf("报告 dataset: %s \n", dataSet);
        }

        // 获取报告 RptID
        const char* rptID = Gsp_ClientReport_getRptId(reportPDU);
        if(rptID){
            printf("报告 RptID: %s \n", rptID);
        }

        // 获取报告时间
        uint64_t reportTimeStamp = Gsp_ClientReport_getReportTime(reportPDU);
        if(reportTimeStamp){
            printf("报告时间: %ld \n", reportTimeStamp);
        }

        // 获取报告数据
        void* reportDataList = Gsp_ClientReport_getDataSetValueList(reportPDU);

        // 获取报告尺寸
        uint32_t reportDataCount = Gsp_ClientReport_getDataSetValuesSize(reportDataList);
        printf("报告中数据的条目个数: %d \n", reportDataCount);

        // 获取entryid
        EntryID_t* entryID = Gsp_ClientReport_getEntryId(reportPDU);
        if(entryID){
            printf("报告 entryID: %s \n", entryID->buf);
        }

        // 获取报告数据
        for(int index=0; static_cast<unsigned int>(index) < reportDataCount; ++index){

            // 获取报告ID
            uint16_t dataID = Gsp_ClientReport_getDataSetValueID(reportDataList, index);

            // 打印分割
            printf("********************** 报告条目 %d *****************************\n", dataID);

            // 获取报告数据的的refs
            const char* dataItemRefs = Gsp_ClientReport_getDataSetValueRefs(reportDataList, index);
            if(dataItemRefs){
                printf(" %d 报告条目的 refs: %s \n", dataID, dataItemRefs);
            }

            // 获取报告数据的功能约束
            const char* fc = Gsp_ClientReport_getDataSetValueFC(reportDataList, index);
            if(fc){
                printf(" %d 报告条目的 fc: %s \n", dataID, fc);
            }

            // 报告上送原因
            const char* reasonCodeStr = Gsp_ClientReport_getReasonCodeStr(reportDataList, index);
            unsigned reasonCode = Gsp_ClientReport_getReasonCode(reportDataList, index);
            printf(" %d 报告条目的报告上送原因: %s -> %d\n", dataID, reasonCodeStr, reasonCode);

            // 获取报告数据
            GspMmsValue* dataItem = Gsp_ClientReport_getDataSetValue(reportDataList, index);
            if(dataItem){
                printf(" 报告条目的数据类型: %d \n", GspMmsValue_getType(dataItem));

                // 报告数据 一般都是 struct 和 array 类型
                switch (GspMmsValue_getType(dataItem)) {
                case Data_PR_structure:
                {
                    for(int innerIndex=0; static_cast<unsigned int>(innerIndex) < GspMmsValue_getStructSize(dataItem); ++innerIndex){
                        GspMmsValue* innerDataItem = GspMmsValue_getElement(dataItem, innerIndex);
                        // 获取内层数据结构(q)
                        if(GspMmsValue_getType(innerDataItem) == Data_PR_quality){
                            Gsp_BitString_print(&innerDataItem->choice.bit_string);
                        }

                        // 获取内层数据结构(time)
                        if(GspMmsValue_getType(innerDataItem) == Data_PR_utc_time){
                            uint64_t ms = GspMmsValue_getUtcTimeInMs(innerDataItem);
                            printf(" 毫秒: %lu \n", ms);
                        }
                    }
                } break;

                default:
                    printf("报告测试时，这种数据类型没有解析打印,请自行添加\n");
                    break;
                }
            }
        }
    }

    // 释放数据内存
    Gsp_Report_Destory(reportPDU);
}

int main(int argc, char** argv) {

    // 目标设备
    char* hostname;

    // 目标IP
    int tcpPort = PORT;

    // 目标报告
    const char* testReportRefs = "P_L2211CLD0/LLN0.brcbCommStateB01";

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

    // 配置的报告
    if (argc > 3){
        testReportRefs = argv[3];
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

    // 获取报告控制块数据
    BRCBControlBlk currentBrcbControlBlk = Gsp_IedConnection_GetBRCBValues(con, &error, testReportRefs);

    // 错误信息判断
    if(error != GSP_IED_ERROR_OK || currentBrcbControlBlk == nullptr){
        printf("获取报告控制块数据失败,错误代码: %d \n", error);

        // 释放内存
        Gsp_BRCBControlBlk_Destory(currentBrcbControlBlk);

        // 释放链接
        Gsp_IedConnection_Release(con, &error, associateID);

        // 释放关联ID
        Gsp_IedConnection_FreeAssociateID(associateID);

        // 销毁链接
        Gsp_IedConnection_Destroy(con);
        return -1;
    }
    if(currentBrcbControlBlk->brcbControlBlk == nullptr){
        // 释放内存
        Gsp_BRCBControlBlk_Destory(currentBrcbControlBlk);

        // 释放链接
        Gsp_IedConnection_Release(con, &error, associateID);

        // 释放关联ID
        Gsp_IedConnection_FreeAssociateID(associateID);

        // 销毁链接
        Gsp_IedConnection_Destroy(con);
        return -1;
    }

    // 调试信息
    printf("**************************** 获取缓存报告控制块应用层打印 ******************************* \n");

    // 解析并打印内容信息
    if(currentBrcbControlBlk->brcbControlBlk->rptID) {
        printf("报告ID: %s \n", currentBrcbControlBlk->brcbControlBlk->rptID->buf);
    }
    if(currentBrcbControlBlk->brcbControlBlk->rptEna) {
        printf("报告是否启用: %d \n", *currentBrcbControlBlk->brcbControlBlk->rptEna);
    }
    if(currentBrcbControlBlk->brcbControlBlk->datSet) {
        printf("报告 datSet: %s \n", currentBrcbControlBlk->brcbControlBlk->datSet->buf);
    }
    if(currentBrcbControlBlk->brcbControlBlk->optFlds){
        printf("报告 optFlds: ");
        Gsp_BitString_print(currentBrcbControlBlk->brcbControlBlk->optFlds);
    }
    if(currentBrcbControlBlk->brcbControlBlk->bufTm){
        printf("报告 bufTm: %lu \n", *currentBrcbControlBlk->brcbControlBlk->bufTm);
    }
    if(currentBrcbControlBlk->brcbControlBlk){
        printf("报告 trgOps: ");
        Gsp_BitString_print(currentBrcbControlBlk->brcbControlBlk->trgOps);
    }
    if(currentBrcbControlBlk->brcbControlBlk->intgPd){
        printf("报告 intgPd: %lu \n", *currentBrcbControlBlk->brcbControlBlk->intgPd);
    }
    if(currentBrcbControlBlk->brcbControlBlk->gi){
        printf("报告 gi: %d \n", *currentBrcbControlBlk->brcbControlBlk->gi);
    }
    if(currentBrcbControlBlk->brcbControlBlk->purgeBuf){
        printf("报告 purgeBuf: %d \n", *currentBrcbControlBlk->brcbControlBlk->purgeBuf);
    }
    if(currentBrcbControlBlk->brcbControlBlk->entryID){
        printf("报告 entryID: %s \n", currentBrcbControlBlk->brcbControlBlk->entryID->buf);
    }

    // 调试信息
    printf("**************************** 缓存报告可用性检查应用层打印 ******************************* \n");
    if(*currentBrcbControlBlk->brcbControlBlk->rptEna){

        // 打印测试
        printf("该报告控制块已经被启用，请检查实例号是否冲突\n");

        // 释放内存
        Gsp_BRCBControlBlk_Destory(currentBrcbControlBlk);

        // 释放链接
        Gsp_IedConnection_Release(con, &error, associateID);

        // 释放关联ID
        Gsp_IedConnection_FreeAssociateID(associateID);

        // 销毁链接
        Gsp_IedConnection_Destroy(con);

        // 返回错误代码
        return -1;
    }


    // 调试信息
    printf("**************************** 设置缓存报告控制块应用层打印 ******************************* \n");
    printf("**************************** 设置缓存报告控制块《操作选项》 ******************************* \n");

    // 准备设置参数
    BRCBControlBlk targetBrcbControlBlk = static_cast<BRCBControlBlk>(GspMemory_calloc(1, sizeof(sBRCBControlBlk)));

    // 设置 refs(从获取的报告控制块中直接拷贝)
    Gsp_BRCBControlBlk_SetReportRefs(targetBrcbControlBlk, currentBrcbControlBlk->reportRefs);

    // 设置操作选项(报告带着报告原因)
    Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFldType::RCBOptFlds_reason_for_inclusion, true, false);

    // 设置操作选项(报告带着序列号)
    Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFldType::RCBOptFlds_sequence_number, true, true);

    // 设置操作选项(报告带着时间戳)
    Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFldType::RCBOptFlds_report_time_stamp, true, true);

    // 设置操作选项(报告带着数据集名字)
    Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFldType::RCBOptFlds_data_set_name, true, true);

    // 设置操作选项(报告带着数据参引串)
    Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFldType::RCBOptFlds_data_reference, true, true);

    // 设置操作选项(报告带着EntryID)
    Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFldType::RCBOptFlds_entryID, true, true);

    // 调试信息
    printf("即将设置的报告 optFlds: ");
    Gsp_BitString_print(targetBrcbControlBlk->brcbControlBlk->optFlds);

    // 设置报告触发选项
    if(Gsp_IedConnection_SetBRCBValues(con, &error, targetBrcbControlBlk)){
        printf("设置报告操作选项成功 \n\n");
    } else {
        printf("设置报告操作选项失败 \n\n");
    }

    // 调试信息
    printf("\n**************************** 设置缓存报告控制块《触发选项》 ******************************* \n");

    // 设置支持总召唤
    Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, RCBTriggerType::TriggerConditions_general_interrogation, true, false);

    // 数据变动触发
    Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, RCBTriggerType::TriggerConditions_data_change, true, true);

    // 设置周期性上送
    Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, RCBTriggerType::TriggerConditions_integrity, true, true);

    // 调试信息
    printf("即将设置的报告 trgOps: ");
    Gsp_BitString_print(targetBrcbControlBlk->brcbControlBlk->trgOps);

    // 设置报告控制块
    if(Gsp_IedConnection_SetBRCBValues(con, &error, targetBrcbControlBlk)){
        printf("设置报告触发选项成功 \n");
    } else {
        printf("设置报告触发选项失败: %d \n", error);
    }

    // 调试信息
    printf("\n**************************** 设置缓存报告控制块《周期时间》 ******************************* \n");

    // 设置周期性上送时间
    Gsp_BRCBControlBlk_IntgPd(targetBrcbControlBlk, 10000);

    // 设置报告控制块
    if(Gsp_IedConnection_SetBRCBValues(con, &error, targetBrcbControlBlk)){
        printf("设置报告周期时间成功 \n");
    } else {
        printf("设置报告周期时间失败: %d \n", error);
    }

    // 调试信息
    printf("\n**************************** 设置缓存报告控制块《清空缓存》 ******************************* \n");

    // 清空缓存
    Gsp_BRCBControlBlk_CleanBuffer(targetBrcbControlBlk);
    if(Gsp_IedConnection_SetBRCBValues(con, &error, targetBrcbControlBlk)){
        printf("清空缓存报告控制块成功 \n");
    } else {
        printf("清空报告控制块失败 \n");
    }

    // 调试信息
    printf("\n**************************** 设置缓存报告控制块《设置RPTID》 ******************************* \n");
    string tmpRPTID(Gsp_BRCBControlBlk_GetRptID(currentBrcbControlBlk));
    replace_all_distinct(tmpRPTID, "$BR$", ".");
    replace_all_distinct(tmpRPTID, "$RP$", ".");

    // 设置RPTID
    Gsp_BRCBControlBlk_SetRPTID(targetBrcbControlBlk, tmpRPTID.data());
    if(Gsp_IedConnection_SetBRCBValues(con, &error, targetBrcbControlBlk)){
        printf("设置报告控制块RPTID成功 \n");
    } else {
        printf("设置报告控制块RPTID失败 \n");
    }

    // 调试信息
    printf("\n**************************** 设置缓存报告控制块《安装回调》 ******************************* \n");

    // 安装报告回调
    Gsp_IedConnection_InstallReportCallBack(con,
                                            testReportRefs,
                                            tmpRPTID.data(),
                                            reportHandler,
                                            (void*)testReportRefs);

    // 调试信息
    printf("\n**************************** 设置缓存报告控制块《开启报告》 ******************************* \n");

    // 设置报告控制块值(开启报告)
    Gsp_BRCBControlBlk_EnableRpt(targetBrcbControlBlk, true);
    if(Gsp_IedConnection_SetBRCBValues(con, &error, targetBrcbControlBlk)){
        printf("报告开启成功 \n");
    } else {
        printf("报告开启失败 \n");
    }

    // 调试信息
    printf("\n**************************** 设置缓存报告控制块《总召报告》 ******************************* \n");
    // 设置总召
    Gsp_BRCBControlBlk_GI(targetBrcbControlBlk, true);
    if(Gsp_IedConnection_SetBRCBValues(con, &error, targetBrcbControlBlk)){
        printf("总召成功 \n");
    } else {
        printf("总召失败 \n");
    }

    // 等待报告到来(仅运行一段时间)
    int count = 0;
    while (1) {
        GspThread_sleep(10);
        if(count++ > 2000){
            break;
        }
    }

    // 卸载回调
    Gsp_IedConnection_ReleaseAllReportCallBack(con);

    // 释放控制块内存
    Gsp_BRCBControlBlk_Destory(currentBrcbControlBlk);

    // 释放内存
    Gsp_BRCBControlBlk_Destory(targetBrcbControlBlk);

    // 中止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 销毁链接
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);
}

