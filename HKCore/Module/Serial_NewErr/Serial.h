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
	int virtual OpenSerial(int nComNumber);//�򿪴���
	int virtual SendData(char *chWriteBuffer,int nDataLen);//��������
	int virtual RecieveData(char *chReadBuffer,DWORD &nDataLen);//��������
	int virtual SetSerialAttributes();//���ô��ڵĲ����ʣ�ֹͣλ��У��λ������λ������
	int virtual SetSerialAttributes(int nBaudRate,int nDataBit,int nStopBit,int nParity);//���ô��ڵĲ����ʣ�ֹͣλ��У��λ������λ
	int virtual GetSerialAttributes();//�õ����ڵĲ����ʣ�ֹͣλ��У��λ������λ
	int virtual SetSerialBufferSize(int nInputBuffer,int nOutPutBuffer);//�������뻺�����������������С
	void virtual GetError(char *chError);
	void virtual CloseSerial();

	void SetUseOverlapped(BOOL bUseOverlapped)	{	m_bUseOverlapped = bUseOverlapped;	}

public:
	DCB m_SerialDcbStruct;
private:
	int virtual SetRWTimeOut();// ���ó�ʱʱ��
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
