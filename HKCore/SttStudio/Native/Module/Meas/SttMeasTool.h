//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMeasTool.h  CSttMeasTool

#pragma once

#include "SttMeasustTestClient.h"

class CSttMeasTool : public CExBaseList
{
private:
	CSttMeasTool();
	virtual ~CSttMeasTool();

	static long g_nSttMeasToolRef;
	static CSttMeasTool* g_pSttMeasTool;

public:
	static CSttMeasTool* Create();
	static CSttMeasTool* GetMeasTool();
	static void Release();

public:
	static CSttMeasDevice* FindMeasDevice(const CString &strFile);
	static CSttMeasDevice* CreateNewMeasDevice(CDataGroup *pDevice);
	static CSttMeasDevice* OpenMeasFile(const CString &strFile);
	static CSttMeasustTestClient* GetSttMeasustTestClient();
	static void CloseMeasDeviceFile(CExBaseObject *pMeasDevice);

	static BOOL IsConnectSuccess();

private:
	CSttMeasDevice* In_OpenMeasFile(const CString &strFile);
	CSttMeasDevice* In_CreateNewMeasDevice(CDataGroup *pDevice);

private:
	CTestMacros *m_pMeasustTestMacros;
	CSttMeasustTestClient *m_pSttMeasTestClient;

//2021-9-24  lijunqing
public:
	static CSttMeasTest_ModuleOutput* MeasModuleOutput()	{	return g_pSttMeasTool->m_pSttMeasTestClient->m_pMeasModuleOutput;	}
	static CSttMeasTest_MeasustOne* MeasModuleMeasust()	{	return g_pSttMeasTool->m_pSttMeasTestClient->m_pMeasModuleMeasust;	}
	static CSttMeasTest_MeasustSwitch* MeasustSwitch()	{	return g_pSttMeasTool->m_pSttMeasTestClient->m_pMeasustSwitch;	}
	static CSttMeasTest_MeasustThree* MeasModuleMeasustThree()	{	return g_pSttMeasTool->m_pSttMeasTestClient->m_pMeasModuleMeasustThree;	}
	static CSttMeasTest_MeasustOne2Points* MeasustOne2Points()	{	return g_pSttMeasTool->m_pSttMeasTestClient->m_pMeasustOne2Points;	}
	static CSttMeasTest_MeasustOneAngle* MeasustOneAngle()	{	return g_pSttMeasTool->m_pSttMeasTestClient->m_pMeasustOneAngle;	}
	static CSttMeasTest_MeasustOneFreq* MeasustOneFreq()	{	return g_pSttMeasTool->m_pSttMeasTestClient->m_pMeasustOneFreq;	}
	static CSttMeasTest_MeasustOneDcZero* MeasustOneDcZero()	{	return g_pSttMeasTool->m_pSttMeasTestClient->m_pMeasustOneDcZero;	}

};

