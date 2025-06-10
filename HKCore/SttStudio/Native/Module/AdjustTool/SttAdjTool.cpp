//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttAdjTool.cpp  CSttAdjTool


#include "stdafx.h"
#include "SttAdjTool.h"

#include "..\..\..\Module\API\FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long CSttAdjTool::g_nSttAdjToolRef = 0;
CSttAdjTool* CSttAdjTool::g_pSttAdjTool = NULL;


CSttAdjTool::CSttAdjTool()
{
	CMacroXmlKeys::Create();//2021-9-22 lijunqing
	CSttMesLocalDb::Create();
	CTestMacroXmlRWKeys::Create();
	
	m_pAdjustTestMacros = new CTestMacros();
	CString strFile;
	strFile = _P_GetInstallPath();
	strFile += _T("e-Report\\Config\\AdjustTest\\");
	strFile += _T("AdjustTestMacro.xml");
	m_pAdjustTestMacros->OpenTestMacroFile(strFile, _T("Adjust"));

	m_pSttAdjTestClient = NULL;
}

CSttAdjTool::~CSttAdjTool()
{
	CSttMesLocalDb::Release();
	CTestMacroXmlRWKeys::Release();
	CMacroXmlKeys::Release(); //2021-9-22 lijunqing

	delete m_pAdjustTestMacros;
	delete m_pSttAdjTestClient;
	
}

CSttAdjTool* CSttAdjTool::Create()
{
	g_nSttAdjToolRef++;

	if (g_nSttAdjToolRef == 1)
	{
		g_pSttAdjTool = new CSttAdjTool();
		g_pSttAdjTool->GetSttAdjustTestClient();
	}

	return g_pSttAdjTool;
}

CSttAdjTool* CSttAdjTool::GetAdjTool()
{
	return g_pSttAdjTool;
}

void CSttAdjTool::Release()
{
	g_nSttAdjToolRef--;

	if (g_nSttAdjToolRef == 0)
	{
		delete g_pSttAdjTool;
		g_pSttAdjTool = NULL;
	}
}

CSttAdjDevice* CSttAdjTool::FindAdjDevice(const CString &strFile)
{
	CSttAdjDevice *pFind = (CSttAdjDevice*)g_pSttAdjTool->FindByID(strFile);

	return pFind;
}

CSttAdjDevice* CSttAdjTool::CreateNewAdjDevice(CDataGroup *pDevice)
{
	if (g_pSttAdjTool == NULL)
	{
		return NULL;
	}

	return g_pSttAdjTool->In_CreateNewAdjDevice(pDevice);
}

CSttAdjDevice* CSttAdjTool::In_CreateNewAdjDevice(CDataGroup *pDevice)
{
	CSttAdjDevice *pFind = (CSttAdjDevice*)g_pSttAdjTool->FindByID(STT_ADJ_ID_EmptyDevice);

	if (pFind != NULL)
	{
		pFind->DettachAdjRef(TRUE);
	}
	else
	{
		pFind = new CSttAdjDevice();
		pFind->m_strName = _T("EmptyDevice");
		pFind->m_strID = _T("EmptyDevice");
		AddTail(pFind);
	}

	pFind->AttatchAdjRef(pDevice, TRUE);
	return pFind;
}

CSttAdjDevice* CSttAdjTool::OpenAdjFile(const CString &strFile)
{
	if (g_pSttAdjTool == NULL)
	{
		return NULL;
	}

	return g_pSttAdjTool->In_OpenAdjFile(strFile);
}

CSttAdjDevice* CSttAdjTool::In_OpenAdjFile(const CString &strFile)
{
	CString strTemp;
	strTemp = strFile;
	strTemp.MakeLower();

	CSttAdjDevice *pFind = (CSttAdjDevice*)g_pSttAdjTool->FindByID(strTemp);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = new CSttAdjDevice();
	
	if (!pFind->OpenSttAdjFile(strTemp))
	{
		delete pFind;
		return NULL;
	}

	pFind->m_strID = strTemp;
	pFind->m_strName = GetPathFileNameFromFilePathName(strFile);
	g_pSttAdjTool->AddTail(pFind);

	return pFind;
}

CSttAdjustTestClient* CSttAdjTool::GetSttAdjustTestClient()
{
	ASSERT (g_pSttAdjTool != NULL);

	if (g_pSttAdjTool->m_pSttAdjTestClient == NULL)
	{
		g_pSttAdjTool->m_pSttAdjTestClient = new CSttAdjustTestClient();
		g_pSttAdjTool->m_pSttAdjTestClient->InitTestMacros(g_pSttAdjTool->m_pAdjustTestMacros);
	}

	return g_pSttAdjTool->m_pSttAdjTestClient;
}

void CSttAdjTool::CloseAdjDeviceFile(CExBaseObject *pAdjDevice)
{
	if (g_pSttAdjTool == NULL)
	{
		return;
	}

	g_pSttAdjTool->Delete(pAdjDevice);
}

BOOL CSttAdjTool::IsConnectSuccess()
{
	if (g_pSttAdjTool == NULL)
	{
		return FALSE;
	}

	if (g_pSttAdjTool->m_pSttAdjTestClient == NULL)
	{
		return FALSE;
	}

	return g_pSttAdjTool->m_pSttAdjTestClient->IsConnectSuccess();
}
