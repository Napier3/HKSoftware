#include "StdAfx.h"
#include "CmmSerialChannel.h"
#include "..\PpPackageSend.h"
#include "..\PpEngineThreadBase.h"
#include "..\DeviceModel\CmmOnConnect.h"
#include "DeviceCmmChannel.h"
#include "..\..\XLanguageResourcePp.h"

CCmmSerialChannel::CCmmSerialChannel(void)
{
	m_pConfig = NULL;
	m_pSerialComm = NULL;
	m_pThread = NULL;
	m_bExitThread = FALSE;
}

CCmmSerialChannel::~CCmmSerialChannel(void)
{
	CloseSerial();
}

void CCmmSerialChannel::CloseSerial()
{
	if (m_pSerialComm != NULL)
	{
		m_pSerialComm->CloseSerial();
		delete m_pSerialComm;
		m_pSerialComm = NULL;
	}
}

BOOL CCmmSerialChannel::InitSerial()
{
	ASSERT (m_pConfig != NULL);

	//创建串口对象
	if(m_pSerialComm == NULL)
	{
		m_pSerialComm = new CSerial();
		ASSERT(m_pSerialComm != NULL);
	}

	if (m_pSerialComm == NULL)
	{
		return FALSE;
	}

	//打开串口
	if(m_pSerialComm->OpenSerial(m_pConfig->m_nPortNum) == CODE_ERROR)
	{
		CAutoSimpleLock oLock(g_oCmmLogAutoCriticSection);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_OpenSerialFail/*_T("打开串口%d失败！")*/, m_pConfig->m_nPortNum);
		return FALSE;
	}

	m_pSerialComm->SetSerialBufferSize(SERIAL_INPUTBUFFERLEN, SERIAL_OUTBUFFERLEN);
	m_pSerialComm->m_SerialDcbStruct.DCBlength = sizeof(DCB);

	if(m_pSerialComm->GetSerialAttributes() == CODE_ERROR)
	{
		CAutoSimpleLock oLock(g_oCmmLogAutoCriticSection);
		CLogPrint::LogString(XLOGLEVEL_ERROR,g_sLangTxt_ReceiveSerialFail/*_T("获取串口属性失败！")*/);
		return FALSE;
	}

	m_pSerialComm->m_SerialDcbStruct.BaudRate = m_pConfig->m_nBaudRate;
	m_pSerialComm->m_SerialDcbStruct.ByteSize = m_pConfig->m_nDataBit ;
	m_pSerialComm->m_SerialDcbStruct.StopBits = m_pConfig->GetStopBits();
	m_pSerialComm->m_SerialDcbStruct.Parity = m_pConfig->m_nParity;

	if(m_pSerialComm->SetSerialAttributes() == CODE_ERROR)
	{
		CAutoSimpleLock oLock(g_oCmmLogAutoCriticSection);
		CLogPrint::LogString(XLOGLEVEL_ERROR,g_sLangTxt_SetSerialError /*_T("设置串口属性错误！")*/);
		m_pSerialComm->CloseSerial();
		return FALSE;
	}

	return TRUE;
}

BOOL CCmmSerialChannel::Create(CExBaseObject *pConfig)
{
	m_pConfig = (CCmmSerialConfig*)pConfig;
	SetReceiveBufferLength(1048576); //1024*1024  1M
	return TRUE;
}

void CCmmSerialChannel::Send(CExBaseObject *pPkgSend)
{
	CAutoSimpleLock oLock(m_oSendListCriticSection);
	m_nSendIndex++;
	CCmmChannel::Send(pPkgSend);
	oLock.Free();
}

BOOL CCmmSerialChannel::Connect()
{
	if (!InitSerial())
	{
		m_dwConnectState = CONNECT_STATE_FAILED;
		CloseSerial();
		return FALSE;
	}

	if (m_pThread == NULL)
	{
		m_pThread = AfxBeginThread(SerialThread,this);
		m_pThread->m_bAutoDelete = TRUE;
	}

	//启动OnConnect定义的过程
	CDeviceCmmChannel *pDeviceCmmChannel = (CDeviceCmmChannel*)(CCmmChannel::GetParent());
	CMM_OnChannelConnectSucc(m_pConfig, pDeviceCmmChannel->m_pThread);
	m_dwConnectState = CONNECT_STATE_SUCCESSFUL;
	OnConnectFinished();

	return TRUE;
}

BOOL CCmmSerialChannel::DisConnect()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CCmmSerialChannel::DisConnect"));
	m_bExitThread = TRUE;
	m_dwConnectState = CONNECT_STATE_NORMAL;

	return TRUE;
}

BOOL CCmmSerialChannel::IsConnectSuccessful()
{
	return CCmmChannel::IsConnectSuccessful();
}

BOOL CCmmSerialChannel::IsCmmChannelExit()
 {
	 if (m_pThread != NULL)
	 {
		 return FALSE;
	 }

	 if (m_pSerialComm != NULL)
	 {
		 return FALSE;
	 }

	return TRUE;
 }

UINT CCmmSerialChannel::SerialThread(LPVOID pParam)
{
	CCmmSerialChannel *pSerialChannel = (CCmmSerialChannel*)pParam;
	CDeviceCmmChannel *pDeviceChannel = (CDeviceCmmChannel*)pSerialChannel->GetParent();
	DWORD dwCommMode = COMMMODE_NORMAL;

	if (pDeviceChannel != NULL)
	{
		if (pDeviceChannel->GetClassID() == CMMCLASSID_DEVICE_CMM_CHANNEL)
		{
			dwCommMode = pDeviceChannel->m_dwCommMode;
		}
	}

	pSerialChannel->m_bExitThread = FALSE;
	CSerial *pSerialComm = pSerialChannel->m_pSerialComm;
	char pBuffer[1024]="\0";
	char pBufferEx[1024]="\0";
	long nLen = 0;
	DWORD dwSndRcvState = 0;
	BOOL bCandSend = TRUE;
	BOOL bHasSend = TRUE;

	while (TRUE)
	{
		CPpPackageSend *pSend = (CPpPackageSend*)pSerialChannel->GetPackageSend();
		bCandSend = FALSE;
		bHasSend = FALSE;
		
		if (pSend != NULL)
		{
			if (dwCommMode == COMMMODE_ASKANSWER)
			{
				if (dwSndRcvState == 0)
				{
					bCandSend = TRUE;
				}
			}
			else
			{
				bCandSend = TRUE;
			}
		}

		if (bCandSend)
		{//有需要发送的报文
			char *pBuffer = (char*)pSend->m_oBuffer.GetBuffer();
			long nLen = pSend->m_oBuffer.GetDataLength();
			pSend->m_pPackageDetail->InitPackageTime();

			//发送数据
			if (pSerialComm->SendData(pBuffer, nLen) )
			{
				pSend->SetSendState(TRUE);
				pSend->LogAndRecordProtocol();
				pSerialChannel->RemoveHead();
				dwSndRcvState = 1;
				bHasSend = TRUE;
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_SendMessageFail/*L"向\"%s\"发送报文失败"*/, pSerialChannel->m_pConfig->m_nPortNum);
				pSerialChannel->m_dwConnectState = CONNECT_STATE_NORMAL;
			}
		}
		
		//没有发送
		if (bHasSend)
		{
			Sleep(50);
		}

		if (pSerialChannel->m_bExitThread)
		{
			break;
		}

		{
			//读串口数据

			pSerialChannel->Receive(dwSndRcvState);

// 			SYSTEMTIME tm;
// 			::GetLocalTime(&tm);
// 			DWORD dwDataLen = 0;
// 			DWORD dwRecvTotalLen = 0;
// 			pSerialComm->RecieveData((char*)pSerialChannel->m_byteReceiveBuffer,dwDataLen);
// 
// 			if (dwDataLen > 0)
// 			{//如果收到收到数据，则一动缓冲区指针
// 				CCmmRcvSndTime *pCmmTime = new CCmmRcvSndTime();
// 				pCmmTime->InitTime(tm);
// 				dwRecvTotalLen = dwDataLen;
// 				//pSerialChannel->AppendRcvBuffer((BYTE*)pSerialChannel->m_byteReceiveBuffer, dwDataLen, pCmmTime);
// 				long nReadIndex = 0;
// 				dwSndRcvState = 0; //收到数据
// 
// 				while (TRUE)
// 				{
// 					Sleep(50);
// 					dwDataLen = 0;
// 					pSerialComm->RecieveData((char*)(pSerialChannel->m_byteReceiveBuffer+dwRecvTotalLen), dwDataLen);
// 
// 					if (dwDataLen > 0)
// 					{
// 						dwRecvTotalLen += dwDataLen;
// 						nReadIndex = 0;
// 						//pSerialChannel->AppendRcvBuffer((BYTE*)pSerialChannel->m_byteReceiveBuffer, dwDataLen, pCmmTime);
// 					}
// 					else
// 					{
// 						nReadIndex++;
// 					}
// 
// 					if (nReadIndex >= 5)
// 					{
// 						break;
// 					}
// 				}
// 
// 				pSerialChannel->AppendRcvBuffer((BYTE*)pSerialChannel->m_byteReceiveBuffer, dwRecvTotalLen, pCmmTime);
// 				LogReceivePackage(pSerialChannel->m_pszPpLogProtocol,
// 					pSerialChannel->m_byteReceiveBuffer, dwRecvTotalLen);
// 				pSerialChannel->OnChannelReceive(pCmmTime);
// 			}
		}

		if (pSerialChannel->m_bExitThread)
		{
			break;
		}

		Sleep(50);
	}

	CMM_SetAllSendPkgState(pSerialChannel);
	pSerialChannel->m_pThread = NULL;
	
	//串口对象
	//pSerialChannel->CloseSerial();

	return 0;
}

void CCmmSerialChannel::Receive(DWORD &dwSndRcvState)
{
	if (m_pSerialComm == NULL)
	{
		return;
	}

	if (m_pXPkgFullRcvJdgInterface == NULL)
	{
		Receive_Only(dwSndRcvState);
	}
	else
	{
		Receive_FullPkg(dwSndRcvState);
	}
}

//#define  _debug_Receive_FullPkg

void CCmmSerialChannel::Receive_FullPkg(DWORD &dwSndRcvState)
{
	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	DWORD dwDataLen = 0;
	DWORD dwRecvTotalLen = 0;

#ifdef _debug_Receive_FullPkg
	BYTE *pTemp = m_byteReceiveBuffer;
	//10 80 01 00 81 16 10 C9 01 00 CA 16
	*pTemp = 0x10;		pTemp++;
	*pTemp = 0x80;		pTemp++;
	*pTemp = 0x01;		pTemp++;
	*pTemp = 0x00;		pTemp++;
	*pTemp = 0x81;		pTemp++;
	*pTemp = 0x16;		pTemp++;
	*pTemp = 0x10;		pTemp++;
	*pTemp = 0xC9;		pTemp++;
	*pTemp = 0x01;		pTemp++;
	*pTemp = 0x00;		pTemp++;
	*pTemp = 0xCA;		pTemp++;
	*pTemp = 0x16;		pTemp++;
	dwDataLen = 12;
#else
	m_pSerialComm->RecieveData((char*)m_byteReceiveBuffer,dwDataLen);
#endif

	if (dwDataLen == 0)
	{//如果没有收到数据
		return;
	}

	CCmmRcvSndTime *pCmmTime = new CCmmRcvSndTime();
	CCmmRcvSndTime *pClone = NULL;
	pCmmTime->InitTime(tm);
	dwRecvTotalLen = dwDataLen;
	long nReadIndex = 0;
	dwSndRcvState = 0; //收到数据
	long nFullLen = 0;
	long nPkgCalLen = 0;

#ifndef _debug_Receive_FullPkg
	LogReceivePackage(m_pszPpLogProtocol, m_byteReceiveBuffer, dwRecvTotalLen);
#endif

	CString strMsg;

	while (TRUE)
	{
		do 
		{
			//进行数据判断
			nFullLen = m_pXPkgFullRcvJdgInterface->XPkgFullRcvJdg(m_byteReceiveBuffer, dwRecvTotalLen, nPkgCalLen);

			//已经接收到了完整的报文，发送完整的报文
			if (nFullLen > 0)
			{
				strMsg.Format(_T("收到完整报文[%d]\r\n"), nFullLen);
// 				CLogPrint::LogString(g_pLogPkgSendPrint, XLOGLEVEL_ERROR, strMsg);
// 				LogReceivePackage(m_pszPpLogProtocol, m_byteReceiveBuffer, nFullLen);
				pClone = pCmmTime->Clone();
				AppendRcvBuffer((BYTE*)m_byteReceiveBuffer, nFullLen, pClone);
				OnChannelReceive(pClone);

				if (nFullLen == dwRecvTotalLen)
				{
					dwRecvTotalLen = 0;
					break;
				}

				//还有报文，将报文移动到首部
				dwRecvTotalLen -= nFullLen;
				memcpy(m_byteReceiveBuffer, m_byteReceiveBuffer + nFullLen, dwRecvTotalLen);
			}
			else
			{
				break;
			}	
		} while (dwRecvTotalLen > 0);

		if (dwRecvTotalLen == 0)
		{
			break;
		}

		//继续接受报文
		Sleep(50);
		dwDataLen = 0;
		m_pSerialComm->RecieveData((char*)(m_byteReceiveBuffer+dwRecvTotalLen), dwDataLen);

		if (dwDataLen > 0)
		{
			LogReceivePackage(m_pszPpLogProtocol, m_byteReceiveBuffer+dwRecvTotalLen, dwDataLen);
			dwRecvTotalLen += dwDataLen;
			nReadIndex = 0;
		}
		else
		{
			nReadIndex++;
		}

		if (nReadIndex >= 40)
		{//连续五次没有收到，则结束
			strMsg.Format(_T(">>>>>>>>>>超过2秒，报文没有收全[%d]"), dwRecvTotalLen);
			CLogPrint::LogString(g_pLogPkgSendPrint, XLOGLEVEL_ERROR, strMsg);
			break;
		}
	}

	//如果有未发送的报文，添加到缓冲区并发送
	if (dwRecvTotalLen > 0)
	{
		strMsg.Format(_T(">>>>>>>>>>报文没有收全[%d]  添加到缓冲区"), dwRecvTotalLen);
		CLogPrint::LogString(g_pLogPkgSendPrint, XLOGLEVEL_ERROR, strMsg);
		pClone = pCmmTime->Clone();
		AppendRcvBuffer((BYTE*)m_byteReceiveBuffer, dwRecvTotalLen, pClone);
		LogReceivePackage(m_pszPpLogProtocol,
			m_byteReceiveBuffer, dwRecvTotalLen);
		OnChannelReceive(pClone);
	}

	delete pCmmTime;
}

void CCmmSerialChannel::Receive_Only(DWORD &dwSndRcvState)
{
	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	DWORD dwDataLen = 0;
	DWORD dwRecvTotalLen = 0;
	m_pSerialComm->RecieveData((char*)m_byteReceiveBuffer,dwDataLen);

	if (dwDataLen > 0)
	{//如果收到收到数据，则一动缓冲区指针
		CCmmRcvSndTime *pCmmTime = new CCmmRcvSndTime();
		pCmmTime->InitTime(tm);
		dwRecvTotalLen = dwDataLen;
		//pSerialChannel->AppendRcvBuffer((BYTE*)pSerialChannel->m_byteReceiveBuffer, dwDataLen, pCmmTime);
		long nReadIndex = 0;
		dwSndRcvState = 0; //收到数据

		while (TRUE)
		{
			Sleep(50);
			dwDataLen = 0;
			m_pSerialComm->RecieveData((char*)(m_byteReceiveBuffer+dwRecvTotalLen), dwDataLen);

			if (dwDataLen > 0)
			{
				dwRecvTotalLen += dwDataLen;
				nReadIndex = 0;
				//pSerialChannel->AppendRcvBuffer((BYTE*)pSerialChannel->m_byteReceiveBuffer, dwDataLen, pCmmTime);
			}
			else
			{
				nReadIndex++;
			}

			if (nReadIndex >= 5)
			{
				break;
			}
		}

		AppendRcvBuffer((BYTE*)m_byteReceiveBuffer, dwRecvTotalLen, pCmmTime);
		LogReceivePackage(m_pszPpLogProtocol,
			m_byteReceiveBuffer, dwRecvTotalLen);
		OnChannelReceive(pCmmTime);
	}
}

BOOL CCmmSerialChannel::TerminateChannel()
{
	return TRUE;
}