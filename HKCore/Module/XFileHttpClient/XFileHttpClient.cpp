#include "stdafx.h"
#include "XFileHttpClient.h"
#include "../xml/JSON/CJSON.h"

namespace CXFileHttpClient
{
	CURLcode errCode;
	std::string strLastReport;

	size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream)
	{
		size_t sizes = fread(ptr, size, nmemb, (FILE *)stream); 
		return sizes;
	}

	size_t write_callback(void *buffer, size_t sz, size_t nmemb, void *ResInfo)
	{
		std::string* psResponse = (std::string*)ResInfo;//强制转换
		psResponse->append((char*)buffer, sz * nmemb);//sz*nmemb表示接受数据的多少
		return sz * nmemb;  //返回接受数据的多少
	}

	BOOL InitXFileHttpClient(long nFlag/*= CURL_GLOBAL_ALL*/)
	{
		errCode = CURLE_OK;
		strLastReport = "";

		CURLcode code = curl_global_init(nFlag);
		errCode = code;

		if(code != CURLE_OK)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("InitXFileHttpClient: failed"));
			return FALSE;
		}

		return TRUE;
	}

	void ExitXFileHttpClient()
	{
		curl_global_cleanup();
	}

	BOOL UploadFile(const char* strUrl, const char* strFilePath)
	{
		if (strlen(strFilePath) <= 5)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("HttpUploadFile: file path is empty........."));
			return FALSE;
		}

		CURL *pUrl;
		pUrl = curl_easy_init();

		strLastReport = "";

		struct curl_httppost *formpost = 0;
		struct curl_httppost *lastptr  = 0;

		curl_formadd(&formpost, &lastptr, CURLFORM_PTRNAME, "file", CURLFORM_FILE, strFilePath, CURLFORM_END);
		curl_easy_setopt(pUrl, CURLOPT_URL, strUrl);
		curl_easy_setopt(pUrl, CURLOPT_HTTPPOST, formpost);
		curl_easy_setopt(pUrl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(pUrl, CURLOPT_WRITEDATA, &strLastReport);
		CURLcode code = curl_easy_perform(pUrl);
		curl_formfree(formpost);
		curl_easy_cleanup(pUrl);

		long nCode = 200;
		CJSON* pJson = CJSON_Parse(strLastReport.c_str());
		if(pJson != NULL)
		{
			CJSON* pCodeJson = CJSON_GetObjectItem(pJson, "code");
			nCode = pCodeJson->valueint;

		CJSON_Delete(pJson);
		}	

		errCode = code;
		if(code != CURLE_OK)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("HttpUploadFile: [%s] failed"),strFilePath);
			return FALSE;
		}

		if(nCode != 200)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("HttpUploadFile: [%s] failed, http error codes = %d"),strFilePath, nCode);
			return FALSE;
		}

		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("HttpUploadFile: [%s] success"),strFilePath);
		return TRUE;
	}
	
	BOOL DownloadFile(const char* strUrl, const char* strFilePath)
	{
		//创建目录
		CString strPath = GetPathFromFilePathName(strFilePath, '\\');
		CreateAllDirectories(strPath);

		FILE* pFile = NULL;
		pFile = fopen(strFilePath, "wb");

		CURL* pUrl = curl_easy_init();
		curl_easy_setopt(pUrl, CURLOPT_FAILONERROR);//区分http返回 >= 400
		curl_easy_setopt(pUrl, CURLOPT_URL, strUrl);
		curl_easy_setopt(pUrl, CURLOPT_WRITEDATA, pFile);
		CURLcode code = curl_easy_perform(pUrl);
		curl_easy_cleanup(pUrl);
		fclose(pFile);

		errCode = code;
		if(code != CURLE_OK)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("HttpDownloadFile: [%s] failed"),strFilePath);
			X_DeleteFile(strFilePath);  //下载失败，则删除fopen创建的空文件  shaolei 20211224
			return FALSE;
		}

		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("HttpDownloadFile: [%s] success"),strFilePath);
		return TRUE;
	}

	CURLcode GetLastError(std::string& strError)
	{
		strError = curl_easy_strerror(errCode);
		return errCode;
	}

	std::string GetLastReport()
	{
		//应当紧跟write date回调函数从而获取report
		return strLastReport;
	}

	//add by yzj 20210807
	void ParseURLReport(std::string& strReport, std::string& strFileName, std::string& strFileUrl)
	{
		if(!strReport.length())
			strReport = GetLastReport();

		CJSON* pJson = CJSON_Parse(strReport.c_str());

		if (pJson == NULL)
		{
			return;
		}

		CJSON* pNode = pJson->child;
		while (pNode)
		{
			if(strcmp(pNode->string, "fileName") == 0)
			{
				strFileName = pNode->valuestring;
			}
			else if(strcmp(pNode->string, "url") == 0)
			{
				strFileUrl = pNode->valuestring;
			}
			pNode = pNode->next;
		}
		CJSON_Delete(pJson);
	}

	BOOL UploadFile(const char* strUrl, const char* strFilePath, const char* strDevSN, const char* strBenchId, const char* strFileType)
	{
		if (strlen(strFilePath) <= 5)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("HttpUploadFile: file path is empty........."));
			return FALSE;
		}

		CURL *pUrl;
		pUrl = curl_easy_init();

		strLastReport = "";

		struct curl_httppost *formpost = 0;
		struct curl_httppost *lastptr  = 0;

		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "file", CURLFORM_FILE, strFilePath, CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "deviceSn", CURLFORM_COPYCONTENTS, strDevSN, CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "benchId", CURLFORM_COPYCONTENTS, strBenchId, CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "fileType", CURLFORM_COPYCONTENTS, strFileType, CURLFORM_END);
		curl_easy_setopt(pUrl, CURLOPT_URL, strUrl);
		curl_easy_setopt(pUrl, CURLOPT_HTTPPOST, formpost);
		curl_easy_setopt(pUrl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(pUrl, CURLOPT_WRITEDATA, &strLastReport);
		CURLcode code = curl_easy_perform(pUrl);
		curl_formfree(formpost);
		curl_easy_cleanup(pUrl);

		long nCode = 200;
		CJSON* pJson = CJSON_Parse(strLastReport.c_str());
		if(pJson != NULL)
		{
			CJSON* pCodeJson = CJSON_GetObjectItem(pJson, "code");
			nCode = pCodeJson->valueint;

			CJSON_Delete(pJson);
		}	

		errCode = code;
		if(code != CURLE_OK)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("HttpUploadFile: [%s] failed"),strFilePath);
			return FALSE;
		}

		if(nCode != 200)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("HttpUploadFile: [%s] failed, http error codes = %d"),strFilePath, nCode);
			return FALSE;
		}

		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("HttpUploadFile: [%s] success"),strFilePath);
		return TRUE;
	}
}