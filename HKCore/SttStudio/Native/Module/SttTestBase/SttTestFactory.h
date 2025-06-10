#pragma once
#include "SttTestCreator.h"

class CSttTestFactory : public CExBaseList
{
public:
	CSttTestFactory(void);
	virtual ~CSttTestFactory(void);

protected:
	void RegisterTestMacro(const CString &strPxAppName, const CString &strName, const CString &strID, PFNCREATE* pFunCreate);
	CSttTestBase* CreateTestMacroByIndex(long nIndex);

public:
	virtual CSttTestBase* CreateTestMacroByMacroID(const CString &strMacroID);
	BOOL BuildXMLFile(const CString &strPath, const CString &strProgID);
	//20231026 zhoulei 用于SetParameter时不更新g_pCSttServerTestCtrlCntr->m_pCurrSttTest
	CDataGroup m_oMacroIDGroup;
	BOOL FindMacroID_NoChgCurrTest(const CString &strMacroID);
};

extern CSttTestFactory* g_pSttTestFactory;

CSttTestBase* stt_CreateTestMacroByMacroID(const CString &strMacroID);
void stt_BuildTestMacroXmlFile(const CString &strFile);
