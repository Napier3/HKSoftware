#pragma once

#include "Config\MonitorCapConfig.h"
#include "EpEthernetCapThread.h"
#include "EpSerialCapThread.h"

class CEpCapThreadMngr : public CExBaseList
{
public:
	CEpCapThreadMngr(void);
	~CEpCapThreadMngr(void);

	CMonitorCapConfig* GetEpCapConfig()	{	return m_pEpCapConfig;	}
protected:
	CMonitorCapConfig *m_pEpCapConfig;

public:
	virtual void InitCapConfig();
	virtual void CreateCapture();
	virtual void ReleaseCapture();
	virtual void RestartNetCap(long nNetCardIndex);
	virtual void ViewThreadRunInfor();
	virtual BOOL CanRestartNetCap(long &nCardIndex, BOOL bReset);

	virtual void StartCapture();
	virtual void StopCapture();
	virtual void ResumeCapture();
	virtual void ExitCapture();
	virtual BOOL HasAllCapThreadExit();
	virtual BOOL IsCaptureStarted();
	virtual void SetCanFreeAllCapDatas();

protected:
	CEpEthernetCapThread* CreateCapThread(CEmcNetDevice *pNetDevice);
	CEpSerialCapThread* CreateCapThread(CEmcSerialConfig *pSerialDevice);
	virtual void CreateCapture(CExBaseList *pList);
};
