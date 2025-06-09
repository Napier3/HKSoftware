#include <iostream>
#include <string>
#include "curl\curl.h"

size_t read(void *buffer, size_t size, size_t nmemb, FILE *file)
{
	char* str = (char*)buffer;
	printf(str);
	return 0;
}

static size_t write_callback(void *buffer, size_t sz, size_t nmemb, void *ResInfo)
{
	std::string* psResponse = (std::string*)ResInfo;//强制转换
	psResponse->append((char*)buffer, sz * nmemb);//sz*nmemb表示接受数据的多少
	return sz * nmemb;  //返回接受数据的多少
}


int main()
{
	char* url = "http://192.168.1.59:21413/v2/iot/devices/direct/auth";
	std::string content = "{\"id\": 10045,\"version\": \"V2.1\",\"function\": \"iot/auth\",\"caller\": \"TTU\",\"body\": {\"sn\": \"1201021180331212\",\"module\": \"SCT230A\",\"manufacture\": \"nari\",\"algId\": \"\",\"checkID\": \"\"}}";
	CURL* curl;
	CURLcode code;
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	getchar();

	return 0;
}

/*
int main()
{
	curl_global_init(CURL_GLOBAL_ALL);
	std::string strCallBack = "";

	CURL *pUrl;
	pUrl = curl_easy_init();

	struct curl_httppost *formpost = 0;
	struct curl_httppost *lastptr  = 0;

	curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "file", CURLFORM_FILE, "D:\\a.txt", CURLFORM_END);
	curl_easy_setopt(pUrl, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(pUrl, CURLOPT_URL, "http://192.168.1.253:8080/file/upload");
	curl_easy_setopt(pUrl, CURLOPT_USERPWD, "User_WebDav:Aa123456789"); 
	curl_easy_setopt(pUrl, CURLOPT_HTTPPOST, formpost);
	curl_easy_setopt(pUrl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(pUrl, CURLOPT_WRITEDATA, &strCallBack);
	CURLcode code = curl_easy_perform(pUrl);
	curl_formfree(formpost);
	curl_easy_cleanup(pUrl);

	getchar();

	return 0;
}
*/