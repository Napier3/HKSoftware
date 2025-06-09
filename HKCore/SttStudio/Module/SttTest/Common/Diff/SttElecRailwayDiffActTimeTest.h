#pragma once

#include "SttElecRailwayDiffThrTest.h"


class CSttElecRailwayDiffActTimeTest : public CSttElecRailwayDiffThrTest
{
public:
    CSttElecRailwayDiffActTimeTest();
    virtual ~CSttElecRailwayDiffActTimeTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttElecRailwayDiffActTimeTest();
	}

public:
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent);
	virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent);
};
