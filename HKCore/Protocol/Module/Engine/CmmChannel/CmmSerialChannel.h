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

	//2019-1-7:COM5003表计，谐波报文最大超过10K，所以将缓冲区大小放大到100K
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
	CSerial *m_pSerialComm;//串口通讯对象		

	BOOL InitSerial();//初始化串口
	void CloseSerial();

#define SERIAL_INPUTBUFFERLEN  4096//输入缓冲区长度。单位：bytes
#define SERIAL_OUTBUFFERLEN    4096//输出缓冲区长度。单位：bytes

};
