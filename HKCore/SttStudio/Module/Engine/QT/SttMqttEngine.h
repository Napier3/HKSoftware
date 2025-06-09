#pragma once

#include "SttMqttEngineBase.h"

class CSttMqttEngine:public CSttMqttEngineBase
{
public:
	CSttMqttEngine();
	virtual ~CSttMqttEngine();

public:
	void PublicTopic(CSttMqttTopicCmbn &oTopicCmbn, CSttParas &oParas);
	void PublicTopic2(CSttMqttTopicCmbn &oTopicCmbn, CSttParas &oParas);
	void ConnectMqttSvr(CString strIP,long nPort,const CString &strUser,const CString &strPwd,BOOL bAuthority = FALSE);

	//主题处理
	virtual void OnStartTest(CSttMqttTopicParser &oSttMqttTopicParser);
	virtual void OnStopTest(CSttMqttTopicParser &oSttMqttTopicParser);

};
