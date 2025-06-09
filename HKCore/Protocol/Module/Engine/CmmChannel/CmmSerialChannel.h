#pragma once
#include "cmmchannel.h"
#include "../../../../Module/Serial/Serial.h"
#include "../DeviceModel/CmmSerialConfig.h"

class CCmmSerialChannel :	public CCmmChannel
{
public:
	CCmmSerialChannel(void);
	virtual ~CCmmSerialChannel(void);

	CCmmSerialConfig *m_pConfig;

	//2019-1-7:COM5003��ƣ�г��������󳬹�10K�����Խ���������С�Ŵ�100K
	char m_pszPpLogProtocol[CMM_RECEIVEBUFFER_LENGTH]; 

public:
	virtual UINT GetClassID(){return CMMCLASSID_SERIAL_CHANNEL;};

public:
	virtual BOOL Create(CExBaseObject *pConfig);
	virtual void Send(CExBaseObject *pPkgSend);
	virtual BOOL Connect();
	virtual BOOL DisConnect();
	virtual BOOL IsConnectSuccessful();
	virtual BOOL IsCmmChannelExit();
	virtual BOOL TerminateChannel();

public:
	static UINT SerialThread(LPVOID pParam);

	void Receive_FullPkg(DWORD &dwSndRcvState);
protected:
	void Receive(DWORD &dwSndRcvState);
	void Receive_Only(DWORD &dwSndRcvState);


private:
	CWinThread *m_pThread;
	BOOL m_bExitThread;
	CSerial *m_pSerialComm;//����ͨѶ����		

	BOOL InitSerial();//��ʼ������
	void CloseSerial();

#define SERIAL_INPUTBUFFERLEN  4096//���뻺�������ȡ���λ��bytes
#define SERIAL_OUTBUFFERLEN    4096//������������ȡ���λ��bytes

};
