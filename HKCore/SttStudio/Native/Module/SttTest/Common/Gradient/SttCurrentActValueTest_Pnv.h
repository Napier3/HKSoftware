#pragma once

#include "../SttGradientTest.h"
#include "tmt_current_act_value_test.h"


class CSttCurrentActValuePnvTest : public CSttGradientTest
{
public:
    CSttCurrentActValuePnvTest();
    virtual ~CSttCurrentActValuePnvTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttCurrentActValuePnvTest();
	}
public:

	virtual void AfterSetParameter();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	void InitParaBeforeGradient();
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
    virtual void Init();

protected:
	void TranslateToGradientParas();

    tmt_CurActValuePnvParas m_oCurActValuePnvParas;
};
