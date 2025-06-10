#include "PpSttCapEngineServer.h"
#include "PpSttCapEngineDevice.h"
#include "..\SmartCap\XSttCap_61850.h"
#include "..\SmartCap\XSmartCapMngr.h"
#include "QSttCapIotEngineFrameBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern QSttCapIotEngineFrameBase *g_pSttCapIotEngineBase;
extern CSttTestAppCfg g_oSttTestAppCfg; 
CPpSttCapEngineServer::CPpSttCapEngineServer()
{
	m_strEngineProgID = _T("PpSttIotEngine");
	m_strID = m_strEngineProgID;
}

CPpSttCapEngineServer::~CPpSttCapEngineServer()
{

}

CIotPxEngineDeviceBase* CPpSttCapEngineServer::CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd)
{
	CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();
	iotpx_ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_ACK, NULL);
	CPpSttCapEngineDevice *pNew = new CPpSttCapEngineDevice();
	AddNewChild(pNew);

	if (!g_pSttCapIotEngineBase->ConnectState())
	{
		g_pSttCapIotEngineBase->BeginIecRecord();
	}
	if (!g_pSttCapIotEngineBase->ConnectState())
	{
		return NULL;
	}
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	if(pXSttCap_61850)
	{
		pNew->m_pDvmDevice = pXSttCap_61850->m_pDvmDevice;
		pNew->m_pX61850CapBase = pXSttCap_61850;
	}
	iotpx_ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_SUCCESS,NULL ,STT_SYS_STATE_ID_ConnectState,EngineEvent_ConnectDeviceSuccessful);

	return pNew;
}

void CPpSttCapEngineServer::CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{

}