#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "gsp_hal_thread.h"
#include "conversions.h"
#include "gsp_lib_memory.h"
#include "../config/example_config.h"

/************************************************
 * 控制用例
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

    /********************************** SBO 用例 **********************************/

    const char* testCaseSBO = "PE1001ALD0/GGIO1.SPCSO2";

    // 创建控制对象
    GspControlObjectClient sboControl = Gsp_ControlObjectClient_Create(testCaseSBO, con);

    // 设置refs
    Gsp_ControlObjectClient_SetControlRefs(sboControl, "PE1001ALD0/GGIO1.SPCSO2");

    // 设置同期检查
    Gsp_ControlObjectClient_SetSyncCheck(sboControl, true);

    if(Gsp_IedConnection_Select(sboControl, &error)){
        // 设置值
        GspMmsValue* ctlVal = GspMmsValue_newBoolean(true);

        // 设置origin
        Gsp_ControlObjectClient_SetOriginator(sboControl, Originator__orCat_remoteControl, "test");

        // 控制
        if(Gsp_IedConnection_Operate(sboControl, &error, ctlVal, 0)){
            printf("%s 选择控制成功 \n", testCaseSBO);
        } else {
            printf("%s 选择控制失败 \n", testCaseSBO);
        }
    }

    /********************************** SWV 用例 **********************************/

    const char* testCaseSWV = "PE1001ALD0/GGIO1.SPCSO1";

    // 创建控制对象
    GspControlObjectClient swvControl = Gsp_ControlObjectClient_Create(testCaseSWV, con);

    // 设置refs
    Gsp_ControlObjectClient_SetControlRefs(sboControl, "PE1001ALD0/GGIO1.SPCSO1");

    // 设置值
    GspMmsValue* swvCtlVal = GspMmsValue_newBoolean(true);

    // 设置同期检查
    Gsp_ControlObjectClient_SetSyncCheck(swvControl, true);

    // 设置origin
    Gsp_ControlObjectClient_SetOriginator(swvControl, Originator__orCat_remoteControl, "test");

    if(Gsp_IedConnection_SelectWithValue(swvControl, &error, swvCtlVal)){
        printf("%s 带值选择控制成功 \n", testCaseSWV);
    } else {
        printf("%s 带值选择控制失败 \n", testCaseSWV);
    }

    /********************************** 直控用例 **********************************/

    const char* testCase = "PE1001ALD0/GGIO1.SPCSO1";

    // 创建控制对象
    GspControlObjectClient directControl = Gsp_ControlObjectClient_Create(testCase, con);

    // 设置refs
    Gsp_ControlObjectClient_SetControlRefs(sboControl, "PE1001ALD0/GGIO1.SPCSO1");

    // 设置值
    GspMmsValue* ctlVal = GspMmsValue_newBoolean(true);

    // 设置同期检查
    Gsp_ControlObjectClient_SetSyncCheck(directControl, true);

    // 设置origin
    Gsp_ControlObjectClient_SetOriginator(directControl, Originator__orCat_remoteControl, "test");

    // 直控
    if(Gsp_IedConnection_Operate(directControl, &error, ctlVal, 0)){
        printf("%s 直接控制成功 \n", testCase);
    } else {
        printf("%s 直接控制失败 \n", testCase);
    }

    // TODO 读值检查

    // 资源释放
    Gsp_ControlObjectClient_Destroy(directControl);
    Gsp_ControlObjectClient_Destroy(swvControl);
    Gsp_ControlObjectClient_Destroy(sboControl);

    // 释放链接
    Gsp_IedConnection_Release(con, &error, associateID);

    // 中止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 销毁链接
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);
}

