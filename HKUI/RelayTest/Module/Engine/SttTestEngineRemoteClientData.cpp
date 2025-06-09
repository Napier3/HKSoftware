#include "stdafx.h"
#include "SttTestEngineRemoteClientData.h"
#include "../SttSocket/SttCmdOverTimeMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
CSttTestEngineRemoteClientData::CSttTestEngineRemoteClientData()
{
	
}

CSttTestEngineRemoteClientData::~CSttTestEngineRemoteClientData()
{
	
}

//Query命令应答，更新注册链表
BOOL CSttTestEngineRemoteClientData::UpdateRegisterList(CSttSysState &oSysState)
{
	CSttParas* pParas = oSysState.GetSttParas();

	if (pParas == NULL)
	{
		return FALSE;
	}

	m_oSttRemoteRegList.DeleteAll();

	POS pos = pParas->GetHeadPosition();
	CExBaseObject *p = NULL;

	while(pos != NULL)
	{
		p = pParas->GetNext(pos);

		if (p->GetClassID() != DVMCLASSID_CDVMDATA)
		{
			continue;
		}

		if (p->m_strID != STT_TERMINAL_TYPE_REMOTE)
		{
			continue;
		}

		CSttTestRemoteRegister *pNew = new CSttTestRemoteRegister(p);
		m_oSttRemoteRegList.AddNewChild(pNew);
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//autotest command
//AutoTest\Module\AtsRpc\AtsRpcServerGlobalApi.h
long CSttTestEngineRemoteClientData::Ats_CreateTest(CExBaseObject *pAtsDefine)
{
	return 0;
}

long CSttTestEngineRemoteClientData::Ats_StartTest() 
{
	return 0;
}

long CSttTestEngineRemoteClientData::Ats_StopTest() 
{
	return 0;
}

long CSttTestEngineRemoteClientData::Ats_TestItem(const CString &strItemPath) 
{
	return 0;
}

long CSttTestEngineRemoteClientData::Ats_TestItem(long nItemIndex) 
{
	return 0;
}

long CSttTestEngineRemoteClientData::Ats_TestFrom(const CString &strItemPath) 
{
	return 0;
}


long CSttTestEngineRemoteClientData::Ats_TestFrom(long nItemIndex) 
{
	return 0;
}

long CSttTestEngineRemoteClientData::Ats_TestAllFailedItems() 
{
	return 0;
}

//【可以不需要】
long CSttTestEngineRemoteClientData::Ats_GetItemReport() 
{
	return 0;
}

long CSttTestEngineRemoteClientData::Ats_GetReportFile() 
{
	return 0;
}

long CSttTestEngineRemoteClientData::Ats_GetSystemState() 
{
	return 0;
}


//assist command
long CSttTestEngineRemoteClientData::Assist_GetTestParas()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_SetTestParas()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_StartTest()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_StopTest()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_SelectTestMacro()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_RunExe()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_ImportDvmFile()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_GetDeviceModel()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_ReadDataset()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_WriteDataset()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_Reset()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_ReadSetZone()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_WriteSetZone()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_StartReport()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_StopReport()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_CreateDevcie()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_EnumDevice()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_EnumLdevice()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_EnumDataset()
{
	return 0;
}

long CSttTestEngineRemoteClientData::Assist_SelectDvmNode()
{
	return 0;
}

///////////////////////////////////
long CSttTestEngineRemoteClientData::Process_SysState_System_Query(CSttSysState &oSysState)
{
	long nCmdExecState = oSysState.Get_ExecStatus();

	if (Stt_Is_ExecStatus_Success(nCmdExecState))
	{
		UpdateRegisterList(oSysState);
	}
	
	return nCmdExecState;
}

long CSttTestEngineRemoteClientData::Process_SysState_System_Bind(CSttSysState &oSysState)
{
	long nCmdExecState = oSysState.Get_ExecStatus();

	if (Stt_Is_ExecStatus_Success(nCmdExecState))
	{
		long nID_Remote = 0;
		oSysState.GetParasDataValueByID(STT_CMD_PARA_IDTESTER, nID_Remote);
		m_oCurrUser.ID_Terminal(STT_TERMINAL_TYPE_REMOTE);
		m_oCurrUser.SetIDTest(nID_Remote);
	}

	return nCmdExecState;
}

CSttTestRemoteRegister* CSttTestEngineRemoteClientData::FindRegisterBySN(const CString &strSN)
{
	CSttTestRemoteRegister* pRegister = NULL;
	CSttTestRemoteRegister* pFind = NULL;

	POS pos = m_oSttRemoteRegList.GetHeadPosition();

	while (pos != NULL)
	{
		pRegister = (CSttTestRemoteRegister*)m_oSttRemoteRegList.GetNext(pos);

		if (pRegister->SN_TestApp() == strSN)
		{
			pFind = pRegister;
			break;
		}
	}

	return pFind;
}