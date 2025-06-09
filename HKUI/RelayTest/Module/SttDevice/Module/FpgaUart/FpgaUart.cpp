#include "FpgaUart.h"
#include <sys/ioctl.h>
#include <fcntl.h>
#include "../../../SttGlobalDef.h"
#include "../../SttDeviceBase.h"

long nRunFlag = 1;
CFpgaUart *g_pFpgaUart = NULL;

CFpgaUart::CFpgaUart()
{
	for(int i = 0; i < UartTotal;i++)
	{
		m_nSocketClient[i] = 0;
		m_oUartSendBuf[i].bValid = FALSE;
		memset(m_oUartSendBuf[i].pszBuf,0,260);
	}
	m_oUartSettings.nUartCnt = 0;
	m_nUartType = 0;
	m_bValid = FALSE;
	m_nUartInited = FALSE;
}

CFpgaUart::~CFpgaUart()
{
    nRunFlag = 0;
    Sleep(200);
}

void CFpgaUart::InitUart(UartSettings* pUartSettings)
{
	if(m_nUartInited)
	{
		SetUart(pUartSettings);
		return;
	}

	system("insmod /mnt/Stt/Bin/SttDriver_Uart");
	Sleep(200);
	m_nFd = open("/dev/SttDriver_Uart", O_RDWR);
	SetUart(pUartSettings);
    pthread_create(&m_pthread, NULL, RecvUartThread, this);
	InitSocket();
	m_nUartInited = TRUE;
}

void CFpgaUart::SetUart(UartSettings* pUartSettings)
{
	m_bValid = FALSE;
	memcpy(&m_oUartSettings,pUartSettings,sizeof(UartSettings));
	long nCode = 0;
	int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	if(m_nUartType)
	{
		//主板串口
		m_oUartSet.nModule = 0;
		switch(m_oUartSettings.oUartSetting[0].nBand)
		{
		case 4800:
			nCode |= BandRate_4800<<16;
			break;
		case 9600:
			nCode |= BandRate_9600<<16;
			break;
		case 14400:
			nCode |= BandRate_14400<<16;
			break;
		case 19200:
			nCode |= BandRate_19200<<16;
			break;
		case 38400:
			nCode |= BandRate_38400<<16;
			break;
		case 57600:
			nCode |= BandRate_57600<<16;
			break;
		case 128000:
			nCode |= BandRate_128000<<16;
			break;
		default:
			nCode |= BandRate_115200<<16;
		}

		if(m_oUartSettings.oUartSetting[0].nOutput)
		{
			//RS232
			nCode |= 1 << 6;
		}

		switch(m_oUartSettings.oUartSetting[0].nCheck)
		{
		case Check_Odd:
			nCode |= Check_Odd << 4;
			break;
		case Check_Even:
			nCode |= Check_Even << 4;
			break;
		case Check_Mark:
			nCode |= Check_Mark << 4;
			break;
		default:
			nCode |= Check_None << 4;
		}

		switch(m_oUartSettings.oUartSetting[0].nStopBit)
		{
		case StopBit_1_5:
			nCode |= StopBit_1_5;
			break;
		case StopBit_2_0:
			nCode |= StopBit_2_0;
			break;
		default:
			nCode |= StopBit_1_0;
		}

		switch(m_oUartSettings.oUartSetting[0].nDatalen)
		{
		case 5:
			nCode |= DataLen_5 << 2;
			break;
		case 6:
			nCode |= DataLen_6 << 2;
			break;
		case 7:
			nCode |= DataLen_7 << 2;
			break;
		default:
			nCode |= DataLen_8 << 2;
		}

		m_oUartSet.dat[0] = 0x05640564;
		m_oUartSet.dat[1] = 2;
		m_oUartSet.dat[2] = 0x4005;
		m_oUartSet.dat[3] = nCode;

		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(nFd, 0x322, 0);
		write(nFd, (char *)&m_oUartSet, sizeof(Drv_UartData));
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	}
	else
	{
		for(int i = 0;i < m_oUartSettings.nUartCnt;i++)
		{
			long nModulePos = m_oUartSettings.oUartSetting[i].nModulePos;
			m_oUartSet.nModule = ModuleIndexTransToDrv(nModulePos) << 16;
			nCode = 0;
			switch(m_oUartSettings.oUartSetting[i].nBand)
			{			
			case 4800:
				nCode |= BandRate_4800<<16;
				break;
			case 9600:
				nCode |= BandRate_9600<<16;
				break;
			case 14400:
				nCode |= BandRate_14400<<16;
				break;
			case 19200:
				nCode |= BandRate_19200<<16;
				break;
			case 38400:
				nCode |= BandRate_38400<<16;
				break;			
			case 57600:
				nCode |= BandRate_57600<<16;
				break;			
			case 128000:
				nCode |= BandRate_128000<<16;
				break;			
			default:
				nCode |= BandRate_115200<<16;
			}

			if(m_oUartSettings.oUartSetting[i].nOutput)
			{
				//RS232
				nCode |= 1 << 6;
			}

			switch(m_oUartSettings.oUartSetting[i].nCheck)
			{
			case Check_Odd:
				nCode |= Check_Odd << 4;
				break;
			case Check_Even:
				nCode |= Check_Even << 4;
				break;
			case Check_Mark:
				nCode |= Check_Mark << 4;
				break;
			default:
				nCode |= Check_None << 4;
			}

			switch(m_oUartSettings.oUartSetting[i].nStopBit)
			{
			case StopBit_1_5:
				nCode |= StopBit_1_5;
				break;
			case StopBit_2_0:
				nCode |= StopBit_2_0;
				break;
			default:
				nCode |= StopBit_1_0;
			}

			switch(m_oUartSettings.oUartSetting[i].nDatalen)
			{
			case 5:
				nCode |= DataLen_5 << 2;
				break;
			case 6:
				nCode |= DataLen_6 << 2;
				break;
			case 7:
				nCode |= DataLen_7 << 2;
				break;
			default:
				nCode |= DataLen_8 << 2;
			}

			m_oUartSet.dat[0] = 0x05640564;
			m_oUartSet.dat[1] = 2;
			m_oUartSet.dat[2] = 0x4005;
			m_oUartSet.dat[3] = nCode;

			g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
			ioctl(nFd, 0x322, 0);
			write(nFd, (char *)&m_oUartSet, sizeof(Drv_UartData));
			g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
		}
	}
	m_bValid = TRUE;
}

void CFpgaUart::InitSocket()
{
	long nPort = STT_PORT_UART_1;
	for(int i = 0; i < m_oUartSettings.nUartCnt;i++)
	{
		switch(i)
		{
		case 0:
			nPort = STT_PORT_UART_1;
			break;
		case 1:
			nPort = STT_PORT_UART_2;
			break;
		case 2:
			nPort = STT_PORT_UART_3;
			break;
		case 3:
			nPort = STT_PORT_UART_4;
			break;
		}

		if((m_nSocketServer[i] = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		{
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("CFpgaUart socket() failed"));
			return;
		}

		int optval = 1;
		setsockopt(m_nSocketServer[i], SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
		sockaddr_in m_sockaddr;
		memset(&m_sockaddr, 0, sizeof(m_sockaddr));
		m_sockaddr.sin_family = AF_INET;
		m_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		m_sockaddr.sin_port = htons(nPort);

		if(bind(m_nSocketServer[i], (SOCKADDR *)&m_sockaddr, sizeof(m_sockaddr)) == SOCKET_ERROR)
		{
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("CFpgaUart bind() failed"));
			close(m_nSocketServer[i]);
			return;
		}

		if(listen(m_nSocketServer[i], 1) == SOCKET_ERROR)
		{
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("CFpgaUart listen() failed"));
			close(m_nSocketServer[i]);
			return;
		}		
	}

	pthread_create(&m_pthread, NULL, AcceptSocketThread, this);
	pthread_create(&m_pthread, NULL, RecvSocketThread, this);
}

void CFpgaUart::SendUartData()
{
	if(!m_nUartInited)
		return;

	if(!m_bValid)
		return;

	int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	if(m_nUartType)
	{
		//主板串口
		if(m_oUartSendBuf[0].bValid)
		{
			if(g_oDrvMutex.trylock(__FILE__,__FUNCTION__,__LINE__))
			{
				m_oUartSendBuf[0].bValid = FALSE;
				m_oUartDownload.nModule = 0;
				m_oUartDownload.dat[0] = 0x05640564;
				m_oUartDownload.dat[1] = 66;
				m_oUartDownload.dat[2] = 0x4006;
				memcpy((char*)&m_oUartDownload.dat[3],m_oUartSendBuf[0].pszBuf,260);

				ioctl(nFd, 0x322, 0);
				write(nFd, (char *)&m_oUartDownload, sizeof(Drv_UartData));

				g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
			}
		}
	}
	else
	{
		for(int i = 0;i < m_oUartSettings.nUartCnt;i++)
		{
			if(m_oUartSendBuf[i].bValid)
			{
				if(g_oDrvMutex.trylock(__FILE__,__FUNCTION__,__LINE__))
				{
					m_oUartSendBuf[i].bValid = FALSE;
					long nModulePos = m_oUartSettings.oUartSetting[i].nModulePos;
					m_oUartDownload.nModule = ModuleIndexTransToDrv(nModulePos) << 16;
					m_oUartDownload.dat[0] = 0x05640564;
					m_oUartDownload.dat[1] = 66;
					m_oUartDownload.dat[2] = 0x4006;
					memcpy((char*)&m_oUartDownload.dat[3],m_oUartSendBuf[i].pszBuf,260);

					ioctl(nFd, 0x322, 0);
					write(nFd, (char *)&m_oUartDownload, sizeof(Drv_UartData));

					g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
				}
			}
		}
	}
}

void *AcceptSocketThread(void *pData)
{
	pthread_setname_np(pthread_self(),"Uart_AcceptSkt");
    CFpgaUart *pFpgaUart = (CFpgaUart *)pData;
    SOCKET serverSocket;
	long nUartCnt = pFpgaUart->m_oUartSettings.nUartCnt;

	struct timeval stTv;
	stTv.tv_sec = 0;
	stTv.tv_usec = 1000;
	fd_set allset;

    while(nRunFlag)
	{
		Sleep(5);

		for(int i = 0;i < UartTotal && i < nUartCnt;i++)
		{
			serverSocket = pFpgaUart->m_nSocketServer[i];
			if(serverSocket == NULL)
			{				
				continue;
			}

			FD_ZERO(&allset);
			FD_SET(serverSocket,&allset);
			int nReady = select((serverSocket+1),&allset,NULL,NULL,&stTv);
			if (nReady < 0)
			{
				continue;
			}

			if(FD_ISSET(serverSocket,&allset))
			{
				SOCKET clientSocket = accept(serverSocket, NULL, NULL);
				if(clientSocket > 0)
				{
					if(pFpgaUart->m_nSocketClient[i] > 0)
					{
						close(pFpgaUart->m_nSocketClient[i]);
					}

					pFpgaUart->m_nSocketClient[i] = clientSocket;
				}
			}
		}
    }

    pthread_exit(0);
}

void *RecvSocketThread(void *pData)
{
	pthread_setname_np(pthread_self(),"Uart_RecvSkt");
	CFpgaUart *pFpgaUart = (CFpgaUart *)pData;
	long nUartCnt = pFpgaUart->m_oUartSettings.nUartCnt;
	unsigned char buffer[256];
	struct timeval stTv;
	stTv.tv_sec = 0;
	stTv.tv_usec = 5000;
	fd_set allset;

    while(nRunFlag)
    {		
		Sleep(5);

		for(int i = 0;i < UartTotal && i < nUartCnt;i++)
		{
			memset(buffer,0,256);
			SOCKET clientSocket = pFpgaUart->m_nSocketClient[i];
			if(clientSocket == NULL)
			{				
				continue;
			}

			FD_ZERO(&allset);
			FD_SET(clientSocket,&allset);
			int nReady = select((clientSocket+1),&allset,NULL,NULL,&stTv);
			if (nReady < 0)
			{
				continue;
			}

			if(FD_ISSET(clientSocket,&allset))
			{
				int numrcv = recv(pFpgaUart->m_nSocketClient[i], buffer, 256, 0);
				if(numrcv > 0)
				{
					pFpgaUart->m_oUartSendBuf[i].pszBuf[0] = numrcv & 0xFF;
					pFpgaUart->m_oUartSendBuf[i].pszBuf[1] = (numrcv >> 8) & 0xFF;
					pFpgaUart->m_oUartSendBuf[i].pszBuf[2] = (numrcv >> 16) & 0xFF;
					pFpgaUart->m_oUartSendBuf[i].pszBuf[3] = (numrcv >> 24) & 0xFF;
					for(int j = 0;j < 64;j++)
					{
						pFpgaUart->m_oUartSendBuf[i].pszBuf[j*4+4] = buffer[j*4+3];
						pFpgaUart->m_oUartSendBuf[i].pszBuf[j*4+5] = buffer[j*4+2];
						pFpgaUart->m_oUartSendBuf[i].pszBuf[j*4+6] = buffer[j*4+1];
						pFpgaUart->m_oUartSendBuf[i].pszBuf[j*4+7] = buffer[j*4];
					}
					pFpgaUart->m_oUartSendBuf[i].bValid = TRUE;
				}
				else
				{
					close(pFpgaUart->m_nSocketClient[i]);
					pFpgaUart->m_nSocketClient[i] = NULL;
				}
			}
		}
    }

    pthread_exit(0);
    return 0;
}

void *RecvUartThread(void *pData)
{
	pthread_setname_np(pthread_self(),"Uart_Recv485");
    CFpgaUart *pFpgaUart = (CFpgaUart *)pData;
	long nUartCnt = pFpgaUart->m_oUartSettings.nUartCnt;
	long nModulePos[UartTotal];
	for(int i = 0;i < nUartCnt;i++)
	{
		nModulePos[i] = pFpgaUart->m_oUartSettings.oUartSetting[i].nModulePos - 1;
	}
    int numrcv;
    int nFd = pFpgaUart->m_nFd;
	long nUartType = pFpgaUart->m_nUartType;
	unsigned char buffer[260];
    long nSendLen;

    while(nRunFlag)
    {
		for(int i = 0;i < nUartCnt;i++)
		{
			if(nUartType == 0)
			{
				numrcv = read(nFd, buffer, nModulePos[i]);
			}
			else
			{
				numrcv = read(nFd, buffer, 0);
			}

			if(numrcv > 0)
			{
				nSendLen = buffer[1];
				if(nSendLen == 0)
				{
					//FPGA串口报文检测失败(校验位不符、波特率不对等)
					// CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("串口%d参数设置不合适,解析接收数据失败"),i+1);
				}
				else
				{
					write(pFpgaUart->m_nSocketClient[i], buffer + 4, nSendLen);
				}
			}
		}

		Sleep(30);
    }

    pthread_exit(0);
    return 0;
}
