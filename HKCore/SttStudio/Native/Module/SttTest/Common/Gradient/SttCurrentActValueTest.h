#pragma once

#include "../SttGradientTest.h"
#include "tmt_current_act_value_test.h"


class CSttCurrentActValueTest : public CSttGradientTest
{
public:
    CSttCurrentActValueTest();
    virtual ~CSttCurrentActValueTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttCurrentActValueTest();
	}
public:

	virtual void AfterSetParameter();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	void InitParaBeforeGradient();

public:
    virtual void Init();

protected:
	void TranslateToGradientParas();

	tmt_CurrentActValueParas m_oCurrentActValueParas;
};
