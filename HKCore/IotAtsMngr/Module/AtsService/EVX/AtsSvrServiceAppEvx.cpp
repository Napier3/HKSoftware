//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

#include "stdafx.h"
#include "AtsSvrServiceAppEvx.h"
#include "../../SttMqttClientEngineConfig.h"
#include "../../../../Module/XFileHttpClient/XFileHttpClient.h"

long CAtsSvrServiceAppEvx::g_nAtsSvrServiceAppEvxRef = 0;
CAtsSvrServiceAppEvx* CAtsSvrServiceAppEvx::g_pAtsSvrServiceAppEvx = NULL;

CAtsSvrServiceAppEvx::CAtsSvrServiceAppEvx()
{
	
}

CAtsSvrServiceAppEvx::~CAtsSvrServiceAppEvx()
{
	
}

CAtsSvrServiceAppEvx* CAtsSvrServiceAppEvx::Create()
{
	g_nAtsSvrServiceAppEvxRef++;

	if (g_nAtsSvrServiceAppEvxRef == 1)
	{
		g_pAtsSvrServiceAppEvx = new CAtsSvrServiceAppEvx();
		g_pAtsSvrServiceAppEvx->InitAtsSvrServiceApp();
		g_pAtsSvrServiceAppEvx->InitAtsSvrService();
	}

	return g_pAtsSvrServiceAppEvx;
}

void CAtsSvrServiceAppEvx::Release()
{
	g_nAtsSvrServiceAppEvxRef--;

	if (g_nAtsSvrServiceAppEvxRef == 0)
	{
		g_pAtsSvrServiceAppEvx->ExitAtsSvrServiceApp();
		delete g_pAtsSvrServiceAppEvx;
		g_pAtsSvrServiceAppEvx = NULL;
	}
}

CAtsSvrServiceAppEvx* CAtsSvrServiceAppEvx::GetApplication()
{
	return g_pAtsSvrServiceAppEvx;
}

CAtsSvrServiceBase* CAtsSvrServiceAppEvx::GetAtsSvrService()
{
	return g_pAtsSvrServiceAppEvx->XGetAtsSvrService();
}

CAtsSvrServiceBase* CAtsSvrServiceAppEvx::GetAtsSvrService(const CString &strSN)
{
	return g_pAtsSvrServiceAppEvx->XGetAtsSvrService(strSN);
}

CAtsSvrServiceBase* CAtsSvrServiceAppEvx::GetAtsSvrService(long nIndex)
{
	return g_pAtsSvrServiceAppEvx->XGetAtsSvrService(nIndex);
}

CXSttSmartTestXInterface* CAtsSvrServiceAppEvx::FindSmartTestXInterface(const CString &strDeviceSN)
{
	return g_pAtsSvrServiceAppEvx->XFindSmartTestXInterface(strDeviceSN);
}


//////////////////////////////////////////////////////////////////////////
//

void CAtsSvrServiceAppEvx::InitAtsSvrServiceApp()
{
	CAtsSvrServiceAppBase::InitAtsSvrServiceApp();

}

void CAtsSvrServiceAppEvx::ExitAtsSvrServiceApp()
{
	CAtsSvrServiceAppBase::ExitAtsSvrServiceApp();
}

CAtsSvrServiceBase* CAtsSvrServiceAppEvx::NewAtsSvrService()
{
	return new CAtsSvrServiceEvx();
}
