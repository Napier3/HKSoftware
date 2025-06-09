#pragma once

#include "../SttGradientTest.h"
#include "tmt_vol_act_value_test.h"


class CSttVolActValueTest : public CSttGradientTest
{
public:
    CSttVolActValueTest();
    virtual ~CSttVolActValueTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttVolActValueTest();
	}
public:

	virtual void AfterSetParameter();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

	void InitParaBeforeGradient();

public:
    virtual void Init();

protected:
	void TranslateToGradientParas();

	tmt_VolActValueParas m_oVolActValueParas;
};
