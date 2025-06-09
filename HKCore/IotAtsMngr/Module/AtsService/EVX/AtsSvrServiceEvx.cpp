//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AtsSvrServiceEvx.cpp  CAtsSvrServiceEvx


#include "stdafx.h"
#include "AtsSvrServiceEvx.h"
#include "AtsSvrTestFlowsEvx.h"

CAtsSvrServiceEvx::CAtsSvrServiceEvx()
{
	
}

CAtsSvrServiceEvx::~CAtsSvrServiceEvx()
{
	
}

CAtsSvrTestFlows* CAtsSvrServiceEvx::NewAtsSvrTestFlows()
{
	return new CAtsSvrTestFlowsEvx();
}


BOOL CAtsSvrServiceEvx::MqttSubscribeTopic()
{
	CAtsSvrServiceBase::MqttSubscribeTopic();

	CString strTopic ;

	strTopic = _T("+/AtsState/EVENT/ExportReport");
	g_theSttOutMqttClient->SubscribeTopic(strTopic, 0);
	strTopic = _T("+/AtsState/EVENT/TestStarted");
	g_theSttOutMqttClient->SubscribeTopic(strTopic, 0);
	strTopic = _T("+/AtsState/EVENT/TestStoped");
	g_theSttOutMqttClient->SubscribeTopic(strTopic, 0);
	strTopic = _T("+/AtsState/EVENT/TestFinished");
	g_theSttOutMqttClient->SubscribeTopic(strTopic, 0);

	strTopic = _T("+/+/AtsState/EVENT/ExportReport");
	g_theSttOutMqttClient->SubscribeTopic(strTopic, 0);
	strTopic = _T("+/+/AtsState/EVENT/TestStarted");
	g_theSttOutMqttClient->SubscribeTopic(strTopic, 0);
	strTopic = _T("+/+/AtsState/EVENT/TestStoped");
	g_theSttOutMqttClient->SubscribeTopic(strTopic, 0);
	strTopic = _T("+/+/AtsState/EVENT/TestFinished");
	g_theSttOutMqttClient->SubscribeTopic(strTopic, 0);

	return TRUE;
}

//����ExportFinish������ʵ��˫ǹ��������ʱ��Ҫ�ϲ�����
BOOL CAtsSvrServiceEvx::MqttUnSubscribeTopic() 
{
	CAtsSvrServiceBase::MqttUnSubscribeTopic();

	CString strTopic ;

	strTopic = _T("+/AtsState/EVENT/ExportReport");
	g_theSttOutMqttClient->SubscribeTopic(strTopic, 0);

	strTopic = _T("+/+/AtsState/EVENT/ExportReport");
	g_theSttOutMqttClient->SubscribeTopic(strTopic, 0);

	return FALSE;
}
