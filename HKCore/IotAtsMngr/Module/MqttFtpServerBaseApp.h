#pragma once
#include "SttMqttClientTool.h"
#include "MqttFtpMngr/MqttFileOptrMngr.h"

class CMqttFtpServerBaseApp : public CMqttMsgInterface
{
public:
	CMqttFtpServerBaseApp();
	virtual ~CMqttFtpServerBaseApp();

	CString m_strLocalID;
	CMqttFileOptrMngr m_oMqttFileOptrMngr;

	//mqtt�ӿ�
public:
	virtual void OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen);
	virtual void OnMqttDisconnected(char *pszErr);

public:
	void InitMqttFtpServerBaseApp();
	void ExitMqttFtpServerBaseApp();

	//��������Ҫ���ĵ�����
	BOOL SubcribeMqttTopic(int nQos);
	BOOL ConnectMqttServer();
};