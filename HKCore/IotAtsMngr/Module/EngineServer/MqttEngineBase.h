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

	//���ڴ�������Դ����Ϣ
	//2021-8-22 lijunqing ���ַ�ʽ�м����ȱ�ݣ������������������Ⱥ�������
	//�յ������ʱ�򣬺���������ID�Ḳ��ǰ��������ID������ȥ���������
// 	CString m_strFirstTopic;
// 	CString m_strSecondTopic;
// 	void InitTopicSrcInfo(const CString &strFirst,const CString &strSecond);
};