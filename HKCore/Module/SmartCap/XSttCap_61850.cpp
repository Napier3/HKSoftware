#include "stdafx.h"
#include "XSttCap_61850.h"

extern CXWndInterface *g_theCapDeviceMngrMsgRcvWnd;

CXSttCap_61850::CXSttCap_61850(CXCapPkgBufferMngrInterface *pSttXCapBufferMngr)
{
	m_pSttXCapBufferMngr = pSttXCapBufferMngr;
	m_pSttTestAppCfg = NULL;
	m_pSttCapThread = NULL;
	m_pRecordTestCalThread = NULL;
	m_pProtocol61850 = NULL;
	m_bUseSttTestEngineClientData = TRUE;
	
#ifdef _XSmartCap_use_SmDb_
	m_pSmDbWriteThread = NULL;
	m_pCapFrameDbFileServer = NULL;
	m_pCapFrameDbFileClient = NULL;

	m_pCapFrameDbFileServer = new CCapFrameDbFile();
	m_pCapFrameDbFileClient = new CCapFrameDbArea();
#endif

	m_pProtocol61850 = new CProtocol61850();
	m_oCapBufferMngr61850.InitXSmMemBufferMngr();
	m_pSttXCapBufferMngr->AttachPkgTransDest(&m_oCapBufferMngr61850);

	m_pFrameMemBufferMngr = &m_oCapBufferMngr61850;

	m_pProtocol61850->SetCapDeviceMngr(&m_oCapDeviceAll);

	m_bTestStarted = FALSE;
	m_bInStateTest = FALSE;
	m_nCount = 0;
	m_pSttClientTestEngine = new CSttClientTestEngine;

	g_nRtFrequencyCalMode = FREQUENCY_CAL_MODE_FFT_DFT;
}

CXSttCap_61850::~CXSttCap_61850(void)
{
	if (m_pSttCapThread != NULL)
	{
		m_pSttCapThread->ReleaseCapture();
	}

	delete m_pSttXCapBufferMngr;
	FreeClientTestEngine();
}

void CXSttCap_61850::FreeClientTestEngine()
{
	if (m_pSttClientTestEngine != NULL)
	{
		m_pSttClientTestEngine->DisConnect();
		delete m_pSttClientTestEngine;
		m_pSttClientTestEngine = NULL;
	}
}

void CXSttCap_61850::OnRcdBufRcv(BYTE *pBuffer, long nLen)
{
	m_pSttXCapBufferMngr->AddFrameBuffer(pBuffer, nLen);
}

long CXSttCap_61850::OnRcdRcvClosed()  ////2022-6-30  lijunqing 
{
	if (!m_bTestStarted)
	{
		
	}

	return 0;
}

void CXSttCap_61850::CreateCapTrhead()
{
	FreeCapture();

	m_pSttCapThread = CSttCapThread::CreateNewSttCapThread(m_pSttXCapBufferMngr);
	m_pSttCapThread->SetCapMemBufferMngr(&m_oCapBufferMngr61850);
	m_pSttCapThread->SetProtocol(m_pProtocol61850);

	//xujinqiang0615add
	m_pSttCapThread->CreateCapture();

#ifdef _XSmartCap_use_SttRcdSocket_
	m_pSttCapThread->SetCaptureThread(m_oSttRcdSocketBase.m_pSttRcdRecvThread);
#endif

#ifdef _XSmartCap_use_SmDb_
	m_pCapFrameDbFileServer->Reset();
	if (m_pSmDbWriteThread == NULL)
	{
		m_pSmDbWriteThread = CSmDbWriteThread::CreateSmDbWriteThread();
	}
#endif

	m_pSttCapThread->SetCapMemBufferMngr(&m_oCapBufferMngr61850);
	m_pFrameMemBufferMngr = m_pSttCapThread->GetCapMemBufferMngr();

	//xujinqiang20200704：历史报文记录原始报文，不需要分帧
#ifdef _XSmartCap_use_SmDb_
	m_pSmDbWriteThread->InitThread(m_pSttXCapBufferMngr->GetXSmMemBufferMngr(), m_pCapFrameDbFileServer);
#endif
	
	if (m_pRecordTestCalThread == NULL)
	{
		m_pRecordTestCalThread = CRecordTestCalThread::CreateRecordTestCalThread();
		m_pRecordTestCalThread->SetRecordTest(m_oCapDeviceChRecordMngr.m_pRecordTest);
	}

	m_oCapDeviceAll.SetRecordTest(m_oCapDeviceChRecordMngr.m_pRecordTest);
	m_pSttCapThread->SetRecordTestCalThread(m_pRecordTestCalThread);
	m_pSttCapThread->SetCapDeviceAll(&m_oCapDeviceAll);
}

BOOL CXSttCap_61850::BeginCap(CIecCfgDatasMngr *pIecfgDataMngr, BOOL bClearDevices)
{

	return TRUE;
}

BOOL CXSttCap_61850::StopCap()
{
	if (!m_bUseSttTestEngineClientData)
	{
		m_bTestStarted = FALSE;
		m_bInStateTest = FALSE;
		return TRUE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++++++进入函数：CXSttCap_61850::StopCap()"));
	long nRet = m_pSttClientTestEngine->Test_StopTest(_T(""));
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++++++退出函数：CXSttCap_61850::StopCap()"));

	if (nRet == STT_CMD_ExecStatus_SocketClose)
	{
		m_bTestStarted = FALSE;
		m_bInStateTest = FALSE;
		ConnectServerEx();
		return TRUE;
	}

	if (Stt_Is_ExecStatus_Success(nRet))
	{
// 		if (m_pSttCapThread != NULL)
// 		{
// 			m_pSttCapThread->ReleaseCapture();
// 		}

		m_bTestStarted = FALSE;
		m_bInStateTest = FALSE;
		return TRUE;
	}
	else
	{
		if (!m_pSttClientTestEngine->IsConnectServerSucc())
		{
			m_bTestStarted = FALSE;
			m_bInStateTest = FALSE;
			return ConnectServerEx();
		}
	}
	
	return FALSE;

	//OnBeginSmDbWrite(); //xujinqiang0616 抓包同时写的，抓包结束后不需要再写
}


BOOL CXSttCap_61850::IsCapExit()
{
	if (m_pSttCapThread != NULL)
	{
		if (!m_pSttCapThread->HasAllCapThreadExit())
		{
			return FALSE;
		}
	}

	return TRUE;
}


BOOL CXSttCap_61850::CanClose()
{
	if (!IsCapExit())
	{
		return FALSE;
	}

#ifndef _PSX_IDE_QT_
	if (m_pSmDbWriteThread != NULL)
	{
		if (!m_pSmDbWriteThread->WaitForExit())
		{
			return FALSE;
		}
	}
#endif

	return TRUE;
}


BOOL CXSttCap_61850::IsInCapture()
{
	if (m_pSttCapThread == NULL)
	{
		return FALSE;
	}

	return m_pSttCapThread->IsCaptureStarted();
}

void CXSttCap_61850::FreeCapture()
{
	if (m_pSttCapThread != NULL)
	{
		m_pSttCapThread->ExitCapture();
		delete m_pSttCapThread;
		m_pSttCapThread = NULL;
	}

	if (m_pRecordTestCalThread != NULL)
	{
		m_pRecordTestCalThread->Exit();
#ifdef _PSX_IDE_QT_
		m_pRecordTestCalThread->wait();
#endif
		m_pRecordTestCalThread = NULL;
	}
}


void CXSttCap_61850::BeginRecord()
{
	m_pSttXCapBufferMngr->ResetBuffer();
	CX61850CapBase::BeginRecord();
}

void CXSttCap_61850::ExitInstance()
{
	FreeCapture();

	if (m_pProtocol61850 != NULL)
	{
		delete m_pProtocol61850;
		m_pProtocol61850 = NULL;
	}

#ifdef _XSmartCap_use_SmDb_
	if (m_pCapFrameDbFileServer != NULL)
	{
		delete m_pCapFrameDbFileServer;
		m_pCapFrameDbFileServer = NULL;
	}

	if (m_pCapFrameDbFileClient != NULL)
	{
		delete m_pCapFrameDbFileClient;
		m_pCapFrameDbFileClient = NULL;
	}
#endif
}

BOOL CXSttCap_61850::ConnectServerEx()
{
	if (!m_bUseSttTestEngineClientData)
	{
		return TRUE;
	}

	if(m_pSttClientTestEngine->IsConnectServerSucc())
	{
		return TRUE;
	}

	return ConnectServer(TRUE);
// 	BOOL bRet = FALSE;
// 
// 	bRet = m_pSttClientTestEngine->ConnectServer(m_pSttTestAppCfg->GetTestAppIP(), m_pSttTestAppCfg->GetTestServerPort());
// 
// 	if(!bRet)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("连接测试仪【%s,%d】失败"),m_pSttTestAppCfg->GetTestAppIP(), m_pSttTestAppCfg->GetTestServerPort());
// 		return FALSE;
// 	}
// 
// 	long nRet = m_pSttClientTestEngine->System_Login_Local_Test();
// 
// 	return nRet;
}

BOOL CXSttCap_61850::CreateSttRcdSocket()
{
#ifdef _XSmartCap_use_SttRcdSocket_
	if (m_oSttRcdSocketBase.IsSocketValid()&&
		(m_oSttRcdSocketBase.m_pSttRcdRecvThread != NULL)/*m_hSocket != 0*/)
	{
		return TRUE;
	}

	CString strTestAppIP;
	strTestAppIP = m_pSttTestAppCfg->GetTestAppIP();

	BOOL bRet = m_oSttRcdClientSocket.ConnectServer(strTestAppIP, STT_PORT_TEST_SERVER/*m_pSttTestAppCfg->GetTestServerPort()*/);

	if(!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("连接测试仪【%s,%d】失败"),strTestAppIP.GetString(), m_pSttTestAppCfg->GetTestServerPort());
		return FALSE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("连接测试仪【%s,%d】成功"),strTestAppIP.GetString(), m_pSttTestAppCfg->GetTestServerPort());
	CTickCount32 oTick;
	//20201221 shaolei 先注释此延时，为减少测试准备时间
	//oTick.DoEvents(1000);  //延迟发送登录命令，防止底层空指针  shaolei

	CSttSystemCmd oSysCmd;
	oSysCmd.m_strID = STT_CMD_TYPE_SYSTEM_Login;
	oSysCmd.m_strTestor = STT_SOFT_ID_RECORD;

	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("建立报文录波通道......"));


	long nRet = m_oSttRcdClientSocket.SendCmd(&oSysCmd);	
	//20201221 shaolei 先注释此延时，为减少测试准备时间
	//oTick.DoEvents(3000);    //防止底层上一次录波发送线程未退出，等待退出后，测试连接登录   20201103

	//nRet = m_pSttClientTestEngine->System_Login_Local_Test();

	if (nRet>0/*Stt_Is_ExecStatus_Success(nRet)*/)//20220621 zhouhj SendCmd命令返回值为发送成功的报文长度
	{
		m_oSttRcdSocketBase.SetReceiveBuffLen( STT_FILECMD_MAX_LEN );
		m_oSttRcdSocketBase.AttatchRcdBufRcvMsg(this);
		m_oSttRcdSocketBase.AttatchSocketDatabase(&m_oSttRcdClientSocket);
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("连接完成，准备开始测试......"));
		return TRUE;
	}
 	else
 	{
 		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Login failed"));
 		return FALSE;
 	}
#endif

	return FALSE;
}

BOOL CXSttCap_61850::ConnectServer(BOOL bEngineConnect)
{
	BOOL bRet = FALSE;

	if(bEngineConnect)
	{
		if (m_bUseSttTestEngineClientData)
		{
			bRet = m_pSttClientTestEngine->ConnectServer(m_pSttTestAppCfg->GetTestAppIP(), m_pSttTestAppCfg->GetTestServerPort());

			if(!bRet)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("连接测试仪【%s,%d】失败")
					,m_pSttTestAppCfg->GetTestAppIP().GetString()
					, m_pSttTestAppCfg->GetTestServerPort());
				return FALSE;
			}
		}
	}
	
	return CreateSttRcdSocket();
}

void CXSttCap_61850::DisConnectServer()
{
	if (m_bUseSttTestEngineClientData)
	{
		m_pSttClientTestEngine->DisConnect();
	}

	//m_oSttClientSocket.CloseSocket();

#ifdef _XSmartCap_use_SttRcdSocket_
	m_oSttRcdSocketBase.SttRcdSocketClose();
#endif
}


void CXSttCap_61850::ReadHexTestFile()
{
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("XSttCap_61850.txt");

	m_pSttXCapBufferMngr->ReadHexTestFile(strFile);
}

BOOL CXSttCap_61850::GetStatesOutputCmd(CDvmDataset *pDsStates, CDataGroup &oDataGroup)
{
	ASSERT(pDsStates != NULL && pDsStates->m_strID == _T("dsState"));

	CDvmData *pDvmData = (CDvmData*)pDsStates->FindByID(_T("StateCount"));
	long nStateCount = CString_To_long(pDvmData->m_strValue);

	CDataGroup *pSubGroup = NULL;
	CDvmData *pDvmData1,*pDvmData2,*pDvmData3;
	CString strDataID, strCount, strState_Long, strState_TrigType/*, strState_Bout*/;
	long nStateIdx = 0;

	CDvmData *pDataStateCount = oDataGroup.AddNewData(_T(""),_T("StateCount"),_T("long"),_T("0"));


	// zhoulei 2020-12-22 xiugai
	pDvmData1 = (CDvmData*)pDsStates->FindByID(_T("BoEnable"));	
	oDataGroup.AddNewData(_T(""),_T("BoEnable"),_T("bool"),pDvmData1->m_strValue);
	pDvmData1 = (CDvmData*)pDsStates->FindByID(_T("GooseBoEnable"));
	oDataGroup.AddNewData(_T(""),_T("GooseBoEnable"),_T("bool"),pDvmData1->m_strValue);

	for (nStateIdx=0;nStateIdx<nStateCount;nStateIdx++)
	{
		pSubGroup = new CDataGroup;
		pSubGroup->m_strID.Format(_T("state%d"),nStateIdx);
		//pSubGroup->m_strName.Format(_T("状态%d"), nStateIdx+1);
		pSubGroup->m_strDataType = _T("State");

		strState_Long.Format(_T("State%d_Long"),nStateIdx+1);
		strState_TrigType.Format(_T("State%d_TrigType"),nStateIdx+1);
	//	strState_Bout.Format(_T("State%d_Bout1"),nStateIdx+1);

		pDvmData1 = (CDvmData*)pDsStates->FindByID(strState_Long);
		pDvmData2 = (CDvmData*)pDsStates->FindByID(strState_TrigType);
// 		pDvmData3 = (CDvmData*)pDsStates->FindByID(strState_Bout);
// 
		if (pDvmData1 == NULL || pDvmData2 == NULL/* || pDvmData3 == NULL*/)
		{
			delete pSubGroup;
			break;
		}
	
		//输出时间（"OutputTime"）
		pSubGroup->AddNewData(_T(""),_T("OutputTime"),_T(""),pDvmData1->m_strValue);

		//触发方式（TrigType）
		pSubGroup->AddNewData(_T(""),_T("TrigType"),_T(""),pDvmData2->m_strValue);


		//开出状态
		CDataGroup *pBoutGroup = new CDataGroup;
		pBoutGroup->m_strID = _T("BOout");
		pBoutGroup->m_strDataType = _T("BOUT");
		pSubGroup->AddNewChild(pBoutGroup);

		CString strOutID, strOutValue, stroutID2;
//		pBoutGroup->AddNewData(_T(""),_T("Bout1State"),_T("DOutputState"),pDvmData3->m_strValue);
		for (int i=1;i<=8;i++)
		{
			strOutID.Format(_T("State%d_Bout%d"), nStateIdx+1, i);
			stroutID2.Format(_T("Bout%dState"), i);
			strOutValue = _T("0");
			pDvmData3 = (CDvmData*)pDsStates->FindByID(strOutID);
			if (pDvmData3 != NULL)
			{
				strOutValue = pDvmData3->m_strValue;
			}
 			pBoutGroup->AddNewData(_T(""),stroutID2,_T("DOutputState"),strOutValue);
		}

		//开出状态（Bout1~Bout8）
// 		pSubGroup->AddNewData(_T(""),_T("Bout1State"),_T(""),pDvmData3->m_strValue);
// 
// 		CString strOutID;
// 		for (int i=2;i<=8;i++)
// 		{
// 			strOutID.Format(_T("Bout%dState"),i);
// 			pSubGroup->AddNewData(_T(""),strOutID,_T(""),_T("0"));
// 		}

		oDataGroup.AddNewChild(pSubGroup);
	}

	 pDataStateCount->SetAttr( (CString)CDataMngrXmlRWKeys::ValueKey(),nStateIdx);

	return TRUE;
}

void CXSttCap_61850::GetSttRecordParas( CIecCfgDatasMngr *pDatasMngr, CSttParas *pParas, const CString &strIecfgDataID)
{
	long nCount = 0;
	CIecCfgDatasSMV *pSmvMngr = pDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pDatasMngr->GetGoutMngr();
	CDataGroup *pNewGroup = NULL;
	CDvmData *pData = NULL;
	CString strMacValue, strAPPIDValue, strPortValue, strTypeValue;

	pData = new CDvmData;
	pData->m_strID = _T("SubscribeCount");
	pParas->AddNewChild(pData);

	//2020-7-15 lijunqing
	//SMV     不获取SV报文有如下情况
	//GOOSE发布能力GooseSendTest、GOOSE报文一致性GooseCstcTest
	//时间控制准确度TimeControlTest  GOOSE同步差GooseSnyTest
	if (strIecfgDataID != _T("GooseSendTest") && strIecfgDataID != _T("GooseCstcTest")
		&& strIecfgDataID != _T("TimeControlTest") && strIecfgDataID != _T("GooseSnyTest") )
	{
		nCount += GetSttRecordParas_SV(pSmvMngr, pParas, strIecfgDataID);
	}
	m_nCount = nCount;//mym 2020-12-12 为了SMV和GOOSE统一排序；
	//GOOSE OUT
	nCount += GetSttRecordParas_GS(pGoutMngr, pParas, strIecfgDataID);
	
	pData->m_strValue.Format(_T("%d"), nCount);
}

long CXSttCap_61850::GetSttRecordParas_SV(CIecCfgDatasSMV *pSmvMngr, CSttParas *pParas, const CString &strIecfgDataID)
{
	CDataGroup *pNewGroup = NULL;
	CDvmData *pData = NULL;
	CString strMacValue, strAPPIDValue, strPortValue, strTypeValue;

	long nCount = 0;
	POS pos = pSmvMngr->GetHeadPosition();
	CIecCfg92Data *p92Data = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pSmvMngr->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != CFGCLASSID_CIECCFG92DATA)
		{
			continue;
		}

		p92Data = (CIecCfg92Data *)pObj;
		strMacValue.Empty();
		strAPPIDValue.Empty();
		MacString_to_String(p92Data->m_strDestAddress, strMacValue);
		long nAppID = (long)p92Data->m_dwAppID;
		strAPPIDValue.Format(_T("%x"), nAppID);        //需要转成16进制
		long nLen = strAPPIDValue.GetLength();
		CString strBULING;  //补零
		if (nLen < 4)
		{
			for (int i=0; i<4-nLen;i++)
			{
				strBULING.AppendFormat(_T("0"));  //不足四位，前面补零
			}

			strAPPIDValue = strBULING+strAPPIDValue;
		}
		strPortValue.Format(_T("%d"), p92Data->m_nFiber2Index);
		strTypeValue = _T("1");        //goose和SV区分, 1-SV;2-GOOSE;3-FT3

		pNewGroup = new CDataGroup;
		pNewGroup->AddNewData(PARA_DATA_ID_MESTMAC, PARA_DATA_ID_MESTMAC, _T("string"), strMacValue);
		pNewGroup->AddNewData(PARA_DATA_ID_APPID, PARA_DATA_ID_APPID, _T("string"), strAPPIDValue);
		pNewGroup->AddNewData(PARA_DATA_ID_Port, PARA_DATA_ID_Port, _T("string"), strPortValue);
		pNewGroup->AddNewData(PARA_DATA_ID_Type, PARA_DATA_ID_Type, _T("string"), strTypeValue);

		pNewGroup->m_strID.Format(_T("Subscribe%d"), nCount);
		pNewGroup->m_strName = pNewGroup->m_strID;
		pNewGroup->m_strDataType = _T("Subscribe");

		pParas->AddNewChild(pNewGroup);
		nCount++;
	}

	return nCount;
}

long CXSttCap_61850::GetSttRecordParas_GS(CIecCfgGoutDatas *pGoutMngr, CSttParas *pParas, const CString &strIecfgDataID)
{
	CDataGroup *pNewGroup = NULL;
	CDvmData *pData = NULL;
	CString strMacValue, strAPPIDValue, strPortValue, strTypeValue;

	long nCount = m_nCount;//=0 mym 2020-12-12
	POS pos = pGoutMngr->GetHeadPosition();
	CIecCfgGoutData *pGoutData = NULL;
	CIecCfg92Data *p92Data = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pGoutMngr->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != CFGCLASSID_CIECCFGGOUTDATA)
		{
			continue;
		}

		pGoutData = (CIecCfgGoutData *)pObj;
		strMacValue.Empty();
		strAPPIDValue.Empty();
		MacString_to_String(pGoutData->m_strDestAddress, strMacValue);
		long nAppID = (long)pGoutData->m_dwAppID;
		strAPPIDValue.Format(_T("%x"), nAppID);        //需要转成16进制
		long nLen = strAPPIDValue.GetLength();
		CString strBULING;  //补零
		if (nLen < 4)
		{
			for (int i=0; i<4-nLen;i++)
			{
				strBULING.AppendFormat(_T("0"));  //不足四位，前面补零
			}

			strAPPIDValue = strBULING+strAPPIDValue;
		}
		strPortValue.Format(_T("%d"), pGoutData->m_nFiber2Index);
		strTypeValue = _T("2");        //goose和SV区分, 1-SV;2-GOOSE;3-FT3

		pNewGroup = new CDataGroup;
		pNewGroup->AddNewData(PARA_DATA_ID_MESTMAC, PARA_DATA_ID_MESTMAC, _T("string"), strMacValue);
		pNewGroup->AddNewData(PARA_DATA_ID_APPID, PARA_DATA_ID_APPID, _T("string"), strAPPIDValue);
		pNewGroup->AddNewData(PARA_DATA_ID_Port, PARA_DATA_ID_Port, _T("string"), strPortValue);
		pNewGroup->AddNewData(PARA_DATA_ID_Type, PARA_DATA_ID_Type, _T("string"), strTypeValue);

		pNewGroup->m_strID.Format(_T("Subscribe%d"), nCount);
		pNewGroup->m_strName = pNewGroup->m_strID;
		pNewGroup->m_strDataType = _T("Subscribe");

		pParas->AddNewChild(pNewGroup);
		nCount++;
	}

	return nCount;
}

BOOL CXSttCap_61850::StateTest(const CString &strDatasetID)
{
	//从模型中获取相关的数据集
	//<dataset name="时间测量准确度" id="dsArTime" gb-rw-optr="write">
	//根据数据集的参数，拼接状态序列参数，执行StartTest命令
	CDvmDataset *pDataSet = m_pDvmDevice->FindDataset(strDatasetID);

	if (pDataSet == NULL)
	{
		return FALSE;
	}

	CDataGroup oDataGroup;
	GetStatesOutputCmd(pDataSet, oDataGroup);

	long nRet = m_pSttClientTestEngine->Test_StartTest(_T("SttTimeMeasureTest"), &oDataGroup);
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("SttStateTest.xml");
	oDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	if (Stt_Is_ExecStatus_Success(nRet))
	{
		m_bTestStarted = TRUE;
		m_bInStateTest = TRUE;
		return TRUE;
	}

	return FALSE;
}

BOOL CXSttCap_61850::DownIecfgData(const CString &strIecfgDataID, const CString &strSwitchFlag)
{
	////下载配置文件，根据strIecfgDataID从装置配置对象中获取配置数据对象
	////进行配置的转化，转换后下载配置（主要是针对goose out）【有问题问周宏军】
	/*
	<test-cmd type="SYSTEM" name="" id="StartTest" testor="TEST$LOCAL">
		<macro name="" id="Iec61850Config" version="" type="" remark="">
			<paras name="" id="">
				<cfg-datas-mngr name="Iec61850Config" id="Iec61850Config">
				......
				</cfg-datas-mngr>
			<paras>
		<macro>
	<test-cmd>
	*/

//	m_pSttClientTestEngine->Test_StopTest(_T(""));
	if (IsIec61850Config(strIecfgDataID))
	{
		return DownIecfgData_Iec61850Config(strIecfgDataID, strSwitchFlag);
	}

	return DownIecfgData_SttRecord(strIecfgDataID);
}

BOOL CXSttCap_61850::DownIecfgData_SttRecord(const CString &strIecfgDataID)
{
	if (g_nXSmartCapDebugMode)
	{
		m_bTestStarted = TRUE;
		return TRUE;
	}

	//录波通道被关闭，继续打开
	CreateSttRcdSocket();
	
	//根据strIecfgDataID查找配置数据对象，根据“SV控制块”“GOOSE发布”控制块的信息
	//拼接SttRecord功能的参数，执行StartTest命令
	CSttParas oParas;
	long nRet = 0;

	CIecCfgDatasMngr *pDatasMngr = GetDatasMngr(strIecfgDataID);
	if (pDatasMngr == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("查找配置错误：CXSttCap_61850::DownIecfgData_SttRecord：%s")
                                   , strIecfgDataID.GetString());
		return FALSE;
	}

	GetSttRecordParas(pDatasMngr, &oParas, strIecfgDataID);
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("SttRecordTest.xml");

	oParas.SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	nRet = m_pSttClientTestEngine->Test_StartTest(_T("SttRecord"), &oParas);
	oParas.DeleteAll();

	if (Stt_Is_ExecStatus_Success(nRet))
	{
		m_bTestStarted = TRUE;
		return TRUE;
	}
	
	return FALSE;
}

BOOL CXSttCap_61850::DownIecfgData_Iec61850Config( const CString &strIecfgDataID, const CString &strSwitchFlag)
{
#ifndef _PSX_IDE_QT_
    CIecCfgDatasMngr *pDatasMngr = GetDatasMngr(strIecfgDataID);
	CSttParas oParas;

	if (pDatasMngr == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("查找配置错误：CXSttCap_61850::DownIecfgData_Iec61850Config：%s")
                                   , strIecfgDataID.GetString());
		return FALSE;
	}

	CIecCfgDatasMngr *pNew = NULL;
	int nValue = ::atoi(strSwitchFlag.GetString());
	if (nValue==1)
	//if (strSwitchFlag == _T("1"))
	{
		pNew = pDatasMngr->GetAT02D_IecCfgDatasMngr();
		CString strTmp;
		strTmp.Format(_T("D:\\%s.xml"),pDatasMngr->m_strID);
		pNew->SaveXmlFile(strTmp,CCfgDataMngrXmlRWKeys::g_pXmlKeys);
		oParas.AddNewChild(pNew);
	}
	else
	{
		oParas.AddNewChild(pDatasMngr);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(">>>DownIecfgData_Iec61850Config::Test_StartTest"));
	long nRet = m_pSttClientTestEngine->Test_StartTest(_T("Iec61850Config"), &oParas);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DownIecfgData_Iec61850Config::Test_StartTest>>>"));

	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("IEC61850CONFIG.xml");

	oParas.SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oParas.RemoveAll();

	if (pNew != NULL)
	{
		delete pNew;
	}

	if (Stt_Is_ExecStatus_Success(nRet))
	{
		m_bTestStarted = TRUE;
		return TRUE;
	}
#endif

	return FALSE;
}

BOOL CXSttCap_61850::IsRecordTestCalThreadCreated()
{
	if (m_pSttCapThread == NULL)
	{
		return FALSE;
	}

	return m_pSttCapThread->IsRecordTestCalThreadCreated();	
}

BOOL CXSttCap_61850::IsIec61850Config( const CString &strIecfgDataID )
{
	if (strIecfgDataID.Find(CONFIG_ID_GOOSEACCEPTTEST) >= 0)
	{
		return TRUE;
	}

	if (strIecfgDataID.Find(CONFIG_ID_BOUTTIMETEST) >= 0)
	{
		return TRUE;
	}

	if (strIecfgDataID.Find(CONFIG_ID_TIMEMEASURETEST) >= 0)
	{
		return TRUE;
	}

	if (strIecfgDataID.Find(CONFIG_ID_IEC61850CONFIG) >= 0)
	{
		return TRUE;
	}

	return FALSE;
}

void CXSttCap_61850::ReadSoe()
{

}

void CXSttCap_61850::Reset()
{
	m_oCapDeviceAll.Reset();

	//各数据及的分析结果初始化
	ResetRecord_Analysis();
}

void CXSttCap_61850::LOG_DEBUG_INFOR()
{
	m_pSttClientTestEngine->Debug_ConfigDebug(0, 0, 0, 1, 0, 0);
}

BOOL CXSttCap_61850::IecDetect(long nMode, const CString &strCRC)
{
	CDataGroup oDataGroup;
	if (nMode == 0)
	{
		oDataGroup.AddNewData(_T(""),_T("Mode"),_T("long"),_T("0"));
	}
	else if (nMode == 1)
	{
		oDataGroup.AddNewData(_T(""),_T("Mode"),_T("long"),_T("1"));
		oDataGroup.AddNewData(_T(""),_T("CRC"),_T("long"), strCRC);
	}
	
	long nRet = m_pSttClientTestEngine->Test_StartTest(_T("SttIecDetectTest"), &oDataGroup);
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("SttIecDetectTest.xml");
	oDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	if (Stt_Is_ExecStatus_Success(nRet))
	{
		m_bTestStarted = TRUE;
		return TRUE;
	}

	return FALSE;
}

BOOL CXSttCap_61850::WriteIecRcdStep(const CString &strDatasetID)
{
	CDvmDataset *pDataSet = m_pDvmDevice->FindDataset(strDatasetID);

	if (pDataSet == NULL)
	{
		return FALSE;
	}

	CDataGroup oDataGroup;
	GetOutputCmd_302IecRcdStep(pDataSet, oDataGroup);

	long nRet = m_pSttClientTestEngine->Test_StartTest(_T("SttStep6U6I"), &oDataGroup);
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("SttStep6U6I.xml");
	oDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	if (Stt_Is_ExecStatus_Success(nRet))
	{
		m_bTestStarted = TRUE;
		return TRUE;
	}
	return FALSE;
}

BOOL CXSttCap_61850::MUTimeTest(const CString &strDatasetID)
{
	CDvmDataset *pDataSet = m_pDvmDevice->FindDataset(strDatasetID);

	if (pDataSet == NULL)
	{
		return FALSE;
	}

	CDataGroup oDataGroup;
	CString strValue;
	CDvmData *pBLogic = (CDvmData*)pDataSet->FindByID(_T("BOutput"));  //B码逻辑
	CDvmData *pRising = (CDvmData*)pDataSet->FindByID(_T("MUPPS"));  //边沿触发方式
	CDvmData *pTestTime = (CDvmData*)pDataSet->FindByID(_T("TestTime"));  //测试时间

	strValue = _T("0");
	if (pBLogic != NULL)
	{
		strValue = pBLogic->m_strValue;
	}

	oDataGroup.AddNewData(_T(""),_T("Logic"),_T("long"),strValue);

	strValue = _T("0");
	if (pRising != NULL)
	{
		strValue = pRising->m_strValue;
	}

	oDataGroup.AddNewData(_T(""),_T("Rising"),_T("long"),strValue);

	strValue = _T("10");
	if (pTestTime != NULL)
	{
		strValue = pTestTime->m_strValue;
	}

	oDataGroup.AddNewData(_T(""),_T("Sec"),_T("long"),strValue);

	long nRet = m_pSttClientTestEngine->Test_StartTest(_T("SttMUTimeTest"), &oDataGroup);
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("SttMUTimeTest.xml");
	oDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	if (Stt_Is_ExecStatus_Success(nRet))
	{
		m_bTestStarted = TRUE;
		return TRUE;
	}
	return FALSE;
}

BOOL CXSttCap_61850::IEDTest(const CString &strDatasetID)
{
#ifndef _PSX_IDE_QT_
	CDvmDataset *pDataSet = m_pDvmDevice->FindDataset(strDatasetID);

	if (pDataSet == NULL)
	{
		return FALSE;
	}

	CDvmData *pCtrlMode = (CDvmData *)pDataSet->FindByID(_T("CtrlMode"));   //控制方式：0-手动测试；1-自动测试
	CString strCtrlMode = pCtrlMode->m_strValue;
	CDvmData *pTestType = (CDvmData *)pDataSet->FindByID(_T("TestProject")); //测试类型 0-延时测试；1-SOE测试；2-风暴测试
	CString strTestType = pTestType->m_strValue;
	CDvmData *pTestMode = (CDvmData *)pDataSet->FindByID(_T("TestMode"));   //测试模式 0-gse2bin; 1-bout2gse；2-gse2bin复归；3-bout2gse复归
	CString strTestMode = pTestMode->m_strValue;

	CString strMacroID;
	if (strTestMode == IEDTEST_TESTMODE_GSE2BIN || strTestMode == IEDTEST_TESTMODE_GSE2BIN_RESET)
	{
		strMacroID.Format(_T("SttGSEtoBinTest"));
	}
	else
	{
		strMacroID.Format(_T("SttBOtoGSETest"));
	}

	CDataGroup oDataGroup;
	GetOutputCmd_IEDTest(pDataSet, oDataGroup);

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(">>>CXSttCap_61850::IEDTest::Test_StartTest"));
	long nRet = m_pSttClientTestEngine->Test_StartTest(strMacroID, &oDataGroup);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CXSttCap_61850::IEDTest::Test_StartTest>>>"));

// 	CString strTime;
// 	SYSTEMTIME tm;
// 	::GetLocalTime(&tm);
//	strTime.Format(_T("%04d-%02d-%02d_%02d-%02d-%02d__"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
	CString strFile;
	strFile = _P_GetLibraryPath();
//	strFile += strTime;
	strFile += _T("SttIEDTest.xml");
	oDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	if (Stt_Is_ExecStatus_Success(nRet))
	{
		m_bTestStarted = TRUE;

		if (strTestMode == IEDTEST_TESTMODE_GSE2BIN_RESET || strTestMode == IEDTEST_TESTMODE_BOUT2GSE_RESET)
		{
			//复归试验，直接返回成功
			return TRUE;
		}

// 		if (strCtrlMode == IEDTEST_CONTROLMODE_AUTOTEST && strTestType == IEDTEST_TESTTYPE_DELAY)
// 		{
// 			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("----------------------------------------------SetTimer(IEDTEST_AUTOTEST_DELAY_TIMER"));
// 			AfxGetMainWnd()->SetTimer(IEDTEST_AUTOTEST_DELAY_TIMER, 8000, NULL);  //IEDTEST_AUTOTEST_DELAY_TIMER  2035
// 		}
		
		if (strTestType == IEDTEST_TESTTYPE_STORM)
		{
			//风暴测试，需要自己预估时间，通过定时器，结束测试
			long nTestTime = 0;
			CDvmData *pPreTime = (CDvmData *)pDataSet->FindByID(_T("PreFaultTime")); //故障前时间
			CDvmData *pRepeatTime = (CDvmData *)pDataSet->FindByID(_T("RepeatCount"));   //重复次数
			CDvmData *pStateTime = (CDvmData *)pDataSet->FindByID(_T("StateTime"));   //保持时间

			nTestTime += CString_To_long(pRepeatTime->m_strValue) * CString_To_long(pStateTime->m_strValue);   //重复次数 * 保持时间
			nTestTime += CString_To_long(pPreTime->m_strValue);  //  + 故障前时间
			nTestTime += 5000;  // + 5000裕度；

			AfxGetMainWnd()->SetTimer(IEDTEST_STORM_SOE_TIMER, nTestTime, NULL);
		}

		if (strTestType == IEDTEST_TESTTYPE_SOE)
		{
			//SOE测试，需要自己预估时间，通过定时器，结束测试
			long nTestTime = 0;
			long nBinaryCount = GetBinaryMapCount_IEDTest(pDataSet);
			CDvmData *pPreTime = (CDvmData *)pDataSet->FindByID(_T("PreFaultTime")); //故障前时间
			CDvmData *pStateTime = (CDvmData *)pDataSet->FindByID(_T("StateTime"));   //保持时间
			CDvmData *pTimeDelay = (CDvmData *)pDataSet->FindByID(_T("TimeDelay"));   //变位时间间隔

			nTestTime += nBinaryCount * CString_To_long(pTimeDelay->m_strValue);   //开关量数量 * 变位间隔时间
			nTestTime += CString_To_long(pPreTime->m_strValue);  //  + 故障前时间
			nTestTime += CString_To_long(pStateTime->m_strValue);  // + 保持时间
			nTestTime += 5000;  // + 5000裕度；

			AfxGetMainWnd()->SetTimer(IEDTEST_STORM_SOE_TIMER, nTestTime, NULL);
		}

		return TRUE;
	}
#endif

	return FALSE;
}

BOOL CXSttCap_61850::GetOutputCmd_302IecRcdStep(CDvmDataset *pDataset, CDataGroup &oDataGroup)
{
	//基波频率
	CDvmData *pFreq = (CDvmData*)pDataset->FindByID(_T("Freq"));
	oDataGroup.AddNewData(_T(""),_T("_BaseFre"),_T("long"),pFreq->m_strValue);

	//是否叠加谐波
	CDvmData *pIsSuperHarm = (CDvmData*)pDataset->FindByID(_T("IsSuperHarm"));
	//叠加谐波次数
	CDvmData *pHarmCount = (CDvmData*)pDataset->FindByID(_T("HarmCount"));

	//6U6I，12个通道，按索引号0-11分别为：Ua1，Ub1, Uc1, Ua2, Ub2, Uc2, Ia1, Ib1, Ic1, Ia2, Ib2, Ic2
	long nChannelIndex = 0;
	long nHarmIndex = 0;
	CDataGroup *pChannelGroup = NULL;
	CString strAmp, strAng;

	for (nChannelIndex = 0; nChannelIndex <= 11; nChannelIndex++)
	{
		pChannelGroup = new CDataGroup;
		CString strChannelName = g_strListChannelName[nChannelIndex];
		CString strChannelGroup = g_strListChannelGroupName[nChannelIndex];
		pChannelGroup->m_strName = strChannelGroup;
		pChannelGroup->m_strID = strChannelGroup;

		//6U6I 前6个是电压 后6个是电流
		if (nChannelIndex < 6)
		{
			strAmp = _T("U0Amp");
			strAng = _T("U0Ang");
		}
		else
		{
			strAmp = _T("I0Amp");
			strAng = _T("I0Ang");
		}

		CDvmData *pData = (CDvmData *)pDataset->FindByID(strChannelName); //基波幅值
		pChannelGroup->AddNewData(_T(""),strAmp,_T("number"),pData->m_strValue);

		pData = (CDvmData *)pDataset->FindByID(g_strListChannelPh[nChannelIndex]);  //基波相位
		pChannelGroup->AddNewData(_T(""),strAng,_T("number"),pData->m_strValue);

		//谐波
		if (pIsSuperHarm->m_strValue == _T("1"))
		{
			nHarmIndex = CString_To_long(pHarmCount->m_strValue);
			CString strHarm, strHarmPh;
			strHarm.Format(_T("harm%dAmp"), nHarmIndex);
			strHarmPh.Format(_T("harm%dAng"), nHarmIndex);

			pData = (CDvmData *)pDataset->FindByID(g_strListChannelHarm[nChannelIndex]);  //谐波幅值
			pChannelGroup->AddNewData(_T(""),strHarm,_T("number"),pData->m_strValue);

			pData = (CDvmData *)pDataset->FindByID(g_strListChannelHarmPh[nChannelIndex]);  //谐波相位
			pChannelGroup->AddNewData(_T(""),strHarm,_T("number"),pData->m_strValue);
		}

		oDataGroup.AddNewChild(pChannelGroup);
	}

	return TRUE;
}

BOOL CXSttCap_61850::GetOutputCmd_IEDTest(CDvmDataset *pDataset, CDataGroup &oDataGroup)
{
	CDvmData *pTestType = (CDvmData *)pDataset->FindByID(_T("TestProject")); //测试类型 0-延时测试；1-SOE测试；2-风暴测试
	CString strValue = pTestType->m_strValue;
	CDvmData *pCtrlMode = (CDvmData *)pDataset->FindByID(_T("CtrlMode"));   //控制方式：0-手动测试；1-自动测试
	CString strCtrlMode = pCtrlMode->m_strValue;
	CDvmData *pTestMode = (CDvmData *)pDataset->FindByID(_T("TestMode"));  //测试模式 0-gse2bin; 1-bout2gse；2-gse2bin复归；3-bout2gse复归
	CDvmData *pPreFaultTime = (CDvmData *)pDataset->FindByID(_T("PreFaultTime"));   //故障前时间
	CDvmData *pStateTime = (CDvmData *)pDataset->FindByID(_T("StateTime"));  //保持时间
	CDvmData *pTimeDelay = (CDvmData *)pDataset->FindByID(_T("TimeDelay"));   //变位时间间隔
	CDvmData *pGin = (CDvmData *)pDataset->FindByID(_T("Gin"));
	CDvmData *pGout = (CDvmData *)pDataset->FindByID(_T("Gout"));

	oDataGroup.AddNewData(_T(""),_T("TestType"),_T("long"),strValue);
	oDataGroup.AddNewData(_T(""),_T("DataMode"),_T("long"),pTestMode->m_strValue);  
	oDataGroup.AddNewData(_T(""),_T("FaultPreTime"),_T("long"),pPreFaultTime->m_strValue); 
	oDataGroup.AddNewData(_T(""),_T("OutputTime"),_T("long"),pTimeDelay->m_strValue);  
	oDataGroup.AddNewData(_T(""),_T("BoKeepTime"),_T("long"),pStateTime->m_strValue); 

	//如果延时测试复归，直接返回
	//只有延时测试，才需要复归
	if (pTestMode->m_strValue == IEDTEST_TESTMODE_GSE2BIN_RESET || IEDTEST_TESTMODE_GSE2BIN_RESET == pTestMode->m_strValue)
	{
		if (strCtrlMode == IEDTEST_CONTROLMODE_MANUTEST)
		{
			ResetBinaryMap_Data(pGout);
			ResetBinaryMap_Data(pGin);
		}

		return TRUE;
	}

	if (strValue == IEDTEST_TESTTYPE_DELAY)
	{
		//延时测试
		return GetOutputCmd_IEDTest_Delay(pDataset, oDataGroup);
	}
	else if (strValue == IEDTEST_TESTTYPE_SOE)
	{
		//SOE测试
		return GetOutputCmd_IEDTest_SOE(pDataset, oDataGroup);
	}
	else if (strValue == IEDTEST_TESTTYPE_STORM)
	{
		//风暴测试
		return GetOutputCmd_IEDTest_Storm(pDataset, oDataGroup);
	}

	return TRUE;
}

BOOL CXSttCap_61850::GetOutputCmd_IEDTest_Delay( CDvmDataset *pDataset, CDataGroup &oDataGroup)
{
	CDvmData *pTestMode = (CDvmData *)pDataset->FindByID(_T("TestMode"));  //测试模式 0-gse2bin; 1-bout2gse；2-gse2bin复归；3-bout2gse复归
	CString strTestMode = pTestMode->m_strValue;

	//先根据传递的变位的索引号和状态，对数据集进行更新
	//数据集更新，已经挪到类CSmartCapCtrl中
	CString strIDMap;
	CDvmData *pBinaryMap = NULL;
	if (strTestMode == IEDTEST_TESTMODE_GSE2BIN)
	{
		strIDMap = _T("Gout");
	}
	else if(strTestMode == IEDTEST_TESTMODE_BOUT2GSE)
	{
		strIDMap = _T("Gin");
	}
	else
	{
		return TRUE;
	}

	pBinaryMap = (CDvmData *)pDataset->FindByID(strIDMap);

	//再进行状态添加；
	CString strStateCount;
	strStateCount.Format(_T("%d"), 1);
	oDataGroup.AddNewData(_T(""),_T("StateCount"),_T("long"),strStateCount);

	CDataGroup *pState = new CDataGroup;
	pState->m_strID.Format(_T("State1"));
	oDataGroup.AddNewChild(pState);
	POS pos = pBinaryMap->GetHeadPosition();
	long nIndex = 0;

	while (pos != NULL)
	{
		CDvmValue *pValue = (CDvmValue *)pBinaryMap->GetNext(pos);
		CString strIndex = pValue->m_strID.Right(3);   //ID诸如bin001  bin002  bout001  bout002这种，取后三位即可
		nIndex = CString_To_long(strIndex);

		if (pValue->m_strValue != _T("-1"))
		{
			CDvmData *pNew = new CDvmData;
			pNew->m_strID.Format(_T("Bout%d"), nIndex);

			if (CString_To_double(pValue->m_strValue)>0)//zhouhj 20200919 当开入结果填入测试时间时，影响正常设置
			{
				pNew->m_strValue = _T("1");
			}
			else
			{
				pNew->m_strValue = pValue->m_strValue;
			}

			pNew->m_strDataType.Format(_T("DOutputState"));
			pState->AddNewChild(pNew);
		}
	}

	//延时测试，分为自动测试和手动测试两种控制方式：
	//手动测试：两个状态，点一个，变一个；
	//自动测试：根据开关量数量，自动依次变化（界面命令变一次，剩余变化在反馈的REPORT中变化）；
// 	CDvmData *pCtrlMode = (CDvmData *)pDataset->FindByID(_T("CtrlMode"));   //控制方式：0-手动测试；1-自动测试
// 	CString strCtrlMode = pCtrlMode->m_strValue;
// 
// 	if (strCtrlMode == _T("0"))
// 	{
// 		return GetOutputCmd_IEDTest_Delay_ManuTest(pDataset, oDataGroup, strSwitchIndex, strSwitchState);
// 	}
// 	else if (strCtrlMode == _T("1"))
// 	{
// 		return GetOutputCmd_IEDTest_Delay_AutoTest(pDataset, oDataGroup, strSwitchIndex, strSwitchState);
// 	}

	return TRUE;
}

//自动测试，此函数不用
BOOL CXSttCap_61850::GetOutputCmd_IEDTest_Delay_AutoTest(CDvmDataset *pDataset, CDataGroup &oDataGroup, const CString &strSwitchIndex, const CString &strSwitchState)
{
	CDvmData *pTestMode = (CDvmData *)pDataset->FindByID(_T("TestMode"));  //测试模式 0-gse2bin; 1-bout2gse；2-gse2bin复归；3-bout2gse复归
	CString strTestMode = pTestMode->m_strValue;
	//BinaryCount的获取函数 移到类CSmartCapCtrl中，后续可以在CXSttCap_61850中增加一个成员，用于记录；
	//long nBinaryCount = GetBinMapCount_IEDTest(strTestMode);   //获取映射的开关量数量
	CString strStateCont;
	//strStateCont.Format(_T("%d"), nBinaryCount+1);
	oDataGroup.AddNewData(_T(""),_T("StateCount"),_T("long"),strStateCont);

	CDataGroup *pState = NULL;
	CDvmData *pNew = NULL;
	//先加初始态：
	pState = new CDataGroup;
	pState->m_strID.Format(_T("State1"));
	oDataGroup.AddNewChild(pState);

	//初始态全部为0
// 	for (long n=1; n<=nBinaryCount; n++)
// 	{
// 		pNew = new CDvmData;
// 		pNew->m_strID.Format(_T("Bout%d"), n);
// 		pNew->m_strValue.Format(_T("0"));
// 		pNew->m_strDataType.Format(_T("DOutputState"));
// 		pState->AddNewChild(pNew);
// 	}

	//再加故障态
// 	for (long nIndex=2; nIndex<=nBinaryCount+1; nIndex++)
// 	{
// 		pState = new CDataGroup;
// 		pState->m_strID.Format(_T("State%d"), nIndex);
// 		oDataGroup.AddNewChild(pState);
// 
// 		for (long i=1; i<=nBinaryCount; i++)
// 		{
// 			pNew = new CDvmData;
// 			pNew->m_strID.Format(_T("Bout%d"), i);
// 			pNew->m_strDataType.Format(_T("DOutputState"));
// 
// 			if (i == nIndex-1)
// 			{
// 				pNew->m_strValue.Format(_T("1"));
// 			}
// 			else
// 			{
// 				pNew->m_strValue.Format(_T("0"));
// 			}
// 			
// 			pState->AddNewChild(pNew);
// 		}
// 	}

	return TRUE;
}

//手动测试，此函数暂时不用
BOOL CXSttCap_61850::GetOutputCmd_IEDTest_Delay_ManuTest(CDvmDataset *pDataset, CDataGroup &oDataGroup, const CString &strSwitchIndex, const CString &strSwitchState)
{
	long nSwitchIndex = CString_To_long(strSwitchIndex);
	CDvmData *pTestMode = (CDvmData *)pDataset->FindByID(_T("TestMode"));  //测试模式 0-gse2bin; 1-bout2gse；2-gse2bin复归；3-bout2gse复归
	CString strTestMode = pTestMode->m_strValue;
// 	long nBinaryCount = GetBinMapCount_IEDTest(strTestMode);   //获取映射的开关量数量
// 
// 	if (nBinaryCount <= nSwitchIndex)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("智能终端测试-延时测试-变化的开关量索引号不正确！"));
// 	}

 	CString strState1, strStateCont;
 	strStateCont.Format(_T("%d"), 2);
 	oDataGroup.AddNewData(_T(""),_T("StateCount"),_T("long"),strStateCont);
 
 	//初始态
 	if (strSwitchState == _T("0"))
 	{
 		strState1.Format(_T("1"));
 	}
 	else
 	{
 		strState1.Format(_T("0"));
 	}
 
 	CDataGroup *pState = NULL;
 	CDvmData *pNew = NULL;
 	//先加初始态：
 	pState = new CDataGroup;
 	pState->m_strID.Format(_T("State1"));
 	oDataGroup.AddNewChild(pState);
 
 	//初始态全部相同
//  	for (long n=1; n<=nBinaryCount; n++)
//  	{
//  		pNew = new CDvmData;
//  		pNew->m_strID.Format(_T("Bout%d"), n);
//  		pNew->m_strValue = strState1;
//  		pNew->m_strDataType.Format(_T("DOutputState"));
//  		pState->AddNewChild(pNew);
//  	}
 
 	pState = new CDataGroup;
 	pState->m_strID.Format(_T("State2"));
 	oDataGroup.AddNewChild(pState);
 
//  	for (long i=1; i<=nBinaryCount; i++)
//  	{
//  		pNew = new CDvmData;
//  		pNew->m_strID.Format(_T("Bout%d"), i);
//  		pNew->m_strDataType.Format(_T("DOutputState"));
//  
//  		if (i == nSwitchIndex+1)
//  		{
//  			pNew->m_strValue = strSwitchState;
//  		}
//  		else
//  		{
//  			pNew->m_strValue = strState1;
//  		}
//  
//  		pState->AddNewChild(pNew);
//  	}

	return TRUE;
}

BOOL CXSttCap_61850::GetOutputCmd_IEDTest_SOE( CDvmDataset *pDataset, CDataGroup &oDataGroup )
{
	return GetOutputCmd_IEDTest_BinaryEnable(pDataset, oDataGroup);
}

BOOL CXSttCap_61850::GetOutputCmd_IEDTest_Storm( CDvmDataset *pDataset, CDataGroup &oDataGroup )
{
	CDvmData *pRepeatCount = (CDvmData *)pDataset->FindByID(_T("RepeatCount"));   //风暴重复次数
	oDataGroup.AddNewData(_T(""),_T("RepeatCount"),_T("long"),pRepeatCount->m_strValue); 
	
	return GetOutputCmd_IEDTest_BinaryEnable(pDataset, oDataGroup);
}

//SOE测试和风暴测试时，告知底层使用了哪几个开关量
BOOL CXSttCap_61850::GetOutputCmd_IEDTest_BinaryEnable(CDvmDataset *pDataset, CDataGroup &oDataGroup)
{
	CDvmData *pTestMode = (CDvmData *)pDataset->FindByID(_T("TestMode"));  //测试模式 0-gse2bin; 1-bout2gse；2-gse2bin复归；3-bout2gse复归
	CString strTestMode, strIDMap;
	strTestMode = pTestMode->m_strValue;

	if (strTestMode == IEDTEST_TESTMODE_GSE2BIN)
	{
		strIDMap = _T("Gout");
	}
	else if(strTestMode == IEDTEST_TESTMODE_BOUT2GSE)
	{
		strIDMap = _T("Gin");
	}
	else
	{
		return TRUE;
	}

	CDvmData *pMap = (CDvmData *)pDataset->FindByID(strIDMap);
	oDataGroup.AddNewData(_T(""),_T("StateCount"),_T("long"), _T("1"));

	CDataGroup *pState = NULL;
	CDvmData *pNew = NULL;
	long nIndex = 0;
	POS pos = pMap->GetHeadPosition();
	//增加一个状态
	pState = new CDataGroup;
	pState->m_strID.Format(_T("State1"));
	oDataGroup.AddNewChild(pState);

	while (pos != NULL)
	{
		CDvmValue *pValue = (CDvmValue *)pMap->GetNext(pos);
		CString strIndex = pValue->m_strID.Right(3);   //ID诸如bin001  bin002  bout001  bout002这种，取后三位即可
		nIndex = CString_To_long(strIndex);

		if (pValue->m_strValue != _T("-1"))
		{
			pNew = new CDvmData;
			pNew->m_strID.Format(_T("Bout%d"), nIndex);
			pNew->m_strValue = _T("1");
			pNew->m_strDataType.Format(_T("DOutputState"));
			pState->AddNewChild(pNew);
		}	
	}

	CDvmData *pTestType = (CDvmData *)pDataset->FindByID(_T("TestProject")); //测试类型 0-延时测试；1-SOE测试；2-风暴测试
	CString strValue = pTestType->m_strValue;

	if (strValue != IEDTEST_TESTTYPE_SOE)
	{
		return TRUE;
	}

	CDvmData *pCtrlMode = (CDvmData *)pDataset->FindByID(_T("CtrlMode"));   //控制方式：0-手动测试；1-自动测试
	CString strCtrlMode = pCtrlMode->m_strValue;

	if (strCtrlMode == IEDTEST_CONTROLMODE_MANUTEST)
	{
		return TRUE;
	}

	//开出->GOOSE  SOE测试，只能取三个；
	if (strTestMode == IEDTEST_TESTMODE_BOUT2GSE)
	{
		CDvmData *pGinIndex1 = (CDvmData *)pDataset->FindByID(_T("GinIndex1"));   //GOOSE订阅索引号1
		CString strGinIndex1 = pGinIndex1->m_strValue;
		CDvmData *pGinIndex2 = (CDvmData *)pDataset->FindByID(_T("GinIndex2"));   //GOOSE订阅索引号2
		CString strGinIndex2 = pGinIndex2->m_strValue;
		CDvmData *pGinIndex3 = (CDvmData *)pDataset->FindByID(_T("GinIndex3"));   //GOOSE订阅索引号3
		CString strGinIndex3 = pGinIndex3->m_strValue;

		pos = pState->GetHeadPosition();

		while (pos != NULL)
		{
			pNew = (CDvmData *)pState->GetNext(pos);
			pNew->m_strValue = _T("0");

			if (pNew->m_strID.Find(strGinIndex1) >= 0)
			{
				pNew->m_strValue = _T("1");
			}

			if (pNew->m_strID.Find(strGinIndex2) >= 0)
			{
				pNew->m_strValue = _T("1");
			}

			if (pNew->m_strID.Find(strGinIndex3) >= 0)
			{
				pNew->m_strValue = _T("1");
			}
		}
	}

	return TRUE;
}

long CXSttCap_61850::GetBinaryMapCount_IEDTest(CDvmDataset *pDataset)
{
	long nBinaryCount = 0;
	CDvmData *pTestMode = (CDvmData *)pDataset->FindByID(_T("TestMode"));   //测试模式 0-gse2bin; 1-bout2gse；2-gse2bin复归；3-bout2gse复归
	CString strTestMode = pTestMode->m_strValue;
	CDvmData *pBoutCnt = (CDvmData *)pDataset->FindByID(_T("BoutCnt")); //开出数量，用于自动测试时，bout2gse试验，记录变化次数的
	CString strBoutCnt = pBoutCnt->m_strValue;
	CDvmValue *pRsltVal = NULL;
	CString strDatasetID, strIDMap;

	if (strTestMode == IEDTEST_TESTMODE_GSE2BIN)
	{
		//GOOSE->开入测试，看GOOSE发布的映射数量
		CDvmDataset *pDatasetGout = NULL;
		//智能终端测试，只有一个控制块，因此数据集ID可以固定
		strDatasetID = CAP_DATASET_MAP_ID_GOUT1;
		strIDMap = _T("bout");

		if (m_pDvmDevice == NULL)
		{
			return nBinaryCount;
		}

		pDatasetGout = (CDvmDataset *)m_pDvmDevice->FindDataset(strDatasetID);

		if (pDatasetGout == NULL)
		{
			return nBinaryCount;
		}

		POS pos = pDatasetGout->GetHeadPosition();
		CDvmData *pData = NULL;
		CDvmValue *pValue = NULL;
		CString strValueID;

		while (pos != NULL)
		{
			pData = (CDvmData *)pDatasetGout->GetNext(pos);
            strValueID.Format(_T("%s$map"), pData->m_strID.GetString());
			pValue = (CDvmValue *)pData->FindByID(strValueID);

			if (pValue != NULL)
			{
				if (pValue->m_strValue.Find(strIDMap) >= 0)
				{
					nBinaryCount++;
				}
			}	
		}
	}
	else if(strTestMode == IEDTEST_TESTMODE_BOUT2GSE)
	{
		//开出->GOOSE测试，看数据集中的开出数量
		nBinaryCount = CString_To_long(strBoutCnt);
		strIDMap = _T("bin");
	}

    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("开关量数量【%s】=【%d】"), strIDMap.GetString(), nBinaryCount);
	return nBinaryCount;
}

void CXSttCap_61850::ResetBinaryMap_Data(CDvmData *pData)
{
	POS pos = pData->GetHeadPosition();
	CDvmValue *pValue = NULL;
	CDvmValue *pTime1 = NULL;
	CDvmValue *pTime2 = NULL;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)pData->GetNext(pos);

		if (pValue->m_strValue != _T("-1"))
		{
			pValue->m_strValue.Format(_T("0"));
			pTime1 = (CDvmValue *)pValue->FindByID(_T("Time1"));
			pTime2 = (CDvmValue *)pValue->FindByID(_T("Time2"));
			pTime1->m_strValue.Format(_T("0"));
			pTime2->m_strValue.Format(_T("0"));
		}
	}
}

void CXSttCap_61850::SetPT_CT_Rates(CIecCfgPrimRatesIn *pPrimRatesIn,BOOL bIsFT3Device)
{
	if (bIsFT3Device)
	{
		for (int nIndex = 0;nIndex<6;nIndex++)
		{
			g_oCapAnalysisConfig.m_fCT_Rate[nIndex] = 1;
			g_oCapAnalysisConfig.m_fPT_Rate[nIndex] = 1;
		}

		return;
	}

	if (pPrimRatesIn == NULL)
	{
		return;
	}

	CString strCT_RateID,strPT_RateID;
	CIecCfgPrimRate *pCurrPrimRate = NULL;
	CIecCfgPrimRate *pVolPrimRate = NULL;

	for (int nIndex = 0;nIndex<6;nIndex++)
	{
		strCT_RateID.Format(_T("I%d-abc"),nIndex+1);
		strPT_RateID.Format(_T("U%d-abc"),nIndex+1);
		pCurrPrimRate = (CIecCfgPrimRate*)pPrimRatesIn->FindByID(strCT_RateID);

		if (pCurrPrimRate != NULL)
		{
			g_oCapAnalysisConfig.m_fCT_Rate[nIndex] = pCurrPrimRate->m_fPrimValue/pCurrPrimRate->m_fSecondValue;
		}

		pVolPrimRate = (CIecCfgPrimRate*)pPrimRatesIn->FindByID(strPT_RateID);

		if (pVolPrimRate != NULL)
		{
			g_oCapAnalysisConfig.m_fPT_Rate[nIndex] = pVolPrimRate->m_fPrimValue*1000/pVolPrimRate->m_fSecondValue;
		}
	}
}
