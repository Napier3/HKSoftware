#pragma once
#include "../SttStateTest.h"

class CSttSmvAbnTest : public CSttStateTest
{
public:
	CSttSmvAbnTest();
	virtual ~CSttSmvAbnTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
		return new CSttSmvAbnTest();
    }

public:
    virtual void StartTest();

public:
    virtual void TtmToDrv();
};


