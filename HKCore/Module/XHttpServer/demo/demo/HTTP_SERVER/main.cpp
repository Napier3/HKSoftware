#include <iostream>
#include "..\..\..\XHttpServer.h"

void CallBack(struct evhttp_request* request, void* arg)
{
	//从request对象获取请求的uri对象
	const struct evhttp_uri* pUrl = evhttp_request_get_evhttp_uri(request);
	//获取post数据
	char *pData = (char*)EVBUFFER_DATA(request->input_buffer);
	pData[request->body_size] = '\0';
	//获取path
	const char *pPath = evhttp_uri_get_path(pUrl);
	//获取get参数
	const char *pQuery = evhttp_uri_get_query(pUrl);

	printf("Server: *** pPath is [%s] and post_body = [%s] ***\n",pPath , pData);

	//返回报文
	struct evbuffer* evbuf = evbuffer_new();
	evbuffer_add_printf(evbuf, "Client: *** pPath is [%s] and post_body = [%s] ***\n",pPath , pData);
	evhttp_send_reply(request, HTTP_OK, "OK", evbuf);
	evbuffer_free(evbuf);
}

int main()
{
	CXHttpServer server;
	server.InitHttpServer("192.168.1.59", 5000);
	server.SetHttpServerCallBack("/this", CallBack);
	server.RunHttpServer();
	server.ExitHttpServer();
	return 0;
}
