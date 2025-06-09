#ifndef _MQTT_SERVER_FUNC_
#define _MQTT_SERVER_FUNC_


//存在id、name等，可以替换成ExBase

class CMosquittoClient : public CExBaseObject
{
public:
	//m_strName - 客户端IP
	//m_strID - 客户端名称

	CExBaseList m_oTopics;

public:
	CMosquittoClient();
	virtual ~CMosquittoClient();

};

#endif