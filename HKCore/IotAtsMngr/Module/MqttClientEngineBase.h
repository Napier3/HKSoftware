#pragma once

#include "SttMqttClientTool.h"
#include "SttMqttCmdExec.h"
#include "PpProject/PpPrjDevices.h"
#include "../../Module/BaseClass/XTimer.h"

#define WM_UPDATE_RTDEVICE_MSG   (WM_USER+100)

class CMqttClientEngineBase : public CXTimer,public CSttMqttMsgInterface
{
public:
	CMqttClientEngineBase();
	virtual ~CMqttClientEngineBase();

	//mqtt�ӿ�
public:
	virtual void OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen);
	virtual void OnMqttDisconnected(char *pszErr);
public:
	virtual void OnXTimer(DWORD dwTimerID);
public:
	void InitMqttClientEngineBase();
	void ExitMqttClientEngineBase();

	BOOL SubcribeMqttTopic(int nQos);
	CSttMqttCmdExec *CreatePpEngineDatas(const CString &strProjectFile);
	CSttMqttCmdExec *CreatePpEngineDatas(CPpPrjDevices *pPpCfgDevices);

	CSttMqttCmdExec *FindDevice(__int64 nSensorID,CPpPrjDevice **ppPrjDevice);
	CSttMqttCmdExec* FindEngineData(const CString &strID);
	CString GetDeviceReportFile(CPpPrjDevice *pDevice);
	void UpdateRTDevice(CPpPrjDevice *pDevice);
	BOOL InitRawPkgFile();
	void WriteRawPkg(char *pBuf,long nLen);

	void ReleaseDevice(const CString &strDeviceID);
	void ReleaseAllDevice();

public:
	CFile m_oRawPkgFile;
	CWnd *m_pMsgWnd;	//ʵʱװ������ˢ�½���
	CExBaseList m_oMqttCmdExecMngr;//����ִ�п��ƹ����Ӷ���ΪCSttMqttCmdExec

};

extern CMqttClientEngineBase *g_pMqttClientEngineBase;