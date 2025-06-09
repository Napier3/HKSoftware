#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "gsp_hal_thread.h"
#include "conversions.h"
#include "gsp_lib_memory.h"
#include "../config/example_config.h"
#include <time.h>

/************************************************
 * 日志测试用例
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

    // 获取日志控制块的基本信息
    const char* lcbRefs = "RMV2201ALD0/LLN0.lcblog";
    //const char* lcbRefs = "RMV2201BRCD0/LD0";
    void* lcbInfo = Gsp_IedConnection_GetLCBValues(con, &error, lcbRefs);

    // 错误判断
    bool errFlag = Gsp_LCBlock_hasError(lcbInfo);
    if(!errFlag){

        // 获取日志控制快refs
        printf("日志控制块refs: %s \n", Gsp_LCBlock_getLogRef(lcbInfo));

        // 获取日志控制块是否启用
        printf("日志控制块是否启用: %u \n", Gsp_LCBlock_getLogEna(lcbInfo));

        // 获取日志控制块相关的数据集描述
        printf("日志控制块相关的数据集描述: %s \n", Gsp_LCBlock_getDatset(lcbInfo));

        // 获取日志控制块的周期数值
        printf("日志控制块的周期数值: %d \n", Gsp_LCBlock_getIntgPd(lcbInfo));

        // 启用日志控制块
//        bool setEnaFlag = Gsp_LCBlock_setLogEna(lcbInfo, true);
//        bool enaFlag = Gsp_IedConnection_SetLCBValues(con, &error, lcbInfo);
//        printf("启用日志控制块: %u \n", setEnaFlag && enaFlag);

//         //查询日志
        uint64_t oneDay = 1000*60*60*24;
        //uint64_t startTimestamp = GSP_Hal_getTimeInMs() - oneDay*7;
        uint64_t startTimestamp = GSP_Hal_getTimeInMs() - 2 *60 * 1000;
        uint64_t endTimestamp = GSP_Hal_getTimeInMs();
        BinaryTime_t startTime;
        BinaryTime_newTimeFromTimeStamp(&startTime, startTimestamp);
        BinaryTime_t stopTime;
        BinaryTime_newTimeFromTimeStamp(&stopTime, endTimestamp);
        struct tm tm_t = {};
        char szBuf[64] = {0};
        uint64_t millsec = 0;
        time_t t;
                GspLinkedList logList = Gsp_IedConnection_QueryLogByTime(con, &error, "RMV2201ALD0/LLN0.LD0", (char*)startTime.buf, (char*)stopTime.buf, nullptr);
                if(logList){
                    for(auto &logItem: *logList){
                        QueryLogByTimeResponsePDU_t* logItemPtr = (QueryLogByTimeResponsePDU_t*) logItem;
                        // 逐个数据单元打印
                        for(int index=0; index < logItemPtr->logEntry.list.count; ++index){
                            LogEntry* logEntryItem = logItemPtr->logEntry.list.array[index];

                            // 日志条目timeOfEntry打印
                            millsec = BinaryTime_getAsUtcMs(&logEntryItem->timeOfEntry);
                            t = (time_t)(millsec / 1000);
                            tm_t = *localtime(&t);//输出时间
                            strftime(szBuf, 64, "%Y-%m-%d %H:%M:%S", &tm_t);
                            printf("log timeOfEntry：%s.%03d\n", szBuf, millsec % 1000);
                            // 日志entryID打印
                            printf("log entryID: ");
                            for(int i = 0; i < logEntryItem->entryID.size; i++){
                                printf("%02d ", logEntryItem->entryID.buf[i]);
                            }
                            printf("\n");

                            // 逐条获取日志内容
                            for (int innerIndex=0; innerIndex < logEntryItem->entryData.list.count; ++innerIndex) {
                                LogEntry__entryData__Member* innerLogItem = logEntryItem->entryData.list.array[innerIndex];
                                printf("日志 Refs: %s\n", innerLogItem->reference.buf);
                                printf("日志 fc: %s\n", innerLogItem->fc.buf);
                                if(*innerLogItem->reason.buf == 0x02){
                                    printf("日志 reason : ReasonCode_data_change\n");
                                }else if(*innerLogItem->reason.buf == 0x40){
                                    printf("日志 reason : ReasonCode_quality_change\n");
                                }else if(*innerLogItem->reason.buf == 0x20){
                                    printf("日志 reason : ReasonCode_data_updates\n");
                                }else if(*innerLogItem->reason.buf == 0x10){
                                    printf("日志 reason : ReasonCode_integrity\n");
                                }else if(*innerLogItem->reason.buf == 0x08){
                                    printf("日志 reason : ReasonCode_general_interrogation\n");
                                }else if(*innerLogItem->reason.buf == 0x04){
                                    printf("日志 reason : ReasonCode_application_trigger\n");
                                }
                                //GspMmsValue_printToBuffer(&innerLogItem->value);
                            }

                        }
                    }
                }
    } else {
        printf("获取日志控制块错误:%s , 错误代码: %u \n", lcbRefs, Gsp_LCBlock_getErrorCode(lcbInfo));
    }

    // 释放链接
    Gsp_IedConnection_Release(con, &error, associateID);

    // 中止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 销毁链接
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);
}

