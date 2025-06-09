#pragma once

#include "SttDiffCurrHarmTest.h"


class CSttDiffCurrHarmTest_I : public CSttDiffCurrHarmTest
{
public:
    CSttDiffCurrHarmTest_I();
    virtual ~CSttDiffCurrHarmTest_I(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttDiffCurrHarmTest_I();
	}

public:

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

protected:
	virtual void TranslateToStateParas();
};
