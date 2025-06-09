//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

