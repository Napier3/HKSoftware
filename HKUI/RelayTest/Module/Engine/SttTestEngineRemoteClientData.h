#pragma once

#include "SttTestEngineClientData.h"
#include "../SttAuthority/SttTestRemoteRegister.h"

class CSttTestEngineRemoteClientData : public CSttTestEngineClientData
{
public:
	CSttTestEngineRemoteClientData();
	virtual ~CSttTestEngineRemoteClientData();

	BOOL UpdateRegisterList(CSttSysState &oSysState);

public:
	CExBaseList m_oSttRemoteRegList;

public:
	//autotest command
	long Ats_CreateTest(CExBaseObject *pAtsDefine); //AutoTest\Module\AtsRpc\AtsRpcServerGlobalApi.h
	long Ats_StartTest(); 
	long Ats_StopTest(); 
	long Ats_TestItem(const CString &strItemPath); 
	long Ats_TestItem(long nItemIndex); 
	long Ats_TestFrom(const CString &strItemPath); 
	long Ats_TestFrom(long nItemIndex); 
	long Ats_TestAllFailedItems(); 
	long Ats_GetItemReport(); //【可以不需要】
	long Ats_GetReportFile(); 
	long Ats_GetSystemState(); 

	//assist command
	long Assist_GetTestParas();
	long Assist_SetTestParas();
	long Assist_StartTest();
	long Assist_StopTest();
	long Assist_SelectTestMacro();
	long Assist_RunExe();
	long Assist_ImportDvmFile();
	long Assist_GetDeviceModel();
	long Assist_ReadDataset();
	long Assist_WriteDataset();
	long Assist_Reset();
	long Assist_ReadSetZone();
	long Assist_WriteSetZone();
	long Assist_StartReport();
	long Assist_StopReport();
	long Assist_CreateDevcie();
	long Assist_EnumDevice();
	long Assist_EnumLdevice();
	long Assist_EnumDataset();
	long Assist_SelectDvmNode();

public:
	long Process_SysState_System_Query(CSttSysState &oSysState);
	long Process_SysState_System_Bind(CSttSysState &oSysState);

	CSttTestRemoteRegister* FindRegisterBySN(const CString &strSN);
};
