#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "gsp_hal_thread.h"
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

    if (argc > 2)
        tcpPort = atoi(argv[2]);

    // 目标目录
    const char* fileDirectory = "/COMTRADE/";
    if(argc > 3) {
        fileDirectory = argv[3];
    }

    // 最近时间
    int timeSpan = 24;
    if(argc > 4) {
        timeSpan = atoi(argv[4]);
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

    // 获取文件目录(最近一天的文件目录)
    bool moreData = false;

    GspLinkedList fileDirs;
    GspMmsValue* timeStart = nullptr;
    GspMmsValue* timeEnd = nullptr;
    if(timeSpan > 0){
        uint64_t oneYear = 1000*60*60*timeSpan;
        uint64_t startTimestamp = GSP_Hal_getTimeInMs() - oneYear;
        uint64_t endTimestamp = GSP_Hal_getTimeInMs();
        timeStart = GspMmsValue_new();
        timeEnd = GspMmsValue_new();
        GspMmsValue_setUtcTimeMs(timeStart, startTimestamp);
        GspMmsValue_setUtcTimeMs(timeEnd, endTimestamp);
        fileDirs = Gsp_IedConnection_GetFileDirectory(con,
                                                      &error,
                                                      fileDirectory,
                                                      (char*)GspMmsValue_getUtcTimeBuffer(timeStart),
                                                      (char*)GspMmsValue_getUtcTimeBuffer(timeEnd),
                                                      nullptr,
                                                      moreData);
    } else {
        fileDirs = Gsp_IedConnection_GetFileDirectory(con,
                                                      &error,
                                                      fileDirectory,
                                                      nullptr,
                                                      nullptr,
                                                      nullptr,
                                                      moreData);
    }

    // 保护性的循环获取10次
    int cycleCount = 10;
    while (moreData && cycleCount-->0) {

        // 获取最后一个文件
        if(GspLinkedList_size(fileDirs) <= 0){
            break;
        }
        GspFileDirectoryEntry fileItem = (GspFileDirectoryEntry)GspLinkedList_getLastElement(fileDirs);


        // 获取文件列表
        GspLinkedList tmpFileList;

        if(timeSpan > 0){
            tmpFileList = Gsp_IedConnection_GetFileDirectory(con,
                                                             &error,
                                                             fileDirectory,
                                                             (char*)GspMmsValue_getUtcTimeBuffer(timeStart),
                                                             (char*)GspMmsValue_getUtcTimeBuffer(timeEnd),
                                                             Gsp_FileDirEntry_GetFileName(fileItem),
                                                             moreData);
        } else {
            tmpFileList = Gsp_IedConnection_GetFileDirectory(con,
                                                             &error,
                                                             fileDirectory,
                                                             nullptr,
                                                             nullptr,
                                                             Gsp_FileDirEntry_GetFileName(fileItem),
                                                             moreData);
        }
        if (error != GSP_IED_ERROR_OK) {
            continue;
        }

        // 结果合并
        for(auto &item: *tmpFileList){
            GspLinkedList_add(fileDirs, item);
        }

        // 删除原列表
        GspLinkedList_destroyStatic(tmpFileList);
    }

    // 解析并打印
    char *remoteFilePath = new char[256];
    for(auto &item : *fileDirs)
    {
        // 获取文件信息
        GspFileDirectoryEntry fileItem = (GspFileDirectoryEntry)item;
        // 本地存储的文件路径
        const char *localFilePath = Gsp_FileDirEntry_GetFileName(fileItem);
        memset(remoteFilePath, 0 , 256);
        memcpy(remoteFilePath, fileDirectory, strlen(fileDirectory));
        memcpy(remoteFilePath+strlen(fileDirectory), localFilePath, strlen(localFilePath));

        // 打印信息
        printf("文件名字: %s \n", Gsp_FileDirEntry_GetFileName(fileItem));
        printf("文件尺寸: %d \n", Gsp_FileDirEntry_GetFileSize(fileItem));
        printf("文件最后修改时间: %lu \n", Gsp_FileDirEntry_GetLastModified(fileItem));
        printf("是否有后续的数据文件: %d \n\n", moreData);

        // 开始下载文件
        FILE* fp = fopen(localFilePath, "w");
        uint32_t filePostion = 1;
        while (Gsp_IedConnection_GetFile(con, &error, remoteFilePath, &filePostion, fileDownloadHandler, (void*)fp))
        {
            printf("下载文件 %s 已下载数据 %d 字节 \n", remoteFilePath, filePostion);
        }

        // 资源销毁
        Gsp_FileDirEntry_Destroy(fileItem);
    }

    // 資源釋放
    GspMmsValue_delete(timeStart);
    GspMmsValue_delete(timeEnd);

    // 目录资源释放
    GspLinkedList_destroyStatic(fileDirs);
    
    // 终止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, associateID);

    // 链接资源释放
    Gsp_IedConnection_Destroy(con);
    Gsp_IedConnection_FreeAssociateID(associateID);
}


