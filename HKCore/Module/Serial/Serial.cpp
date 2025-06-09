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
		���ܣ��򿪴���
		nComNumber:���ںţ����磺1
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
		m_handle=CreateFile((LPCWSTR)chName,//�˿�
#else
		m_handle=CreateFile((LPCSTR)chName,//�˿�
#endif
			GENERIC_READ|GENERIC_WRITE, //�������д
			0, //��ռ��ʽ
			NULL,
			OPEN_EXISTING, //�򿪶����Ǵ���
			FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //�첽��ʽ
			NULL//�Դ��ڶ��Ըò���������ΪNULL
			);
	}
	else
	{
#ifdef UNICODE
		m_handle=CreateFile((LPCWSTR)chName,//�˿�
#else
		m_handle=CreateFile(chName,//�˿�
#endif
			GENERIC_READ|GENERIC_WRITE, //�������д
			0, //��ռ��ʽ
			NULL,
			OPEN_EXISTING, //�򿪶����Ǵ���
			0, //FILE_ATTRIBUTE_NORMAL/*|FILE_FLAG_OVERLAPPED*/, //�첽��ʽ
			NULL//�Դ��ڶ��Ըò���������ΪNULL
			);

	}

	if(m_handle==(HANDLE)-1)
	{
		int nn=GetLastError();
		SetError((char*)"�ô����Ѿ���ռ�û��߲����ڣ�");
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
	���ܣ���������
	chWriteBuffer:������������
	nDataLen���������ݳ���
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
			m_handle,	//���ڵľ��
			(LPCVOID)chWriteBuffer,	// д������ݴ洢�ĵ�ַ
			nDataLen,//Ҫд������ݵ��ֽ���
			&dwNumberOfBytesWritten,// ָ��ָ��һ��DWORD��ֵ������ֵ����ʵ��д����ֽ���
			&m_WriteOverlapped 	// �ص�����ʱ���ò���ָ��һ��OVERLAPPED�ṹ��ͬ������ʱ���ò���ΪNULL
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
			m_handle,	//���ڵľ��
			(LPCVOID)chWriteBuffer,	// д������ݴ洢�ĵ�ַ
			nDataLen,//Ҫд������ݵ��ֽ���
			&dwNumberOfBytesWritten,// ָ��ָ��һ��DWORD��ֵ������ֵ����ʵ��д����ֽ���
			NULL 	// �ص�����ʱ���ò���ָ��һ��OVERLAPPED�ṹ��ͬ������ʱ���ò���ΪNULL
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

	SetError((char*)("�������ݳ���"));
	return CODE_ERROR;
}

int CSerial::RecieveData(BYTE *chReadBuffer,DWORD &nDataLen)
{
	return RecieveData((char*)chReadBuffer, nDataLen);
}

int CSerial::RecieveData(char *chReadBuffer,DWORD &nDataLen)
{

	/*
	���ܣ���������
	chReadBuffer:������������
	nDataLen������ʵ�����ݳ���
	*/

	ClearError(m_Readcomstat);
	BOOL bRead=FALSE;
	DWORD dwReadDataLen=4096;

	nDataLen=min(dwReadDataLen, (DWORD)m_Readcomstat.cbInQue);
	bRead=ReadFile(
						m_handle,	//���ڵľ��
						chReadBuffer,	
						nDataLen,	// Ҫ��������ݵ��ֽ���	
						&nDataLen,// ָ��һ��DWORD��ֵ������ֵ���ض�����ʵ�ʶ�����ֽ���
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
			SetError((char*)("��ȡ���ڴ���"));
		}
	}

	return CODE_OK;
}


int CSerial::SetSerialAttributes()
{
	/*
		���ܣ����ô��ڵ�����
	*/
	if(SetCommState(m_handle,&m_SerialDcbStruct))
	{
		
		return CODE_OK;
	}

	SetError((char*)("���ô�������ʧ�ܣ�"));

	return CODE_ERROR;
	
}


int CSerial::SetSerialAttributes(int nBaudRate, int nDataBit, int nStopBit, int nParity)
{
	/*
	  ���ܣ����ô��ڵĲ����ʣ�����λ��ֹͣλ��У��λ
	  ������
	  nBaudRate��������
	  nDataBit������λ
	  nStopBit��ֹͣλ
	  nParit��У��λ
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

	SetError((char*)("��ȡ��������ʧ�ܣ�"));
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
	//�ڶ�һ�����뻺���������ݺ���������������أ�
	//�������Ƿ������Ҫ����ַ���

	//�趨д��ʱ
	m_Timeout.WriteTotalTimeoutMultiplier=100;
	m_Timeout.WriteTotalTimeoutConstant=500;
	SetCommTimeouts(m_handle,&m_Timeout); //���ó�ʱ

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
	���ܣ����û������ֽ���
	nInputBuffer:���뻺����
	nOutPutBuffer�����������
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
	SetError("���û�����ʱ��������");
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
