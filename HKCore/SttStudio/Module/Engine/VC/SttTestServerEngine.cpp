#include "stdafx.h"
#include "SttTestServerEngine.h"

#include "../../SttTestBase/SttTestFactory.h"

#include "../../SttSocket/TestServer/VC/SttTestServerSocket.h"

#include "../../ReplayTest/SttComtradeRcvSocket.h"
#include "../../RecordTest/SttRcdSendSocket.h"

#include"../../SttTest/Common/Adjust/SttAdjustTool.h"
#include"../../SttTest/Common/Meas/meas_define.h"

extern MEAS_DEVICE *g_MeasDevice;
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttTestServerEngine* CSttTestServerEngine::Create(char *pszIP, int nPort)
{
    m_nSttTestServerEngineRef++;

    if (m_nSttTestServerEngineRef == 1)
    {
        g_pSttTestServerEngine = new CSttTestServerEngine();
        g_pSttTestServerEngine->InitSttServerEngine(pszIP, nPort);
    }

    return (CSttTestServerEngine*)g_pSttTestServerEngine;
}

void CSttTestServerEngine::Release()
{
    m_nSttTestServerEngineRef--;

    if (m_nSttTestServerEngineRef == 0)
    {
		//CSttTestServerBase的析构函数为protected，在此直接删除有语法错误
		//所以将基类指针强制转换为CSttTestServerEngine，然后再删除
		 //delete g_pSttTestServerEngine;
		CSttTestServerEngine *pTestServer = (CSttTestServerEngine*)g_pSttTestServerEngine;
		//2020-4-6  lijq
		pTestServer->ExitSttServerEngine();
        delete pTestServer;
        g_pSttTestServerEngine = NULL;
    }
}


CSttTestServerEngine::CSttTestServerEngine()
{
 
}

CSttTestServerEngine::~CSttTestServerEngine()
{

}

CSttXmlSerializeBase* stt_create_sys_state_paras_register1(CSttXmlSerializeTool &oSttXmlRegister, CSttSysState &oSysState, CSttCmdBase *pSttCmd)
{
	oSysState.UpdateSysStateHead(pSttCmd);
	oSysState.GetSttParas();
	oSysState.Set_ExecStatus_Success();
	oSttXmlRegister.CreateXmlSerializeRegister(&oSysState);

	CSttXmlSerializeBase *pParasRegister = oSttXmlRegister.GetParas();

	return pParasRegister;
}

long CSttTestServerEngine::Process_Cmd_Ajust_ReadDeviceParameter(CSttSocketDataBase *pClientSocket, CSttAdjustCmd &oAdjustCmd,CSttXmlSerializeTool &oSttXmlSerializeTool)
{
	//ReturnSysState(STT_CMD_ExecStatus_ACK);
	CSttTestEngineBase::ReturnSysState(&oAdjustCmd, STT_CMD_ExecStatus_ACK,pClientSocket, NULL);
	//获取配置参数
	CSttXmlSerializeBase *pXmlSerializeParas = oSttXmlSerializeTool.GetParas();
	stt_xml_serialize_adj_para_config(pXmlSerializeParas);

	//获取数据
	CSttXmlSerializeTool oSttXmlRegister;
	CSttSysState oSysState;
	CSttXmlSerializeBase *pParasRegister = NULL;
	oSysState.SetRetType(SYS_STATE_RETTYPE_REPORT);
	pParasRegister = stt_create_sys_state_paras_register1(oSttXmlRegister, oSysState, &oAdjustCmd);

	g_bWriteHdInfor=FALSE;
	stt_xml_serialize_register_adjust(pParasRegister);

	//恢复配置
	stt_init_adj_para_config();

	//返回结果
	Ret_SysState(oSysState, pClientSocket, oSttXmlRegister);

	//返回成功
	CSttTestEngineBase::ReturnSysState(&oAdjustCmd, STT_CMD_ExecStatus_SUCCESS, pClientSocket, NULL);
	return 1;
}

long CSttTestServerEngine::Process_Cmd_Test_SetParameter(CSttXmlSerializeTool &oSttXmlSerializeTool)
{
	ReturnSysState(STT_CMD_ExecStatus_ACK);
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	CString strMacroID = oSttXmlSerializeTool.GetMacroID(CSttCmdDefineXmlRWKeys::CSttTestCmdKey());

	if (strMacroID == STT_MACRO_ID_SystemConfig)
	{
		ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		return 0;
	}

	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
	CSttTestBase *pNewTest = NULL;
    if (pCurrTest == NULL)
	{
		pNewTest = stt_CreateTestMacroByMacroID(strMacroID);
		//ASSERT (pNewTest != NULL);
		if(pNewTest == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] CreateTestMacroByMacroID Fail %s"), strMacroID.GetString());
			ReturnSysState(STT_CMD_ExecStatus_FAILURE);
			return 0;
		}

		pNewTest->Init();
		pNewTest->Para_XmlSerialize(pMacroParas);
		CSttServerTestCtrlCntr::SetParameter(pNewTest);
		ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
	}
	else
	{
		//20231020  zhoulei  以注册类里面的strMacroID为唯一判断依据
		if(pCurrTest->m_strID == strMacroID)
		{
			pCurrTest->Init();
			pCurrTest->Para_XmlSerialize(pMacroParas);
			CSttServerTestCtrlCntr::SetParameter();
			ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		}
		else
		{
			pNewTest = stt_CreateTestMacroByMacroID(strMacroID);
			if(pNewTest == NULL)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] CreateTestMacroByMacroID Fail %s"), strMacroID.GetString());
				ReturnSysState(STT_CMD_ExecStatus_FAILURE);
				return 0;
			}

			pNewTest->Init();
			pNewTest->Para_XmlSerialize(pMacroParas);
			CSttServerTestCtrlCntr::SetParameter(pNewTest);
			ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		}
	}
	return 0;
}
long CSttTestServerEngine::Process_Cmd_Test_StartTest(CSttXmlSerializeTool &oSttXmlSerializeTool)
{
	ReturnSysState(STT_CMD_ExecStatus_ACK);

	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	CString strMacroID = "SttTestForDebug";

	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
	CSttTestBase *pNewTest = NULL;

	if (pCurrTest == NULL)
	{
		pNewTest = stt_CreateTestMacroByMacroID(strMacroID);
		//ASSERT (pNewTest != NULL);
		if(pNewTest == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] CreateTestMacroByMacroID Fail %s"), strMacroID.GetString());
			ReturnSysState(STT_CMD_ExecStatus_FAILURE);
			return 0;
		}

		pNewTest->Init();
		pNewTest->Para_XmlSerialize(pMacroParas);
		CSttServerTestCtrlCntr::Test(pNewTest);
		ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		if(!pNewTest->TestPara_CheckOK())
		{
			//实验参数异常,直接返回TestFinish
			ReturnTestParaCheckFail();
			STT_TIME pTime;
			pTime.dRealTime=0;
			pTime.dTime=0;
			pTime.dBinActTime=-1;
			ReturnTestStateEvent(SttResult_Type_TestFinish,&pTime,FALSE);
		}
	}
	else
	{
		//20231020  zhoulei  以注册类里面的strMacroID为唯一判断依据
		if(pCurrTest->m_strID == strMacroID)
		{
			pCurrTest->Init();
			pCurrTest->Para_XmlSerialize(pMacroParas);
			CSttServerTestCtrlCntr::Test();
			ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		}
		else
		{
			pNewTest = stt_CreateTestMacroByMacroID(strMacroID);
			if(pNewTest == NULL)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] CreateTestMacroByMacroID Fail %s"), strMacroID.GetString());
				ReturnSysState(STT_CMD_ExecStatus_FAILURE);
				return 0;
			}

			pNewTest->Init();
			pNewTest->Para_XmlSerialize(pMacroParas);
			CSttServerTestCtrlCntr::Test(pNewTest);
			ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		}
	}
	STT_TIME pTime;
	pTime.dRealTime=0;
	pTime.dTime=0;
	pTime.dBinActTime=-1;
	ReturnTestStateEvent(SttResult_Type_TestFinish,&pTime,FALSE);
	return 0;
}