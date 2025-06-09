#include "stdafx.h"
#include "VmDKSource.h"

CVmDKSourceApp::CVmDKSourceApp()
{
	m_nLock = 0;
}

CVmDKSourceApp::~CVmDKSourceApp()
{

}

void CVmDKSourceApp::OnXTimer(DWORD dwTimerID)
{
	if(dwTimerID == STT_MACROTEST_TIMER_ID_READMEAS)
	{
		if (!m_nLock)
		{
			m_nLock = DKSOURCE_LOCK_REPORT;

			CString strTemp;
			CString strACReport = _T("");
			CString strDCReport = _T("");

			tagDKSource tag;
			m_oDK51E1.m_strCurProcedure = DKSOURCE_MACROTEST_DC_GETPARAM;
			m_oDK51E1.RunProcedure(&tag);

			DWORD dwLen = 0;
			unsigned char byteDC[1024] = {0};
			Sleep(500);
			m_oDK51E1.RecieveData(byteDC, dwLen);
			for (int i = 0; i < dwLen; i++)
			{
				strTemp.Format(_T("%.2x"), byteDC[i]);
				strDCReport += strTemp;
			}

			m_oDK51E1.m_strCurProcedure = DKSOURCE_MACROTEST_AC_GETPARAM;
			m_oDK51E1.RunProcedure(&tag);
			unsigned char byteAC[1024] = {0};
			Sleep(500);
			m_oDK51E1.RecieveData(byteAC, dwLen);
			for (int i = 0; i < dwLen; i++)
			{
				strTemp.Format(_T("%.2x"), byteAC[i]);
				strACReport += strTemp;
			}

			m_oDK51E1.GetReport(strDCReport, strACReport);
			SendRtData();

			m_nLock = DKSOURCE_UNLOCK;
		}	
	}
	else
	{
		DWORD dwLen = 0;
		unsigned char strRecv[1024] = {0};
		m_oDK51E1.RecieveData(strRecv, dwLen);
		if(dwLen)
		{
			//串口接收到数据则测试结果回传并结束计时器
			CString strTemp;
			m_oDK51E1.m_strBuffer = "";
			for (int i = 0; i < dwLen; i++)
			{
				strTemp.Format(_T("%.2x"), strRecv[i]);
				m_oDK51E1.m_strBuffer += strTemp;
			}
			KillTimer(m_pVmImpMsgWnd->m_hWnd, dwTimerID);
			m_pVmImpMsgWnd->PostMessage(STT_MACROTEST_MSG_FINISH, (WPARAM)this, 0);
		}
		m_nLock = DKSOURCE_UNLOCK;
	}
}

long CVmDKSourceApp::TestCmd_ConfigDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas)
{
	//DK测试仪内部数据是手册中固定死的,如需改变则在此处增加stt_GetDataValueByID
	//COM口由此处获取并确定
	long nCom = 0;
	m_oDK51E1.m_oConfig.GetSerialComm(nCom);
	m_pVmImpMsgWnd->PostMessage(STT_MACROTEST_MSG_CONFIGDEVICE, 0, nCom);
	return 1;
}

long CVmDKSourceApp::TestCmd_CloseDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas)
{
	KillTimer(m_pVmImpMsgWnd->m_hWnd, STT_MACROTEST_TIMER_ID_READMEAS);
	m_oDK51E1.m_bIsXTimerRunning = FALSE;
	return m_oDK51E1.CloseDevice();
}

void CVmDKSourceApp::OnConfigDevice(WPARAM wParam, LPARAM lParam)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CVmDKSourceApp::OnConfigDevice"));
	m_oDK51E1.Connect((long)lParam);
}

long CVmDKSourceApp::StopTest()
{
	//m_strCurrTestMacroID = DTVP_MACRO_ID_StopTest;
	//m_oDK51E1.StopTest();

	//回复成功应答，让IotVm清除正在测试标记
	CSttSysState oSysState;
	m_pSttMacroTestEventServerInterface->OnTestState_Reply(m_pCmmOptrInterface, &oSysState, STT_CMD_ExecStatus_SUCCESS, STT_CMD_TYPE_ATS_StopTest, STT_CMD_SYSSTATE_TEST);

	return 0;
}


long CVmDKSourceApp::TestExec(CDataGroup *pParas)
{	
	//确定执行的命令的idx
	m_oDK51E1.m_strCurProcedure = m_strCurrTestMacroID;
	if(!m_oDK51E1.m_strCurProcedure)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("DKSource: 未知的命令ID!"));
	}

	long nParamNum = 0;
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_ACOpenSource, nParamNum);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_DCOpenSource, nParamNum);

	tagDKSource tagDK;
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_Ua, tagDK.m_fUa);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_Ub, tagDK.m_fUb);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_Uc, tagDK.m_fUc);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_Ia, tagDK.m_fIa);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_Ib, tagDK.m_fIb);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_Ic, tagDK.m_fIc);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_IPa, tagDK.m_fIPa);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_IPb, tagDK.m_fIPb);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_IPc, tagDK.m_fIPc);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_Fa, tagDK.m_fFa);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_Fb, tagDK.m_fFb);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_Fc, tagDK.m_fFc);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_Type, tagDK.m_nType);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_Range, tagDK.m_nRange);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_SData, tagDK.m_fSData);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_Flag, tagDK.m_nType);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_PRINCIPLE, tagDK.m_nMode);	
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_CloseloopEn, tagDK.m_nEnable);
	stt_GetDataValueByID(pParas, DKSOURCE_PARA_ID_HarmonicMode, tagDK.m_nMode);

	if(m_strCurrTestMacroID == DKSOURCE_MACROTEST_AC_SETHARMONICPARAM)
	{
		if(tagDK.m_pHarmonic)
		{
			delete tagDK.m_pHarmonic;
		}
		tagDK.m_pHarmonic = new CExBaseList;
		//设置谐波时需要动态读取
		POS pos = pParas->GetHeadPosition();
		CDvmData* pChannel = (CDvmData*)pParas->GetNext(pos);
		tagDK.m_nType = CString_To_long(pChannel->m_strValue);
		CDvmData* pCount = (CDvmData*)pParas->GetNext(pos);
		tagDK.m_nCount = CString_To_long(pCount->m_strValue);
		for (int i = 0; i < tagDK.m_nCount; i++)
		{
			CDvmData* pHarmonic = (CDvmData*)pParas->GetNext(pos);
			CDvmData* pAmplitude = (CDvmData*)pParas->GetNext(pos); 
			CDvmData* pAngle = (CDvmData*)pParas->GetNext(pos);
			CHarmonic* tagHar =  new CHarmonic;
			tagHar->m_nHarmonic = CString_To_long(pHarmonic->m_strValue);
			tagHar->m_fAmplitude = CString_To_double(pAmplitude->m_strValue) * 0.01;
			tagHar->m_fAngle = CString_To_double(pAngle->m_strValue);
			tagDK.m_pHarmonic->AddNewChild((CExBaseObject*)tagHar);
		}
	}
	//理论上串口通信配合自动测试时不会出现多次创建计时器的情况
	//但为防止意外,仍判断一次计时器是否启动
	if (m_oDK51E1.m_bIsXTimerRunning == FALSE)
	{
		m_oDK51E1.m_bIsXTimerRunning = TRUE;
		m_pVmImpMsgWnd->SetTimer(STT_MACROTEST_TIMER_ID_READMEAS, DKSOURCE_TIMER_NUMBER, NULL);  //启动发送实时数据的定时器
	}

	m_pVmImpMsgWnd->SetTimer(DKSource_Str_To_Idx(m_oDK51E1.m_strCurProcedure), DKSOURCE_TIMER_NUMBER, NULL);  //启动发送实时数据的定时器

	while (!m_nLock)
	{
		m_nLock = DKSOURCE_LOCK_USER;

		Sleep(100);
		m_oDK51E1.RunProcedure(&tagDK, nParamNum);
	}

	return TRUE;
}

void CVmDKSourceApp::OnMacroTestMsgFinish(WPARAM wParam, LPARAM lParam)
{
	if(m_pCmmOptrInterface)
	{	
		CDataGroup* pDataGroup = m_oDK51E1.ParseBuffer();
		pDataGroup->m_strID = m_strCurrTestMacroID;
		m_pSttMacroTestEventServerInterface->OnTestEvent_TestFinished(m_pCmmOptrInterface, pDataGroup);
		delete pDataGroup;
	}
	else
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("m_pCmmOptrInterface == NULL"));
}

BOOL CVmDKSourceApp::IsConnectSuccess()
{
	return m_oDK51E1.IsConnectSuccess();
}

void CVmDKSourceApp::SendRtData()
{
	//yzj 2021-10-11 拼RTDATA报文
	CString strXML;
	CDataGroup oGroup;
	oGroup.AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
	CDataGroup* pParas = oGroup.AddNewGroup(_T(""), _T("RTDATA"), _T(""));
	
	POS pos = m_oDK51E1.m_pReport->GetHeadPosition();
	while (pos)
	{
		CDvmData* pChild = (CDvmData*)m_oDK51E1.m_pReport->GetNext(pos);
		pParas->AddNewData(pChild->m_strID, pChild->m_strValue);
	}

	oGroup.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strXML);
	CString strTopic = m_strDeviceSN + _T("/RTDATA");
	m_pCmmOptrInterface->Send(const_cast<char*>(strXML.GetString()), 
		strXML.GetLength(), strTopic);
}