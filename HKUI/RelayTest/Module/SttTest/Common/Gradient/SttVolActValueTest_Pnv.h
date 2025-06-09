#pragma once

#include "../SttGradientTest.h"
#include "tmt_vol_act_value_test.h"


class CSttVolActValuePnvTest : public CSttGradientTest
{
public:
    CSttVolActValuePnvTest();
    virtual ~CSttVolActValuePnvTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttVolActValuePnvTest();
	}
public:

	virtual void AfterSetParameter();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

	void InitParaBeforeGradient();

public:
    virtual void Init();
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

protected:
	void TranslateToGradientParas();

    tmt_VolActValuePnvParas m_oVolActValuePnvParas;
};
