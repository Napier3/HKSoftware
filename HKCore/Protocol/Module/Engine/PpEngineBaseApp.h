#pragma once


// CPpEngineBaseApp
//����ģ��ʵ�ֶ�����ͨѶƽ̨�������ֵĹ���
//ȫ�ֺ����Ķ���//ȫ�ֺ�Ķ���//ȫ�����ݽӿڵĶ���

/*//�ű�ִ��˵��
����֧�ֶ��豸ͬʱͨѶ
LUA����ֻ����һ��
ÿ��ִֻ��һ�νű�
�ű�ִ��ʱ���û��⴦����֤����ʱ��ֻ��һ��LUA�ű���ִ��
ÿ��ִ�нű�ʱ����¼�ű����󣬼�¼��ű�������صĶ���
�������ڽű����õ�ϵͳ�����о��ܹ���õ�ǰ�ű������Ķ���
*/

#include "../Engine/PpScript.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"

#include "PpEngineThreadBase.h"
#include "PpEngineDataMngrCntr.h"

#include "PpDevBaseApp.h"
#include "EngineConfig/PpEngineConfig.h"

//�豸ģ�Ͷ������

typedef CTLinkListEx<CPpEngineThreadBase>  CPpEngineMngr;

class CPpEngineBaseApp : public CPpDevBaseApp
{
public:
	CPpEngineBaseApp();
	virtual ~CPpEngineBaseApp();

	//����Engine������״̬����ͨѶ�����Ƿ�ɹ���ֻ��ע���ݴ���Ĺ���
	BOOL m_bDebugMode;
	CPpEngineConfig *m_pPpEngineConfig;

public:
#ifdef _debug_spy
	CDebugSpy *m_pDebugSpy;
	CDebugSpy *m_pRunDebugSpy;
#endif

public:
	//��ʼ��
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
//���������
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
	CPpEngineData* Create(const CString &strPpTemplateFile, const CString &strDeviceFile, BOOL bRunEngine=TRUE);  //�½��豸
	CPpEngineData* Create();  //�½��豸
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
