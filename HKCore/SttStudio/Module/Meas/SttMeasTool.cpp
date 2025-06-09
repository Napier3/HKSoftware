//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMeasTool.cpp  CSttMeasTool


#include "stdafx.h"
#include "SttMeasTool.h"

#include "..\..\..\Module\API\FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long CSttMeasTool::g_nSttMeasToolRef = 0;
CSttMeasTool* CSttMeasTool::g_pSttMeasTool = NULL;


CSttMeasTool::CSttMeasTool()
{
	CMacroXmlKeys::Create();//2021-9-22 lijunqing
	CSttMesLocalDb::Create();
	CTestMacroXmlRWKeys::Create();
	
	m_pMeasustTestMacros = new CTestMacros();
	CString strFile;
	strFile = _P_GetInstallPath();
	strFile += _T("e-Report\\Config\\MeasustTest\\");
	strFile += _T("MeasustTestMacro.xml");
	m_pMeasustTestMacros->OpenTestMacroFile(strFile, _T("Measust"));

	m_pSttMeasTestClient = NULL;
}

CSttMeasTool::~CSttMeasTool()
{
	CSttMesLocalDb::Release();
	CTestMacroXmlRWKeys::Release();
	CMacroXmlKeys::Release(); //2021-9-22 lijunqing

	delete m_pMeasustTestMacros;
	delete m_pSttMeasTestClient;
	
}

CSttMeasTool* CSttMeasTool::Create()
{
	g_nSttMeasToolRef++;

	if (g_nSttMeasToolRef == 1)
	{
		g_pSttMeasTool = new CSttMeasTool();
		g_pSttMeasTool->GetSttMeasustTestClient();
	}

	return g_pSttMeasTool;
}

CSttMeasTool* CSttMeasTool::GetMeasTool()
{
	return g_pSttMeasTool;
}

void CSttMeasTool::Release()
{
	g_nSttMeasToolRef--;

	if (g_nSttMeasToolRef == 0)
	{
		delete g_pSttMeasTool;
		g_pSttMeasTool = NULL;
	}
}

CSttMeasDevice* CSttMeasTool::FindMeasDevice(const CString &strFile)
{
	CSttMeasDevice *pFind = (CSttMeasDevice*)g_pSttMeasTool->FindByID(strFile);

	return pFind;
}

CSttMeasDevice* CSttMeasTool::CreateNewMeasDevice(CDataGroup *pDevice)
{
	if (g_pSttMeasTool == NULL)
	{
		return NULL;
	}

	return g_pSttMeasTool->In_CreateNewMeasDevice(pDevice);
}

CSttMeasDevice* CSttMeasTool::In_CreateNewMeasDevice(CDataGroup *pDevice)
{
	CSttMeasDevice *pFind = (CSttMeasDevice*)g_pSttMeasTool->FindByID(STT_Meas_ID_EmptyDevice);

	if (pFind != NULL)
	{
		pFind->DettachMeasRef(TRUE);
	}
	else
	{
		pFind = new CSttMeasDevice();
		pFind->m_strName = _T("EmptyDevice");
		pFind->m_strID = _T("EmptyDevice");
		AddTail(pFind);
	}

	pFind->AttatchMeasRef(pDevice, TRUE);
	return pFind;
}

CSttMeasDevice* CSttMeasTool::OpenMeasFile(const CString &strFile)
{
	if (g_pSttMeasTool == NULL)
	{
		return NULL;
	}

	return g_pSttMeasTool->In_OpenMeasFile(strFile);
}

CSttMeasDevice* CSttMeasTool::In_OpenMeasFile(const CString &strFile)
{
	CString strTemp;
	strTemp = strFile;
	strTemp.MakeLower();

	CSttMeasDevice *pFind = (CSttMeasDevice*)g_pSttMeasTool->FindByID(strTemp);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = new CSttMeasDevice();
	
	if (!pFind->OpenSttMeasFile(strTemp))
	{
		delete pFind;
		return NULL;
	}

	pFind->m_strID = strTemp;
	pFind->m_strName = GetPathFileNameFromFilePathName(strFile);
	g_pSttMeasTool->AddTail(pFind);

	return pFind;
}

CSttMeasustTestClient* CSttMeasTool::GetSttMeasustTestClient()
{
	ASSERT (g_pSttMeasTool != NULL);

	if (g_pSttMeasTool->m_pSttMeasTestClient == NULL)
	{
		g_pSttMeasTool->m_pSttMeasTestClient = new CSttMeasustTestClient();
		g_pSttMeasTool->m_pSttMeasTestClient->InitTestMacros(g_pSttMeasTool->m_pMeasustTestMacros);
	}

	return g_pSttMeasTool->m_pSttMeasTestClient;
}

void CSttMeasTool::CloseMeasDeviceFile(CExBaseObject *pMeasDevice)
{
	if (g_pSttMeasTool == NULL)
	{
		return;
	}

	g_pSttMeasTool->Delete(pMeasDevice);
}

BOOL CSttMeasTool::IsConnectSuccess()
{
	if (g_pSttMeasTool == NULL)
	{
		return FALSE;
	}

	if (g_pSttMeasTool->m_pSttMeasTestClient == NULL)
	{
		return FALSE;
	}

	return g_pSttMeasTool->m_pSttMeasTestClient->IsConnectSuccess();
}
