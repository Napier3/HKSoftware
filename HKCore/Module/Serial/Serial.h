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
	virtual int OpenSerial(int nComNumber);//�򿪴���
	virtual int SendData(char *chWriteBuffer,int nDataLen);//��������
	virtual int SendData(BYTE *chWriteBuffer,int nDataLen);//��������
	virtual int RecieveData(char *chReadBuffer,DWORD &nDataLen);//��������
	virtual int RecieveData(BYTE *chReadBuffer,DWORD &nDataLen);//��������
	virtual int SetSerialAttributes();//���ô��ڵĲ����ʣ�ֹͣλ��У��λ������λ������
	virtual int SetSerialAttributes(int nBaudRate,int nDataBit,int nStopBit,int nParity);//���ô��ڵĲ����ʣ�ֹͣλ��У��λ������λ
	virtual int GetSerialAttributes();//�õ����ڵĲ����ʣ�ֹͣλ��У��λ������λ
	virtual int SetSerialBufferSize(int nInputBuffer,int nOutPutBuffer);//�������뻺�����������������С
	virtual void GetError(char *chError);
	virtual void CloseSerial();
	virtual BOOL OpenSucc()	{	return (m_handle != (HANDLE)-1);	}
	HANDLE GetHANDLE()	{	return m_handle;	}

	void SetUseOverlapped(BOOL bUseOverlapped)	{	m_bUseOverlapped = bUseOverlapped;	}

	//////////////////////
	//sf 20211115  ����ֱ�Ӵ������ļ��ж�ȡ���ڲ�������
	virtual int OpenSerialEx();
	virtual int SetSerialAttributesEx();

public:
	DCB m_SerialDcbStruct;
private:
	virtual int SetRWTimeOut();// ���ó�ʱʱ��
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
