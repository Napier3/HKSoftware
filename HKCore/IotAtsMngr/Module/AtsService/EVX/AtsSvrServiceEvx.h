//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AtsSvrServiceEvx.h  CAtsSvrServiceEvx

#pragma once

#include "../AtsSvrServiceBase.h"

class CAtsSvrServiceEvx : public CAtsSvrServiceBase
{
public:
	CAtsSvrServiceEvx();
	virtual ~CAtsSvrServiceEvx();

	virtual CAtsSvrTestFlows* NewAtsSvrTestFlows();

//CMqttMsgProcessInterface
public:
	virtual BOOL MqttSubscribeTopic();
	virtual BOOL MqttUnSubscribeTopic() ;

};

