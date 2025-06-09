#pragma once

// CEpEngineBaseApp

#include "..\CriticalSection\SynCriticalSection.h"
#include "EpEngineThread.h"

class CEpEngineBaseApp : public CWinAppEx
{
public:
	CEpEngineBaseApp();
	virtual ~CEpEngineBaseApp();

public:
	//初始化
	virtual long InitPpBaseApp();
	virtual long ExitPpBaseApp();
	virtual long ExitEngineThread();
	virtual BOOL IsAllEngineThreadExit();
	BOOL GetProtocolSpy()	{	return m_bProtocolSpy;	}
	void SetProtocolSpy(BOOL bProtocolSpy=TRUE)	{	m_bProtocolSpy = bProtocolSpy;	}
	void SetCurrSpyDevice(CEpDevice *pDevice = NULL)	{		m_pCurrSpyDevice = pDevice;	}
	CEpDevice* GetCurrSpyDevice()	{		return m_pCurrSpyDevice;	}
	BOOL IsExitEngineThread()	{		return m_bExitEngineThread;	}	

//////////////////////////////////////////////////////////////////////////
//引擎管理部分
private:
	CEpEngineDataMngrCntr *m_pPpEngineDataMngrCntr;
	CAutoCriticSection m_oEngineDataCriticSection;
	BOOL m_bProtocolSpy;
	CEpDevice *m_pCurrSpyDevice;
	BOOL m_bExitEngineThread;

public:
	CEpEngineDataMngrCntr* GetPpEngineDataMngrCntr(){return m_pPpEngineDataMngrCntr;}

public:
	CEpEngineData* Create(CEpProtocolBase *pProtocol, CEpDevice *pDevice);  //新建设备
	BOOL LoadEngineData(CEpEngineData*pEngineData, const CString &strPpTemplateFile, const CString &strDeviceFile);
	void ReleaseEngineData(CEpEngineData *pData);
	void ReleaseEngineDataMngrCntr();
	void DeleteEngineData(CEpEngineData *pData);
	BOOL HasEngineDataDeleted(CEpEngineData *pData);

	CEpEngineThread* FindEngineThread(CEpProtocolBase *pTemplate);
};
