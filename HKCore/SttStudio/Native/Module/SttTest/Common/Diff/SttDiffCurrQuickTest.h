#pragma once

#include "SttDiffCurrThrTest.h"


class CSttDiffCurrQuickTest : public CSttDiffCurrThrTest
{
public:
    CSttDiffCurrQuickTest();
    virtual ~CSttDiffCurrQuickTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttDiffCurrQuickTest();
	}

public:
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
