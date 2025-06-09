#include "stdafx.h"
#include "AtsMngrInterface.h"

CAtsMngrInterface *CAtsMngrInterface::g_pAtsMngrInterface = NULL;
long CAtsMngrInterface::g_nInterfaceRef = 0;

CAtsMngrInterface::CAtsMngrInterface()
{

}

CAtsMngrInterface::~CAtsMngrInterface()
{

}

CAtsMngrInterface *CAtsMngrInterface::Create()
{
	g_nInterfaceRef++;

	if (g_nInterfaceRef == 1)
	{
		g_pAtsMngrInterface = new CAtsMngrInterface();
	}

	return g_pAtsMngrInterface;
}

void CAtsMngrInterface::Release()
{
	g_nInterfaceRef--;

	if (g_nInterfaceRef == 0)
	{
		g_pAtsMngrInterface->OnRelease();

		delete g_pAtsMngrInterface;
		g_pAtsMngrInterface = NULL;
	}
}

void CAtsMngrInterface::OnRelease()
{
	if (g_pAtsMngrInterface == NULL)
	{
		return;
	}

	m_oXAtsEngine = NULL;
}

BOOL CAtsMngrInterface::InitAtsMngrInterface()
{
	if (m_oXAtsEngine == NULL)
	{
		m_oXAtsEngine.CreateDispatch(_T("MqttClientEngine.PoEngine"));

		if (m_oXAtsEngine == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("MQTT客户端com接口初始化失败"));
		}
	}

	return (m_oXAtsEngine != NULL);
}

long CAtsMngrInterface::CreateDevice(const CString &strTemplateFile,const CString &strDeviceFile,const CString &strDeviceID)
{
	if (g_pAtsMngrInterface == NULL)
	{
		ASSERT (FALSE);
		return 0;
	}

	if (!g_pAtsMngrInterface->InitAtsMngrInterface())
	{
		return 0;
	}

	AtsMngrInterface::CPoDevice oXAtsDevice = g_pAtsMngrInterface->m_oXAtsEngine.CreateDevice(strTemplateFile,strDeviceFile,strDeviceID);

	if (oXAtsDevice == NULL)
	{
		return 0;
	}

	return 1;
}