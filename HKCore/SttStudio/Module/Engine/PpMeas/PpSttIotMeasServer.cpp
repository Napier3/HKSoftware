#include "stdafx.h"
#include "../../SttCmd/SttSysState.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "PpSttIotMeasServer.h"
#include "PpSttIotMeasDevice.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPpSttIotMeasServer::CPpSttIotMeasServer()
{
	//m_pMeasDevice = NULL;
	m_strEngineProgID = _T("PpSttIotEngine");
	m_strID = m_strEngineProgID;
}

CPpSttIotMeasServer::~CPpSttIotMeasServer()
{
// 	if(m_pMeasDevice)
// 	{
// 		delete m_pMeasDevice;
// 		m_pMeasDevice = NULL;
// 	}
}
// 
// CPpSttIotMeasServer* CPpSttIotMeasServer::Create(char *pszIP, int nPort)
// {
// 	CPpSttIotMeasServer *pNew = new CPpSttIotMeasServer();
// 
// 	pNew->InitSttServerEngine(pszIP, nPort);
// 
// 	return pNew;
// }

CIotPxEngineDeviceBase* CPpSttIotMeasServer::CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd)
{
	CPpSttIotMeasDevice *pNew = new CPpSttIotMeasDevice();
	AddNewChild(pNew);

	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	if(pXSttCap_61850)
	{
		pNew->m_pDvmDevice = pXSttCap_61850->m_pDvmDevice;
		pNew->m_pX61850CapBase = pXSttCap_61850;
	}

	//zhouhj 2024.4.8 合并单元测试时,创建设备时,自动返回连接成功结果
	CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();
	CSttParas *pSrcParas = pIotCmd->GetSttParas();
	pSrcParas->SetDataValue(STT_SYS_STATE_ID_ConnectState,EngineEvent_ConnectDeviceSuccessful, TRUE);
	return pNew;
}

void CPpSttIotMeasServer::CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{

}
// 
// long CPpSttIotMeasServer::Process_Cmd_Test(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
// {
// 	if(!CheckBeforeProcessCmdTest(pClientSocket,pBuf,nLen,pszCmdID,pszTestor))
// 	{
// 		if (CanSendLog())
// 		{//2020-07-12 lijq
// 			CString strInfor;
// 			strInfor.Format(_T(">>> Process_Cmd_Test : %s,%u   has no [test] authority"), pszCmdID, pClientSocket->GetIDTest());
// 			LogDebugInfor(strInfor);
// 		}
// 		return 0;
// 	}
// 
// 	CSttXmlSerializeTool oSttXmlSerializeTool;
// 	m_oSttTestCmd.SetRefSocketData(pClientSocket);
// 	char *pszPkgXml = m_oSttTestCmd.ParsePkgOnly(pBuf);
// 	CSttTestCmd *pSttTestCmd=new CSttTestCmd;
// 	oSttXmlSerializeTool.CreateXmlSerializeRead(pSttTestCmd, pszPkgXml, nLen - STT_PKG_HEAD_LEN);
// 	m_oSttTestCmd.m_strID=pSttTestCmd->m_strID;
// 	m_oSttTestCmd.CopyOwn(pSttTestCmd);
// 
// 	if (CanSendLog())
// 	{//2020-07-12 lijq
// 		CString strInfor;
// 		strInfor.Format(_T(">>> Process_Cmd_Test : %s"), pszCmdID);
// 		LogDebugInfor(strInfor);
// 	}
// 
// 	long nRet = 0;
// 	CString strText;
// 	if (strcmp(pszCmdID ,STT_CMD_TYPE_TEST_SetDataset) == 0)
// 	{
// 		nRet =  Process_Cmd_Test_SetDataset(pSttTestCmd, pClientSocket);
// 	}
// 	else if(strcmp(pszCmdID, STT_CMD_TYPE_TEST_GetDataset) == 0)
// 	{
// 		nRet =  Process_Cmd_Test_GetDataset(pSttTestCmd, pClientSocket);
// 	}
// 
// 	if (CanSendLog())
// 	{//2020-07-12 lijq
// 		LogDebugInfor(_T("Process_Cmd_Test >>>>"));
// 	}
// 
// 	delete pSttTestCmd;
// 	pSttTestCmd=NULL;
// 
// 	return nRet;
// }
// 
// long CPpSttIotMeasServer::Process_Cmd_Test_SetDataset(CSttTestCmd* pTestCmd, CSttSocketDataBase *pClientSocket)
// {
// 	ReturnSysState(STT_CMD_ExecStatus_ACK);
// 
// 	CSttParas* pParas = pTestCmd->GetSttParas();
// 	CDvmData* pDeviceSN = (CDvmData*)pParas->FindByID(STT_CMD_PARA_DeviceSN);
// 	CDvmData* pDatasetPath = (CDvmData*)pParas->FindByID(STT_CMD_PARA_DatasetPath);
// 	CDvmDataset* pDataset = (CDvmDataset*)pParas->FindByClassID(DVMCLASSID_CDVMDATASET);
// 
// 	CSttSysState *pSysState = m_pMeasDevice->SetDataset(pDataset, pDeviceSN->m_strValue, pDatasetPath->m_strValue);
// 	pSysState->UpdateSysStateHead(pTestCmd);
// 	pClientSocket->SendSysState(pSysState);
// 	delete pSysState;
// 	return 0;
// }
// 
// long CPpSttIotMeasServer::Process_Cmd_Test_GetDataset(CSttTestCmd* pTestCmd, CSttSocketDataBase *pClientSocket)
// {
// 	ReturnSysState(STT_CMD_ExecStatus_ACK);
// 
// 	CSttParas* pParas = pTestCmd->GetSttParas();
// 	CDvmData* pDeviceSN = (CDvmData*)pParas->FindByID(STT_CMD_PARA_DeviceSN);
// 	CDvmData* pDatasetPath = (CDvmData*)pParas->FindByID(STT_CMD_PARA_DatasetPath);
// 
// 	CSttSysState *pSysState = m_pMeasDevice->GetDataset(pDeviceSN->m_strValue, pDatasetPath->m_strValue);
// 	pSysState->UpdateSysStateHead(pTestCmd);
// 	pClientSocket->SendSysState(pSysState);
// 	delete pSysState;
// 	return 0;
// }
