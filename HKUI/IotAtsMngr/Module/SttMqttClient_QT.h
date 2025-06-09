#pragma once

/*******************************
CSttMqttClient：Mqtt客户端作为全局唯一对象类
CMqttClient：Mqtt客户端作为局部对象类
*******************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <stdlib.h>
#include <string.h>
#include <signal.h>


#include "MQTTClient_QT/MQTTClient.h"               //引用mqtt的头文件
#include "MqttCmmInterface.h"


class IPStack
{
public:
    IPStack()
    {

    }

    int Socket_error(const char* aString)
    {

        if (errno != EINTR && errno != EAGAIN && errno != EINPROGRESS && errno != EWOULDBLOCK)
        {
            if (strcmp(aString, "shutdown") != 0 || (errno != ENOTCONN && errno != ECONNRESET))
                printf("Socket error %s in %s for socket %d\n", strerror(errno), aString, mysock);
        }
        return errno;
    }

    int connect(const char* strRemote, int port)
    {
        int type = SOCK_STREAM;
        struct sockaddr_in address;
        int rc = -1;
        sa_family_t family = AF_INET;
        address.sin_port = htons(port);
        address.sin_family = family = AF_INET;
        address.sin_addr.s_addr = inet_addr(strRemote);

        mysock = socket(family, type, 0);
        if (mysock != -1)
        {
            rc = ::connect(mysock, (struct sockaddr*)&address, sizeof(address));
        }

        return rc;
    }

    int read(unsigned char* buffer, int len, int timeout_ms)
    {
        struct timeval interval = {timeout_ms / 1000, (timeout_ms % 1000) * 1000};
        if (interval.tv_sec < 0 || (interval.tv_sec == 0 && interval.tv_usec <= 0))
        {
            interval.tv_sec = 0;
            interval.tv_usec = 100;
        }

        setsockopt(mysock, SOL_SOCKET, SO_RCVTIMEO, (char *)&interval, sizeof(struct timeval));

        //printf("reading %d bytes\n", len);
        int rc = ::recv(mysock, buffer, (size_t)len, 0);
        if (rc == -1)
            Socket_error("read");
        //printf("read %d bytes\n", rc);
        return rc;
    }

    int write(unsigned char* buffer, int len, int timeout)
    {
        struct timeval tv;

        tv.tv_sec = 0;  /* 30 Secs Timeout */
        tv.tv_usec = timeout * 1000;  // Not init'ing this can cause strange errors

        setsockopt(mysock, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv,sizeof(struct timeval));
        int	rc = ::write(mysock, buffer, len);
        //printf("write rc %d\n", rc);
        return rc;
    }

    int disconnect()
    {
        return ::close(mysock);
    }

private:

    int mysock;

};


class Countdown
{
public:
    Countdown()
    {

    }

    Countdown(int ms)
    {
        countdown_ms(ms);
    }


    bool expired()
    {
        struct timeval now, res;
        gettimeofday(&now, NULL);
        timersub(&end_time, &now, &res);
        //printf("left %d ms\n", (res.tv_sec < 0) ? 0 : res.tv_sec * 1000 + res.tv_usec / 1000);
        //if (res.tv_sec > 0 || res.tv_usec > 0)
        //	printf("expired %d %d\n", res.tv_sec, res.tv_usec);
        return res.tv_sec < 0 || (res.tv_sec == 0 && res.tv_usec <= 0);
    }


    void countdown_ms(int ms)
    {
        struct timeval now;
        gettimeofday(&now, NULL);
        struct timeval interval = {ms / 1000, (ms % 1000) * 1000};
        //printf("interval %d %d\n", interval.tv_sec, interval.tv_usec);
        timeradd(&now, &interval, &end_time);
    }


    void countdown(int seconds)
    {
        struct timeval now;
        gettimeofday(&now, NULL);
        struct timeval interval = {seconds, 0};
        timeradd(&now, &interval, &end_time);
    }


    int left_ms()
    {
        struct timeval now, res;
        gettimeofday(&now, NULL);
        timersub(&end_time, &now, &res);
        //printf("left %d ms\n", (res.tv_sec < 0) ? 0 : res.tv_sec * 1000 + res.tv_usec / 1000);
        return (res.tv_sec < 0) ? 0 : res.tv_sec * 1000 + res.tv_usec / 1000;
    }

private:

    struct timeval end_time;
};

class CMqttClient
{
public:
	CMqttClient();
	virtual ~CMqttClient();
    char *m_pTopic;
    MQTT::Message m_oMqttSendBuff;

private:
    IPStack m_ipstack;
    MQTT::Client<IPStack, Countdown> *m_pMqttClient;					//具体mqtt客户端对象
    static CMqttMsgInterface *g_pMqttMsgInterface;		//mqtt事件接口
	BOOL m_bConnected;

public:
    void AttachMqttMsgInterface(CMqttMsgInterface *pInterface){g_pMqttMsgInterface = pInterface;}
	BOOL IsConnectSuccessful();

	//mqtt事件全局回调接口
	static void OnMsgArrived(MQTT::MessageData &message);
	static void OnDisconnected(void *context, char *cause);

	//mqtt客户端初始化连接断链接口
	BOOL InitMqttClient(const CString &strServerURI,const CString &strClientID,const CString &strUser,const CString &strPwd,BOOL bAuthority = FALSE);
	BOOL InitMqttClient(const CString &strIP,long nPort,const CString &strClientID,const CString &strUser,const CString &strPwd,BOOL bAuthority = FALSE);
	BOOL Disconnect(unsigned int nTimeout = 2000);

	//mqtt客户端订阅、发布和取消订阅主题接口
	BOOL PublicTopic(const char* pszTopic, char* pszData,int nDataLen, int nQos=MQTT_QOS_DEFAULT, unsigned int nTimeout=MQTT_TIMEOUT_DEFAULT);
	BOOL SubscribeTopic(const char* pszTopic,int nQos);
	BOOL UnSubscribeTopic(const char* pszTopic);

public:
    void RCV_Thread();
protected:
    void Create_MqttClient_RCV_Thread();
    CWinThread *m_pThread;

};
