#pragma once

#include "SttManuDiffCurrThrTest.h"


class CSttManuDiffCurrQuickTest : public CSttManuDiffCurrThrTest
{
public:
    CSttManuDiffCurrQuickTest();
    virtual ~CSttManuDiffCurrQuickTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttManuDiffCurrQuickTest();
	}

public:
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
