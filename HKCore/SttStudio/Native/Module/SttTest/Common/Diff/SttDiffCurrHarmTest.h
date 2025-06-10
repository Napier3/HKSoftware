#pragma once

#include "SttDiffCurrThrTest.h"


class CSttDiffCurrHarmTest : public CSttDiffCurrThrTest
{
public:
    CSttDiffCurrHarmTest();
    virtual ~CSttDiffCurrHarmTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttDiffCurrHarmTest();
	}

public:
	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

protected:
	virtual void TranslateToStateParas();
};
