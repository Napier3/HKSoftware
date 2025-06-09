#include "mms_server_internal.h"
#include "asn_inc.h"
#include "nlogging.h"
#include "iso_server_private.h"
#include <filesystem>
#include <chrono>
#include <limits>
#include "crc32.h"
#include "mms_server_func.h"

using namespace std::chrono_literals;

namespace fs = std::filesystem;

void toRelFilePath(size_t prefixLen, string &fileName)
{
    fileName = fileName.substr(prefixLen);
    if(fileName[0] == '/')
    {
        fileName = fileName.substr(1);
    }
}

uint32_t GspServerFile::getFileCrc32(const string &fileName)
{ 
    const int BUF_SIZE = 4096;
    char buf[BUF_SIZE]; 
    NLOG_DEBUG(fileName);
    auto *pFile = fopen(fileName.c_str(), "r+"); 
    ssize_t byteRead = fread(buf, 1, BUF_SIZE, pFile);
    auto param = CRC::CRC_32();
    param.polynomial = 0x04C11DB7;  
    uint32_t crc = 0;

    if(byteRead > 0) 
    {
        crc = CRC::Calculate(buf, byteRead, param);
    }
    else
    {
        return 0;
    }
    byteRead = fread(buf, 1, BUF_SIZE, pFile);
    while(byteRead > 0)
    {
        crc = CRC::Calculate(buf, byteRead, param, crc);
        byteRead = fread(buf, 1, BUF_SIZE, pFile);
    }
    fclose(pFile);
    return crc;
}

bool GspServerFile::getFileInfo(const filesystem::path& filename, uint32_t* fileSize, uint64_t* lastModificationTimestamp)
{
    try {
        fs::directory_entry entry(filename);

        if (!entry.exists())
        {
            return false;
        }
        auto ftime = entry.last_write_time();
        std::time_t cftime = to_time_t(ftime);

        if(entry.is_regular_file())
        {
            *fileSize = entry.file_size();
            *lastModificationTimestamp = cftime * 1000;
        }
        else if(entry.is_directory())
        {
            auto it = fs::directory_iterator(entry);
            *fileSize = std::distance(begin(it), end(it));
            *lastModificationTimestamp = cftime * 1000;
        }
        else
        {
            return false;
        }
    }  catch (const exception &e) {
        NLOG_WARN(e.what());
        return false;
    } 
    return true;
}

void *GspServerFile::handleGetFileDirectory(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetFileDirectoryRequestPDU_t*>(requestData);
    auto response = createAsnResponse<GetFileDirectoryResponsePDU_t>();

    string pathName = self->server->filestoreBasepath;
    uint64_t startTimeMs = 0;
    uint64_t stopTimeMs = (numeric_limits<uint64_t>::max)();
    string fileAfter;

    pathName += (char *)request->pathName.buf;
    size_t prefixLen = pathName.size();

    if(request->startTime)
    {
        startTimeMs = convertUtcTimeToMs(*request->startTime);
    }

    if(request->stopTime)
    {
        uint64_t time = convertUtcTimeToMs(*request->stopTime);
        if(time > 0)
        {
            stopTimeMs = time;
        }
    }

    if(request->fileAfter)
    {
        fileAfter = (char *)request->fileAfter->buf;
    }

    bool start = fileAfter.empty();
    response->moreFollows = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
    *response->moreFollows = false;
    int count = 0;
    for(const auto &entry : fs::directory_iterator(pathName))
    {
        if(count == 51)
        {
            *response->moreFollows = true;
            break;
        }

        if(!start && !fileAfter.empty())
        {
            string entryName = entry.path().string(); //full path
            toRelFilePath(prefixLen, entryName); //entry name(file and folder name)
            if(entry.is_directory())
            {
                entryName += "/";
            }
            start = (fileAfter == entryName);
            continue;
        }

        uint32_t size = 0;
        uint64_t lastModified = 0;
        NLOG_DEBUG(entry.path().string());

        auto ret = getFileInfo(entry.path(), &size, &lastModified);
        if(ret)
        {
            NLOG_DEBUG("{} {} {} {}", entry.path().string(), startTimeMs, lastModified, stopTimeMs);
            if(startTimeMs <= lastModified && stopTimeMs >= lastModified)
            {
                FileEntry_t *fileEntry = createAsnResponse<FileEntry_t>();
                string fileName = entry.path().string();
                toRelFilePath(prefixLen, fileName);
                if(entry.is_directory()) 
                {
                    fileName += "/";
                }
                OCTET_STRING_fromBuf(&fileEntry->fileName, fileName.c_str(), -1);
                fileEntry->fileSize = size;
                auto value = GspMmsValue_newUtcTimeByMsTime(lastModified);
                GspFillMmsValueToUtcTime(fileEntry->lastModified, value);
                ASN_STRUCT_FREE(asn_DEF_Data, value);
                ASN_SEQUENCE_ADD(&response->fileEntry, fileEntry);
                if(!entry.is_directory())
                {
                    string filePath = entry.path().string();
                    fileEntry->checkSum = getFileCrc32(filePath); 
                } 
                count++;
            }
        }
    }

    return response;
}

void *GspServerFile::handleGetFileAttributeValues(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetFileAttributeValuesRequestPDU_t*>(requestData);
    auto response = createAsnResponse<GetFileAttributeValuesResponsePDU_t>();

    string fileName = self->server->filestoreBasepath;
    fileName += (char *)request->filename.buf;
    uint64_t ms = 0;
    fs::directory_entry entry(fileName);

    if (!getFileInfo(entry.path(), (uint32_t *)&response->fileSize, &ms))
    {
        throw runtime_error(string("没有找到文件[") + fileName + "]");
    }
    response->fileName = request->filename;

    auto value = GspMmsValue_newUtcTimeByMsTime(ms);
    GspFillMmsValueToUtcTime(response->lastModified, value);
    return response;
}

void *GspServerFile::handleDeleteFile(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<DeleteFileRequestPDU_t*>(requestData);
    auto response = createAsnResponse<DeleteFileResponsePDU_t>();
    string fileName = self->server->filestoreBasepath;

    fileName += (char *)request->filename.buf;
    NLOG_DEBUG("请求删除文件%s\n", fileName.c_str());
    if(!fs::remove((char *)fileName.c_str()))
    {
        throw runtime_error(string("删除文件[") + fileName + "]失败\n");
    }

    return response;
}

void *GspServerFile::handleGetFile(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<GetFileRequestPDU_t*>(requestData);
    auto response = createAsnResponse<GetFileResponsePDU_t>();
    string fileName = self->server->filestoreBasepath;

    fileName += (char *)request->filename.buf;
    auto file = fopen(fileName.c_str(), "r+");
    if(!file)
    {
        ASN_STRUCT_FREE(asn_DEF_GetFileResponsePDU, response);
        throw invalid_argument(fmt::format("文件[{}]打开失败", fileName));
    }
    auto startPos = request->startPostion - 1;
    fseek(file, startPos, SEEK_SET);
    const int BLOCK_SIZE = 10 * 1024;

    response->fileData.buf = new uint8_t[BLOCK_SIZE];
    int readSize = fread(response->fileData.buf, 1, BLOCK_SIZE, file);
    if(readSize < 0)
    {
        fclose(file);
        ASN_STRUCT_FREE(asn_DEF_GetFileResponsePDU, response);
        throw invalid_argument(fmt::format("文件[{}]读取失败", fileName));
    }
    response->fileData.size = readSize;
    NLOG_DEBUG("get file size {}\n", readSize);
    fs::path p(fileName);
    auto totalSize = fs::file_size(p);

    response->endOfFile = ((readSize + startPos) >= totalSize ? 1 : 0);
    fclose(file);

    return response;
}

void *GspServerFile::handleSetFile(GspMmsServerConnection self, void *requestData)
{
    auto request = static_cast<SetFileRequestPDU_t*>(requestData);
    auto response = createAsnResponse<SetFileResponsePDU_t>();
    string fileName = self->server->filestoreBasepath;
    fileName += "/";
    fileName += (const char *)request->filename.buf;

    if(request->startPostion == 0)
    {
        // 删除文件
        if(!fs::remove((char *)fileName.c_str()))
        {
            throw runtime_error(string("删除文件[") + fileName + "]失败\n");
        }
        return response;
    }
    auto startPos = request->startPostion - 1;

    auto file = fopen(fileName.c_str(), "a+");
    if(!file)
    {
        throw runtime_error(string("打开文件[") + fileName + "]失败");
    }

    auto ret = fseek(file, startPos, SEEK_SET);
    if(ret < 0)
    {
        throw runtime_error(string("偏转文件[") + fileName + "]失败,位置[" + to_string(startPos) + "]");
    }

    ret = fwrite(request->fileData.buf, 1, request->fileData.size, file);
    if(ret < 0 || size_t(ret) < request->fileData.size)
    {
        throw runtime_error(string("写入文件[") + fileName + "]失败");
    }
    fflush(file);
    fclose(file);
    return response;
}
