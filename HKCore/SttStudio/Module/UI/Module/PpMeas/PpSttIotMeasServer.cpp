#include "../../../SttCmd/SttSysState.h"
#include "../../../../../Module/SmartCap/XSmartCapMngr.h"
#include "PpSttIotMeasServer.h"
#include "PpSttIotMeasDevice.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPpSttIotMeasServer::CPpSttIotMeasServer()
{
	m_pMeasDevice = NULL;
}

CPpSttIotMeasServer::~CPpSttIotMeasServer()
{
	if(m_pMeasDevice)
	{
		delete m_pMeasDevice;
		m_pMeasDevice = NULL;
	}
}

CPpSttIotMeasServer* CPpSttIotMeasServer::Create(char *pszIP, int nPort)
{
	m_nSttTestServerEngineRef++;

	if (m_nSttTestServerEngineRef == 1)
	{
		g_pSttTestServerEngine = new CPpSttIotMeasServer();
		g_pSttTestServerEngine->InitSttServerEngine(pszIP, nPort);
	}

	return (CPpSttIotMeasServer*)g_pSttTestServerEngine;
}

void CPpSttIotMeasServer::Release()
{
	m_nSttTestServerEngineRef--;

	if (m_nSttTestServerEngineRef == 0)
	{
		//CSttTestServerBase的析构函数为protected，在此直接删除有语法错误
		//所以将基类指针强制转换为CSttTestServerEngine，然后再删除
		//delete g_pSttTestServerEngine;
		CPpSttIotMeasServer *pTestServer = (CPpSttIotMeasServer*)g_pSttTestServerEngine;
		//2020-4-6  lijq
		pTestServer->ExitSttServerEngine();
		delete pTestServer;
		g_pSttTestServerEngine = NULL;
	}
}

long CPpSttIotMeasServer::Process_Cmd_Test(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	if(!CheckBeforeProcessCmdTest(pClientSocket,pBuf,nLen,pszCmdID,pszTestor))
	{
		if (CanSendLog())
		{//2020-07-12 lijq
			CString strInfor;
			strInfor.Format(_T(">>> Process_Cmd_Test : %s,%u   has no [test] authority"), pszCmdID, pClientSocket->GetIDTest());
			LogDebugInfor(strInfor);
		}
		return 0;
	}

	CSttXmlSerializeTool oSttXmlSerializeTool;
	m_oSttTestCmd.SetRefSocketData(pClientSocket);
	char *pszPkgXml = m_oSttTestCmd.ParsePkgOnly(pBuf);
	CSttTestCmd *pSttTestCmd=new CSttTestCmd;
	oSttXmlSerializeTool.CreateXmlSerializeRead(pSttTestCmd, pszPkgXml, nLen - STT_PKG_HEAD_LEN);
	m_oSttTestCmd.m_strID=pSttTestCmd->m_strID;
	m_oSttTestCmd.CopyOwn(pSttTestCmd);

	if (CanSendLog())
	{//2020-07-12 lijq
		CString strInfor;
		strInfor.Format(_T(">>> Process_Cmd_Test : %s"), pszCmdID);
		LogDebugInfor(strInfor);
	}

	long nRet = 0;
	CString strText;
	if (strcmp(pszCmdID ,STT_CMD_TYPE_TEST_SetDataset) == 0)
	{
		nRet =  Process_Cmd_Test_SetDataset(pSttTestCmd, pClientSocket);
	}
	else if(strcmp(pszCmdID, STT_CMD_TYPE_TEST_GetDataset) == 0)
	{
		nRet =  Process_Cmd_Test_GetDataset(pSttTestCmd, pClientSocket);
	}

	if (CanSendLog())
	{//2020-07-12 lijq
		LogDebugInfor(_T("Process_Cmd_Test >>>>"));
	}

	delete pSttTestCmd;
	pSttTestCmd=NULL;

	return nRet;
}

long CPpSttIotMeasServer::Process_Cmd_Test_SetDataset(CSttTestCmd* pTestCmd, CSttSocketDataBase *pClientSocket)
{
	ReturnSysState(STT_CMD_ExecStatus_ACK);

	CSttParas* pParas = pTestCmd->GetSttParas();
	CDvmData* pDeviceSN = (CDvmData*)pParas->FindByID(STT_CMD_PARA_DeviceSN);
	CDvmData* pDatasetPath = (CDvmData*)pParas->FindByID(STT_CMD_PARA_DatasetPath);
	CDvmDataset* pDataset = (CDvmDataset*)pParas->FindByClassID(DVMCLASSID_CDVMDATASET);

	CSttSysState *pSysState = m_pMeasDevice->SetDataset(pDataset, pDeviceSN->m_strValue, pDatasetPath->m_strValue);
	pSysState->UpdateSysStateHead(pTestCmd);
	pClientSocket->SendSysState(pSysState);
	delete pSysState;
	return 0;
}

long CPpSttIotMeasServer::Process_Cmd_Test_GetDataset(CSttTestCmd* pTestCmd, CSttSocketDataBase *pClientSocket)
{
	ReturnSysState(STT_CMD_ExecStatus_ACK);

	CSttParas* pParas = pTestCmd->GetSttParas();
	CDvmData* pDeviceSN = (CDvmData*)pParas->FindByID(STT_CMD_PARA_DeviceSN);
	CDvmData* pDatasetPath = (CDvmData*)pParas->FindByID(STT_CMD_PARA_DatasetPath);

	CSttSysState *pSysState = m_pMeasDevice->GetDataset(pDeviceSN->m_strValue, pDatasetPath->m_strValue);
	pSysState->UpdateSysStateHead(pTestCmd);
	pClientSocket->SendSysState(pSysState);
	delete pSysState;
	return 0;
}

void CPpSttIotMeasServer::InitMeasServer()
{
	if(m_pMeasDevice)
	{
		delete m_pMeasDevice;
		m_pMeasDevice = NULL;
	}

	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	if(pXSttCap_61850)
	{
		m_pMeasDevice = new CPpSttIotMeasDevice();
		m_pMeasDevice->SetDeviceRef(pXSttCap_61850->m_pDvmDevice);
	}
}