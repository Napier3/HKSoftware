#pragma once

#include "IotSmartTestCtrlMngr.h"

class CSmartTestCtrlServerBaseApp : public CSttMqttMsgInterface
{
public:
	CSmartTestCtrlServerBaseApp();
	virtual ~CSmartTestCtrlServerBaseApp();

	//自动测试控制管理对象
	CIotSmartTestCtrlMngr m_oIotSmartTestCtrlMngr;

	//mqtt接口
public:
	virtual void OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen);
	virtual void OnMqttDisconnected(char *pszErr);

public:
	void InitSmartTestCtrlServerBaseApp();
	void ExitSmartTestCtrlServerBaseApp();

	//启动后需要订阅的主题
	BOOL SubcribeMqttTopic(int nQos);
	BOOL ConnectMqttServer();
};

BOOL HasSubString(CStringTokenizer &oToken,const CString &strSub);
BOOL IsAtsTopic(CStringTokenizer &oTopicToken);
BOOL IsTestTopic(CStringTokenizer &oTopicToken);