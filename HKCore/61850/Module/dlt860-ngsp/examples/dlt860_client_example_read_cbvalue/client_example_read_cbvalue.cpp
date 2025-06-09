#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "gsp_hal_thread.h"
#include "GetAllCBValuesResponsePDU.h"
#include "../config/example_config.h"


int main(int argc, char** argv) {

    char* hostname;
    int tcpPort = PORT;

    if (argc > 1){
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

    // 获取 所有控制块数据
    GspLinkedList allCBDataValue = Gsp_IedConnection_GetAllCBValues(con, &error, GSP_ACSIClass_lcb, "P_L2211DLD0/LLN0", LNREFERENCE);

    // 获取数据并打印 测试
    if(allCBDataValue)
    {
        for(auto &item : *allCBDataValue)
        {
            GetAllCBValuesResponsePDU_t * dataItem = (GetAllCBValuesResponsePDU_t *)item;

            // 逐条解析
            for(int i=0; i< dataItem->cbValue.list.count; ++i){
                
                // 获取数据
                GetAllCBValuesResponsePDU__cbValue__Member* item = dataItem->cbValue.list.array[i];
                printf("************************** 控制块值测试(数据条目 %d/%d) ************************** \n", i+1, dataItem->cbValue.list.count);
                printf("控制块的 refs: %s \n", item->reference.buf);
                switch(item->value.present){
                case GetAllCBValuesResponsePDU__cbValue__Member__value_PR_brcb:
                {
                    // 打印测试
                    BRCB_t itemData = item->value.choice.brcb;
                    printf("BRCB_t rptID: %s \n", itemData.rptID.buf);
                    printf("BRCB_t rptEna: %d \n", itemData.rptEna);
                    printf("BRCB_t datSet: %s \n", itemData.datSet.buf);
                    printf("BRCB_t confRev: %d \n", itemData.confRev);
                    printf("BRCB_t optFlds: %x \n", itemData.optFlds.buf);
                    printf("BRCB_t bufTm: %d \n", itemData.bufTm);
                    printf("BRCB_t sqNum: %d \n", itemData.sqNum);
                    printf("BRCB_t trgOps: %d \n", itemData.trgOps);
                    printf("BRCB_t intgPd: %d \n", itemData.intgPd);
                    printf("BRCB_t gi: %d \n", itemData.gi);
                    printf("BRCB_t purgeBuf: %d \n", itemData.purgeBuf);
                    printf("BRCB_t entryID: %s \n", itemData.entryID.buf);
                    printf("BRCB_t timeOfEntry: %s \n", itemData.timeOfEntry.buf);
                } break;
                case GetAllCBValuesResponsePDU__cbValue__Member__value_PR_urcb: {
                    // 打印测试
                    URCB_t itemData = item->value.choice.urcb;
                } break;
                case GetAllCBValuesResponsePDU__cbValue__Member__value_PR_lcb: {
                    // 打印测试
                    LCB_t itemData = item->value.choice.lcb;
                    printf("LCB_t logEna: %d\n", itemData.logEna);
                    printf("LCB_t datSet: %s\n", itemData.datSet.buf);
                    printf("LCB_t intgPd: %u\n", itemData.intgPd);
                    printf("LCB_t logRef: %s\n", itemData.logRef.buf);
                } break;
                case GetAllCBValuesResponsePDU__cbValue__Member__value_PR_sgcb: {
                    // 打印测试
                    SGCB_t itemData = item->value.choice.sgcb;
                } break;
                case GetAllCBValuesResponsePDU__cbValue__Member__value_PR_gocb: {
                    // 打印测试
                    GoCB_t itemData = item->value.choice.gocb;
                } break;
                case GetAllCBValuesResponsePDU__cbValue__Member__value_PR_msvcb: {
                    // 打印测试
                    MSVCB_t itemData = item->value.choice.msvcb;
                } break;
                }
            }

            // 内存释放
            Gsp_FreeAllCBValue(dataItem);
        }
    }

    // 内存释放
    GspLinkedList_destroyStatic(allCBDataValue);

    // 终止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 销毁链接
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);
}


