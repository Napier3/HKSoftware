#include "stdafx.h"
#include"PpSttIotEngine.h"
#include "../../../IotProtoServer/Module/SttPxCommCmdDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern BOOL g_bShowTestWndTop;

//////////////////////////////////////////////////////////////////////////
//CPpSttIotDevice
CPpSttIotDevice::CPpSttIotDevice()
{
    m_pSttIotClient = NULL;
	m_oPkgSpyList.AllocBuffer(STT_PP_IOT_ENGINE_SPY_DATA_MAX_NUM);
}

CPpSttIotDevice::~CPpSttIotDevice()
{
	DisConnect();
}

void CPpSttIotDevice::NewSttIotClient()
{
    if (m_pSttIotClient == NULL)
    {
        m_pSttIotClient = new CPpSttIotClient();
        m_pSttIotClient->SetSttCmdDataFormat(m_nSttCmdDataFormat);
    }
}


BOOL CPpSttIotDevice::ConnectSttServer()
{
	//连接服务器
	long nRet = m_pSttIotClient->ConnectSttServer();
	m_pSttIotClient->SetTestEventInterface(this);

	if (! nRet)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("Connect IOT Protocol Server Failed!"));
		PostDeviceSysMessage(0, engineConnectDeviceFailed);

		return FALSE;
	}

	return TRUE;
}

void CPpSttIotDevice::SetSttCmdDataFormat(long nSttCmdForat)
{
    m_nSttCmdDataFormat = nSttCmdForat;

    if (m_pSttIotClient != NULL)
    {
        m_pSttIotClient->SetSttCmdDataFormat(nSttCmdForat);
    }
}

long CPpSttIotDevice::IsConnectSuccessful()
{
	return m_bIsSvrDeviceConnectSucc;
}

void CPpSttIotDevice::On_SysState_IOT(CSttSysState *pSysState)
{
	CPpSttIotDeviceBase::On_SysState_IOT(pSysState);
}

 long CPpSttIotDevice::X_SendIotCmd(CSttIotCmd &oIotCmd)
 {
	 if (m_pSttIotClient == NULL)
	 {
		 return false;
	 }

	return m_pSttIotClient->SendIotCmd(oIotCmd);
 }

BOOL CPpSttIotDevice::IsConnectIotServerSucc()
{
    if (m_pSttIotClient == NULL)
    {
        return false;
    }

    return m_pSttIotClient->IsConnectSuccess();
}

void CPpSttIotDevice::DisConnect()
{
    if (m_pSttIotClient == NULL)
    {
        return;
    }

    m_pSttIotClient->DisConnect();
    m_pSttIotClient->DestroyWindow();   //应该在创建的线程中进行释放
#ifdef _PSX_IDE_QT_
    m_pSttIotClient->deleteLater();
#else
   delete m_pSttIotClient;
#endif
    m_pSttIotClient = NULL;
}

void CPpSttIotDevice::DisConnectForClose(BOOL bDelete)
{
    m_pSttIotClient->DisConnectForClose(bDelete);  //断开连接
	m_bIsSvrDeviceConnectSucc = FALSE;
}

long CPpSttIotDevice::Event_OnPkgSpy(CSttParas *pSttParas)
{
	if (m_oPkgSpyList.GetDataCount()>=STT_PP_IOT_ENGINE_SPY_DATA_MAX_NUM)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("报文监听缓存已满."));
		return 0;
	}

	m_oPkgSpyList.Add((CExBaseObject*)pSttParas->Clone());
	PostDeviceEventMessage(EngineEvent_ID_PkgSpy, EngineEvent_ID_PkgSpy);
	return 0;
}

BOOL CPpSttIotDevice::GetRunProcedureRltValue(const CString &strID,long &nValue)
{
// 	CDvmDataset *pFindDvmDataset = (CDvmDataset*)m_listDataset.FindByID(XPARA_ID_DEVICE_ATTR);
// 
// 	if (pFindDvmDataset == NULL)
// 	{
// 		return FALSE;
// 	}

	CDvmData *pFindData = (CDvmData*)m_listRunProcedureRlt.FindByID(strID);

	if (pFindData == NULL)
	{
		return FALSE;
	}

	nValue = CString_To_long(pFindData->m_strValue);
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//CPpSttIotEngine
CPpSttIotEngine::CPpSttIotEngine()
{
	
}

CPpSttIotEngine::~CPpSttIotEngine(void)
{
	
}

CPpSttIotDeviceBase* CPpSttIotEngine::CreateNewDevice()
{
	return new CPpSttIotDevice();
}
