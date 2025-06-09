//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

//订阅ExportFinish，用于实现双枪导出报告时需要合并报告
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
