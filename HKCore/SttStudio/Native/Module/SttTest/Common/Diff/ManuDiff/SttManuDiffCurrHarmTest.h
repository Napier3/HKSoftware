#pragma once

#include "SttManuDiffCurrThrTest.h"


class CSttManuDiffCurrHarmTest : public CSttManuDiffCurrThrTest
{
public:
    CSttManuDiffCurrHarmTest();
    virtual ~CSttManuDiffCurrHarmTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttManuDiffCurrHarmTest();
	}

public:
	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

protected:
	virtual void TranslateToStateParas();
};
