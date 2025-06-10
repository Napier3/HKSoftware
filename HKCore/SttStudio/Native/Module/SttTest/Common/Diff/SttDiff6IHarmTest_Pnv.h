#pragma once

#include "SttDiffCurrHarmTest.h"


class CSttDiff6IHarmPnvTest : public CSttDiffCurrHarmTest
{
public:
    CSttDiff6IHarmPnvTest();
    virtual ~CSttDiff6IHarmPnvTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttDiff6IHarmPnvTest();
	}

public:
    virtual void AfterSetParameter();

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
protected:
    virtual void TranslateToStateParas();
};
