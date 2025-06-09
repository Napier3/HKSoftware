//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

#pragma once

#include "AtsSvrServiceBase.h"

#include "../SttMqttClientTool.h"
#include "../Iot_AtsMngrDB/Iot_Bench.h"

class CAtsSvrServiceAppBase : public CExBaseList
{
public:
	CAtsSvrServiceAppBase();
	virtual ~CAtsSvrServiceAppBase();

	CIot_Benchs* m_pIotBenchs;

public:
	virtual void InitAtsSvrServiceApp();
	virtual void ExitAtsSvrServiceApp();
	virtual CAtsSvrServiceBase* NewAtsSvrService();

public:
	CAtsSvrServiceBase* XGetAtsSvrService();
	CAtsSvrServiceBase* XGetAtsSvrService(const CString &strSN);
	CAtsSvrServiceBase* XGetAtsSvrService(long nIndex);
	CXSttSmartTestXInterface* XFindSmartTestXInterface(const CString &strDeviceSN);

public:
	virtual void InitAtsSvrService();
	virtual void InitAtsSvrService(const CString &strFile);
	virtual void SaveAtsSvrService();
};

