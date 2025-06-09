#pragma once
#include "curl\curl.h"
#include <string>

namespace CXFileHttpClient
{
	BOOL InitXFileHttpClient(long nFlag = CURL_GLOBAL_ALL);
	void ExitXFileHttpClient();
	BOOL UploadFile(const char* strUrl, const char* strFilePath);
	BOOL UploadFile(const char* strUrl, const char* strFilePath, const char* strDevSN, const char* strBenchId, const char* strFileType);
	BOOL DownloadFile(const char* strUrl, const char* strFilePath);
	CURLcode GetLastError(std::string& strError);
	std::string GetLastReport();
	void ParseURLReport(std::string& strReport, std::string& strFileName, std::string& strFileUrl);
}