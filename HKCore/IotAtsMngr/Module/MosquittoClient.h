#ifndef _MQTT_SERVER_FUNC_
#define _MQTT_SERVER_FUNC_


//����id��name�ȣ������滻��ExBase

class CMosquittoClient : public CExBaseObject
{
public:
	//m_strName - �ͻ���IP
	//m_strID - �ͻ�������

	CExBaseList m_oTopics;

public:
	CMosquittoClient();
	virtual ~CMosquittoClient();

};

#endif