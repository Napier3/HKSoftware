#pragma once

#include "IotSmartTestCtrlMngr.h"

class CSmartTestCtrlServerBaseApp : public CSttMqttMsgInterface
{
public:
	CSmartTestCtrlServerBaseApp();
	virtual ~CSmartTestCtrlServerBaseApp();

	//�Զ����Կ��ƹ������
	CIotSmartTestCtrlMngr m_oIotSmartTestCtrlMngr;

	//mqtt�ӿ�
public:
	virtual void OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen);
	virtual void OnMqttDisconnected(char *pszErr);

public:
	void InitSmartTestCtrlServerBaseApp();
	void ExitSmartTestCtrlServerBaseApp();

	//��������Ҫ���ĵ�����
	BOOL SubcribeMqttTopic(int nQos);
	BOOL ConnectMqttServer();
};

BOOL HasSubString(CStringTokenizer &oToken,const CString &strSub);
BOOL IsAtsTopic(CStringTokenizer &oTopicToken);
BOOL IsTestTopic(CStringTokenizer &oTopicToken);