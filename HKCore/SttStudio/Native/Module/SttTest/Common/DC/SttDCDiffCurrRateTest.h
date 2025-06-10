#pragma once

#include "SttDCDiffCurrThrTest.h"


class CSttDCDiffCurrRateTest : public CSttDCDiffCurrThrTest
{
public:
    CSttDCDiffCurrRateTest();
    virtual ~CSttDCDiffCurrRateTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttDCDiffCurrRateTest();
	}

public:
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
