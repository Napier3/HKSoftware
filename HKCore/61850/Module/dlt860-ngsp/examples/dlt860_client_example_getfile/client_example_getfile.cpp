#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "../config/example_config.h"

bool fileDownloadHandler(void* parameter, uint8_t* buffer, uint32_t bytesRead, bool endFlag){

    FILE* fp = (FILE*) parameter;
    printf("received %i bytes\n", bytesRead);
    if (fwrite(buffer, bytesRead, 1, fp) == 1){

        if(endFlag){
            // 关闭文件
            fclose(fp);
            printf("文件下载完毕, 保存操作\n");
        }

        return true;
    } else {
        printf("Failed to write local file!\n");

        // 关闭文件
        fclose(fp);

        return false;
    }
};

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

    const char* targetFile = "/兴隆变.scd";
    if (argc > 3) {
        targetFile = argv[3];
    }

    const char* fileName = "/兴隆变.scd";
    if (argc > 4) {
        fileName = argv[4];
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

    // 本地存储的文件路径
    const char *localFilePath = fileName;

    // 远程请求的文件绝对路径
    const char *remoteFilePath = targetFile;

    // 下载文件
    FILE* fp = fopen(localFilePath, "w");
    uint32_t filePostion = 1;
    while (Gsp_IedConnection_GetFile(con, &error, remoteFilePath, &filePostion, fileDownloadHandler, (void*)fp))
    {
        printf("下载文件 %s 已下载数据 %d 字节 \n", remoteFilePath, filePostion);
    }
    
    // 终止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 销毁链接
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);
}


