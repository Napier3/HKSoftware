#pragma once

#include "SttManuDiffCurrThrTest.h"


class CSttManuDiffCurrRateTest : public CSttManuDiffCurrThrTest
{
public:
    CSttManuDiffCurrRateTest();
    virtual ~CSttManuDiffCurrRateTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttManuDiffCurrRateTest();
	}

public:
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
