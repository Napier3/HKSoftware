#pragma once
#include "../MqttCmmInterface.h"
#include "../../../SttStudio/Module/Engine/SttEngineInterface.h"


class CMqttEngineBase:public CSttEngineInterface
{
public:
	CMqttEngineBase();
	virtual ~CMqttEngineBase();

public:
	CString m_strIP;
	long m_nPort;

	//用于传递主题源端信息
	//2021-8-22 lijunqing 这种方式有极大的缺陷，就是如果两个请求端先后发送命令
	//收到命令的时候，后面的请求端ID会覆盖前面的请求端ID，所以去掉这个部分
// 	CString m_strFirstTopic;
// 	CString m_strSecondTopic;
// 	void InitTopicSrcInfo(const CString &strFirst,const CString &strSecond);
};