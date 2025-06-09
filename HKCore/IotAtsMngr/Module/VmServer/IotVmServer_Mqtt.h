#pragma once

#include "IotVmEngineBase_Mqtt.h"
#include "../EngineServer/XCommSvrWnd.h"
#include "IotVmProtoToXImp.h"

#define WM_TIMER_ID_HEARTBEAT_TESTAPP   (WM_USER + 1945)
#define FILE_VM_CONFIG _T("VmEngineServerConfig.xml")

class CIotVmServer_Mqtt : public CIotVmEngineBase_Mqtt,public CXCommSvrWndInterface
{
public:
	CIotVmServer_Mqtt();
	virtual ~CIotVmServer_Mqtt();

public:
	//用于发消息创建IotEngineProtocolServer模块
	CXCommSvrWnd *m_pXCommSvrWnd;
	void OnXTimer(UINT nIDEvent);
	void OnXCommMsg(WPARAM wParam, LPARAM lParam);
	void OnClseDevice(CIotVmProtoToXImp *pIotVmProtocolXImp);

	CDataGroup *m_pVmConfig;
	BOOL OpenVmConfigFile();

public:
	virtual void BufToCmd(CExBaseObject *pCmdBase,char *pBuf,long nLen,const CString &strFormat);

public:
	//断链事件触发接口
	virtual void OnClose(char *pszErr);
	virtual BOOL Init(const char *pszIP,long nPort);
	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN,char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);

	BOOL CreateIotVmProtoToXImp(CSttTestCmd &oTestCmd);
	void SendHeartBeat();
};