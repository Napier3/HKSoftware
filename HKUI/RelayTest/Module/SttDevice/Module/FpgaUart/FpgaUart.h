#ifndef FPGAUART_H
#define FPGAUART_H
#include "../../../Module/Socket/WinBaseSocket.h"

#define BandRate_4800		0
#define BandRate_9600		1
#define BandRate_14400		2
#define BandRate_19200		3
#define BandRate_38400		4
#define BandRate_57600		5
#define BandRate_115200		6
#define BandRate_128000		7

#define StopBit_1_0  0
#define StopBit_1_5  1
#define StopBit_2_0  2

#define DataLen_5  3
#define DataLen_6  2
#define DataLen_7  1
#define DataLen_8  0

#define Check_None  0
#define Check_Odd   1
#define Check_Even  2
#define Check_Mark  3

#define UartTotal  4
typedef struct
{
	long nModulePos;
	long nBand;
	long nStopBit;
	long nDatalen;
	long nCheck;
	long nOutput;//0-'RS485',1-'RS232
}UartSetting;

typedef struct
{
	long nUartCnt;
	UartSetting oUartSetting[UartTotal];
}UartSettings;

typedef struct
{
	BOOL bValid;
	unsigned char pszBuf[260];
}UartSendBuf;

typedef struct
{
	unsigned int nModule;
	long dat[70];
} Drv_UartData;
//仿串口服务器的功能，将Uart口数据桥接至Tcp端口
//单帧报文数据总长度限制为255字节
//Tcp发送至Uart口的速度由TcpClient端控制，需考虑Uart实际的报文发送耗时及转发耗时
//只适用于PL逻辑串口，不适用于PS系统串口
class CFpgaUart
{
public:
    CFpgaUart();
    ~CFpgaUart();
	void InitUart(UartSettings* pUartSettings);
	void SetUart(UartSettings* pUartSettings);
	void InitSocket();

public:
	SOCKET m_nSocketClient[UartTotal];
	SOCKET m_nSocketServer[UartTotal];
    int m_nFd;
	long m_nUartType;//0-插件串口,1-主板串口
	UartSettings m_oUartSettings;
	UartSendBuf m_oUartSendBuf[UartTotal];
	void SendUartData();
	BOOL m_bValid;

private:
	pthread_t m_pthread;
	Drv_UartData m_oUartDownload;
	Drv_UartData m_oUartSet;
	BOOL m_nUartInited;
};

void *AcceptSocketThread(void *pParam);
void *RecvSocketThread(void *pParam);
void *RecvUartThread(void *pParam);
extern CFpgaUart *g_pFpgaUart;
#endif
