#include "StdAfx.h"
#include "EpCmmSerialChannel.h"
#include "EpDeviceCmmChannel.h"


CEpCmmSerialChannel::CEpCmmSerialChannel(void)
{
	m_pConfig = NULL;
	m_pSerialComm = NULL;
	m_pThread = NULL;
	m_bExitThread = FALSE;
}

CEpCmmSerialChannel::~CEpCmmSerialChannel(void)
{
}

void CEpCmmSerialChannel::CloseSerial()
{
	if (m_pSerialComm != NULL)
	{
		m_pSerialComm->CloseSerial();
		delete m_pSerialComm;
		m_pSerialComm = NULL;
	}
}

BOOL CEpCmmSerialChannel::InitSerial()
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
		CLogPrint::LogFormatString(LOGLEVEL_ERROR,_T("打开串口%d失败！"), m_pConfig->m_nPortNum);
		return FALSE;
	}

	m_pSerialComm->SetSerialBufferSize(SERIAL_INPUTBUFFERLEN, SERIAL_OUTBUFFERLEN);

	m_pSerialComm->m_SerialDcbStruct.DCBlength = sizeof(DCB);

	if(m_pSerialComm->GetSerialAttributes() == CODE_ERROR)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR,_T("获取串口属性失败！"));
		return FALSE;
	}

	m_pSerialComm->m_SerialDcbStruct.BaudRate = m_pConfig->m_nBaudRate;
	m_pSerialComm->m_SerialDcbStruct.ByteSize = m_pConfig->m_nDataBit ;
	m_pSerialComm->m_SerialDcbStruct.StopBits = m_pConfig->GetStopBits();
	m_pSerialComm->m_SerialDcbStruct.Parity = m_pConfig->m_nParity;

	if(m_pSerialComm->SetSerialAttributes() == CODE_ERROR)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR,_T("设置串口属性错误！"));
		m_pSerialComm->CloseSerial();
		return FALSE;
	}

	return TRUE;
}

BOOL CEpCmmSerialChannel::Create(CExBaseObject *pConfig)
{
	m_pConfig = (CEpCmmSerialConfig*)pConfig;
	SetReceiveBufferLength(1048576); //1024*1024  1M
	return TRUE;
}

void CEpCmmSerialChannel::Send(CExBaseObject *pPkgSend)
{
	CAutoSimpleLock oLock(m_oSendListCriticSection);
	m_nSendIndex++;
	CEpCmmChannel::Send(pPkgSend);
	oLock.Free();
}

BOOL CEpCmmSerialChannel::Connect()
{
	if (!InitSerial())
	{
		m_dwConnectState = CONNECT_STATE_FAILED;
		return FALSE;
	}

	if (m_pThread == NULL)
	{
		m_pThread = AfxBeginThread(SerialThread,this);
		m_pThread->m_bAutoDelete = TRUE;
	}

	//启动OnConnect定义的过程
	CEpDeviceCmmChannel *pEpDeviceCmmChannel = (CEpDeviceCmmChannel*)(CEpCmmChannel::GetParent());
	CMM_OnChannelConnectSucc(m_pConfig, pEpDeviceCmmChannel->m_pThread);

	m_dwConnectState = CONNECT_STATE_SUCCESSFUL;
	OnConnectFinished();

	return TRUE;
}

BOOL CEpCmmSerialChannel::DisConnect()
{
	m_bExitThread = TRUE;
	m_dwConnectState = CONNECT_STATE_NORMAL;

	return TRUE;
}

BOOL CEpCmmSerialChannel::IsConnectSuccessful()
{
	return CEpCmmChannel::IsConnectSuccessful();
}

BOOL CEpCmmSerialChannel::IsEpCmmChannelExit()
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


//UDP客户端函数
UINT CEpCmmSerialChannel::SerialThread(LPVOID pParam)
{
	CEpCmmSerialChannel *pSerialChannel = (CEpCmmSerialChannel*)pParam;
	pSerialChannel->m_bExitThread = FALSE;
	CSerial *pSerialComm = pSerialChannel->m_pSerialComm;
	char pBuffer[1024]="\0";
	char pBufferEx[1024]="\0";
	long nLen = 0;

	while (TRUE)
	{
		CEpFrameBase *pSend = (CEpFrameBase*)pSerialChannel->GetFrameSend();

		if (pSend != NULL)
		{//有需要发送的报文
			CCycleMemBuffer *pCycleBuffer = pSend->m_pBuffer;
			char *pBuffer = (char*)pCycleBuffer->GetBuffer();
			long nLen = pCycleBuffer->GetDataLength();
			pSend->InitTime();

			//发送数据
			if (pSerialComm->SendData(pBuffer, nLen) )
			{
				pSend->LogAndRecordProtocol();
				pSerialChannel->RemoveHead();
			}
			else
			{
				CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("向\"%s\"发送报文失败"), pSerialChannel->m_pConfig->m_nPortNum);

				//发送失败处理
			}
		}
		else
		{
			SYSTEMTIME tm;
			::GetLocalTime(&tm);

			//读串口数据
			DWORD dwDataLen = 0;
			pSerialComm->RecieveData((char*)pSerialChannel->m_byteReceiveBuffer,dwDataLen);

			if (dwDataLen > 0)
			{//如果收到收到数据，则一动缓冲区指针
				CEpCmmRcvSndTime *pEpCmmTime = new CEpCmmRcvSndTime();
				pEpCmmTime->InitTime(tm);
				pSerialChannel->AppendRcvBuffer((BYTE*)pSerialChannel->m_byteReceiveBuffer, dwDataLen, pEpCmmTime);
				long nReadIndex = 0;

				while (TRUE)
				{
					Sleep(20);
					dwDataLen = 0;
					pSerialComm->RecieveData((char*)pSerialChannel->m_byteReceiveBuffer, dwDataLen);

					if (dwDataLen > 0)
					{
						pSerialChannel->AppendRcvBuffer((BYTE*)pSerialChannel->m_byteReceiveBuffer, dwDataLen, pEpCmmTime);
					}
					else
					{
						nReadIndex++;
					}

					if (nReadIndex >= 3)
					{
						break;
					}
				}

				pSerialChannel->OnChannelReceive(pEpCmmTime);
			}
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
	pSerialChannel->CloseSerial();

	return 0;
}
