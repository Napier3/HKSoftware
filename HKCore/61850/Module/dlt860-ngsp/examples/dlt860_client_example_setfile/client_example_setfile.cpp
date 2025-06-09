#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "../config/example_config.h"


int main(int argc, char** argv) {

    char* hostname;
    int tcpPort = PORT;

    if (argc > 1) {
        hostname = argv[1];
    } else {
        hostname = HOSTNAME;
    }

    if (argc > 2) {
        tcpPort = atoi(argv[2]);
    }

    const char* fileName = "test.file";
    if (argc > 3) {
        fileName = argv[3];
    }

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

    // 写文件
    FILE* fp = fopen(fileName, "r");
    uint32_t filePostion = 1;
    char fileDataBlock[1024] = {0};
    while (!feof(fp)) {

        // 读取一定数量数据
        memset(fileDataBlock, 0 , sizeof(fileDataBlock));
        int count = fread(fileDataBlock, sizeof (char), 1024, fp);

        // 是否为空
        bool endFlag = false;
        if(feof(fp)){
            endFlag = true;
        }

        // 发送文件
        bool ret = Gsp_IedConnection_setFile(con, &error, fileName, filePostion, fileDataBlock, count, endFlag);
        printf("写一帧文件, 字节数量:%d, 是否写成功:%d \n", 1024, ret);
    }

    // 终止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 销毁链接
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);
}


