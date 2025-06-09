#pragma once

#include"MacroTestInterface.h"

#ifdef _USE_SMARTTEST_INTERFACE_COM_
#include"VmMacroTest.h"
#endif

#ifdef _USE_SMARTTEST_INTERFACE_STT_
#include"VmSttMacroTest.h"
#endif

#ifdef _USE_SMARTTEST_INTERFACE_MQTT_
#include"VmMqttMacroTest.h"
#endif

class CMacroTestFactory : public CExBaseList
{
private:
	CMacroTestFactory();
	virtual ~CMacroTestFactory(void);

	static CMacroTestFactory *g_pMacroTestFactory;
	static long g_nMacroTestFactory;

#ifdef _USE_SMARTTEST_INTERFACE_COM_
	CVmMacroTestCreator *m_pVmMacroTestCreator;
#endif

#ifdef _USE_SMARTTEST_INTERFACE_STT_
	CSttMacroTestCreator *m_pSttMacroTestCreator;
#endif

#ifdef _USE_SMARTTEST_INTERFACE_MQTT_
	CVmMqttMacroTestCreator *m_pMqttMacroTestCreator;
#endif

public:
	static CMacroTestFactory* Create();
	static void Release();

	static void RemoveMacroTest(CMacroTestInterface *pMacroTestInterface);
	static CMacroTestEngineInterface* CreateMacroTestEngine(const CString &strMacroFile);
	static void ExecuteMtCmd(const CString &strCmdID, const CString &strCmdPara);
	static void ReleaseMacroTestEngine();
	static void InitMacroTestEngineShowSpyWnd();
	static CMacroTestInterface* GetMacroTest(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps);
	static void ConfigMacroTestEngine(const CString &strMacroFile, const CString &strIP);
	static long AttatchLogWnd(unsigned long hWnd);

private:
	CMacroTestInterface* In_GetMacroTest(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps);
	void In_ConfigMacroTestEngine(const CString &strMacroFile, const CString &strIP);
	CMacroTestInterface* In_GetMacroTest_EngineMode(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps);

};

extern CString g_strActiveTestMacroProgID;

inline BOOL mt_IsVirtualVm(const CString &strProgID)
{
	return strProgID == _T("VirtualVm.TestEngine");
}

inline BOOL mt_IsVirtualVm()
{
	return mt_IsVirtualVm(g_strActiveTestMacroProgID);
}
