#pragma once

#include "SerialConfig/SerialConfig.h"

const int CODE_OK=1;
const int CODE_ERROR=-1;


class CSerial
{
public:
	CSerial(void);
	virtual ~CSerial(void);

	CSerialConfig m_oConfig;

public:
	virtual int OpenSerial(int nComNumber);//打开串口
	virtual int SendData(char *chWriteBuffer,int nDataLen);//发送数据
	virtual int SendData(BYTE *chWriteBuffer,int nDataLen);//发送数据
	virtual int RecieveData(char *chReadBuffer,DWORD &nDataLen);//接收数据
	virtual int RecieveData(BYTE *chReadBuffer,DWORD &nDataLen);//接收数据
	virtual int SetSerialAttributes();//设置串口的波特率，停止位，校验位，数据位等属性
	virtual int SetSerialAttributes(int nBaudRate,int nDataBit,int nStopBit,int nParity);//设置串口的波特率，停止位，校验位，数据位
	virtual int GetSerialAttributes();//得到串口的波特率，停止位，校验位，数据位
	virtual int SetSerialBufferSize(int nInputBuffer,int nOutPutBuffer);//串口输入缓冲区和输出缓冲区大小
	virtual void GetError(char *chError);
	virtual void CloseSerial();
	virtual BOOL OpenSucc()	{	return (m_handle != (HANDLE)-1);	}
	HANDLE GetHANDLE()	{	return m_handle;	}

	void SetUseOverlapped(BOOL bUseOverlapped)	{	m_bUseOverlapped = bUseOverlapped;	}

	//////////////////////
	//sf 20211115  增加直接从配置文件中读取串口参数功能
	virtual int OpenSerialEx();
	virtual int SetSerialAttributesEx();

public:
	DCB m_SerialDcbStruct;
private:
	virtual int SetRWTimeOut();// 设置超时时间
	virtual void SetError(char *chError);
	virtual void ClearError(COMSTAT &constat);
//	virtual int  GetSerialName(char *chName);

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
