#include "stdafx.h"
#include "IotPxEngineServer.h"
#include "IotPxEngineDeviceBase.h"

#ifdef IOT_PROTOCOL_SERVER_USE_MQTT
#include "../../../SttStudio/Module/Engine/PpEngineServerBase/PpSvrInterfaceMqttClient.h"
#endif

CIotPxCommChannelInterface::CIotPxCommChannelInterface()
{
	m_pPxEngineServer = NULL;
	m_PxEngineDevice = NULL;

	m_nSttCmdDataFormat = -1;  //默认为什么格式都没有，收到的第一帧报文进行初始化
	m_oArrIotCmd.SetMaxCount(50);
}

CIotPxCommChannelInterface::~CIotPxCommChannelInterface()
{
		
}

void CIotPxCommChannelInterface::FreeCmd(CExBaseObject *pCmd)
{
	m_oArrIotCmd.FreeObject((CSttCmdBase *)pCmd);
}

void CIotPxCommChannelInterface::AddCmd(CExBaseObject *pCmd)
{
	m_oArrIotCmd.AddObject((CSttCmdBase *)pCmd);
}

void CIotPxCommChannelInterface::Release()
{
	Release(TRUE);
// 	m_nObjectRefCount--;
// 
// 	if (m_nObjectRefCount == 0)
// 	{
// 		long nIndex = 0;
// 
// 		for (nIndex=0; nIndex< m_oArrIotCmd.GetMaxCount(); nIndex++)
// 		{
// 			CSttCmdBase *pCmd = (CSttCmdBase *)m_oArrIotCmd.GetObject(nIndex);
// 
// 			if (pCmd != NULL)
// 			{
// 				pCmd->SetSttCmmOptrInterface(NULL);
// 			}
// 		}
// 
// 		delete this;
// 	}
}

void CIotPxCommChannelInterface::Release(BOOL bDeleteThis)
{
	m_nObjectRefCount--;

	if (m_nObjectRefCount == 0)
	{
		long nIndex = 0;

		for (nIndex=0; nIndex< m_oArrIotCmd.GetMaxCount(); nIndex++)
		{
			CSttCmdBase *pCmd = (CSttCmdBase *)m_oArrIotCmd.GetObject(nIndex);

			if (pCmd != NULL)
			{
				pCmd->SetSttCmmOptrInterface(NULL);
			}
		}

		if (bDeleteThis)
		{
			delete this;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//CIotPxEngineInterface
CIotPxEngineInterface::CIotPxEngineInterface()
{

}

CIotPxEngineInterface::~CIotPxEngineInterface()
{

}
CIotPxEngineDeviceBase* CIotPxEngineInterface::CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd)
{
	return NULL;
}

void CIotPxEngineInterface::CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd)
{

}


//////////////////////////////////////////////////////////////////////////
//CIotPxEngineServerInterface
CIotPxEngineServerInterface::CIotPxEngineServerInterface()
{

}

CIotPxEngineServerInterface::~CIotPxEngineServerInterface()
{

}





void iotpx_AppendCmdParas(CSttCmdBase *pSttCmd, CSttSysState &oDestSysState)
{
	CSttParas *pSrcParas = pSttCmd->GetSttParas();
	CSttParas *pDestParas = oDestSysState.GetSttParas();

	POS pos = pSrcParas->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pSrcParas->GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			pDestParas->AddTail((CExBaseObject*)p->Clone());
		}
	}
}

//lijunqing 2022-10-9
long iotpx_ReturnSysState(CIotPxCommChannelInterface *pCommCh, CSttCmdBase *pSttCmd, long nCmdExecStatus,
						  CDvmDataset *pDataset,const CString &strAddDataID,const CString &strAddDataValue)
{
	if (pCommCh == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("SttCmd->m_pRefSocketDataBase == NULL"));
		return 0;
	}

	CSttSysState oSysState;
	oSysState.Set_Xml_Pkg_With_Name(pSttCmd->Get_Xml_Pkg_With_Name());
	CSttParas *pSttParas = oSysState.GetSttParas();
	oSysState.UpdateSysStateHead(pSttCmd);
	iotpx_AppendCmdParas(pSttCmd, oSysState);

	if (pDataset != NULL)
	{//返回结果数据集
		pSttParas->AddTail(pDataset);
	}

// 	oSysState.AddNewParasData(STT_SYS_STATE_ID_ConnectState, _T("ConnectSuccess"));
// 	pSttParas->SetDataValue(PXI_DATA_ID_EngineSysState, EngineSysState_CommFinish, TRUE);

	if (!strAddDataID.IsEmpty())
	{
		pSttParas->SetDataValue(strAddDataID, strAddDataValue, TRUE);
	}

	oSysState.Set_ExecStatus(nCmdExecStatus);
	long nRet = pCommCh->PxSendSysState(&oSysState);
	
	if (pDataset != NULL)
	{//返回结果数据集
		pSttParas->Remove(pDataset);
	}

	return nRet;
}

long iotpx_ReturnSysState(CIotPxCommChannelInterface *pCommCh, CSttSysState &oSysState)
{
	if (pCommCh == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("SttCmd->m_pRefSocketDataBase == NULL"));
		return 0;
	}

	long nRet = pCommCh->PxSendSysState(&oSysState);

	return nRet;
}

long iotpx_ReturnSysState(CSttSysState &oSysState, const CString &strFromSN, const CString &strDeviceSN)
{
#ifdef IOT_PROTOCOL_SERVER_USE_MQTT
	if (g_thePpSvrMqttClient != NULL)
	{
		CMqttPpServerClient* pClient = g_thePpSvrMqttClient->FindByDeviceSN(strDeviceSN);

		if (pClient == NULL)
		{
			return -1;
		}

		return g_thePpSvrMqttClient->PxSendSysState(&oSysState, strFromSN, strDeviceSN, pClient->m_nSttCmdDataFormat);
	}
#endif

	return -1;
}

//监视服务端所有的命令报文
extern long g_nSttLogServerSpyAllCmd;

//2022-12-15  lijunqing
void iotpx_LogSttCmd(CSttCmdBase *pSttCmd)
{
	if (g_nSttLogServerSpyAllCmd == 0)
	{
		return;
	}

	char *pBuffer = NULL;

	CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	long nRet = pSttCmd->GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pBuffer, 0);
	CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	if (pBuffer != NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, pBuffer);
		delete pBuffer;
	}
}


