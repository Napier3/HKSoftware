//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AtsSvrService.h  CAtsSvrService

#pragma once

#include "AtsSvrService.h"

#include "AtsSvrServiceAppBase.h"

class CAtsSvrServiceAppLocal : public CAtsSvrServiceAppBase
{
private:
	CAtsSvrServiceAppLocal();
	virtual ~CAtsSvrServiceAppLocal();

	static long g_nAtsSvrServiceAppLocalRef;
	static CAtsSvrServiceAppLocal *g_pAtsSvrServiceAppLocal;

public:
	static CAtsSvrServiceAppLocal* Create();
	static void Release();
	static CAtsSvrServiceAppLocal* GetApplication();

	static CAtsSvrServiceBase* GetAtsSvrService();
	static CAtsSvrServiceBase* GetAtsSvrService(const CString &strSN);
	static CAtsSvrServiceBase* GetAtsSvrService(long nIndex);
	static CXSttSmartTestXInterface* FindSmartTestXInterface(const CString &strDeviceSN);

public:
	virtual void InitAtsSvrServiceApp();
	virtual void ExitAtsSvrServiceApp();
};

