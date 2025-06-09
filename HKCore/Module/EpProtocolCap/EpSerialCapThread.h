#pragma once

#include "EpSerialCapGlobalDef.h"
#include "EpCapThreadBase.h"
#include "Config\EmcSerialConfig.h"
#include "..\Serial\Serial.h"


class CEpSerialCapThread : public CEpCapThreadBase
{
public:
	CEpSerialCapThread(void);
	~CEpSerialCapThread(void);
	virtual UINT GetClassID()	{	return CAPTHREAD_SERIAL;	}

	static CEpSerialCapThread* CreateCapThread()
	{
		CEpSerialCapThread *pThread = new CEpSerialCapThread();
		return pThread;
	}

	CEmcSerialConfig* GetCapConfig()	{	return m_pCapConfig;	}
	void SetCapConfig(CEmcSerialConfig *pConfig)	{	m_pCapConfig = pConfig;	}

protected:
	HANDLE m_hSerial;

	CEmcSerialConfig *m_pCapConfig; 
	CCycleMemBuffer m_buffer;

protected:
	virtual DWORD CreateCaptureThread();
	virtual void ExitCapture();
	void ReadFromSerial(COMSTAT &comstat, DWORD &dwError, BYTE *byData, DWORD &dwCount);

protected:
	static UINT CaptureThread(LPVOID pParam);	
	static UINT ParseThread(LPVOID pParam);	

	HANDLE OpenSerial();
	void CloseSerial();
};
