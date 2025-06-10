#pragma once

#include "../SttCmd/SttSystemCmd.h"
#include "../SttCmd/SttAssistCmd.h"
#include "../SttCmd/SttAtsCmd.h"
#include "../SttCmd/SttDebugCmd.h"
#include "../SttCmd/SttRemoteCmd.h"
#include "../SttCmd/SttSysState.h"
#include "../SttCmd/SttTestCmd.h"
#include "../SttCmd/SttAdjustCmd.h"
#include "../SttGlobalDef.h"

#include "../SttRegisterCode.h"
#include "../SttCmd/GuideBook/SttContents.h"

#ifdef _SttTestServer_For_Debug_
//Debug仍放在Engine路径，以便大家都能获取
#include"../Engine/SttSmartTest_SvrDebug.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"
#else
#include"../SttAtsSvr/XSttSmartTestEntry.h"
#endif

extern CDataGroup *g_pDeviceAttrs;

class CSttAtsInterface
{
public:
	virtual DWORD CreateTest() = 0;
	virtual DWORD StartTest() = 0;
	virtual DWORD StopTest() = 0;
	virtual DWORD TestItem() = 0;
	virtual DWORD TestFrom() = 0;
	virtual DWORD TestAllFailedItems() = 0;
	virtual DWORD GetItemReport() = 0;
	virtual DWORD GetReportFile() = 0;
	virtual DWORD GetSystemState() = 0;
};

class CSttNativeTestEngineInterface : public CPxiDeviceCommCmdMessage, public CSttPkgDispatchInterface
{
public:
	CSttNativeTestEngineInterface();
	virtual ~CSttNativeTestEngineInterface();

public:
	virtual long X_ReturnSysStateToChildren(void *pCommInterface, CSttSysState *pSysState) = 0;
	virtual long X_Ats_InputData(void *pCommInterface, CDataGroup *pDatas,CExBaseList *pMsgs) = 0;

	virtual void OnTimer() = 0;
};


//////////////////////////////////////////////////////////////////////////
//CSttNativeTestEngineInterfaces
//系统可能会同时连接STT协议以及MQTT协议，以及将来的其他协议，只要启动了协议
//就添加到管理对象，数据将返回给全部的连接客户端
typedef CTLinkList<CSttNativeTestEngineInterface> CSttNativeTestEngineInterfaceList;

class  CSttNativeTestEngineInterfaces : public CSttNativeTestEngineInterface, public CSttNativeTestEngineInterfaceList
{
private:
	CSttNativeTestEngineInterfaces();
	virtual ~CSttNativeTestEngineInterfaces();

	static long g_nSttNativeTestEngineInterfaces;
	static CSttNativeTestEngineInterfaces *g_pNativeTestEngineInterfaces;

public:
	static void Create();
	static void Release();

public:  //CSttNativeTestEngineInterface
	virtual long X_ReturnSysStateToChildren(void *pCommInterface, CSttSysState *pSysState);
	virtual long X_Ats_InputData(void *pCommInterface, CDataGroup *pDatas,CExBaseList *pMsgs);

public://CSttPkgDispatchInterface
	 virtual void DispatchMsg(unsigned char *pBuf, long nLen);

public://CPxiDeviceCommCmdMessage
	 virtual void OnCommCmdMessage(WPARAM wParam, LPARAM lParam);
	 virtual void OnSysMessage(WPARAM wParam, LPARAM lParam);

	 void Return_Ats_Success(CSttAtsCmd *pAtsCmd, unsigned int nState=STT_CMD_ExecStatus_SUCCESS, CDvmDataset *pDatas=NULL, CExBaseObject *pGuideBook = NULL);

	 void OnTimer();

};

extern CSttNativeTestEngineInterfaces *g_theNativeTestEngine;
