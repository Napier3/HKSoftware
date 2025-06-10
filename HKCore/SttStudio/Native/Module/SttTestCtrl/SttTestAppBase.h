#ifndef _SttTestAppBase_h__
#define _SttTestAppBase_h__

#include "SttTestCtrlCntrBase.h"
#include "../../Module/XLanguage/XLanguageMngr.h"
#include "../../Module/KeyDb/XKeyDB.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"

#include <QProcess>
#ifndef _PSX_QT_LINUX_
#include <ShellAPI.h>
#include "../Main/Module/SttWgtCmdThread.h"
#endif

//2023-2-21  lijunqing ͨ�Ų���
#include "../SmartTestInterface/PpSttCommConfig.h"

class CSttTestAppBase
{
public:
    QProcess m_Process;
    CSttTestAppBase();
    virtual ~CSttTestAppBase();

	virtual void InitSttTestApp(CXLanguageResourceBase *pLanguage=NULL);
	virtual void ExitSttTestApp();

public:
	void SetSttTestCtrlCntr(CSttTestCtrlCntrBase *pTestCtrlCntr);
	void SetCurrTestMacroUI(const CString &strID);
	void SetCurrTestMacroUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	CString GetCurrTestMacroUI();
	CString GetCurrUI_ID();
	bool IsTestMacro_CurrVolChAsItem();//20230110 �жϵ�ǰ���Թ����Ƿ�Ϊ��ѹ����ͨ������һ���������������ɱ����
	bool IsMuTest();
	bool IsMuTest(const CString &strMacroID);

	//zhouhj 2023.12.19 �Զ����Ե��õ�ʱ��,�Ƿ���Ҫ���д���
	bool SmartTestIsNeedArguments(const CString &strMacroID);

#ifdef _PSX_QT_LINUX_
    BOOL StartSmartTest();
    void ExitSmartTest();
#endif
#ifndef _PSX_QT_LINUX_
	BOOL StartSmartTest(const CString& strMacroID);//zhouhj 2023.7.24 ����ֵΪ�Ƿ�ִ������SmartTest����,���SmartTest�������򷵻�false
	void ExitSmartTest();
	void StartIotProtoServer();
	void ExitIotProtoServer();
	//QSttWgtCmdThread m_oSmartTestThread;
#endif

public:
	CSttTestCtrlCntrBase *m_pTestCtrlCntr;
	CSttMacroTestUI_TestMacroUI *m_pTestMacroUI;

	CXKeyDB *m_pKeyDB;
//////////////////////////////////////////////////////////////////////////
//OnTestCtrlCntrCmd
public:
	void OnCmd_StartTest();
	void OnCmd_StopTest();

//2022-4-11 lijunqing
public:
	virtual void InitSttIecRecord(CSttTestAppCfg* pSttTestAppCfg);
	virtual void ExitSttIecRecord();
	virtual void InitKeyDB();

//2023-2-21  lijunqing  ����װ�õ��豸����ģ��
public:
	CDvmDevice *m_pDvmDevice; 
	CPpSttCommConfig m_oCommConfig;

	void CreateNewDvmDevice();
	void CreateNewDvmDevice(const CString &strFile);
	void OpenDvmDevice(const CString &strFile);
	void FreeDvmDevice();
	void AttachDvmDevice(CDvmDevice *pDevice);
	BOOL IsDeviceNewCreate();
	void OpenPpSttCommConfigFile();

	//2023-03-01 lijunqing Ϊ����߳��������ٶȣ���ͨ����صģ���ͨ�Ž����ʱ����������ʼ��
	virtual void IinitGbWzdAiTool();
};

extern CSttTestAppBase *g_pTheSttTestApp;
extern long g_nLogDebugInfor;

#endif // _SttTestAppBase_h__
