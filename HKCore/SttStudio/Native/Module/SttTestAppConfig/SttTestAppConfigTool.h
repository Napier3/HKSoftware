#ifndef _SttTestAppConfigTool_h_
#define _SttTestAppConfigTool_h_

#include "../../Module/Engine/SttRemoteClientTestEngine.h"
#include "../../Module/Engine/SttClientTestEngine.h"
#include "SttTestAppCfg.h"

#define STT_LOCALCONFIG_DLG_INDEX			0
#define STT_LOCALSCANCONFIG_DLG_INDEX		1
#define STT_REMOTECONFIG_DLG_INDEX			2
#define STT_REMOTESCANCONFIG_DLG_INDEX		3
#define STT_REMOTESCANCONFIG_DLG_ALLINDEX	0xFF

#define TESTAPPCONFIG_OK_MSG			10001
#define TESTAPPCONFIG_LOCKTAB_MSG		10002
/*
2021-8-12  lijunqing  ���ǵ����Ӷ�̨�����ǣ�����ʹ��ȫ�ֵ�CSttTestAppConfigTool
��CSttTestAppCfg����������˴ε��޸ġ�
ͬʱΪ�˼�����������ƽ̨�Ĺ淶��CSttTestAppCfg����DataGroupģʽ�����������
Ϊ�˼���֮ǰ�İ汾���µ������ļ�����Ϊ��TestAppConfig.xml",�������ϵ������ļ���SttTestAppCfg.xml��
*/

class CSttTestAppConfigTool
{
public:
	CSttTestAppConfigTool();
	virtual ~CSttTestAppConfigTool();

	void GetSttTestEngineBase(CSttTestAppCfg *pSttTestAppCfg, CSttTestEngineBase** ppTestEngineBase);
	CSttTestEngineBase* GetSttTestEngineBase(CSttTestAppCfg *pSttTestAppCfg);
	void GetSttTestEngineClientData(CSttTestEngineClientData** ppTestEngineClientData);
	CSttTestEngineClientData* GetSttTestEngineClientData();

	CSttTestEngineClientData* CreateTestEngine(CSttTestAppCfg *pSttTestAppCfg);

#ifndef _PSX_IDE_QT_
	void TestAppConfig(CSttTestEngineClientData **ppXClientEngine, CSttTestMsgViewInterface *pMsgView, CWnd *pParentWnd);
#endif
	
protected:
	CSttTestEngineClientData* CreateTestCtrlEngine(CSttTestAppCfg *pSttTestAppCfg, const CString &strSoftID);
	CSttTestEngineClientData* CreateAtsEngine(CSttTestAppCfg *pSttTestAppCfg, const CString &strSoftID);

public:
	CSttTestAppCfg *m_pSttTestAppCfg;

	CSttTestMsgViewInterface *m_pSttTestMsgViewInterface;
	CString m_strSoftID;
	CString m_strServerID;  //2020-11-29  lijunqing  ���ӵķ����ID
	CSttTestEngineClientData *m_pClientEngine;
	void FreeClientEngine();
	void UpdateClientEngine();

public:
	BOOL Local_ConnectServer();
	BOOL Remote_ConnectServer();
	BOOL Remote_DisconnectServer();
	BOOL Local_ConnectServer(CSttTestAppCfg *pSttTestAppCfg, const CString &strIP,long nPort
		,const CString &strIdSoft=STT_SOFT_ID_TEST, CTestEventBaseInterface *pTestEventRcv=NULL);
	BOOL Remote_ConnectServer(CSttTestAppCfg *pSttTestAppCfg, const CString &strIP,long nPort);
	BOOL Remote_BindAndLogin(CSttTestAppCfg *pSttTestAppCfg, CSttTestRemoteRegister *pRegister,CSttTestClientUser *pUser);
	BOOL ConnectServer(CSttTestAppCfg *pSttTestAppCfg, const CString &strIP,long nPort);

	static BOOL IsTestAppExist(CSttTestAppCfg *pSttTestAppCfg);
	static BOOL IsCloudServerExist(CSttTestAppCfg *pSttTestAppCfg);

};

// extern CSttTestAppConfigTool g_oSttTestAppConfigTool;


#endif