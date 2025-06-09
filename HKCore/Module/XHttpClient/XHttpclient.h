#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <curl/curl.h>
#include <StlLock.h>
using namespace std;

//CHTTPResponse ±ðÃû
typedef struct tagResponse
{
	int code;
	string buff;
	char m_strBuffer[1024];

	tagResponse()
	{
		for (int i = 0; i < 1024; i++)
		{
			m_strBuffer[i] = 0;
		}
	}

}CHTTPResponse;

class CHTTPClient
{
public:
	CHTTPClient();
	CHTTPClient(int keepalive);
	virtual ~CHTTPClient();

private:
	CHTTPResponse* m_pResult;

private:
	void init(int keepalive);
	CURL *m_curl;
	CCritSec * m_critSec;
	static int writer(char *data, size_t size, size_t nmemb,std::string *writerData);

public:
	CHTTPResponse *Get(string httpHead,string httpIp,long httpPort);
	CHTTPResponse *GetUrl(string urlString);
	CHTTPResponse *Post(string url,string contentType,string data);
	CHTTPResponse *PostForm(string url,string data);

	void GetResultFromUrl(const std::string strUrl);
	CHTTPResponse* GetUrlResult() { return m_pResult; }
};
