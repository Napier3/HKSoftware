#include "stdafx.h"
#include "GbWzdItemsNameLib.h"
#include "../../../../Module/API/GlobalConfigApi.h"

long CGbWzdItemsNameLib::g_nGbWzdItemsNameLibRef = 0;
CGbWzdItemsNameLib* CGbWzdItemsNameLib::g_pGbWzdItemsNameLib = NULL;

CGbWzdItemsNameLib::CGbWzdItemsNameLib(void)
{
	
}

CGbWzdItemsNameLib::~CGbWzdItemsNameLib(void)
{

}

void CGbWzdItemsNameLib::InitAfterRead()
{
	m_pDeviceTypeDef = (CDataGroup*)FindByID(_T("DeviceTypeDef"));
}

void CGbWzdItemsNameLib::OpenLibFile()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("ItemsNameLib.xml");

	OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}


CGbWzdItemsNameLib* CGbWzdItemsNameLib::Create()
{
	g_nGbWzdItemsNameLibRef++;

	if (g_nGbWzdItemsNameLibRef == 1)
	{
		g_pGbWzdItemsNameLib = new CGbWzdItemsNameLib();
		g_pGbWzdItemsNameLib->OpenLibFile();
	}

	return g_pGbWzdItemsNameLib;
}

void CGbWzdItemsNameLib::Release()
{
	g_nGbWzdItemsNameLibRef--;

	if (g_nGbWzdItemsNameLibRef == 0)
	{
		delete g_pGbWzdItemsNameLib;
		g_pGbWzdItemsNameLib = NULL;
	}
}

CDataGroup* CGbWzdItemsNameLib::GetDeviceTypeDef()
{
	return g_pGbWzdItemsNameLib->m_pDeviceTypeDef;
}

CDataGroup* CGbWzdItemsNameLib::FindDeviceTypeLib(const CString &strDeviceTypeID)
{
	return (CDataGroup*)g_pGbWzdItemsNameLib->FindByID(strDeviceTypeID);
}

