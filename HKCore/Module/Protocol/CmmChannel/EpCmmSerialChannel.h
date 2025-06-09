#pragma once
#include "epcmmchannel.h"
#include "..\..\Serial\Serial.h"
#include "config\EpCmmSerialConfig.h"

class CEpCmmSerialChannel :	public CEpCmmChannel
{
public:
	CEpCmmSerialChannel(void);
	~CEpCmmSerialChannel(void);

	CEpCmmSerialConfig *m_pConfig;

public:
	virtual UINT GetClassID(){return EPCMMCLASSID_SERIAL_CHANNEL;};

public:
	virtual BOOL Create(CExBaseObject *pConfig);
	virtual void Send(CExBaseObject *pPkgSend);
	virtual BOOL Connect();
	virtual BOOL DisConnect();
	virtual BOOL IsConnectSuccessful();
	virtual BOOL IsEpCmmChannelExit();

public:
	static UINT SerialThread(LPVOID pParam);

private:
	CWinThread *m_pThread;
	BOOL m_bExitThread;
	CSerial *m_pSerialComm;//����ͨѶ����		

	BOOL InitSerial();//��ʼ������
	void CloseSerial();

#define SERIAL_INPUTBUFFERLEN  4096//���뻺�������ȡ���λ��bytes
#define SERIAL_OUTBUFFERLEN    4096//������������ȡ���λ��bytes

};
