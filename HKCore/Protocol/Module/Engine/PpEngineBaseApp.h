#pragma once


// CPpEngineBaseApp
//管理模块实现对整个通讯平台公共部分的管理
//全局函数的定义//全局宏的定义//全局数据接口的定义

/*//脚本执行说明
引擎支持多设备同时通讯
LUA对象只创建一个
每次只执行一段脚本
脚本执行时采用互斥处理，保证任意时间只有一个LUA脚本在执行
每次执行脚本时，记录脚本对象，记录与脚本对象相关的对象
这样，在脚本调用的系统函数中就能够获得当前脚本关联的对象
*/

#include "../Engine/PpScript.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"

#include "PpEngineThreadBase.h"
#include "PpEngineDataMngrCntr.h"

#include "PpDevBaseApp.h"
#include "EngineConfig/PpEngineConfig.h"

//设备模型定义管理

typedef CTLinkListEx<CPpEngineThreadBase>  CPpEngineMngr;

class CPpEngineBaseApp : public CPpDevBaseApp
{
public:
	CPpEngineBaseApp();
	virtual ~CPpEngineBaseApp();

	//调试Engine，此种状态不管通讯处理是否成功，只关注数据处理的过程
	BOOL m_bDebugMode;
	CPpEngineConfig *m_pPpEngineConfig;

public:
#ifdef _debug_spy
	CDebugSpy *m_pDebugSpy;
	CDebugSpy *m_pRunDebugSpy;
#endif

public:
	//初始化
	virtual long InitPpBaseApp();
	virtual long ExitPpBaseApp();
	virtual long ExitEngineThread();
	virtual BOOL IsAllEngineThreadExit();
	BOOL GetProtocolSpy()	{	return m_bProtocolSpy;	}
	void SetProtocolSpy(BOOL bProtocolSpy=TRUE)	
	{	
		m_bProtocolSpy = bProtocolSpy;	/*g_bLogBindQueryErrorInfor = bProtocolSpy;*/
		CXPpPkgLogTool::SetProtocolSpy(m_bProtocolSpy);
	}

	void SetCurrSpyDevice(CDvmDevice *pDevice = NULL)	{		m_pCurrSpyDevice = pDevice;	}
	CDvmDevice* GetCurrSpyDevice()	{		return m_pCurrSpyDevice;	}
	BOOL IsExitEngineThread()	{		return m_bExitEngineThread;	}	

//////////////////////////////////////////////////////////////////////////
//引擎管理部分
private:
	CPpEngineDataMngrCntr *m_pPpEngineDataMngrCntr;
	CAutoCriticSection m_oEngineDataCriticSection;
	BOOL m_bProtocolSpy;
	CDvmDevice *m_pCurrSpyDevice;
	BOOL m_bExitEngineThread;

public:
	CPpEngineDataMngrCntr* GetPpEngineDataMngrCntr(){return m_pPpEngineDataMngrCntr;}
	void ConnectDeviceAll()	{	m_pPpEngineDataMngrCntr->ConnectDeviceAll();	}
	BOOL IsAllDeviceConnectFinished()		{	return m_pPpEngineDataMngrCntr->IsAllDeviceConnectFinished();	}
	void WaitAllDeviceConnectFinished()		{	m_pPpEngineDataMngrCntr->WaitAllDeviceConnectFinished();		}
	BOOL IsAllDeviceEngineThreadExit()	{	return m_pPpEngineDataMngrCntr->IsAllDeviceEngineThreadExit();	}
	void WaitExitAllEngineThread()			{	m_pPpEngineDataMngrCntr->WaitExitAllEngineThread();		}
	void ExitAllEngineThread()					{	m_pPpEngineDataMngrCntr->ExitAllEngineThread();				}

    //2020-11-24  lijunqing
    virtual void OnEngineDataDeleted(const CString &strDeviceID);

public:
	CPpEngineData* FindEngineData(const CString &strID);
	CPpEngineData* Create(const CString &strPpTemplateFile, const CString &strDeviceFile, BOOL bRunEngine=TRUE);  //新建设备
	CPpEngineData* Create();  //新建设备
	BOOL LoadEngineData(CPpEngineData*pEngineData, const CString &strPpTemplateFile, const CString &strDeviceFile);
	BOOL BeginThreadEngine(CPpEngineData *pEngineData);
	BOOL ExitThreadEngine(CPpEngineData *pEngineData);
	BOOL ReleaseEngineData(CPpEngineData *pData);
	void ReleaseEngineDataMngrCntr();
	void DeleteEngineData(CPpEngineData *pData);
	long FindDeviceIndex(CPpEngineData *pData);
	BOOL HasEngineDataDeleted(CPpEngineData *pData);

	virtual void ScriptSetPkgLen(long nLen);
	CPpEngineThreadBase* FindEngineThread(CPpTemplate *pTemplate);

	virtual void GetNomVarScript(CString &strNomVarScript);
	virtual void SerializeTrigerScript(long &nScriptIndex, CExBaseList &listTrigerScript, const CString &strID);
};

extern CPpEngineBaseApp *g_pTheEngineApp;
