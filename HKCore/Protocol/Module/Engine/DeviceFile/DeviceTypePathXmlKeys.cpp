#include "StdAfx.h"
#include "DeviceTypePathXmlKeys.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDeviceTypePathXmlKeys::CDeviceTypePathXmlKeys(void)
{
	m_strDevice = L"devicetype";
	m_strPath = L"devicetypepath";
	m_strName = L"name";
	m_strDeviceModelFile = L"device-file";
	m_strTemplateFile = L"template-file";
	m_strRoot = L"devicetyperoot";

}

CDeviceTypePathXmlKeys::~CDeviceTypePathXmlKeys(void)
{
}


CDeviceTypePathXmlKeys* CDeviceTypePathXmlKeys::g_pXmlRWKeys = NULL;
long CDeviceTypePathXmlKeys::g_nDeviceTypathRef = 0;


CDeviceTypePathXmlKeys* CDeviceTypePathXmlKeys::Create()
{
	if (g_pXmlRWKeys == NULL)
	{
		g_pXmlRWKeys = new CDeviceTypePathXmlKeys();
	}

	g_nDeviceTypathRef++;

	return g_pXmlRWKeys;
}

void CDeviceTypePathXmlKeys::Release()
{
	g_nDeviceTypathRef--;

	if (g_nDeviceTypathRef == 0)
	{
		delete g_pXmlRWKeys;
		g_pXmlRWKeys = NULL;
	}
}
