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

	//�������ڶ���
	if(m_pSerialComm == NULL)
	{
		m_pSerialComm = new CSerial();
		ASSERT(m_pSerialComm != NULL);
	}

	if (m_pSerialComm == NULL)
	{
		return FALSE;
	}

	//�򿪴���
	if(m_pSerialComm->OpenSerial(m_pConfig->m_nPortNum) == CODE_ERROR)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR,_T("�򿪴���%dʧ�ܣ�"), m_pConfig->m_nPortNum);
		return FALSE;
	}

	m_pSerialComm->SetSerialBufferSize(SERIAL_INPUTBUFFERLEN, SERIAL_OUTBUFFERLEN);

	m_pSerialComm->m_SerialDcbStruct.DCBlength = sizeof(DCB);

	if(m_pSerialComm->GetSerialAttributes() == CODE_ERROR)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR,_T("��ȡ��������ʧ�ܣ�"));
		return FALSE;
	}

	m_pSerialComm->m_SerialDcbStruct.BaudRate = m_pConfig->m_nBaudRate;
	m_pSerialComm->m_SerialDcbStruct.ByteSize = m_pConfig->m_nDataBit ;
	m_pSerialComm->m_SerialDcbStruct.StopBits = m_pConfig->GetStopBits();
	m_pSerialComm->m_SerialDcbStruct.Parity = m_pConfig->m_nParity;

	if(m_pSerialComm->SetSerialAttributes() == CODE_ERROR)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR,_T("���ô������Դ���"));
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

	//����OnConnect����Ĺ���
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


//UDP�ͻ��˺���
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
		{//����Ҫ���͵ı���
			CCycleMemBuffer *pCycleBuffer = pSend->m_pBuffer;
			char *pBuffer = (char*)pCycleBuffer->GetBuffer();
			long nLen = pCycleBuffer->GetDataLength();
			pSend->InitTime();

			//��������
			if (pSerialComm->SendData(pBuffer, nLen) )
			{
				pSend->LogAndRecordProtocol();
				pSerialChannel->RemoveHead();
			}
			else
			{
				CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("��\"%s\"���ͱ���ʧ��"), pSerialChannel->m_pConfig->m_nPortNum);

				//����ʧ�ܴ���
			}
		}
		else
		{
			SYSTEMTIME tm;
			::GetLocalTime(&tm);

			//����������
			DWORD dwDataLen = 0;
			pSerialComm->RecieveData((char*)pSerialChannel->m_byteReceiveBuffer,dwDataLen);

			if (dwDataLen > 0)
			{//����յ��յ����ݣ���һ��������ָ��
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
	
	//���ڶ���
	pSerialChannel->CloseSerial();

	return 0;
}
