#pragma once
#include "SttSmvAbnormalTest.h"

class CSttGseAbnTest : public CSttSmvAbnTest
{
public:
	CSttGseAbnTest();
	virtual ~CSttGseAbnTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
		return new CSttGseAbnTest();
    }

public:
    virtual void TtmToDrv();
};


