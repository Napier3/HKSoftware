#ifndef _PxCmmInterface_h_
#define _PxCmmInterface_h_

#define MQTT_QOS_DEFAULT         0
#define MQTT_TIMEOUT_DEFAULT     2000L 

//Э��ͨ�Žӿ�

//ͨ����Ϣ�ӿ�
class CPxCmmMsgInterface
{
public:
	virtual void OnRecieve(char *pBuf,long nLen,long nCmdType, char *pszCmdID, char *pszRetType)=0;
	virtual void OnClose(char *pszErr)=0;
};

//ͨ�Žӿ�
class CPxCmmInterface
{
public:
	virtual long Send(char *pBuf,long nLen,long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)=0;
	virtual long Send(LPVOID pCmdBase)=0;
	virtual BOOL Connect(const char *pszIP,long nPort)=0;
	virtual void Disconnect()=0;	
};

//Mqtt�¼��ӿ�
class CSttMqttMsgInterface
{
public:
	virtual void OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen) = 0;
	virtual void OnMqttDisconnected(char *pszErr) = 0;
};

#endif

