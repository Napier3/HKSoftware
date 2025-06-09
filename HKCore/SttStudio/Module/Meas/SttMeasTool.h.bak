//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttAdjTool.h  CSttAdjTool

#pragma once

#include "SttAdjustTestClient.h"

class CSttAdjTool : public CExBaseList
{
private:
	CSttAdjTool();
	virtual ~CSttAdjTool();

	static long g_nSttAdjToolRef;
	static CSttAdjTool* g_pSttAdjTool;

public:
	static CSttAdjTool* Create();
	static CSttAdjTool* GetAdjTool();
	static void Release();

public:
	static CSttAdjDevice* FindAdjDevice(const CString &strFile);
	static CSttAdjDevice* CreateNewAdjDevice(CDataGroup *pDevice);
	static CSttAdjDevice* OpenAdjFile(const CString &strFile);
	static CSttAdjustTestClient* GetSttAdjustTestClient();
	static void CloseAdjDeviceFile(CExBaseObject *pAdjDevice);

	static BOOL IsConnectSuccess();

private:
	CSttAdjDevice* In_OpenAdjFile(const CString &strFile);
	CSttAdjDevice* In_CreateNewAdjDevice(CDataGroup *pDevice);

private:
	CTestMacros *m_pAdjustTestMacros;
	CSttAdjustTestClient *m_pSttAdjTestClient;

//2021-9-24  lijunqing
public:
	static CSttAdjTest_ModuleOutput* AdjModuleOutput()	{	return g_pSttAdjTool->m_pSttAdjTestClient->m_pAdjModuleOutput;	}
	static CSttAdjTest_AdjustOne* AdjModuleAdjust()	{	return g_pSttAdjTool->m_pSttAdjTestClient->m_pAdjModuleAdjust;	}
	static CSttAdjTest_AdjustSwitch* AdjustSwitch()	{	return g_pSttAdjTool->m_pSttAdjTestClient->m_pAdjustSwitch;	}
	static CSttAdjTest_AdjustThree* AdjModuleAdjustThree()	{	return g_pSttAdjTool->m_pSttAdjTestClient->m_pAdjModuleAdjustThree;	}
	static CSttAdjTest_AdjustOne2Points* AdjustOne2Points()	{	return g_pSttAdjTool->m_pSttAdjTestClient->m_pAdjustOne2Points;	}
	static CSttAdjTest_AdjustOneAngle* AdjustOneAngle()	{	return g_pSttAdjTool->m_pSttAdjTestClient->m_pAdjustOneAngle;	}
	static CSttAdjTest_AdjustOneFreq* AdjustOneFreq()	{	return g_pSttAdjTool->m_pSttAdjTestClient->m_pAdjustOneFreq;	}
	static CSttAdjTest_AdjustOneDcZero* AdjustOneDcZero()	{	return g_pSttAdjTool->m_pSttAdjTestClient->m_pAdjustOneDcZero;	}

};

