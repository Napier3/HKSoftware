#include "StdAfx.h"
#include "EpSerialCapThread.h"


CEpSerialCapThread::CEpSerialCapThread(void)
{
	m_hSerial = NULL;

	m_pCaptureThread = NULL;
	m_buffer.SetBufferLength(MAX_SERIAL_BUFFER_LEN);
}

CEpSerialCapThread::~CEpSerialCapThread(void)
{
	CloseSerial();
	m_buffer.FreeBuffer();
}

DWORD CEpSerialCapThread::CreateCaptureThread()
{
	if (g_DEBUG_MONITOR_STATE == 1)
	{
		m_hSerial = NULL;
	}
	else
	{
		m_hSerial = OpenSerial();

		if (m_hSerial == NULL)
		{
			CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("（%s）打开串口失败"), m_strName);
			return 0xFFFFFFFF;
		}	
		else
		{
			CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("（%s）打开串口成功"), m_strName);
		}
	}

	m_pCaptureThread = AfxBeginThread(CaptureThread,this);
	m_pCaptureThread->m_bAutoDelete = TRUE;

	if (m_bUseParseThread)
	{
		m_pParseThread = AfxBeginThread(ParseThread,this);
		m_pParseThread->m_bAutoDelete = TRUE;
	}

	return 0;
}

void CEpSerialCapThread::ExitCapture()
{
	
}

HANDLE CEpSerialCapThread::OpenSerial()
{
	HANDLE hSerial;
	CString strSerial, strMsg;
	strSerial.Format(_T("COM%d"), m_pCapConfig->m_nPort);

	hSerial = ::CreateFile(strSerial, 
		GENERIC_READ | GENERIC_WRITE, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		0/*FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED*/, 
		NULL); 
	if(hSerial == INVALID_HANDLE_VALUE) 
	{ 
		CloseHandle(hSerial);
		hSerial = NULL;
		strMsg.Format(_T("%s打开失败"), strSerial);
		MessageBox(NULL, strMsg, _T("提示"), MB_OK);
		return NULL;
	}

	SetupComm(hSerial, MAX_BUFFER_LEN, MAX_BUFFER_LEN);
	DCB dcbConfig;
	GetCommState(hSerial, &dcbConfig);

	dcbConfig.BaudRate = m_pCapConfig->m_nBaudRate;
	dcbConfig.ByteSize = m_pCapConfig->m_nByteSize;
	dcbConfig.Parity = m_pCapConfig->m_nParity;
	dcbConfig.StopBits = m_pCapConfig->m_nStopBits;

	SetCommState(hSerial, &dcbConfig);
	PurgeComm(hSerial, PURGE_TXCLEAR|PURGE_RXCLEAR);
	return hSerial;
}

void CEpSerialCapThread::CloseSerial()
{
	if (m_hSerial == NULL)
	{
		return;
	}

	PurgeComm(m_hSerial, PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
	CloseHandle(m_hSerial);
	m_hSerial = NULL;
}

void  CEpSerialCapThread::ReadFromSerial(COMSTAT &comstat, DWORD &dwError, BYTE *byData, DWORD &dwCount)
{
	dwCount = 0;

	if (!ClearCommError(m_hSerial, &dwError, &comstat) || dwError != 0)
	{
		PurgeComm(m_hSerial, PURGE_RXABORT | PURGE_RXCLEAR);
		//Sleep(10);
		return;
	}

	if (comstat.cbInQue == 0)
	{
		//Sleep(10);
		return;
	}

	ReadFile(m_hSerial, byData, comstat.cbInQue, &dwCount, NULL);

// 	if (dwCount > 0 || comstat.cbInQue > 0)
// 	{
// 		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("%d>>%d"), comstat.cbInQue, dwCount);
// 	}
}

UINT CEpSerialCapThread::CaptureThread(LPVOID pParam)
{
	CEpSerialCapThread* pThis = (CEpSerialCapThread*)pParam;
	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("（%s）开启串口监视线程"), pThis->m_strName);
	
	// 开始对串口数据监视
	CString strContent;
	DWORD dwError = 0;

	BYTE byData[MAX_BUFFER_LEN];
	EP_ETHER_CAP_IP_GROUP ipg;
	memset(&ipg, 0, sizeof(EP_ETHER_CAP_IP_GROUP));
	ipg.dst.port = (u_short)pThis->m_pCapConfig->m_nPort;
	ipg.src.port = (u_short)pThis->m_pCapConfig->m_nPort;
	long nReadDataLen = 0;

	DWORD dwCount; //读取的字节数
	COMSTAT comstat;

	ClearCommError(pThis->m_hSerial, &dwError, &comstat);
	PurgeComm(pThis->m_hSerial, PURGE_TXCLEAR|PURGE_RXCLEAR);

	if (g_DEBUG_MONITOR_STATE == 1)
	{
		pThis->CapGenDataThread(EP_CAP_CHTYPE_SERIAL, &ipg);
	}
	else
	{
		CCapCycleMemBuffer *pBuffer = NULL;

		while (TRUE)
		{
			if (pThis->m_bExitCapture)
			{
				break;
			}

			if (pThis->m_bViewThreadRunInfor)
			{
				CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("%s running......"), pThis->m_strName);
				pThis->m_bViewThreadRunInfor = FALSE;
			}

			if (!pThis->m_bCapData)
			{
				Sleep(500);
				continue;
			}

			if (pThis->m_oCapCycleBufferMngr.GetCount() > 100000)
			{
				pThis->m_bCapData = FALSE;
				CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("%s 线程监视出现错误"), pThis->m_strName);
			}

			dwCount = 0;
			nReadDataLen = 0;
// 			if (!ClearCommError(pThis->m_hSerial, &dwError, &comstat) || dwError != 0)
// 			{
// 				PurgeComm(pThis->m_hSerial, PURGE_RXABORT | PURGE_RXCLEAR);
// 				Sleep(10);
// 				continue;
// 			}
// 
// 			if (comstat.cbInQue == 0)
// 			{
// 				Sleep(10);
// 				continue;
// 			}
// 
// 			ReadFile(pThis->m_hSerial, byData, comstat.cbInQue, &dwCount, NULL);
			pThis->ReadFromSerial(comstat, dwError, byData, dwCount);

// 			if (dwCount > 0)
// 			{
// 				pBuffer = pThis->m_oCapCycleBufferMngr.AddCapBuffer(ipg, byData, dwCount, EP_CAP_CHTYPE_SERIAL);
// 				pThis->ParseEx(pBuffer);
// 			}
// 			else
// 			{
// 				Sleep(50);
// 			}

			//如果有数据
			if (dwCount > 0)
			{
				nReadDataLen += dwCount;
				long nIndex = 0;

				while (nIndex<3)
				{
					if (pThis->m_bExitCapture)
					{
						break;
					}

					Sleep(10);
					pThis->ReadFromSerial(comstat, dwError, byData+nReadDataLen, dwCount);

					if (dwCount == 0)
					{
						nIndex++;
					}
					else
					{
						nReadDataLen+=dwCount;
					}
				}

// 				CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("nReadDataLen=%d"), nReadDataLen);
				pBuffer = pThis->m_oCapCycleBufferMngr.AddCapBuffer(ipg, byData, nReadDataLen, EP_CAP_CHTYPE_SERIAL);
				pThis->ParseEx(pBuffer);
			}
			else
			{
				Sleep(50);	
			}

			//释放
			pThis->WriteCap();
			pThis->FreeAllParsedBuffer();
		}
	}

	pThis->CloseSerial();
	pThis->FreeAllCapDatas();
	pThis->m_pCaptureThread = NULL;
	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("监视线程（%s）结束"), pThis->m_strName);

	return 0;
}

UINT CEpSerialCapThread::ParseThread(LPVOID pParam)
{
	CEpSerialCapThread *pThis = (CEpSerialCapThread*)pParam;

//	pThis->Parse();
//	pThis->m_pParseThread = NULL;

	return 0;
}
