#pragma once

#include <winbase.h>

const int CODE_OK=1;
const int CODE_ERROR=-1;


class CSerial
{
public:
	CSerial(void);
	virtual ~CSerial(void);

public:
	int virtual OpenSerial(int nComNumber);//打开串口
	int virtual SendData(char *chWriteBuffer,int nDataLen);//发送数据
	int virtual RecieveData(char *chReadBuffer,DWORD &nDataLen);//接收数据
	int virtual SetSerialAttributes();//设置串口的波特率，停止位，校验位，数据位等属性
	int virtual SetSerialAttributes(int nBaudRate,int nDataBit,int nStopBit,int nParity);//设置串口的波特率，停止位，校验位，数据位
	int virtual GetSerialAttributes();//得到串口的波特率，停止位，校验位，数据位
	int virtual SetSerialBufferSize(int nInputBuffer,int nOutPutBuffer);//串口输入缓冲区和输出缓冲区大小
	void virtual GetError(char *chError);
	void virtual CloseSerial();

	void SetUseOverlapped(BOOL bUseOverlapped)	{	m_bUseOverlapped = bUseOverlapped;	}

public:
	DCB m_SerialDcbStruct;
private:
	int virtual SetRWTimeOut();// 设置超时时间
	void virtual SetError(char *chError);
	void virtual ClearError(COMSTAT &constat);
//	int virtual  GetSerialName(char *chName);

private:
	OVERLAPPED m_WriteOverlapped;
	OVERLAPPED m_ReadOverlapped;
	HANDLE m_handle;
	COMSTAT m_Writecomstat;
	COMSTAT m_Readcomstat;
	DWORD m_dwErrorFlags;
	char* m_chErrorInformation[512];
	COMMTIMEOUTS m_Timeout;

	BOOL m_bUseOverlapped;

};
