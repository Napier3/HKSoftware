#include "XHttpclient.h"

CHTTPClient::CHTTPClient()
{
	init(0);
	m_critSec = new CCritSec;
	m_pResult = 0;
}

CHTTPClient::CHTTPClient(int keepalive)
{
	init(keepalive);
	m_pResult = 0;
}

void CHTTPClient::init(int keepalive){
	//pthread_mutex_init(&m_mutex,NULL);
	curl_global_init(CURL_GLOBAL_DEFAULT);
	m_curl = curl_easy_init();
	curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1L); //禁止产生信号
	//https证书忽略
	curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0L);
	//返回数据写入句柄
	//curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, HTTPClient::writer);
	if(keepalive==1){
		curl_easy_setopt(m_curl,CURLOPT_TIMEOUT,0L);
		curl_easy_setopt(m_curl,CURLOPT_TCP_KEEPALIVE, 1L);
		curl_easy_setopt(m_curl,CURLOPT_TCP_KEEPIDLE, 120L);
		curl_easy_setopt(m_curl,CURLOPT_TCP_KEEPINTVL, 60L);
	}else{
		curl_easy_setopt(m_curl,CURLOPT_TIMEOUT,45L);
		curl_easy_setopt(m_curl,CURLOPT_FORBID_REUSE, 1L);
	}
}


CHTTPClient::~CHTTPClient()
{
	//pthread_mutex_destroy(&m_mutex); 
	curl_global_cleanup();
	if(m_pResult)
	{
		delete m_pResult;
		m_pResult = 0;
	}
}
CHTTPResponse *CHTTPClient::Get(string httpHead,string httpIp,long httpPort)
{
	m_critSec->Enter();
	std::string url;
	std::string strPort;
	stringstream stream;
	stream << httpPort;
	stream >> strPort;
	url.append(httpIp);
	url.append(":");
	url.append(strPort);


	CHTTPResponse *resp = new CHTTPResponse();
	resp->code=200;
	resp->buff.clear();
	struct curl_slist *http_header = NULL;
	http_header = curl_slist_append(http_header, "Accept: *");
	http_header = curl_slist_append(http_header, "User-Agent: HB-HTTPCLI");
	curl_easy_setopt(m_curl,CURLOPT_URL,url.c_str());
	curl_easy_setopt(m_curl,CURLOPT_HTTPHEADER, http_header);//设置HTTP HEADER
	curl_easy_setopt(m_curl,CURLOPT_WRITEDATA, &resp->buff);
	CURLcode code = curl_easy_perform(m_curl);
	if(code !=CURLE_OK)
	{
		resp->code = code;
	}
	curl_slist_free_all(http_header);//http_header需要释放
	m_critSec->Leave();
	return resp;
}

CHTTPResponse *CHTTPClient::GetUrl(string urlString)
{
	CHTTPResponse *resp = new CHTTPResponse();
	resp->code=200;
	resp->buff.clear();
	struct curl_slist *http_header = NULL;
	http_header = curl_slist_append(http_header, "Accept: *");
	http_header = curl_slist_append(http_header, "User-Agent: HB-HTTPCLI");
	curl_easy_setopt(m_curl,CURLOPT_URL,urlString.c_str());
	curl_easy_setopt(m_curl,CURLOPT_HTTPHEADER, http_header);//设置HTTP HEADER
	curl_easy_setopt(m_curl,CURLOPT_WRITEDATA, &resp->buff);
	CURLcode code = curl_easy_perform(m_curl);
	if(code !=CURLE_OK)
	{
		resp->code = code;
	}
	curl_slist_free_all(http_header);//http_header需要释放
	m_critSec->Leave();
	return resp;

}

size_t GetFromUrl(void *buffer, size_t size, size_t nmemb, void *user)
{
	//返回的字符串
	user = buffer;
	return size * nmemb;
}

size_t read(void *buffer, size_t size, size_t nmemb, void *user)
{
	//返回的字符串
	memcpy(user, buffer, size * nmemb);
	return size * nmemb;
}

void CHTTPClient::GetResultFromUrl(const std::string strUrl)
{
	if(!m_pResult)
	{
		m_pResult = new CHTTPResponse;
	}

	char* url = const_cast<char*>(strUrl.c_str());
	CURL* curl;
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &m_pResult->m_strBuffer);
	CURLcode urlCode = curl_easy_perform(curl);
	m_pResult->code = urlCode;
	curl_easy_cleanup(curl);
}

CHTTPResponse *CHTTPClient::Post(std::string url, std::string contentType, std::string data)
{
	//pthread_mutex_lock(&m_mutex);
	m_critSec->Enter();
	CHTTPResponse *resp = new CHTTPResponse();
	resp->code=200;

	struct curl_slist *http_header = NULL;
	http_header = curl_slist_append(http_header, "Accept: *");
	string tp=string("Content-Type: ")+contentType;
	http_header = curl_slist_append(http_header, tp.c_str());
	http_header = curl_slist_append(http_header, "Charset: utf-8");
	http_header = curl_slist_append(http_header, "User-Agent: HB-HTTPCLI");

	curl_easy_setopt(m_curl,CURLOPT_URL,url.c_str());
	curl_easy_setopt(m_curl,CURLOPT_HTTPHEADER, http_header);//设置HTTP HEADER
	curl_easy_setopt(m_curl,CURLOPT_POST,1L);
	curl_easy_setopt(m_curl,CURLOPT_POSTFIELDS, data.c_str());

	curl_easy_setopt(m_curl,CURLOPT_WRITEDATA, &resp->buff);
	CURLcode code = curl_easy_perform(m_curl);
	if(code !=CURLE_OK)
	{
		resp->code = code;
	}
	curl_slist_free_all(http_header);//http_header需要释放
	m_critSec->Leave();
	return resp;
}

CHTTPResponse *CHTTPClient::PostForm(std::string url, std::string data)
{
	m_critSec->Enter();
	CHTTPResponse *resp = new CHTTPResponse();
	resp->code=200;

	struct curl_slist *http_header = NULL;
	http_header = curl_slist_append(http_header, "Accept: *");
	http_header = curl_slist_append(http_header, "application/x-www-form-urlencoded");
	http_header = curl_slist_append(http_header, "Charset: utf-8");
	http_header = curl_slist_append(http_header, "User-Agent: HB-HTTPCLI");

	curl_easy_setopt(m_curl,CURLOPT_URL,url.c_str());
	curl_easy_setopt(m_curl,CURLOPT_HTTPHEADER, http_header);//设置HTTP HEADER
	curl_easy_setopt(m_curl,CURLOPT_POST,1L);
	curl_easy_setopt(m_curl,CURLOPT_POSTFIELDS, data.c_str());
	curl_easy_setopt(m_curl,CURLOPT_WRITEDATA, &resp->buff);
	CURLcode code = curl_easy_perform(m_curl);
	if(code !=CURLE_OK)
	{
		resp->code = code;
	}
	curl_slist_free_all(http_header);//http_header需要释放
	//pthread_mutex_unlock(&m_mutex);
	m_critSec->Leave();
	return resp;
}

int CHTTPClient::writer(char *data, size_t size, size_t nmemb,std::string *writerData)
{
	if(writerData == NULL)
		return 0;

	writerData->append(data, size*nmemb);

	return size * nmemb;
}
