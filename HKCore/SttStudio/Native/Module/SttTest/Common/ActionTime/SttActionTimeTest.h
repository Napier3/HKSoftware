#pragma once

#include "../SttStateTest.h"
#include "tmt_action_time_test.h"


class CSttActionTimeTest : public CSttStateTest ,public tmt_ActionTimeParas
{
public:
    CSttActionTimeTest();
    virtual ~CSttActionTimeTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttActionTimeTest();
	}
public:

	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);

protected:
	virtual void TranslateToStateParas();

	tmt_ActionTimeResults m_oActionTimeResults;
};
