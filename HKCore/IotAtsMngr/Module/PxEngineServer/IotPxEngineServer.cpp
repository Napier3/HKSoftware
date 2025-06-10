#include "stdafx.h"
#include "IotPxEngineServer.h"
#include "../../../AutoTest/Module/AutoTestGlobalDefine.h"
#include"../../Module/API/GlobalConfigApi.h"

#ifdef _PSX_IDE_QT_
#include "IotPxEngineServerWnd_Linux.h"
#else
#include "IotPxEngineServerWnd_Win.h"
#endif

CIotPxEngineServer* g_theIotPxEngineServer = NULL;

long CIotPxEngineServer::g_nPxEngineServerRef = 0;
CIotPxEngineServer* CIotPxEngineServer::g_pIotPxEngineServer = NULL;
//CExBaseList* CIotPxEngineServer::m_pServerSocketRef = NULL;
long g_nWriteLogTxtFile = 0;//zhouhj 2024.10.19 用于写xml文件查找机器里软件崩溃问题原因

void Global_WriteLogTxtFile_IotPxEngineServer(const CString &strLogString)
{
	if (g_nWriteLogTxtFile == 0)
	{
		return;
	}

	CFile oFile;
	CString strPath;
	strPath = _P_GetBinPath();
	strPath += "IotProtoServerLog.txt";
	BOOL bRet = FALSE;

	if (!IsFileExist(strPath))
	{
		bRet = oFile.Open(strPath, CFile::modeCreate | CFile::modeWrite);
	}
	else
	{
#ifdef _PSX_IDE_QT_
		bRet = oFile.Open(strPath, CFile::modeNoTruncate/*modeWrite*/);
#else
		bRet = oFile.Open(strPath, CFile::modeWrite);
#endif
	}
 
	if (bRet)
	{
		oFile.SeekToEnd();
		SYSTEMTIME tm;
		CString strTmp;
		::GetLocalTime(&tm);
		strTmp.Format(_T("%d-%d-%d %d-%d-%d.%d   "), tm.wYear, tm.wMonth, tm.wDay
			, tm.wHour, tm.wMinute, tm.wSecond,tm.wMilliseconds);

		strTmp += strLogString;
		char *pWriteString = NULL;
		CString_to_char(strTmp,&pWriteString);
		oFile.Write(pWriteString, strlen(pWriteString));
		oFile.Write("\r\n", 2);
		oFile.Close();
		delete pWriteString;

	}
}

//监视服务端所有的命令报文
extern long g_nSttLogServerSpyAllCmd;


CIotPxEngineServer::CIotPxEngineServer()
{
	g_theIotPxEngineServer = this;

	CDataMngrXmlRWKeys::Create();
	CSttCmdDefineXmlRWKeys::Create();
	m_oPxCommChannelInterfaceRef.SetMaxCount(100);

#ifdef _PSX_IDE_QT_
	m_pIotPxEngineServerWnd = new CIotPxEngineServerWnd_Linux();
#else
	m_pIotPxEngineServerWnd = new CIotPxEngineServerWnd_Win();
#endif

	m_pIotPxEngineServerWnd->CreateIotPxEngineServerWnd();
	m_pIotPxEngineServerWnd->m_pIotPxEngineServer = this;
}

CIotPxEngineServer::~CIotPxEngineServer()
{
	long nCount = m_oPxCommChannelInterfaceRef.GetObjectCount();
	CIotPxCommChannelInterface *pIotPxCommChannelInterface = NULL;

	for (int nIndex = 0; nIndex<nCount;nIndex++)
	{
		pIotPxCommChannelInterface = m_oPxCommChannelInterfaceRef.GetObject(nIndex);

		if (pIotPxCommChannelInterface != NULL)
		{
			delete pIotPxCommChannelInterface;
		}
	}
//	m_oIotPxCommChannelInterfaceRef.Free();
	CDataMngrXmlRWKeys::Release();
	CSttCmdDefineXmlRWKeys::Release();
}

CIotPxEngineServer*  CIotPxEngineServer::Create()
{
	g_nPxEngineServerRef++;

	if (g_nPxEngineServerRef == 1)
	{
		g_pIotPxEngineServer = new CIotPxEngineServer();
	}

	return g_pIotPxEngineServer;
}

void CIotPxEngineServer::Release()
{
	g_nPxEngineServerRef--;

	if (g_nPxEngineServerRef == 0)
	{
		delete g_pIotPxEngineServer;
		g_pIotPxEngineServer = NULL;
	}
}

void CIotPxEngineServer::RegisterFactory(CIotPxEngineFactoryBase *pFactory)
{
	g_pIotPxEngineServer->m_oIotPxEngineFactoryMngr.AddNewChild(pFactory);
}

void CIotPxEngineServer::POST_WM_IOT_CMD_MSG(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	if (g_pIotPxEngineServer != NULL)
	{
// 		if (pIotCmd->m_strID == STT_CMD_TYPE_IOT_CreateDevice)
// 		{
// 			if (!g_pIotPxEngineServer->m_oIotPxCommChannelInterfaceRef.HasObject(pPxCommChn))//zhouhj 2024.9.21 创建设备时,添加索引,关闭删除时,删除此索引
// 			{
// 				g_pIotPxEngineServer->m_oIotPxCommChannelInterfaceRef.AddObject(pPxCommChn);
// 			}
// 		}

		CString strLogMsg;
		strLogMsg.Format("CIotPxEngineServer::POST_WM_IOT_CMD_MSG(%s),pPxCommChn == 0x%08X",pIotCmd->m_strID.GetString(),(DWORD)pPxCommChn);
		Global_WriteLogTxtFile_IotPxEngineServer(strLogMsg);
		g_pIotPxEngineServer->m_pIotPxEngineServerWnd->PostMessage(WM_IOT_CMD_MSG, (WPARAM)pPxCommChn, (LPARAM)pIotCmd);
	}
}

//shaolei 从需要删除的设备列表中移除，因为已经从外部删除了
void CIotPxEngineServer::RemoveDeviceFromFolDel(CIotPxEngineDeviceBase *pDevice)
{
	m_oDeviceMngrForDel.Remove(pDevice);
}

/*
<iot-cmd name="" id=" CreateDevice" testor="">
	<paras>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data name="" id="ppxml-file" data-type="" value="SZNR-TTU.ppxml"/>
		<data name="" id="dvm-file" data-type="" value="SZNR-TTU.xml"/>
		<data name="" id="cmm-cfg-file" data-type="" value="SZNR-TTU202012131700"/>
		<group name="" id="comm-config" data-type="" value="">
			<data name="" id="tcp-client" data-type="" value="">
				<value name="" id="local-ip" data-type="" value="192.168.10.10"/>
				<value name="" id="local-port" data-type="" value="20183"/>
				<value name="" id="remote-ip" data-type="" value="192.168.10.101"/>
				<value name="" id="remote-port" data-type="" value="2404"/>
			</data>
		</group>
	</paras>
</iot-cmd>
*/
CIotPxEngineDeviceBase* CIotPxEngineServer::CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd)
{
    DeleteAllDevice();//Delete All Device In CreateDevice CMD;

	CString strDeviceSN, strEngineProgID;
	CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();
	iotpx_LogSttCmd(pIotCmd);

	if (! pIotCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN))
	{
		return NULL;
	}

	if (! pIotCmd->GetParasDataValueByID(STT_CMD_PARA_EngineProgID, strEngineProgID))
	{
		return NULL;
	}

	CIotPxEngineDeviceBase *pFind = (CIotPxEngineDeviceBase*)m_oIotPxEngineDeviceMngr.FindByID(strDeviceSN);

	if (pFind != NULL)
	{
		pFind->Process_Cmd_IOT_CreateDevice(pPxCommChn, oDrvIotCmd);

		return pFind;
	}

	CIotPxEngineFactoryBase *pFactory = (CIotPxEngineFactoryBase*)m_oIotPxEngineFactoryMngr.FindByID(strEngineProgID);

	if (pFactory == NULL)
	{
		CString strMsg = "factory not regieter : " + strEngineProgID;
		CLogPrint::LogString(XLOGLEVEL_ERROR,  strMsg);
		return NULL;
	}

	pFind = pFactory->CreateDevice(pPxCommChn, oDrvIotCmd);

	if (pFind != NULL)
	{
		m_oIotPxEngineDeviceMngr.AddTail(pFind);
	}

	return pFind;
}

void CIotPxEngineServer::CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd) 
{
	CString strDeviceSN, strEngineProgID;
	CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();
	pPxCommChn->m_PxEngineDevice = NULL;  //清空设备指针

	if ( ! pIotCmd->HasSttParas())
	{
		CloseByPxCommChannel(pPxCommChn);
		return;
	}

	if (! pIotCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN))
	{
		CloseByPxCommChannel(pPxCommChn);
		return ;
	}

// 	if (! pIotCmd->GetParasDataValueByID(STT_CMD_PARA_EngineProgID, strEngineProgID))
// 	{
// 		return ;
// 	}

	CIotPxEngineDeviceBase *pFind = (CIotPxEngineDeviceBase*)m_oIotPxEngineDeviceMngr.FindByID(strDeviceSN);

	if (pFind != NULL)
	{
		//返回值：表示没有通信端口连接到这个设备。此处暂时不考虑复杂的冲突过程
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Close Device [%s]"), strDeviceSN.GetString());
		long nRet = pFind->Process_Cmd_IOT_CloseDevice(pPxCommChn, oDrvIotCmd);

		if (nRet == 0)
		{
			m_oIotPxEngineDeviceMngr.Remove(pFind);
			//delete pFind;   //不能在此删除，否则会导致出错，应该在实际关闭的时候删除对象
			m_oDeviceMngrForDel.AddTail(pFind);
		}
	}
}

void CIotPxEngineServer::DeleteAllDevice()
{
    POS pos = m_oDeviceMngrForDel.GetHeadPosition();
    CIotPxEngineDeviceBase *p = NULL;

    while (pos != NULL)
    {
        p = (CIotPxEngineDeviceBase*)m_oDeviceMngrForDel.GetNext(pos);
        //delete p;
    }
}

void CIotPxEngineServer::CloseByPxCommChannel(CIotPxCommChannelInterface *pPxCommChn) 
{
	POS pos = m_oIotPxEngineDeviceMngr.GetHeadPosition();
	CIotPxEngineDeviceBase *p = NULL;

	while (pos != NULL)
	{
		p = (CIotPxEngineDeviceBase *)m_oIotPxEngineDeviceMngr.GetNext(pos);

		if (p->CloseByPxCommChannel(pPxCommChn))
		{
			m_oIotPxEngineDeviceMngr.Remove(p);
			//delete pFind;   //不能在此删除，否则会导致出错，应该在实际关闭的时候删除对象
			m_oDeviceMngrForDel.AddTail(p);

			break;
		}
	}
}


void CIotPxEngineServer::OnIotCmd(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
// 	if (!m_oIotPxCommChannelInterfaceRef.HasObject(pPxCommChn))//zhouhj 2024.9.21 排除未创建的设备
// 	{
// 		return;
// 	}

	CSttIotCmdDriver oDrvIotCmd;
	oDrvIotCmd.AttachXObject(pIotCmd);
	CString strLogMsg;
	strLogMsg.Format("CIotPxEngineServer::OnIotCmd(%s)-Start,pPxCommChn == 0x%08X",pIotCmd->m_strID.GetString(),(DWORD)pPxCommChn);
	Global_WriteLogTxtFile_IotPxEngineServer(strLogMsg);

	if (pIotCmd->m_strID ==  STT_CMD_TYPE_IOT_CreateDevice )
	{//创建设备
		Process_Cmd_IOT_CreateDevice(pPxCommChn, oDrvIotCmd);
	}
	else if (pIotCmd->m_strID ==  STT_CMD_TYPE_IOT_CloseDevice )
	{
		Process_Cmd_IOT_CloseDevice(pPxCommChn, oDrvIotCmd);
		long nRefCount = pPxCommChn->GetRefCount();
//		m_oIotPxCommChannelInterfaceRef.FreeObject(pPxCommChn);
		pPxCommChn->Release(FALSE);
		m_oPxCommChannelInterfaceRef.AddObject(pPxCommChn);
		
		if (nRefCount == 1)
		{
			//刚释放的是最后一次
			pPxCommChn = NULL;
		}
// 		delete pPxCommChn;
// 		pPxCommChn = NULL;
	}
	else
	{
		if (pPxCommChn->m_PxEngineDevice != NULL)
		{
			pPxCommChn->m_PxEngineDevice->Process_Cmd_IOT(pPxCommChn, oDrvIotCmd);
		}
	}
	
	strLogMsg.Format("CIotPxEngineServer::OnIotCmd(%s)-End,pPxCommChn == 0x%08X.",pIotCmd->m_strID.GetString(),(DWORD)pPxCommChn);
	Global_WriteLogTxtFile_IotPxEngineServer(strLogMsg);
}

void CIotPxEngineServer::AddIotPxCommChannelInterfaceRef(CIotPxCommChannelInterface *pPxCommChn)
{

}


long CIotPxEngineServer::Process_Cmd_IOT_CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();

	//返回reply   不能返回EngineEvent_ConnectDeviceSuccessful
// 	iotpx_ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_ACK,
// 		NULL,STT_SYS_STATE_ID_ConnectState,EngineEvent_ConnectDeviceSuccessful);
	iotpx_ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_ACK, NULL);

	//创建设备对象
	CIotPxEngineDeviceBase *pNewDevice = CreateDevice(pPxCommChn, oDrvIotCmd);
	pPxCommChn->m_PxEngineDevice = pNewDevice;

	if (pNewDevice != NULL)
	{
		pNewDevice->AddCommCh(pPxCommChn);

		//返回执行成功   
 		iotpx_ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_SUCCESS,NULL);
			//,STT_SYS_STATE_ID_ConnectState,EngineEvent_ConnectDeviceSuccessful);
		//2023-5-28  lijunqing 不能返回连接状态

		return TRUE;
	}
	else
	{
		//返回执行失败
		iotpx_ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE,NULL);;
			//,STT_SYS_STATE_ID_ConnectState,EngineEvent_ConnectDeviceFailed);
			//2023-5-28  lijunqing 不能返回连接状态

		return FALSE;
	}
}


long CIotPxEngineServer::Process_Cmd_IOT_CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();

	if (pIotCmd->HasSttParas())
	{ //2023-3-12  lijunqing  Socket断开时等效close-device指令
		//返回reply
		iotpx_ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_ACK);

		//返回执行成功
		iotpx_ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_SUCCESS);
	}
	
	//关闭设备
	CloseDevice(pPxCommChn, oDrvIotCmd);

	return TRUE;
}

