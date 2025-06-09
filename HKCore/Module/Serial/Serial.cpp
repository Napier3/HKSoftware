#include "StdAfx.h"
#include "Serial.h"

CSerial::CSerial(void)
{
	m_handle=(HANDLE)-1;

	memset(m_chErrorInformation,0,512);
	m_dwErrorFlags=0;

	memset(&m_Writecomstat,0,sizeof(COMSTAT));
	memset(&m_Readcomstat,0,sizeof(COMSTAT));

	memset(&m_WriteOverlapped,0,sizeof(OVERLAPPED));
	memset(&m_ReadOverlapped,0,sizeof(OVERLAPPED));
	m_bUseOverlapped = TRUE;
}

CSerial::~CSerial(void)
{

}


int CSerial::OpenSerial(int nComNumber)
{
	/*
		功能：打开串口
		nComNumber:串口号：例如：1
	*/
#ifdef _PSX_IDE_QT_
	WCHAR chName[50]={0};
	swprintf(chName,L"\\\\.\\COM%d",nComNumber);
#else
#ifdef _UNICODE
	WCHAR chName[50]={0};
	swprintf(chName,L"\\\\.\\COM%d",nComNumber);
#else
	char chName[50]={0};
	sprintf(chName,"\\\\.\\COM%d",nComNumber);
#endif
#endif

	if (m_bUseOverlapped)
	{
#ifdef UNICODE
		m_handle=CreateFile((LPCWSTR)chName,//端口
#else
		m_handle=CreateFile((LPCSTR)chName,//端口
#endif
			GENERIC_READ|GENERIC_WRITE, //允许读和写
			0, //独占方式
			NULL,
			OPEN_EXISTING, //打开而不是创建
			FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //异步方式
			NULL//对串口而言该参数必须置为NULL
			);
	}
	else
	{
#ifdef UNICODE
		m_handle=CreateFile((LPCWSTR)chName,//端口
#else
		m_handle=CreateFile(chName,//端口
#endif
			GENERIC_READ|GENERIC_WRITE, //允许读和写
			0, //独占方式
			NULL,
			OPEN_EXISTING, //打开而不是创建
			0, //FILE_ATTRIBUTE_NORMAL/*|FILE_FLAG_OVERLAPPED*/, //异步方式
			NULL//对串口而言该参数必须置为NULL
			);

	}

	if(m_handle==(HANDLE)-1)
	{
		int nn=GetLastError();
		SetError((char*)"该串口已经被占用或者不存在！");
		return CODE_ERROR;
	}

	
	if (m_bUseOverlapped)
	{
		PurgeComm(m_handle, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
		SetRWTimeOut();
		m_ReadOverlapped.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
		m_WriteOverlapped.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	}
	else
	{
		//SetupComm(m_handle, 4096, 4096);
		//PurgeComm(m_handle, PURGE_TXCLEAR|PURGE_RXCLEAR);
	}

	return CODE_OK;

}

int CSerial::OpenSerialEx()
{
	int nComm = 0;
	m_oConfig.GetSerialComm((long&) nComm);
	return OpenSerial(nComm);
}

int CSerial::SendData(BYTE *chWriteBuffer,int nDataLen)
{
	return SendData((char*)chWriteBuffer, nDataLen);
}

int CSerial::SendData(char *chWriteBuffer,int nDataLen)
{

	/*
	功能：发送数据
	chWriteBuffer:存贮发送数据
	nDataLen：发送数据长度
	*/

	if (m_bUseOverlapped)
	{
		ClearError(m_Writecomstat);
	}
	else
	{
		COMSTAT comstat;
		DWORD dwError = 0;

		if (!ClearCommError(m_handle, &dwError, &comstat) || dwError != 0)
		{
			PurgeComm(m_handle, PURGE_RXABORT | PURGE_RXCLEAR);
			Sleep(10);
		}

		if (comstat.cbInQue == 0)
		{
			Sleep(10);
		}
	}


	DWORD dwNumberOfBytesWritten=0;
	BOOL bWrite=FALSE;

	if (m_bUseOverlapped)
	{
		bWrite=WriteFile(
			m_handle,	//串口的句柄
			(LPCVOID)chWriteBuffer,	// 写入的数据存储的地址
			nDataLen,//要写入的数据的字节数
			&dwNumberOfBytesWritten,// 指向指向一个DWORD数值，该数值返回实际写入的字节数
			&m_WriteOverlapped 	// 重叠操作时，该参数指向一个OVERLAPPED结构，同步操作时，该参数为NULL
			);

		if(bWrite)
		{
			return CODE_OK;
		}

		if(GetLastError()==ERROR_IO_PENDING)
		{
			WaitForSingleObject(m_WriteOverlapped.hEvent,2000);
			//	PurgeComm(m_handle, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
		}		
	}
	else
	{
		bWrite=WriteFile(
			m_handle,	//串口的句柄
			(LPCVOID)chWriteBuffer,	// 写入的数据存储的地址
			nDataLen,//要写入的数据的字节数
			&dwNumberOfBytesWritten,// 指向指向一个DWORD数值，该数值返回实际写入的字节数
			NULL 	// 重叠操作时，该参数指向一个OVERLAPPED结构，同步操作时，该参数为NULL
			);

		if(bWrite)
		{
			return CODE_OK;
		}

		if(GetLastError()==ERROR_IO_PENDING)
		{
			WaitForSingleObject(m_WriteOverlapped.hEvent,2000);
		}	
	}

	SetError((char*)("发送数据出错！"));
	return CODE_ERROR;
}

int CSerial::RecieveData(BYTE *chReadBuffer,DWORD &nDataLen)
{
	return RecieveData((char*)chReadBuffer, nDataLen);
}

int CSerial::RecieveData(char *chReadBuffer,DWORD &nDataLen)
{

	/*
	功能：接收数据
	chReadBuffer:存贮接收数据
	nDataLen：返回实际数据长度
	*/

	ClearError(m_Readcomstat);
	BOOL bRead=FALSE;
	DWORD dwReadDataLen=4096;

	nDataLen=min(dwReadDataLen, (DWORD)m_Readcomstat.cbInQue);
	bRead=ReadFile(
						m_handle,	//串口的句柄
						chReadBuffer,	
						nDataLen,	// 要读入的数据的字节数	
						&nDataLen,// 指向一个DWORD数值，该数值返回读操作实际读入的字节数
						&m_ReadOverlapped 	
					);	

	if(!bRead)
	{
		if(GetLastError()==ERROR_IO_PENDING)
		{
			WaitForSingleObject(m_ReadOverlapped.hEvent,2000);
			PurgeComm(m_handle, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
		}
		else
		{
			SetError((char*)("读取串口错误！"));
		}
	}

	return CODE_OK;
}


int CSerial::SetSerialAttributes()
{
	/*
		功能：设置串口的属性
	*/
	if(SetCommState(m_handle,&m_SerialDcbStruct))
	{
		
		return CODE_OK;
	}

	SetError((char*)("设置串口属性失败！"));

	return CODE_ERROR;
	
}


int CSerial::SetSerialAttributes(int nBaudRate, int nDataBit, int nStopBit, int nParity)
{
	/*
	  功能：设置串口的波特率，数据位，停止位，校验位
	  参数：
	  nBaudRate：波特率
	  nDataBit：数据位
	  nStopBit：停止位
	  nParit：校验位
	*/
	//GetCommState(m_handle, &m_SerialDcbStruct);

	m_SerialDcbStruct.BaudRate=nBaudRate;
	m_SerialDcbStruct.ByteSize=nDataBit ;
	m_SerialDcbStruct.StopBits=nStopBit;
	m_SerialDcbStruct.Parity=nParity;

	if(SetSerialAttributes()!=CODE_ERROR)
	{
		return CODE_OK;
	}

	return CODE_ERROR;
	
}

int CSerial::SetSerialAttributesEx()
{
	GetSerialAttributes();
	
	long nVal = 0;

	m_oConfig.GetSerialBaudRate(nVal);
	m_SerialDcbStruct.BaudRate = nVal;

	m_oConfig.GetSerialDataBit(nVal);
	m_SerialDcbStruct.ByteSize = nVal;

	m_oConfig.GetSerialStopBit(nVal);
	m_SerialDcbStruct.StopBits = nVal;

	m_oConfig.GetSerialParity(nVal);
	m_SerialDcbStruct.Parity = nVal;

	if(SetSerialAttributes()!=CODE_ERROR)
	{
		return CODE_OK;
	}

	return CODE_ERROR;

}



int CSerial::GetSerialAttributes()
{
	if(GetCommState(m_handle,&m_SerialDcbStruct))
	{
		return CODE_OK;
	}

	SetError((char*)("获取串口属性失败！"));
	return CODE_ERROR;

}


void CSerial::ClearError(COMSTAT &constat)
{
	if(!ClearCommError(m_handle,&m_dwErrorFlags,&constat))
	{
		int nn=GetLastError();
	}
}

int CSerial::SetRWTimeOut()
{
	m_Timeout.ReadIntervalTimeout=MAXDWORD;
	m_Timeout.ReadTotalTimeoutMultiplier=0;
	m_Timeout.ReadTotalTimeoutConstant=0;
	//在读一次输入缓冲区的内容后读操作就立即返回，
	//而不管是否读入了要求的字符。

	//设定写超时
	m_Timeout.WriteTotalTimeoutMultiplier=100;
	m_Timeout.WriteTotalTimeoutConstant=500;
	SetCommTimeouts(m_handle,&m_Timeout); //设置超时

	return CODE_OK;
}

void CSerial::SetError(char *chError)
{
	if(chError==NULL)
	{
		return;
	}

	memset(m_chErrorInformation,0,512);
	memcpy(m_chErrorInformation,chError,strlen(chError));
}

void CSerial::GetError(char *chError)
{
	if(chError==NULL)
	{
		return;
	}

	memcpy(chError,m_chErrorInformation,strlen((char*)m_chErrorInformation));
}

int CSerial::SetSerialBufferSize(int nInputBuffer,int nOutPutBuffer)
{
	/*
	功能：设置缓冲区字节数
	nInputBuffer:输入缓冲区
	nOutPutBuffer：输出缓冲区
	*/

	if(SetupComm(m_handle,nInputBuffer,nInputBuffer))
	{
		if (m_bUseOverlapped)
		{
			PurgeComm(m_handle, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR );
		}
		else
		{
			PurgeComm(m_handle, PURGE_TXCLEAR | PURGE_RXCLEAR );
		}

		return CODE_OK;
	}
	
	PurgeComm(m_handle, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR );
	SetError("设置缓冲区时发生错误！");
	return CODE_ERROR;
	
}

void CSerial::CloseSerial()
{
	if (m_handle != (HANDLE)-1)
	{
		CloseHandle(m_handle);
		m_handle = (HANDLE)-1;
	}
}
