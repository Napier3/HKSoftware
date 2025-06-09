//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

#pragma once

#include "../Evx/AtsSvrServiceEvx.h"
#include "../AtsSvrServiceAppBase.h"

class CAtsSvrServiceAppEvx : public CAtsSvrServiceAppBase
{
private:
	CAtsSvrServiceAppEvx();
	virtual ~CAtsSvrServiceAppEvx();

	static long g_nAtsSvrServiceAppEvxRef;
	static CAtsSvrServiceAppEvx *g_pAtsSvrServiceAppEvx;

public:
	static CAtsSvrServiceAppEvx* Create();
	static void Release();
	static CAtsSvrServiceAppEvx* GetApplication();

	static CAtsSvrServiceBase* GetAtsSvrService();
	static CAtsSvrServiceBase* GetAtsSvrService(const CString &strSN);
	static CAtsSvrServiceBase* GetAtsSvrService(long nIndex);
	static CXSttSmartTestXInterface* FindSmartTestXInterface(const CString &strDeviceSN);

public:
	virtual void InitAtsSvrServiceApp();
	virtual void ExitAtsSvrServiceApp();
	virtual CAtsSvrServiceBase* NewAtsSvrService();

};

