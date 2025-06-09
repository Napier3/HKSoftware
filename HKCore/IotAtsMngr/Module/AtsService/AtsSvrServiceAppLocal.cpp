//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrService.cpp  CAtsSvrService


#include "stdafx.h"
#include "AtsSvrServiceAppLocal.h"
#include "../SttMqttClientEngineConfig.h"
#include "../../../Module/XFileHttpClient/XFileHttpClient.h"

long CAtsSvrServiceAppLocal::g_nAtsSvrServiceAppLocalRef = 0;
CAtsSvrServiceAppLocal* CAtsSvrServiceAppLocal::g_pAtsSvrServiceAppLocal = NULL;

CAtsSvrServiceAppLocal::CAtsSvrServiceAppLocal()
{
	
}

CAtsSvrServiceAppLocal::~CAtsSvrServiceAppLocal()
{
	
}

CAtsSvrServiceAppLocal* CAtsSvrServiceAppLocal::Create()
{
	g_nAtsSvrServiceAppLocalRef++;

	if (g_nAtsSvrServiceAppLocalRef == 1)
	{
		g_pAtsSvrServiceAppLocal = new CAtsSvrServiceAppLocal();
		g_pAtsSvrServiceAppLocal->InitAtsSvrServiceApp();
		g_pAtsSvrServiceAppLocal->InitAtsSvrService();
	}

	return g_pAtsSvrServiceAppLocal;
}

void CAtsSvrServiceAppLocal::Release()
{
	g_nAtsSvrServiceAppLocalRef--;

	if (g_nAtsSvrServiceAppLocalRef == 0)
	{
		g_pAtsSvrServiceAppLocal->ExitAtsSvrServiceApp();
		delete g_pAtsSvrServiceAppLocal;
		g_pAtsSvrServiceAppLocal = NULL;
	}
}

CAtsSvrServiceAppLocal* CAtsSvrServiceAppLocal::GetApplication()
{
	return g_pAtsSvrServiceAppLocal;
}

CAtsSvrServiceBase* CAtsSvrServiceAppLocal::GetAtsSvrService()
{
	return g_pAtsSvrServiceAppLocal->XGetAtsSvrService();
}

CAtsSvrServiceBase* CAtsSvrServiceAppLocal::GetAtsSvrService(const CString &strSN)
{
	return g_pAtsSvrServiceAppLocal->XGetAtsSvrService(strSN);
}

CAtsSvrServiceBase* CAtsSvrServiceAppLocal::GetAtsSvrService(long nIndex)
{
	return g_pAtsSvrServiceAppLocal->XGetAtsSvrService(nIndex);
}

CXSttSmartTestXInterface* CAtsSvrServiceAppLocal::FindSmartTestXInterface(const CString &strDeviceSN)
{
	return g_pAtsSvrServiceAppLocal->XFindSmartTestXInterface(strDeviceSN);
}


//////////////////////////////////////////////////////////////////////////
//

void CAtsSvrServiceAppLocal::InitAtsSvrServiceApp()
{
	CAtsSvrServiceAppBase::InitAtsSvrServiceApp();

}

void CAtsSvrServiceAppLocal::ExitAtsSvrServiceApp()
{
	CAtsSvrServiceAppBase::ExitAtsSvrServiceApp();
}
