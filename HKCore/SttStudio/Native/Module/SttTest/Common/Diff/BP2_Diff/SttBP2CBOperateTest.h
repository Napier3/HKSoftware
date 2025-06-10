#pragma once

#include "SttBP2DiffThrTest.h"


class CSttBP2CBOperateTest : public CSttBP2DiffThrTest
{
public:
    CSttBP2CBOperateTest();
    virtual ~CSttBP2CBOperateTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttBP2CBOperateTest();
	}

public:
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent);
	virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent);

protected:
	virtual void TranslateToStateParas();
};
